#pragma once

#include "j_type.h"
#include "FlootTool.h"
#include "ScreenWnd.h"
#include "PlayWnd.h"
// CRPlayWnd

class CRPlayWnd : public CPlayWnd
{
	DECLARE_DYNAMIC(CRPlayWnd)

public:
	CRPlayWnd(HWND hParent,UINT nID);
	virtual ~CRPlayWnd();

protected:
	DECLARE_MESSAGE_MAP()

private:
	void InitParm();
	UINT FindArea(CPoint point);

private:
	static double m_arrAreaAgl[4];
	UINT m_nowCusID;
	DWORD m_DobWMTime;


public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


