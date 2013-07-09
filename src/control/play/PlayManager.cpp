#include "PlayManager.h"
#include "x_adapter_factory.h"
#include "RealPlayObj.h"

JO_IMPLEMENT_SINGLETON(PlayManager)

static char *get_string(char *src, char *xxx,char **dst)
{
	char *p = src;
	char *p2 = strstr(p, xxx);
	if (p2 != NULL)
	{
		*dst = (j_char_t *)malloc(p2 - p + 1);
		memcpy(*dst, p, p2-p);
		*dst[p2 - p] = '\0';
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
	m_nDevId = 0;
	m_bStart = false;
	for (int i=0; i<100; i++)
	{
		J_PlayStreamInfo info = {0};
		m_streamMap[i] = info;
	}
}

CPlayManager::~CPlayManager()
{

}

j_result_t CPlayManager::Init()
{
	if (m_loadSo.JoLoadSo() != J_OK)
	{
		J_OS::LOGINFO("CPlayManager::Init loadSo JoLoadSo error");
		return J_UNKNOW;
	}
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
	m_loadSo.JoUnloadSo();
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
		GetAdapterFactoryLayer()->MakeAdapterDev(info.host_type, ++m_nDevId, info.host_addr, info.host_port, info.user_name, info.pass_word);
		m_adapterMap[info.dev_id] = m_nDevId;
	}
	TUnlock(m_adapterLocker);

	j_int32_t nStreamId = 0;
	TLock(m_streamLocker);
	StreamMap::iterator itStream = m_streamMap.begin();
	for (; itStream!=m_streamMap.end(); ++itStream)
	{
		if (!itStream->second.bStart)
		{
			nStreamId = itStream->first;
			itStream->second.pPlayObj = new CRealPlayObj(nStreamId, info.player_type, info.stream_type, info.resid);
			itStream->second.bStart = true;
			break;
		}
	}
	TUnlock(m_streamLocker);
	itStream->second.pPlayObj->PlayMedia(info.play_wnd);

	return nStreamId;
}

void CPlayManager::CloseStream(j_int32_t streamHandle)
{
	TLock(m_streamLocker);
	StreamMap::iterator itStream = m_streamMap.find(streamHandle);
	if (itStream!=m_streamMap.end())
	{
		if (itStream->second.bStart)
		{
			itStream->second.pPlayObj->StopMedia();
			delete itStream->second.pPlayObj;
			itStream->second.pPlayObj = NULL;
			itStream->second.bStart = false;
		}
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
	if (info.dev_id != NULL)
		free(info.dev_id);
	memset(&info, 0, sizeof(J_PlayManagerInfo));
}

j_boolean_t CPlayManager::ParserUrl(const j_char_t *pUrl, const j_char_t *pUrl2, J_PlayManagerInfo &info)
{
	char *p = (char *)pUrl;
	if ((p = get_string(p, "://", &info.host_type)) == NULL)
		goto parser_usr_error;
	if ((p = get_string(p, ":", &info.host_addr)) == NULL)
		goto parser_usr_error;
	if ((p = get_int(p, "?resid=", (int *)&info.host_port)) == NULL)
		goto parser_usr_error;
	if ((p = get_string(p, "&username=", &info.resid)) == NULL)
		goto parser_usr_error;
	if ((p = get_string(p, "&passwd=", &info.user_name)) == NULL)
		goto parser_usr_error;
	if ((p = get_string(p, "&stream_type", &info.pass_word)) == NULL)
		goto parser_usr_error;
	if ((p = get_int(p, "\0", (int *)&info.stream_type)) == NULL)
		goto parser_usr_error;

	p = (char *)pUrl2;
	if ((p = get_string(p, "://", &info.player_type)) == NULL)
		goto parser_usr_error;
	if ((p = get_int(p, "\0", (int *)&info.play_wnd)) == NULL)
		goto parser_usr_error;

	if (info.dev_id == NULL)
	{
		info.dev_id = (j_char_t *)malloc(strlen(info.host_type) + strlen(info.host_addr) + 2);
		sprintf(info.dev_id, "%s_%s", info.host_type, info.host_addr);
		info.dev_id[strlen(info.host_type) + strlen(info.host_addr) + 2] = '\0';
	}

parser_usr_error:
	FreePlayManagerInfo(info);
	return false;
}

void CPlayManager::OnWork()
{
	StreamMap::iterator it;
	while (m_bStart)
	{
		j_sleep(10);
		TLock(m_streamLocker);
		if (m_streamMap.empty())
		{
			j_sleep(10);
		}
		it = m_streamMap.begin();
		for (;it != m_streamMap.end(); it++)
		{
			if (it->second.pPlayObj->ProcessMedia() != J_OK)
			{
				//断线重连处理
				it->second.pPlayObj->StopMedia();
			}
		}
		TUnlock(m_streamLocker);
	}
}