#include "SonyStream.h"

#include "x_socket.h"
#include "x_msg_queue.h"
#include "x_media_msg.h"

#define RECV_SIZE (1024 * 1024)
CSonyStream::CSonyStream(void *pTCPSocket, std::string resid)
: m_bStartup(false)
, m_pRecvBuff(NULL)
, m_resid(resid)
{
	m_pTCPSocket = pTCPSocket;
	m_nSocket = ((J_OS::CTCPSocket *)pTCPSocket)->GetHandle();
	if (NULL == m_pRecvBuff)
		m_pRecvBuff = new char[RECV_SIZE];

	m_parser.Init();
	J_OS::LOGINFO("CSonyStream::CSonyStream create this = %d", this);
}

CSonyStream::~CSonyStream()
{
	m_parser.Deinit();
	if (m_pRecvBuff != NULL)
	{
		delete m_pRecvBuff;
		m_pRecvBuff = NULL;
	}

	J_OS::LOGINFO("CSonyStream::~CSonyStream destroy this = %d", this);
}

int CSonyStream::Startup()
{
	if (m_bStartup)
		return J_OK;

    TLock(m_locker);
    m_bStartup = true;
    CRdAsio::Instance()->Init();
    CRdAsio::Instance()->AddUser(m_nSocket.sock, this);
    TUnlock(m_locker);
	J_OS::LOGINFO("CSonyStream::Startup Startup this = %d", this);

	return J_OK;
}

int CSonyStream::Shutdown()
{
	if (!m_bStartup)
		return J_OK;

    TLock(m_locker);
    m_bStartup = false;
    CRdAsio::Instance()->DelUser(m_nSocket.sock);
    TUnlock(m_locker);
	J_OS::LOGINFO("CSonyStream::Shutdown Shutdown this = %d", this);

	return J_OK;
}

int CSonyStream::OnRead(int nfd)
{
    if (!m_bStartup)
    {
        J_OS::LOGINFO("!m_bStartup socket = %d", m_nSocket);
        return J_SOCKET_ERROR;
    }

    TLock(m_locker);
    int	nLen = recv(nfd, m_pRecvBuff, RECV_SIZE, 0);
    if (nLen < 0)
    {
        J_OS::LOGERROR("CSonyStream::OnRead recv data error");
        TUnlock(m_locker);
        return J_SOCKET_ERROR;
    }

    if (nLen > 0)
    {
        m_parser.InputData(m_pRecvBuff, nLen);
        int nRet = 0;
        do
        {
            J_StreamHeader streamHeader;
            nRet = m_parser.GetOnePacket(m_pRecvBuff, streamHeader);
            if (nRet == J_OK)
            {
                TLock(m_vecLocker);
                std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
                for (; it != m_vecRingBuffer.end(); it++)
                {
                    //J_OS::LOGINFO("begin %lld,%lld", streamHeader.timeStamp, CTime::Instance()->GetLocalTime(0));
                    //J_OS::LOGINFO("nDataLen > 0 socket = %d", m_nSocket);
                    (*it)->PushBuffer(m_pRecvBuff, streamHeader);
                }
                TUnlock(m_vecLocker);
            }
        }
        while (nRet == J_OK);
    }

    TUnlock(m_locker);

    return J_OK;
}

int CSonyStream::OnBroken(int nfd)
{
    J_OS::LOGINFO("CSonyStream::OnBroken");
    TLock(m_locker);
    J_StreamHeader streamHeader = {0};
    streamHeader.frameType = jo_media_broken;
    streamHeader.timeStamp = CTime::Instance()->GetLocalTime(0);

    TLock(m_vecLocker);
    std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
    for (; it != m_vecRingBuffer.end(); it++)
    {
        //J_OS::LOGINFO("nDataLen > 0 socket = %d", m_nSocket);
        (*it)->PushBuffer(m_pRecvBuff, streamHeader);
    }
    TUnlock(m_vecLocker);

    TUnlock(m_locker);

    return J_OK;
}
