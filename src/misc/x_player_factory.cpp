#include "x_player_factory.h"
#include "x_string.h"

JO_IMPLEMENT_SINGLETON(PlayerFactory)

int CPlayerFactory::RegisterPlayer(const char *playerType, J_MakePlayerFun pFun)
{
	PlayerRegistMap::iterator it = m_playerRegistMap.find(playerType);
	if (it == m_playerRegistMap.end())
	{
		m_playerRegistMap[playerType] = pFun;
		J_OS::LOGINFO("CPlayerFactory::RegisterPlayer %s Regist Sucess!!!", playerType);

		return J_OK;
	}

	return J_EXIST;
}

J_Player *CPlayerFactory::GetPlayer(j_socket_t nSocket, const char *pType)
{
	TLock(m_lock);
	J_Obj *protocolPlayer = NULL;
	PlayerMap::iterator it = m_playerMap.find(nSocket);
	if (it == m_playerMap.end())
	{
		PlayerRegistMap::iterator itPlayer = m_playerRegistMap.find(pType);
		if (itPlayer == m_playerRegistMap.end())
		{
			J_OS::LOGINFO("CPlayerFactory::GetPlayer Player not registed, playerType = %s", pType);
		}
		else
		{
			itPlayer->second(protocolPlayer);
		}

		if (protocolPlayer != NULL)
			m_playerMap[nSocket] = dynamic_cast<J_Player *>(protocolPlayer);
	}
	else
		protocolPlayer = it->second;

	TUnlock(m_lock);

	return dynamic_cast<J_Player *>(protocolPlayer);
}

void CPlayerFactory::DelPlayer(j_socket_t nSocket)
{
	TLock(m_lock);
	PlayerMap::iterator it = m_playerMap.find(nSocket);
	if (it != m_playerMap.end())
	{
		delete it->second;
		m_playerMap.erase(it);
	}
	TUnlock(m_lock);
}
