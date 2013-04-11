#include "StdAfx.h"
#include "pl_manager.h"
#include "pl_factory.h"
#include "pl_reconn.h"
#include "pl_json_parser.h"
#include "runner_log.h"

/*******************类实现*****************************/
PlManager::PlManager()
{
	m_nLastTime			= 0;
	m_nVodEndTime	= 0;
	m_pFuncCallBk		= NULL;
	m_nPlayNum		= 0;
}

PlManager::~PlManager(void)
{

}

BOOL PlManager::Play(HWND hWnd, const PL_PlayInfo &playInfo)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end() && it->second.bPlay)
	{
		Stop(it->first);
	}

	BOOL bRet;
	
	it->second.hWnd = hWnd;
	it->second.playInfo = playInfo;
	CreateMrl(playInfo);
	switch(playInfo.nStreamType)
	{
	case HIK_VIDEO:
		it->second.pPlayer = CPlFactory::Instance()->GetPlayer("pl_hik", playInfo.nPlayMode, this, hWnd);
		break;
	case VLC_VIDEO:
		if (playInfo.nPlayMode == STREAME_REALTIME)
			it->second.pPlayer = CPlFactory::Instance()->GetPlayer("pl_jo", playInfo.nPlayMode, this, hWnd);
		else
			it->second.pPlayer = CPlFactory::Instance()->GetPlayer("pl_vlc", playInfo.nPlayMode, this, hWnd);
		break;
	default:
		return FALSE;
	}

	if(it->second.pPlayer)
	{
		if((bRet = it->second.pPlayer->Play(hWnd, playInfo)))
		{
			m_nPlayNum++;
			it->second.bPlay = TRUE;
			it->second.dwPlayTime = playInfo.nStartTime;
		}

		if(playInfo.nPlayMode == STREAME_REALTIME)
		{
			if(!it->second.pReconnWnd)
				it->second.pReconnWnd = new CWaitStatus(CWnd::FromHandle(::GetParent(hWnd)));
		}
		else
		{
			VodCallBack(hWnd);
		}
	}

	return bRet;
}

void PlManager::CreateMrl(const PL_PlayInfo &playInfo)
{
	if(playInfo.nStreamType == VLC_VIDEO)
		sprintf((char *)playInfo.pUrl, PROTO_HTTP);
	else
		sprintf((char *)playInfo.pUrl, PROTO_JOSP);

	char tmpInfo[128];
	if(STREAME_REALTIME == playInfo.nPlayMode)
	{
		sprintf(tmpInfo,"%s:%d/real?resid=%s&cmd=%d&type=%d",
			playInfo.strIpaddr, playInfo.nPort, playInfo.strResid, 1, playInfo.nSubStreamType);
	}
	else if(STREAME_FILE == playInfo.nPlayMode)
	{
		m_nVodEndTime = playInfo.nEndTime;
		sprintf(tmpInfo,"%s:%d/vodl?resid=%s&cmd=%d&start=%d&end=%d",
			playInfo.strIpaddr, playInfo.nPort, playInfo.strResid, 3, playInfo.nStartTime, playInfo.nEndTime);
	}
	strcat((char *)playInfo.pUrl, tmpInfo);
}

BOOL PlManager::Capture(HWND hWnd, char *pPath)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		time_t t_locatime = time(NULL);
		tm *tm_locatime; 
		tm_locatime = localtime(&t_locatime);
		char locatime[256]	= {0};
		char path_name[512] = {0};
		sprintf(locatime,"\\RonYaoCapture-%d-%d-%d-%d-%d-%d.png",
			tm_locatime->tm_year+1990,
			tm_locatime->tm_mon+1,
			tm_locatime->tm_mday,
			tm_locatime->tm_hour,
			tm_locatime->tm_min,
			tm_locatime->tm_sec);
		strcat(path_name, pPath);
		strcat(path_name, locatime);

		return it->second.pPlayer->Capture(path_name);
	}
	return FALSE;
}

BOOL PlManager::SetSpeed(HWND hWnd, BOOL bSpeedUp)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		return it->second.pPlayer->SetSpeed(bSpeedUp);
	}
	return FALSE;
}

BOOL PlManager::Record(HWND hWnd, char *pPath)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		return it->second.pPlayer->Record(pPath);
	}
	return FALSE;
}

void PlManager::Stop(HWND hWnd)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end() && it->second.bPlay)
	{
		SendMessage(hWnd, WM_OWN_ERASEBKGROUND,TRUE,0);
		it->second.pPlayer->Stop();

		m_nPlayNum--;
		m_nVodEndTime = 0;
		if(m_nPlayNum == 0)
		{
			int args[2];
			args[0] = 1;
			args[1] = (int)"null";

			NotifyNpn(hWnd, CALLBACK_ONSTATE, args, sizeof(args)/sizeof(int));
		}
		CPlFactory::Instance()->DelPlayer(hWnd);
		it->second.bPlay = FALSE;
	}
	return;
}

