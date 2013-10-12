#include "PlayManager.h"
#include "x_adapter_factory.h"
#include "RealPlayObj.h"
#include "VodPlayObj.h"

JO_IMPLEMENT_SINGLETON(PlayManager)

static char *get_string(char *src, char *xxx,char **dst)
{
	char *p = src;
	char *p2 = strstr(p, xxx);
	if (p2 != NULL)
	{
		int index = p2 - p;
		*dst = (j_char_t *)malloc(index + 10);
		memset(*dst, 0, index + 1);
		memcpy(*dst, p, index);
		//(*dst)[index] = '\0';
		return p2 + strlen(xxx);
	}
	return NULL;
}

static char *get_int(char *src, char *xxx,int *dst)
{
	char *p = src;
	char *p2 = strstr(p, xxx);
	if (p2 != NULL)
	{
		*dst = atoi(p);
		return p2 + strlen(xxx);
	}
	return NULL;
}

CPlayManager::CPlayManager()
{
	m_bStart = false;
	m_nStreamId = 1;
	m_nDevId = 0;
}

CPlayManager::~CPlayManager()
{

}

j_result_t CPlayManager::Init()
{
	/*if (m_loadSo.JoLoadSo() != J_OK)
	{
		J_OS::LOGINFO("CPlayManager::Init loadSo JoLoadSo error");
		return J_UNKNOW;
	}*/
	m_bStart = true;
	j_thread_parm parm = {0};
	parm.entry = CPlayManager::WorkThread;
	parm.data = this;
	m_thread.Create(parm);

	return J_OK;
}

void CPlayManager::Deinit()
{
	m_bStart = false;
	//m_loadSo.JoUnloadSo();
}

j_int32_t CPlayManager::OpenStream(const j_char_t *pUrl, const j_char_t *pUrl2)
{
	J_PlayManagerInfo info;
	InitPlayManagerInfo(info);
	ParserUrl(pUrl, pUrl2, info);
	TLock(m_adapterLocker);
	AdapterMap::iterator itAdapter = m_adapterMap.find(info.dev_id);
	if (itAdapter == m_adapterMap.end())
	{
		GetAdapterFactoryLayer()->MakeAdapterDev(info.host_type, info.dev_id, info.host_addr, info.host_port, info.user_name, info.pass_word);
		m_adapterMap[info.dev_id] = 0;
	}
	TUnlock(m_adapterLocker);

	TLock(m_streamLocker);
	J_PlayStreamInfo streamInfo = {0};
	streamInfo.pPlayObj = new CRealPlayObj(m_nStreamId, info.player_type, info.stream_type, info.resid);
	streamInfo.pPlayObj->PlayMedia(info.play_wnd, info.dev_id);
	streamInfo.nDevid = info.dev_id;
	streamInfo.bStart = true;
	m_streamMap[m_nStreamId] = streamInfo;
	TUnlock(m_streamLocker);
	FreePlayManagerInfo(info);

	return m_nStreamId++;
}

void CPlayManager::CloseStream(j_int32_t streamHandle)
{
	TLock(m_streamLocker);
	StreamMap::iterator itStream = m_streamMap.find(streamHandle);
	if (itStream!=m_streamMap.end())
	{
		if (itStream->second.bStart)
		{
			itStream->second.pPlayObj->StopMedia(itStream->second.nDevid);
			delete itStream->second.pPlayObj;
			itStream->second.pPlayObj = NULL;
			itStream->second.bStart = false;
		}
		m_streamMap.erase(itStream);
	}
	TUnlock(m_streamLocker);
}

j_int32_t CPlayManager::OpenVod(const j_char_t *pUrl, const j_char_t *pUrl2)
{
	J_PlayManagerInfo info;
	InitPlayManagerInfo(info);
	ParserUrl2(pUrl, pUrl2, info);

	TLock(m_streamLocker);
	J_PlayStreamInfo streamInfo = {0};
	streamInfo.pPlayObj = new CVodPlayObj(m_nStreamId, info.player_type, info.host_type, info.resid);
	streamInfo.pPlayObj->PlayVod(info.play_wnd, info.start_time, info.end_time);
	streamInfo.nDevid = info.dev_id;
	streamInfo.bStart = true;
	m_streamMap[m_nStreamId] = streamInfo;
	TUnlock(m_streamLocker);
	FreePlayManagerInfo(info);

	return m_nStreamId++;
}

void CPlayManager::CloseVod(j_int32_t streamHandle)
{
	TLock(m_streamLocker);
	StreamMap::iterator itStream = m_streamMap.find(streamHandle);
	if (itStream!=m_streamMap.end())
	{
		if (itStream->second.bStart)
		{
			itStream->second.pPlayObj->StopVod();
			delete itStream->second.pPlayObj;
			itStream->second.pPlayObj = NULL;
			itStream->second.bStart = false;
		}
		m_streamMap.erase(itStream);
	}
	TUnlock(m_streamLocker);
}

