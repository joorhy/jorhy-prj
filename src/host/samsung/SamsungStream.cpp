#include "SamsungStream.h"

#include "x_socket.h"
#include "x_msg_queue.h"
#include "x_media_msg.h"
#include "x_time.h"

#define RECV_SIZE (1024 * 1024)
CSamsungStream::CSamsungStream(j_void_t *pTCPSocket, j_string_t resid)
    : m_bStartup(false)
    , m_pRecvBuff(NULL)
    , m_resid(resid)
{
    m_pTCPSocket = pTCPSocket;
    m_nSocket = ((J_OS::CTCPSocket *)pTCPSocket)->GetHandle();
    if (NULL == m_pRecvBuff)
        m_pRecvBuff = new char[RECV_SIZE];

    m_parser.Init();
    J_OS::LOGINFO("CSamsungStream::CSamsungStream create this = %d", this);
}

CSamsungStream::~CSamsungStream()
{
    m_parser.Deinit();
    if (m_pRecvBuff != NULL)
    {
        delete m_pRecvBuff;
        m_pRecvBuff = NULL;
    }

    J_OS::LOGINFO("CSamsungStream::~CSamsungStream destroy this = %d", this);
}

j_result_t CSamsungStream::Startup()
{
    if (m_bStartup)
        return J_OK;

    TLock(m_locker);
    m_bStartup = true;
    GetAsioLayer()->Init();
    GetAsioLayer()->AddUser(m_nSocket, this);
	m_asioData.ioUser = this;
	m_asioData.ioRead.buf = m_pRecvBuff;
	m_asioData.ioRead.bufLen = RECV_SIZE;
	m_asioData.ioRead.whole = false;
	GetAsioLayer()->Read(m_nSocket, &m_asioData);
    TUnlock(m_locker);

    J_OS::LOGINFO("CSamsungStream::Startup Startup this = %d", this);

    return J_OK;
}

j_result_t CSamsungStream::Shutdown()
{
    if (!m_bStartup)
        return J_OK;

    TLock(m_locker);
    m_bStartup = false;
    GetAsioLayer()->DelUser(m_nSocket);
    TUnlock(m_locker);

    J_OS::LOGINFO("CSamsungStream::Shutdown Shutdown this = %d", this);

    return J_OK;
}

void CSamsungStream::OnRead(const J_AsioDataBase *pAsioData, int nRet)
{
    if (!m_bStartup)
    {
        J_OS::LOGINFO("CSamsungStream:: !m_bStartup socket = %d", m_nSocket);
        return;
    }

    TLock(m_locker);

	m_parser.InputData(pAsioData->ioRead.buf, pAsioData->ioRead.finishedLen);
	j_result_t nResult = 0;
	do
	{
		J_StreamHeader streamHeader;
		nResult = m_parser.GetOnePacket(m_pRecvBuff, streamHeader);
		if (nResult == J_OK)
		{
			TLock(m_vecLocker);
			std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
			for (; it != m_vecRingBuffer.end(); it++)
			{
				//J_OS::LOGINFO("streamHeader > 0 socket = %d", m_nSocket);
				(*it)->PushBuffer(m_pRecvBuff, streamHeader);
			}
			TUnlock(m_vecLocker);
		}
	}
	while (nResult == J_OK);

    TUnlock(m_locker);
}

void CSamsungStream::OnBroken(const J_AsioDataBase *pAsioData, int nRet)
{
    J_OS::LOGERROR("CSamsungStream::OnBroken");
    TLock(m_locker);
    J_StreamHeader streamHeader = {0};
    streamHeader.frameType = jo_media_broken;
    streamHeader.timeStamp = GetTimeLayer()->GetLocalTime(0);

    TLock(m_vecLocker);
    j_vec_buffer_t::iterator it = m_vecRingBuffer.begin();
    for (; it != m_vecRingBuffer.end(); it++)
    {
        //J_OS::LOGINFO("nDataLen > 0 socket = %d", m_nSocket);
        (*it)->PushBuffer(m_pRecvBuff, streamHeader);
    }
    TUnlock(m_vecLocker);

    TUnlock(m_locker);
}
