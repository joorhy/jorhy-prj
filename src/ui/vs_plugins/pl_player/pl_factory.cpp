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

PlPlayer *CPlFactory::GetPlayer(const char *pType, int nWorkMode, void *pUser, HWND hWnd)
{
	m_lock.Lock();
	PlPlayer *player = NULL;
	PlayerMap::iterator it = m_playerMap.find(hWnd);
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
			m_playerMap[hWnd] = dynamic_cast<PlPlayer *>(player);
	}
	else
		player = it->second;

	m_lock.Unlock();

	return dynamic_cast<PlPlayer *>(player);
}

void CPlFactory::DelPlayer(HWND hWnd)
{
	m_lock.Lock();
	PlayerMap::iterator it = m_playerMap.find(hWnd);
	if (it != m_playerMap.end())
	{
		delete it->second;
		m_playerMap.erase(it);
	}
	m_lock.Unlock();
}