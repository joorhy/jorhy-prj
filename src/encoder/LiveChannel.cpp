#include "LiveChannel.h"
#include "LiveStream.h"

CLiveChannel::CLiveChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode)
{
	m_bOpened = false;
	m_nChannel = nChannel;
}

CLiveChannel::~CLiveChannel()
{

}

int CLiveChannel::OpenStream(void *&pObj, CRingBuffer *pRingBuffer)
{
	if (m_bOpened && pObj != NULL)
	{
		(static_cast<CLiveStream *> (pObj))->AddRingBuffer(pRingBuffer);
		return J_OK;
	}

	m_bOpened = true;
	pObj = new CLiveStream(m_resid, m_nChannel);
	(static_cast<CLiveStream *> (pObj))->AddRingBuffer(pRingBuffer);
	(static_cast<CLiveStream *> (pObj))->Startup();

	return J_OK;
}

int CLiveChannel::CloseStream(void *pObj, CRingBuffer *pRingBuffer)
{
	if (!m_bOpened)
		return J_OK;

	CLiveStream *pStream = static_cast<CLiveStream *>(pObj);
	if (pStream == NULL)
		return J_OK;

	if (pStream->RingBufferCount() == 1)
	{
		m_bOpened = false;
		(static_cast<CLiveStream *> (pObj))->Shutdown();
		pStream->DelRingBuffer(pRingBuffer);
		delete (CLiveStream *) pObj;

		return J_NO_REF;
	}

	if (pStream->RingBufferCount() > 0)
		pStream->DelRingBuffer(pRingBuffer);

	return J_OK;
}
