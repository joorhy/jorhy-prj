#include "x_render.h"
#include "x_errtype.h"
#include <gdk/gdkx.h>

CXRender::CXRender()
{
	m_bRun = false;
	//m_window = NULL;
	//display = XOpenDisplay(NULL);
	
	//m_img = XCreateImage(display, XDefaultVisual(display, 1), 3, ZPixmap, 0, NULL, 352, 288, 1, 16);
	//XInitImage(m_img);
}

CXRender::~CXRender()
{
	
}

int CXRender::Start(GdkWindow *window, int w, int h)
{
	m_display = GDK_WINDOW_XDISPLAY(window);
	m_drawable = GDK_WINDOW_XID(window);
	m_width = w;
	m_height = h;
	m_bRun = true;
	Create();
	Run();
	
	return J_OK;
}

void CXRender::Stop()
{
	m_bRun = false;
}

int CXRender::InputData(const char *pData, int nLen)
{
	m_buffer.PushData(pData, nLen);
	
	return J_OK;
}

void *CXRender::Entry()
{
	int nLen = 0;
	char *pBuffer = new char[1024 * 1024 * 5];
	while (m_bRun)
	{
		nLen = m_buffer.PopData(pBuffer);
		if (nLen == 0)
			usleep(1);
		else 
		{
			RendRrame(pBuffer);
		}
	}
	delete pBuffer;
	
	return NULL;
}

		
void CXRender::OnExit()
{
	Delete();
}

void CXRender::RendRrame(const char *pData)
{
	m_img = XGetImage(m_display, m_drawable, 0, 0, m_width, m_height, 0, ZPixmap);
	m_img->data = (char*)pData;
	XPutImage(m_display, m_drawable, 
		XDefaultGC(m_display, 0), m_img,
              0, 0, 0, 0, m_width, m_height);
    XSync(m_display, false);
    //XSync(GDK_WINDOW_XDISPLAY(m_window), false);
}