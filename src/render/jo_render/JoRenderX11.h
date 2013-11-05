#ifndef __JORENDER_H_
#define __JORENDER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavcore/imgutils.h"
};
#include <X11/Xlib.h>

class CJoRender : public J_Render
{
public:
	CJoRender();
	~CJoRender();

	static int Maker(J_Obj *&pObj)
	{
		pObj = new CJoRender();
		return J_OK;
	}

public:
	///J_Render
	virtual j_result_t InitRender(j_wnd_t hwnd);
	virtual j_result_t DisplayFrame(j_char_t *pData, j_int32_t nLen);
	virtual j_result_t DeinitRender();
	virtual j_result_t SetDisplayParam(const J_VideoDisplayParam &displayParam);
	virtual j_result_t AspectRatio(j_int32_t nWidth, j_int32_t nHeight)
	{
		m_width = nWidth;
		m_height = nHeight;
		return J_OK;
	}

private:
	XImage *m_xImage;
	Display *m_display;
	Drawable m_drawable;
	GC m_gc;
	J_VideoDecodeParam m_videoparm;
	j_boolean_t m_bShow;
	j_int32_t m_width;
	j_int32_t m_height;
};

#endif //~__JORENDER_H_