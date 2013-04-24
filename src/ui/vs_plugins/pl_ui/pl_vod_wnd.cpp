// VPlayWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "pl_vod_wnd.h"

// CVPlayWnd
IMPLEMENT_DYNAMIC(CPlVodWnd, CWnd)

CPlVodWnd::CPlVodWnd(HWND hParent, UINT nID)
//: CPlWnd(hParent, nID)
{
	LPCTSTR lpWndClass = AfxRegisterWndClass(CS_DBLCLKS, 
											NULL,
											(HBRUSH)GetStockObject(BLACK_BRUSH),
											0);
	CString wndName;
	wndName.Format("Vod Player Window:%d",nID);
	CreateEx(NULL,lpWndClass,wndName,
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
		0,0,0,0, hParent ,(HMENU)nID);	
}

void CPlVodWnd::Init()
{
	if (m_FullWnd == NULL)
	{
		m_FullWnd = dynamic_cast<PlFullScreen *>(CPlFactoryWnd::Instance()->GetWindow("f_play", NULL, IDF_SCREEN));
		ASSERT(m_FullWnd != NULL);
	}

	if(NULL == m_Tool)
	{
		m_Tool = dynamic_cast<PlToolWin *>(CPlFactoryWnd::Instance()->GetWindow("t_play", m_hWnd, (UINT)m_hParent));
		ASSERT(m_Tool != NULL);
		m_Tool->SetModel(STREAME_FILE);
		//m_Tool->AttachPlayer(&m_PlayerParm, this);
	}
}

CPlVodWnd::~CPlVodWnd()
{
}

BEGIN_MESSAGE_MAP(CPlVodWnd, CWnd)
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
	ON_MESSAGE(WM_MEDIA_END_REACHED, CPlVodWnd::MediaEnd)
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CPlVodWnd message handlers
void CPlVodWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPlWnd::OnLButtonDown(nFlags, point);
}

void CPlVodWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CPlWnd::OnLButtonDblClk(nFlags, point);
}

void CPlVodWnd::OnSize(UINT nType, int cx, int cy)
{
	CPlWnd::OnSize(nType, cx, cy);
}

void CPlVodWnd::OnMouseMove(UINT nFlags, CPoint point)
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

BOOL CPlVodWnd::OnEraseBkgnd(CDC* pDC)
{
	return CPlWnd::OnEraseBkgnd(pDC);
}


void CPlVodWnd::OnPaint()
{
	CPlWnd::OnPaint();
}

void CPlVodWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPlWnd::OnRButtonDown(nFlags, point);
}

void CPlVodWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CPlWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

LRESULT CPlVodWnd::MediaEnd(WPARAM wParam,LPARAM lParam)
{
	if(m_Tool)
	{
		m_Tool->StopPlayer();
	}
	return TRUE;
}

WND_BEGIN_MAKER(v_play)
	WND_ENTER_MAKER("v_play", CPlVodWnd::Maker)
WND_END_MAKER()