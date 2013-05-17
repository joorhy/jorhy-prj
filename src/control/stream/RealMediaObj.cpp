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

	J_OS::LOGINFO("CRealMediaObj::CRealMediaObj created socket =  %d", m_nSocket);
}

CRealMediaObj::~CRealMediaObj()
{
	if (m_pDataBuff != NULL)
		delete m_pDataBuff;

	J_OS::LOGINFO("CRealMediaObj::~CRealMediaObj destroyed socket =  %d", m_nSocket);
}

int CRealMediaObj::Process(int nIoType)
{
	int nRet = J_OK;
	J_CommandFilter *videoCommand = dynamic_cast<J_CommandFilter *>(m_pObj);
	if (videoCommand != NULL)
	{
		if (nIoType == jo_io_read)
		{
			m_resid = videoCommand->GetResid();
			switch (videoCommand->GetCommandType())
			{
			case jo_start_real:
				nRet = StartVideo();
				J_OS::LOGINFO("CRealMediaObj::Process StartVideo socket =  %d ret = %d", m_nSocket, nRet);
				break;
			case jo_stop_real:
			{
				nRet = StopVideo();
				J_OS::LOGINFO("CRealMediaObj::Process StopVideo socket =  %d ret = %d", m_nSocket, nRet);
				break;
			}
			default:
				J_OS::LOGINFO("CRealMediaObj::Process CommandType unkown type =  %d", videoCommand->GetCommandType());
				break;
			}
		}
		else if (nIoType == jo_io_write)
		{
			if (!m_bStart)
			{
				J_OS::LOGINFO("CRealMediaObj::Process !m_bStart socket = %d", m_nSocket);
				return J_OK;
			}
			
			/*TLock(m_locker);
			if (m_taskNum == 0)
			{
				CRealTask * pTask = new CRealTask;
				pTask->m_pParam = this;
				CThreadPool::Instance()->AddTask(pTask);
				++m_taskNum;
			}
			TUnlock(m_locker);*/
			return OnWriteData();
		}
	}

	return nRet;
}

int CRealMediaObj::OnWriteData()
{
	int nRet = J_OK;
	J_RequestFilter *pAccess = dynamic_cast<J_RequestFilter *>(m_pObj);
	while (true)
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
							
						m_nextFrameTime = CTime::Instance()->GetLocalTime(0);
						if ((nRet = m_sendSocket.Write_n(m_pConvetBuff, (uint32_t)nDataLen)) < 0)
						{
							J_OS::LOGERROR("CRealMediaObj::OnWrite Data error");
							return J_SOCKET_ERROR;
						}
						m_nextFrameTime = CTime::Instance()->GetLocalTime(0) - m_nextFrameTime;
						//J_OS::LOGINFO("m_nextFrameTime = %d", m_nextFrameTime);
						break;
					}
					else
					{
						m_nextFrameTime -= 40;
						continue;
					}
				}
				else
				{
					m_nextFrameTime -= m_streamHeader.timeStamp - m_lastFrameTime;
					//return J_OK;
					continue;
				}
			}
			else
			{
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
			usleep(1);
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
		CFilterFactory::Instance()->DelFilter(m_nSocket);
		m_pObj = NULL;
	}
	J_OS::LOGINFO("CRealMediaObj::OnBroken socket = %d broken", m_nSocket);

	return J_OK;
}

int CRealMediaObj::Run(bool bFlag)
{
	m_bStart = bFlag;

	return J_OK;
}

int CRealMediaObj::StartVideo()
{
	int nRet = CAdapterManager::Instance()->StartVideo(m_resid.c_str(), m_nStreamType, m_nSocket);
	if (nRet < 0)
	{
		J_OS::LOGINFO("CRealMediaObj::StartVideo StartVideo error ret = %d", nRet);
		return nRet;
	}

	nRet = CAdapterManager::Instance()->GetRingBuffer(m_resid.c_str(), m_nStreamType, m_nSocket, m_pRingBuffer);
	if (nRet < 0)
	{
		J_OS::LOGINFO("CVideoClient::StartVideo GetRingBuffer error ret = %d", nRet);
		return nRet;
	}
	//m_bStart = true;

	J_OS::LOGINFO("CRealMediaObj::StartVideo socket =  %d start", m_nSocket);

	return J_OK;
}

int CRealMediaObj::StopVideo()
{
	if (m_bStart)
	{
		m_bStart = false;
		int nRet = CAdapterManager::Instance()->StopVideo(m_resid.c_str(), m_nStreamType, m_nSocket);
		if (nRet < 0)
		{
			J_OS::LOGINFO("CRealMediaObj::StopVideo StopVideo error ret = %d", nRet);
			return nRet;
		}

		J_OS::LOGINFO("CRealMediaObj::StopVideo socket =  %d stop", m_nSocket);
	}

	return J_OK;
}

const char *CRealMediaObj::GetResid() const
{
	return m_resid.c_str();
}
