#include "x_socket.h"
#include "x_lock.h"
#include "x_msg_queue.h"
#include "x_media_msg.h"
#include "HikStream.h"

const char PACK_HEAD[5] = { 0x00, 0x00, 0x01, 0xBA };
const char PSM_HEAD[5] = { 0x00, 0x00, 0x01, 0xBC };
const char VIDEO_HEAD[5] = { 0x00, 0x00, 0x01, 0xE0 };
const char AUDIO_HEAD[5] = { 0x00, 0x00, 0x01, 0xC0 };

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
	int nOffset = 0;
	int nDataLen = recv(nfd, m_pRecvBuff, 4, MSG_WAITALL);
	if (nDataLen < 0)
	{
		J_OS::LOGERROR("CHikStream::OnWork recv data error");
		TUnlock(m_locker);
		return J_SOCKET_ERROR;
	}
	nOffset += 4;
	
	int nNextLen = 0;
	if (memcmp(m_pRecvBuff, PACK_HEAD, 4) == 0)
	{
		nDataLen = recv(nfd, m_pRecvBuff + 4, 10, MSG_WAITALL);
		nOffset += 10;
		nNextLen = (*(m_pRecvBuff + 13) & 0x07);
	}
	else if ((memcmp(m_pRecvBuff, PSM_HEAD, 4) == 0)
		|| (memcmp(m_pRecvBuff, VIDEO_HEAD, 4) == 0)
		|| (memcmp(m_pRecvBuff, AUDIO_HEAD, 4) == 0))
	{
		nDataLen = recv(nfd, m_pRecvBuff + 4, 2, MSG_WAITALL);
		nOffset += 2;
		nNextLen = (((*(m_pRecvBuff + 4) & 0xFF) << 8) + (*(m_pRecvBuff + 5) & 0xFF)); 
	}
	
	if (nNextLen > 0)
	{
		nDataLen = recv(nfd, m_pRecvBuff + nOffset, nNextLen, MSG_WAITALL);
		nOffset += nNextLen;
	}

	if (nNextLen > 0)
	{
		m_parser.InputData(m_pRecvBuff, nOffset);
		int nRet = 0;
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
