// ScreenWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "pl_full_wnd.h"

// CPlFullWnd
IMPLEMENT_DYNAMIC(CPlFullWnd, CWnd)

CPlFullWnd::CPlFullWnd(HWND hParent, UINT nID)
{
	LPCTSTR wndClass = AfxRegisterWndClass(CS_DBLCLKS, 
									AfxGetApp()->LoadStandardCursor(IDC_ARROW),
									(HBRUSH)GetStockObject(WHITE_BRUSH),
									0);
	CreateEx(NULL,wndClass,_T("FullScreenWindow"),
			WS_POPUP | WS_CLIPCHILDREN, 
			0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),
			NULL ,0,0);
	m_bFullScreen = FALSE;
	m_hNeedFullWnd = NULL;
	m_oldParent = NULL;
	memset(&m_OldWndPlacement,0,sizeof(m_OldWndPlacement));
}

CPlFullWnd::~CPlFullWnd()
{

}

BEGIN_MESSAGE_MAP(CPlFullWnd, CWnd)
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CPlFullWnd message handlers
void CPlFullWnd::onFullScreen(HWND hNeedFullWnd)
{
	if(hNeedFullWnd == NULL) return;
	m_hNeedFullWnd = hNeedFullWnd;
	if(m_bFullScreen == TRUE)
	{
		m_bFullScreen = FALSE;
		::SetParent(hNeedFullWnd,m_oldParent);
		::SetWindowPlacement(hNeedFullWnd,&m_OldWndPlacement);
		::ShowWindow(hNeedFullWnd,SW_SHOWNORMAL);
		ShowWindow(SW_HIDE);
	}
	else
	{
		::GetWindowPlacement(hNeedFullWnd,&m_OldWndPlacement);
		m_oldParent = ::SetParent(hNeedFullWnd,this->m_hWnd);
		m_bFullScreen = TRUE;
		::ShowWindow(hNeedFullWnd,SW_SHOWMAXIMIZED);
		::SetFocus(hNeedFullWnd);
		ShowWindow(SW_SHOW);
	}
}

void CPlFullWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

WND_BEGIN_MAKER(f_play)
	WND_ENTER_MAKER("f_play", CPlFullWnd::Maker)
WND_END_MAKER()