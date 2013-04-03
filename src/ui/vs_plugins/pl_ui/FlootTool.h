#pragma once

#include "ExactSlider.h"
#include "PngButton.h"
#include "DataCenter.h"
#include "PlayerFactor.h"
#include "NewToolTip.h"
// CFlootTool

typedef struct
{
	PlayerFactor *pPlayer;

	int pVolume;
	BOOL pSound;
	BOOL bRecoder;

	DWORD dwUIT;
	BOOL bNeedShowCTRL;
	BOOL bPlayOneByOne;
	

}PlayParm;

class CFlootTool : public CWnd
{
	DECLARE_DYNAMIC(CFlootTool)

public:
	CFlootTool(CWnd *parent,UINT nId,enum WorkModel model);
	virtual ~CFlootTool();

protected:
	DECLARE_MESSAGE_MAP()

private:
	BOOL CreateToolBar();
	void InitParm();
	void SetLayout();
	void RelayEvent(UINT message,WPARAM wParam,LPARAM lParam);

private:
	enum WorkModel m_eModel;
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
	PlayParm *m_Player;
	BOOL m_bCreate;
	CNewToolTip m_toolTip;

public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	void LayWndLeft(BOOL bLeft,HWND hReferWnd,HWND hMoveWnd,int nInterval);

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


	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	BOOL AttachPlayer(PlayParm *pPlayParm,CWnd *parent);
	void ShowControls(BOOL bShow);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void EnableSomeButton(BOOL bEnable);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


