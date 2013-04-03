#include "StdAfx.h"
#include "BTKPlayer.h"
#include "PlayerFactor.h"
#include "WaitStatus.h"

/*********************回调函数*******************/
void BTKAPI BTKPlayer::EndCBK(void *pdata)
{
	BTKPlayer *user = reinterpret_cast<BTKPlayer*>(pdata);
	if(user)
	{
		PlayerFactor *tmp = static_cast<PlayerFactor*>(user->m_pFactor);
		if(tmp)
		{
			if(user->m_Model == STREAME_REALTIME)
			{
				HWND wnd = ((CWaitStatus*)tmp->GetRecntWnd())->m_hWnd;
				PostMessage(wnd,WM_OWN_START_WAIT,(WPARAM)tmp,0);
			}
			else
			{
				HWND wnd = tmp->GetPlayHwnd();
				PostMessage(wnd,WM_MEDIA_END_REACHED,0,0);
			}
		}
	}
}

/*********************类实现*********************/
BTKPlayer::BTKPlayer(int nWorkMode,void *pFactorUser)
{
	m_player	= new BTKControl();
	m_Model		= nWorkMode;
	m_pFactor	= pFactorUser;
}

BTKPlayer::~BTKPlayer(void)
{
	if(m_player)
		delete m_player;
}

BOOL BTKPlayer::Play(HWND hPlayWnd,char *psz_mrl)
{
	BTK_RESULT br;
	char *beg = strstr(psz_mrl,"//");
	char *end = NULL;
	int len = 0;
	char mrl[128] = {0};
	char ip[16] = {0};
	char resid[16] = {0};
	if(beg)
	{
		beg += strlen("//");
		end = strchr(beg,':');
		memcpy(ip,beg,end-beg);
		
		beg = end;
		beg = strstr(beg,"resid=");
		beg += strlen("resid=");
		end = strchr(beg,'&');
		memcpy(resid,beg,end-beg);

		sprintf(mrl,"RYSP://%s:%d/%s",ip,8002,resid);

		//sprintf(mrl,"RYSP://192.168.1.10:8002/44");
		br = m_player->InitPlayByNetwork(mrl);
		if(br != BTK_NO_ERROR)
			return FALSE;
		br = m_player->SetHwnd(hPlayWnd);
		if(br != BTK_NO_ERROR)
			return FALSE;
		br = m_player->Run();
		if(br != BTK_NO_ERROR)
			return FALSE;
		
		m_lastMrl = mrl;
		m_hwnd = hPlayWnd;

		m_player->SetEndCBK(EndCBK,this);
		
	}
	return TRUE;
}

void BTKPlayer::Play()
{
	m_lock.Lock();
	if(m_player)
	{

		BTK_RESULT br;
		delete m_player;
		m_player = NULL;
		m_player = new BTKControl();
	
		br = m_player->InitPlayByNetwork(m_lastMrl.c_str());
		if(br != BTK_NO_ERROR)
			goto BTK_Exit;
		br = m_player->SetHwnd(m_hwnd);
		if(br != BTK_NO_ERROR)
			goto BTK_Exit;
		br = m_player->Run();
		if(br != BTK_NO_ERROR)
			goto BTK_Exit;

		m_player->SetEndCBK(EndCBK,this);
	}
	m_lock.Unlock();

BTK_Exit:
	m_lock.Unlock();
}

void BTKPlayer::Stop()
{
	if(m_player)
	{
		m_player->Stop();
	}
}

void BTKPlayer::Pause()
{

}

void BTKPlayer::PlayOneByOne()
{

}

int BTKPlayer::GetVolume()
{
	return 0;
}

BOOL BTKPlayer::SetVolume(int nVolume)
{
	return TRUE;
}

BOOL BTKPlayer::IsPlaying()
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

BOOL BTKPlayer::SetSpeed(BOOL bSpeedUp)
{
	return TRUE;
}

BOOL BTKPlayer::Capture(char *path)
{
	if(m_player)
	{
		m_player->Snapshot(path);
	}
	return TRUE;
}

BOOL BTKPlayer::Record(char *path)
{
	return TRUE;
}

int BTKPlayer::GetPlayStatus()
{
	int state = BTK_NORMAL;
	if(m_player)
	{
		m_player->GetState(state);
	}
	return state;
}

HWND BTKPlayer::GetPlayHwnd()
{
	return m_hwnd;
}

BOOL BTKPlayer::VodStreamJump(char *pNewTime_MRL)
{
	return TRUE;
}

BOOL BTKPlayer::SetOSDText(int stime,char *osdText)
{
	return TRUE;
}

BOOL BTKPlayer::IsPaused()
{
	return TRUE;
}

void BTKPlayer::AspectRatio(int width,int height)
{

}

void BTKPlayer::SleepPlayer(bool bSleep)
{
	if(m_player)
	{
		m_player->SleepPlayer(bSleep);
	}
}