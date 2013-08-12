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
	m_playerMap.clear();
}

PlManager::~PlManager(void)
{

}

BOOL PlManager::Play(HWND hWnd, const PL_PlayInfo &playInfo)
{
	m_locker.Lock();
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end() && it->second.bPlay)
	{
		SendMessage(hWnd, WM_OWN_ERASEBKGROUND,TRUE,0);
		it->second.pPlayer->Stop();
		CPlFactory::Instance()->DelPlayer(hWnd);
		it->second.bPlay = FALSE;

		m_nPlayNum--;
		m_nVodEndTime = 0;
		if(m_nPlayNum == 0)
		{
			int args[2];
			args[0] = 1;
			args[1] = (int)"null";

			NotifyNpn(hWnd, CALLBACK_ONSTATE, args, sizeof(args)/sizeof(int));
		}
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
			it->second.pPlayer = CPlFactory::Instance()->GetPlayer("pl_jo", playInfo.nPlayMode, this, hWnd);
		break;
	default:
		{
			m_locker.Unlock();
			return FALSE;
		}
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
	m_locker.Unlock();

	return bRet;
}

void PlManager::CreateMrl(const PL_PlayInfo &playInfo)
{
	if(playInfo.nStreamType == VLC_VIDEO)
		sprintf((char *)playInfo.pUrl, PROTO_HTTP);
	else
		sprintf((char *)playInfo.pUrl, PROTO_JOSP);

	char tmpInfo[256] = {0};
	if(STREAME_REALTIME == playInfo.nPlayMode)
	{
		sprintf(tmpInfo,"%s:%d/real?resid=%s&cmd=%d&type=%d",
			playInfo.strIpaddr, playInfo.nPort, playInfo.strResid, 1, playInfo.nSubStreamType);
	}
	else if(STREAME_FILE == playInfo.nPlayMode)
	{
		m_nVodEndTime = playInfo.nEndTime;
		sprintf(tmpInfo,"%s:%d/vodl?resid=%s&cmd=3&start=%d&end=", playInfo.strIpaddr, playInfo.nPort, playInfo.strResid, playInfo.nStartTime);
		sprintf(tmpInfo, "%s%d", tmpInfo, playInfo.nEndTime);
	}
	strcat((char *)playInfo.pUrl, tmpInfo);
}

BOOL PlManager::Capture(HWND hWnd, char *pPath)
{
	m_locker.Lock();
	BOOL bRet = FALSE;
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
		bRet = it->second.pPlayer->Capture(path_name);
		
	}
	m_locker.Unlock();
	return bRet;
}

BOOL PlManager::SetSpeed(HWND hWnd, BOOL bSpeedUp)
{
	m_locker.Lock();
	BOOL bRet = FALSE;
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		bRet = it->second.pPlayer->SetSpeed(bSpeedUp);
	}
	m_locker.Unlock();
	return bRet;
}

BOOL PlManager::Record(HWND hWnd, char *pPath)
{
	m_locker.Lock();
	BOOL bRet = FALSE;
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		bRet = it->second.pPlayer->Record(pPath);
	}
	m_locker.Unlock();
	return bRet;
}

void PlManager::Stop(HWND hWnd)
{
	m_locker.Lock();
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end() && it->second.bPlay)
	{
		SendMessage(hWnd, WM_OWN_ERASEBKGROUND,TRUE,0);
		it->second.pPlayer->Stop();
		CPlFactory::Instance()->DelPlayer(hWnd);
		it->second.bPlay = FALSE;

		m_nPlayNum--;
		m_nVodEndTime = 0;
		if(m_nPlayNum == 0)
		{
			int args[2];
			args[0] = 1;
			args[1] = (int)"null";

			NotifyNpn(hWnd, CALLBACK_ONSTATE, args, sizeof(args)/sizeof(int));
		}
	}
	m_locker.Unlock();
	return;
}

void PlManager::Pause(HWND hWnd)
{
	m_locker.Lock();
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
		it->second.pPlayer->Pause();
	
	m_locker.Unlock();
	return;
}

void PlManager::PlayOneByOne(HWND hWnd)
{
	m_locker.Lock();
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
		 it->second.pPlayer->PlayOneByOne();

	m_locker.Unlock();
	return;
}

int PlManager::GetVolume(HWND hWnd)
{
	m_locker.Lock();
	int nRet = -1;
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
		nRet = it->second.pPlayer->GetVolume();
	
	m_locker.Unlock();
	return nRet;
}

BOOL PlManager::SetVolume(HWND hWnd, int nVolume)
{
	m_locker.Lock();
	BOOL bRet = FALSE;
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
		bRet = it->second.pPlayer->SetVolume(nVolume);

	m_locker.Unlock();
	return bRet;
}

BOOL PlManager::IsPlaying(HWND hWnd)
{
	m_locker.Lock();
	BOOL bRet = FALSE;
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end() && it->second.bPlay)
		bRet = it->second.pPlayer->IsPlaying();

	m_locker.Unlock();
	return bRet;
}

