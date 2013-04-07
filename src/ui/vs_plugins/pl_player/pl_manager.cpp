#include "StdAfx.h"
#include "pl_manager.h"
#include "pl_factory.h"
#include "WaitStatus.h"
#include "runner_log.h"

/*********************static 初始化***********************/
WorkModel PlManager::m_playMode = REALMODEL;
CALLBACK_onEvent PlManager::m_pFuncCallBk = NULL;
int PlManager::m_nPlayerNum = 0;
/*******************类实现*****************************/
PlManager::PlManager(enum WorkModel playModel)
{
	m_pPlayer		= NULL;
	m_playMode		= playModel;
	m_jsPlayInfo	= NULL;
	m_nLastTime		= 0;
	m_waitStatus	= NULL;
	m_videoType		= VLC_VIDEO;
	m_nVodEndTime	= 0;
	m_pUser			= NULL;
	
}

PlManager::~PlManager(void)
{
	Stop();
	if(NULL != m_waitStatus)
	{
		delete (CWaitStatus*)m_waitStatus;
		m_waitStatus = NULL;
	}
}


BOOL PlManager::Play(HWND hwnd,char *js_playInfo)
{
	BOOL bRet;
	if(NULL != m_pPlayer)
	{
		m_pPlayer->Stop();
		delete m_pPlayer;
		m_pPlayer = NULL;
	}
#ifndef APACHE_TEST
	json_object *js_obj = json_tokener_parse(js_playInfo);
	if(is_error(js_obj))
	{
		return FALSE;
	}
	if(m_jsPlayInfo != NULL)
	{
		delete m_jsPlayInfo;
	}
	int len = strlen(js_playInfo);
	m_jsPlayInfo = new char[len+1];
	strcpy(m_jsPlayInfo,js_playInfo);
	m_jsPlayInfo[len] = '\0';
	m_nLastTime = 0;		////防止时间调跳动
#endif
	m_videoType = GetVideoType();
	switch(m_videoType)
	{
	case HIK_VIDEO:
		if(m_playMode == REALMODEL)
			m_pPlayer = CPlFactory::Instance()->GetPlayer("pl_hik", STREAME_REALTIME, this);
		else
			m_pPlayer = CPlFactory::Instance()->GetPlayer("pl_hik", STREAME_FILE, this);
	
		break;

	case VLC_VIDEO:
		if(m_playMode == REALMODEL)
			m_pPlayer = CPlFactory::Instance()->GetPlayer("pl_jo", STREAME_REALTIME, this);
		else
			m_pPlayer = CPlFactory::Instance()->GetPlayer("pl_vlc", STREAME_FILE, this);
		break;

	default:
		return FALSE;
	}

	if(m_pPlayer)
	{
#ifndef APACHE_TEST
		char mrl[512] = {0};
		CreateMrl(mrl);
		if((bRet = m_pPlayer->Play(hwnd,mrl)))
			m_nPlayerNum++;
		if(m_playMode == REALMODEL)
		{
			if(!m_waitStatus)
			{
				m_waitStatus = new CWaitStatus(CWnd::FromHandle(::GetParent(hwnd)));
			}
		}
#else 
		bRet = m_pPlayer->Play(hwnd,js_playInfo);
#endif
	}
	return bRet;
}

int PlManager::GetVideoType()
{

	return VLC_VIDEO;
}

void PlManager::CreateMrl(char *OUT_playInfo)
{
	if(m_videoType == VLC_VIDEO)
		sprintf(OUT_playInfo,"http://");
	else
		sprintf(OUT_playInfo,CUSTOM_PROTOCOL);
	char tmpInfo[128];
	json_object *js_obj = json_tokener_parse(m_jsPlayInfo);
	if(is_error(js_obj))
	{
		return ;
	}
	if(REALMODEL == m_playMode)
	{
		sprintf(tmpInfo,"%s:%d/real?resid=%s&cmd=%d&type=%d",
			json_object_get_string(json_object_object_get(js_obj,"ip")),
			json_object_get_int(json_object_object_get(js_obj,"port")),
			json_object_get_string(json_object_object_get(js_obj,"resid")),
			1,
			json_object_get_int(json_object_object_get(js_obj,"ms"))
			);
	}
	else if(VODMODEL == m_playMode)
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
	strcat(OUT_playInfo,tmpInfo);
	json_object_put(js_obj);
}

