#pragma once
#include "x_pl_video_decode.h"

extern "C"
{
#include "libavcodec\avcodec.h"
};

class CXPlDecodeH264 : public J_PlVideoDecode
{
public:
	CXPlDecodeH264(void);
	~CXPlDecodeH264(void);

	virtual J_PL_RESULT Decode(char *IN_buf,int In_len,char *OUT_buf,int *OUT_len, j_pl_video_info_t &vInfo);
	virtual J_PL_RESULT FlushBuffer();
	virtual J_PL_RESULT GetOutputType(j_pl_video_out_t &t);
	virtual J_PL_RESULT InitDecode();

protected:
	virtual J_PL_RESULT SetOutputType(j_pl_video_out_t &t);

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
