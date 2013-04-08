// VPlayWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "VPlayWnd.h"

// CVPlayWnd
IMPLEMENT_DYNAMIC(CVPlayWnd, CWnd)

CVPlayWnd::CVPlayWnd(HWND hParent, UINT nID)
: CPlWnd(hParent, nID)
{
	LPCTSTR lpWndClass = AfxRegisterWndClass(CS_DBLCLKS, 
											NULL,
											(HBRUSH)GetStockObject(BLACK_BRUSH),
											0);
	// player parm Init
	memset(&m_PlayerCenter,0,sizeof(m_PlayerCenter));
	m_PlayerCenter.pPlayer	= new PlManager(VODMODEL);
	m_PlayerCenter.pSound	= FALSE;
	m_PlayerCenter.pVolume	= DEFAULT_VOLUME;
	m_PlayerCenter.bNeedShowCTRL = SHOWCTRLCOMMAND;
	CString wndName;
	wndName.Format("Vod Player Window:%d",nID);
	CreateEx(NULL,lpWndClass,wndName,
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
		0,0,0,0, hParent ,(HMENU)nID);	

	InitParm();
}

void CVPlayWnd::InitParm()
{
	if(NULL == m_Tool)
	{
		m_Tool = new CFlootTool(this,IDT_TOOL);
		m_Tool->SetModel(VODMODEL);
	}
}

CVPlayWnd::~CVPlayWnd()
{
	m_wndRef--;
	if(m_Tool != NULL && m_wndRef == 0)
	{
		delete m_Tool;
		m_Tool = NULL;
	}
	if(NULL != m_PlayerCenter.pPlayer)
	{
		delete m_PlayerCenter.pPlayer;
		m_PlayerCenter.pPlayer = NULL;
	}
}


BEGIN_MESSAGE_MAP(CVPlayWnd, CWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_MESSAGE(WM_TRY_SET_MOUSE_HOOK, CPlWnd::SetMouseHook)
	ON_MESSAGE(WM_OWN_ERASEBKGROUND, CPlWnd::SetEraseType)
	ON_MESSAGE(WM_OWN_SETFOCUS, CPlWnd::SetWndFocus)
	ON_MESSAGE(WM_OWN_KILLFOCUS, CPlWnd::KillWndFocus)
	ON_MESSAGE(WM_MEDIA_END_REACHED, CVPlayWnd::MediaEnd)
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CVPlayWnd message handlers



void CVPlayWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPlWnd::OnLButtonDown(nFlags, point);
}

void CVPlayWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CPlWnd::OnLButtonDblClk(nFlags, point);
}


void CVPlayWnd::OnSize(UINT nType, int cx, int cy)
{
	CPlWnd::OnSize(nType, cx, cy);
}

void CVPlayWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	/*if(m_bTrack)
	{
		TRACKMOUSEEVENT tmp;
		tmp.cbSize		= sizeof(tmp);
		tmp.dwFlags		= TME_HOVER | TME_LEAVE;
		tmp.dwHoverTime	= 1;
		tmp.hwndTrack	= this->m_hWnd;
		m_bTrack =_TrackMouseEvent(&tmp);
	}*/

	CPlWnd::OnMouseMove(nFlags, point);
}

BOOL CVPlayWnd::OnEraseBkgnd(CDC* pDC)
{
	return CPlWnd::OnEraseBkgnd(pDC);
}


void CVPlayWnd::OnPaint()
{

	CPlWnd::OnPaint();
}

void CVPlayWnd::OnRButtonDown(UINT nFlags, CPoint point)
{

	CPlWnd::OnRButtonDown(nFlags, point);
}

void CVPlayWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CPlWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

LRESULT CVPlayWnd::MediaEnd(WPARAM wParam,LPARAM lParam)
{
	if(m_Tool)
	{
		m_Tool->Stop();
	}
	return TRUE;
}

WND_BEGIN_MAKER(v_play)
	WND_ENTER_MAKER("v_play", CVPlayWnd::Maker)
WND_END_MAKER()