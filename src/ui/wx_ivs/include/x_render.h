#ifndef __X_RENDER_H_
#define __X_RENDER_H_

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/thread.h>

class CXRender : public wxThread
{
	public:
		CXRender(CXRender *reciver);
		~CXRender();
		
	public:
		virtual void *Entry();
		virtual void OnExit();
};

#endif //~__X_RENDER_H_