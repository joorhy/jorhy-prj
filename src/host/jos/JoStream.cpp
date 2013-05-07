#include "JoStream.h"

#include "x_socket.h"
#include "x_msg_queue.h"
#include "x_media_msg.h"
#include "x_time.h"

#define RECV_SIZE (1024 * 1024)
CJoStream::CJoStream(void *pTCPSocket, std::string resid)
: m_nSocket(0)
, m_bStartup(false)
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
    CRdAsio::Instance()->Init();
    CRdAsio::Instance()->AddUser(m_nSocket, this);
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
    CRdAsio::Instance()->DelUser(m_nSocket);
    TUnlock(m_locker);
	J_OS::LOGINFO("CJoStream::Shutdown Shutdown this = %d", this);

	return J_OK;
}

int CJoStream::OnRead(int nfd)
{
    if (!m_bStartup)
    {
        J_OS::LOGINFO("!m_bStartup socket = %d", m_nSocket);
        return J_SOCKET_ERROR;
    }

    TLock(m_locker);
	J_DataHead head = {0};
    int	nLen = recv(nfd, &head, sizeof(head), MSG_WAITALL);
    if (nLen < 0)
    {
        J_OS::LOGERROR("CJoStream::OnRead recv data error");
        TUnlock(m_locker);
        return J_SOCKET_ERROR;
    }
	int nLength = ntohl(head.data_len);
	nLen = recv(nfd, m_pRecvBuff, nLength, MSG_WAITALL);
    if (nLen > 0)
    {
        int nRet = 0;
		J_StreamHeader streamHeader = {0};
		streamHeader.timeStamp = head.time_stamp;
		streamHeader.frameType = head.frame_type;
		streamHeader.dataLen = nLength;
		streamHeader.frameNum = head.frame_seq;
		if (nRet == J_OK)
		{
			TLock(m_vecLocker);
			std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
			for (; it != m_vecRingBuffer.end(); it++)
			{
				(*it)->PushBuffer(m_pRecvBuff, streamHeader);
			}
			TUnlock(m_vecLocker);
		}
    }

    TUnlock(m_locker);

    return J_OK;
}

int CJoStream::OnBroken(int nfd)
{
    J_OS::LOGINFO("CJoStream::OnBroken");
    TLock(m_locker);
    J_StreamHeader streamHeader = {0};
    streamHeader.frameType = jo_media_broken;
    streamHeader.timeStamp = CTime::Instance()->GetLocalTime(0);

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
