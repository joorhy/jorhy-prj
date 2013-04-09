#include "StdAfx.h"
#include "pl_manager.h"
#include "pl_factory.h"
#include "pl_reconn.h"
#include "runner_log.h"

/*********************static 初始化***********************/
CALLBACK_onEvent PlManager::m_pFuncCallBk = NULL;
int PlManager::m_nPlayerNum = 0;
/*******************类实现*****************************/
PlManager::PlManager()
{
	m_nLastTime		= 0;
	m_waitStatus	= NULL;
	m_videoType		= VLC_VIDEO;
	m_nVodEndTime	= 0;
	m_pUser			= NULL;
}

PlManager::~PlManager(void)
{
	if(NULL != m_waitStatus)
	{
		delete (CWaitStatus*)m_waitStatus;
		m_waitStatus = NULL;
	}
}

BOOL PlManager::Play(HWND hWnd, char *pJsUrl, int nPlayMode, int nSteamType)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		Stop(it->first);
		m_playerMap.erase(it);
	}

	BOOL bRet;
	json_object *js_obj = json_tokener_parse(pJsUrl);
	if(is_error(js_obj))
		return FALSE;

	PL_PlayerInfo info = {0};
	info.hWnd = hWnd;
	info.nType = nPlayMode;
	CreateMrl(nPlayMode, nSteamType, pJsUrl, info.pUrl);
	switch(nSteamType)
	{
	case HIK_VIDEO:
		info.pPlayer = CPlFactory::Instance()->GetPlayer("pl_hik", nPlayMode, this, hWnd);
		break;
	case VLC_VIDEO:
		info.pPlayer = CPlFactory::Instance()->GetPlayer("pl_jo", nPlayMode, this, hWnd);
		break;
	default:
		return FALSE;
	}

	if(info.pPlayer)
	{
		if((bRet = info.pPlayer->Play(hWnd, info.pUrl)))
			m_nPlayerNum++;
		if(info.nType == STREAME_REALTIME)
		{
			if(!m_waitStatus)
			{
				m_waitStatus = new CWaitStatus(CWnd::FromHandle(::GetParent(hWnd)));
			}
		}
	}
	m_playerMap[hWnd] = info;

	return bRet;
}

void PlManager::CreateMrl(int nPlayMode, int nSteamType,  char *pJsUrl, char *pUrl)
{
	if(nSteamType == VLC_VIDEO)
		sprintf(pUrl,"http://");
	else
		sprintf(pUrl,CUSTOM_PROTOCOL);
	char tmpInfo[128];
	json_object *js_obj = json_tokener_parse(pJsUrl);
	if(is_error(js_obj))
		return ;
	
	if(STREAME_REALTIME == nPlayMode)
	{
		sprintf(tmpInfo,"%s:%d/real?resid=%s&cmd=%d&type=%d",
			json_object_get_string(json_object_object_get(js_obj,"ip")),
			json_object_get_int(json_object_object_get(js_obj,"port")),
			json_object_get_string(json_object_object_get(js_obj,"resid")),
			1,
			json_object_get_int(json_object_object_get(js_obj,"ms"))
			);
	}
	else if(STREAME_FILE == nPlayMode)
	{
		m_nVodEndTime = json_object_get_int(json_object_object_get(js_obj,"end"));
		sprintf(tmpInfo,"%s:%d/vodl?resid=%s&cmd=%d&start=%d&end=%d",
			json_object_get_string(json_object_object_get(js_obj,"ip")),
			json_object_get_int(json_object_object_get(js_obj,"port")),
			json_object_get_string(json_object_object_get(js_obj,"resid")),
			3,
			json_object_get_int(json_object_object_get(js_obj,"start")),
			json_object_get_int(json_object_object_get(js_obj,"end"))
			);
	}
	strcat(pUrl, tmpInfo);
	json_object_put(js_obj);
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
	if (it != m_playerMap.end())
	{
		SendMessage(hWnd, WM_OWN_ERASEBKGROUND,TRUE,0);
		it->second.pPlayer->Stop();

		m_nPlayerNum--;
		m_nVodEndTime = 0;
		if(m_nPlayerNum == 0)
		{
			int args[2];
			args[0] = 1;
			args[1] = (int)"null";

			onCallBack(CALLBACK_ONSTATE, args, sizeof(args)/sizeof(int));
		}
		CPlFactory::Instance()->DelPlayer(m_hPlayWnd);
		m_playerMap.erase(it);
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
	if (it != m_playerMap.end())
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
		/*int args[1];
		int64_t startTime = 0;
		if(m_jsPlayInfo)
		{
			json_object *js_obj = json_tokener_parse(m_jsPlayInfo);
			if(is_error(js_obj))
			{
				return ;
			}
			json_object *tmp = json_object_object_get(js_obj,"start");
			if(!is_error(tmp))
			{
				startTime = json_object_get_int(tmp);
				startTime += m_nLastTime;
				if(startTime > m_nVodEndTime)
				{
					PostMessage(GetPlayHwnd(),WM_MEDIA_END_REACHED,0,0);
					return;
				}
				args[0] = (int)&startTime;
				onCallBack(CALLBACK_ONVOD,args,sizeof(args)/sizeof(int));
				m_nLastTime++;
			}
			else
				return;
			json_object_put(js_obj);
		}
		else
			return;*/
	}
	return;
}

