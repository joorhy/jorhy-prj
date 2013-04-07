#pragma once

#include "pl_core.h"
#include "pl_define.h"
#include "pl_manager.h"

// CPlayWnd
class PL_API CPlWnd : public CWnd
{
	DECLARE_DYNAMIC(CPlWnd)

public:
	CPlWnd();
	virtual ~CPlWnd();

protected:
	DECLARE_MESSAGE_MAP()

	static UINT m_nFocus;		//目前的焦点窗口
	static PlFullScreen *m_FullWnd;
	static int m_WndNumber;
	static int m_nNowShowWnd;
	static PlToolWin *m_Tool;
	static DWORD m_MouseHookThreadId;
	static int m_wndRef;	 //	多个实例tool和fullwnd的销毁使用
	CBitmap m_hBkg;
	BOOL m_bFullScreen;
	UINT m_nFullModel;
	BOOL m_bTrack;
	BOOL m_bOver;
	PlayParm m_PlayerCenter;
	DWORD m_Last_WM_MOUSEMOVE_Pos;
	DWORD m_dwInterval;

	BOOL bEraseOwn;
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT SetMouseHook(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT SetEraseType(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT SetWndFocus(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT KillWndFocus(WPARAM wParam,LPARAM lParam);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

public:
	void DrawBorder(CPen *pen);
	void SetFullModel(UINT nType);
	PlManager *GetPlayer();
	void ShowAllWindowEpt(HWND hWnd,int nCmdShow);
	void SetNowShowWindow(int nNum);
	HWND GetFocusWnd();

	void MouseHook(bool bSetHook);
	HWND FindPlayerWnd();

private:
	static LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);	
};


