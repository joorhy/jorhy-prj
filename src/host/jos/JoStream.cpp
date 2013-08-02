#include "JoStream.h"

#include "x_socket.h"
#include "x_msg_queue.h"
#include "x_media_msg.h"
#include "x_time.h"
extern "C"
{
#include "x_inet.h"
}

#define RECV_SIZE (1024 * 1024)
CJoStream::CJoStream(void *pTCPSocket, std::string resid)
: m_bStartup(false)
, m_pRecvBuff(NULL)
, m_resid(resid)
{
	m_pTCPSocket = pTCPSocket;
	m_nSocket = ((J_OS::CTCPSocket *)pTCPSocket)->GetHandle();
	if (NULL == m_pRecvBuff)
		m_pRecvBuff = new char[RECV_SIZE];

	J_OS::LOGINFO("CJoStream::CJoStream create this = %d", this);
}

CJoStream::~CJoStream()
{
	if (m_pRecvBuff != NULL)
	{
		delete m_pRecvBuff;
		m_pRecvBuff = NULL;
	}

	J_OS::LOGINFO("CJoStream::~CJoStream destroy this = %d", this);
}

int CJoStream::Startup()
{
	if (m_bStartup)
		return J_OK;

    TLock(m_locker);
    m_bStartup = true;
    JoXAsio->Init();
    JoXAsio->AddUser(m_nSocket, this);
	m_asioData.ioUser = this;
	m_asioData.ioRead.buf = (j_char_t *)&m_dataHead;
	m_asioData.ioRead.bufLen = sizeof(J_DataHead);
	m_asioData.ioRead.whole = true;
	m_asioData.ioRead.finishedLen = 0;
	m_nState = JO_READ_HEAD;
	JoXAsio->Read(m_nSocket, &m_asioData);
    TUnlock(m_locker);
	J_OS::LOGINFO("COnvifStream::Startup Startup this = %d", this);

	return J_OK;
}

int CJoStream::Shutdown()
{
	if (!m_bStartup)
		return J_OK;

    TLock(m_locker);
    m_bStartup = false;
    JoXAsio->DelUser(m_nSocket);
    TUnlock(m_locker);
	J_OS::LOGINFO("CJoStream::Shutdown Shutdown this = %d", this);

	return J_OK;
}

j_result_t CJoStream::OnRead(const J_AsioDataBase *pAsioData, int nRet)
{
    if (!m_bStartup)
    {
        J_OS::LOGINFO("!m_bStartup socket = %d", m_nSocket);
        return J_SOCKET_ERROR;
    }

	j_result_t nResult = J_OK;
	J_StreamHeader streamHeader = {0};
    TLock(m_locker);
	switch (m_nState)
	{
		case JO_READ_HEAD:
			m_asioData.ioRead.bufLen = ntohl(m_dataHead.data_len);
			m_nState = JO_READ_DATA;
			m_asioData.ioRead.buf = m_pRecvBuff;
			break;
		case JO_READ_DATA:
			m_asioData.ioRead.bufLen = sizeof(J_DataHead);
			streamHeader.timeStamp = JoTime->GetLocalTime(0);//ntohll(head.time_stamp);
			streamHeader.frameType = ntohl(m_dataHead.frame_type);
			streamHeader.dataLen = ntohl(m_dataHead.data_len);;
			streamHeader.frameNum = ntohl(m_dataHead.frame_seq);
			if (nResult == J_OK)
			{
				TLock(m_vecLocker);
				std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
				for (; it != m_vecRingBuffer.end(); it++)
				{
					(*it)->PushBuffer(m_pRecvBuff, streamHeader);
				}
				TUnlock(m_vecLocker);
			}
			m_nState = JO_READ_HEAD;
			m_asioData.ioRead.buf = (j_char_t *)&m_dataHead;
			break;
	}
	m_asioData.ioRead.whole = true;
	m_asioData.ioRead.finishedLen = 0;
	JoXAsio->Read(m_nSocket, &m_asioData);
	
	TUnlock(m_locker);
	return J_OK;
}

j_result_t CJoStream::OnBroken(const J_AsioDataBase *pAsioData, int nRet)
{
    J_OS::LOGINFO("CJoStream::OnBroken");
    TLock(m_locker);
    J_StreamHeader streamHeader = {0};
    streamHeader.frameType = jo_media_broken;
    streamHeader.timeStamp = JoTime->GetLocalTime(0);

    TLock(m_vecLocker);
    std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
    for (; it != m_vecRingBuffer.end(); it++)
    {
        (*it)->PushBuffer(m_pRecvBuff, streamHeader);
    }
    TUnlock(m_vecLocker);

    TUnlock(m_locker);
	return J_OK;
}