BOOL PlManager::Capture(char *path)
{
	if(m_pPlayer == NULL)
		return FALSE;

	time_t t_locatime = time(NULL);
	tm *tm_locatime; 
	tm_locatime=localtime(&t_locatime);
	char locatime[256]	= {0};
	char path_name[512] = {0};
	sprintf(locatime,"\\RonYaoCapture-%d-%d-%d-%d-%d-%d.png",
		tm_locatime->tm_year+1990,
		tm_locatime->tm_mon+1,
		tm_locatime->tm_mday,
		tm_locatime->tm_hour,
		tm_locatime->tm_min,
		tm_locatime->tm_sec);
	strcat(path_name,path);
	strcat(path_name,locatime);

	return m_pPlayer->Capture(path_name);
}

BOOL PlManager::SetSpeed(BOOL bSpeedUp)
{
	if(m_pPlayer == NULL)
		return FALSE;
	return m_pPlayer->SetSpeed(bSpeedUp);
}

BOOL PlManager::Record(char *path)
{
	if(m_pPlayer == NULL)
		return FALSE;
	return m_pPlayer->Record(path);
}


void PlManager::Stop()
{
	if(m_pPlayer == NULL)
		return;
	SendMessage(GetPlayHwnd(),WM_OWN_ERASEBKGROUND,TRUE,0);
	m_pPlayer->Stop();

	m_videoType = VLC_VIDEO;
	m_nPlayerNum--;
	m_nVodEndTime = 0;
	if(m_nPlayerNum == 0)
	{
		int args[2];
		args[0] = 1;
		args[1] = (int)"null";

		onCallBack(CALLBACK_ONSTATE,args,sizeof(args)/sizeof(int));
	}
	delete m_pPlayer;
	m_pPlayer = NULL;
	if(m_jsPlayInfo)
	{
		delete m_jsPlayInfo;
		m_jsPlayInfo = NULL;
	}
}

void PlManager::Pause()
{
	if(m_pPlayer == NULL)
		return;
	return m_pPlayer->Pause();
}

void PlManager::PlayOneByOne()
{
	if(m_pPlayer == NULL)
		return;
	return m_pPlayer->PlayOneByOne();
}

int PlManager::GetVolume()
{
	if(m_pPlayer == NULL)
		return -1;
	return m_pPlayer->GetVolume();
}

BOOL PlManager::SetVolume(int nVolume)
{
	if(m_pPlayer == NULL)
		return FALSE;
	return m_pPlayer->SetVolume(nVolume);
}

BOOL PlManager::IsPlaying()
{
	if(m_pPlayer == NULL)
		return FALSE;
	return m_pPlayer->IsPlaying();
}

char *PlManager::GetJSInfo() const
{
	return m_jsPlayInfo;
}

void PlManager::VodCallBack()
{
	if(m_pPlayer == NULL)
		return;
	int args[1];
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
		return;
}

HWND PlManager::GetPlayHwnd()
{
	if(m_pPlayer == NULL)
		return NULL;
	return m_pPlayer->GetPlayHwnd();
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



BOOL PlManager::GetWndPlayParm(char *OUT_playerParm)
{
	json_object *resid = NULL;
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
	json_object_put(js_obj);

	return TRUE;
}

BOOL PlManager::VodStreamJump(char *js_time)
{
	if(m_pPlayer == NULL)
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
	return m_pPlayer->VodStreamJump(mrl);
}

void PlManager::Play()
{
	if(m_pPlayer == NULL)
		return;
	return m_pPlayer->Play();
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

BOOL PlManager::SetUserData(void *pUser)
{
	if(pUser)
	{
		m_pUser = pUser;
		return TRUE;
	}
	return FALSE;
}

BOOL PlManager::SetOsdText(int stime,char *osdtext)
{
	if(m_pPlayer == NULL)
		return FALSE;
	return m_pPlayer->SetOSDText(stime,osdtext);
}

BOOL PlManager::IsPaused()
{
	if(m_pPlayer == NULL)
		return FALSE;
	return m_pPlayer->IsPaused();
}

void PlManager::AspectRatio(int width,int height)
{
	if(m_pPlayer == NULL)
		return;
	m_pPlayer->AspectRatio(width,height);
}

void PlManager::SleepPlayer(bool bSleep)
{
	if(m_pPlayer == NULL)
		return;
	m_pPlayer->SleepPlayer(bSleep);
}