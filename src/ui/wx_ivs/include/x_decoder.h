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
		int AspectRatio(int w, int h);
		int Resize(int x, int y);
		int InputData(const char *pData, int nLen);
		
		
	public:
		virtual void *Entry();
		virtual void OnExit();
	
	private:
		int InitDecoder();
		void DeinitDecoder();
		int DecodeRendFrame(const char *pData, int nLen);
							  
	private:
		CXRender *m_pRender;
		uint8_t *m_dst_data[4];
		int m_dst_linesize[4];
		uint8_t *m_src_data[4];
		int m_src_linesize[4];
		int m_dataLen;
		int m_srcLen;
		AVCodec *m_codec;
		AVCodecContext *m_context;
		AVFrame *m_frame;
		AVPacket m_avpkt;
		struct SwsContext *m_sws_ctx;
		CXBuffer m_buffer;
		bool m_bRun;
		int m_width;
		int m_height;
		wxMutex m_locker;
		wxSemaphore m_sem;
};
#endif //~__X_DECODER_H_