#include "RealPlayObj.h"
#include "x_player_factory.h"
#include "x_time.h"

#define CLIENT_BUFFER_SIZE (2 * 1024 * 1024)

CRealPlayObj::CRealPlayObj(int nStreamId, const char *pPlayerType, int nStreamType, const char *pResid)
{
	m_nSocket = nStreamId;
	m_nStreamType = nStreamType;

	m_bStart = false;
	m_pDataBuff = new char[CLIENT_BUFFER_SIZE];
	//m_pConvetBuff = new char[CLIENT_BUFFER_SIZE];

	m_nextFrameTime = 0;
	m_lastFrameTime = 0;
	m_lastFrameNum = 0;

	m_resid = pResid;
	m_playerType = pPlayerType;
}

CRealPlayObj::~CRealPlayObj()
{
	if (m_pDataBuff != NULL)
		delete m_pDataBuff;

	//if (m_pConvetBuff != NULL)
	//	delete m_pConvetBuff;
}

j_result_t CRealPlayObj::PlayMedia(j_wnd_t hWnd, j_int32_t nDevid)
{
	StartVideo(nDevid);
	JoPlayerFactory->GetPlayer(m_nSocket, m_playerType.c_str())->Play(hWnd);
	
	return J_OK;
}

j_result_t CRealPlayObj::StopMedia(j_int32_t nDevid)
{
	JoPlayerFactory->GetPlayer(m_nSocket, m_playerType.c_str())->Stop();
	StopVideo(nDevid);

	return J_OK;
}

j_result_t CRealPlayObj::AspectRatio(j_int32_t nWidth, j_int32_t nHeight)
{
	JoPlayerFactory->GetPlayer(m_nSocket, m_playerType.c_str())->AspectRatio(nWidth, nHeight);
	return J_OK;
}

j_result_t CRealPlayObj::ProcessMedia()
{
	int nRet = J_OK;
	if (!m_bStart)
		return nRet;

	memset(&m_streamHeader, 0, sizeof(m_streamHeader));
	nRet = m_pRingBuffer->PopBuffer(m_pDataBuff, m_streamHeader);
	if (nRet == J_OK && m_streamHeader.dataLen > 0)
	{
		if (m_nextFrameTime <= 40)
		{
			m_lastFrameTime = m_streamHeader.timeStamp;
			if (m_streamHeader.frameType == jo_video_i_frame ||
				((m_streamHeader.frameType == jo_video_p_frame) && (m_streamHeader.frameNum == ++m_lastFrameNum)))
			{
				if (m_streamHeader.frameType == jo_video_i_frame)
					m_lastFrameNum = m_streamHeader.frameNum;

				m_nextFrameTime = JoTime->GetLocalTime(0);
				JoPlayerFactory->GetPlayer(m_nSocket, m_playerType.c_str())->InputData(m_pDataBuff, m_streamHeader);
				m_nextFrameTime = JoTime->GetLocalTime(0) - m_nextFrameTime;
			}
			else
			{
				return J_OK;
			}
		}
		else
		{
			return J_OK;
		}
	}
	else if (nRet == J_OK && m_streamHeader.frameType == jo_media_broken)
	{
		J_OS::LOGERROR("CRealPlayObj::ProcessMedia() Source Broken");
		return J_SOCKET_ERROR;
	}
	else
	{
		return J_OK;
	}

	return nRet;
}

j_result_t CRealPlayObj::StartVideo(j_int32_t nDevid)
{
	int nRet = JoAdapterManager->StartVideo(m_resid.c_str(), m_nStreamType, m_nSocket, nDevid);
	if (nRet < 0)
	{
		J_OS::LOGINFO("CRealPlayObj::StartVideo StartVideo error ret = %d", nRet);
		return nRet;
	}

	nRet = JoAdapterManager->GetRingBuffer(m_resid.c_str(), m_nStreamType, m_nSocket, m_pRingBuffer);
	if (nRet < 0)
	{
		J_OS::LOGINFO("CRealPlayObj::StartVideo GetRingBuffer error ret = %d", nRet);
		return nRet;
	}
	m_bStart = true;
	J_OS::LOGINFO("CRealPlayObj::StartVideo socket =  %d start", m_nSocket.sock);
	return J_OK;
}

j_result_t CRealPlayObj::StopVideo(j_int32_t nDevid)
{
	if (m_bStart)
	{
		m_bStart = false;
		int nRet = JoAdapterManager->StopVideo(m_resid.c_str(), m_nStreamType, m_nSocket, nDevid);
		if (nRet < 0)
		{
			J_OS::LOGINFO("CRealPlayObj::StopVideo StopVideo error ret = %d", nRet);
			return nRet;
		}

		J_OS::LOGINFO("CRealPlayObj::StopVideo socket =  %d stop", m_nSocket.sock);
	}
	return J_OK;
}
