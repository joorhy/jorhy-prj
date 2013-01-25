#ifndef __AIPSTARADAPTER_H_
#define __AIPSTARADAPTER_H_
#include "j_includes.h"
#include "ModuleManagerDef.h"
#include "config.h"
#include "tmTransDefine.h"
#include "tmControlClient.h"

class CAipstarAdapterBase : public J_DevAdapter
{};

class CAipstarAdapter : public J_BaseAdapter<CAipstarAdapterBase>
{
	friend class CAipstarChannel;
public:
	CAipstarAdapter(int nDevId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword);
	~CAipstarAdapter();

	static int Maker(J_Obj *&pObj, int nDevId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
	{
		pObj = new CAipstarAdapter(nDevId, pAddr, nPort, pUsername, pPassword);
		return J_OK;
	}

public:
	///J_VideoAdapter
	virtual J_DevStatus GetStatus() const;
	virtual int Broken();
	virtual int MakeChannel(const char *pResid, void *&pObj, void *pOwner, int nChannel, int nStream, int nMode);

protected:
    int Relogin();

private:
	char *GetRemoteIp() const { return (char *)m_remoteIP; }
	int GetRemotePort() const { return m_remotePort; }
	char *GetRemoteUser() const { return (char *)m_username; }
	char *GetRemotePw() const { return (char *)m_password; }
	HANDLE GetClientHandle() const { return m_devHandle; }

	static BOOL OnConnectCallBack(HANDLE hHandle, BOOL bConnect, unsigned int dResult, void *context)
	{
		CAipstarAdapter *pThis = static_cast<CAipstarAdapter *>(context);
		if (pThis != NULL)
			pThis->OnConnect(hHandle, bConnect);

		return true;
	}
	void OnConnect(HANDLE hHandle, BOOL bConnect);

private:
	int Login();
	int Logout();

private:
	char m_remoteIP[16];
	int  m_remotePort;
	char m_username[64];
	char m_password[64];

	J_DevStatus m_status;
	HANDLE m_devHandle;
};

ADAPTER_BEGIN_MAKER(Aipstar)
	ADAPTER_ENTER_MAKER("aipstar", CAipstarAdapter::Maker)
ADAPTER_END_MAKER()

#endif //~__AIPSTARADAPTER_H_
