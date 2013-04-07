// PlayWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "RPlayWnd.h"
#include "FlootTool.h"
#include "pl_type.h"
#include "runner_log.h"
#include <cmath>

// CRPlayWnd

IMPLEMENT_DYNAMIC(CRPlayWnd, CPlWnd)

CRPlayWnd::CRPlayWnd(HWND hParent,UINT nID)
{
	LPCTSTR lpWndClass = AfxRegisterWndClass(CS_DBLCLKS, 
											NULL,
											(HBRUSH)GetStockObject(BLACK_BRUSH),
											0);
	
	// player parm Init
	memset(&m_PlayerCenter,0,sizeof(m_PlayerCenter));
	m_PlayerCenter.pPlayer	= new PlManager(REALMODEL);
	m_PlayerCenter.pSound	= FALSE;
	m_PlayerCenter.pVolume	= DEFAULT_VOLUME;
	m_PlayerCenter.bNeedShowCTRL = SHOWCTRLCOMMAND;
	CString wndName;
	wndName.Format("Real Player Window:%d",nID);
	CreateEx(NULL,lpWndClass,wndName,
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
		0,0,0,0,hParent ,(HMENU)nID);	
	InitParm();

}

double CRPlayWnd::m_arrAreaAgl[4] = {atan(double(1.0/3)),atan(double(3.0/1)),
									atan(double(3.0/-1)),atan(double(1.0/-3))};
void CRPlayWnd::InitParm()
{
	m_nowCusID = -1;
	if(NULL == m_Tool)
	{
		m_Tool = new CFlootTool(this, IDT_TOOL);
		m_Tool->SetModel(REALMODEL);
	}
	m_DobWMTime = 0;
}

CRPlayWnd::~CRPlayWnd()
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


BEGIN_MESSAGE_MAP(CRPlayWnd, CWnd)
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



// CRPlayWnd message handlers


UINT CRPlayWnd::FindArea(CPoint point)
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

BOOL CRPlayWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	HCURSOR hc;
	if(m_PlayerCenter.pPlayer->IsPlaying() && pWnd == this)
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

void CRPlayWnd::OnMouseMove(UINT nFlags, CPoint point)
 {
	if(m_PlayerCenter.pPlayer->IsPlaying())
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


void CRPlayWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD interval = GetTickCount();
	if(m_dwInterval -  interval< 300)
		return;
	m_dwInterval = interval;
	if(m_PlayerCenter.pPlayer->IsPlaying())
	{
		int args[3];
		CRect rect;
		char *resid = NULL;
		int speed = 0;
		json_object *info = NULL;
		char *js_info = NULL;

		GetClientRect(&rect);
		js_info = m_PlayerCenter.pPlayer->GetJSInfo();
		if(!js_info)
			return;
		info = json_tokener_parse(js_info);
		if(is_error(info))
		{
			return;
		}
		resid = json_object_get_string(json_object_object_get(info,"resid"));
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
		args[1] = (int)resid;
		args[2]	= speed;
		m_PlayerCenter.pPlayer->onCallBack(CALLBACK_PTZCTL,args,sizeof(args)/sizeof(int));
		json_object_put(info);

	}
	CPlWnd::OnLButtonDown(nFlags, point);
}

void CRPlayWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{

	CPlWnd::OnLButtonDblClk(nFlags, point);
}


void CRPlayWnd::OnSize(UINT nType, int cx, int cy)
{
	CPlWnd::OnSize(nType,cx,cy);
}

BOOL CRPlayWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{	
	if(m_PlayerCenter.pPlayer->IsPlaying())
	{
		DWORD IntervalTime = GetTickCount() - m_DobWMTime;
		m_DobWMTime = GetTickCount();
		int args[3];
		char *resid = NULL;
		json_object *info = NULL;
		char *js_info = NULL;

		if(zDelta > 0) args[0] = 12;
		else		args[0] = 13;

		js_info = m_PlayerCenter.pPlayer->GetJSInfo();
		if(!js_info)
			return CPlWnd::OnMouseWheel(nFlags, zDelta, pt);
		info = json_tokener_parse(js_info);
		if(is_error(info))
		{
			return CPlWnd::OnMouseWheel(nFlags, zDelta, pt);
		}
		resid = json_object_get_string(json_object_object_get(info,"resid"));
		args[1] = (int)resid;

		if(IntervalTime <= 1000)
		{
			args[2] = ((1000 - m_DobWMTime)*255/1000)%256;	
		}
		else
		{
			args[2] = 20;
		}
		m_PlayerCenter.pPlayer->onCallBack(CALLBACK_PTZCTL,args,sizeof(args)/sizeof(int));

		Sleep(300);
		args[2] = 0;
		m_PlayerCenter.pPlayer->onCallBack(CALLBACK_PTZCTL,args,sizeof(args)/sizeof(int));
		json_object_put(info);
	}
	return CPlWnd::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CRPlayWnd::OnEraseBkgnd(CDC* pDC)
{
	return CPlWnd::OnEraseBkgnd(pDC);
}


void CRPlayWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_PlayerCenter.pPlayer->IsPlaying())
	{
		int args[3];
		char *resid = NULL;
		int speed = 0;
		json_object *info = NULL;
		char *js_info = NULL;

		js_info = m_PlayerCenter.pPlayer->GetJSInfo();
		if(!js_info)
			return CPlWnd::OnLButtonUp(nFlags, point);
		info = json_tokener_parse(js_info);
		if(is_error(info))
		{
			return;
		}
		resid = json_object_get_string(json_object_object_get(info,"resid"));

		args[0]	= m_nowCusID - 999;
		args[1] = (int)resid;
		args[2]	= speed;
		m_PlayerCenter.pPlayer->onCallBack(CALLBACK_PTZCTL,args,sizeof(args)/sizeof(int));
		json_object_put(info);
	}

	CPlWnd::OnLButtonUp(nFlags, point);
}

void CRPlayWnd::OnPaint()
{
	CPlWnd::OnPaint();
}


void CRPlayWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPlWnd::OnRButtonDown(nFlags, point);
}


void CRPlayWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CPlWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
