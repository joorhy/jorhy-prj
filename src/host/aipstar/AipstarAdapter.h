#ifndef __AIPSTARADAPTER_H_
#define __AIPSTARADAPTER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
#include "config.h"
#include "tmTransDefine.h"
#include "tmControlClient.h"

class CAipstarAdapterBase : public J_DevAdapter
{};

class CAipstarAdapter : public J_BaseAdapter<CAipstarAdapterBase>
{
	friend class CAipstarChannel;
public:
	CAipstarAdapter(j_int32_t nDevId, const j_char_t *pAddr, j_int32_t nPort, const j_char_t *pUsername, const j_char_t *pPassword);
	~CAipstarAdapter();

	static j_result_t Maker(J_Obj *&pObj, j_int32_t nDevId, const j_char_t *pAddr, j_int32_t nPort, const j_char_t *pUsername, const j_char_t *pPassword)
	{
		pObj = new CAipstarAdapter(nDevId, pAddr, nPort, pUsername, pPassword);
		return J_OK;
	}

public:
	///J_VideoAdapter
	virtual J_DevStatus GetStatus() const;
	virtual j_result_t Broken();
	virtual j_result_t MakeChannel(const j_char_t *pResid, j_void_t *&pObj, j_void_t *pOwner, j_int32_t nChannel, j_int32_t nStream, j_int32_t nMode);

protected:
    int Relogin();

private:
	j_char_t *GetRemoteIp() const { return (j_char_t *)m_remoteIP; }
	j_int32_t GetRemotePort() const { return m_remotePort; }
	j_char_t *GetRemoteUser() const { return (j_char_t *)m_username; }
	j_char_t *GetRemotePw() const { return (j_char_t *)m_password; }
	HANDLE GetClientHandle() const { return m_devHandle; }

	static BOOL OnConnectCallBack(HANDLE hHandle, BOOL bConnect, unsigned int dResult, void *context)
	{
		CAipstarAdapter *pThis = static_cast<CAipstarAdapter *>(context);
		if (pThis != NULL)
			pThis->OnConnect(hHandle, bConnect);

		return true;
	}
	j_void_t OnConnect(HANDLE hHandle, BOOL bConnect);

private:
	j_result_t Login();
	j_result_t Logout();

private:
	j_char_t m_remoteIP[16];
	j_int32_t  m_remotePort;
	j_char_t m_username[64];
	j_char_t m_password[64];

	J_DevStatus m_status;
	HANDLE m_devHandle;
};

ADAPTER_BEGIN_MAKER(Aipstar)
	ADAPTER_ENTER_MAKER("aipstar", CAipstarAdapter::Maker)
ADAPTER_END_MAKER()

#endif //~__AIPSTARADAPTER_H_
