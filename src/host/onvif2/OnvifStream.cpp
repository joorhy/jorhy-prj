#include "OnvifStream.h"

#include "x_socket.h"
#include "x_msg_queue.h"
#include "x_media_msg.h"


COnvifStream::COnvifStream(void *pTCPSocket, std::string resid)
: m_bStartup(false)
, m_pRecvBuff(NULL)
, m_resid(resid)
{
	if (NULL == m_pRecvBuff)
		m_pRecvBuff = new char[RECV_SIZE];

	m_parser.Init();
	m_RtspProxy.Init(COnvifStream::AddRtspBuffDataToDeque, this);
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
    TUnlock(m_locker);

	j_thread_parm RtspThreadParam = {0};
	RtspThreadParam.data = (void *)this;
	RtspThreadParam.entry = COnvifStream::RtspThread;
	m_Thread.Create(RtspThreadParam);

	J_OS::LOGINFO("COnvifStream::Startup Startup this = %d", this);

	return J_OK;
}

int COnvifStream::Shutdown()
{
	if (!m_bStartup)
		return J_OK;

    TLock(m_locker);
    m_bStartup = false;
	m_RtspProxy.Stop();
    TUnlock(m_locker);
	J_OS::LOGINFO("COnvifStream::Shutdown Shutdown this = %d", this);

	return J_OK;
}

unsigned COnvifStream::RtspThread( void * pCOnvifStream )
{
	COnvifStream * pThis = (COnvifStream *)pCOnvifStream;
	pThis->m_RtspProxy.Begin();

	printf("lei yin chun 1111111111\n");
	return 0;
}
