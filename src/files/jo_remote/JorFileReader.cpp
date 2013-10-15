#include "JorFileReader.h"
#include "x_sdk.h"
#include "x_config.h"
extern "C"
{
#include "x_inet.h"
}

#define RECORD_INTERVAL	(24 * 60 * 60)
#define TIMER_INTERVAL	128
#define RECORD_BUFF_SIZE (1024 * 1024 * 5)

JO_IMPLEMENT_INTERFACE(FileReader, "jorf", CJorFileReader::Maker)

CJorFileReader::CJorFileReader(const char *pResid)
{
	m_recvSocket = NULL;
	m_resid = pResid;
	m_bPaused = false;
	
	m_lastTime = 0;
	m_bRun = false;
	m_buffer = new CRingBuffer(0, RECORD_BUFF_SIZE);
	
	m_bRun = true;
	j_thread_parm parm = {0};
	parm.entry = CJorFileReader::WorkThread;
	parm.data = this;
	m_thread.Create(parm);
}

CJorFileReader::~CJorFileReader()
{
	if (m_bRun)
	{
		m_bRun = false;
		m_thread.Release();
	}
	if (m_buffer)
		delete m_buffer;
	
	if (m_recvSocket != NULL)
	{
		delete m_recvSocket;
		m_recvSocket = NULL;
	}
	CloseFile();
}

int CJorFileReader::GetContext(J_MediaContext *&mediaContext)
{
	return J_OK;
}

int CJorFileReader::GetPacket(char *pBuffer, J_StreamHeader &streamHeader)
{
	TLock(m_locker);
	int nRet = J_OK;
	if (m_bPaused)
	{
		streamHeader.dataLen = 0;
		streamHeader.frameType = jo_media_unknow;
		streamHeader.timeStamp = 0;
		streamHeader.frameNum = 0;
	}
	else
	{
		nRet = m_buffer->PopBuffer(pBuffer, streamHeader);
		if (nRet != J_OK)
		{
			streamHeader.dataLen = 0;
			streamHeader.frameType = jo_media_unknow;
			streamHeader.timeStamp = 0;
			streamHeader.frameNum = 0;
		}
	}
	TUnlock(m_locker);
	return J_OK;
}

int CJorFileReader::Pause()
{
	return J_OK;
}

int CJorFileReader::SetScale(float nScale)
{
	return J_OK;
}

int CJorFileReader::SetTime(j_uint64_t s_time, j_uint64_t e_time)
{
	OpenFile(s_time, e_time);
	return J_OK;
}

int CJorFileReader::SetPosition(int nPos)
{
	return J_OK;
}

int CJorFileReader::GetMediaData(j_uint64_t beginTime, int nIval)
{
	TLock(m_locker);
	m_lastTime += 24*60*60*1000;
	m_cond.Single();
	TUnlock(m_locker);
	
	return J_OK;
}

int CJorFileReader::OpenFile(j_uint64_t s_time, j_uint64_t e_time)
{
	J_DeviceInfo info = {0};
	//if (CManagerFactory::Instance()->GetManager(CXConfig::GetConfigType())->GetDeviceInfo(m_resid.c_str(), info) != J_OK)
	//	return J_INVALID_DEV;
	strcpy(info.devIp, "192.168.1.12");
	info.devPort = 8002;
	
	m_recvSocket = new J_OS::CTCPSocket();
	m_recvSocket->Connect(info.devIp, info.devPort);
	
	if (m_jorHelper.OpenFile(m_recvSocket, m_resid.c_str(), s_time, e_time) != J_OK)
	{
		delete m_recvSocket;
		m_recvSocket = NULL;
		
		return J_INVALID_DEV;
	}
	
	return J_OK;
}

void CJorFileReader::CloseFile()
{
	m_jorHelper.CloseFile(m_recvSocket, m_resid.c_str());
	if (m_recvSocket != NULL)
	{
		delete m_recvSocket;
		m_recvSocket = NULL;
	}
}

void CJorFileReader::OnWork()
{
	int nRet = J_OK;
	J_StreamHeader streamHeader;
	char *pBuffer = new char[1024 * 1024 * 5];
	int nfd = 0;
	while (m_bRun)
	{
		if (m_lastTime == 0)
		{
			TLock(m_mux);
			m_cond.Wait(m_mux);
			//m_jorHelper.ReadFile(m_recvSocket, m_resid.c_str(), 0, 2*60*1000);
			//m_lastTime += 2*60*1000;
			//nfd = m_recvSocket->GetHandle();
			TUnlock(m_mux);
		}
		if (m_buffer->GetIdleLength() != RECORD_BUFF_SIZE)
		{
			j_sleep(10);
			continue;
		}

		TLock(m_locker);
		J_DataHead head = {0};
		int	nLen = m_recvSocket->Read_n((char *)&head, sizeof(head));
		if (nLen < 0)
		{
			J_OS::LOGERROR("CJorFileReader::OnRead recv data error");
			//TUnlock(m_locker);
			//return J_SOCKET_ERROR;
			//未处理
			m_bRun = false;
			TUnlock(m_locker);
			break;
		}
		int nLength = ntohl(head.data_len);
		nLen = m_recvSocket->Read_n(pBuffer, nLength);
		if (nLen > 0)
		{
			int nRet = 0;
			J_StreamHeader streamHeader = {0};
			streamHeader.timeStamp = ntohll(head.time_stamp);
			streamHeader.frameType = ntohl(head.frame_type);
			streamHeader.dataLen = nLength;
			streamHeader.frameNum = ntohl(head.frame_seq);
			if (nRet == J_OK)
			{
				m_buffer->PushBuffer(pBuffer, streamHeader);
				m_lastTime -= 40;
			}
		}
		TUnlock(m_locker);
	}
	delete pBuffer;
}

