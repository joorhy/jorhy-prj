#include "x_adapter_manager.h"

JO_IMPLEMENT_SINGLETON(AdapterManager)

CAdapterManager::CAdapterManager()
{

}

CAdapterManager::~CAdapterManager()
{

}

int CAdapterManager::StartVideo(const char *pResId, int nStreamType, const j_socket_t nSocket, j_int32_t nDevid)
{
	J_ChannelStream *pChannelStream = dynamic_cast<J_ChannelStream *>(JoAdapterFactory->FatchChannel(pResId, nStreamType, nDevid));
	if (pChannelStream == NULL)
	{
		J_OS::LOGINFO("CAdapterManager::StartVideo channel not exist, resid = %s", pResId);
		return J_NOT_EXIST;
	}

	CRingBuffer *pRingBuff = NULL;
	GetRingBuffer(pResId, nStreamType, nSocket, pRingBuff);

	int nRet = J_OK;
	J_ChannelKey key;
	key.resid = pResId;
	key.stream_type = nStreamType;
	StreamMap::iterator it = m_streamMap.find(key);
	if (it == m_streamMap.end() || it->second.videoStream == NULL)
	{
		J_Obj *pObjStream = NULL;
		nRet = pChannelStream->OpenStream(pObjStream, pRingBuff);
		if (nRet == J_OK)
		{
		    m_streamMap[key].videoStream = pObjStream;
		    if (!pChannelStream->HasMultiStream())
		    {
		        key.stream_type = nStreamType == 0 ? 1 : 0;
                m_streamMap[key].videoStream = pObjStream;
		    }
		}
	}
	else
	{
		nRet = pChannelStream->OpenStream(it->second.videoStream, pRingBuff);
	}

	//(static_cast<J_VideoStream *>(m_streamMap[pResId]))->Startup();

	return nRet;
}

int CAdapterManager::StopVideo(const char *pResId, int nStreamType, const j_socket_t nSocket, j_int32_t nDevid)
{
    J_ChannelKey key;
	key.resid = pResId;
	key.stream_type = nStreamType;
	StreamMap::iterator it = m_streamMap.find(key);
	if (it == m_streamMap.end())
		return J_NOT_EXIST;

	RingBufferMap::iterator it2 = it->second.ringBufferMap.find(nSocket);
	if (it2 == it->second.ringBufferMap.end())
		return J_NOT_EXIST;

	J_Obj *pObj = JoAdapterFactory->FatchChannel(pResId, nStreamType, nDevid);
	if (pObj != NULL)
	{
		J_ChannelStream *pChannelStream = dynamic_cast<J_ChannelStream *>(pObj);
		if (pChannelStream != NULL)
		{
			if (pChannelStream->CloseStream(it->second.videoStream, it2->second) == J_NO_REF)
			{
				DelRingBuffer(pResId, nStreamType, nSocket);
				if (!pChannelStream->HasMultiStream())
				{
					DelRingBuffer(pResId, nStreamType == 0 ? 1 : 0, nSocket);
					JoAdapterFactory->ReleaseChannel(pResId, nStreamType == 0 ? 1 : 0);
				}
				JoAdapterFactory->ReleaseChannel(pResId, nStreamType);
			}
		}
	}

	return J_OK;
}

int CAdapterManager::StartVoice(const char *pResId, const j_socket_t nSocket, j_int32_t nDevid)
{
    int nStreamType = 0;
	J_ChannelStream *pChannelStream = dynamic_cast<J_ChannelStream *>(JoAdapterFactory->FatchChannel(pResId, nStreamType, nDevid));
	if (pChannelStream == NULL)
	{
		J_OS::LOGINFO("CAdapterManager::StartVoice channel not exist, resid = %s", pResId);
		return J_NOT_EXIST;
	}

	CRingBuffer *pRingBuff = NULL;
	GetRingBuffer(pResId, 0, nSocket, pRingBuff);

	int nRet = J_OK;
    J_ChannelKey key;
	key.resid = pResId;
	key.stream_type = 0;
	StreamMap::iterator it = m_streamMap.find(key);
	if (it == m_streamMap.end() || it->second.videoStream == NULL)
	{
		J_Obj *pObjStream = NULL;
		nRet = pChannelStream->OpenStream(pObjStream, pRingBuff);
		if (nRet == J_OK)
			m_streamMap[key].videoStream = pObjStream;
	}
	else
	{
		nRet = pChannelStream->OpenStream(it->second.videoStream, pRingBuff);
	}

	return nRet;
}

