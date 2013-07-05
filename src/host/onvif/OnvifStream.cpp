#include "OnvifStream.h"

#include "x_socket.h"
#include "x_msg_queue.h"
#include "x_media_msg.h"

#define RECV_SIZE (1024 * 1024)
COnvifStream::COnvifStream(void *pTCPSocket, std::string resid)
: m_bStartup(false)
, m_pRecvBuff(NULL)
, m_resid(resid)
{
	m_pTCPSocket = pTCPSocket;
	m_nSocket = ((J_OS::CTCPSocket *)pTCPSocket)->GetHandle();
	if (NULL == m_pRecvBuff)
		m_pRecvBuff = new char[RECV_SIZE];

	m_parser.Init();
	J_OS::LOGINFO("COnvifStream::COnvifStream create this = %d", this);
}

COnvifStream::~COnvifStream()
{
	m_parser.Deinit();
	if (m_pRecvBuff != NULL)
	{
		delete m_pRecvBuff;
		m_pRecvBuff = NULL;
	}

	J_OS::LOGINFO("COnvifStream::~COnvifStream destroy this = %d", this);
}

int COnvifStream::Startup()
{
	if (m_bStartup)
		return J_OK;

    TLock(m_locker);
    m_bStartup = true;
    JoXAsio->Init();
    JoXAsio->AddUser(m_nSocket, this);
	m_asioData.ioUser = this;
	m_asioData.ioRead.buf = m_pRecvBuff;
	m_asioData.ioRead.bufLen = 4;
	m_asioData.ioRead.whole = true;
	m_nState = ONVIF_READ_HEAD;
	JoXAsio->Read(m_nSocket, &m_asioData);
    TUnlock(m_locker);
	J_OS::LOGINFO("COnvifStream::Startup Startup this = %d", this);

	return J_OK;
}

int COnvifStream::Shutdown()
{
	if (!m_bStartup)
		return J_OK;

    TLock(m_locker);
    m_bStartup = false;
    JoXAsio->DelUser(m_nSocket);
    TUnlock(m_locker);
	J_OS::LOGINFO("COnvifStream::Shutdown Shutdown this = %d", this);

	return J_OK;
}

void COnvifStream::OnRead(const J_AsioDataBase *pAsioData, int nRet)
{
    if (!m_bStartup)
    {
        J_OS::LOGINFO("!m_bStartup socket = %d", m_nSocket);
        return;
    }

	j_result_t nResult = J_OK;
	J_StreamHeader streamHeader = {0};
    TLock(m_locker);
	switch (m_nState)
	{
		case ONVIF_READ_HEAD:
			m_asioData.ioRead.buf = m_pRecvBuff + pAsioData->ioRead.bufLen;
			m_asioData.ioRead.bufLen = ((m_asioData.ioRead.buf[2] & 0xFF) << 8) + (m_asioData.ioRead.buf[3] & 0xFF);
			m_nState = ONVIF_READ_DATA;
			break;
		case ONVIF_READ_DATA:
			m_parser.InputData(m_pRecvBuff, pAsioData->ioRead.bufLen + 4);
			nResult = m_parser.GetOnePacket(m_pRecvBuff, streamHeader);
			if (nResult == J_OK)
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
			m_asioData.ioRead.bufLen = 4;
			m_asioData.ioRead.buf = m_pRecvBuff;
			m_nState = ONVIF_READ_HEAD;
			break;
	}
	m_asioData.ioRead.whole = true;
	JoXAsio->Read(m_nSocket, &m_asioData);

    TUnlock(m_locker);
}

void COnvifStream::OnBroken(const J_AsioDataBase *pAsioData, int nRet)
{
    J_OS::LOGINFO("COnvifStream::OnBroken");
    TLock(m_locker);
    J_StreamHeader streamHeader = {0};
    streamHeader.frameType = jo_media_broken;
    streamHeader.timeStamp = JoTime->GetLocalTime(0);

    TLock(m_vecLocker);
    std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
    for (; it != m_vecRingBuffer.end(); it++)
    {
        //J_OS::LOGINFO("nDataLen > 0 socket = %d", m_nSocket);
        (*it)->PushBuffer(m_pRecvBuff, streamHeader);
    }
    TUnlock(m_vecLocker);

    TUnlock(m_locker);
}
