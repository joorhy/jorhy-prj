#ifndef __MANAGERFACTORY_H_
#define __MANAGERFACTORY_H_
#include "j_includes.h"
#include "x_singleton.h"
#include "x_lock.h"

typedef int (*J_MakeManagerFun)(J_Obj *&);

class JO_API CManagerFactory
{
	typedef std::map<std::string, J_MakeManagerFun> ManagerRegistMap;
	typedef std::map<std::string, J_JoManager *> ManagerMap;
public:
	CManagerFactory() {}
	~CManagerFactory() {}

public:
	///注册Filter类
	///@param[in] 	managerType Manager
	///@param[in] 	J_MakeManagerFun Manager的构造函数
	///@return 		参考x_error_type.h
	int RegisterManager(const char *managerType, J_MakeManagerFun pFun);

	J_JoManager *GetManager(const char *pMuxType);
	void DelManager(const char *pMuxType);

private:
	ManagerRegistMap m_managerRegistMap;
	ManagerMap m_managerMap;
	J_OS::TLocker_t m_lock;
};

#endif //~__MANAGERFACTORY_H_
