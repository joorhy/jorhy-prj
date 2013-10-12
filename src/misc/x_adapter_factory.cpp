#include "x_adapter_manager.h"
#include "x_manager_factory.h"
#include "x_sdk.h"
#include "x_config.h"

#define TYPE_OR_ID_SIZE 8

JO_IMPLEMENT_SINGLETON(AdapterFactory)

CAdapterFactory::CAdapterFactory()
{
	m_adapterRegistMap.clear();
}

CAdapterFactory::~CAdapterFactory()
{
	
}

int CAdapterFactory::RegisterAdapter(const char *adapterType, J_MakeAdapterFun pFun)
{
	AdapterRegistMap::iterator it = m_adapterRegistMap.find(adapterType);
	if (it == m_adapterRegistMap.end())
	{
		m_adapterRegistMap[adapterType] = pFun;
		J_OS::LOGINFO("CAdapterFactory::RegisterAdapter %s Regist Sucess!!!", adapterType);

		return J_OK;
	}

	return J_EXIST;
}

J_Obj *CAdapterFactory::FatchAdapter(const char *pResId)
{
	//pResId 标识的是DVR ID
	AdapterMap::iterator it = m_adapterMap.find(pResId);
	if (it != m_adapterMap.end())
		return it->second;

	return NULL;
}

J_Obj* CAdapterFactory::FatchChannel(const char *pResId, int nStreamType, j_int32_t nDevId)
{
	//pResId 标识的是通道ID
	if (NULL == pResId)
	{
		J_OS::LOGINFO("CAdapterFactory::FatchChannel param error, resid = %s", pResId);
		return NULL;
	}
	J_ChannelKey key;
	key.resid = pResId;
	key.stream_type = nStreamType;

	ChannelMap::iterator it = m_channelMap.find(key);
	if (it == m_channelMap.end())
	{
		J_ResourceInfo channelInfo = {0};
		if (nDevId < 0)
		{
			int nRet = JoManagerFactory->GetManager(CXConfig::GetConfigType())->GetChannelInfo(pResId, channelInfo);
			if (nRet != J_OK)
			{
				J_OS::LOGINFO("CAdapterFactory::FatchChannel GetDevinfoByChannel error, resid = %s", pResId);
				return NULL;
			}
		}
		else
		{
			channelInfo.devInfo.devId = nDevId;
			channelInfo.chNum = atoi(pResId);
		}

		char res_or_dvr[TYPE_OR_ID_SIZE];
		memset (res_or_dvr, 0, sizeof(res_or_dvr));
		sprintf(res_or_dvr, "%d", channelInfo.devInfo.devId);

		AdapterMap::iterator it = m_adapterMap.find(res_or_dvr);
		if (it == m_adapterMap.end())
			return NULL;

		J_Obj *pObjChannel = NULL;
		printf("8---%x\n", it->second);
		J_DevAdapter *pDevAdapter = dynamic_cast<J_DevAdapter *>(it->second);
		if (pDevAdapter != NULL)
		{
			pDevAdapter->MakeChannel(pResId, pObjChannel, it->second, channelInfo.chNum, nStreamType);
		}
		else
		{
			J_OS::LOGINFO("CAdapterFactory::FatchChannel VideoAdapter not Exist");
		}

		if (pObjChannel != NULL)
		{
			m_channelMap[key] = pObjChannel;
			printf("9---%x\n", pObjChannel);
			J_ChannelStream *pChannel = dynamic_cast<J_ChannelStream *>(pObjChannel);
			if (pChannel && !pChannel->HasMultiStream())
			{
				key.stream_type = (nStreamType == 0 ? 1 : 0);
				m_channelMap[key] = pObjChannel;
			}
			return pObjChannel;
		}
	}
	else
	{
        return it->second;
	}

	return NULL;
}

int CAdapterFactory::ReleaseChannel(const char *pResId, int nStreamType)
{
	//pResId 标识的是通道ID
	J_ChannelKey key;
	key.resid = pResId;
	key.stream_type = nStreamType;

	ChannelMap::iterator it = m_channelMap.find(key);
	if (it != m_channelMap.end())
	{
	    delete (J_Obj *)it->second;
		m_channelMap.erase(it);
	}

	return J_OK;
}

int CAdapterFactory::MakeAdapterDev(const char *pDevType, int nDevId, const char *pDevIp, int nDevPort, const char *pUsername, const char *pPasswd)
{
	AdapterRegistMap::iterator itRegister = m_adapterRegistMap.find(pDevType);
	if (itRegister == m_adapterRegistMap.end())
	{
		J_OS::LOGINFO("CAdapterFactory::MakeAdapterDev Adapter not registed, adapterType = %s", pDevType);
		return J_UNKNOW;
	}

	char dev_id[TYPE_OR_ID_SIZE];
	memset(dev_id, 0, TYPE_OR_ID_SIZE);
	sprintf(dev_id, "%d", nDevId);
	if (m_adapterMap.find(dev_id) == m_adapterMap.end())
	{
		J_Obj *pObj = NULL;
		itRegister->second(pObj, nDevId, pDevIp, nDevPort, pUsername, pPasswd);
		if (pObj != NULL)
		{
			m_adapterMap[dev_id] = pObj;
		}
	}
	return J_OK;
}