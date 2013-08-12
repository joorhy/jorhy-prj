#include "RealMediaObj.h"
#include "x_filter_factory.h"
#include "x_socket.h"
#include "x_time.h"
#include "x_thread_pool.h"

#define CLIENT_BUFFER_SIZE (2 * 1024 * 1024)
#define MAX_SEND_BUFF	8100

CRealMediaObj::CRealMediaObj(j_socket_t nSocket, int nStreamType, J_Obj *pObj)
{
	m_nSocket = nSocket;
	m_nStreamType = nStreamType;
	m_pRingBuffer = NULL;
	m_bStart = false;
	m_pDataBuff = new char[CLIENT_BUFFER_SIZE];
	m_pConvetBuff = new char[CLIENT_BUFFER_SIZE];
	m_sendSocket.Init(nSocket);

	m_pObj = pObj;
	m_taskNum = 0;
	m_nextFrameTime = 0;
	m_lastFrameTime = 0;
	m_lastFrameNum = 0;

	J_OS::LOGINFO("CRealMediaObj::CRealMediaObj created socket =  %d", m_nSocket.sock);
}

CRealMediaObj::~CRealMediaObj()
{
	if (m_pDataBuff != NULL)
		delete m_pDataBuff;
	
	if (m_pConvetBuff != NULL)
		delete m_pConvetBuff;

	J_OS::LOGINFO("CRealMediaObj::~CRealMediaObj destroyed socket =  %d", m_nSocket.sock);
}

int CRealMediaObj::Process(J_AsioDataBase &asioData)
{
	int nRet = J_OK;
	J_CommandFilter *videoCommand = dynamic_cast<J_CommandFilter *>(m_pObj);
	if (videoCommand != NULL)
	{
		if (asioData.ioCall == J_AsioDataBase::j_read_e)
		{
			m_resid = videoCommand->GetResid();
			switch (videoCommand->GetCommandType())
			{
			case jo_start_real:
				nRet = StartVideo();
				J_OS::LOGINFO("CRealMediaObj::Process StartVideo socket =  %d ret = %d", m_nSocket.sock, nRet);
				break;
			case jo_stop_real:
			{
				nRet = StopVideo();
				J_OS::LOGINFO("CRealMediaObj::Process StopVideo socket =  %d ret = %d", m_nSocket.sock, nRet);
				break;
			}
			default:
				J_OS::LOGINFO("CRealMediaObj::Process CommandType unkown type =  %d", videoCommand->GetCommandType());
				break;
			}
		}
		else if (asioData.ioCall == J_AsioDataBase::j_write_e)
		{
			if (!m_bStart)
			{
				J_OS::LOGINFO("CRealMediaObj::Process !m_bStart socket = %d", m_nSocket.sock);
				return J_OK;
			}
			return OnWriteData(asioData);
		}
	}

	return nRet;
}

int CRealMediaObj::OnWriteData(J_AsioDataBase &asioData)
{
	int nRet = J_OK;
	J_RequestFilter *pAccess = dynamic_cast<J_RequestFilter *>(m_pObj);
	//while (true)
	{
		memset(&m_streamHeader, 0, sizeof(m_streamHeader));
		nRet = m_pRingBuffer->PopBuffer(m_pDataBuff, m_streamHeader);
		if (nRet == J_OK && m_streamHeader.dataLen > 0)
		{
			int nDataLen = 0;
			pAccess->Convert(m_pDataBuff, m_streamHeader, m_pConvetBuff, nDataLen);
			if (nDataLen > 0)
			{
				int nRet = 0;
				if (m_nextFrameTime <= 40)
				{
					m_lastFrameTime = m_streamHeader.timeStamp;
					if (m_streamHeader.frameType == jo_video_i_frame ||
						((m_streamHeader.frameType == jo_video_p_frame) && (m_streamHeader.frameNum == ++m_lastFrameNum)))
					{
						if (m_streamHeader.frameType == jo_video_i_frame)
							m_lastFrameNum = m_streamHeader.frameNum;
							
						m_nextFrameTime = JoTime->GetLocalTime(0);
						asioData.ioWrite.buf = m_pConvetBuff;
						asioData.ioWrite.bufLen = nDataLen;
						asioData.ioWrite.whole = true;
						m_nextFrameTime = JoTime->GetLocalTime(0) - m_nextFrameTime;
						//break;
					}
					else
					{
						m_nextFrameTime = 0;
						asioData.ioWrite.buf = NULL;
						asioData.ioWrite.bufLen = 0;
						asioData.ioWrite.whole = false;
						//continue;
					}
				}
				else
				{
					m_nextFrameTime -= m_streamHeader.timeStamp - m_lastFrameTime;
					asioData.ioWrite.buf = NULL;
					asioData.ioWrite.bufLen = 0;
					asioData.ioWrite.whole = false;
					//continue;
				}
			}
			else
			{
				asioData.ioWrite.buf = NULL;
				asioData.ioWrite.bufLen = 0;
				asioData.ioWrite.whole = false;
				return J_OK;
			}
		}
		else if (nRet == J_OK && m_streamHeader.frameType == jo_media_broken)
		{
			J_OS::LOGERROR("CRealMediaObj::OnWrite Source Broken");
			return J_SOCKET_ERROR;
		}
		else
		{
			asioData.ioWrite.buf = NULL;
			asioData.ioWrite.bufLen = 0;
			asioData.ioWrite.whole = false;
			//usleep(1);
			return J_OK;
		}
	}
	
	return nRet;
}

int CRealMediaObj::Clearn()
{
	StopVideo();
	if (m_pObj)
	{
		JoFilterFactory->DelFilter(m_nSocket);
		m_pObj = NULL;
	}
	J_OS::LOGINFO("CRealMediaObj::OnBroken socket = %d broken", m_nSocket.sock);

	return J_OK;
}

int CRealMediaObj::Run(bool bFlag)
{
	m_bStart = bFlag;

	return J_OK;
}

int CRealMediaObj::StartVideo()
{
	int nRet = JoAdapterManager->StartVideo(m_resid.c_str(), m_nStreamType, m_nSocket);
	if (nRet < 0)
	{
		J_OS::LOGINFO("CRealMediaObj::StartVideo StartVideo error ret = %d", nRet);
		return nRet;
	}

	nRet = JoAdapterManager->GetRingBuffer(m_resid.c_str(), m_nStreamType, m_nSocket, m_pRingBuffer);
	if (nRet < 0)
	{
		J_OS::LOGINFO("CVideoClient::StartVideo GetRingBuffer error ret = %d", nRet);
		return nRet;
	}
	//m_bStart = true;

	J_OS::LOGINFO("CRealMediaObj::StartVideo socket =  %d start", m_nSocket.sock);

	return J_OK;
}

int CRealMediaObj::StopVideo()
{
	if (m_bStart)
	{
		m_bStart = false;
		int nRet = JoAdapterManager->StopVideo(m_resid.c_str(), m_nStreamType, m_nSocket);
		if (nRet < 0)
		{
			J_OS::LOGINFO("CRealMediaObj::StopVideo StopVideo error ret = %d", nRet);
			return nRet;
		}

		J_OS::LOGINFO("CRealMediaObj::StopVideo socket =  %d stop", m_nSocket.sock);
	}

	return J_OK;
}

const char *CRealMediaObj::GetResid() const
{
	return m_resid.c_str();
}
