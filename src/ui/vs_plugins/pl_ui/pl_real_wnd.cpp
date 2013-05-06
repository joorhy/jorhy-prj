// PlayWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "pl_real_wnd.h"
#include "pl_toolbar.h"
#include "pl_type.h"
#include "runner_log.h"
#include <cmath>

double CPlRealWnd::m_arrAreaAgl[4] = {atan(double(1.0/3)),atan(double(3.0/1)),
		atan(double(3.0/-1)),atan(double(1.0/-3))};

// CRPlayWnd
IMPLEMENT_DYNAMIC(CPlRealWnd, CWnd)
CPlRealWnd::CPlRealWnd(HWND hParent,UINT nID)
{
	m_hParent = hParent;
	LPCTSTR lpWndClass = AfxRegisterWndClass(CS_DBLCLKS, 
											NULL,
											(HBRUSH)GetStockObject(BLACK_BRUSH),
											0);
	CString wndName;
	wndName.Format("Real Player Window:%d",nID);
	CreateEx(NULL,lpWndClass,wndName,
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
		0,0,0,0,hParent ,(HMENU)nID);	
	//InitParm();
}

CPlRealWnd::~CPlRealWnd()
{

}

BEGIN_MESSAGE_MAP(CPlRealWnd, CWnd)
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_MESSAGE(WM_TRY_SET_MOUSE_HOOK, CPlWnd::SetMouseHook)
	ON_MESSAGE(WM_OWN_SETFOCUS, CPlWnd::SetWndFocus)
	ON_MESSAGE(WM_OWN_KILLFOCUS, CPlWnd::KillWndFocus)
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void CPlRealWnd::Init()
{
	m_nowCusID = -1;
	if (m_FullWnd == NULL)
	{
		m_FullWnd = dynamic_cast<PlFullScreen *>(CPlFactoryWnd::Instance()->GetWindow("f_play", NULL, IDF_SCREEN));
		ASSERT(m_FullWnd != NULL);
	}

	if (m_Tool == NULL)
	{
		CWnd *pWnd = CPlFactoryWnd::Instance()->GetWindow("t_play", m_hWnd, (UINT)m_hParent);
		m_Tool = dynamic_cast<PlToolWin *>(pWnd);
		//m_Tool = (PlToolWin *)(CPlFactoryWnd::Instance()->GetWindow("t_play", m_hWnd, (UINT)m_hParent));
		ASSERT(m_Tool != NULL);
		m_Tool->SetModel(STREAME_REALTIME);
		m_Tool->AttachPlayer(NULL, this);
	}
	else
	{
		m_Tool->AttachPlayer(NULL, this);
	}

	m_DobWMTime = 0;
}

// CRPlayWnd message handlers
UINT CPlRealWnd::FindArea(CPoint point)
{
	CRect rect;
	double a;

	GetClientRect(&rect);
	point -= rect.CenterPoint();
	point.y = -point.y;
	if(point.x == 0)
	{
		return -1;
	}
	a = atan(double(point.y)/(double)point.x);
	if(point.x > 0)
	{
		if(point.y > 0)
		{
			if(a >= m_arrAreaAgl[0] && a <m_arrAreaAgl[1])
			{
				return PTZ_RIGHT_UP;
			}
			else if(a >= m_arrAreaAgl[1])
			{
				return PTZ_UP;
			}
			else
			{
				return PTZ_RIGHT;
			}
		}
		else
		{
			if(a >= m_arrAreaAgl[2] && a <m_arrAreaAgl[3])
			{
				return PTZ_RIGHT_DOWN;
			}
			else if(a >= m_arrAreaAgl[3])
			{
				return PTZ_RIGHT;
			}
			else
			{
				return PTZ_DOWN;
			}
		}
	}
	else
	{
		if(point.y > 0)
		{
			if(a >= m_arrAreaAgl[2] && a <m_arrAreaAgl[3])
			{
				return PTZ_LEFT_UP;
			}
			else if(a >= m_arrAreaAgl[3])
			{
				return PTZ_LEFT;
			}
			else
			{
				return PTZ_UP;
			}
		}
		else
		{
			if(a >= m_arrAreaAgl[0] && a <m_arrAreaAgl[1])
			{
				return PTZ_LEFT_DOWN;
			}
			else if(a >= m_arrAreaAgl[1])
			{
				return PTZ_DOWN;
			}
			else
			{
				return PTZ_LEFT;
			}
		}
	}
}

