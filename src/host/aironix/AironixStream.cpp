#include "AironixStream.h"
//#include "j_type.h"

CAironixStream::CAironixStream(std::string resid, int nChannel)
{
	m_bStartup = false;
}

CAironixStream::~CAironixStream()
{

}

int CAironixStream::Startup()
{
	if (m_bStartup)
		return J_OK;
	m_bStartup = true;

	return J_OK;
}

int CAironixStream::Shutdown()
{
	if (!m_bStartup)
		return J_OK;
	m_bStartup = false;

	return J_OK;
}

void CAironixStream::OnRecv(LONG lLiveHandle, NET_SDK_FRAME_INFO frameInfo, BYTE *pBuffer)
{
	if (m_bStartup)
	{
		J_StreamHeader streamHeader;
		streamHeader.dataLen = frameInfo.length;
		streamHeader.timeStamp = CTime::Instance()->GetLocalTime(0);
		//J_OS::LOGINFO("streamId = %d", frameInfo.streamID);
		if (frameInfo.frameType == 1)
		{
			streamHeader.frameType = (frameInfo.keyFrame ? J_VideoIFrame : J_VideoPFrame);
		}
		else if (frameInfo.frameType == 2)
		{
			streamHeader.frameType =  J_AudioFrame;
		}
		else
		{
			return;
		}

		TLock(m_vecLocker);
		std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
		for (; it != m_vecRingBuffer.end(); it++)
		{
			(*it)->PushBuffer((const char *)pBuffer, streamHeader);
		}
		TUnlock(m_vecLocker);
	}
}
