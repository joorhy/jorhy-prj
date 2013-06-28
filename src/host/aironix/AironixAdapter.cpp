#include "AironixAdapter.h"
#include "x_adapter_manager.h"
#include "AironixChannel.h"
#include "DVR_NET_SDK.h"

CAironixAdapter::CAironixAdapter(j_int32_t nDevId, const j_char_t *pAddr, j_int32_t nPort, const j_char_t *pUsername, const j_char_t *pPassword)
{
	//m_devHandle = NULL;
	m_status = jo_dev_broken;
	memset(m_remoteIP, 0, sizeof(m_remoteIP));
	memset(m_username, 0, sizeof(m_username));
	memset(m_password, 0, sizeof(m_password));
	m_remotePort = nPort;
	strcpy(m_remoteIP, pAddr);
	strcpy(m_username, pUsername);
	strcpy(m_password, pPassword);

	BOOL bInit = NET_SDK_Init();
	assert(bInit);
	Login();

	J_OS::LOGINFO("CAironixAdapter::CAironixAdapter(ip = %s, port = %d)", pAddr, nPort);
}

CAironixAdapter::~CAironixAdapter()
{
	if (Logout() == J_OK)
		m_status = jo_dev_broken;

    NET_SDK_Cleanup();

	J_OS::LOGINFO("CAironixAdapter::~CAironixAdapter()");
}

J_DevStatus CAironixAdapter::GetStatus() const
{
	return m_status;
}

j_result_t CAironixAdapter::Broken()
{
	return J_OK;
}

j_result_t CAironixAdapter::MakeChannel(const j_char_t *pResid, j_void_t *&pObj, j_void_t *pOwner, j_int32_t nChannel, j_int32_t nStream, j_int32_t nMode)
{
	CAironixChannel *pChannel = new CAironixChannel(pResid, pOwner, nChannel, nStream, nMode);
	if (NULL == pChannel)
		return J_MEMORY_ERROR;

	pObj = pChannel;

	return J_OK;
}

j_result_t CAironixAdapter::Login()
{
    NET_SDK_DEVICEINFO info;
    m_userId = NET_SDK_Login(m_remoteIP, m_remotePort, m_username, m_password, &info);
    if (m_userId == -1)
    {
        return J_UNKNOW;
    }
    m_userSubId = NET_SDK_Login(m_remoteIP, m_remotePort, m_username, m_password, &info);
    if (m_userSubId == -1)
    {
        return J_UNKNOW;
    }
	m_status = jo_dev_ready;

	return J_OK;
}

j_result_t CAironixAdapter::Logout()
{
    BOOL bRet = NET_SDK_Logout(m_userId);
    assert(bRet);
    bRet = NET_SDK_Logout(m_userSubId);
    assert(bRet);
	m_status = jo_dev_broken;

	return J_OK;
}

/*void CAironixAdapter::OnConnect(HANDLE hHandle, BOOL bConnect)
{
	printf("connect = %d\n", bConnect);
}*/

extern "C"
{
	void __declspec(dllexport)  Register()
	{
		SingletonTmpl<CAdapterFactory>::Instance()->RegisterAdapter("aipstar", CAipstarAdapter::Maker);
	}
}
