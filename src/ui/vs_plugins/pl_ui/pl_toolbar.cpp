// FlootTool.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "pl_toolbar.h"
#include "pl_ctrl.h"
#include "pl_factory_wnd.h"

// CFlootTool
IMPLEMENT_DYNAMIC(CPlToolBar, CWnd)

CPlToolBar::CPlToolBar(HWND pParent, UINT nId)
{
	LPCTSTR wndClass = AfxRegisterWndClass(CS_DBLCLKS, 
										AfxGetApp()->LoadStandardCursor(IDC_ARROW),
										(HBRUSH)(COLOR_3DFACE+1),
										0);
	m_bCreate = FALSE;
	m_hPlWnd = pParent;
	CreateEx(WS_EX_TOPMOST,
			wndClass,_T("myToolWnd"),
			WS_CHILD | WS_CLIPSIBLINGS, 
			0, 0, MINWINDOW_WIDTH,MINWINDOW_HEIGHT,
			m_hPlWnd, 0);
	//SetLayeredWindowAttributes(RGB(128,128,128),128,LWA_ALPHA);
}

void CPlToolBar::InitParm()
{
	if(!m_bCreate)
	{
		m_bnStop				= NULL;
		m_bnSound			= NULL;
		m_bnCapture		= NULL;
		m_bnSlider			= NULL;
		m_bnSpeak			= NULL;
		m_bnRecord			= NULL;
		m_bnPause			= NULL;
		m_bnFramePlay	= NULL;
		m_bnSpeedup		= NULL;
		m_bnSlowdown	= NULL;
		m_bnDownload	= NULL;
		m_pPlayParm		= NULL;
		if (CreateToolBar())
			m_bCreate		= TRUE;
	}
}

CPlToolBar::~CPlToolBar()
{
	delete m_bnStop;
	delete m_bnSound;
	delete m_bnCapture;
	delete m_bnSlider;
	delete m_bnSpeak;
	delete m_bnRecord;
	delete m_bnPause;
	delete m_bnFramePlay;
	delete m_bnSpeedup;
	delete m_bnSlowdown;
	delete m_bnDownload;
}

BEGIN_MESSAGE_MAP(CPlToolBar, CWnd)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDBN_STOP,&CPlToolBar::Stop)
	ON_BN_CLICKED(IDBN_CAPTURE,&CPlToolBar::Capture)
	ON_BN_CLICKED(IDBN_SOUND,&CPlToolBar::EnableSound)
	ON_BN_CLICKED(IDBN_SPEAK,&CPlToolBar::Speak)
	ON_BN_CLICKED(IDBN_RECORD,&CPlToolBar::Record)
	ON_BN_CLICKED(IDBN_PAUSE,&CPlToolBar::Pause)
	ON_BN_CLICKED(IDBN_FRAMEPLAY,&CPlToolBar::PlayOneByOne)
	ON_BN_CLICKED(IDBN_SPEEDUP,&CPlToolBar::SpeedUp)
	ON_BN_CLICKED(IDBN_SLOWDOWN,&CPlToolBar::SlowDown)
	ON_BN_CLICKED(IDBN_DOWNLOAD,&CPlToolBar::Download)
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CFlootTool message handlers

