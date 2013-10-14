#pragma once

#include "resource.h"
// CWaitStatus dialog
#include "gdiplus.h" 
using namespace Gdiplus; 

class CReconnWindow : public CDialog
{
	DECLARE_DYNAMIC(CReconnWindow)
public:
	CReconnWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReconnWindow();

// Dialog Data
	enum { IDD = IDD_WAITSTAUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()	

private:
	static void WorkThread(void *pUser)
	{
		CReconnWindow *pThis = (CReconnWindow *)pUser;
		if (pThis)
			pThis->ShowGifPicture();
	}
	void ShowGifPicture();
	static void ReconnectThread(void *pUser)
	{
		CReconnWindow *pThis = (CReconnWindow *)pUser;
		if (pThis)
			pThis->Reconnect();
	}
	void Reconnect();

private:
	CString m_csText;
	CString m_scPoint;
	HWND m_pPlWnd;
	int m_nPointNum;
	CFont m_font;
	///GIF œ‘ æ
	ULONG_PTR m_gdiplusToken;
	Image *m_image;
	UINT m_fcount;
	UINT m_frameCount;
	HDC m_hDC;
	GUID m_Guid;
	BOOL m_bRun;
public:
	afx_msg LRESULT StartWait(WPARAM wParam,LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};