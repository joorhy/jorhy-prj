#pragma once

#include <atlimage.h>
#include "pl_type.h"


class CPlButton : public CButton
{
	DECLARE_DYNAMIC(CPlButton)

public:
	CPlButton(HINSTANCE hIns,CWnd *Parent,UINT nBtnId);
	virtual ~CPlButton();

public:
	void LoadPng(UINT nNormalID,UINT nOverId=NULL,UINT nDownId=NULL,UINT nDisableId=NULL,
				 UINT nExNorID=NULL,UINT nExOverID=NULL,UINT nExDownId=NULL,UINT nExDisID=NULL);
	static void LoadImageFromResource(CBitmap * pBitmap,UINT nResId,LPCSTR lpType);
	void ChangePng(BOOL bInitStatus=TRUE);

private:
	HINSTANCE m_hInstance;
	CBitmap m_NormalBitmap;
	CBitmap m_OverBitmap;
	CBitmap m_DownBitmap;
	CBitmap m_DisableBitmap;
	//CBitmap m_FocusBitmap;
	CBitmap m_NormalBitmap_EX;
	CBitmap m_OverBitmap_EX;
	CBitmap m_DownBitmap_EX;
	CBitmap m_DisableBitmap_EX;

	BOOL m_bTrack;
	enum ButtonStatus m_ButtonStatus;
	BOOL m_bChanged;		//按钮图标是否改变

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL EnableWindow(BOOL bEnable=TRUE);
	void ReSizeButton();

private:
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam,LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