BOOL CPlToolBar::CreateToolBar()
{
	EnableToolTips(TRUE);
	m_toolTip.Create(this);
	HINSTANCE hInst = AfxGetInstanceHandle();
	m_bnStop	= new CPlButton(hInst,this,IDBN_STOP);
	m_bnStop->LoadPng(IDP_STOP_N,IDP_STOP_V,IDP_STOP_D,IDP_STOP_X);
	m_toolTip.AddTool(m_bnStop,"停止");

	m_bnSound	= new CPlButton(hInst,this,IDBN_SOUND);
	m_bnSound->LoadPng(IDP_SOUND_CLOSE_N,IDP_SOUND_CLOSE_V,IDP_SOUND_CLOSE_D,IDP_SOUND_CLOSE_X,
					IDP_SOUND_OPEN_N,IDP_SOUND_OPEN_V,IDP_SOUND_OPEN_D,IDP_SOUND_OPEN_X);
	m_toolTip.AddTool(m_bnSound,"取消静音");

	m_bnCapture	= new CPlButton(hInst,this,IDBN_CAPTURE);
	m_bnCapture->LoadPng(IDP_CAPTURE_N,IDP_CAPTURE_V,IDP_CAPTURE_D,IDP_CAPTURE_X);
	m_toolTip.AddTool(m_bnCapture,"抓图");

	m_bnSlider	= new CExactSlider(this,IDBN_SLIDER);
	m_toolTip.AddTool(m_bnSlider,DEFAULT_VOLUME);
	switch(m_eModel)
	{
	case STREAME_REALTIME:
		m_bnSpeak	= new CPlButton(hInst,this,IDBN_SPEAK);
		m_bnSpeak->LoadPng(IDP_SPEAK_CLOSE_N,IDP_SPEAK_CLOSE_V,IDP_SPEAK_CLOSE_D,IDP_SPEAK_CLOSE_X);
		m_toolTip.AddTool(m_bnSpeak,"开启对讲");

		m_bnRecord	= new CPlButton(hInst,this,IDBN_RECORD);
		m_bnRecord->LoadPng(IDP_RECORD_CLOSE_N,IDP_RECORD_CLOSE_V,IDP_RECORD_CLOSE_D,IDP_RECORD_CLOSE_X,
							IDP_RECORD_OPEN_N,IDP_RECORD_OPEN_V,IDP_RECORD_OPEN_D,IDP_RECORD_OPEN_X);
		m_toolTip.AddTool(m_bnRecord,"开启录像");
		break;
	case STREAME_FILE:
		m_bnPause	= new CPlButton(hInst,this,IDBN_PAUSE);
		m_bnPause->LoadPng(IDP_PAUSE_N,IDP_PAUSE_V,IDP_PAUSE_D,IDP_PAUSE_X);
		m_toolTip.AddTool(m_bnPause,"暂停播放");

		m_bnFramePlay= new CPlButton(hInst,this,IDBN_FRAMEPLAY);
		m_bnFramePlay->LoadPng(IDP_FRAMEPLAY_N,IDP_FRAMEPLAY_V,IDP_FRAMEPLAY_D,IDP_FRAMEPLAY_X);
		m_toolTip.AddTool(m_bnFramePlay,"单帧播放");

		m_bnSpeedup	= new CPlButton(hInst,this,IDBN_SPEEDUP);
		m_bnSpeedup->LoadPng(IDP_SPEEDUP_N,IDP_SPEEDUP_V,IDP_SPEEDUP_D,IDP_SPEEDUP_X);
		m_toolTip.AddTool(m_bnSpeedup,"快进");

		m_bnSlowdown= new CPlButton(hInst,this,IDBN_SLOWDOWN);
		m_bnSlowdown->LoadPng(IDP_SLOWDOWN_N,IDP_SLOWDOWN_V,IDP_SLOWDOWN_D,IDP_SLOWDOWN_X);
		m_toolTip.AddTool(m_bnSlowdown,"慢放");

		m_bnDownload	= new CPlButton(hInst,this,IDBN_DOWNLOAD);
		m_bnDownload->LoadPng(IDP_SAVE_N,IDP_SAVE_V,IDP_SAVE_D,IDP_SAVE_X);
		m_toolTip.AddTool(m_bnDownload,"录像下载");
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void CPlToolBar::SetLayout()
{
	if(!m_bCreate)
		return;
	CRect rect,bnPos;
	GetClientRect(&rect);
	m_bnStop->CenterWindow();
	switch(m_eModel)
	{
	case STREAME_REALTIME:
		LayWndLeft(FALSE,m_bnStop->m_hWnd,m_bnSound->m_hWnd,5);	
		LayWndLeft(FALSE,m_bnSound->m_hWnd,m_bnSlider->m_hWnd,5);	
		LayWndLeft(FALSE,m_bnSlider->m_hWnd,m_bnSpeak->m_hWnd,5);
		LayWndLeft(TRUE,m_bnStop->m_hWnd,m_bnCapture->m_hWnd,5);
		LayWndLeft(TRUE,m_bnCapture->m_hWnd,m_bnRecord->m_hWnd,5);
		break;

	case STREAME_FILE:
		LayWndLeft(FALSE,m_bnStop->m_hWnd,m_bnPause->m_hWnd,5);	
		LayWndLeft(FALSE,m_bnPause->m_hWnd,m_bnSpeedup->m_hWnd,5);	
		LayWndLeft(FALSE,m_bnSpeedup->m_hWnd,m_bnSound->m_hWnd,5);
		LayWndLeft(FALSE,m_bnSound->m_hWnd,m_bnSlider->m_hWnd,5);
		LayWndLeft(TRUE,m_bnStop->m_hWnd,m_bnFramePlay->m_hWnd,5);
		LayWndLeft(TRUE,m_bnFramePlay->m_hWnd,m_bnSlowdown->m_hWnd,5);
		LayWndLeft(TRUE,m_bnSlowdown->m_hWnd,m_bnCapture->m_hWnd,5);
		LayWndLeft(TRUE,m_bnCapture->m_hWnd,m_bnDownload->m_hWnd,5);
		break;
	default:
		break;
	}
}

void CPlToolBar::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
{
	lpMMI->ptMinTrackSize.x	= MINWINDOW_WIDTH;
	lpMMI->ptMinTrackSize.y	= MINWINDOW_HEIGHT;
	lpMMI->ptMaxTrackSize.x	= MINWINDOW_WIDTH;
	lpMMI->ptMaxTrackSize.y = MINWINDOW_HEIGHT;
}

void CPlToolBar::LayWndLeft(BOOL bLeft,HWND hReferWnd,HWND hMoveWnd,int nInterval)
{
	CRect refRect,movRect;
	::GetWindowRect(hReferWnd,&refRect);
	this->ScreenToClient(&refRect);
	::GetClientRect(hMoveWnd,&movRect);
	if(bLeft)
	{
		::MoveWindow(hMoveWnd,
					refRect.left - nInterval - movRect.Width(),	//x
					refRect.CenterPoint().y - movRect.Height() / 2,	//y
					movRect.Width(),	//width
					movRect.Height(),	//height
					TRUE);
	}
	else
	{
		::MoveWindow(hMoveWnd,
					refRect.right + nInterval,			//x
					refRect.CenterPoint().y - movRect.Height() / 2,	//y
					movRect.Width(),	//width
					movRect.Height(),	//height
					TRUE);	 
	}
}


/************************************************************************/
/*								Both									*/
/************************************************************************/
void CPlToolBar::Stop()
{
	PlManager::Instance()->StatusCallBack(m_hPlWnd);
	PlManager::Instance()->Stop(m_hPlWnd);
	m_pPlayParm->pSound  = FALSE;
	m_pPlayParm->pVolume = DEFAULT_VOLUME;
	ShowControls(FALSE);
}

void CPlToolBar::EnableSound()
{
	if(m_pPlayParm == NULL) 
		return;
	if(m_pPlayParm->pSound)
	{
		m_bnSound->ChangePng();
		m_pPlayParm->pSound = FALSE;
		m_pPlayParm->pVolume = PlManager::Instance()->GetVolume(m_hPlWnd);
		PlManager::Instance()->SetVolume(m_hPlWnd, 0);
		m_bnSlider->SetPos(0);

		m_toolTip.AddTool(m_bnSound,"取消静音");
		m_toolTip.AddTool(m_bnSlider,0);
	}
	else
	{
		m_bnSound->ChangePng(FALSE);
		m_pPlayParm->pSound = TRUE;
		PlManager::Instance()->SetVolume(m_hPlWnd, m_pPlayParm->pVolume);
		m_bnSlider->SetPos(m_pPlayParm->pVolume);
		m_toolTip.AddTool(m_bnSound, "静音");
		m_toolTip.AddTool(m_bnSlider, m_pPlayParm->pVolume);
	}
}

void CPlToolBar::Capture()
{
	char path[PATH_LENGTH] = {0};
	CPlCtrl::Instance()->GetPath(path, IMAGEPATH);
	PlManager::Instance()->Capture(m_hPlWnd, path);
}

/************************************************************************/
/*                               Real									*/
/************************************************************************/
void CPlToolBar::Speak()
{
	PlManager::Instance()->SetOsdText(m_hPlWnd, 2, "对讲");
}

void CPlToolBar::Record()
{
	char path[PATH_LENGTH] = {0};
	CPlCtrl::Instance()->GetPath(path,VIDEOPATH);
	if(PlManager::Instance()->Record(m_hPlWnd, path))
	{
		m_pPlayParm->bRecoder = !m_pPlayParm->bRecoder;
		if(m_pPlayParm->bRecoder)
		{
			m_bnRecord->ChangePng(FALSE);
			m_toolTip.AddTool(m_bnRecord,"关闭录像");
		}
		else
		{
			m_bnRecord->ChangePng();
			m_toolTip.AddTool(m_bnRecord,"开启录像");
		}
		PlManager::Instance()->SetOsdText(m_hPlWnd, 2, "录像");
	}
}

/************************************************************************/
/*                             Vod										*/
/************************************************************************/
void CPlToolBar::Pause()
{
	PlManager::Instance()->Pause(m_hPlWnd);
	if(m_pPlayParm->bPlayOneByOne)
	{
		PlManager::Instance()->SetOsdText(m_hPlWnd, 2, "恢复播放");
		m_pPlayParm->bPlayOneByOne = FALSE;
	}
	else
	{
		if(PlManager::Instance()->IsPaused(m_hPlWnd))
			PlManager::Instance()->SetOsdText(m_hPlWnd, 2, "恢复播放");
		else
			PlManager::Instance()->SetOsdText(m_hPlWnd, 2, "暂停");
	}
}

void CPlToolBar::PlayOneByOne()
{
	PlManager::Instance()->PlayOneByOne(m_hPlWnd);
	m_pPlayParm->bPlayOneByOne = TRUE;
	PlManager::Instance()->SetOsdText(m_hPlWnd, 2,"单帧播放>>");
}

void CPlToolBar::SpeedUp()
{
	PlManager::Instance()->SetSpeed(m_hPlWnd, TRUE);
}

void CPlToolBar::SlowDown()
{
	PlManager::Instance()->SetSpeed(m_hPlWnd, FALSE);
}

void CPlToolBar::Download()
{
	PlManager::Instance()->SetOsdText(m_hPlWnd, 2, "下载");
}

void CPlToolBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pPlayParm->pVolume = ((CExactSlider*)pScrollBar)->GetPos();
	PlManager::Instance()->SetVolume(m_hPlWnd, m_pPlayParm->pVolume);
	m_toolTip.AddTool(m_bnSlider, m_pPlayParm->pVolume);
	if(m_pPlayParm->pVolume == 0 && m_pPlayParm->pSound)
	{
		m_bnSound->ChangePng();
		m_pPlayParm->pSound = FALSE;
	}
	else if(m_pPlayParm->pVolume != 0 && !m_pPlayParm->pSound)
	{
		m_bnSound->ChangePng(FALSE);
		m_pPlayParm->pSound = TRUE;
	}
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CPlToolBar::AttachPlayer(PL_PlayParm *pPlayParm, void *parent)
{
	if(NULL == pPlayParm) 
		return FALSE;

	if(m_pPlayParm == pPlayParm) 
	{
		DWORD newTime = GetTickCount();
		if(newTime - m_pPlayParm->dwUIT >= UPDATETOOLTIME)
		{
			m_pPlayParm->dwUIT = newTime;
			//disable some button
			if(PlManager::Instance()->IsPlaying(m_hPlWnd))
				EnableSomeButton(TRUE);
			else
				EnableSomeButton(FALSE);
		}
		return TRUE;
	}
	else
	{
		m_pPlayParm = pPlayParm;
		//ShowControls(FALSE);	//右键以后只有该窗口才不现实工具条
		SetParent((CWnd *)parent);
		m_hPlWnd = ((CWnd *)parent)->m_hWnd;
	}

	//绘制声音开关
	if(m_pPlayParm->pSound)
	{
		m_bnSound->ChangePng(FALSE);
		m_toolTip.AddTool(m_bnSound,"静音");
		//绘制音量条
		m_bnSlider->SetPos(m_pPlayParm->pVolume);
		m_toolTip.AddTool(m_bnSlider, m_pPlayParm->pVolume);
	}
	else
	{
		m_bnSound->ChangePng();
		m_toolTip.AddTool(m_bnSound,"取消静音");
		//绘制音量条
		m_bnSlider->SetPos(0);
		m_toolTip.AddTool(m_bnSlider,0);
	}

	return TRUE;
}

void CPlToolBar::ShowControls(BOOL bShow)
{
	if(bShow)
	{
		if(!(GetWindowLong(this->m_hWnd, GWL_STYLE) & WS_VISIBLE))
		{
			ShowWindow(SW_SHOW);
		}
		SetTimer(TOOL_TIMER, TOOLSTAYTIME, NULL);
	}
	else
	{
		KillTimer(TOOL_TIMER);
		ShowWindow(SW_HIDE);
	}
}

void CPlToolBar::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == TOOL_TIMER)
	{
		POINT MousePoint;
		GetCursorPos(&MousePoint);
		RECT ToolWndRect;
		GetWindowRect(&ToolWndRect);
		if(PtInRect(&ToolWndRect, MousePoint))
		{
			//do not allow control window to close while mouse is within
			ShowControls(TRUE);
		}
		else
		{
			ShowControls(FALSE);
		}
	}
	
	CWnd::OnTimer(nIDEvent);
}

