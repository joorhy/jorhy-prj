#include "x_decoder.h"
#include "x_errtype.h"
#include "x_render.h"

CXDecoder::CXDecoder(CXRender *render)
{
	m_bAllocPicture = false;
	m_sws_ctx = NULL;
	m_pRender = render;
	m_bRun = false;
	m_pBuffer = new char[1024 * 1024 * 5];
}

CXDecoder::~CXDecoder()
{
	delete m_pBuffer;
}

int CXDecoder::Start()
{
	InitDecoder();
	m_bRun = true;
	Create();
	Run();
	return J_OK;
}

void CXDecoder::Stop()
{
	m_bRun = false;
}

int CXDecoder::InitDecoder()
{
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
	m_avpkt.data = NULL;
    m_avpkt.size = 0;
	DecodeRendFrame();
	
	if (m_bAllocPicture)
	{
		av_freep(&m_dst_data[0]);
		m_bAllocPicture = false;
	}
	sws_freeContext(m_sws_ctx);
    avcodec_close(m_context);
    av_free(m_context);
    avcodec_free_frame(&m_frame);
}

int CXDecoder::DecodeRendFrame()
{
    int len, got_frame;
    len = avcodec_decode_video2(m_context, m_frame, &got_frame, &m_avpkt);
    if (len < 0) {
        return len;
    }
    if (got_frame) {
        /* the picture is allocated by the decoder, no need to free it */
		
		if (!m_bAllocPicture)
		{
			m_dataLen = av_image_alloc(m_dst_data, m_dst_linesize,
                              352, 288, PIX_FMT_YUV420P, 1);
			m_bAllocPicture = true;
		}
		if (m_sws_ctx == NULL)
		{
			m_sws_ctx = sws_getContext(m_context->width, m_context->height, PIX_FMT_YUV420P,
                             352, 288, PIX_FMT_RGB24,
                             SWS_BILINEAR, NULL, NULL, NULL);
		}
		
		m_sws_ctx = sws_getCachedContext(m_sws_ctx,
                      m_context->width, m_context->height, PIX_FMT_YUV420P,
                      352, 288,  PIX_FMT_RGB24, SWS_X, NULL, NULL, NULL);

		sws_scale(m_sws_ctx, m_frame->data, m_frame->linesize,
              352, 288, m_dst_data, m_dst_linesize);
		//int nLen = 0;
		//for(int i=0; i<m_context->height; i++)
		//{
		//	memcpy(m_pBuffer + nLen, (const char *)m_frame->data[0] + i * m_frame->linesize[0], m_context->width);
		//	nLen += m_context->width;
		//	m_pRender->InputData((const char *)m_frame->data[0] + i * m_frame->linesize[0], m_context->width);
		//}
		m_pRender->InputData((const char *)m_dst_data[0], m_dataLen);
			
		fprintf(stderr, "w = %d h = %d d_len = %d\n", m_context->width, m_context->height, m_dataLen);
    }
    return 0;
}

int CXDecoder::InputData(const char *pData, int nLen)
{
	/*static FILE *fp = NULL;
	if (fp == NULL)
		fp = fopen("test.h264", "wb+");
	fwrite (pData, 1, nLen, fp);*/
	m_buffer.PushData(pData, nLen);
		
	return J_OK;
}

void *CXDecoder::Entry()
{
	char *pBuffer = new char[1024 * 1024];
	int nLen = 0;
	while (m_bRun)
	{
		nLen = m_buffer.PopData(pBuffer);
		if (nLen == 0)
			usleep(1);
		else 
		{
			//fprintf(stderr, "nLen = %d\n", nLen);
			m_avpkt.data = (uint8_t *)pBuffer;
			m_avpkt.size = nLen;
			DecodeRendFrame();
		}
	}
	delete pBuffer;

	return NULL;
}

		
void CXDecoder::OnExit()
{
	DeinitDecoder();
	Delete();
}