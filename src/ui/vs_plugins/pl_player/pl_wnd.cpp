// PlayWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "pl_wnd.h"
#include "pl_factory.h"
#include "pl_factory_wnd.h"
#include "pl_json_parser.h"
#include "runner_log.h"

// CPlayWnd
IMPLEMENT_DYNAMIC(CPlWnd, CWnd)

UINT CPlWnd::m_nFocus = 1;
int CPlWnd::m_nNowShowWnd = 0;
DWORD CPlWnd::m_MouseHookThreadId = 0;

CPlWnd::CPlWnd(HWND hParent, UINT nID)
: CWnd()
{
	m_hBkg.LoadBitmap(IDB_BACKGROUND);
	m_bFullScreen		= FALSE;
	m_nFullModel		= FULL_PLUGIN;
	m_bTrack				= TRUE;
	m_bOver				= FALSE;
	m_Tool					= NULL;
	m_Last_WM_MOUSEMOVE_Pos = 0;
	bEraseOwn			= TRUE;
	m_FullWnd = dynamic_cast<PlFullScreen *>(CPlFactoryWnd::Instance()->GetWindow("f_play", NULL, IDF_SCREEN));
	ASSERT(m_FullWnd != NULL);
	m_nFocus = 1;

	memset(&m_PlayerParm, 0, sizeof(m_PlayerParm));
	m_PlayerParm.pSound					= FALSE;
	m_PlayerParm.pVolume				= DEFAULT_VOLUME;
	m_PlayerParm.bNeedShowCTRL	= SHOWCTRLCOMMAND;
}

CPlWnd::~CPlWnd()
{
	if(NULL != m_FullWnd)
	{
		CPlFactoryWnd::Instance()->DelWindow(IDF_SCREEN);
		m_FullWnd = NULL;
	}

	if(m_Tool != NULL)
	{
		CPlFactoryWnd::Instance()->DelWindow(IDT_TOOL);
		m_Tool = NULL;
	}
}

BEGIN_MESSAGE_MAP(CPlWnd, CWnd)
END_MESSAGE_MAP()

// CPlayWnd message handlers
void CPlWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(!(PlManager::Instance()->IsPlaying(m_hWnd)))
	{
		if(!m_bFullScreen)
			return;
	}

	if(m_nFullModel == FULL_PLUGIN)
	{
		if(m_bFullScreen == TRUE)
		{
			ShowWindow(SW_SHOWNORMAL);
			ShowAllWindowEpt(this->m_hWnd,SW_SHOWNOACTIVATE);
			m_bFullScreen = FALSE;
		}
		else
		{
			ShowWindow(SW_SHOWMAXIMIZED);
			ShowAllWindowEpt(this->m_hWnd,SW_HIDE);
			m_bFullScreen = TRUE;
		}
	}
	else if(m_nFullModel == FULL_SCREEN)
	{
		if(NULL == m_FullWnd) return; 
		if(m_bFullScreen == TRUE)
		{
			m_FullWnd->onFullScreen(this->m_hWnd);
			ShowAllWindowEpt(this->m_hWnd,SW_SHOWNOACTIVATE);
			m_bFullScreen = FALSE;
		}
		else
		{
			m_FullWnd->onFullScreen(this->m_hWnd);
			ShowAllWindowEpt(this->m_hWnd,SW_HIDE);
			m_bFullScreen = TRUE;
		}
	}
	PostMessage(WM_OWN_SETFOCUS);
	CWnd::OnLButtonDblClk(nFlags, point);
}

BOOL CPlWnd::OnEraseBkgnd(CDC* pDC)
{
	if(!bEraseOwn)
		return CWnd::OnEraseBkgnd(pDC);

	if(PlManager::Instance()->IsPlaying(m_hWnd))
	{
		return TRUE;
	}

	CRect rect;
	GetClientRect(&rect);
	//±≥æ∞
	CDC memdc;
	BITMAP hbitmap;
	memdc.CreateCompatibleDC(pDC);
	CBitmap *oldbit = memdc.SelectObject(&m_hBkg);

	m_hBkg.GetBitmap(&hbitmap);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,hbitmap.bmWidth,hbitmap.bmHeight,SRCCOPY);
	memdc.SelectObject(oldbit);

	return TRUE;
	//return CWnd::OnEraseBkgnd(pDC);
}

