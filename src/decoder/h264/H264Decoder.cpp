#include "H264Decoder.h"

void *CH264Decoder::m_mtx = NULL;

JO_IMPLEMENT_INTERFACE(Decoder, "h264", CH264Decoder::Maker)

CH264Decoder::CH264Decoder()
{
	m_bInit = false;
}

CH264Decoder::~CH264Decoder()
{

}

j_result_t CH264Decoder::InidDecoder()
{
	J_OS::LOGINFO("CH264Decoder::InidDecoder");
#if LIBAVCODEC_VERSION_MAJOR < 54
	avcodec_init();
#endif
	avcodec_register_all();
#ifdef _DEBUG
	av_log_set_callback(LogCallBack);
#endif
	av_lockmgr_register(lockmgr);
	av_init_packet(&m_Packet);
#ifdef WIN32
	m_pCodec	= avcodec_find_decoder(CODEC_ID_H264);
	m_pContext	= avcodec_alloc_context();
#else
	m_pCodec	= avcodec_find_decoder(AV_CODEC_ID_H264);
	m_pContext	= avcodec_alloc_context3(m_pCodec);
#endif
	if(!m_pCodec || !m_pContext)
		return J_DECODER_INIT_ERROR;

	if(m_pCodec->capabilities & CODEC_CAP_TRUNCATED)
		m_pContext->flags|= CODEC_FLAG_TRUNCATED;  /*we do not send complete frames */

#ifdef WIN32
	if(avcodec_open(m_pContext,m_pCodec) < 0)
#else
	if(avcodec_open2(m_pContext,m_pCodec, NULL) < 0)
#endif
		return J_DECODER_INIT_ERROR;
	
	m_pPicture	= avcodec_alloc_frame();
	if (!m_pPicture)
		return J_DECODER_INIT_ERROR;
		
	m_bInit = true;

	return J_OK;
}

j_result_t CH264Decoder::FlushBuffer()
{
	J_OS::LOGINFO("CH264Decoder::FlushBuffer");
	avcodec_flush_buffers(m_pContext);
	return J_OK;
}

j_result_t CH264Decoder::GetDecodeParam(J_VideoDecodeParam &decParam)
{
	decParam = m_decParam;
	return J_OK;
}

j_result_t CH264Decoder::DecodeOneFrame(j_char_t *pInputData, j_int32_t nInputLen, j_char_t *pOutuptData, j_int32_t &nOutputLen)
{
	nOutputLen = 0;
	if (!m_bInit)
	{
		return J_OK;
	}

	int nRet = 0;
	int got_frame;
	m_Packet.data	= (uint8_t *)pInputData;
	m_Packet.size	= nInputLen;
	nRet = avcodec_decode_video2(m_pContext, m_pPicture, &got_frame, &m_Packet);
	if(nRet < 0)
	{
		J_OS::LOGINFO("CXPlDecodeH264::Decode error :%d\n",nRet);
		return J_OK;
	}
	
	InitDecodeParam(m_decParam);
	nOutputLen = CopyData(m_pPicture, pOutuptData, nOutputLen);

	return J_OK;
}

j_result_t CH264Decoder::DeinitDecoder()
{
	if(m_pContext)
	{
		avcodec_close(m_pContext);
		av_free(m_pContext);
	}
	if(m_pPicture)
	{
		av_free(m_pPicture);
	}
	av_free_packet(&m_Packet);

	return J_OK;
}

j_result_t CH264Decoder::InitDecodeParam(J_VideoDecodeParam &decParam)
{
	decParam.fourcc_type	= jo_codec_yv12;
	decParam.vout_dev		= jo_dev_ddraw;
	decParam.height			= m_pContext->height;
	decParam.width			= m_pContext->width;

	return J_OK;
}

j_int32_t CH264Decoder::CopyData(AVFrame *frame, j_char_t *pOutputData ,j_int32_t &nOutputLen)
{
	int len = 0;
	uint8_t *pYuvData = NULL;
	int height	= 0;
	int width	= 0;

	pYuvData = frame->data[0];
	if (pYuvData == NULL)
		return len;

	height	= m_pContext->height;
	width	= m_pContext->width;
	
#ifdef WIN32
	for(int i=0;i<height;i++)
	{
		memcpy(pOutputData,pYuvData,width);
		len		+= width;
		pYuvData+= frame->linesize[0];
		pOutputData += width;
	}

	pYuvData = frame->data[1];
	height = m_pContext->height / 2;
	width	= m_pContext->width / 2;
	for(int i=0;i<height;i++)
	{
		memcpy(pOutputData,pYuvData,width);
		len		+= width;
		pYuvData+= frame->linesize[1];
		pOutputData += width;
	}

	pYuvData = frame->data[2];
	height = m_pContext->height / 2;
	width	= m_pContext->width / 2;
	for(int i=0;i<height;i++)
	{
		memcpy(pOutputData,pYuvData,width);
		len		+= width;
		pYuvData+= frame->linesize[2];
		pOutputData += width;
	}
#else
		int dst_linesize[4];
		uint8_t *dst_data[4];
		int dataLen = av_image_alloc(dst_data, dst_linesize,
							  m_width, m_height, AV_PIX_FMT_RGB24, 1);
		
		uint8_t *src_data[4];
		int src_linesize[4];
		int srcLen = av_image_alloc(src_data, src_linesize,
							 width, height, AV_PIX_FMT_YUV420P, 16);
			
		struct SwsContext *sws_ctx = NULL;
		sws_ctx = sws_getCachedContext(sws_ctx,
					  width, height, AV_PIX_FMT_YUV420P,
					  m_width, m_height,  AV_PIX_FMT_RGB24, SWS_FAST_BILINEAR, NULL, NULL, NULL);
				
		for (int i=0; i<height; i++)
		{
			memcpy(src_data[0] + i * src_linesize[0], frame->data[0] + i * frame->linesize[0], src_linesize[0]);
		}
		
		for (int i=0; i<height/2; i++)
		{
			memcpy(src_data[1] + i * src_linesize[1], frame->data[1] + i * frame->linesize[1], src_linesize[1]);
			memcpy(src_data[2] + i * src_linesize[2], frame->data[2] + i * frame->linesize[2], src_linesize[2]);
		}
		
		sws_scale(sws_ctx, src_data, src_linesize,
			  0, height, dst_data, dst_linesize);
		
		memcpy(pOutputData, (const char *)dst_data[0],dataLen);
		nOutputLen = dataLen;
		len = dataLen;
		av_freep(&dst_data[0]);
		av_freep(&src_data[0]);
#endif

	return len;
}

void CH264Decoder::LogCallBack(void *pUser, int level, const char *fmt, va_list args)
{
	//va_start(args, fmt);
	J_OS::LOGINFO(fmt, args);
	//va_end(args);
}

int CH264Decoder::lockmgr(void **mtx, enum AVLockOp op)
{
	switch(op) 
	{
	case AV_LOCK_CREATE:
		if (m_mtx == NULL)
			m_mtx = new J_OS::CTLock();
		*mtx = m_mtx;
		return 0;
	case AV_LOCK_OBTAIN:
		(( J_OS::CTLock *)(*mtx))->_Lock();
		return 0;
	case AV_LOCK_RELEASE:
		(( J_OS::CTLock *)(*mtx))->_Unlock();
		return 0;
	case AV_LOCK_DESTROY:
		//delete ((J_PlMutexLock *)(*mtx));
		return 0;
	}
	return 1;
}