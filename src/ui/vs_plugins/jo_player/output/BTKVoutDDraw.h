#pragma once
#include "..\include\btkvideooutput.h"
#include "..\include\DataStruct.h"
#include "..\include\BTKCommon.h"
#include <ddraw.h>

class BTKVoutDDraw : public BTKVideoOutput
{
public:
	BTKVoutDDraw(btk_video_out_t &t);
	~BTKVoutDDraw(void);

	virtual BTK_RESULT Display();
	virtual BTK_RESULT PrepareData(char *IN_buf,int IN_len);
	virtual BTK_RESULT SetHwnd(HWND hwnd);
	virtual BTK_RESULT GetHwnd(HWND &hwnd);

private:
	BTK_RESULT OpenDDraw();
	BTK_RESULT OpenDisplay();
	BTK_RESULT GetDDrawCaps(DDCAPS &ddcaps);
	BTK_RESULT CreateCliper(LPDIRECTDRAWSURFACE7 surface,HWND hwnd);
	BTK_RESULT CreateSurface(btk_video_out_t &t);
	//BTK_RESULT UpdateOverlay(LPDIRECTDRAWSURFACE7 surface);
	//int FindColorKey(int *color);
	BTK_RESULT Restore();
	BTK_RESULT CopyData(char *buf,int len);
	BTK_RESULT ShowPicture();
	void Release();

	static LRESULT CALLBACK ControlProc(HWND,UINT,WPARAM,LPARAM);

private:
	LPDIRECTDRAW7			m_pDD;
	LPDIRECTDRAWCLIPPER		m_pcClipper;		//Clipper
	LPDIRECTDRAWSURFACE7	m_pDDSPrimary;		//DirectDrawœ‘ æª∫≥ÂøÈ Primary surface
	LPDIRECTDRAWSURFACE7	m_pSurface;

	HWND m_hwnd;
	WNDPROC m_oldProc;
	btk_video_out_t m_videoparm;
	BOOL m_bShow;
};
