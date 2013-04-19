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
	CWnd *hWnd = NULL;
	m_key.hWnd = hParent;
	m_key.nId = nId;
	WindowMap::iterator it = m_wndMap.find(m_key);
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
		{
			PL_WndInfo info = {0};
			info.pWnd = hWnd;
			info.nRef = 1;
			m_wndMap[m_key] = info;
		}
	}
	else
	{
		++it->second.nRef;
		hWnd = it->second.pWnd;
	}

	m_lock.Unlock();

	return hWnd;
}

void CPlFactoryWnd::DelWindow(HWND hParent, UINT nId)
{
	m_lock.Lock();
	m_key.hWnd = hParent;
	m_key.nId = nId;
	WindowMap::iterator it = m_wndMap.find(m_key);
	if (it != m_wndMap.end())
	{
		--it->second.nRef;
		if (it->second.nRef == 0)
		{
			delete (CWnd *)it->second.pWnd;
			m_wndMap.erase(it);
		}
	}
	m_lock.Unlock();
}