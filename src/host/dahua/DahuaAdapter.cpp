#include "DahuaAdapter.h"

#include "x_adapter_manager.h"
#include "DahuaChannel.h"

CDahuaAdapter::CDahuaAdapter(int nDevId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
{
	m_devID = 0;
	m_status = jo_dev_broken;
	memset(m_remoteIP, 0, sizeof(m_remoteIP));
	memset(m_username, 0, sizeof(m_username));
	memset(m_password, 0, sizeof(m_password));
	m_remotePort = nPort;
	strcpy(m_remoteIP, pAddr);
	strcpy(m_username, pUsername);
	strcpy(m_password, pPassword);

	CLIENT_Init(NULL, 0);
	Login();
	CLIENT_SetAutoReconnect(OnConnectCallBack, (DWORD)this);

	J_OS::LOGINFO("CDahuaAdapter::CDahuaAdapter(ip = %s, port = %d)", pAddr, nPort);
}

CDahuaAdapter::~CDahuaAdapter()
{
	if (Logout() == J_OK)
		m_status = jo_dev_broken;
	
	CLIENT_Cleanup();

	J_OS::LOGINFO("CDahuaAdapter::~CDahuaAdapter()");
}

J_DevStatus CDahuaAdapter::GetStatus() const
{
	return m_status;
}
int CDahuaAdapter::Broken()
{
	return J_OK;
}

int CDahuaAdapter::MakeChannel(const char *pResid, void *&pObj, void *pOwner, int nChannel, int nStream, int nMode)
{
	CDahuaChannel *pChannel = new CDahuaChannel(pResid, pOwner, nChannel, nStream, nMode);
	if (NULL == pChannel)
		return J_MEMORY_ERROR;

	pObj = pChannel;

	return J_OK;
}

int CDahuaAdapter::Relogin()
{
    Logout();
    return Login();
}

int CDahuaAdapter::Login()
{
	NET_DEVICEINFO info = {0};
	int nError = 0;

	m_devID = CLIENT_Login(m_remoteIP, m_remotePort, m_username, m_password, &info, &nError);
	if (m_devID != 0)
    {
        m_status = jo_dev_ready;
    }
    else
    {
        J_OS::LOGINFO("CDahuaAdapter::Login() Login faild, error = %d", nError);
    }

	return J_OK;
}

int CDahuaAdapter::Logout()
{
	if (CLIENT_Logout(m_devID))
        m_status = jo_dev_broken;

	return J_OK;
}

void CDahuaAdapter::OnConnect(LONG hHandle, char *pDVRIP, LONG nDVRPort, DWORD dwUser)
{
	printf("connect = %d\n", hHandle);
}
