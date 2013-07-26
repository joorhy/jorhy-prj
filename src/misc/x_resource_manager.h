#ifndef __X_RESOURCE_MANAGER_H_
#define __X_RESOURCE_MANAGER_H_
#include "j_includes.h"
#include "x_timer.h"
#include "x_lock.h"

class JO_API CResourceManager
{
public:
	CResourceManager();
	~CResourceManager();

public:
	///启动定时器
	///@return 		参考x_error_type.h
	int InitResource();
	///停止定时器
	void ReleaseResource();
	///添加资源
	///@param		resInfo 资源信息
	///@return 		参考x_error_type.h
	j_result_t AddResource(J_ResourceInfo &resInfo);

private:
	static void TimerThread(void *pUser)
	{
		CResourceManager *pThis = static_cast<CResourceManager *>(pUser);
		if (pThis != NULL)
			pThis->OnTimer();
	}
	void OnTimer();

private:
	J_OS::CTLock m_locker;
	J_OS::CTimer m_timer;
	j_boolean_t m_bRegiste;
	ResourceMap m_devMap;
};
JO_DECLARE_SINGLETON(ResourceManager)

#endif //~__X_RESOURCE_MANAGER_H_