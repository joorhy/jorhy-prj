#ifndef __REMOTEMANAGER_H_
#define __REMOTEMANAGER_H_
#include "j_includes.h"
#include "x_singleton.h"
#include "x_sdk_def.h"
#include "ModuleManagerDef.h"

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
	virtual int ListDevices(std::vector<J_DeviceInfo> &devList);
	virtual int GetChannelInfo(const char *channelId, J_ChannelInfo &channelInfo);
	virtual int GetRecordInfo(J_RecordInfo &recordInfo);

private:

private:
	r_register *m_regInfo;
	J_OS::TLocker_t m_locker;
};

MANAGER_BEGIN_MAKER(remote)
	MANAGER_ENTER_MAKER("mc", CRemoteManager::Maker)
MANAGER_END_MAKER()

#endif //~__REMOTEMANAGER_H_
