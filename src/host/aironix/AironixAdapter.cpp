#include "AironixAdapter.h"
#include "x_adapter_manager.h"
#include "AironixChannel.h"
#include "DVR_NET_SDK.h"

CAironixAdapter::CAironixAdapter(int nDevId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
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
int CAironixAdapter::Broken()
{
	return J_OK;
}

int CAironixAdapter::MakeChannel(const char *pResid, void *&pObj, void *pOwner, int nChannel, int nStream, int nMode)
{
	CAironixChannel *pChannel = new CAironixChannel(pResid, pOwner, nChannel, nStream, nMode);
	if (NULL == pChannel)
		return J_MEMORY_ERROR;

	pObj = pChannel;

	return J_OK;
}

int CAironixAdapter::Login()
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

int CAironixAdapter::Logout()
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
