#ifndef __DAHUAADAPTER_H_
#define __DAHUAADAPTER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
#include "dhnetsdk.h"

class CDahuaAdapterBase : public J_DevAdapter
{};

class CDahuaAdapter : public J_BaseAdapter<CDahuaAdapterBase>
{
	friend class CDahuaChannel;
public:
	CDahuaAdapter(int nDevId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword);
	~CDahuaAdapter();

	static int Maker(J_Obj *&pObj, int nDevId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
	{
		pObj = new CDahuaAdapter(nDevId, pAddr, nPort, pUsername, pPassword);
		return J_OK;
	}

public:
	///J_VideoAdapter
	virtual J_DevStatus GetStatus() const;
	virtual int Broken();
	virtual int MakeChannel(const char *pResid, J_Obj *&pObj, J_Obj *pOwner, int nChannel, int nStream, int nMode);

protected:
    int Relogin();

private:
	char *GetRemoteIp() const { return (char *)m_remoteIP; }
	int GetRemotePort() const { return m_remotePort; }
	char *GetRemoteUser() const { return (char *)m_username; }
	char *GetRemotePw() const { return (char *)m_password; }
	LONG GetDevID() const { return m_devID; }

#ifdef WIN32
	static void CALLBACK OnConnectCallBack(LLONG hHandle, char *pDVRIP, LONG nDVRPort, LDWORD dwUser)
#else
	static void OnConnectCallBack(long hHandle, char *pDVRIP, int nDVRPort, long dwUser)
#endif
	{
		CDahuaAdapter *pThis = reinterpret_cast<CDahuaAdapter *>(dwUser);
		if (pThis != NULL)
			pThis->OnConnect(hHandle, pDVRIP, nDVRPort, dwUser);
	}
	void OnConnect(LONG hHandle, char *pDVRIP, LONG nDVRPort, DWORD dwUser);

private:
	int Login();
	int Logout();

private:
	char m_remoteIP[16];
	int  m_remotePort;
	char m_username[64];
	char m_password[64];

	J_DevStatus m_status;
	LONG m_devID;
};

/*ADAPTER_BEGIN_MAKER(Dahua)
	ADAPTER_ENTER_MAKER("dahua", CDahuaAdapter::Maker)
ADAPTER_END_MAKER()*/

#endif //~__DAHUAADAPTER_H_