void PlManager::Pause(HWND hWnd)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		return it->second.pPlayer->Pause();
	}
	return;
}

void PlManager::PlayOneByOne(HWND hWnd)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		return it->second.pPlayer->PlayOneByOne();
	}
	return;
}

int PlManager::GetVolume(HWND hWnd)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		return it->second.pPlayer->GetVolume();
	}
	return -1;
}

BOOL PlManager::SetVolume(HWND hWnd, int nVolume)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		return it->second.pPlayer->SetVolume(nVolume);
	}
	return FALSE;
}

BOOL PlManager::IsPlaying(HWND hWnd)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end() && it->second.bPlay)
	{
		return it->second.pPlayer->IsPlaying();
	}
	return FALSE;
}

void PlManager::VodCallBack(HWND hWnd)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		int args[1];
		if(it->second.dwPlayTime > m_nVodEndTime)
		{
			PostMessage(hWnd, WM_MEDIA_END_REACHED, 0, 0);
			return;
		}
		args[0] = (int)&it->second.dwPlayTime;
		++it->second.dwPlayTime;
		NotifyNpn(hWnd, CALLBACK_ONVOD, args, sizeof(args)/sizeof(int));
	}
	return;
}

BOOL PlManager::RegisterCallBack(NpnNotifyFunc funcAddr)
{
	if(NULL == funcAddr)
		return FALSE;
	else
		m_pFuncCallBk = funcAddr;

	return TRUE;
}

void PlManager::NotifyNpn(HWND hWnd, UINT nType, int args[], UINT argCount)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		if(NULL == m_pFuncCallBk || NULL == it->second.pUser) 
			return;
		else
			m_pFuncCallBk(it->second.pUser, nType, args, argCount);
	}
}

BOOL PlManager::GetWndPlayParm(HWND hWnd, char *pPlayerParm)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		PlJsonParser::Instance()->MakeWndParam(it->second.playInfo, pPlayerParm);
		return  TRUE;
	}
	return FALSE;
}

BOOL PlManager::GetPlayInfo(HWND hWnd, PL_PlayInfo &playInfo)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		playInfo = it->second.playInfo;
		return  TRUE;
	}
	return FALSE;
}

BOOL PlManager::VodStreamJump(HWND hWnd, const PL_PlayInfo &playInfo)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		if(!IsPlaying(hWnd))
			return TRUE;
		
		if (playInfo.nStartTime > it->second.playInfo.nEndTime)		//超出结束时间就停止
		{
			PostMessage(hWnd, WM_MEDIA_END_REACHED, 0, 0);
			return FALSE;
		}
		it->second.playInfo.nStartTime = playInfo.nStartTime;
		it->second.dwPlayTime = playInfo.nStartTime;
		CreateMrl(it->second.playInfo);
		return it->second.pPlayer->VodStreamJump(it->second.playInfo);
	}
	return FALSE;
}

void PlManager::Play(HWND hWnd)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		return it->second.pPlayer->Play();
	}
}

CWnd *PlManager::GetRecntWnd(HWND hWnd)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		return it->second.pReconnWnd;
	}
}

void PlManager::StatusCallBack(HWND hPlayWnd)
{
	PlayerMap::iterator it = m_playerMap.find(hPlayWnd);
	if (it != m_playerMap.end())
	{
		char pJsStr[512] = {0};
		int args[2];
		args[0] = 3;
		PlJsonParser::Instance()->MakeCbStatus(it->second.playInfo, pJsStr);
		args[1] = (int)pJsStr;
		NotifyNpn(hPlayWnd, CALLBACK_ONSTATE, args, sizeof(args)/sizeof(int));
	}
}

BOOL PlManager::SetUserData(HWND hWnd, void *pUser)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		it->second.pUser = pUser;
	}
	else
	{
		PL_PlayerInfo info = {0};
		info.pUser = pUser;
		m_playerMap[hWnd] = info;
	}

	return TRUE;
}

BOOL PlManager::SetOsdText(HWND hWnd, int stime,char *osdtext)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		it->second.pPlayer->SetOSDText(stime,osdtext);
	}
	return FALSE;
}

BOOL PlManager::IsPaused(HWND hWnd)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		it->second.pPlayer->IsPaused();
	}
	return FALSE;
}

void PlManager::AspectRatio(HWND hWnd, int width,int height)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		it->second.pPlayer->AspectRatio(width,height);
	}
}

void PlManager::SleepPlayer(HWND hWnd, bool bSleep)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		it->second.pPlayer->SleepPlayer(bSleep);
	}
}