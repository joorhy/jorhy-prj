#ifndef __REMOTEMANAGER_H_
#define __REMOTEMANAGER_H_
#include "j_includes.h"
#include "x_singleton.h"
#include "x_sdk_def.h"
#include "x_module_manager_def.h"

class CRemoteManager : public J_JoManager
{
public:
	CRemoteManager();
	~CRemoteManager();

	static int Maker(J_Obj *&pObj)
	{
		pObj = new CRemoteManager();
		return J_OK;
	}

public:
	///J_JoManager
	virtual j_result_t GetStreamServerInfo(const j_char_t *pResid, J_StreamServerInfo &ssInfo);
	virtual j_result_t GetResourceInfo(ResourceMap &resInfo);
	virtual j_result_t GetChannelInfo(const char *pResid, J_ResourceInfo &resInfo);
	virtual j_result_t StartRecord();
	virtual j_result_t StopRecord() { return J_OK; }

private:

private:
	r_register *m_regInfo;
	J_OS::TLocker_t m_locker;
};

#endif //~__REMOTEMANAGER_H_
