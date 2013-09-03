#pragma once

#include "resource.h"
// CWaitStatus dialog
#include "gdiplus.h" 
using namespace Gdiplus; 

class CWaitStatus : public CDialog
{
	DECLARE_DYNAMIC(CWaitStatus)

public:
	CWaitStatus(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWaitStatus();

// Dialog Data
	enum { IDD = IDD_WAITSTAUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	void EndWait(CWaitStatus *pUser);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	void ShowGifPicture();
	static void WorkThread(void *pUser)
	{
		CWaitStatus *pThis = (CWaitStatus *)pUser;
		if (pThis)
			pThis->ShowGifPicture();
	}
	//void ShowGifPicture();

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
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg LRESULT StartWait(WPARAM wParam,LPARAM lParam);
	afx_msg void OnPaint();
};