#pragma once
#include "..\include\btkvideodecode.h"

extern "C"
{
#include "libavcodec\avcodec.h"
};

class BTKDecodeH264 : public BTKVideoDecode
{
public:
	BTKDecodeH264(void);
	~BTKDecodeH264(void);

	virtual BTK_RESULT Decode(char *IN_buf,int In_len,char *OUT_buf,int *OUT_len);
	virtual BTK_RESULT GetOutputType(btk_video_out_t &t);
	virtual BTK_RESULT InitDecode();

protected:
	virtual BTK_RESULT SetOutputType(btk_video_out_t &t);

private:
	int CopyData(AVFrame *frame,char *OUT_buf,int *OUT_len);
	void Release();
	void SetDebugInfo();
	void ReleaseDebugInfo();
	static void LogCallBack(void*, int, const char*, va_list);
	static int lockmgr(void **mtx, enum AVLockOp op);

private:
	static void *m_mtx;
	AVCodecContext *m_pContext;
	AVFrame *m_pPicture;
	AVPacket m_Packet;
	AVCodec *m_pCodec;

};
