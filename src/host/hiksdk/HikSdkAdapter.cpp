#include "HikSdkAdapter.h"
#include "HikSdkChannel.h"
#include "HikSdkType.h"
#include "x_adapter_manager.h"

JO_IMPLEMENT_INTERFACE(Adapter, "hiksdk", CHikSdkAdapter::Maker)

CHikSdkAdapter::CHikSdkAdapter(int nDvrId, const char *pAddr, int nPort,
		const char *pUsername, const char *pPassword)
{
	if (!NET_DVR_Init())
		J_OS::LOGINFO("CHikSdkAdapter NET_DVR_Init Error");
	
	NET_DVR_DEVICEINFO_V30 devInfo = {0};
	m_nUserId = NET_DVR_Login_V30((char *)pAddr, nPort, (char *)pUsername, (char *)pPassword, &devInfo);
	if (m_nUserId == -1)
		J_OS::LOGINFO("CHikSdkAdapter NET_DVR_Login_V30 Error");
		
	J_OS::LOGINFO("CHikSdkAdapter::CHikSdkAdapter(ip = %s, port = %d)", pAddr, nPort);
}

CHikSdkAdapter::~CHikSdkAdapter()
{
	if (!NET_DVR_Cleanup())
		J_OS::LOGINFO("CHikSdkAdapter NET_DVR_Cleanup Error");
		
	NET_DVR_Logout(m_nUserId);
		
	J_OS::LOGINFO("CHikSdkAdapter::~CHikSdkAdapter()");
}

///J_VideoAdapter
J_DevStatus CHikSdkAdapter::GetStatus() const
{
	return jo_dev_ready;//m_status;
}

j_result_t CHikSdkAdapter::Broken()
{
	return J_OK;
}

j_result_t CHikSdkAdapter::MakeChannel(const char *pResid, J_Obj *&pObj, J_Obj *pOwner,
		int nChannel, int nStream, int nMode)
{
	CHikSdkChannel *pChannel = new CHikSdkChannel(pResid, pOwner, nChannel, nStream, nMode);
	if (NULL == pChannel)
		return J_MEMORY_ERROR;

	pObj = pChannel;

	return J_OK;
}