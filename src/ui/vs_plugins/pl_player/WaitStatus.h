#pragma once

#include "resource.h"
// CWaitStatus dialog

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
	void DrawStatus();

private:
	CString m_csText;
	CString m_scPoint;
	void *m_pUser;
	int m_nPointNum;
	CFont m_font;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg LRESULT StartWait(WPARAM wParam,LPARAM lParam);
};