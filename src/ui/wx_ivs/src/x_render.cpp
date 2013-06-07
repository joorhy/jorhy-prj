#include "x_render.h"
#include "x_errtype.h"
#include <gdk/gdkx.h>

CXRender::CXRender()
{
	m_bRun = false;
	m_width = 352;
	m_height = 288;
	
	m_display = NULL;
	m_gc = NULL;
}

CXRender::~CXRender()
{
	m_locker.Lock();
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
	m_locker.Unlock();
}

int CXRender::Start(GdkWindow *window)
{
	if (!m_bRun)
	{
		m_display = XOpenDisplay(NULL);
		m_drawable = GDK_WINDOW_XID(window);
		XGCValues values;
		unsigned long valuemask = 0;
		m_gc = XCreateGC(m_display, m_drawable, valuemask, &values);
		m_bRun = true;
		Create();
		Run();
	}
	
	return J_OK;
}

void CXRender::Stop()
{
	if (m_bRun)
	{
		m_bRun = false;
		m_sem.WaitTimeout(1000);
		//Delete();
	}
}

int CXRender::AspectRatio(int w, int h)
{
	m_locker.Lock();
	m_width = w;
	m_height = h;
	m_img = XGetImage(m_display, m_drawable, 0, 0, 547, 556, 0, ZPixmap);
	m_img->bytes_per_line = m_width * 3;
	m_img->bits_per_pixel = 24;
	m_locker.Unlock();
	
	return 0;
}

int CXRender::InputData(const char *pData, int nLen)
{
	if (m_bRun)
		m_buffer.PushData(pData, nLen);
	//RendRrame(pData);
	
	return J_OK;
}

void *CXRender::Entry()
{
	int nLen = 0;
	char *pBuffer = new char[1024 * 1024 * 5];
	while (m_bRun)
	{
		nLen = m_buffer.PopData(pBuffer);
		if (nLen > 0) 
		{
			RendRrame(pBuffer);
		}
	}
	delete pBuffer;
	
	return NULL;
}

		
void CXRender::OnExit()
{
	m_sem.Post();
}

void CXRender::RendRrame(const char *pData)
{
	m_locker.Lock();
	//m_img = XGetImage(m_display, m_drawable, 0, 0, m_width, m_height, 0, ZPixmap);
	//m_img->bytes_per_line = m_width * 3;
	//m_img->bits_per_pixel = 24;
	
	m_img->data = (char*)pData;
	XPutImage(m_display, m_drawable, m_gc, m_img, 0, 0, 0, 0, m_width, m_height);
    XSync(m_display, false);
    XSync(m_display, false);
	m_locker.Unlock();
}