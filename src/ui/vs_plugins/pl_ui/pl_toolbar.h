#pragma once

#include "pl_type.h"
#include "pl_define.h"
#include "ExactSlider.h"
#include "pl_button.h"
#include "pl_manager.h"
#include "pl_err.h"

#include "NewToolTip.h"

// CFlootTool
class CPlToolBar : public CWnd
						 , public PlToolWin
{
	DECLARE_DYNAMIC(CPlToolBar)

public:
	CPlToolBar(HWND parent, UINT nId);
	virtual ~CPlToolBar();

	static int Maker(CWnd *&pObj, HWND hParent,UINT nID)
	{
		pObj = new CPlToolBar(hParent, nID);
		return PL_OK;
	}
protected:
	DECLARE_MESSAGE_MAP()

private:
	BOOL CreateToolBar();
	void InitParm();
	void SetLayout();
	void RelayEvent(UINT message,WPARAM wParam,LPARAM lParam);

private:
	HWND m_hPlWnd;
	HWND m_hParent;
	int m_eModel;
	//Both
	CPlButton *m_bnStop;
	CPlButton *m_bnSound;
	CPlButton *m_bnCapture;
	CExactSlider *m_bnSlider;
	//real
	CPlButton *m_bnSpeak;
	CPlButton *m_bnRecord;
	//vod
	CPlButton *m_bnPause;
	CPlButton *m_bnFramePlay;
	CPlButton *m_bnSpeedup;
	CPlButton *m_bnSlowdown;
	CPlButton *m_bnDownload;
	//player
	BOOL m_bCreate;
	CNewToolTip m_toolTip;
	PL_PlayParm *m_pPlayParm;

public:
	///PlToolWin
	virtual void SetModel(int nModel) { m_eModel = nModel; InitParm(); } 
	virtual void ShowControls(BOOL bShow);
	virtual void StopPlayer() { Stop(); }
	virtual BOOL AttachPlayer(PL_PlayParm *pPlayParm, void *parent);
	//virtual HWND GetPlWnd() { return m_hPlWnd; }

public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:
	//Both
	void Stop();
	void Capture();
	void EnableSound();
	//Real
	void Speak();
	void Record();
	//Vod
	void Pause();
	void PlayOneByOne();
	void SpeedUp();
	void SlowDown();
	void Download();

	void LayWndLeft(BOOL bLeft,HWND hReferWnd,HWND hMoveWnd,int nInterval);
	void EnableSomeButton(BOOL bEnable);
};