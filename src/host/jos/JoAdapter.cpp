#include "JoAdapter.h"
#include "JoChannel.h"

JO_IMPLEMENT_INTERFACE(Adapter, "joh", CJoAdapter::Maker)

CJoAdapter::CJoAdapter(int nDvrId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
{
	memset(m_remoteIP, 0, sizeof(m_remoteIP));
	memset(m_username, 0, sizeof(m_username));
	memset(m_password, 0, sizeof(m_password));

	m_remotePort = nPort;
	strcpy(m_remoteIP, pAddr);
	strcpy(m_username, pUsername);
	strcpy(m_password, pPassword);

	m_status = jo_dev_ready;

	J_OS::LOGINFO("CJoAdapter::CJoAdapter(ip = %s, port = %d)", pAddr, nPort);
}

CJoAdapter::~CJoAdapter()
{

}

J_DevStatus CJoAdapter::GetStatus() const
{
	return m_status;
}

int CJoAdapter::Broken()
{
    m_status = jo_dev_broken;
	return J_OK;
}

int CJoAdapter::MakeChannel(const char *pResid, void *&pObj, void *pOwner, int nChannel, int nStream, int nMode)
{
	CJoChannel *pChannel = new CJoChannel(pResid, pOwner, nChannel, nStream,
			nMode);
	if (NULL == pChannel)
		return J_MEMORY_ERROR;

	pObj = pChannel;

	return J_OK;
}
