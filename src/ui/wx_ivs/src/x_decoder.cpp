#include "x_decoder.h"
#include "x_errtype.h"
#include "x_render.h"

const char header[4] = { 0x00, 0x00, 0x00, 0x01 };

CXDecoder::CXDecoder(CXRender *render)
{
	m_sws_ctx = NULL;
	m_pRender = render;
	m_bRun = false;
}

CXDecoder::~CXDecoder()
{
	
}

int CXDecoder::Start()
{
	if (!m_bRun)
	{
		InitDecoder();
		m_bRun = true;
		Create();
		Run();
	}
	return J_OK;
}

void CXDecoder::Stop()
{
	if (m_bRun)
	{
		m_bRun = false;
		m_sem.WaitTimeout(1000);
		DeinitDecoder();
		//Delete();
	}
}

int CXDecoder::AspectRatio(int w, int h)
{
	m_locker.Lock();
	m_width = w;
	m_height = h;
	m_locker.Unlock();
	
	return 0;
}

int CXDecoder::InitDecoder()
{
	//LIBAVCODEC_VERSION_MAJOR
	/* register all the codecs */
    avcodec_register_all();
	
	av_init_packet(&m_avpkt);
	m_codec = avcodec_find_decoder(AV_CODEC_ID_H264);
	if (!m_codec) 
	{
        fprintf(stderr, "CXDecoder::InitDecoder() Codec not found\n");
        return J_UNKNOW;
    }
	
	m_context = avcodec_alloc_context3(m_codec);
    if (!m_context) {
        fprintf(stderr, "CXDecoder::InitDecoder()Could not allocate video codec context\n");
        return J_UNKNOW;
    }
	
    if(m_codec->capabilities & CODEC_CAP_TRUNCATED)
        m_context->flags|= CODEC_FLAG_TRUNCATED; /* we do not send complete frames */

    /* For some codecs, such as msmpeg4 and mpeg4, width and height
       MUST be initialized there because this information is not
       available in the bitstream. */

    /* open it */
    if (avcodec_open2(m_context, m_codec, NULL) < 0) 
	{
        fprintf(stderr, "CXDecoder::InitDecoder() Could not open codec\n");
        return J_UNKNOW;
    }
	
	m_frame = avcodec_alloc_frame();
    if (!m_frame) {
        fprintf(stderr, "CXDecoder::InitDecoder() Could not allocate video frame\n");
        return J_UNKNOW;
    }
	
	return J_OK;
}

void CXDecoder::DeinitDecoder()
{
	//DecodeRendFrame(NULL, 0);
	sws_freeContext(m_sws_ctx);
    avcodec_close(m_context);
    av_free(m_context);
    avcodec_free_frame(&m_frame);
}

int CXDecoder::DecodeRendFrame(const char *pData, int nLen)
{
	m_avpkt.data = (uint8_t *)pData;
	m_avpkt.size = nLen;
    int len, got_frame;
	len = avcodec_decode_video2(m_context, m_frame, &got_frame, &m_avpkt);
	if (len < 0) 
	{
		return len;
	}
	if (got_frame > 0) 
	{
		m_locker.Lock();
		m_dataLen = av_image_alloc(m_dst_data, m_dst_linesize,
							  m_width, m_height, AV_PIX_FMT_RGB24, 1);
							  
		m_srcLen = av_image_alloc(m_src_data, m_src_linesize,
							  m_context->width, m_context->height, AV_PIX_FMT_YUV420P, 16);
							  
		m_sws_ctx = sws_getCachedContext(m_sws_ctx,
					  m_context->width, m_context->height, AV_PIX_FMT_YUV420P,
					  m_width, m_height,  AV_PIX_FMT_RGB24, SWS_BILINEAR, NULL, NULL, NULL);
					  
		for (int i=0; i<m_context->height; i++)
		{
			memcpy(m_src_data[0] + i * m_src_linesize[0], m_frame->data[0] + i * m_frame->linesize[0], m_src_linesize[0]);
		}
		
		for (int i=0; i<m_context->height/2; i++)
		{
			memcpy(m_src_data[1] + i * m_src_linesize[1], m_frame->data[1] + i * m_frame->linesize[1], m_src_linesize[1]);
			memcpy(m_src_data[2] + i * m_src_linesize[2], m_frame->data[2] + i * m_frame->linesize[2], m_src_linesize[2]);
		}
			
		sws_scale(m_sws_ctx, m_src_data, m_src_linesize,
			  0, m_context->height, m_dst_data, m_dst_linesize);
		m_pRender->InputData((const char *)m_dst_data[0], m_dataLen);
		av_freep(&m_dst_data[0]);
		av_freep(&m_src_data[0]);
		
		/*if (m_avpkt.data) 
		{
			m_avpkt.size -= len;
			if (m_avpkt.size > 0)
			{
				memmove(m_avpkt.data, m_avpkt.data + len, m_avpkt.size);
			}
		}*/
		m_locker.Unlock();
	}
	
    return 0;
}

int CXDecoder::InputData(const char *pData, int nLen)
{
	m_buffer.PushData(pData, nLen);
	//DecodeRendFrame(pData, nLen);
		
	return J_OK;
}

void *CXDecoder::Entry()
{
	char *pBuffer = new char[1024 * 1024];
	int nLen = 0;
	m_avpkt.size = 0;
	while (m_bRun)
	{
		nLen = m_buffer.PopData(pBuffer);
		if (nLen == 0)
			usleep(1);
		else 
		{
			DecodeRendFrame(pBuffer, nLen);
		}
	}
	delete pBuffer;

	return NULL;
}

		
void CXDecoder::OnExit()
{
	m_sem.Post();
}