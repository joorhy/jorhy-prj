#pragma once

#include "pl_singleton.h"
#include <map>

typedef int (*J_MakePlayerFun)(void *&, const char *pResid);
typedef int (*J_MakeWindowFun)(void *&, const char *pResid);

class CPlFactory : public SingletonTmpl<CPlFactory>
{
	typedef std::map<std::string, J_MakePlayerFun> PlayerRegistMap;
	typedef std::map<std::string, J_MakeWindowFun> WindowRegistMap;

public:
	CPlFactory();
	~CPlFactory();

public:
	int RegisterPlayer(const char *playerType, J_MakePlayerFun pFun);

	void *GetPlayer(int nSocket, const char *pType, const char *pResid);
	void DelPlayer(int nSocket);

	int RegisterWindow(const char *playerType, J_MakePlayerFun pFun);

	void *GetWindow(int nSocket, const char *pType, const char *pResid);
	void DelWindow(int nSocket);
};