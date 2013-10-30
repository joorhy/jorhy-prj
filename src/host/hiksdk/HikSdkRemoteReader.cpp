#include "HikSdkRemoteReader.h"

extern void CovertTime(const time_t &t, NET_DVR_TIME  &nvrTime);
extern void CovertTime2(time_t &t, const NET_DVR_TIME  &nvrTime);
#define RECV_SIZE (1024 * 1024)
CHikRemoteReader::CHikRemoteReader(J_Obj *pOwner, j_int32_t nChanne)
{
	m_pAdapter = dynamic_cast<CHikSdkAdapter *>(pOwner);
	m_nChannel = nChanne;
	m_parser.Init();
	m_pDataBuff = new char[RECV_SIZE];
}

CHikRemoteReader::~CHikRemoteReader()
{
	 NET_DVR_StopPlayBack(m_hStream);

	m_parser.Deinit();
	if (m_pDataBuff != NULL)
	{
		delete m_pDataBuff;
		m_pDataBuff = NULL;
	}
}

j_result_t CHikRemoteReader::GetContext(J_MediaContext *&mediaContext)
{
	return J_OK;
}

j_result_t CHikRemoteReader::GetPacket(j_char_t *pBuffer, J_StreamHeader &streamHeader)
{
	m_ringBuffer.PopBuffer(pBuffer, streamHeader);
	return J_OK;
}

j_result_t CHikRemoteReader::Pause()
{
	return J_OK;
}

j_result_t CHikRemoteReader::SetScale(float nScale)
{
	return J_OK;
}

j_result_t CHikRemoteReader::SetTime(j_uint64_t s_time, j_uint64_t e_time)
{
	NET_DVR_VOD_PARA vodInfo = {0};
	vodInfo.dwSize = sizeof(NET_DVR_VOD_PARA);
	CovertTime(s_time, vodInfo.struBeginTime);
	CovertTime(s_time + 600, vodInfo.struEndTime);
	vodInfo.hWnd = NULL;
	m_hStream = NET_DVR_PlayBackByTime_V40(m_pAdapter->GetUserId(), &vodInfo);
	if (m_hStream == -1)
	{
		//m_pAdapter->Broken();
		J_OS::LOGINFO("CHikRemoteReader::SetTime error, ret = %d", NET_DVR_GetLastError());
		return J_STREAM_ERROR;
	}
	NET_DVR_SetPlayDataCallBack_V40(m_hStream, CHikRemoteReader::VodDataCallback, this);
	NET_DVR_PlayBackControl_V40(m_hStream, NET_DVR_PLAYSTART);

	return J_OK;
}

j_result_t CHikRemoteReader::SetPosition(j_int32_t nPos)
{
	return J_OK;
}

j_result_t CHikRemoteReader::GetMediaData(j_uint64_t beginTime, j_int32_t nIval)
{
	return J_OK;
}

void CHikRemoteReader::OnRecvData(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize)
{
	if (dwDataType == 2)
	{
		J_StreamHeader streamHeader;
		m_parser.InputData((const char *)pBuffer, dwBufSize);
		j_result_t nResult = m_parser.GetOnePacket(m_pDataBuff, streamHeader);
		if (nResult == J_OK)
		{
			m_ringBuffer.PushBuffer(m_pDataBuff, streamHeader);
		}
	}
}