BOOL CPlRealWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	HCURSOR hc;
	if(PlManager::Instance()->IsPlaying(m_hWnd) && pWnd == this)
	{
		hc = ::LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(m_nowCusID));
	}
	else
	{
		hc = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	}
	SetCursor(hc);

	return CPlWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CPlRealWnd::OnMouseMove(UINT nFlags, CPoint point)
 {
	if(PlManager::Instance()->IsPlaying(m_hWnd))
	{
		switch(FindArea(point))
		{
		case PTZ_UP:		m_nowCusID = IDC_UP;		break;
		case PTZ_DOWN:		m_nowCusID = IDC_DOWN;		break;
		case PTZ_LEFT:		m_nowCusID = IDC_LEFT;		break;
		case PTZ_RIGHT:		m_nowCusID = IDC_RIGHT;		break;
		case PTZ_LEFT_UP:	m_nowCusID = IDC_LEFTUP;	break;
		case PTZ_RIGHT_UP:	m_nowCusID = IDC_RIGHTUP;	break;
		case PTZ_LEFT_DOWN:	m_nowCusID = IDC_LEFTDOWN;	break;
		case PTZ_RIGHT_DOWN:m_nowCusID = IDC_RIGHTDOWN; break;
		}
	}
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


void CPlRealWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD interval = GetTickCount();
	if(m_dwInterval -  interval< 300)
		return;
	m_dwInterval = interval;
	if(PlManager::Instance()->IsPlaying(m_hWnd))
	{
		int args[3];
		CRect rect;
		int speed = 0;
		GetClientRect(&rect);

		PL_PlayInfo playInfo = {0};
		if(!PlManager::Instance()->GetPlayInfo(m_hWnd, playInfo))
			return;

		if(rect.PtInRect(point))
		{
			if(m_nowCusID == IDC_RIGHT || m_nowCusID == IDC_LEFT)
			{
				int x = abs(point.x - rect.CenterPoint().x);
				if(x == 0)
					speed = abs(point.x - rect.CenterPoint().x);
				else
					speed = (double)255 * x / ((double)rect.Width() / 2.0);
			}
			else
			{
				int x = abs(point.y - rect.CenterPoint().y);
				if(x == 0)
					speed = abs(point.y - rect.CenterPoint().y);
				else
					speed = (double)255 * x / ((double)rect.Height() / 2.0);
			}
		}

		args[0]	= m_nowCusID - 999;
		args[1] = (int)playInfo.strResid;
		args[2]	= speed;
		PlManager::Instance()->NotifyNpn(m_hWnd, CALLBACK_PTZCTL, args, sizeof(args)/sizeof(int));
	}
	CPlWnd::OnLButtonDown(nFlags, point);
}

void CPlRealWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CPlWnd::OnLButtonDblClk(nFlags, point);
}


void CPlRealWnd::OnSize(UINT nType, int cx, int cy)
{
	CPlWnd::OnSize(nType,cx,cy);
}

BOOL CPlRealWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{	
	if(PlManager::Instance()->IsPlaying(m_hWnd))
	{
		DWORD IntervalTime = GetTickCount() - m_DobWMTime;
		m_DobWMTime = GetTickCount();
		int args[3];
		if(zDelta > 0) 
			args[0] = 12;
		else		
			args[0] = 13;

		PL_PlayInfo playInfo = {0};
		if(!PlManager::Instance()->GetPlayInfo(m_hWnd, playInfo))
			return CPlWnd::OnMouseWheel(nFlags, zDelta, pt);

		args[1] = (int)playInfo.strResid;
		if(IntervalTime <= 1000)
		{
			args[2] = ((1000 - m_DobWMTime)*255/1000)%256;	
		}
		else
		{
			args[2] = 20;
		}
		PlManager::Instance()->NotifyNpn(m_hWnd, CALLBACK_PTZCTL, args, sizeof(args)/sizeof(int));
		Sleep(300);
		args[2] = 0;
		PlManager::Instance()->NotifyNpn(m_hWnd, CALLBACK_PTZCTL, args, sizeof(args)/sizeof(int));
	}
	return CPlWnd::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CPlRealWnd::OnEraseBkgnd(CDC* pDC)
{
	return CPlWnd::OnEraseBkgnd(pDC);
}

void CPlRealWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(PlManager::Instance()->IsPlaying(m_hWnd))
	{
		int args[3];
		int speed = 0;

		PL_PlayInfo playInfo = {0};
		if(!PlManager::Instance()->GetPlayInfo(m_hWnd, playInfo))
			return CPlWnd::OnLButtonUp(nFlags, point);

		args[0]	= m_nowCusID - 999;
		args[1] = (int)playInfo.strResid;
		args[2]	= speed;
		PlManager::Instance()->NotifyNpn(m_hWnd, CALLBACK_PTZCTL,args,sizeof(args)/sizeof(int));
	}
	CPlWnd::OnLButtonUp(nFlags, point);
}

void CPlRealWnd::OnPaint()
{
	CPlWnd::OnPaint();
}

void CPlRealWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPlWnd::OnRButtonDown(nFlags, point);
}

void CPlRealWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CPlWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

WND_BEGIN_MAKER(r_play)
	WND_ENTER_MAKER("r_play", CPlRealWnd::Maker)
WND_END_MAKER()