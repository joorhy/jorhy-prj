#include "LiveAdapter.h"

#include "AdapterManager.h"
#include "LiveChannel.h"

CLiveAdapter::CLiveAdapter(int nDevId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
{
	m_status = J_DevReady;
	J_OS::LOGINFO("CLiveAdapter::CLiveAdapter()");
}

CLiveAdapter::~CLiveAdapter()
{
	J_OS::LOGINFO("CLiveAdapter::~CLiveAdapter()");
}

J_DevStatus CLiveAdapter::GetStatus() const
{
	return m_status;
}
int CLiveAdapter::Broken()
{
	return J_OK;
}

int CLiveAdapter::MakeChannel(const char *pResid, void *&pObj, void *pOwner, int nChannel, int nStream, int nMode)
{
	CLiveChannel *pChannel = new CLiveChannel(pResid, pOwner, nChannel, nStream, nMode);
	if (NULL == pChannel)
		return J_MEMORY_ERROR;

	pObj = pChannel;

	return J_OK;
}
