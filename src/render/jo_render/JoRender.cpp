#include "JoRender.h"
#include "JoPictrue.h"

CJoRender::CJoRender()
{
	m_pDD		= NULL;
	m_pcClipper	= NULL;
	m_hwnd		= NULL;
	m_pSurface	= NULL;
	m_pDDSPrimary	= NULL;
	m_oldProc	= NULL;
	memset(&m_videoparm, 0, sizeof(m_videoparm));
	m_bShow		= true;
	J_OS::LOGINFO("CJoRender::CJoRender()\n");
}

CJoRender::~CJoRender()
{
	DeinitRender();
}

j_result_t CJoRender::InitRender(j_wnd_t hwnd)
{
	m_hwnd = hwnd;

	if (OpenDDraw() != J_OK)
	{
		J_OS::LOGINFO("OpenDDraw Error\n");
		return J_UNKNOW;
	}

	if (OpenDisplay() != J_OK)
	{
		J_OS::LOGINFO("OpenDisplay Error\n");
		return J_UNKNOW;
	}
	if (CreateCliper(m_pDDSPrimary,m_hwnd) != J_OK)
	{
		J_OS::LOGINFO("CreateCliper Error\n");
		return J_UNKNOW;
	}
	if (CreateSurface(m_videoparm) != J_OK)
	{
		J_OS::LOGINFO("CreateSurface Error\n");
		return J_UNKNOW;
	}

	m_oldProc = (WNDPROC)SetWindowLongPtr(m_hwnd,GWLP_WNDPROC,(LONG_PTR)ControlProc);
	SetWindowLong(m_hwnd, GWL_USERDATA, (LONG)this);

	if(!m_oldProc)
		return J_INVALID_HANDLE;

	return J_OK;
}

j_result_t CJoRender::DisplayFrame(j_char_t *pData, j_int32_t nLen)
{
	j_result_t br;
	br = CopyData(pData, nLen);
	if(br != J_OK)
		return br;
	br = ShowPicture();
	if(br != J_OK)
		return br;

	return J_OK;
}

j_result_t CJoRender::DeinitRender()
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

	return J_OK;
}

j_result_t CJoRender::OpenDDraw()
{
	HRESULT hr;
	hr = CoInitializeEx(NULL,COINIT_MULTITHREADED|COINIT_SPEED_OVER_MEMORY);
	if(hr !=  S_OK) 
		return J_RENDER_INIT_ERROR;

	hr = DirectDrawCreateEx(NULL,(LPVOID*)&m_pDD,IID_IDirectDraw7,NULL);
	if(hr != DD_OK) 
		return J_RENDER_INIT_ERROR;

	hr = IDirectDraw7_SetCooperativeLevel(m_pDD,NULL,DDSCL_NORMAL);
	if(hr != DD_OK) 
		return J_RENDER_INIT_ERROR;

	return J_OK;
}

j_result_t CJoRender::GetDDrawCaps(DDCAPS &ddcaps)
{
	ZeroMemory(&ddcaps, sizeof(ddcaps));
	ddcaps.dwSize = sizeof(ddcaps);
	HRESULT hr = IDirectDraw7_GetCaps(m_pDD, &ddcaps, NULL);
	if (hr != DD_OK)
		return J_ERROR_NO_CAPS;

	return J_OK;
}

j_result_t CJoRender::CreateCliper(LPDIRECTDRAWSURFACE7 surface,HWND hwnd)
{
	HRESULT hr;
	hr = IDirectDraw7_CreateClipper(m_pDD, 0, &m_pcClipper, NULL);
	if (hr != DD_OK)
	{
		J_OS::LOGINFO("IDirectDraw7_CreateClipper Error\n");
		return J_ERROR_NO_CLIPPER;
	}

	hr = IDirectDrawClipper_SetHWnd(m_pcClipper,0,hwnd);
	if (hr != DD_OK)
	{
		J_OS::LOGINFO("IDirectDrawClipper_SetHWnd Error\n");
		return J_ERROR_NO_CLIPPER;
	}

	hr = IDirectDrawSurface_SetClipper(surface, m_pcClipper);
	if (hr != DD_OK)
	{
		J_OS::LOGINFO("IDirectDrawSurface_SetClipper Error\n");
		return J_ERROR_NO_CLIPPER;
	}

	return J_OK;
}

j_result_t CJoRender::OpenDisplay()
{
	HRESULT hr;
	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	hr = IDirectDraw7_CreateSurface(m_pDD, &ddsd, &m_pDDSPrimary, NULL);
	if (hr != DD_OK)
		return J_ERROR_PRIMARY_SURFACE;

	return J_OK;
}