void CPlayManager::InitPlayManagerInfo(J_PlayManagerInfo &info)
{
	memset(&info, 0, sizeof(J_PlayManagerInfo));
}

void CPlayManager::FreePlayManagerInfo(J_PlayManagerInfo &info)
{
	if (info.host_type != NULL)
		free(info.host_type);
	if (info.host_addr != NULL)
		free(info.host_addr);
	if (info.resid != NULL)
		free(info.resid);
	if (info.user_name != NULL)
		free(info.user_name);
	if (info.pass_word != NULL)
		free(info.pass_word);
	if (info.player_type != NULL)
		free(info.player_type);
	//if (info.dev_id != NULL)
	//	free(info.dev_id);
	memset(&info, 0, sizeof(J_PlayManagerInfo));
}

j_boolean_t CPlayManager::ParserUrl(const j_char_t *pUrl, const j_char_t *pUrl2, J_PlayManagerInfo &info)
{
	char *p = (char *)pUrl;
	if ((p = get_string(p, (char *)"://", &info.host_type)) == NULL)
		goto parser_usr_error;
	if ((p = get_string(p, (char *)":", &info.host_addr)) == NULL)
		goto parser_usr_error;
	if ((p = get_int(p, (char *)"?resid=", (int *)&info.host_port)) == NULL)
		goto parser_usr_error;
	if ((p = get_string(p, (char *)"&username=", &info.resid)) == NULL)
		goto parser_usr_error;
	if ((p = get_string(p, (char *)"&passwd=", &info.user_name)) == NULL)
		goto parser_usr_error;
	if ((p = get_string(p, (char *)"&stream_type=", &info.pass_word)) == NULL)
		goto parser_usr_error;
	if ((p = get_int(p, (char *)"\0", (int *)&info.stream_type)) == NULL)
		goto parser_usr_error;

	p = (char *)pUrl2;
	if ((p = get_string(p, (char *)"://", &info.player_type)) == NULL)
		goto parser_usr_error;
	if ((p = get_int(p, (char *)"\0", (int *)&info.play_wnd)) == NULL)
		goto parser_usr_error;

	info.dev_id = m_nDevId++;

	return true;

parser_usr_error:
	FreePlayManagerInfo(info);
	return false;
}

j_boolean_t CPlayManager::ParserUrl2(const j_char_t *pUrl, const j_char_t *pUrl2, J_PlayManagerInfo &info)
{
	char *p = (char *)pUrl;
	if ((p = get_string(p, (char *)"://", &info.host_type)) == NULL)
		goto parser_usr_error;
	if ((p = get_string(p, (char *)":", &info.host_addr)) == NULL)
		goto parser_usr_error;
	if ((p = get_int(p, (char *)"?resid=", (int *)&info.host_port)) == NULL)
		goto parser_usr_error;
	if ((p = get_string(p, (char *)"&username=", &info.resid)) == NULL)
		goto parser_usr_error;
	if ((p = get_string(p, (char *)"&passwd=", &info.user_name)) == NULL)
		goto parser_usr_error;
	if ((p = get_string(p, (char *)"&start=", &info.pass_word)) == NULL)
		goto parser_usr_error;
	if ((p = get_int(p, (char *)"&end=", (int *)&info.start_time)) == NULL)
		goto parser_usr_error;
	if ((p = get_int(p, (char *)"\0", (int *)&info.end_time)) == NULL)
		goto parser_usr_error;

	p = (char *)pUrl2;
	if ((p = get_string(p, (char *)"://", &info.player_type)) == NULL)
		goto parser_usr_error;
	if ((p = get_int(p, (char *)"\0", (int *)&info.play_wnd)) == NULL)
		goto parser_usr_error;

	info.dev_id = m_nDevId++;

	return true;

parser_usr_error:
	FreePlayManagerInfo(info);
	return false;
}

void CPlayManager::OnWork()
{
	StreamMap::iterator it;
	while (m_bStart)
	{
		TLock(m_streamLocker);
		if (m_streamMap.empty())
		{
			j_sleep(10);
		}
		it = m_streamMap.begin();
		for (;it != m_streamMap.end(); it++)
		{
			if (it->second.bStart && it->second.pPlayObj->ProcessMedia() != J_OK)
			{
				//¶ÏÏßÖØÁ¬´¦Àí
				it->second.pPlayObj->StopMedia(it->second.nDevid);
			}
		}
		TUnlock(m_streamLocker);
	}
}