void CPlWnd::DrawBorder(CPen *pen)
{
	CRect rect;
	GetClientRect(&rect);
	if(m_bFullScreen || m_nNowShowWnd == 1)
		return;

	CDC *wndDC = GetWindowDC();
	CPen *oldpen = wndDC->SelectObject(pen);
	wndDC->MoveTo(rect.left,rect.top);
	wndDC->LineTo(rect.right+1,rect.top);
	wndDC->LineTo(rect.right+1,rect.bottom+1);
	wndDC->LineTo(rect.left,rect.bottom+1);
	wndDC->LineTo(rect.left,rect.top);
	wndDC->SelectObject(oldpen);
}

void CPlWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(!m_bFullScreen)
	{
		SendMessage(WM_OWN_SETFOCUS);
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CPlWnd::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
{
	lpMMI->ptMinTrackSize.x	= MINWINDOW_WIDTH + 20;
	lpMMI->ptMinTrackSize.y	= MINWINDOW_HEIGHT + 20;
}

void CPlWnd::SetFullModel(UINT nType)
{
	m_nFullModel = nType;
}

void CPlWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if(!m_Tool) 
		return;

	if(dynamic_cast<CWnd *>(m_Tool)->GetParent() != this) 
		return;

	if(nType == SIZE_MINIMIZED)
	{
		m_Tool->ShowControls(FALSE);
	}

	CRect rect,toolRect;
	GetClientRect(&rect);
	//ClientToScreen(&rect);
	::GetWindowRect(dynamic_cast<CWnd *>(m_Tool)->m_hWnd, &toolRect);
	this->ScreenToClient(&toolRect);
	/*m_Tool->MoveWindow(	rect.CenterPoint().x - toolRect.Width() / 2,
						rect.bottom - toolRect.Height(),
						toolRect.Width(),
						toolRect.Height(),
						TRUE);*/
	dynamic_cast<CWnd *>(m_Tool)->MoveWindow(rect.left+1,
						rect.bottom - toolRect.Height()-1,
						rect.Width(),
						toolRect.Height(),
						TRUE);
	if(PlManager::Instance()->IsPlaying(m_hWnd))
	{
		PlManager::Instance()->AspectRatio(m_hWnd);		//¿≠…Ï
	}
}

void CPlWnd::ShowAllWindowEpt(HWND hWnd,int nCmdShow)
{
	HWND hTemp;
	for(int i=1;i<=m_nNowShowWnd;i++)
	{
		hTemp = ::GetDlgItem(GetParent()->m_hWnd,i);
		if(hTemp == hWnd) continue;
		::ShowWindow(hTemp,nCmdShow);
	}
}

void CPlWnd::SetNowShowWindow(int nNum)
{
	m_nNowShowWnd = nNum;
}

HWND CPlWnd::GetFocusWnd()
{
	return ::GetDlgItem(GetParent()->m_hWnd,m_nFocus);
}

void CPlWnd::OnPaint()
{
	CPaintDC dc(this); 
	
	if(m_nFocus == GetWindowLong(this->m_hWnd,GWL_ID))
	{
		CPen pen = CPen(PS_SOLID,2,RGB(255,0,0));
		DrawBorder(&pen);
		DeleteObject(pen);
	}
	else
	{
		CPen pen = CPen(PS_SOLID,2,RGB(128,128,128));
		DrawBorder(&pen);
		DeleteObject(pen);
	}
	
}

void CPlWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	DWORD MsgPos = GetMessagePos();
	if(m_Last_WM_MOUSEMOVE_Pos != MsgPos)
	{
		m_Last_WM_MOUSEMOVE_Pos = MsgPos;
		if(m_Tool && PlManager::Instance()->IsPlaying(m_hWnd))
		{
			m_Tool->AttachPlayer(&m_PlayerParm, this);
			m_Tool->ShowControls(m_PlayerParm.bNeedShowCTRL);
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CPlWnd::OnMouseLeave()
{
	m_Tool->ShowControls(m_PlayerParm.bNeedShowCTRL);
}

//MouseHook
void CPlWnd::MouseHook(bool bSetHook)
{
	if(bSetHook)
	{
		HWND hMPWnd = FindPlayerWnd();
		const DWORD WndThreadID = (hMPWnd) ? GetWindowThreadProcessId(hMPWnd, NULL) : 0;
		if(!hMPWnd || WndThreadID != m_MouseHookThreadId)
		{
			MouseHook(false);
		}
		if(hMPWnd && WndThreadID)
		{
			m_MouseHookThreadId = WndThreadID;
		}
	}
	else
	{
		m_MouseHookThreadId = 0;
	}
}

HWND CPlWnd::FindPlayerWnd()
{
	if(m_Tool)
		return ::GetWindow(dynamic_cast<CWnd *>(m_Tool)->m_hWnd,GW_HWNDNEXT);
	else
		return ::GetWindow(this->m_hWnd,GW_CHILD);
}

LRESULT CPlWnd::SetMouseHook(WPARAM wParam,LPARAM lParam)
{
	HWND hMPWnd = FindPlayerWnd();
	const DWORD WndThreadID = (hMPWnd) ? GetWindowThreadProcessId(hMPWnd, NULL) : 0;

	//if no hook, or window thread has changed
	if(hMPWnd && WndThreadID != m_MouseHookThreadId)
	{
		DWORD s = GetWindowLong(FindPlayerWnd(), GWL_STYLE);
		s |= WS_CLIPSIBLINGS;
		SetWindowLong(FindPlayerWnd(), GWL_STYLE, s);
		MouseHook(wParam);
	}
	return TRUE;
}

void CPlWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_PlayerParm.bNeedShowCTRL = !m_PlayerParm.bNeedShowCTRL;
	if(m_Tool && PlManager::Instance()->IsPlaying(m_hWnd))
		m_Tool->ShowControls(m_PlayerParm.bNeedShowCTRL);
}

LRESULT CPlWnd::SetEraseType(WPARAM wParam,LPARAM lParam)
{
	bEraseOwn = wParam;
	return TRUE;
}

void CPlWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == VK_ESCAPE && m_bFullScreen == TRUE)
	{
		PostMessage(WM_LBUTTONDBLCLK, 0, 0);
	}
	CWnd::OnKeyDown(nChar,nRepCnt,nFlags);
}

LRESULT CPlWnd::SetWndFocus(WPARAM wParam,LPARAM lParam)
{
	CPen pen = CPen(PS_SOLID, 2, RGB(255,0,0));
	DrawBorder(&pen);
	DeleteObject(pen);

	HWND hOld= ::GetDlgItem(GetParent()->m_hWnd, m_nFocus); 
	//ªÿµ˜
	int nIdWnd = GetWindowLong(this->m_hWnd, GWL_ID);
	if(nIdWnd != m_nFocus)
	{
		m_nFocus = nIdWnd;
		::SendMessage(hOld, WM_OWN_KILLFOCUS, 0, 0);
		if(PlManager::Instance()->IsPlaying(m_hWnd))
		{
			PL_PlayInfo playInfo = {0};
			if(!PlManager::Instance()->GetPlayInfo(m_hWnd, playInfo))
				return TRUE;
			
			char pJsData[64] = {0};
			PlJsonParser::Instance()->MakeFocus(playInfo, pJsData);
			int args[2];
			args[0] = 2;
			args[1]	= (int)pJsData;
			PlManager::Instance()->NotifyNpn(m_hWnd, CALLBACK_ONSTATE,args,sizeof(args)/sizeof(int));
		}
	}
	return FALSE;
}

LRESULT CPlWnd::KillWndFocus(WPARAM wParam,LPARAM lParam)
{
	int Id = GetWindowLong(this->m_hWnd,GWL_ID);
	if(Id == m_nFocus) 
		return TRUE;

	CPen pen = CPen(PS_SOLID,2,RGB(128,128,128));
	DrawBorder(&pen);
	DeleteObject(pen);
	return FALSE;
}
