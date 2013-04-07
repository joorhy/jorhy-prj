#pragma once

#include "pl_singleton.h"
#include "pl_core.h"
#include "pl_lock.h"
#include "pl_player.h"
#include <map>
#include <string>

typedef int (*J_MakePlayerFun)(PlPlayer *&, int nWorkMode, void *pUser);
typedef int (*J_MakeWindowFun)(CWnd *&, HWND hParent,UINT nID);

class PL_API CPlFactory : public SingletonTmpl<CPlFactory>
{
	typedef std::map<std::string, J_MakePlayerFun> PlayerRegistMap;
	typedef std::map<void *, PlPlayer *> PlayerMap;
	typedef std::map<std::string, J_MakeWindowFun> WindowRegistMap;
	typedef std::map<int, CWnd *> WindowMap;
public:
	CPlFactory() {}
	~CPlFactory() {}

public:
	int RegisterPlayer(const char *playerType, J_MakePlayerFun pFun);
	PlPlayer *GetPlayer(const char *pType, int nWorkMode, void *pUser);
	void DelPlayer(void *pUser);

	int RegisterWindow(const char *wndType, J_MakeWindowFun pFun);
	CWnd *GetWindow(const char *pType, HWND hParent, UINT nId);
	void DelWindow(int nId);

private:
	PlayerRegistMap m_playerRegistMap;
	PlayerMap m_playerMap;
	WindowRegistMap m_wndRegistMap;
	WindowMap m_wndMap;
	PlLock m_lock;
};

///Window
#define PLAYER_BEGIN_MAKER(type)\
	static int pl_##type =

#define PLAYER_ENTER_MAKER(plType, maker)\
	CPlFactory::Instance()->RegisterPlayer((plType), (maker))

#define PLAYER_END_MAKER()\
	;

///Window
#define WINDOW_ENTER_MAKER(wndType, maker)\
	static void PL_API RegisterMaker() \
	{\
		CPlFactory::Instance()->RegisterWindow((wndType), (maker));\
	}