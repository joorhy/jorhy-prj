#include "x_socket.h"
#include "x_lock.h"
#include "x_msg_queue.h"
#include "x_media_msg.h"
#include "Hikv3Stream.h"

#define RECV_SIZE (1024 * 1024)
CHikv3Stream::CHikv3Stream(void *pTCPSocket, std::string resid,char *pHeader)
: m_recvThread(0)
, m_bStartup(false)
, m_pRecvBuff(NULL)
, m_resid(resid)
{
	//m_nSocket = nSocket;
	m_pTCPSocket = pTCPSocket;
	if (NULL == m_pRecvBuff)
		m_pRecvBuff = new char[RECV_SIZE];
	//memset(m_pRecvBuff, 0, sizeof(m_pRecvBuff));

	//m_parser.Init(pHeader);

	J_OS::LOGINFO("CHikv3Stream::CHikv3Stream create this = %d", this);
}

CHikv3Stream::~CHikv3Stream()
{
	m_parser.Deinit();
	if (m_pRecvBuff != NULL)
	{
		delete m_pRecvBuff;
		m_pRecvBuff = NULL;
	}

	J_OS::LOGINFO("CHikv3Stream::~CHikv3Stream destroy this = %d", this);
}

int CHikv3Stream::Startup()
{
	if (m_bStartup)
		return J_OK;

	m_bStartup = true;
	pthread_create(&m_recvThread, NULL, CHikv3Stream::WorkThread, this);
	J_OS::LOGINFO("CHikv3Stream::Startup Startup this = %d", this);

	return J_OK;
}

int CHikv3Stream::Shutdown()
{
	if (!m_bStartup)
		return J_OK;

	m_bStartup = false;
	//sleep(1);
	pthread_cancel(m_recvThread);
	pthread_join(m_recvThread, NULL);
	J_OS::LOGINFO("CHikv3Stream::Shutdown Shutdown this = %d", this);

	return J_OK;
}

void CHikv3Stream::OnWork()
{
	int nLen = 0;
	pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
	while (true)
	{
		//J_OS::LOGINFO(" CHikv3Stream::OnWork()");
		nLen = ((J_OS::CTCPSocket *)m_pTCPSocket)->Read(m_pRecvBuff, RECV_SIZE);
		if (nLen < 0)
		{
			//CMediaMessage *pMessage = new CMediaMessage();
			//pMessage->SetMsgType(MSG_MEDIA_BROKEN);
			//pMessage->SetResid(m_resid.c_str());
			//CXMessageQueue::Instance()->PostMessage(MSG_MEDIA, pMessage);

			J_OS::LOGINFO("CHikv3Stream::OnWork recv data error errno = %d", errno);
			break;
		}

		//printf("datalen = %d\n", nLen);
		m_parser.InputData(m_pRecvBuff, nLen);

		int nPackLen = 0;
		int nFrameType;
		do
		{
			/*bool bKeyFrame = m_parser.GetOnePacket(m_pRecvBuff, nPackLen, nFrameType);
			if (nPackLen > 0)
			{
				NVRStreamHeader streamHeader;
				streamHeader.dataLen = nPackLen;
				if (bKeyFrame)
					streamHeader.frameType = KEY_FRAME;
				else
					streamHeader.frameType = nFrameType;

				TLock(m_vecLocker);
				std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
				for (; it != m_vecRingBuffer.end(); it++)
				{
					(*it)->PushBuffer(m_pRecvBuff, streamHeader);
				}
				TUnlock(m_vecLocker);
			}*/
		}while (nPackLen > 0);
		pthread_testcancel();
	}

	J_OS::LOGINFO("CHikv3Stream::OnWork pthread_exit");
}
