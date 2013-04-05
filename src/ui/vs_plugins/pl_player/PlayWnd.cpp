// PlayWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "PlayWnd.h"
#include "runner_log.h"


// CPlayWnd

IMPLEMENT_DYNAMIC(CPlayWnd, CWnd)

CPlayWnd::CPlayWnd()
{
	
	m_hBkg.LoadBitmap(IDB_BACKGROUND);
	m_bFullScreen = FALSE;
	m_nFullModel = FULL_PLUGIN;
	m_bTrack	= TRUE;
	m_bOver		= FALSE;
	m_Last_WM_MOUSEMOVE_Pos = 0;
	bEraseOwn = TRUE;
	if(NULL == m_FullWnd)
	{
		//m_FullWnd = new CScreenWnd();
	}
	m_WndNumber++;
	m_nFocus = 1;
	m_wndRef++;
}
UINT CPlayWnd::m_nFocus = 1;
CScreenWnd *CPlayWnd::m_FullWnd = NULL;
int CPlayWnd::m_WndNumber = 0;
int CPlayWnd::m_nNowShowWnd = 0;
CFlootTool *CPlayWnd::m_Tool = NULL;
DWORD CPlayWnd::m_MouseHookThreadId = 0;
int CPlayWnd::m_wndRef = 0;

CPlayWnd::~CPlayWnd()
{
	m_WndNumber--;
	if(NULL != m_FullWnd && m_wndRef == 0)
	{
		delete m_FullWnd;
		m_FullWnd = NULL;
	}
}


BEGIN_MESSAGE_MAP(CPlayWnd, CWnd)
END_MESSAGE_MAP()



// CPlayWnd message handlers


void CPlayWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(!(m_PlayerCenter.pPlayer->IsPlaying()))
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
			//m_FullWnd->onFullScreen(this->m_hWnd);
			ShowAllWindowEpt(this->m_hWnd,SW_SHOWNOACTIVATE);
			m_bFullScreen = FALSE;
		}
		else
		{
			//m_FullWnd->onFullScreen(this->m_hWnd);
			ShowAllWindowEpt(this->m_hWnd,SW_HIDE);
			m_bFullScreen = TRUE;
		}
	}
	PostMessage(WM_OWN_SETFOCUS);
	CWnd::OnLButtonDblClk(nFlags, point);
}


BOOL CPlayWnd::OnEraseBkgnd(CDC* pDC)
{

	if(!bEraseOwn)
		return CWnd::OnEraseBkgnd(pDC);

	if(m_PlayerCenter.pPlayer)
	{
		if(m_PlayerCenter.pPlayer->IsPlaying())
		{
			return TRUE;
		}
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

void CPlayWnd::DrawBorder(CPen *pen)
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

void CPlayWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(!m_bFullScreen)
	{
		SendMessage(WM_OWN_SETFOCUS);
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CPlayWnd::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
{
	lpMMI->ptMinTrackSize.x	= MINWINDOW_WIDTH + 20;
	lpMMI->ptMinTrackSize.y	= MINWINDOW_HEIGHT + 20;
}

void CPlayWnd::SetFullModel(UINT nType)
{
	m_nFullModel = nType;
}

PlayerFactor *CPlayWnd::GetPlayer()
{
	return m_PlayerCenter.pPlayer;
}

void CPlayWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if(!m_Tool) return;
	if(m_Tool->GetParent() != this) return;

	if(nType == SIZE_MINIMIZED)
	{
		//m_Tool->ShowControls(FALSE);
	}

	CRect rect,toolRect;
	GetClientRect(&rect);
	//ClientToScreen(&rect);
	::GetWindowRect(m_Tool->m_hWnd,&toolRect);
	this->ScreenToClient(&toolRect);
	/*m_Tool->MoveWindow(	rect.CenterPoint().x - toolRect.Width() / 2,
						rect.bottom - toolRect.Height(),
						toolRect.Width(),
						toolRect.Height(),
						TRUE);*/
	m_Tool->MoveWindow(rect.left+1,
						rect.bottom - toolRect.Height()-1,
						rect.Width(),
						toolRect.Height(),
						TRUE);
	if(m_PlayerCenter.pPlayer)
	{
		if(m_PlayerCenter.pPlayer->IsPlaying())
		{
			m_PlayerCenter.pPlayer->AspectRatio();		//¿≠…Ï
		}
	}
}

void CPlayWnd::ShowAllWindowEpt(HWND hWnd,int nCmdShow)
{
	HWND hTemp;
	for(int i=1;i<=m_nNowShowWnd;i++)
	{
		hTemp = ::GetDlgItem(GetParent()->m_hWnd,i);
		if(hTemp == hWnd) continue;
		::ShowWindow(hTemp,nCmdShow);
	}
}

void CPlayWnd::SetNowShowWindow(int nNum)
{
	m_nNowShowWnd = nNum;
}

HWND CPlayWnd::GetFocusWnd()
{
	return ::GetDlgItem(GetParent()->m_hWnd,m_nFocus);
}

void CPlayWnd::OnPaint()
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

void CPlayWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	DWORD MsgPos = GetMessagePos();
	if(m_Last_WM_MOUSEMOVE_Pos != MsgPos)
	{
		m_Last_WM_MOUSEMOVE_Pos = MsgPos;
		if(m_Tool)
		{
			//m_Tool->AttachPlayer(&m_PlayerCenter,this);
			//m_Tool->ShowControls(TRUE);
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}


//MouseHook
void CPlayWnd::MouseHook(bool bSetHook)
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

HWND CPlayWnd::FindPlayerWnd()
{
	if(m_Tool)
		return ::GetWindow(m_Tool->m_hWnd,GW_HWNDNEXT);
	else
		return ::GetWindow(this->m_hWnd,GW_CHILD);
}

LRESULT CPlayWnd::SetMouseHook(WPARAM wParam,LPARAM lParam)
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

void CPlayWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_PlayerCenter.bNeedShowCTRL = !m_PlayerCenter.bNeedShowCTRL;
	//if(m_Tool)
	//	m_Tool->ShowControls(m_PlayerCenter.bNeedShowCTRL);
}

LRESULT CPlayWnd::SetEraseType(WPARAM wParam,LPARAM lParam)
{
	bEraseOwn = wParam;
	return TRUE;
}

void CPlayWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == VK_ESCAPE && m_bFullScreen == TRUE)
	{
		PostMessage(WM_LBUTTONDBLCLK,0,0);
	}
	CWnd::OnKeyDown(nChar,nRepCnt,nFlags);
}

