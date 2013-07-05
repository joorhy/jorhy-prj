#include "x_adapter_manager.h"

JO_IMPLEMENT_SINGLETON(AdapterManager)

CAdapterManager::CAdapterManager()
{

}

CAdapterManager::~CAdapterManager()
{

}

int CAdapterManager::StartVideo(const char *pResId, int nStreamType, const j_socket_t nSocket)
{
	J_ChannelStream *pChannelStream = static_cast<J_ChannelStream *>(JoAdapterFactory->GetInstance(pResId, OBJ_CHANNEL, nStreamType));
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
		void *pObjStream = NULL;
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

int CAdapterManager::StopVideo(const char *pResId, int nStreamType, const j_socket_t nSocket)
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

	J_ChannelStream *pChannelStream = static_cast<J_ChannelStream *>(JoAdapterFactory->GetInstance(pResId, OBJ_CHANNEL, nStreamType));
	if (pChannelStream->CloseStream(it->second.videoStream, it2->second) == J_NO_REF)
	{
		//(static_cast<J_VideoStream *>(m_streamMap[pResId]))->Shutdown();
		//m_streamMap.erase(it);
		DelRingBuffer(pResId, nStreamType, nSocket);
		if (!pChannelStream->HasMultiStream())
		{
           // key.stream_type = nStreamType == 0 ? 1 : 0;
			DelRingBuffer(pResId, nStreamType == 0 ? 1 : 0, nSocket);
			JoAdapterFactory->RemoveInstance(pResId, OBJ_CHANNEL, nStreamType == 0 ? 1 : 0);
            //m_streamMap.erase(key);
		}
		JoAdapterFactory->RemoveInstance(pResId, OBJ_CHANNEL, nStreamType);
	}
	//DelRingBuffer(pResId, nStreamType, nSocket);

	return J_OK;
}

int CAdapterManager::StartVoice(const char *pResId, const j_socket_t nSocket)
{
    int nStreamType = 0;
	J_ChannelStream *pChannelStream = static_cast<J_ChannelStream *>(JoAdapterFactory->GetInstance(pResId, OBJ_CHANNEL, nStreamType));
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
		void *pObjStream = NULL;
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

int CAdapterManager::StopVoice(const char *pResId, const j_socket_t nSocket)
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

	J_ChannelStream *pVoiceChannel = static_cast<J_ChannelStream *>(JoAdapterFactory->GetInstance(pResId, OBJ_CHANNEL, key.stream_type));
	if (pVoiceChannel->CloseStream(it->second.videoStream, it2->second) == J_NO_REF)
	{
		m_streamMap.erase(it);
	}
	DelRingBuffer(pResId, 0, nSocket);

	return J_OK;
}

int CAdapterManager::GetParser(const char *pResId, J_StreamParser *&pObj)
{
    int nStreamType = 0;
	J_StreamParser *pVideoParser = static_cast<J_StreamParser *>(JoAdapterFactory->GetInstance(pResId, OBJ_CHANNEL, nStreamType));
	if (pVideoParser == NULL)
	{
		J_OS::LOGINFO("CAdapterManager::StartRecord channel not exist, resid = %s", pResId);
		return J_NOT_EXIST;
	}

	std::map<std::string, void *>::iterator it = m_parserMap.find(pResId);
	if (it == m_parserMap.end())
	{
		void *pParser = NULL;
		pVideoParser->OpenParser(pParser);
		m_parserMap[pResId] = pParser;
	}
	pObj = (J_StreamParser *)m_parserMap[pResId];

	return J_OK;
}

int CAdapterManager::DelParser(const char *pResId)
{
    int nStreamType = 0;
	J_StreamParser *pVideoParser = static_cast<J_StreamParser *>(JoAdapterFactory->GetInstance(pResId, OBJ_CHANNEL, nStreamType));
	if (pVideoParser == NULL)
	{
		J_OS::LOGINFO("CAdapterManager::StopRecord channel not exist, resid = %s", pResId);
		return J_NOT_EXIST;
	}

	std::map<std::string, void *>::iterator it = m_parserMap.find(pResId);
	if (it == m_parserMap.end())
	{
		J_OS::LOGINFO("CAdapterManager::StopRecord parser not exist, resid = %s", pResId);
		return J_NOT_EXIST;
	}
	pVideoParser->CloseParser(it->second);
	m_parserMap.erase(it);

	return J_OK;
}

int CAdapterManager::FindVodFile(const char *pResid, time_t beginTime, time_t endTime, std::vector<J_FileInfo> &fileList)
{
    int nStreamType = 0;
	J_RemoteVod *pRemoteVod = static_cast<J_RemoteVod *>(JoAdapterFactory->GetInstance(pResid, OBJ_CHANNEL, nStreamType));
	if (pRemoteVod == NULL)
	{
		J_OS::LOGINFO("CAdapterManager::GetVodStream channel not exist, resid = %s", pResid);
		return J_NOT_EXIST;
	}

	return pRemoteVod->EmunFileByTime(beginTime, endTime, fileList);
}

int CAdapterManager::OnAlarm(int nDvrId, int nChannel, int nAlarmType)
{
	/*NorMsg *pMessage = new NorMsg();

	pMessage->m_almType = nAlarmType;

	CDBHelper::Instance()->GetDB().GetResidByDvrCh(nDvrId, nChannel, pMessage->m_resId);*/

	return J_OK;
}

int CAdapterManager::GetVodStream(j_socket_t nSocket, const char *pResId, J_RemoteVod *&pObj)
{
    int nStreamType = 0;
	J_RemoteVod *pRemoteVod = static_cast<J_RemoteVod *>(JoAdapterFactory->GetInstance(pResId, OBJ_CHANNEL, nStreamType));
	if (pRemoteVod == NULL)
	{
		J_OS::LOGINFO("CAdapterManager::GetVodStream channel not exist, resid = %s", pResId);
		return J_NOT_EXIST;
	}

	std::map<j_socket_t, void *>::iterator it = m_vodMap.find(nSocket);
	if (it == m_vodMap.end())
	{
		void *pVodStream = NULL;
		pRemoteVod->OpenVodStream(pVodStream);
		m_vodMap[nSocket] = pVodStream;
	}
	pObj = (J_RemoteVod *)m_vodMap[nSocket];

	return J_OK;
}

int CAdapterManager::DelVodStream(j_socket_t nSocket, const char *pResId)
{
    int nStreamType = 0;
	J_RemoteVod *pRemoteVod = static_cast<J_RemoteVod *>(JoAdapterFactory->GetInstance(pResId, OBJ_CHANNEL, nStreamType));
	if (pRemoteVod == NULL)
	{
		J_OS::LOGINFO("CAdapterManager::DelVodStream channel not exist, resid = %s", pResId);
		return J_NOT_EXIST;
	}

	std::map<j_socket_t, void *>::iterator it = m_vodMap.find(nSocket);
	if (it == m_vodMap.end())
	{
		J_OS::LOGINFO("CAdapterManager::DelVodStream vodStream not exist, id = %d", nSocket);
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
