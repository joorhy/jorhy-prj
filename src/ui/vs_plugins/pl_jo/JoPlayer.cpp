#include "StdAfx.h"
#include "JoPlayer.h"
#include "pl_manager.h"
#include "pl_reconn.h"

/*********************回调函数*******************/
void X_PL_API JoPlayer::EndCBK(void *pdata)
{
	JoPlayer *user = reinterpret_cast<JoPlayer*>(pdata);
	if(user)
	{
		if(user->m_Model == STREAME_REALTIME)
		{
			user->Stop();
			PostMessage(PlManager::Instance()->GetRecntWnd(user->m_pPlWnd),WM_OWN_START_WAIT,(WPARAM)user->m_pPlWnd,0);
		}
		else
		{
			PostMessage(user->m_pPlWnd,WM_MEDIA_END_REACHED,0,0);
		}
	}
}

void JoPlayer::OnDisplayCbFunc( j_pl_mtime_t frame_time)
{
	if (frame_time - m_lastFrameTime >= 1000)
	{
		PlManager::Instance()->VodCallBack(m_pPlWnd);
		m_lastFrameTime = frame_time;
	}
}

/*********************类实现*********************/
JoPlayer::JoPlayer(int nWorkMode, HWND hWnd)
{
	m_player		= new J_PlControl();
	m_Model		= nWorkMode;
	m_pPlWnd	= hWnd;
	m_lastFrameTime = 0;
}

JoPlayer::~JoPlayer(void)
{
	if(m_player)
		delete m_player;
}

BOOL JoPlayer::Play(HWND hPlayWnd, const PL_PlayInfo &playInfo)
{
	J_PL_RESULT br;
	char mrl[128] = {0};
	if (playInfo.nPlayMode == STREAME_REALTIME)
	{
		sprintf(mrl,"RYSP://%s:%d/%s", playInfo.strIpaddr, 8002, playInfo.strResid);
		m_lastMrl = mrl;
		br = m_player->InitPlayByNetwork(mrl);
	}
	else
	{
		Stop();
		sprintf(mrl,"RYSP://%s:%d/%s?start=%d&end=%d", playInfo.strIpaddr, 8002, playInfo.strResid, playInfo.nStartTime, playInfo.nEndTime);
		br = m_player->InitPlayByNetwork(mrl, J_PL_PLAY_FILE);
		m_player->SetDisplayCBK(JoPlayer::DisplayCbFunc, this);
	}
	if(br != J_PL_NO_ERROR)
		return FALSE;
	br = m_player->SetHwnd(hPlayWnd);
	if(br != J_PL_NO_ERROR)
		return FALSE;
	br = m_player->Run();
	if(br != J_PL_NO_ERROR)
		return FALSE;
	
	m_pPlWnd = hPlayWnd;

	m_player->SetEndCBK(EndCBK,this);
	
	return TRUE;
}

BOOL JoPlayer::RePlay()
{
	m_lock.Lock();
	if(m_player)
	{
		J_PL_RESULT br;
		delete m_player;
		m_player = NULL;
		m_player = new J_PlControl();
	
		br = m_player->InitPlayByNetwork(m_lastMrl.c_str());
		if(br != J_PL_NO_ERROR)
		{
			m_lock.Unlock();
			return FALSE;
		}
		br = m_player->SetHwnd(m_pPlWnd);
		if(br != J_PL_NO_ERROR)
		{
			m_lock.Unlock();
			return FALSE;
		}
		br = m_player->Run();
		if(br != J_PL_NO_ERROR)
		{
			m_lock.Unlock();
			return FALSE;
		}

		m_player->SetEndCBK(EndCBK,this);
	}
	m_lock.Unlock();
	return TRUE;
}

void JoPlayer::Stop()
{
	if(m_player)
	{
		m_player->Stop();
	}
}

void JoPlayer::Pause()
{

}

void JoPlayer::PlayOneByOne()
{

}

int JoPlayer::GetVolume()
{
	return 0;
}

BOOL JoPlayer::SetVolume(int nVolume)
{
	return TRUE;
}

BOOL JoPlayer::IsPlaying()
{
	BOOL bRet = FALSE;
	m_lock.Lock();
	if(m_player)
	{
		bRet = m_player->IsPlaying();
	}
	m_lock.Unlock();
	return bRet;
}

BOOL JoPlayer::SetSpeed(BOOL bSpeedUp)
{
	return TRUE;
}

BOOL JoPlayer::Capture(char *path)
{
	if(m_player)
	{
		m_player->Snapshot(path);
	}
	return TRUE;
}

BOOL JoPlayer::Record(char *path)
{
	return TRUE;
}

int JoPlayer::GetPlayStatus()
{
	int state = J_PL_NORMAL;
	if(m_player)
	{
		m_player->GetState(state);
	}
	return state;
}

HWND JoPlayer::GetPlayHwnd()
{
	return m_pPlWnd;
}

BOOL JoPlayer::VodStreamJump(const PL_PlayInfo &playInfo)
{
	HWND hwnd = GetPlayHwnd();
	SendMessage(hwnd,WM_OWN_ERASEBKGROUND,FALSE,0);
	//m_nSpeedIndex = NORMALSPEED;
	return Play(hwnd, playInfo);
}

BOOL JoPlayer::SetOSDText(int stime,char *osdText)
{
	return TRUE;
}

BOOL JoPlayer::IsPaused()
{
	return TRUE;
}

void JoPlayer::AspectRatio(int width,int height)
{

}

void JoPlayer::SleepPlayer(bool bSleep)
{
	if(m_player)
	{
		m_player->SleepPlayer(bSleep);
	}
}

PLAYER_BEGIN_MAKER(pl_jo)
	PLAYER_ENTER_MAKER("pl_jo", JoPlayer::Maker)
PLAYER_END_MAKER()