void PlManager::VodCallBack(HWND hWnd)
{
	//m_locker.Lock();
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		int args[1];
		if(it->second.dwPlayTime > m_nVodEndTime)
		{
			PostMessage(hWnd, WM_MEDIA_END_REACHED, 0, 0);
			//m_locker.Unlock();
			return;
		}
		args[0] = (int)&it->second.dwPlayTime;
		++it->second.dwPlayTime;
		NotifyNpn(hWnd, CALLBACK_ONVOD, args, sizeof(args)/sizeof(int));
	}
	//m_locker.Unlock();
	return;
}

BOOL PlManager::RegisterCallBack(NpnNotifyFunc funcAddr)
{
	if(NULL == funcAddr)
		return FALSE;
	else if (m_pFuncCallBk == NULL)
		m_pFuncCallBk = funcAddr;

	return TRUE;
}

void PlManager::NotifyNpn(HWND hWnd, UINT nType, int args[], UINT argCount)
{
	//m_locker.Lock();
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		if(NULL == m_pFuncCallBk || NULL == it->second.pUser) 
		{
			//m_locker.Unlock();
			return;
		}
		else
		{
			int nArgCount = argCount + 1;
			int *pArgs = new int[nArgCount];
			pArgs[0] = nType;
			for (int i=1; i<=argCount; ++i)
			{
				pArgs[i] = args[i-1];
			}
			m_pFuncCallBk(it->second.pUser, nType, pArgs, nArgCount);
			delete pArgs;
		}
	}
	//m_locker.Unlock();
}

BOOL PlManager::GetWndPlayParm(HWND hWnd, char *pPlayerParm)
{
	m_locker.Lock();
	BOOL bRet = FALSE;
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		PlJsonParser::Instance()->MakeWndParam(it->second.playInfo, pPlayerParm);
		bRet = TRUE;
	}
	m_locker.Unlock();
	return bRet;
}

BOOL PlManager::GetPlayInfo(HWND hWnd, PL_PlayInfo &playInfo)
{
	m_locker.Lock();
	BOOL bRet = FALSE;
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		playInfo = it->second.playInfo;
		bRet = TRUE;
	}
	m_locker.Unlock();
	return bRet;
}

BOOL PlManager::VodStreamJump(HWND hWnd, const PL_PlayInfo &playInfo)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		Stop(hWnd);
		if (playInfo.nStartTime > it->second.playInfo.nEndTime)		//超出结束时间就停止
		{
			PostMessage(hWnd, WM_MEDIA_END_REACHED, 0, 0);
			return FALSE;
		}

		it->second.playInfo.nStartTime = playInfo.nStartTime;
		it->second.dwPlayTime = playInfo.nStartTime;
		return Play(hWnd, it->second.playInfo);
	}
	return TRUE;
	/*m_locker.Lock();
	BOOL bRet = FALSE;
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		if (it->second.pPlayer == NULL || !it->second.bPlay)
		{
			m_locker.Unlock();
			return Play(hWnd, playInfo);
		}
		//if(!it->second.pPlayer->IsPlaying())
		//{
		//	m_locker.Unlock();
		//	return FALSE;
		//}
		
		if (playInfo.nStartTime > it->second.playInfo.nEndTime)		//超出结束时间就停止
		{
			PostMessage(hWnd, WM_MEDIA_END_REACHED, 0, 0);
			return FALSE;
		}
		it->second.playInfo.nStartTime = playInfo.nStartTime;
		it->second.dwPlayTime = playInfo.nStartTime;
		CreateMrl(it->second.playInfo);
		bRet = it->second.pPlayer->VodStreamJump(it->second.playInfo);
	}
	m_locker.Unlock();
	return bRet;*/
}

BOOL PlManager::RePlay(HWND hWnd)
{
	m_locker.Lock();
	BOOL bRet = FALSE;
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
		bRet = it->second.pPlayer->RePlay();

	m_locker.Unlock();
	return bRet;
}

HWND PlManager::GetRecntWnd(HWND hWnd)
{
	m_locker.Lock();
	HWND hRet = NULL;
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
		hRet = it->second.pReconnWnd->m_hWnd;
	
	m_locker.Unlock();
	return hRet;
}

void PlManager::StatusCallBack(HWND hPlayWnd)
{
	m_locker.Lock();
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
	m_locker.Unlock();
}

BOOL PlManager::SetUserData(HWND hWnd, void *pUser)
{
	m_locker.Lock();
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
	m_locker.Unlock();

	return TRUE;
}

BOOL PlManager::SetOsdText(HWND hWnd, int stime,char *osdtext)
{
	m_locker.Lock();
	BOOL bRet = FALSE;
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		if (it->second.bPlay)
			bRet = it->second.pPlayer->SetOSDText(stime,osdtext);
	}
	m_locker.Unlock();
	return bRet;
}

BOOL PlManager::IsPaused(HWND hWnd)
{
	m_locker.Lock();
	BOOL bRet = FALSE;
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		if (it->second.bPlay)
			bRet = it->second.pPlayer->IsPaused();
	}
	m_locker.Unlock();
	return bRet;
}

void PlManager::AspectRatio(HWND hWnd, int width,int height)
{
	m_locker.Lock();
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		if (it->second.bPlay)
			it->second.pPlayer->AspectRatio(width,height);
	}
	m_locker.Unlock();
}

void PlManager::SleepPlayer(HWND hWnd, bool bSleep)
{
	m_locker.Lock();
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		if (it->second.bPlay)
			it->second.pPlayer->SleepPlayer(bSleep);
	}
	m_locker.Unlock();
}