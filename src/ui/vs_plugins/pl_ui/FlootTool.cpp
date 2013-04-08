// FlootTool.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "FlootTool.h"
#include "Resource.h"
#include "pl_ctrl.h"

// CFlootTool

IMPLEMENT_DYNAMIC(CFlootTool, CWnd)

CFlootTool::CFlootTool(CWnd *parent, UINT nId)
{
	LPCTSTR wndClass = AfxRegisterWndClass(CS_DBLCLKS, 
										AfxGetApp()->LoadStandardCursor(IDC_ARROW),
										(HBRUSH)(COLOR_3DFACE+1),
										0);
	m_bCreate = FALSE;
	CreateEx(WS_EX_TOPMOST,
			wndClass,_T("myToolWnd"),
			WS_CHILD | WS_CLIPSIBLINGS, 
			0,0,MINWINDOW_WIDTH,MINWINDOW_HEIGHT,
			parent->m_hWnd,0);
	//SetLayeredWindowAttributes(RGB(128,128,128),128,LWA_ALPHA);
}

void CFlootTool::InitParm()
{
	m_bnStop	= NULL;
	m_bnSound	= NULL;
	m_bnCapture	= NULL;
	m_bnSlider	= NULL;
	m_bnSpeak	= NULL;
	m_bnRecord	= NULL;
	m_bnPause	= NULL;
	m_bnFramePlay	= NULL;
	m_bnSpeedup		= NULL;
	m_bnSlowdown	= NULL;
	m_bnDownload	= NULL;
	if(CreateToolBar())
	{
		m_bCreate = TRUE;
	}
	m_Player	= NULL; 
}

CFlootTool::~CFlootTool()
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


BEGIN_MESSAGE_MAP(CFlootTool, CWnd)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDBN_STOP,&CFlootTool::Stop)
	ON_BN_CLICKED(IDBN_CAPTURE,&CFlootTool::Capture)
	ON_BN_CLICKED(IDBN_SOUND,&CFlootTool::EnableSound)
	ON_BN_CLICKED(IDBN_SPEAK,&CFlootTool::Speak)
	ON_BN_CLICKED(IDBN_RECORD,&CFlootTool::Record)
	ON_BN_CLICKED(IDBN_PAUSE,&CFlootTool::Pause)
	ON_BN_CLICKED(IDBN_FRAMEPLAY,&CFlootTool::PlayOneByOne)
	ON_BN_CLICKED(IDBN_SPEEDUP,&CFlootTool::SpeedUp)
	ON_BN_CLICKED(IDBN_SLOWDOWN,&CFlootTool::SlowDown)
	ON_BN_CLICKED(IDBN_DOWNLOAD,&CFlootTool::Download)
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CFlootTool message handlers

BOOL CFlootTool::CreateToolBar()
{
	EnableToolTips(TRUE);
	m_toolTip.Create(this);
	HINSTANCE hInst = AfxGetInstanceHandle();
	m_bnStop	= new CPngButton(hInst,this,IDBN_STOP);
	m_bnStop->LoadPng(IDP_STOP_N,IDP_STOP_V,IDP_STOP_D,IDP_STOP_X);
	m_toolTip.AddTool(m_bnStop,"停止");

	m_bnSound	= new CPngButton(hInst,this,IDBN_SOUND);
	m_bnSound->LoadPng(IDP_SOUND_CLOSE_N,IDP_SOUND_CLOSE_V,IDP_SOUND_CLOSE_D,IDP_SOUND_CLOSE_X,
					IDP_SOUND_OPEN_N,IDP_SOUND_OPEN_V,IDP_SOUND_OPEN_D,IDP_SOUND_OPEN_X);
	m_toolTip.AddTool(m_bnSound,"取消静音");

	m_bnCapture	= new CPngButton(hInst,this,IDBN_CAPTURE);
	m_bnCapture->LoadPng(IDP_CAPTURE_N,IDP_CAPTURE_V,IDP_CAPTURE_D,IDP_CAPTURE_X);
	m_toolTip.AddTool(m_bnCapture,"抓图");

	m_bnSlider	= new CExactSlider(this,IDBN_SLIDER);
	m_toolTip.AddTool(m_bnSlider,DEFAULT_VOLUME);
	switch(m_eModel)
	{
	case REALMODEL:
		m_bnSpeak	= new CPngButton(hInst,this,IDBN_SPEAK);
		m_bnSpeak->LoadPng(IDP_SPEAK_CLOSE_N,IDP_SPEAK_CLOSE_V,IDP_SPEAK_CLOSE_D,IDP_SPEAK_CLOSE_X);
		m_toolTip.AddTool(m_bnSpeak,"开启对讲");

		m_bnRecord	= new CPngButton(hInst,this,IDBN_RECORD);
		m_bnRecord->LoadPng(IDP_RECORD_CLOSE_N,IDP_RECORD_CLOSE_V,IDP_RECORD_CLOSE_D,IDP_RECORD_CLOSE_X,
							IDP_RECORD_OPEN_N,IDP_RECORD_OPEN_V,IDP_RECORD_OPEN_D,IDP_RECORD_OPEN_X);
		m_toolTip.AddTool(m_bnRecord,"开启录像");

		break;

	case VODMODEL:
		m_bnPause	= new CPngButton(hInst,this,IDBN_PAUSE);
		m_bnPause->LoadPng(IDP_PAUSE_N,IDP_PAUSE_V,IDP_PAUSE_D,IDP_PAUSE_X);
		m_toolTip.AddTool(m_bnPause,"暂停播放");

		m_bnFramePlay= new CPngButton(hInst,this,IDBN_FRAMEPLAY);
		m_bnFramePlay->LoadPng(IDP_FRAMEPLAY_N,IDP_FRAMEPLAY_V,IDP_FRAMEPLAY_D,IDP_FRAMEPLAY_X);
		m_toolTip.AddTool(m_bnFramePlay,"单帧播放");

		m_bnSpeedup	= new CPngButton(hInst,this,IDBN_SPEEDUP);
		m_bnSpeedup->LoadPng(IDP_SPEEDUP_N,IDP_SPEEDUP_V,IDP_SPEEDUP_D,IDP_SPEEDUP_X);
		m_toolTip.AddTool(m_bnSpeedup,"快进");

		m_bnSlowdown= new CPngButton(hInst,this,IDBN_SLOWDOWN);
		m_bnSlowdown->LoadPng(IDP_SLOWDOWN_N,IDP_SLOWDOWN_V,IDP_SLOWDOWN_D,IDP_SLOWDOWN_X);
		m_toolTip.AddTool(m_bnSlowdown,"慢放");

		m_bnDownload	= new CPngButton(hInst,this,IDBN_DOWNLOAD);
		m_bnDownload->LoadPng(IDP_SAVE_N,IDP_SAVE_V,IDP_SAVE_D,IDP_SAVE_X);
		m_toolTip.AddTool(m_bnDownload,"录像下载");
		
		break;

	default:
		return FALSE;
	}
	return TRUE;
}