int CAdapterManager::StopVoice(const char *pResId, const j_socket_t nSocket, j_int32_t nDevid)
{
    J_ChannelKey key;
	key.resid = pResId;
	key.stream_type = 0;
	StreamMap::iterator it = m_streamMap.find(key);
	if (it == m_streamMap.end())
		return J_NOT_EXIST;

	RingBufferMap::iterator it2 = it->second.ringBufferMap.find(nSocket);
	if (it2 == it->second.ringBufferMap.end())
		return J_NOT_EXIST;

	J_ChannelStream *pVoiceChannel = dynamic_cast<J_ChannelStream *>(JoAdapterFactory->FatchChannel(pResId, key.stream_type, nDevid));
	if (pVoiceChannel->CloseStream(it->second.videoStream, it2->second) == J_NO_REF)
	{
		m_streamMap.erase(it);
	}
	DelRingBuffer(pResId, 0, nSocket);

	return J_OK;
}

int CAdapterManager::GetParser(const char *pResId, J_StreamParser *&pObj, j_int32_t nDevid)
{
    int nStreamType = 0;
	J_StreamParser *pVideoParser = dynamic_cast<J_StreamParser *>(JoAdapterFactory->FatchChannel(pResId, nStreamType, nDevid));
	if (pVideoParser == NULL)
	{
		J_OS::LOGINFO("CAdapterManager::StartRecord channel not exist, resid = %s", pResId);
		return J_NOT_EXIST;
	}

	std::map<j_string_t, J_Obj *>::iterator it = m_parserMap.find(pResId);
	if (it == m_parserMap.end())
	{
		J_Obj *pParser = NULL;
		pVideoParser->OpenParser(pParser);
		m_parserMap[pResId] = pParser;
	}
	pObj = dynamic_cast<J_StreamParser *>(m_parserMap[pResId]);

	return J_OK;
}

int CAdapterManager::DelParser(const char *pResId, j_int32_t nDevid)
{
    int nStreamType = 0;
	J_StreamParser *pVideoParser = dynamic_cast<J_StreamParser *>(JoAdapterFactory->FatchChannel(pResId, nStreamType, nDevid));
	if (pVideoParser == NULL)
	{
		J_OS::LOGINFO("CAdapterManager::StopRecord channel not exist, resid = %s", pResId);
		return J_NOT_EXIST;
	}

	std::map<j_string_t, J_Obj *>::iterator it = m_parserMap.find(pResId);
	if (it == m_parserMap.end())
	{
		J_OS::LOGINFO("CAdapterManager::StopRecord parser not exist, resid = %s", pResId);
		return J_NOT_EXIST;
	}
	pVideoParser->CloseParser(it->second);
	m_parserMap.erase(it);

	return J_OK;
}

int CAdapterManager::FindVodFile(const char *pResid, time_t beginTime, time_t endTime, std::vector<J_FileInfo> &fileList, j_int32_t nDevid)
{
    int nStreamType = 0;
	J_RemoteVod *pRemoteVod = dynamic_cast<J_RemoteVod *>(JoAdapterFactory->FatchChannel(pResid, nStreamType, nDevid));
	if (pRemoteVod == NULL)
	{
		J_OS::LOGINFO("CAdapterManager::GetVodStream channel not exist, resid = %s", pResid);
		return J_NOT_EXIST;
	}

	return pRemoteVod->EmunFileByTime(beginTime, endTime, fileList);
}