void CPlToolBar::EnableSomeButton(BOOL bEnable)
{
	//m_bnSound ,m_bnSlider,always enable;

	m_bnStop->EnableWindow(bEnable);
	m_bnCapture->EnableWindow(bEnable);

	if(m_eModel == STREAME_REALTIME)
	{
		m_bnSpeak->EnableWindow(bEnable);
		m_bnRecord->EnableWindow(bEnable);
	}
	else
	{
		m_bnPause->EnableWindow(bEnable);
		m_bnFramePlay->EnableWindow(bEnable);
		m_bnSpeedup->EnableWindow(bEnable);
		m_bnSlowdown->EnableWindow(bEnable);
		m_bnDownload->EnableWindow(bEnable);
	}
}
void CPlToolBar::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd::OnShowWindow(bShow, nStatus);
}

void CPlToolBar::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	SetLayout();
}

void CPlToolBar::OnMouseMove(UINT nFlags, CPoint point)
{
	::SendMessage(GetParent()->m_hWnd,WM_MOUSEMOVE,0,MAKELPARAM(point.x,point.y));
	CWnd::OnMouseMove(nFlags, point);
}

WND_BEGIN_MAKER(t_play)
	WND_ENTER_MAKER("t_play", CPlToolBar::Maker)
WND_END_MAKER()