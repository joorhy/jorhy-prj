#pragma once


// CNewToolTip

class CNewToolTip : public CWnd
{
	DECLARE_DYNAMIC(CNewToolTip)

public:
	CNewToolTip();
	virtual ~CNewToolTip();

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL AddTool(CWnd *pWnd,LPSTR lpszText);
	BOOL AddTool(CWnd *pWnd,int nText);
	void Create(CWnd *parent);

};


