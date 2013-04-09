#pragma once

#include "pl_type.h"
#include "pl_err.h"
#include "pl_factory_wnd.h"
#include "pl_wnd.h"
#include "pl_toolbar.h"
#include "ScreenWnd.h"
// CRPlayWnd

class PL_API CRPlayWnd : public CPlWnd
{
	DECLARE_DYNAMIC(CRPlayWnd)
public:
	CRPlayWnd(HWND hParent,UINT nID);
	virtual ~CRPlayWnd();

	static int Maker(CWnd *&pObj, HWND hParent,UINT nID)
	{
		pObj = new CRPlayWnd(hParent, nID);
		return PL_OK;
	}
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