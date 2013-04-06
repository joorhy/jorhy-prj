#pragma once

#include "ScreenWnd.h"
#include "j_type.h"
#include "FlootTool.h"
#include "PlayWnd.h"
// CVPlayWnd

class CVPlayWnd : public CPlayWnd
{
	DECLARE_DYNAMIC(CVPlayWnd)

public:
	CVPlayWnd(HWND hParent,UINT nID);
	virtual ~CVPlayWnd();

protected:
	DECLARE_MESSAGE_MAP()

private:
	void InitParm();

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	LRESULT MediaEnd(WPARAM wParam,LPARAM lParam);
};