void CFlootTool::SetLayout()
{
	if(!m_bCreate)
		return;
	CRect rect,bnPos;
	GetClientRect(&rect);
	m_bnStop->CenterWindow();
	switch(m_eModel)
	{
	case REALMODEL:
		LayWndLeft(FALSE,m_bnStop->m_hWnd,m_bnSound->m_hWnd,5);	
		LayWndLeft(FALSE,m_bnSound->m_hWnd,m_bnSlider->m_hWnd,5);	
		LayWndLeft(FALSE,m_bnSlider->m_hWnd,m_bnSpeak->m_hWnd,5);
		LayWndLeft(TRUE,m_bnStop->m_hWnd,m_bnCapture->m_hWnd,5);
		LayWndLeft(TRUE,m_bnCapture->m_hWnd,m_bnRecord->m_hWnd,5);
		break;

	case VODMODEL:
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

void CFlootTool::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
{
	lpMMI->ptMinTrackSize.x	= MINWINDOW_WIDTH;
	lpMMI->ptMinTrackSize.y	= MINWINDOW_HEIGHT;
	lpMMI->ptMaxTrackSize.x	= MINWINDOW_WIDTH;
	lpMMI->ptMaxTrackSize.y = MINWINDOW_HEIGHT;
}

void CFlootTool::LayWndLeft(BOOL bLeft,HWND hReferWnd,HWND hMoveWnd,int nInterval)
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
void CFlootTool::Stop()
{
	if(m_Player == NULL) return;
	if(m_Player->pPlayer != NULL)
	{
		HWND wnd = m_Player->pPlayer->GetPlayHwnd();
		m_Player->pPlayer->StatusCallBack(wnd);
		m_Player->pPlayer->Stop();
		m_Player->pSound  = FALSE;
		m_Player->pVolume = DEFAULT_VOLUME;
	}
}

void CFlootTool::EnableSound()
{
	if(m_Player == NULL) return;
	if(m_Player->pSound)
	{
		m_bnSound->ChangePng();
		m_Player->pSound = FALSE;
		m_Player->pVolume = m_Player->pPlayer->GetVolume();
		m_Player->pPlayer->SetVolume(0);
		m_bnSlider->SetPos(0);

		m_toolTip.AddTool(m_bnSound,"取消静音");
		m_toolTip.AddTool(m_bnSlider,0);
	}
	else
	{
		m_bnSound->ChangePng(FALSE);
		m_Player->pSound = TRUE;
		m_Player->pPlayer->SetVolume(m_Player->pVolume);
		m_bnSlider->SetPos(m_Player->pVolume);
		m_toolTip.AddTool(m_bnSound,"静音");
		m_toolTip.AddTool(m_bnSlider,m_Player->pVolume);
	}
	
	
}

void CFlootTool::Capture()
{
	char path[PATH_LENGTH] = {0};
	CPlCtrl::GetPath(path,IMAGEPATH);
	m_Player->pPlayer->Capture(path);
}


/************************************************************************/
/*                               Real									*/
/************************************************************************/
void CFlootTool::Speak()
{
	m_Player->pPlayer->SetOsdText(2,"对讲");
}

void CFlootTool::Record()
{
	char path[PATH_LENGTH] = {0};
	CPlCtrl::GetPath(path,VIDEOPATH);
	if(m_Player->pPlayer->Record(path))
	{
		m_Player->bRecoder = !m_Player->bRecoder;
		if(m_Player->bRecoder)
		{
			m_bnRecord->ChangePng(FALSE);
			m_toolTip.AddTool(m_bnRecord,"关闭录像");
		}
		else
		{
			m_bnRecord->ChangePng();
			m_toolTip.AddTool(m_bnRecord,"开启录像");
		}
		m_Player->pPlayer->SetOsdText(2,"录像");
	}
}

/************************************************************************/
/*                             Vod										*/
/************************************************************************/
void CFlootTool::Pause()
{
	m_Player->pPlayer->Pause();
	if(m_Player->bPlayOneByOne)
	{
		m_Player->pPlayer->SetOsdText(2,"恢复播放");
		m_Player->bPlayOneByOne = FALSE;
	}
	else
	{
		if(m_Player->pPlayer->IsPaused())
			m_Player->pPlayer->SetOsdText(2,"恢复播放");
		else
			m_Player->pPlayer->SetOsdText(2,"暂停");
	}
}

void CFlootTool::PlayOneByOne()
{
	m_Player->pPlayer->PlayOneByOne();
	m_Player->bPlayOneByOne = TRUE;
	m_Player->pPlayer->SetOsdText(2,"单帧播放>>");

}

void CFlootTool::SpeedUp()
{
	m_Player->pPlayer->SetSpeed(TRUE);
}

void CFlootTool::SlowDown()
{
	m_Player->pPlayer->SetSpeed(FALSE);
}

void CFlootTool::Download()
{
	m_Player->pPlayer->SetOsdText(2,"下载");
}


void CFlootTool::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_Player->pVolume = ((CExactSlider*)pScrollBar)->GetPos();
	m_Player->pPlayer->SetVolume(m_Player->pVolume);
	m_toolTip.AddTool(m_bnSlider,m_Player->pVolume);
	if(m_Player->pVolume == 0 && m_Player->pSound)
	{
		m_bnSound->ChangePng();
		m_Player->pSound = FALSE;
	}
	else if(m_Player->pVolume != 0 && !m_Player->pSound)
	{
		m_bnSound->ChangePng(FALSE);
		m_Player->pSound = TRUE;
	}

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CFlootTool::AttachPlayer(void *pPlayParm, void *parent)
{
	if(NULL == pPlayParm) 
		return FALSE;
	PlayParm *pPlayer = reinterpret_cast<PlayParm *>(pPlayParm);
	if(m_Player == pPlayer) 
	{
		DWORD newTime = GetTickCount();
		if(newTime - m_Player->dwUIT >= UPDATETOOLTIME)
		{
			m_Player->dwUIT = newTime;
			//disable some button
			if(m_Player->pPlayer->IsPlaying())
				EnableSomeButton(TRUE);
			else
				EnableSomeButton(FALSE);
		}
		return TRUE;
	}
	else
	{
		m_Player = pPlayer;
		ShowControls(FALSE);	//右键以后只有该窗口才不现实工具条
		SetParent((CWnd *)parent);
	}

	//绘制声音开关
	if(m_Player->pSound)
	{
		m_bnSound->ChangePng(FALSE);
		m_toolTip.AddTool(m_bnSound,"静音");
		//绘制音量条
		m_bnSlider->SetPos(m_Player->pVolume);
		m_toolTip.AddTool(m_bnSlider,m_Player->pVolume);
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

void CFlootTool::ShowControls(BOOL bShow)
{
	if(bShow)
	{
		if(m_Player && m_Player->bNeedShowCTRL == FALSE)
			return;
		if(!(GetWindowLong(this->m_hWnd, GWL_STYLE) & WS_VISIBLE))
		{
			ShowWindow(SW_SHOW);
		}
		SetTimer(TOOL_TIMER,TOOLSTAYTIME,NULL);
	}
	else
	{
		KillTimer(TOOL_TIMER);
		ShowWindow(SW_HIDE);
	}
}


void CFlootTool::OnTimer(UINT_PTR nIDEvent)
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

void CFlootTool::EnableSomeButton(BOOL bEnable)
{
	//m_bnSound ,m_bnSlider,always enable;

	m_bnStop->EnableWindow(bEnable);
	m_bnCapture->EnableWindow(bEnable);

	if(m_eModel == REALMODEL)
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
void CFlootTool::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd::OnShowWindow(bShow, nStatus);
}

void CFlootTool::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	SetLayout();
}

void CFlootTool::OnMouseMove(UINT nFlags, CPoint point)
{
	::SendMessage(GetParent()->m_hWnd,WM_MOUSEMOVE,0,MAKELPARAM(point.x,point.y));
	CWnd::OnMouseMove(nFlags, point);
}
