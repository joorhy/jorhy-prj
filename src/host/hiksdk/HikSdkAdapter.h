#ifndef __HIKSDKADAPTER_H_
#define __HIKSDKADAPTER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
#include "x_timer.h"
#include "x_socket.h"
#include "x_thread.h"

#include "HCNetSDK.h"

class CHikSdkAdapterBase : public J_DevAdapter
{};

class CHikSdkAdapter : public J_BaseAdapter<CHikSdkAdapterBase>
{
	friend class CHikSdkChannel;
public:
	CHikSdkAdapter(int nDvrId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword);
	~CHikSdkAdapter();

	static int Maker(J_Obj *&pObj, int nDrvId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
	{
		pObj = new CHikSdkAdapter(nDrvId, pAddr, nPort, pUsername, pPassword);
		return J_OK;
	}

public:
	///J_VideoAdapter
	j_result_t GetDevInfo(J_DeviceInfo &info) { return J_OK; }
	virtual J_DevStatus GetStatus() const;
	virtual int Broken();
	virtual int MakeChannel(const char *pResid, J_Obj *&pObj, J_Obj *pOwner, int nChannel, int nStream, int nMode);
	
protected:
	LONG GetUserId() { return m_nUserId; }

private:
	LONG m_nUserId;
};
#endif //~__HIKSDKADAPTER_H_
