#ifndef __JORENDER_H_
#define __JORENDER_H_
#include "j_includes.h"
#include <ddraw.h>
extern "C"
{
#include "libavcodec\avcodec.h"
#include "libavcore\imgutils.h"
};

class CJoRender : public J_Render
{
public:
	CJoRender();
	~CJoRender();

public:
	///J_Render
	virtual j_result_t InitRender(j_wnd_t hwnd);
	virtual j_result_t DisplayFrame(j_char_t *pData, j_int32_t nLen);
	virtual j_result_t DeinitRender();

private:
	j_result_t OpenDDraw();
	j_result_t OpenDisplay();
	j_result_t GetDDrawCaps(DDCAPS &ddcaps);
	j_result_t CreateCliper(LPDIRECTDRAWSURFACE7 surface,HWND hwnd);
	j_result_t CreateSurface(J_VideoDecodeParam &videoParam);
	j_result_t Restore();
	j_result_t CopyData(char *buf,int len);
	j_result_t ShowPicture();
	j_void_t Release();

#ifdef WIN32
	static LRESULT CALLBACK ControlProc(HWND,UINT,WPARAM,LPARAM);
#endif

private:
	LPDIRECTDRAW7					m_pDD;
	LPDIRECTDRAWCLIPPER		m_pcClipper;		//Clipper
	LPDIRECTDRAWSURFACE7	m_pDDSPrimary;		//DirectDrawœ‘ æª∫≥ÂøÈ Primary surface
	LPDIRECTDRAWSURFACE7	m_pSurface;

	j_wnd_t m_hwnd;
	J_VideoDecodeParam m_videoparm;
	j_boolean_t m_bShow;
#ifdef WIN32
	WNDPROC m_oldProc;
#endif
};

#endif //~__JORENDER_H_