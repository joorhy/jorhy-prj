#include "stdafx.h"
#include "pl_reconn.h"
#include "pl_type.h"
#include "pl_manager.h"
#include <process.h>
#include <direct.h>

IMPLEMENT_DYNAMIC(CReconnWindow, CDialog)

CReconnWindow::CReconnWindow(CWnd* pParent /*=NULL*/)
: CDialog(CReconnWindow::IDD, pParent)
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

CReconnWindow::~CReconnWindow()
{
	GdiplusShutdown(m_gdiplusToken);
}

void CReconnWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReconnWindow, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_MESSAGE(WM_OWN_START_WAIT,CReconnWindow::StartWait)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CWaitStatus message handlers
LRESULT CReconnWindow::StartWait(WPARAM wParam,LPARAM lParam)
{
	m_pPlWnd = (HWND)wParam;
	CenterWindow(CWnd::FromHandle(m_pPlWnd));
	CRect rect;
	CWnd::FromHandle(m_pPlWnd)->GetWindowRect(rect);

	//SetWindowPos(CWnd::FromHandle(m_hWnd),0,0,rect.Width(),rect.Height(),SWP_NOMOVE);
	SetWindowPos(CWnd::FromHandle(HWND_TOP),1,1,rect.Width()-2,rect.Height()-2,SWP_NOMOVE);
	ShowWindow(SW_SHOW);
	m_bRun = TRUE;
	_beginthread(CReconnWindow::WorkThread, 0, this);
	_beginthread(CReconnWindow::ReconnectThread, 0, this);

	return TRUE;
}

void CReconnWindow::ShowGifPicture()
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
		}
		else if (w >= (rect.Width() / 3))
		{
			w = rect.Width() / 4;
			h = w;
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

void CReconnWindow::Reconnect()
{
	while (m_bRun)
	{
		Sleep(3000);
		if(!(PlManager::Instance()->IsPlaying(m_pPlWnd)))
		{
			if (PlManager::Instance()->RePlay(m_pPlWnd))
			{
				m_bRun = FALSE;
				ShowWindow(SW_HIDE);
			}
		}
	}
}

void CReconnWindow::OnPaint()
{
	CRect rect;
	CPaintDC dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect,RGB(0,0,0)); //设置为黑色背景
}

void CReconnWindow::OnSize(UINT nType, int cx, int cy)
{
	//CReconnWindow::OnSize(nType,cx,cy);
	if (m_bRun == TRUE)
	{
		CenterWindow(CWnd::FromHandle(m_pPlWnd));
		CRect rect;
		CWnd::FromHandle(m_pPlWnd)->GetWindowRect(rect);
		SetWindowPos(CWnd::FromHandle(HWND_TOP),1,1,rect.Width()-2,rect.Height()-2,SWP_NOMOVE);
		Invalidate(TRUE);
	}
}

void CReconnWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	::SendMessage(m_pPlWnd,WM_LBUTTONDOWN,(WPARAM)&nFlags,(LPARAM)&point);
	//OnLButtonDown(nFlags, point);
}

void CReconnWindow::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_bRun = FALSE;
	ShowWindow(SW_HIDE);
}