#include "stdafx.h"
#include "pl_factory.h"
#include "pl_err.h"

int CPlFactory::RegisterPlayer(const char *playerType, J_MakePlayerFun pFun)
{
	PlayerRegistMap::iterator it = m_playerRegistMap.find(playerType);
	if (it == m_playerRegistMap.end())
	{
		m_playerRegistMap[playerType] = pFun;
		//J_OS::LOGINFO("CFilterFactory::RegisterFilter %s Regist Sucess!!!", filterType);

		return PL_OK;
	}

	return PL_ERR_EXIST;
}

PlPlayer *CPlFactory::GetPlayer(const char *pType, int nWorkMode, void *pUser)
{
	m_lock.Lock();
	PlPlayer *player = NULL;
	PlayerMap::iterator it = m_playerMap.find(pUser);
	if (it == m_playerMap.end())
	{
		PlayerRegistMap::iterator itPlayer = m_playerRegistMap.find(pType);
		if (itPlayer == m_playerRegistMap.end())
		{
			//J_OS::LOGINFO("CFilterFactory::GetFilter Filter not registed, filterType = %s", pType);
		}
		else
		{
			itPlayer->second(player, nWorkMode, pUser);
		}

		if (player != NULL)
			m_playerMap[pUser] = dynamic_cast<PlPlayer *>(player);
	}
	else
		player = it->second;

	m_lock.Unlock();

	return dynamic_cast<PlPlayer *>(player);
}

void CPlFactory::DelPlayer(void *pUser)
{
	m_lock.Lock();
	PlayerMap::iterator it = m_playerMap.find(pUser);
	if (it != m_playerMap.end())
	{
		delete it->second;
		m_playerMap.erase(it);
	}
	m_lock.Unlock();
}

int CPlFactory::RegisterWindow(const char *wndType, J_MakeWindowFun pFun)
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

CWnd *CPlFactory::GetWindow(const char *pType, HWND hParent, UINT nId)
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

void CPlFactory::DelWindow(int nId)
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

