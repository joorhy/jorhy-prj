#pragma once
#include "pl_player.h"
#include "pl_err.h"
#include "pl_factory_wnd.h"

// CScreenWnd
class CScreenWnd	 : public CWnd
							 , public PlFullScreen
{
	DECLARE_DYNAMIC(CScreenWnd)

public:
	CScreenWnd(HWND hParent = NULL, UINT nID = 0);
	virtual ~CScreenWnd();

	static int Maker(CWnd *&pObj, HWND hParent,UINT nID)
	{
		pObj = new CScreenWnd(hParent, nID);
		return PL_OK;
	}
protected:
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bFullScreen;
	WINDOWPLACEMENT m_OldWndPlacement; //用来保存原窗口位置
	HWND m_oldParent;
	HWND m_hNeedFullWnd;		//要全屏窗口

public:
	///PlFullScreen
	virtual void onFullScreen(HWND hNeedFullWnd);

public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};