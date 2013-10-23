#include "JoAdapter.h"
#include "JoChannel.h"

JO_IMPLEMENT_INTERFACE(Adapter, "joh", CJoAdapter::Maker)

CJoAdapter::CJoAdapter(int nDvrId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
{
	memset (&m_devInfo, 0, sizeof(J_DeviceInfo));

	m_devInfo.devPort = nPort;
	m_devInfo.devId = nDvrId;
	strcpy(m_devInfo.devIp, pAddr);
	strcpy(m_devInfo.userName, pUsername);
	strcpy(m_devInfo.passWd, pPassword);
	strcpy(m_devInfo.devType, "joh");
	m_devInfo.devStatus = jo_dev_ready;

	J_OS::LOGINFO("CJoAdapter::CJoAdapter(ip = %s, port = %d)", pAddr, nPort);
}

CJoAdapter::~CJoAdapter()
{

}

j_result_t CJoAdapter::GetDevInfo(J_DeviceInfo &info)
{
	
	memcpy(&info, &m_devInfo, sizeof(J_DeviceInfo));
	return J_OK;
}

J_DevStatus CJoAdapter::GetStatus() const
{
	return (J_DevStatus)m_devInfo.devStatus;
}

int CJoAdapter::Broken()
{
    m_devInfo.devStatus = jo_dev_broken;
	return J_OK;
}

int CJoAdapter::MakeChannel(const char *pResid, J_Obj *&pObj, J_Obj *pOwner, int nChannel, int nStream, int nMode)
{
	CJoChannel *pChannel = new CJoChannel(pResid, pOwner, nChannel, nStream,
			nMode);
	if (NULL == pChannel)
		return J_MEMORY_ERROR;

	pObj = pChannel;

	return J_OK;
}
