#include "ManagerFactory.h"

int CManagerFactory::RegisterManager(const char *managerType, J_MakeManagerFun pFun)
{
	ManagerRegistMap::iterator it = m_managerRegistMap.find(managerType);
	if (it == m_managerRegistMap.end())
	{
		m_managerRegistMap[managerType] = pFun;
		J_OS::LOGINFO("CManagerFactory::RegisterManager %s Regist Sucess!!!", managerType);

		return J_OK;
	}

	return J_EXIST;
}

J_JoManager *CManagerFactory::GetManager(const char *pManagerType)
{
	TLock(m_lock);
	J_Obj *pManager = NULL;
	ManagerMap::iterator it = m_managerMap.find(pManagerType);
	if (it == m_managerMap.end())
	{
		ManagerRegistMap::iterator itManager = m_managerRegistMap.find(pManagerType);
		if (itManager == m_managerRegistMap.end())
		{
			J_OS::LOGINFO("CManagerFactory::GetManager Manager not registed, managerType = %s", pManagerType);
		}
		else
		{
			itManager->second(pManager);
		}

		if (pManager != NULL)
			m_managerMap[pManagerType] = dynamic_cast<J_JoManager *>(pManager);
	}
	else
		pManager = it->second;

	TUnlock(m_lock);

	return dynamic_cast<J_JoManager *>(pManager);
}

void CManagerFactory::DelManager(const char *pManagerType)
{
	TLock(m_lock);
	ManagerMap::iterator it = m_managerMap.find(pManagerType);
	if (it != m_managerMap.end())
	{
		delete it->second;
		m_managerMap.erase(it);
	}
	TUnlock(m_lock);
}

