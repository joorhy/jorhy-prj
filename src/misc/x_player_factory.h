#ifndef __X_PLAYER_FACTORY_H_
#define __X_PLAYER_FACTORY_H_

#include "j_includes.h"
#include "x_singleton.h"
#include "x_lock.h"

typedef int (*J_MakePlayerFun)(J_Obj *&);

class JO_API CPlayerFactory
{
	typedef std::map<j_string_t, J_MakePlayerFun> PlayerRegistMap;
	typedef std::map<j_socket_t, J_Player *> PlayerMap;
public:
	CPlayerFactory() {}
	~CPlayerFactory() {}

public:
	///注册Player类
	///@param[in] 	adapterType player
	///@param[in] 	J_MakePlayerFun Filter的构造函数
	///@return 		参考x_error_type.h
	int RegisterPlayer(const char *plyaerType, J_MakePlayerFun pFun);

	J_Player *GetPlayer(j_socket_t nSocket, const char *pType);
	void DelPlayer(j_socket_t nSocket);

private:
	PlayerRegistMap m_playerRegistMap;
	PlayerMap m_playerMap;
	J_OS::TLocker_t m_lock;
};

JO_DECLARE_SINGLETON(PlayerFactory)

#endif //~__X_PLAYER_FACTORY_H_