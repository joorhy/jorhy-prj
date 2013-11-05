#include "JoRenderX11.h"
#include "JoPictrue.h"

JO_IMPLEMENT_INTERFACE(Render, "live", CJoRender::Maker)

CJoRender::CJoRender()
{
	memset(&m_videoparm, 0, sizeof(m_videoparm));
	m_display = NULL;
	m_gc = NULL;
	m_bShow		= false;
	J_OS::LOGINFO("CJoRender::CJoRender()\n");
}

CJoRender::~CJoRender()
{
	DeinitRender();
}

j_result_t CJoRender::InitRender(j_wnd_t hwnd)
{
	if (!m_bShow)
	{
		//J_OS::LOGINFO("%d %d", hwnd, this);
		m_display = XOpenDisplay(NULL);
		m_drawable = GDK_WINDOW_XID(GTK_WIDGET(hwnd)->window);
		//J_OS::LOGINFO("%d %d", hwnd, m_drawable);
		XGCValues values;
		unsigned long valuemask = 0;
		m_gc = XCreateGC(m_display, m_drawable, valuemask, &values);
		//J_OS::LOGINFO("%d %d $$$$$$$$$$$$$$", m_width, m_height);
		m_xImage = XGetImage(m_display, m_drawable, 0, 0, m_width, m_height, 0, ZPixmap);
		m_xImage->bytes_per_line = m_width * 3;
		m_xImage->bits_per_pixel = 24;
		m_bShow = true;
	}

	return J_OK;
}

j_result_t CJoRender::DeinitRender()
{
	m_bShow = false;
	if (m_gc)
	{
		XFreeGC(m_display, m_gc);
		m_gc = NULL;
	}
	
	if (m_display)
	{
		XCloseDisplay(m_display);
		m_display = NULL;
	}
	
	return J_OK;
}

j_result_t CJoRender::DisplayFrame(j_char_t *pData, j_int32_t nLen)
{
	if (!m_bShow)
		return J_OK;
		
	//J_OS::LOGINFO("%d", nLen);
	m_xImage->data = (char*)pData;
	XPutImage(m_display, m_drawable, m_gc, m_xImage, 0, 0, 0, 0, m_width, m_height);
	XSync(m_display, false);
	XSync(m_display, false);

	return J_OK;
}

j_result_t CJoRender::SetDisplayParam(const J_VideoDisplayParam &displayParam)
{
	m_videoparm = displayParam;
	
	return J_OK;
}