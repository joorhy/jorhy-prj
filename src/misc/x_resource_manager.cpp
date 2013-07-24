#include "x_resource_manager.h"
#include "x_manager_factory.h"
#include "x_adapter_factory.h"
#include "x_config.h"

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
	m_timer.Create(1 * 1000, CResourceManager::TimerThread, this);
	return J_OK;
}

void CResourceManager::ReleaseResource()
{
	m_timer.Destroy();
}

void CResourceManager::OnTimer()
{
	int nRet = J_OK;
	if (!m_bRegiste)
	{
		J_JoManager *pManager = JoManagerFactory->GetManager(CXConfig::GetConfigType());
		nRet = pManager->GetResourceInfo(m_devMap);
		if (nRet == J_OK)
		{
			m_bRegiste = true;
		}
	}

	TLock(m_locker);
	ResourceMap::iterator itDev = m_devMap.begin();
	for (; itDev != m_devMap.end(); ++itDev)
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