int CAdapterManager::GetVodStream(j_socket_t nSocket, const char *pResId, J_RemoteVod *&pObj, j_int32_t nDevid)
{
    int nStreamType = 0;
	J_RemoteVod *pRemoteVod = dynamic_cast<J_RemoteVod *>(JoAdapterFactory->FatchChannel(pResId, nStreamType, nDevid));
	if (pRemoteVod == NULL)
	{
		J_OS::LOGINFO("CAdapterManager::GetVodStream channel not exist, resid = %s", pResId);
		return J_NOT_EXIST;
	}

	std::map<j_socket_t, J_Obj *>::iterator it = m_vodMap.find(nSocket);
	if (it == m_vodMap.end())
	{
		J_Obj *pVodStream = NULL;
		pRemoteVod->OpenVodStream(pVodStream);
		m_vodMap[nSocket] = pVodStream;
	}
	pObj = dynamic_cast<J_RemoteVod *>(m_vodMap[nSocket]);

	return J_OK;
}

int CAdapterManager::DelVodStream(j_socket_t nSocket, const char *pResId, j_int32_t nDevid)
{
    int nStreamType = 0;
	J_RemoteVod *pRemoteVod = dynamic_cast<J_RemoteVod *>(JoAdapterFactory->FatchChannel(pResId, nStreamType, nDevid));
	if (pRemoteVod == NULL)
	{
		J_OS::LOGINFO("CAdapterManager::DelVodStream channel not exist, resid = %s", pResId);
		return J_NOT_EXIST;
	}

	std::map<j_socket_t, J_Obj *>::iterator it = m_vodMap.find(nSocket);
	if (it == m_vodMap.end())
	{
		J_OS::LOGINFO("CAdapterManager::DelVodStream vodStream not exist, id = %d", nSocket.sock);
		return J_NOT_EXIST;
	}
	pRemoteVod->CloseVodStream(it->second);
	m_vodMap.erase(it);

	return J_OK;
}

int CAdapterManager::GetRingBuffer(const char *pResid, int nStreamType, const j_socket_t nSocket, CRingBuffer *&pRingBuffer)
{
    J_ChannelKey key;
	key.resid = pResid;
	key.stream_type = nStreamType;
	StreamMap::iterator it = m_streamMap.find(key);
	if (it == m_streamMap.end() /*|| m_streamMap[pResid].ringBufferMap == NULL*/)
	{
		StreamInfo info;
		info.videoStream = NULL;
		info.ringBufferMap.clear();// = new RingBufferMap;

		m_streamMap[key] = info;
	}

	RingBufferMap::iterator it2 = m_streamMap[key].ringBufferMap.find(nSocket);
	if (it2 == m_streamMap[key].ringBufferMap.end())
	{
		m_streamMap[key].ringBufferMap[nSocket] = new CRingBuffer();
		//J_OS::LOGINFO("m_streamMap[pResid].ringBufferMap[nSocket] = new CRingBuffer();");
	}

	pRingBuffer = m_streamMap[key].ringBufferMap[nSocket];

	return J_OK;
}

int CAdapterManager::DelRingBuffer(const char *pResid, int nStreamType, const j_socket_t nSocket)
{
    J_ChannelKey key;
	key.resid = pResid;
	key.stream_type = nStreamType;
	StreamMap::iterator it = m_streamMap.find(key);
	if (it == m_streamMap.end())
		return J_OK;

	RingBufferMap::iterator it2 = it->second.ringBufferMap.find(nSocket);
	if (it2 == it->second.ringBufferMap.end())
		return J_OK;

	delete(it2->second);
	it->second.ringBufferMap.erase(it2);
	//J_OS::LOGINFO("it->second.ringBufferMap.erase(it2);");

	if (it->second.ringBufferMap.empty())
	{
		//delete it->second.ringBufferMap;
		it->second.ringBufferMap.clear();// = NULL;
	}

	return J_OK;
}
