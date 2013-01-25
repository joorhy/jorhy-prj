#ifndef __AIRONIXADAPTER_H_
#define __AIRONIXADAPTER_H_
#include "j_includes.h"
#include "ModuleManagerDef.h"
//#include "DVR_NET_SDK.h"

class CAironixAdapterBase : public J_DevAdapter
{};

class CAironixAdapter : public J_BaseAdapter<CAironixAdapterBase>
{
	friend class CAironixChannel;
public:
	CAironixAdapter(int nDevId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword);
	~CAironixAdapter();

	static int Maker(J_Obj *&pObj, int nDevId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
	{
		pObj = new CAironixAdapter(nDevId, pAddr, nPort, pUsername, pPassword);
		return J_OK;
	}

public:
	///J_VideoAdapter
	virtual J_DevStatus GetStatus() const;
	virtual int Broken();
	virtual int MakeChannel(const char *pResid, void *&pObj, void *pOwner, int nChannel, int nStream, int nMode);

private:
	char *GetRemoteIp() const { return (char *)m_remoteIP; }
	int GetRemotePort() const { return m_remotePort; }
	char *GetRemoteUser() const { return (char *)m_username; }
	char *GetRemotePw() const { return (char *)m_password; }
	long GetUserId() const { return m_userId; }
	long GetSubUserId() const { return m_userSubId; }

	/*static BOOL OnConnectCallBack(HANDLE hHandle, BOOL bConnect, unsigned int dResult, void *context)
	{
		CAironixAdapter *pThis = static_cast<CAironixAdapter *>(context);
		if (pThis != NULL)
			pThis->OnConnect(hHandle, bConnect);

		return true;
	}
	void OnConnect(HANDLE hHandle, BOOL bConnect);*/

private:
	int Login();
	int Logout();

private:
	char m_remoteIP[16];
	int  m_remotePort;
	char m_username[64];
	char m_password[64];

	J_DevStatus m_status;
	long m_userId;
	long m_userSubId;
};

ADAPTER_BEGIN_MAKER(Aironix)
	ADAPTER_ENTER_MAKER("aironix", CAironixAdapter::Maker)
ADAPTER_END_MAKER()

#endif //~__AIRONIXADAPTER_H_
