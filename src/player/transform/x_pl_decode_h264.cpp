#include "x_pl_decode_h264.h"
#include "x_pl_error.h"
#include "x_pl_file.h"
#include "x_pl_log.h"
#include "x_pl_thread.h"

void *CXPlDecodeH264::m_mtx = NULL;
CXPlDecodeH264::CXPlDecodeH264(void)
{
	m_pContext	= NULL;
	m_pPicture	= NULL;
	m_pCodec	= NULL;
	m_codeID	= CODE_H264;
	InitDecode();
}

CXPlDecodeH264::~CXPlDecodeH264(void)
{
	Release();
}

J_PL_RESULT CXPlDecodeH264::FlushBuffer()
{
	avcodec_flush_buffers(m_pContext);
	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlDecodeH264::Decode(char *IN_buf,int In_len,char *OUT_buf,int *OUT_len)
{
	int nRet = 0;
	int size = 0;
	m_Packet.data	= (uint8_t*)IN_buf;
	m_Packet.size	= In_len;
	nRet = avcodec_decode_video2(m_pContext,m_pPicture,&size,&m_Packet);
	if(nRet < 0)
	{
		j_pl_error("CXPlDecodeH264::Decode error :%d\n",nRet);
		return J_PL_NO_ERROR;
	}

	SetOutputType(m_voutT);
	*OUT_len = CopyData(m_pPicture,OUT_buf,OUT_len);

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlDecodeH264::GetOutputType(j_pl_video_out_t &t)
{
	t = m_voutT;
	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlDecodeH264::InitDecode()
{
#if LIBAVCODEC_VERSION_MAJOR < 54
	avcodec_init();
#endif
	avcodec_register_all();
#ifdef _DEBUG
	av_log_set_callback(LogCallBack);
#endif
	av_lockmgr_register(lockmgr);
	m_pCodec	= avcodec_find_decoder(CODEC_ID_H264);
	m_pContext	= avcodec_alloc_context();
	m_pPicture	= avcodec_alloc_frame();
	av_init_packet(&m_Packet);
	if(!m_pCodec || !m_pContext || !m_pPicture)
		return J_PL_ERROR_DECODE_INIT;

	//if(m_pCodec->capabilities & CODEC_CAP_TRUNCATED)
	//	m_pContext->flags|= CODEC_FLAG_TRUNCATED; /* we do not send complete frames */

	if(avcodec_open(m_pContext,m_pCodec) < 0)
		return J_PL_ERROR_DECODE_INIT;

	return J_PL_NO_ERROR;
}

int CXPlDecodeH264::CopyData(AVFrame *frame,char *OUT_buf,int *OUT_len)
{
	int len = 0;
	uint8_t *pYuvData = NULL;
	int height	= 0;
	int width	= 0;

	pYuvData = frame->data[0];
	height	= m_pContext->height;
	width	= m_pContext->width;
	for(int i=0;i<height;i++)
	{
		memcpy(OUT_buf,pYuvData,width);
		len		+= width;
		pYuvData+= frame->linesize[0];
		OUT_buf += width;

	}
	

	pYuvData = frame->data[1];
	height = m_pContext->height / 2;
	width	= m_pContext->width / 2;
	for(int i=0;i<height;i++)
	{
		memcpy(OUT_buf,pYuvData,width);
		len		+= width;
		pYuvData+= frame->linesize[1];
		OUT_buf += width;
	}

	pYuvData = frame->data[2];
	height = m_pContext->height / 2;
	width	= m_pContext->width / 2;
	for(int i=0;i<height;i++)
	{
		memcpy(OUT_buf,pYuvData,width);
		len		+= width;
		pYuvData+= frame->linesize[2];
		OUT_buf += width;
	}
	
	return len;
}

J_PL_RESULT CXPlDecodeH264::SetOutputType(j_pl_video_out_t &t)
{
	t.FourCCType	= J_PL_CODEC_YV12;
	t.VoutDev		= J_PL_DDRAW;
	t.height		= m_pContext->height;
	t.width			= m_pContext->width;

	return J_PL_NO_ERROR;
}

void CXPlDecodeH264::Release()
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
}

void CXPlDecodeH264::LogCallBack(void *pUser, int level, const char *fmt, va_list args)
{
	va_start(args, fmt);
	j_pl_error(fmt,args);
	va_end(args);
}

int CXPlDecodeH264::lockmgr(void **mtx, enum AVLockOp op)
{
	switch(op) 
	{
		case AV_LOCK_CREATE:
			if (m_mtx == NULL)
				m_mtx = new J_PlMutexLock();
			*mtx = m_mtx;
			return 0;
		case AV_LOCK_OBTAIN:
			((J_PlMutexLock *)(*mtx))->Lock();
			return 0;
		case AV_LOCK_RELEASE:
			((J_PlMutexLock *)(*mtx))->Unlock();
			return 0;
		case AV_LOCK_DESTROY:
			//delete ((J_PlMutexLock *)(*mtx));
			return 0;
	}
	return 1;
}