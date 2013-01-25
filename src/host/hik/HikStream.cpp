#include "x_socket.h"
#include "x_lock.h"
#include "x_msg_queue.h"
#include "x_media_msg.h"
#include "HikStream.h"

#define RECV_SIZE (1024 * 1024)
CHikStream::CHikStream(void *pTCPSocket, std::string resid)
: m_recvThread(0)
, m_bStartup(false)
, m_pRecvBuff(NULL)
, m_resid(resid)
{
	m_pTCPSocket = pTCPSocket;
	m_nSocket = ((J_OS::CTCPSocket *)pTCPSocket)->GetHandle();
	if (NULL == m_pRecvBuff)
		m_pRecvBuff = new char[RECV_SIZE];

	m_parser.Init();

	J_OS::LOGINFO("CHikStream::CHikStream create this = %d", this);
}

CHikStream::~CHikStream()
{
	m_parser.Deinit();
	if (m_pRecvBuff != NULL)
	{
		delete m_pRecvBuff;
		m_pRecvBuff = NULL;
	}

	J_OS::LOGINFO("CHikStream::~CHikStream destroy this = %d", this);
}

int CHikStream::Startup()
{
	if (m_bStartup)
		return J_OK;

	TLock(m_locker);
	m_bStartup = true;
	CRdAsio::Instance()->Init();
	CRdAsio::Instance()->AddUser(m_nSocket, this);
	TUnlock(m_locker);

	J_OS::LOGINFO("CHikStream::Startup Startup this = %d", this);

	return J_OK;
}

int CHikStream::Shutdown()
{
	if (!m_bStartup)
		return J_OK;

	TLock(m_locker);
	m_bStartup = false;
	CRdAsio::Instance()->DelUser(m_nSocket);
	TUnlock(m_locker);

	J_OS::LOGINFO("CHikStream::Shutdown Shutdown this = %d", this);

	return J_OK;
}

int CHikStream::OnRead(int nfd)
{
	if (!m_bStartup)
	{
		J_OS::LOGINFO("!m_bStartup socket = %d", m_nSocket);
		return J_SOCKET_ERROR;
	}

	TLock(m_locker);
	//J_OS::LOGINFO("OnRead socket = %d %d", m_nSocket, &m_vecRingBuffer);

	/*static bool bFirst = true;
	int nDataLen = 0;
	if (bFirst)
	{
	    nDataLen = ((J_OS::CTCPSocket *)m_pTCPSocket)->Read_n(m_pRecvBuff, 44);
	    bFirst = false;
	}
	else
	{*/
    //    int nLen = 0;
    //    nLen = ((J_OS::CTCPSocket *)m_pTCPSocket)->Read_n(m_pRecvBuff, 16);
    //    if (nLen < 0)
    //    {
    //        J_OS::LOGERROR("CHikStream::OnWork recv data error");
    //        TUnlock(m_locker);
    //        return J_SOCKET_ERROR;
    //    }
	//
    //    int nDataLen = 0;
    //    if ((m_pRecvBuff[0] & 0xFF) == 0x03)
    //    {
    //        nDataLen = HIK_PACK_LENGHT(m_pRecvBuff);
    //    }
    //    else if ((m_pRecvBuff[0] & 0xFF) == 0x24)
    //    {
    //        nDataLen = HIK_PACK_LENGHT2(m_pRecvBuff);
    //    }
	//
    //    nLen = ((J_OS::CTCPSocket *)m_pTCPSocket)->Read_n(m_pRecvBuff + 16, nDataLen - 16);
    //    if (nLen < 0)
    //    {
    //        J_OS::LOGERROR("CHikStream::OnWork recv data error");
    //        TUnlock(m_locker);
    //        return J_SOCKET_ERROR;
    //    }
	//}
	
	int nDataLen = ((J_OS::CTCPSocket *)m_pTCPSocket)->Read(m_pRecvBuff, 8192);
	if (nDataLen < 0)
	{
		J_OS::LOGERROR("CHikStream::OnWork recv data error");
		TUnlock(m_locker);
		return J_SOCKET_ERROR;
	}

	if (nDataLen > 0)
	{
		//J_OS::LOGINFO("nDataLen > 0 socket = %d", m_nSocket);
		m_parser.InputData(m_pRecvBuff, nDataLen);

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
					//J_OS::LOGINFO("nDataLen > 0 socket = %d", m_nSocket);
					(*it)->PushBuffer(m_pRecvBuff, streamHeader);
				}
				TUnlock(m_vecLocker);
			}
		}while (nRet == J_OK);
	}
	TUnlock(m_locker);

	return J_OK;
}

int CHikStream::OnBroken(int nfd)
{
    J_OS::LOGINFO("CHikStream::OnBroken");
    TLock(m_locker);
    J_StreamHeader streamHeader = {0};
    streamHeader.frameType = J_MediaBroken;
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
