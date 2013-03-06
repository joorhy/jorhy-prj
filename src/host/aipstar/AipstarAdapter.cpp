#include "AipstarAdapter.h"

#include "x_adapter_manager.h"
#include "AipstarChannel.h"

CAipstarAdapter::CAipstarAdapter(int nDevId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
{
	m_devHandle = NULL;
	m_status = jo_dev_broken;
	memset(m_remoteIP, 0, sizeof(m_remoteIP));
	memset(m_username, 0, sizeof(m_username));
	memset(m_password, 0, sizeof(m_password));
	m_remotePort = nPort;
	strcpy(m_remoteIP, pAddr);
	strcpy(m_username, pUsername);
	strcpy(m_password, pPassword);

	m_devHandle = TMCC_Init(TMCC_INITTYPE_CONTROL);
	//assert(m_devHandle != NULL);
	Login();
	TMCC_RegisterConnectCallBack(m_devHandle, OnConnectCallBack, this);
	TMCC_SetAutoReConnect(m_devHandle, true);

	J_OS::LOGINFO("CAipstarAdapter::CAipstarAdapter(ip = %s, port = %d)", pAddr, nPort);
}

CAipstarAdapter::~CAipstarAdapter()
{
	if (Logout() == J_OK)
		m_status = jo_dev_broken;

	if (m_devHandle != NULL)
		TMCC_Done(m_devHandle);

	J_OS::LOGINFO("CAipstarAdapter::~CAipstarAdapter()");
}

J_DevStatus CAipstarAdapter::GetStatus() const
{
	return m_status;
}
int CAipstarAdapter::Broken()
{
	return J_OK;
}

int CAipstarAdapter::MakeChannel(const char *pResid, void *&pObj, void *pOwner, int nChannel, int nStream, int nMode)
{
	CAipstarChannel *pChannel = new CAipstarChannel(pResid, pOwner, nChannel, nStream, nMode);
	if (NULL == pChannel)
		return J_MEMORY_ERROR;

	pObj = pChannel;

	return J_OK;
}

int CAipstarAdapter::Relogin()
{
    Logout();
    return Login();
}

int CAipstarAdapter::Login()
{
	tmConnectInfo_t conInfo = {0};
	conInfo.dwSize = sizeof(tmConnectInfo_t);
	strcpy(conInfo.pIp, m_remoteIP);
	conInfo.iPort = m_remotePort;
	strcpy(conInfo.szUser, m_username);
	strcpy(conInfo.szPass, m_password);

	int nRet = TMCC_Connect(m_devHandle, &conInfo, true);
	//assert(nRet == TMCC_ERR_SUCCESS);
	if (nRet == TMCC_ERR_SUCCESS)
    {
        m_status = jo_dev_ready;
    }
    else
    {
        J_OS::LOGINFO("CAipstarAdapter::Login() Login faild");
    }

	return J_OK;
}

int CAipstarAdapter::Logout()
{
	int nRet = TMCC_DisConnect(m_devHandle);
	if (nRet == TMCC_ERR_SUCCESS)
        m_status = jo_dev_broken;

	return J_OK;
}

void CAipstarAdapter::OnConnect(HANDLE hHandle, BOOL bConnect)
{
	printf("connect = %d\n", bConnect);
}
