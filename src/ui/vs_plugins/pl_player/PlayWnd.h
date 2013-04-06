#pragma once

#include "ScreenWnd.h"
#include "FlootTool.h"
#include "PlayerFactor.h"
// CPlayWnd

#ifdef   PL_PLAYER_EXPORTS 
#define   DLLAPI	__declspec(dllexport) 
#else 
#define   DLLAPI	__declspec(dllimport) 
#endif 

class DLLAPI CPlayWnd : public CWnd
{
	DECLARE_DYNAMIC(CPlayWnd)

public:
	CPlayWnd();
	virtual ~CPlayWnd();

protected:
	DECLARE_MESSAGE_MAP()

	static UINT m_nFocus;		//目前的焦点窗口
	CBitmap m_hBkg;
	static CScreenWnd *m_FullWnd;
	static int m_WndNumber;
	static int m_nNowShowWnd;
	static CFlootTool *m_Tool;
	static DWORD m_MouseHookThreadId;
	static int m_wndRef;	 //	多个实例tool和fullwnd的销毁使用
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
	PlayerFactor *GetPlayer();
	void ShowAllWindowEpt(HWND hWnd,int nCmdShow);
	void SetNowShowWindow(int nNum);
	HWND GetFocusWnd();

	void MouseHook(bool bSetHook);
	HWND FindPlayerWnd();

private:
	static LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);	
};