BOOL PlManager::RegisterCallBack(CALLBACK_onEvent funcAddr)
{
	if(NULL == funcAddr)
		return FALSE;
	else
		m_pFuncCallBk = funcAddr;
	return TRUE;
}

void PlManager::onCallBack(unsigned int nType,int args[],unsigned int argCount)
{
	if(NULL == m_pFuncCallBk || NULL == m_pUser) 
		return;
	else
		m_pFuncCallBk(m_pUser,nType,args,argCount);
}

BOOL PlManager::GetWndPlayParm(HWND hWnd, char *OUT_playerParm)
{
	/*json_object *resid = NULL;
	json_object *ms	= NULL;
	json_object *retInfo = NULL;
	json_object *id = NULL;

	if(m_jsPlayInfo == NULL || m_pPlayer == NULL)
	{
		return TRUE;
	}
	json_object *js_obj = json_tokener_parse(m_jsPlayInfo);
	if(is_error(js_obj))
	{
		return FALSE;
	}
	resid = json_object_object_get(js_obj,"resid");
	ms = json_object_object_get(js_obj,"ms");
	if(is_error(ms))
	{
		ms = json_object_new_int(-1);
	}
	id = json_object_new_int(GetWindowLong(m_pPlayer->GetPlayHwnd(),GWL_ID));
	retInfo = json_object_new_object();

	json_object_object_add(retInfo,"id",id);
	json_object_object_add(retInfo,"resid",json_object_new_string(json_object_get_string(resid)));
	json_object_object_add(retInfo,"ms",json_object_new_string(json_object_get_string(ms)));

	sprintf(OUT_playerParm,"%s",json_object_to_json_string(retInfo));

	json_object_put(id);
	json_object_put(retInfo);
	json_object_put(js_obj);*/

	return TRUE;
}

BOOL PlManager::VodStreamJump(HWND hWnd, char *js_time)
{
	/*if(m_pPlayer == NULL)
		return FALSE;
	if(!m_pPlayer->IsPlaying())
	{
		return TRUE;
	}
	m_nLastTime = 0;		//防止时间调跳动
	BOOL bRet = FALSE;
	char mrl[512] = {0};
	json_object *tmp = json_tokener_parse(js_time);
	json_object *newTime = NULL;
	if(is_error(tmp))
	{
		return FALSE;
	}
	newTime = json_object_object_get(tmp,"stime");
	int time = json_object_get_int(newTime);
	if(time > m_nVodEndTime)		//超出结束时间就停止
	{
		PostMessage(GetPlayHwnd(),WM_MEDIA_END_REACHED,0,0);
		return FALSE;
	}
	json_object *js_obj = json_tokener_parse(m_jsPlayInfo);
	if(is_error(js_obj))
	{
		return FALSE;
	}
	json_object_object_add(js_obj,"start",json_object_new_int(time));
	delete m_jsPlayInfo;
	char *js_str = json_object_to_json_string(js_obj);
	int len = strlen(js_str);
	m_jsPlayInfo = new char[len + 1];
	strcpy(m_jsPlayInfo,js_str);
	m_jsPlayInfo[len] = '\0';

	CreateMrl(mrl);
	return m_pPlayer->VodStreamJump(mrl);*/
	return TRUE;
}

void PlManager::Play()
{
	/*if(m_pPlayer == NULL)
		return;
	return m_pPlayer->Play();*/
}


void *PlManager::GetRecntWnd() const
{
	return m_waitStatus;
}

void PlManager::StatusCallBack(HWND hPlayWnd)
{
	int args[2];
	int idWnd = 0;
	json_object *j_obj = json_object_new_object();

	args[0] = 3;
	idWnd = GetWindowLong(hPlayWnd,GWL_ID);
	json_object_object_add(j_obj,"id",json_object_new_int(idWnd));
	json_object_object_add(j_obj,"state",json_object_new_int(1));
	args[1] = (int)json_object_to_json_string(j_obj);

	onCallBack(CALLBACK_ONSTATE,args,sizeof(args)/sizeof(int));

	json_object_put(j_obj);
}

BOOL PlManager::SetUserData(HWND hWnd, void *pUser)
{
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		it->second.pUser = pUser;
	}
	return FALSE;
}

BOOL PlManager::SetOsdText(int stime,char *osdtext)
{
	/*if(m_pPlayer == NULL)
		return FALSE;
	return m_pPlayer->SetOSDText(stime,osdtext);*/
	return FALSE;
}

BOOL PlManager::IsPaused()
{
	/*if(m_pPlayer == NULL)
		return FALSE;
	return m_pPlayer->IsPaused();*/
	return FALSE;
}

void PlManager::AspectRatio(int width,int height)
{
	/*if(m_pPlayer == NULL)
		return;
	m_pPlayer->AspectRatio(width,height);*/
}

void PlManager::SleepPlayer(bool bSleep)
{
	/*if(m_pPlayer == NULL)
		return;
	m_pPlayer->SleepPlayer(bSleep);*/
}