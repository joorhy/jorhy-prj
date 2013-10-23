#ifndef __JOADAPTER_H_
#define __JOADAPTER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"

class CJoAdapterBase : public J_DevAdapter
{};

class CJoAdapter : public J_BaseAdapter<CJoAdapterBase>
{
	friend class CJoChannel;
public:
	CJoAdapter(int nDvrId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword);
	~CJoAdapter();

	static int Maker(J_Obj *&pObj, int nDrvId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
	{
		pObj = new CJoAdapter(nDrvId, pAddr, nPort, pUsername, pPassword);
		return J_OK;
	}

public:
	///J_VideoAdapter
	j_result_t GetDevInfo(J_DeviceInfo &info);
	virtual J_DevStatus GetStatus() const;
	virtual j_result_t Broken();
	virtual j_result_t MakeChannel(const char *pResid, J_Obj *&pObj, J_Obj *pOwner, int nChannel, int nStream, int nMode);

protected:
	char *GetRemoteIp() const { return (char *)m_devInfo.devIp; }
	int GetRemotePort() const { return m_devInfo.devPort; }
	char *GetUser() const { return (char *)m_devInfo.userName; }
	char *GetPassword() const { return (char *)m_devInfo.passWd; }

private:
	J_DeviceInfo m_devInfo;
};

#endif //~__JOADAPTER_H_
