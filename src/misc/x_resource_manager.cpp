#include "x_resource_manager.h"
#include "x_manager_factory.h"
#include "x_adapter_factory.h"
#include "x_config.h"
#include "x_sdk.h"

JO_IMPLEMENT_SINGLETON(ResourceManager)

CResourceManager::CResourceManager()
{
	m_bRegiste = false;
}

CResourceManager::~CResourceManager()
{

}

int CResourceManager::InitResource()
{
	m_timer.Create(5 * 1000, CResourceManager::TimerThread, this);
	return J_OK;
}

void CResourceManager::ReleaseResource()
{
	m_timer.Destroy();
}

j_result_t CResourceManager::AddResource(J_ResourceInfo &resInfo)
{
	TLock(m_locker);
	ResourceMap::iterator itDev = m_resMap.find(resInfo.resid);
	if (itDev == m_resMap.end())
	{
		resInfo.devInfo.devStatus = jo_dev_broken;
		m_resMap[resInfo.resid] = resInfo;
	}
	TUnlock(m_locker);
	return J_OK;
}

j_result_t CResourceManager::GetResource(const char *pResid, J_ResourceInfo &resInfo)
{
	j_result_t nResult = J_UNKNOW;
	TLock(m_locker);
	ResourceMap::iterator itDev = m_resMap.find(pResid);
	if (itDev != m_resMap.end())
	{
		resInfo = itDev->second;
		nResult = J_OK;
	}
	TUnlock(m_locker);
	return nResult;
}

void CResourceManager::OnTimer()
{
	int nRet = J_OK;
	if (!m_bRegiste)
	{
		J_JoManager *pManager = JoManagerFactory->GetManager(CXConfig::GetConfigType());
		nRet = pManager->GetResourceInfo(m_resMap);
		if (nRet == J_OK)
		{
			m_bRegiste = true;
		}
		else
		{
			return;
		}
	}
	else
	{
		if (JoXSdk->KeepAlive(CXConfig::GetStreamServerId(), (j_char_t *)CXConfig::GetUrl()) != J_OK)
			m_bRegiste = false;
	}

	TLock(m_locker);
	ResourceMap::iterator itDev = m_resMap.begin();
	for (; itDev != m_resMap.end(); ++itDev)
	{
		if (itDev->second.devInfo.devStatus == jo_dev_broken)
		{
			if (JoAdapterFactory->MakeAdapterDev(itDev->second.devInfo.devType, itDev->second.devInfo.devId, itDev->second.devInfo.devIp,
				itDev->second.devInfo.devPort, itDev->second.devInfo.userName, itDev->second.devInfo.passWd) == J_OK)
				itDev->second.devInfo.devStatus = jo_dev_ready;
		}
	}
	TUnlock(m_locker);
	JoManagerFactory->GetManager(CXConfig::GetConfigType())->StartRecord();
}