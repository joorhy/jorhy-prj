#pragma once
#include "x_pl_video_output.h"
#include "x_pl_data_struct.h"
#include "x_pl_common.h"
#include <ddraw.h>

class CXPlVoutDDraw : public CXPlVideoOutput
{
public:
	CXPlVoutDDraw(j_pl_video_out_t &t);
	~CXPlVoutDDraw(void);

	virtual J_PL_RESULT Display();
	virtual J_PL_RESULT PrepareData(char *IN_buf,int IN_len);
	virtual J_PL_RESULT SetHwnd(HWND hwnd);
	virtual J_PL_RESULT GetHwnd(HWND &hwnd);

private:
	J_PL_RESULT OpenDDraw();
	J_PL_RESULT OpenDisplay();
	J_PL_RESULT GetDDrawCaps(DDCAPS &ddcaps);
	J_PL_RESULT CreateCliper(LPDIRECTDRAWSURFACE7 surface,HWND hwnd);
	J_PL_RESULT CreateSurface(j_pl_video_out_t &t);
	//J_PL_RESULT UpdateOverlay(LPDIRECTDRAWSURFACE7 surface);
	//int FindColorKey(int *color);
	J_PL_RESULT Restore();
	J_PL_RESULT CopyData(char *buf,int len);
	J_PL_RESULT ShowPicture();
	void Release();

	static LRESULT CALLBACK ControlProc(HWND,UINT,WPARAM,LPARAM);

private:
	LPDIRECTDRAW7			m_pDD;
	LPDIRECTDRAWCLIPPER		m_pcClipper;		//Clipper
	LPDIRECTDRAWSURFACE7	m_pDDSPrimary;		//DirectDrawœ‘ æª∫≥ÂøÈ Primary surface
	LPDIRECTDRAWSURFACE7	m_pSurface;

	HWND m_hwnd;
	WNDPROC m_oldProc;
	j_pl_video_out_t m_videoparm;
	BOOL m_bShow;
};