LRESULT CPlayWnd::SetWndFocus(WPARAM wParam,LPARAM lParam)
{
	CPen pen = CPen(PS_SOLID,2,RGB(255,0,0));
	DrawBorder(&pen);
	DeleteObject(pen);

	HWND hOld= ::GetDlgItem(GetParent()->m_hWnd,m_nFocus); 

	//ªÿµ˜
	int IdWnd = GetWindowLong(this->m_hWnd,GWL_ID);
	if(IdWnd != m_nFocus)
	{
		m_nFocus = IdWnd;
		::SendMessage(hOld,WM_OWN_KILLFOCUS,0,0);
		if(m_PlayerCenter.pPlayer->IsPlaying())
		{
			int args[2];
			json_object *js_args	= NULL;
			json_object *resid  = NULL;
			json_object *ms		= NULL;
			json_object *info	= NULL;
			char *p_jsinfo		= NULL;

			p_jsinfo = m_PlayerCenter.pPlayer->GetJSInfo();
			if(!p_jsinfo)
				return TRUE;
			info = json_tokener_parse(p_jsinfo);
			if(!is_error(info) && info)
			{
				js_args = json_object_new_object();
				resid = json_object_object_get(info,"resid");
				json_object_object_add(js_args,"id",json_object_new_int(IdWnd));
				json_object_object_add(js_args,"resid",resid);
				ms = json_object_object_get(info,"ms");
				if(is_error(ms))
				{
					ms = json_object_new_string("NULL");
					json_object_object_add(js_args,"ms",ms);
				}
				else
				{
					ms = json_object_new_string(json_object_get_string(ms));
					json_object_object_add(js_args,"ms",ms);
				}
				args[0] = 2;
				args[1]	= (int)json_object_to_json_string(js_args);
				m_PlayerCenter.pPlayer->onCallBack(CALLBACK_ONSTATE,args,sizeof(args)/sizeof(int));

				json_object_put(info);
				json_object_put(js_args);

			}
		}
	}
	return FALSE;
}

LRESULT CPlayWnd::KillWndFocus(WPARAM wParam,LPARAM lParam)
{
	int Id = GetWindowLong(this->m_hWnd,GWL_ID);
	if(Id == m_nFocus) 
		return TRUE;

	CPen pen = CPen(PS_SOLID,2,RGB(128,128,128));
	DrawBorder(&pen);
	DeleteObject(pen);
	return FALSE;
}
