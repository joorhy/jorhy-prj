#include "x_decoder.h"
#include "x_errtype.h"

CXDecoder::CXDecoder(CXRender *render)
{
	m_pRender = render;
}

CXDecoder::~CXDecoder()
{
	
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
	decode_write_frame();
	
    avcodec_close(m_context);
    av_free(m_context);
    avcodec_free_frame(&m_frame);
}

int CXDecoder::decode_write_frame()
{
    int len, got_frame;
    len = avcodec_decode_video2(m_context, m_frame, &got_frame, &m_avpkt);
    if (len < 0) {
        return len;
    }
    if (got_frame) {
        /* the picture is allocated by the decoder, no need to free it */
        //pgm_save(m_frame->data[0], m_frame->linesize[0],
        //         m_context->width, m_context->height, buf);
    }
    if (m_avpkt.data) {
        m_avpkt.size -= len;
        m_avpkt.data += len;
    }
    return 0;
}

int CXDecoder::InputData(const char *pData, int nLen)
{
	m_avpkt.data = (uint8_t *)pData;
    m_avpkt.size = nLen;
	if (decode_write_frame() < 0)
		return J_UNKNOW;
		
	return J_OK;
}

void *CXDecoder::Entry()
{
	return NULL;
}

		
void CXDecoder::OnExit()
{
	
}