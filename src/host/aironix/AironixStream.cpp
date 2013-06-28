#include "AironixStream.h"
//#include "j_type.h"

CAironixStream::CAironixStream(j_string_t resid, j_int32_t nChannel)
{
	m_bStartup = false;
	m_frameNum = 0;
}

CAironixStream::~CAironixStream()
{

}

j_result_t CAironixStream::Startup()
{
	if (m_bStartup)
		return J_OK;
	m_bStartup = true;

	return J_OK;
}

j_result_t CAironixStream::Shutdown()
{
	if (!m_bStartup)
		return J_OK;
	m_bStartup = false;

	return J_OK;
}

j_void_t CAironixStream::OnRecv(LONG lLiveHandle, NET_SDK_FRAME_INFO frameInfo, BYTE *pBuffer)
{
	if (m_bStartup)
	{
		J_StreamHeader streamHeader;
		streamHeader.dataLen = frameInfo.length;
		streamHeader.timeStamp = SingletonTmpl<CTime>::Instance()->GetLocalTime(0);
		//J_OS::LOGINFO("streamId = %d", frameInfo.streamID);
		if (frameInfo.frameType == 1)
		{
			streamHeader.frameType = (frameInfo.keyFrame ? jo_video_i_frame : jo_video_p_frame);
			streamHeader.frameNum = m_frameNum++;
			m_frameNum %= 0xFFFFFFFF;
		}
		else if (frameInfo.frameType == 2)
		{
			streamHeader.frameType =  jo_audio_frame;
		}
		else
		{
			return;
		}

		TLock(m_vecLocker);
		j_vec_buffer_t::iterator it = m_vecRingBuffer.begin();
		for (; it != m_vecRingBuffer.end(); it++)
		{
			(*it)->PushBuffer((const char *)pBuffer, streamHeader);
		}
		TUnlock(m_vecLocker);
	}
}
