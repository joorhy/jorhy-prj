#pragma once

#include "pl_type.h"
#include "pl_define.h"
#include "ExactSlider.h"
#include "PngButton.h"
#include "pl_manager.h"
#include "NewToolTip.h"

// CFlootTool
class CPlToolBar : public CWnd
						 , public PlToolWin
{
	DECLARE_DYNAMIC(CPlToolBar)

public:
	CPlToolBar(CWnd *parent, UINT nId);
	virtual ~CPlToolBar();

protected:
	DECLARE_MESSAGE_MAP()

private:
	BOOL CreateToolBar();
	void InitParm();
	void SetLayout();
	void RelayEvent(UINT message,WPARAM wParam,LPARAM lParam);

private:
	HWND m_hPlWnd;
	int m_eModel;
	//Both
	CPngButton *m_bnStop;
	CPngButton *m_bnSound;
	CPngButton *m_bnCapture;
	CExactSlider *m_bnSlider;
	//real
	CPngButton *m_bnSpeak;
	CPngButton *m_bnRecord;
	//vod
	CPngButton *m_bnPause;
	CPngButton *m_bnFramePlay;
	CPngButton *m_bnSpeedup;
	CPngButton *m_bnSlowdown;
	CPngButton *m_bnDownload;
	//player
	BOOL m_bCreate;
	CNewToolTip m_toolTip;

public:
	///PlToolWin
	virtual void SetModel(int nModel) { m_eModel = nModel; InitParm(); } 
	virtual void ShowControls(BOOL bShow);
	virtual void StopPlayer() { Stop(); }
	BOOL AttachPlayer(void *pPlayParm, void *parent);

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