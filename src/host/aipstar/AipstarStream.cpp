#include "AipstarStream.h"

CAipstarStream::CAipstarStream(std::string resid, int nChannel)
{
	m_bStartup = false;
}

CAipstarStream::~CAipstarStream()
{

}

int CAipstarStream::Startup()
{
	if (m_bStartup)
		return J_OK;
	m_bStartup = true;

	return J_OK;
}

int CAipstarStream::Shutdown()
{
	if (!m_bStartup)
		return J_OK;
	m_bStartup = false;

	return J_OK;
}

void CAipstarStream::OnRecv(HANDLE hHandle, tmRealStreamInfo_t *streamInfo)
{
	if (m_bStartup)
	{
		J_StreamHeader streamHeader;
		streamHeader.dataLen = streamInfo->iBufferSize - 8;
		streamHeader.timeStamp = CTime::Instance()->GetLocalTime(0);
		if (streamInfo->byFrameType == 0)
		{
			streamHeader.frameType = (streamInfo->byKeyFrame ? jo_video_i_frame : jo_video_p_frame);
		}
		else if (streamInfo->byFrameType == 1)
		{
			streamHeader.frameType =  jo_audio_frame;
			//for (int i=0; i<32; i++)
			//{
			//	printf("%02X ", *(unsigned char *)(streamInfo->pBuffer + i));
			//}
		}
		else
		{
			return;
		}

		TLock(m_vecLocker);
		std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
		for (; it != m_vecRingBuffer.end(); it++)
		{
			(*it)->PushBuffer((const char *)streamInfo->pBuffer + 8, streamHeader);
		}
		TUnlock(m_vecLocker);
	}
}
