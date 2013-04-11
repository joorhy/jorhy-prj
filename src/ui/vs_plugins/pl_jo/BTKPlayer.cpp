#include "StdAfx.h"
#include "BTKPlayer.h"
#include "pl_manager.h"
#include "pl_reconn.h"

/*********************回调函数*******************/
void BTKAPI BTKPlayer::EndCBK(void *pdata)
{
	BTKPlayer *user = reinterpret_cast<BTKPlayer*>(pdata);
	if(user)
	{
		if(user->m_Model == STREAME_REALTIME)
		{
			PostMessage(user->m_pPlWnd,WM_OWN_START_WAIT,(WPARAM)user->m_pPlWnd,0);
		}
		else
		{
			PostMessage(user->m_pPlWnd,WM_MEDIA_END_REACHED,0,0);
		}
	}
}

/*********************类实现*********************/
BTKPlayer::BTKPlayer(int nWorkMode, HWND hWnd)
{
	m_player		= new BTKControl();
	m_Model		= nWorkMode;
}

BTKPlayer::~BTKPlayer(void)
{
	if(m_player)
		delete m_player;
}

BOOL BTKPlayer::Play(HWND hPlayWnd, const PL_PlayInfo &playInfo)
{
	BTK_RESULT br;
	char *beg = strstr((char *)playInfo.pUrl, "//");
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

		sprintf(mrl,"RYSP://%s:%d/%s", playInfo.strIpaddr, 8002, playInfo.strResid);

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

BOOL BTKPlayer::VodStreamJump(const PL_PlayInfo &playInfo)
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

PLAYER_BEGIN_MAKER(pl_jo)
	PLAYER_ENTER_MAKER("pl_jo", BTKPlayer::Maker)
PLAYER_END_MAKER()