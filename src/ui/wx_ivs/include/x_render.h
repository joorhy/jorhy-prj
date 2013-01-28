#ifndef __X_RENDER_H_
#define __X_RENDER_H_

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/thread.h>

#include "x_buffer.h"
#include <stdint.h>
#include <X11/Xlib.h>

class CXRender : public wxThread
{
	public:
		CXRender();
		~CXRender();
		
	public:
		int Start(GdkWindow *window, int w, int h);
		void Stop();
		int InputData(const char *pData, int nLen);
		
	public:
		virtual void *Entry();
		virtual void OnExit();
	
	private:
		void RendRrame(const char *pData);
		
	private:
		CXBuffer m_buffer;
		bool m_bRun;
		char *m_pBuffer;
		//GdkWindow *m_window;
		int m_width;
		int m_height;
		XImage *m_img;
		Display *m_display;
		Drawable m_drawable;
};

#endif //~__X_RENDER_H_