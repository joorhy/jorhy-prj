#include "x_pl_vout_ddraw.h"
#include "x_pl_error.h"
#include "x_pl_data_def.h"
#include "x_pl_log.h"

CXPlVoutDDraw::CXPlVoutDDraw(j_pl_video_out_t &t)
:CXPlVideoOutput(t)
{
	m_pDD		= NULL;
	m_pcClipper	= NULL;
	m_hwnd		= NULL;
	m_pSurface	= NULL;
	m_pDDSPrimary	= NULL;
	m_oldProc	= NULL;
	memset(&m_videoparm,0,sizeof(m_videoparm));
	m_bShow		= TRUE;

}

CXPlVoutDDraw::~CXPlVoutDDraw(void)
{
	Release();
}

J_PL_RESULT CXPlVoutDDraw::OpenDDraw()
{
	HRESULT hr;
	
	hr = CoInitializeEx(NULL,COINIT_MULTITHREADED|COINIT_SPEED_OVER_MEMORY);
	if(hr !=  S_OK) 
		return J_PL_ERROR_INIT_DDRAW;

	hr = DirectDrawCreateEx(NULL,(LPVOID*)&m_pDD,IID_IDirectDraw7,NULL);
	if(hr != DD_OK) 
		return J_PL_ERROR_INIT_DDRAW;

	hr = IDirectDraw7_SetCooperativeLevel(m_pDD,NULL,DDSCL_NORMAL);
	if(hr != DD_OK) 
		return J_PL_ERROR_INIT_DDRAW;

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlVoutDDraw::GetDDrawCaps(DDCAPS &ddcaps)
{
	ZeroMemory(&ddcaps, sizeof(ddcaps));
	ddcaps.dwSize = sizeof(ddcaps);
	HRESULT hr = IDirectDraw7_GetCaps(m_pDD, &ddcaps, NULL);
	if (hr != DD_OK)
		return J_PL_ERROR_NO_CAPS;

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlVoutDDraw::CreateCliper(LPDIRECTDRAWSURFACE7 surface,HWND hwnd)
{
	HRESULT hr;
	
	hr = IDirectDraw7_CreateClipper(m_pDD,0,&m_pcClipper,NULL);
	if (hr != DD_OK)
		return J_PL_ERROR_NO_CLIPPER;

	hr = IDirectDrawClipper_SetHWnd(m_pcClipper,0,hwnd);
	if (hr != DD_OK)
		return J_PL_ERROR_NO_CLIPPER;

	hr = IDirectDrawSurface_SetClipper(surface, m_pcClipper);
	if (hr != DD_OK)
		return J_PL_ERROR_NO_CLIPPER;
	
	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlVoutDDraw::OpenDisplay()
{
	HRESULT hr;

	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	hr = IDirectDraw7_CreateSurface(m_pDD,&ddsd,&m_pDDSPrimary,NULL);
	if (hr != DD_OK)
		return J_PL_ERROR_PRIMARY_SURFACE;

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlVoutDDraw::GetHwnd(HWND &hwnd)
{
	hwnd = m_hwnd;
	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlVoutDDraw::CreateSurface(j_pl_video_out_t &t)
{
	DDSURFACEDESC2 ddsd;
	HRESULT hr;

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize			= sizeof(ddsd);
	ddsd.dwFlags		= DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT | DDSD_CAPS;
	ddsd.dwHeight		= t.height;
	ddsd.dwWidth		= t.width;
	ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
	ddsd.ddpfPixelFormat.dwSize		= sizeof(ddsd.ddpfPixelFormat);
	ddsd.ddpfPixelFormat.dwFlags	= DDPF_FOURCC;
	ddsd.ddpfPixelFormat.dwFourCC	= t.FourCCType;

	hr = IDirectDraw7_CreateSurface(m_pDD,&ddsd,&m_pSurface,NULL);
	//if(hr == DDERR_OUTOFVIDEOMEMORY)
	//{
	//	ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	//	ddsd.ddpfPixelFormat.dwFlags		= DDPF_RGB | DDPF_PALETTEINDEXED8;
	//	ddsd.ddpfPixelFormat.dwRGBBitCount	= 8;

	//}

	if (hr != DD_OK)
	{
		return J_PL_ERROR_CREATE_SURFACE;
	}
	m_videoparm = t;
	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlVoutDDraw::Display()
{
	J_PL_RESULT br;

	br = ShowPicture();
	if(br != J_PL_NO_ERROR)
		return br;

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlVoutDDraw::CopyData(char *buf,int len)
{
	DDSURFACEDESC2 ddsd;
	HRESULT hr;
	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize		= sizeof(ddsd);
	int height	= 0;
	int width	= 0;
	int lPitch	= 0;

	if(!buf)
		return J_PL_ERROR_PTR;
	do
	{
		hr = m_pSurface->Lock(NULL,&ddsd,DDLOCK_WAIT | DDLOCK_WRITEONLY,NULL);
	}while(hr == DDERR_WASSTILLDRAWING);
	if(hr != DD_OK) 
		return J_PL_ERROR_SURFACE_LOCK;

	LPBYTE lpSurf = (LPBYTE)ddsd.lpSurface;
	LPBYTE PtrYUV = (LPBYTE)buf;
	LPBYTE PtrY = NULL;
	LPBYTE PtrU = NULL;
	LPBYTE PtrV = NULL;

	if(!lpSurf)
		return J_PL_ERROR_PTR;

	switch(m_videoparm.FourCCType)
	{
	case J_PL_CODEC_YV12:
		PtrY = PtrYUV;
		PtrU = PtrYUV + ddsd.dwHeight * ddsd.dwWidth;
		PtrV = PtrYUV + (ddsd.dwHeight * ddsd.dwWidth) + 
						((ddsd.dwHeight / 2) * (ddsd.dwWidth / 2));

		height	= ddsd.dwHeight;
		width	= ddsd.dwWidth;
		lPitch	= ddsd.lPitch;
		for(int i=0;i<height;i++)
		{
			memcpy(lpSurf,PtrY,width);
			PtrY	+= width;
			lpSurf	+= lPitch;
		}

		height	= ddsd.dwHeight	/ 2;
		width	= ddsd.dwWidth / 2;
		lPitch	= ddsd.lPitch / 2;
		for(int i=0;i<height;i++)
		{
			memcpy(lpSurf,PtrV,width);
			PtrV	+= width;
			lpSurf	+= lPitch;
		}

		height	= ddsd.dwHeight	/ 2;
		width	= ddsd.dwWidth / 2;
		lPitch	= ddsd.lPitch / 2;
		for(int i=0;i<height;i++)
		{
			memcpy(lpSurf,PtrU,width);
			PtrU	+= width;
			lpSurf	+= lPitch;
		}

		break;
	default:
		m_pSurface->Unlock(NULL);
		return J_PL_ERROR_MISMATCH_PLANE;
	}
	m_pSurface->Unlock(NULL);
	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlVoutDDraw::ShowPicture()
{
	HRESULT hRet;
	RECT DestRect;
	GetClientRect(m_hwnd,&DestRect);
	if(m_bShow)
	{
		ClientToScreen(m_hwnd,(LPPOINT)&DestRect.left);
		ClientToScreen(m_hwnd,(LPPOINT)&DestRect.right);
		
		hRet = m_pDDSPrimary->Blt(&DestRect,m_pSurface,NULL,DDBLT_ALPHADEST,NULL);
		//while(hRet == DDERR_WASSTILLDRAWING); 
		if(hRet != DD_OK) 
			return J_PL_ERROR_SURFACE_BLT;
	}

	return J_PL_NO_ERROR;
}

LRESULT CALLBACK CXPlVoutDDraw::ControlProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	CXPlVoutDDraw *pUser = (CXPlVoutDDraw*)GetWindowLong(hwnd,GWL_USERDATA);
	if(pUser)
	{
		switch(message)
		{
		case WM_PAINT:
			pUser->Restore();
			break;

		case WM_SHOWWINDOW:
			break;	
		}
		//直接调用窗口过程会出错
		if(message != 0 && message != WM_SYSCOLORCHANGE)
			return CallWindowProc(pUser->m_oldProc,hwnd,message,wParam,lParam);
		else
			return TRUE;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}

J_PL_RESULT CXPlVoutDDraw::SetHwnd(HWND hwnd)
{
	m_hwnd = hwnd;

	OpenDDraw();

	OpenDisplay();
	CreateCliper(m_pDDSPrimary,m_hwnd);
	CreateSurface(m_parm);

	m_oldProc = (WNDPROC)SetWindowLongPtr(m_hwnd,GWLP_WNDPROC,(LONG_PTR)ControlProc);
	SetWindowLong(m_hwnd, GWL_USERDATA, (LONG)this);

	if(!m_oldProc)
		return J_PL_ERROR_WINDOW_HWND;

	return J_PL_NO_ERROR;
}
J_PL_RESULT CXPlVoutDDraw::Restore()
{
	if(!m_pDDSPrimary || !m_pSurface)
		return J_PL_ERROR_NO_SURFACE;

	return ShowPicture();
}

void CXPlVoutDDraw::Release()
{
	if(m_oldProc)
	{
		SetWindowLongPtr(m_hwnd,GWLP_WNDPROC,(LONG_PTR)m_oldProc);
		m_oldProc = NULL;
	}

	if(m_pcClipper)
		m_pcClipper->Release();

	if(m_pSurface)
		m_pSurface->Release();

	if(m_pDDSPrimary)
		m_pDDSPrimary->Release();

	if(m_pDD)
		m_pDD->Release();

	CoUninitialize();
	InvalidateRect(m_hwnd,NULL,TRUE);
}

J_PL_RESULT CXPlVoutDDraw::PrepareData(char *IN_buf,int IN_len)
{
	return CopyData(IN_buf,IN_len);
}