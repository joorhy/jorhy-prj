#ifndef __X_DECODER_H_
#define __X_DECODER_H_

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/thread.h>

extern "C"
{
#include <libavcodec/avcodec.h>
}

class CXRender;
class CXDecoder : public wxThread
{
	public:
		CXDecoder(CXRender *render);
		~CXDecoder();
	
	public:
		int InitDecoder();
		void DeinitDecoder();
		int InputData(const char *pData, int nLen);
		
	public:
		virtual void *Entry();
		virtual void OnExit();
	
	private:
		int decode_write_frame();
							  
	private:
		CXRender *m_pRender;
		AVCodec *m_codec;
		AVCodecContext *m_context;
		AVFrame *m_frame;
		AVPacket m_avpkt;
};
#endif //~__X_DECODER_H_