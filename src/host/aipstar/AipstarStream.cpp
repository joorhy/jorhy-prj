#include "AipstarStream.h"

CAipstarStream::CAipstarStream(j_string_t resid, j_int32_t nChannel)
{
	m_bStartup = false;
	m_frameNum = 0;
}

CAipstarStream::~CAipstarStream()
{

}

j_result_t CAipstarStream::Startup()
{
	if (m_bStartup)
		return J_OK;
	m_bStartup = true;

	return J_OK;
}

j_result_t CAipstarStream::Shutdown()
{
	if (!m_bStartup)
		return J_OK;
	m_bStartup = false;

	return J_OK;
}

j_void_t CAipstarStream::OnRecv(HANDLE hHandle, tmRealStreamInfo_t *streamInfo)
{
	if (m_bStartup)
	{
		J_StreamHeader streamHeader = {0};
		streamHeader.dataLen = streamInfo->iBufferSize - 8;
		streamHeader.timeStamp = CTime::Instance()->GetLocalTime(0);
		if (streamInfo->byFrameType == 0)
		{
			streamHeader.frameType = (streamInfo->byKeyFrame ? jo_video_i_frame : jo_video_p_frame);
			streamHeader.frameNum = m_frameNum++;
			m_frameNum %= 0xFFFFFFFF;
		}
		else if (streamInfo->byFrameType == 1)
		{
			streamHeader.frameType =  jo_audio_frame;
		}
		else
		{
			J_OS::LOGINFO("CAipstarStream::OnRecv Data type");
			return;
		}
		//J_OS::LOGINFO("CAipstarStream::OnRecv Data type = %d", streamInfo->byFrameType);
		TLock(m_vecLocker);
		j_vec_buffer_t::iterator it = m_vecRingBuffer.begin();
		for (; it != m_vecRingBuffer.end(); it++)
		{
			(*it)->PushBuffer((const char *)streamInfo->pBuffer + 8, streamHeader);
		}
		TUnlock(m_vecLocker);
	}
}

int CAipstarStream::Broken()
{
	TLock(m_vecLocker);
	J_StreamHeader streamHeader = {0};
	streamHeader.frameType = jo_media_broken;
	j_vec_buffer_t::iterator it = m_vecRingBuffer.begin();
	for (; it != m_vecRingBuffer.end(); it++)
	{
		(*it)->PushBuffer(NULL, streamHeader);
	}
	TUnlock(m_vecLocker);
	return J_OK;
}
