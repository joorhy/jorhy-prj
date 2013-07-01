#include "SonyAdapter.h"
#include "SonyChannel.h"

JO_IMPLEMENT_INTERFACE(Adapter, "sony", CSonyAdapter::Maker)

CSonyAdapter::CSonyAdapter(int nDvrId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
{
	memset(m_remoteIP, 0, sizeof(m_remoteIP));
	memset(m_username, 0, sizeof(m_username));
	memset(m_password, 0, sizeof(m_password));

	m_remotePort = nPort;
	strcpy(m_remoteIP, pAddr);
	strcpy(m_username, pUsername);
	strcpy(m_password, pPassword);

	m_status = jo_dev_broken;
	m_ping.SetAddr(m_remoteIP);
	UserExchange();
    //定时检测设备状态
	m_timer.Create(5 * 1000, CSonyAdapter::OnTimer, this);

	J_OS::LOGINFO("CSonyAdapter::CSonyAdapter(ip = %s, port = %d)", pAddr, nPort);
}

CSonyAdapter::~CSonyAdapter()
{
    m_timer.Destroy();
}

J_DevStatus CSonyAdapter::GetStatus() const
{
	return m_status;
}

int CSonyAdapter::Broken()
{
    m_status = jo_dev_broken;
	return J_OK;
}

int CSonyAdapter::MakeChannel(const char *pResid, void *&pObj, void *pOwner, int nChannel, int nStream, int nMode)
{
	CSonyChannel *pChannel = new CSonyChannel(pResid, pOwner, nChannel, nStream,
			nMode);
	if (NULL == pChannel)
		return J_MEMORY_ERROR;

	pObj = pChannel;

	return J_OK;
}

void CSonyAdapter::UserExchange()
{
	if (m_ping.SendPacket() < 0 || m_ping.RecvPacket() < 0)
	{
		m_status = jo_dev_broken;
		return;
	}
	m_status = jo_dev_ready;
}
