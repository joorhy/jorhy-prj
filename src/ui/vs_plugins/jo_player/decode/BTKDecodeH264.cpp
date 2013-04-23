#include "BTKDecodeH264.h"
#include "..\include\BTKError.h"
#include "..\include\BTKFile.h"
#include "..\include\BTKLog.h"
#include "..\include\BTKThread.h"

void *BTKDecodeH264::m_mtx = NULL;
BTKDecodeH264::BTKDecodeH264(void)
{
	m_pContext	= NULL;
	m_pPicture	= NULL;
	m_pCodec	= NULL;
	m_codeID	= CODE_H264;
	InitDecode();
}

BTKDecodeH264::~BTKDecodeH264(void)
{
	Release();
}

BTK_RESULT BTKDecodeH264::FlushBuffer()
{
	avcodec_flush_buffers(m_pContext);
	return BTK_NO_ERROR;
}

BTK_RESULT BTKDecodeH264::Decode(char *IN_buf,int In_len,char *OUT_buf,int *OUT_len)
{
	int nRet = 0;
	int size = 0;
	m_Packet.data	= (uint8_t*)IN_buf;
	m_Packet.size	= In_len;
	nRet = avcodec_decode_video2(m_pContext,m_pPicture,&size,&m_Packet);
	if(nRet < 0)
	{
		btk_Error("BTKDecodeH264::Decode error :%d\n",nRet);
		return BTK_ERROR_DECODE;
	}

	SetOutputType(m_voutT);
	*OUT_len = CopyData(m_pPicture,OUT_buf,OUT_len);

	return BTK_NO_ERROR;
}

BTK_RESULT BTKDecodeH264::GetOutputType(btk_video_out_t &t)
{
	t = m_voutT;
	return BTK_NO_ERROR;
}

BTK_RESULT BTKDecodeH264::InitDecode()
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
		return BTK_ERROR_DECODE_INIT;

	//if(m_pCodec->capabilities & CODEC_CAP_TRUNCATED)
	//	m_pContext->flags|= CODEC_FLAG_TRUNCATED; /* we do not send complete frames */

	if(avcodec_open(m_pContext,m_pCodec) < 0)
		return BTK_ERROR_DECODE_INIT;

	return BTK_NO_ERROR;
}

int BTKDecodeH264::CopyData(AVFrame *frame,char *OUT_buf,int *OUT_len)
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

BTK_RESULT BTKDecodeH264::SetOutputType(btk_video_out_t &t)
{
	t.FourCCType	= BTK_CODEC_YV12;
	t.VoutDev		= BTK_DDRAW;
	t.height		= m_pContext->height;
	t.width			= m_pContext->width;

	return BTK_NO_ERROR;
}

void BTKDecodeH264::Release()
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

void BTKDecodeH264::LogCallBack(void *pUser, int level, const char *fmt, va_list args)
{
	va_start(args, fmt);
	btk_Error(fmt,args);
	va_end(args);
}

int BTKDecodeH264::lockmgr(void **mtx, enum AVLockOp op)
{
	switch(op) 
	{
		case AV_LOCK_CREATE:
			if (m_mtx == NULL)
				m_mtx = new BTKMutexLock();
			*mtx = m_mtx;
			return 0;
		case AV_LOCK_OBTAIN:
			((BTKMutexLock *)(*mtx))->Lock();
			return 0;
		case AV_LOCK_RELEASE:
			((BTKMutexLock *)(*mtx))->Unlock();
			return 0;
		case AV_LOCK_DESTROY:
			//delete ((BTKMutexLock *)(*mtx));
			return 0;
	}
	return 1;
}