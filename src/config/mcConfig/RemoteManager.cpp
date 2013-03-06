#include "RemoteManager.h"
#include "x_config.h"
#include "x_sdk.h"

CRemoteManager::CRemoteManager()
{
	m_regInfo = NULL;
}

CRemoteManager::~CRemoteManager()
{
	if (m_regInfo)
		free(m_regInfo);
}

int CRemoteManager::ListDevices(std::vector<J_DeviceInfo> &devList)
{
    TLock(m_locker);
    if (m_regInfo == NULL)
        m_regInfo = StreamServerResgister(CXConfig::GetStreamServerId(), CXConfig::GetUrl());

	if (m_regInfo)
	{
		vector<_res>::iterator itDvr = m_regInfo->parm.resnum.begin();
		for (; itDvr != m_regInfo->parm.resnum.end(); itDvr++)
		{
			J_DeviceInfo devInfo = {0};
			devInfo.devId = itDvr->id;
			memcpy(devInfo.devIp, itDvr->ip.c_str(), strlen(itDvr->ip.c_str()));
			devInfo.devPort = (unsigned short)itDvr->port;
			if (itDvr->type == 1)
				strcpy(devInfo.devType, "hik");
			else if (itDvr->type == 2)
				strcpy(devInfo.devType, "sony");
			else if (itDvr->type == 3)
				strcpy(devInfo.devType, "aipstar");
            else if (itDvr->type == 4)
                strcpy(devInfo.devType, "aironix");
            else if (itDvr->type == 5)
                strcpy(devInfo.devType, "samsung");
			else if (itDvr->type == 6)
                strcpy(devInfo.devType, "dahua");
			else if (itDvr->type == 7)
                strcpy(devInfo.devType, "onvif");
			else
				J_OS::LOGINFO("CRemoteManager::ListDevices error devType = %d", itDvr->type);

			memcpy(devInfo.userName, itDvr->user.c_str(), strlen(itDvr->user.c_str()));
			memcpy(devInfo.passWd, itDvr->pass.c_str(), strlen(itDvr->pass.c_str()));

			devInfo.devStatus = jo_dev_broken;
			devList.push_back(devInfo);
		}

		//free(regInfo);
		//regInfo = NULL;

        TUnlock(m_locker);
		return J_OK;
	}
	TUnlock(m_locker);
	return J_DB_ERROR;
}

int CRemoteManager::GetChannelInfo(const char *channelId, J_ChannelInfo &channelInfo)
{
	r_devconfig *defConfig = GetDevConfigByResid((char *)channelId, CXConfig::GetUrl());
	if (defConfig == NULL)
	{
		J_OS::LOGINFO("CCmsConf::GetChannelInfo error, resid = %s", channelId);
		return J_DB_ERROR;
	}

	channelInfo.devId = defConfig->parm.id;
	channelInfo.channelNum = defConfig->parm.cha;

	free(defConfig);

	return J_OK;
}

int CRemoteManager::GetRecordInfo(J_RecordInfo &recordInfo)
{
    TLock(m_locker);
    if (m_regInfo == NULL)
        m_regInfo = StreamServerResgister(CXConfig::GetStreamServerId(), CXConfig::GetUrl());

	if (m_regInfo)
	{
		memset(&recordInfo, 0, sizeof(recordInfo));
		memcpy(recordInfo.vodPath, m_regInfo->parm.store.c_str(), m_regInfo->parm.store.length());
		recordInfo.timeInterval = m_regInfo->parm.segment_h;
		//free(regInfo);
		//regInfo = NULL;
	}
    TUnlock(m_locker);

	return J_OK;
}