j_result_t CJoRender::CreateSurface(J_VideoDecodeParam &videoParam)
{
	DDSURFACEDESC2 ddsd;
	HRESULT hr;
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize			= sizeof(ddsd);
	ddsd.dwFlags		= DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT | DDSD_CAPS;
	ddsd.dwHeight		= videoParam.height;
	ddsd.dwWidth		= videoParam.width;
	ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
	ddsd.ddpfPixelFormat.dwSize		= sizeof(ddsd.ddpfPixelFormat);
	ddsd.ddpfPixelFormat.dwFlags	= DDPF_FOURCC;
	ddsd.ddpfPixelFormat.dwFourCC	= videoParam.fourcc_type;

	hr = IDirectDraw7_CreateSurface(m_pDD,&ddsd,&m_pSurface,NULL);
	if(hr == DDERR_OUTOFVIDEOMEMORY || hr == DDERR_INVALIDPIXELFORMAT)
	{
		ddsd.dwFlags				= DDSD_HEIGHT | DDSD_WIDTH | DDSD_CAPS;
		ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
		//ddsd.ddpfPixelFormat.dwFlags		= DDPF_RGB | DDPF_PALETTEINDEXED8;
		//ddsd.ddpfPixelFormat.dwRGBBitCount	= 8;
		hr = IDirectDraw7_CreateSurface(m_pDD, &ddsd, &m_pSurface, NULL);
		videoParam.fourcc_type = jo_codec_rgb32;
		J_OS::LOGINFO("CJoRender::CreateSurface RGBA Mode\n");
	}
	if (hr != DD_OK)
	{
		J_OS::LOGINFO("CJoRender::CreateSurface Error = %x\n", hr);
		return J_ERROR_CREATE_SURFACE;
	}
	m_videoparm = videoParam;

	return J_OK;
}

j_result_t CJoRender::Restore()
{
	if(!m_pDDSPrimary || !m_pSurface)
		return J_PARAM_ERROR;

	return ShowPicture();
}

j_result_t CJoRender::CopyData(char *buf,int len)
{
	DDSURFACEDESC2 ddsd;
	HRESULT hr;
	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize		= sizeof(ddsd);
	int height	= 0;
	int width	= 0;
	int lPitch	= 0;

	if(!buf)
		return J_ERROR_PTR;
	do
	{
		hr = m_pSurface->Lock(NULL,&ddsd,DDLOCK_WAIT | DDLOCK_WRITEONLY,NULL);
	}while(hr == DDERR_WASSTILLDRAWING);
	if(hr != DD_OK) 
		return J_ERROR_SURFACE_LOCK;

	LPBYTE lpSurf = (LPBYTE)ddsd.lpSurface;
	LPBYTE PtrYUV = (LPBYTE)buf;
	LPBYTE PtrY = NULL;
	LPBYTE PtrU = NULL;
	LPBYTE PtrV = NULL;

	if(!lpSurf)
		return J_ERROR_PTR;

	switch(m_videoparm.fourcc_type)
	{
	case jo_codec_yv12:
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
	case jo_codec_rgb32:
		{
			j_result_t br;
			AVPicture src,dst;

			int img_len = 0;
			memset(&src,0,sizeof(AVPicture));
			memset(&dst,0,sizeof(AVPicture));
			br = CJoPicture::FillYuv(src,m_videoparm,buf);
			if(br != J_OK)
				return br;

			if((img_len = av_image_alloc(dst.data,dst.linesize,m_videoparm.width,m_videoparm.height,PIX_FMT_RGBA,1)) < 0)
			{
				br = J_UNKNOW;
				goto CopyRGBData_Error;
			}

			br = CJoPicture::YUV2RGB32(src,dst,m_videoparm);
			if(br != J_OK)
				goto CopyRGBData_Error;
			memcpy(lpSurf, dst.data[0], img_len);

			//av_freep(&dst.data[0]);
			//break;

CopyRGBData_Error:
			for(int i=0;i<4;i++)
			{
				if(dst.data[i])
					av_freep(&dst.data[i]);
			}
			//m_pSurface->Unlock(NULL);
			//return br;
		}
		break;
	default:
		m_pSurface->Unlock(NULL);
		return J_ERROR_MISMATCH_PLANE;
	}
	m_pSurface->Unlock(NULL);
	return J_OK;
}

j_result_t CJoRender::ShowPicture()
{
	HRESULT hRet;
	RECT DestRect;
	GetClientRect(m_hwnd,&DestRect);
	if(m_bShow)
	{
		ClientToScreen(m_hwnd,(LPPOINT)&DestRect.left);
		ClientToScreen(m_hwnd,(LPPOINT)&DestRect.right);

		hRet = m_pDDSPrimary->Blt(&DestRect,m_pSurface,NULL,DDBLT_ALPHADEST,NULL);
		while(hRet == DDERR_WASSTILLDRAWING); 
		if(hRet != DD_OK) 
			return J_ERROR_SURFACE_BLT;
	}

	return J_OK;
}

LRESULT CALLBACK CJoRender::ControlProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	CJoRender *pUser = (CJoRender*)GetWindowLong(hwnd,GWL_USERDATA);
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