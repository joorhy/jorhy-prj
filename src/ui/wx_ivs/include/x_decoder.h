#ifndef __X_DECODER_H_
#define __X_DECODER_H_

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/thread.h>

#include "x_buffer.h"

extern "C"
{
	#include <libavcodec/avcodec.h>
	#include <libswscale/swscale.h>
	#include <libavutil/imgutils.h>
}

class CXRender;
class CXDecoder : public wxThread
{
	public:
		CXDecoder(CXRender *render);
		~CXDecoder();
	
	public:
		int Start();
		void Stop();
		int InputData(const char *pData, int nLen);
		
		
	public:
		virtual void *Entry();
		virtual void OnExit();
	
	private:
		int InitDecoder();
		void DeinitDecoder();
		int DecodeRendFrame();
							  
	private:
		CXRender *m_pRender;
		char *m_pBuffer;
		uint8_t *m_dst_data[4];
		int m_dst_linesize[4];
		int m_dataLen;
		AVCodec *m_codec;
		AVCodecContext *m_context;
		AVFrame *m_frame;
		AVPacket m_avpkt;
		struct SwsContext *m_sws_ctx;
		CXBuffer m_buffer;
		bool m_bRun;
		bool m_bAllocPicture;
};
#endif //~__X_DECODER_H_