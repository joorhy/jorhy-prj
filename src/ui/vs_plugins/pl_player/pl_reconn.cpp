// WaitStaus.cpp : implementation file
//

#include "stdafx.h"
#include "pl_reconn.h"
#include "pl_type.h"
#include "pl_manager.h"
#include <process.h>
#include <direct.h>

#define TIMER 1234
// CWaitStatus dialog

IMPLEMENT_DYNAMIC(CWaitStatus, CDialog)

CWaitStatus::CWaitStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CWaitStatus::IDD, pParent)
{
	Create(IDD_WAITSTAUS,pParent);

	GdiplusStartupInput gdiplusStartupInput; 
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL); 

	char curPath[256] = {0};
	getcwd(curPath, 255);
	m_image = ::new Image(L"..\\plugins\\reconnect.gif");
	UINT count = 0;
	count = m_image->GetFrameDimensionsCount();
	GUID *pDimensionIDs=(GUID*)new GUID[count];
	m_image->GetFrameDimensionsList(pDimensionIDs, count);
	WCHAR strGuid[39];
	StringFromGUID2(pDimensionIDs[0], strGuid, 39);
	m_frameCount=m_image->GetFrameCount(&pDimensionIDs[0]);
	delete []pDimensionIDs; 

	int size =m_image->GetPropertyItemSize(PropertyTagFrameDelay);
	PropertyItem* pItem = NULL;
	pItem = (PropertyItem*)malloc(size);
	m_image->GetPropertyItem(PropertyTagFrameDelay,size,pItem);

	m_Guid = FrameDimensionTime;
	m_hDC = GetDC()->GetSafeHdc();
	m_fcount = 0;
	m_bRun = FALSE;
}

CWaitStatus::~CWaitStatus()
{
	//CWaitStatus::EndWait(this);
	GdiplusShutdown(m_gdiplusToken);
}

void CWaitStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWaitStatus, CDialog)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_MESSAGE(WM_OWN_START_WAIT,CWaitStatus::StartWait)
	ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()


// CWaitStatus message handlers
LRESULT CWaitStatus::StartWait(WPARAM wParam,LPARAM lParam)
{
	m_pPlWnd = (HWND)wParam;
	SetTimer(TIMER,WAITSTATUS_TIME,NULL);
	CenterWindow(CWnd::FromHandle(m_pPlWnd));
	CRect rect;
	CWnd::FromHandle(m_pPlWnd)->GetWindowRect(rect);

	SetWindowPos(CWnd::FromHandle(HWND_TOP),0,0,rect.Width(),rect.Height(),/*SWP_NOSIZE|*/SWP_NOMOVE);
	ShowWindow(SW_SHOW);
	m_bRun = TRUE;
	_beginthread(CWaitStatus::WorkThread, 0, this);

	return TRUE;
}

void CWaitStatus::EndWait(CWaitStatus *pUser)
{
	
}

void CWaitStatus::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == TIMER)
	{
		if(!(PlManager::Instance()->IsPlaying(m_pPlWnd)))
		{
			if (PlManager::Instance()->RePlay(m_pPlWnd))
			{
				m_bRun = FALSE;
				KillTimer(TIMER);
				OnOK();//重连
			}
		}
		else
		{
			m_bRun = FALSE;
			KillTimer(TIMER);
			OnOK();
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CWaitStatus::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(nHitTest == HTCAPTION)
		return;
	CDialog::OnNcLButtonDown(nHitTest, point);
}

void CWaitStatus::ShowGifPicture()
{
	while (m_bRun)
	{
			CenterWindow(CWnd::FromHandle(m_pPlWnd));
			//m_hDC是外部传入的画图DC
			Graphics gh(m_hDC); 
			CRect rect;
			GetWindowRect(rect);
			int w = m_image->GetWidth();
			int h = m_image->GetHeight();
			if (w >= (rect.Width() / 6))
			{
				w = rect.Height() / 4;
				h = w;
				//w /= 4;
				//h /= 4;
			}
			else if (w >= (rect.Width() / 3))
			{
				w = rect.Width() / 4;
				h = w;
				//w /= 2;
				//h /= 2;
			}
			int x = rect.Width() - w;
			int y = rect.Height() - h;
			gh.DrawImage(m_image, x / 2, y / 2, w, h);
			//重新设置当前的活动数据帧
			m_image->SelectActiveFrame(&m_Guid, m_fcount++);
			//frameCount是上面GetFrameCount返回值
			if(m_fcount == m_frameCount)	
			{
				//如果到了最后一帧数据又重新开始
				m_fcount= 0;			
			}
			Sleep(100);
	}
}

void CWaitStatus::OnPaint()
{
	CRect rect;
	CPaintDC dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect,RGB(0,0,0)); //设置为黑色背景
}