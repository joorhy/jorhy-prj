#pragma once

#include "pl_singleton.h"
#include "pl_core.h"
#include "pl_lock.h"
#include "pl_player.h"
#include <map>
#include <string>

typedef int (*J_MakePlayerFun)(PlPlayer *&, int nWorkMode, void *pUser);

class PL_API CPlFactory : public SingletonTmpl<CPlFactory>
{
	typedef std::map<std::string, J_MakePlayerFun> PlayerRegistMap;
	typedef std::map<HWND, PlPlayer *> PlayerMap;
public:
	CPlFactory() {}
	~CPlFactory() {}

public:
	int RegisterPlayer(const char *playerType, J_MakePlayerFun pFun);
	PlPlayer *GetPlayer(const char *pType, int nWorkMode, void *pUser, HWND hWnd);
	void DelPlayer(HWND hWnd);

private:
	PlayerRegistMap m_playerRegistMap;
	PlayerMap m_playerMap;
	PlLock m_lock;
};

///Window
#define PLAYER_BEGIN_MAKER(type)\
	static int pl_##type =

#define PLAYER_ENTER_MAKER(plType, maker)\
	CPlFactory::Instance()->RegisterPlayer((plType), (maker))

#define PLAYER_END_MAKER()\
	;