// WaitStaus.cpp : implementation file
//

#include "stdafx.h"
//#include "Plugin_2.1.h"
#include "WaitStatus.h"
#include "DataCenter.h"
#include "PlayerFactor.h"

#define TIMER 1234
#define TIMER2 1235
// CWaitStatus dialog

IMPLEMENT_DYNAMIC(CWaitStatus, CDialog)

CWaitStatus::CWaitStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CWaitStatus::IDD, pParent)
{
	m_csText.Format("重连中");
	for(int i=0;i<MAX_POINTNUM;i++)
	{
		m_scPoint += "..";
	}
	m_pUser = NULL;
	m_nPointNum = 0;

	Create(IDD_WAITSTAUS,pParent);
	LOGFONT logfnt; 
	logfnt.lfCharSet   =   DEFAULT_CHARSET; 
	logfnt.lfClipPrecision   =   CLIP_DEFAULT_PRECIS; 
	logfnt.lfEscapement   =   0; 
	strcpy(logfnt.lfFaceName, FONT_TYPE);
	logfnt.lfHeight   =   15; 
	logfnt.lfItalic   =   false; 
	logfnt.lfOrientation   =   0; 
	logfnt.lfPitchAndFamily   =   FF_SWISS; 
	logfnt.lfQuality   =   DEFAULT_QUALITY; 
	logfnt.lfStrikeOut   =   false; 
	logfnt.lfUnderline   =   false; 
	logfnt.lfWeight   =   400; 
	logfnt.lfWidth   =   9; 
	logfnt.lfOutPrecision   =   OUT_DEFAULT_PRECIS; 
	m_font.CreateFontIndirect(&logfnt);
}

CWaitStatus::~CWaitStatus()
{
	//CWaitStatus::EndWait(this);
}

void CWaitStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWaitStatus, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CWaitStatus::OnBnClickedOk)
	ON_MESSAGE(WM_OWN_START_WAIT,CWaitStatus::StartWait)
	ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()


// CWaitStatus message handlers
LRESULT CWaitStatus::StartWait(WPARAM wParam,LPARAM lParam)
{
	m_pUser = (void*)wParam;
	PlayerFactor *user = static_cast<PlayerFactor*>(m_pUser);
	SetTimer(TIMER,WAITSTATUS_TIME,NULL);
	SetTimer(TIMER2,RESIZE_TIME,NULL);
	CenterWindow(CWnd::FromHandle(user->GetPlayHwnd()));
	SetWindowPos(CWnd::FromHandle(HWND_TOP),0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	ShowWindow(SW_SHOW);

	return TRUE;
}

void CWaitStatus::EndWait(CWaitStatus *pUser)
{
	
}

void CWaitStatus::OnTimer(UINT_PTR nIDEvent)
{
	PlayerFactor *pUser = static_cast<PlayerFactor*>(m_pUser);
	if(nIDEvent == TIMER)
	{
		if(!(pUser->IsPlaying()))
		{
			DrawStatus();
			pUser->Play();			//重连
		}
		else
		{
			KillTimer(TIMER);
			KillTimer(TIMER2);
			OnOK();
		}
	}
	else if(nIDEvent == TIMER2)
	{
		CenterWindow(CWnd::FromHandle(pUser->GetPlayHwnd()));
	}
	

	CDialog::OnTimer(nIDEvent);
}

void CWaitStatus::DrawStatus()
{
	CClientDC dc(this);
	dc.SetBkMode(TRANSPARENT);
	CFont *oldFont = dc.SelectObject(&m_font);
	CRect rect;
	GetClientRect(&rect);
	if(m_nPointNum <= MAX_POINTNUM)
	{
		dc.DrawText(m_csText+m_scPoint.Left(m_nPointNum*2),
			&rect,DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		m_nPointNum++;
	}
	else
	{
		COLORREF color;
		color = dc.SetTextColor(dc.GetBkColor());
		dc.DrawText(m_csText+m_scPoint.Left(m_nPointNum*2),
			&rect,DT_LEFT | DT_VCENTER | DT_SINGLELINE);

		dc.SetTextColor(color);
		m_nPointNum = 0;
		dc.DrawText(m_csText+m_scPoint.Left(m_nPointNum*2),
			&rect,DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}
	dc.SelectObject(oldFont);
}
void CWaitStatus::OnBnClickedOk()
{
	PlayerFactor *pUser = static_cast<PlayerFactor*>(m_pUser);
	pUser->Stop();
	KillTimer(TIMER);
	KillTimer(TIMER2);
	OnOK();
}


void CWaitStatus::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(nHitTest == HTCAPTION)
		return;
	CDialog::OnNcLButtonDown(nHitTest, point);
}
