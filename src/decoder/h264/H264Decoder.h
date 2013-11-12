#ifndef __H264DECODER_H_
#define __H264DECODER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
extern "C"{
	#include "libavcodec/avcodec.h"
	#include "libavformat/avformat.h"
	#include "libswscale/swscale.h"
#ifndef WIN32 
	#include "libavutil/imgutils.h"
#endif
}

class CH264Decoder : public J_Decoder
{
public:
	CH264Decoder();
	~CH264Decoder();

	static int Maker(J_Obj *&pObj)
	{
		pObj = new CH264Decoder();
		return J_OK;
	}

public:
	///J_Decoder
	virtual j_result_t InidDecoder();
	virtual j_result_t FlushBuffer();
	virtual j_result_t GetDecodeParam(J_VideoDecodeParam &decParam);
	virtual j_result_t DecodeOneFrame(j_char_t *pInputData, j_int32_t nInputLen, j_char_t *pOutuptData, j_int32_t &nOutputLen);
	virtual j_result_t DeinitDecoder();
	virtual j_result_t AspectRatio(j_int32_t nWidth, j_int32_t nHeight)
	{
		m_width = nWidth;
		m_height = nHeight;
		return J_OK;
	}

private:
	j_result_t InitDecodeParam(J_VideoDecodeParam &decParam);
	j_int32_t CopyData(AVFrame *frame, j_char_t *pOutputData ,j_int32_t &nOutputLen);
	static void LogCallBack(void*, int, const char*, va_list);
	static int lockmgr(void **mtx, enum AVLockOp op);

private:
	static void *m_mtx;
	AVCodecContext *m_pContext;
	AVFrame *m_pPicture;
	AVPacket m_Packet;
	AVCodec *m_pCodec;
	j_boolean_t m_bInit;
	j_int32_t m_width;
	j_int32_t m_height;
	
#ifndef WIN32
	int m_dataLen;
	int m_dst_linesize[4];
	uint8_t *m_dst_data[4];
	int m_srcLen;
	uint8_t *m_src_data[4];
	int m_src_linesize[4];
	struct SwsContext *m_sws_ctx;
#endif
};

#endif //~__H264DECODER_H_