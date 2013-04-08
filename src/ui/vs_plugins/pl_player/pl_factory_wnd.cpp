#include "stdafx.h"
#include "pl_factory_wnd.h"
#include "pl_err.h"

int CPlFactoryWnd::RegisterWindow(const char *wndType, J_MakeWindowFun pFun)
{
	WindowRegistMap::iterator it = m_wndRegistMap.find(wndType);
	if (it == m_wndRegistMap.end())
	{
		m_wndRegistMap[wndType] = pFun;
		//J_OS::LOGINFO("CFilterFactory::RegisterFilter %s Regist Sucess!!!", filterType);

		return PL_OK;
	}

	return PL_ERR_EXIST;
}

CWnd *CPlFactoryWnd::GetWindow(const char *pType, HWND hParent, UINT nId)
{
	m_lock.Lock();
	CWnd *wnd = NULL;
	WindowMap::iterator it = m_wndMap.find(nId);
	if (it == m_wndMap.end())
	{
		WindowRegistMap::iterator itWnd = m_wndRegistMap.find(pType);
		if (itWnd == m_wndRegistMap.end())
		{
			//J_OS::LOGINFO("CFilterFactory::GetFilter Filter not registed, filterType = %s", pType);
		}
		else
		{
			itWnd->second(wnd, hParent, nId);
		}

		if (wnd != NULL)
			m_wndMap[nId] = dynamic_cast<CWnd *>(wnd);
	}
	else
		wnd = it->second;

	m_lock.Unlock();

	return dynamic_cast<CWnd *>(wnd);
}

void CPlFactoryWnd::DelWindow(int nId)
{
	m_lock.Lock();
	WindowMap::iterator it = m_wndMap.find(nId);
	if (it != m_wndMap.end())
	{
		delete it->second;
		m_wndMap.erase(it);
	}
	m_lock.Unlock();
}