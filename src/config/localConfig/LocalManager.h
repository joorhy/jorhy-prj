#ifndef __LOCALMANAGER_H_
#define __LOCALMANAGER_H_
#include "j_includes.h"
#include "DeviceControl.h"
#include "sqlite3.h"
#include "x_module_manager_def.h"

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
	///J_JoManager
	virtual j_result_t GetStreamServerInfo(const j_char_t *pResid, J_StreamServerInfo &ssInfo) { return 0; }
	virtual j_result_t GetResourceInfo(ResourceMap &resInfo);
	virtual j_result_t GetChannelInfo(const char *pResid, J_ResourceInfo &resInfo);
	virtual j_result_t StartRecord();
	virtual j_result_t StopRecord();

private:
	int OpenDB();

private:
	sqlite3 *m_sqlite;
	CDeviceControl m_deviceControl;
};

#endif //~__LOCALMANAGER_H_
