// NewToolTip.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "pl_tool_tip.h"


// CPlToolTip

IMPLEMENT_DYNAMIC(CPlToolTip, CWnd)

CPlToolTip::CPlToolTip()
{
	
}

CPlToolTip::~CPlToolTip()
{
}


BEGIN_MESSAGE_MAP(CPlToolTip, CWnd)
END_MESSAGE_MAP()



// CPlToolTip message handlers

BOOL CPlToolTip::AddTool(CWnd *pWnd,LPSTR lpszText)
{
	TOOLINFO ti;
	RECT rect;
	::GetWindowRect(pWnd->m_hWnd, &rect);
	ti.cbSize = sizeof(TOOLINFO);
	ti.uFlags = TTF_SUBCLASS|TTF_IDISHWND;
	ti.hwnd   = this->m_hWnd;
	ti.hinst  = AfxGetInstanceHandle();
	ti.uId = (UINT_PTR)pWnd->m_hWnd;
	ti.rect = rect;
	ti.lpszText = lpszText;
	
	SendMessage(TTM_ADDTOOL, 0,(LPARAM)(LPTOOLINFO) &ti);

	return TRUE;
}

BOOL CPlToolTip::AddTool(CWnd *pWnd,int nText)
{
	TOOLINFO ti;
	RECT rect;
	char text[32];

	memset(text,0,sizeof(text));
	sprintf(text,"%d",nText);
	::GetWindowRect(pWnd->m_hWnd, &rect);
	ti.cbSize = sizeof(TOOLINFO);
	ti.uFlags = TTF_SUBCLASS|TTF_IDISHWND;
	ti.hwnd   = this->m_hWnd;
	ti.hinst  = AfxGetInstanceHandle();
	ti.uId = (UINT_PTR)pWnd->m_hWnd;
	ti.rect = rect;
	ti.lpszText = text;

	SendMessage(TTM_ADDTOOL, 0,(LPARAM)(LPTOOLINFO) &ti);

	return TRUE;
}

void CPlToolTip::Create(CWnd *parent)
{
	CreateEx(WS_EX_TOPMOST,TOOLTIPS_CLASS,NULL,WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		parent->m_hWnd,NULL,NULL);
	::SetWindowPos(this->m_hWnd,
		HWND_TOPMOST,
		0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}