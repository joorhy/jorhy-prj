#ifndef __LOCALMANAGER_H_
#define __LOCALMANAGER_H_
#include "j_includes.h"
#include "sqlite3.h"
#include "ModuleManagerDef.h"

class CLocalManager : public J_JoManager
{
public:
	CLocalManager();
	~CLocalManager();

	static int Maker(J_Obj *&pObj)
	{
		pObj = new CLocalManager();
		return J_OK;
	}

public:
	virtual int ListDevices(std::vector<J_DeviceInfo> &devList);
	virtual int GetChannelInfo(const char *channelId, J_ChannelInfo &channelInfo);
	virtual int GetRecordInfo(J_RecordInfo &recordInfo);

private:
	int OpenDB();

private:
	sqlite3 *m_sqlite;
};

MANAGER_BEGIN_MAKER(local)
	MANAGER_ENTER_MAKER("local", CLocalManager::Maker)
MANAGER_END_MAKER()

#endif //~__LOCALMANAGER_H_
