#pragma once


// CPlToolTip

class CPlToolTip : public CWnd
{
	DECLARE_DYNAMIC(CPlToolTip)

public:
	CPlToolTip();
	virtual ~CPlToolTip();

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL AddTool(CWnd *pWnd,LPSTR lpszText);
	BOOL AddTool(CWnd *pWnd,int nText);
	void Create(CWnd *parent);

};


