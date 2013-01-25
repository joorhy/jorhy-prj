#include "DahuaStream.h"

CDahuaStream::CDahuaStream(std::string resid, int nChannel)
{
	m_pRecvBuff = NULL;
	m_bStartup = false;
	if (NULL == m_pRecvBuff)
		m_pRecvBuff = new char[1024 * 1024];	
		
	m_parser.Init();
}

CDahuaStream::~CDahuaStream()
{
	m_parser.Deinit();
	if (m_pRecvBuff != NULL)
	{
		delete m_pRecvBuff;
		m_pRecvBuff = NULL;
	}
}

int CDahuaStream::Startup()
{
	if (m_bStartup)
		return J_OK;
	m_bStartup = true;

	return J_OK;
}

int CDahuaStream::Shutdown()
{
	if (!m_bStartup)
		return J_OK;
	m_bStartup = false;

	return J_OK;
}

void CDahuaStream::OnRecv(LONG hHandle, DWORD dwDayaType, BYTE *pBuffer, DWORD dwBufsize)
{
	//printf("data_type = %d len = %d\n", dwDayaType, dwBufsize);
	if (m_bStartup && dwDayaType == 0)
	{
		m_parser.InputData((const char *)pBuffer, dwBufsize);
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
}
