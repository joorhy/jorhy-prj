#include "x_socket.h"
#include "x_lock.h"
#include "x_media_msg.h"
#include "HikSdkStream.h"

const char PACK_HEAD[5] = { 0x00, 0x00, 0x01, 0xBA };
const char PSM_HEAD[5] = { 0x00, 0x00, 0x01, 0xBC };
const char VIDEO_HEAD[5] = { 0x00, 0x00, 0x01, 0xE0 };
const char AUDIO_HEAD[5] = { 0x00, 0x00, 0x01, 0xC0 };
static FILE *fp = NULL;
#define RECV_SIZE (2 * 1024 * 1024)
CHikSdkStream::CHikSdkStream(std::string resid)
: m_pDataBuff(NULL)
{
	m_bStartup = false;
	m_parser.Init();
	if (NULL == m_pDataBuff)
		m_pDataBuff = new char[RECV_SIZE];
		
	J_OS::LOGINFO("CHikSdkStream::CHikSdkStream create this = %d", this);
}

CHikSdkStream::~CHikSdkStream()
{
	m_parser.Deinit();
	if (m_pDataBuff != NULL)
	{
		delete m_pDataBuff;
		m_pDataBuff = NULL;
	}
	J_OS::LOGINFO("CHikSdkStream::~CHikSdkStream destroy this = %d", this);
}

int CHikSdkStream::Startup()
{
	if (m_bStartup)
		return J_OK;

	m_bStartup = true;
	
	J_OS::LOGINFO("CHikStream::Startup Startup this = %d", this);

	return J_OK;
}

int CHikSdkStream::Shutdown()
{
	if (!m_bStartup)
		return J_OK;

	m_bStartup = false;

	J_OS::LOGINFO("CHikStream::Shutdown Shutdown this = %d", this);

	return J_OK;
}

void CHikSdkStream::OnRecvData(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize)
{
	if (dwDataType == 2)
	{
		J_StreamHeader streamHeader;
		m_parser.InputData((const char *)pBuffer, dwBufSize);
		j_result_t nResult = m_parser.GetOnePacket(m_pDataBuff, streamHeader);
		while (nResult == J_OK)
		{
			TLock(m_vecLocker);
			std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
			for (; it != m_vecRingBuffer.end(); it++)
			{
				//J_OS::LOGINFO("nDataLen > 0 socket = %d", m_nSocket);
				(*it)->PushBuffer(m_pDataBuff, streamHeader);
			}
			TUnlock(m_vecLocker);
			nResult = m_parser.GetOnePacket(m_pDataBuff, streamHeader);
		}
	}
}