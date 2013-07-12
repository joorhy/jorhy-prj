#ifndef __AIRONIXADAPTER_H_
#define __AIRONIXADAPTER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
//#include "DVR_NET_SDK.h"

class CAironixAdapterBase : public J_DevAdapter
{};

class CAironixAdapter : public J_BaseAdapter<CAironixAdapterBase>
{
	friend class CAironixChannel;
public:
	CAironixAdapter(j_int32_t nDevId, const j_char_t *pAddr, j_int32_t nPort, const j_char_t *pUsername, const j_char_t *pPassword);
	~CAironixAdapter();

	static j_int32_t Maker(J_Obj *&pObj, j_int32_t nDevId, const j_char_t *pAddr, j_int32_t nPort, const j_char_t *pUsername, const j_char_t *pPassword)
	{
		pObj = new CAironixAdapter(nDevId, pAddr, nPort, pUsername, pPassword);
		return J_OK;
	}

public:
	///J_VideoAdapter
	virtual J_DevStatus GetStatus() const;
	virtual j_result_t Broken();
	virtual j_result_t MakeChannel(const j_char_t *pResid, J_Obj *&pObj, J_Obj *pOwner, j_int32_t nChannel, j_int32_t nStream, j_int32_t nMode);

private:
	j_char_t *GetRemoteIp() const { return (j_char_t *)m_remoteIP; }
	j_int32_t GetRemotePort() const { return m_remotePort; }
	j_char_t *GetRemoteUser() const { return (j_char_t *)m_username; }
	j_char_t *GetRemotePw() const { return (j_char_t *)m_password; }
	j_int32_t GetUserId() const { return m_userId; }
	j_int32_t GetSubUserId() const { return m_userSubId; }

	/*static BOOL OnConnectCallBack(HANDLE hHandle, BOOL bConnect, unsigned int dResult, void *context)
	{
		CAironixAdapter *pThis = static_cast<CAironixAdapter *>(context);
		if (pThis != NULL)
			pThis->OnConnect(hHandle, bConnect);

		return true;
	}
	void OnConnect(HANDLE hHandle, BOOL bConnect);*/

private:
	j_int32_t Login();
	j_int32_t Logout();

private:
	j_char_t m_remoteIP[16];
	j_int32_t  m_remotePort;
	j_char_t m_username[64];
	j_char_t m_password[64];

	J_DevStatus m_status;
	j_int32_t m_userId;
	j_int32_t m_userSubId;
};
#endif //~__AIRONIXADAPTER_H_
