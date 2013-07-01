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
: m_bStartup(false)
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
	SingletonTmpl<CRdAsio>::Instance()->Init();
	SingletonTmpl<CRdAsio>::Instance()->AddUser(m_nSocket, this);
	//读取4字节头信息
	m_asioData.ioUser = this;
	m_asioData.ioRead.buf = m_pRecvBuff;
	m_asioData.ioRead.bufLen = 4;
	m_asioData.ioRead.whole = true;
	m_nState = HIK_READ_HEAD;
	m_nOffset = 0;
	SingletonTmpl<CRdAsio>::Instance()->Read(m_nSocket, &m_asioData);
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
	SingletonTmpl<CRdAsio>::Instance()->DelUser(m_nSocket);
	TUnlock(m_locker);

	J_OS::LOGINFO("CHikStream::Shutdown Shutdown this = %d", this);

	return J_OK;
}

void CHikStream::OnRead(const J_AsioDataBase *pAsioData, int nRet)
{
	if (!m_bStartup)
	{
		J_OS::LOGINFO("!m_bStartup socket = %d", m_nSocket);
		return;
	}

	j_result_t nResult = 0;
	J_StreamHeader streamHeader;
	TLock(m_locker);
	m_nOffset += m_asioData.ioRead.bufLen;
	m_asioData.ioRead.whole = true;
	switch (m_nState)
	{
		case HIK_READ_HEAD:
			if (memcmp(m_pRecvBuff, PACK_HEAD, 4) == 0)
				m_asioData.ioRead.bufLen = 10;
			else if ((memcmp(m_pRecvBuff, PSM_HEAD, 4) == 0)
				|| (memcmp(m_pRecvBuff, VIDEO_HEAD, 4) == 0)
				|| (memcmp(m_pRecvBuff, AUDIO_HEAD, 4) == 0))
				m_asioData.ioRead.bufLen = 2;
	
			m_asioData.ioRead.buf = m_pRecvBuff + m_nOffset;
			m_nState = HIK_READ_PS_HEAD;
			break;
		case HIK_READ_PS_HEAD:
			if (m_asioData.ioRead.bufLen == 10)
				m_asioData.ioRead.bufLen = (*(m_asioData.ioRead.buf + 9) & 0x07);
			else if (m_asioData.ioRead.bufLen == 2)
				m_asioData.ioRead.bufLen = (((*(m_asioData.ioRead.buf) & 0xFF) << 8) + (*(m_asioData.ioRead.buf + 1) & 0xFF));
			m_asioData.ioRead.buf = m_pRecvBuff + m_nOffset;
			m_nState = HIK_READ_DATA;
			break;
		case HIK_READ_DATA:
			m_parser.InputData(m_pRecvBuff, m_nOffset);
			nResult = m_parser.GetOnePacket(m_pRecvBuff, streamHeader);
			if (nResult == J_OK)
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
			m_asioData.ioRead.bufLen = 4;
			m_asioData.ioRead.buf = m_pRecvBuff;
			m_nState = HIK_READ_HEAD;
			m_nOffset = 0;
	}
	SingletonTmpl<CRdAsio>::Instance()->Read(m_nSocket, &m_asioData);
	TUnlock(m_locker);
}

void CHikStream::OnBroken(const J_AsioDataBase *pAsioData, int nRet)
{
    J_OS::LOGINFO("CHikStream::OnBroken");
    TLock(m_locker);
    J_StreamHeader streamHeader = {0};
    streamHeader.frameType = jo_media_broken;
    streamHeader.timeStamp = SingletonTmpl<CTime>::Instance()->GetLocalTime(0);

    TLock(m_vecLocker);
    std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
    for (; it != m_vecRingBuffer.end(); it++)
    {
        //J_OS::LOGINFO("nDataLen > 0 socket = %d", m_nSocket);
        (*it)->PushBuffer(m_pRecvBuff, streamHeader);
    }
    TUnlock(m_vecLocker);
	SingletonTmpl<CRdAsio>::Instance()->DelUser(m_nSocket);

    TUnlock(m_locker);
}
