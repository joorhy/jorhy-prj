#include "x_filter_factory.h"
#include "x_string.h"

int CFilterFactory::RegisterFilter(const char *filterType, J_MakeFilterFun pFun)
{
	FilterRegistMap::iterator it = m_filterRegistMap.find(filterType);
	if (it == m_filterRegistMap.end())
	{
		m_filterRegistMap[filterType] = pFun;
		J_OS::LOGINFO("CFilterFactory::RegisterFilter %s Regist Sucess!!!", filterType);

		return J_OK;
	}

	return J_EXIST;
}

J_RequestFilter *CFilterFactory::GetFilter(int nSocket, const char *pType)
{
	TLock(m_lock);
	J_Obj *protocolFilter = NULL;
	FilterMap::iterator it = m_filterMap.find(nSocket);
	if (it == m_filterMap.end())
	{
		FilterRegistMap::iterator itFilter = m_filterRegistMap.find(pType);
		if (itFilter == m_filterRegistMap.end())
		{
			J_OS::LOGINFO("CFilterFactory::GetFilter Filter not registed, filterType = %s", pType);
		}
		else
		{
			itFilter->second(protocolFilter);
		}

		if (protocolFilter != NULL)
			m_filterMap[nSocket] = dynamic_cast<J_RequestFilter *>(protocolFilter);
	}
	else
		protocolFilter = it->second;

	TUnlock(m_lock);

	return dynamic_cast<J_RequestFilter *>(protocolFilter);
}

void CFilterFactory::DelFilter(int nSocket)
{
	TLock(m_lock);
	FilterMap::iterator it = m_filterMap.find(nSocket);
	if (it != m_filterMap.end())
	{
		delete it->second;
		m_filterMap.erase(it);
	}
	TUnlock(m_lock);
}
