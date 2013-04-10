#include "stdafx.h"
#include "pl_factory_wnd.h"
#include "pl_wnd.h"
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
	CWnd *hWnd = NULL;
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
			itWnd->second(hWnd, hParent, nId);
		}

		if (hWnd != NULL)
			m_wndMap[nId] = hWnd;
	}
	else
		hWnd = it->second;

	m_lock.Unlock();

	return hWnd;
}

void CPlFactoryWnd::DelWindow(int nId)
{
	m_lock.Lock();
	WindowMap::iterator it = m_wndMap.find(nId);
	if (it != m_wndMap.end())
	{
		delete (CPlWnd *)it->second;
		m_wndMap.erase(it);
	}
	m_lock.Unlock();
}