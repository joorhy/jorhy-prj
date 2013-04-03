#pragma once


// CScreenWnd

class CScreenWnd : public CWnd
{
	DECLARE_DYNAMIC(CScreenWnd)

public:
	CScreenWnd();
	virtual ~CScreenWnd();

protected:
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bFullScreen;
	WINDOWPLACEMENT m_OldWndPlacement; //用来保存原窗口位置
	HWND m_oldParent;
	HWND m_hNeedFullWnd;		//要全屏窗口

public:
	void onFullScreen(HWND hNeedFullWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


