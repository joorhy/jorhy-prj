#include "VodPlayObj.h"
#include "x_player_factory.h"
#include "x_filereader_factory.h"
#include "x_time.h"

#define CLIENT_BUFFER_SIZE (2 * 1024 * 1024)

CVodPlayObj::CVodPlayObj(int nStreamId, const char *pPlayerType, const char* pReaderType, const char *pResid)
{
	m_nSocket = nStreamId;
	m_bStart = false;
	m_readerType = pReaderType;
	m_resid = pResid;
	m_playerType = pPlayerType;
	m_pReader = NULL;
	m_mode = jo_push_mode;

	m_pDataBuff = new char[CLIENT_BUFFER_SIZE];
	//m_pConvetBuff = new char[CLIENT_BUFFER_SIZE];

	m_nextFrameTime = 0;
	m_lastFrameTime = 0;
	m_lastFrameNum = 0;
}

CVodPlayObj::~CVodPlayObj()
{
	if (m_pDataBuff != NULL)
		delete m_pDataBuff;

	//if (m_pConvetBuff != NULL)
	//	delete m_pConvetBuff;
}

j_result_t CVodPlayObj::PlayVod(j_wnd_t hWnd, j_uint64_t nStart, j_uint64_t nEnd)
{
	if (!m_bStart)
	{
		OpenFile(nStart, nEnd);
		JoPlayerFactory->GetPlayer(m_nSocket, m_playerType.c_str())->Play(hWnd);
		m_bStart = true;
	}

	return J_OK;
}

j_result_t CVodPlayObj::StopVod()
{
	if (m_bStart)
	{
		m_bStart = false;
		JoPlayerFactory->GetPlayer(m_nSocket, m_playerType.c_str())->Stop();
		CloseFile();
	}
	return J_OK;
}

j_result_t CVodPlayObj::ProcessMedia()
{
	if (!m_bStart)
		return J_OK;

	int nRet = J_OK;
	memset(&m_streamHeader, 0, sizeof(m_streamHeader));
	nRet = m_pReader->GetPacket(m_pDataBuff, m_streamHeader);
	if (nRet == J_OK && m_streamHeader.dataLen > 0)
	{
		if (m_nextFrameTime <= 40)
		{
			m_lastFrameTime = m_streamHeader.timeStamp;
			if (m_streamHeader.frameType == jo_video_i_frame ||
				((m_streamHeader.frameType == jo_video_p_frame) && (m_streamHeader.frameNum == ++m_lastFrameNum)))
			{
				if (m_streamHeader.frameType == jo_video_i_frame)
					m_lastFrameNum = m_streamHeader.frameNum;

				JoPlayerFactory->GetPlayer(m_nSocket, m_playerType.c_str())->InputData(m_pDataBuff, m_streamHeader);
			}
			m_nextFrameTime = 0;
		}
		else
		{
			m_nextFrameTime -= m_streamHeader.timeStamp - m_lastFrameTime;
			return J_OK;
		}
	}
	else if (nRet < 0 || (nRet==J_OK && m_streamHeader.frameType==jo_file_end
		|| m_streamHeader.frameType==jo_media_broken))
	{
		return J_SOCKET_ERROR;
	}
	else
	{
		return J_OK;
	}
	return nRet;
}

int CVodPlayObj::OpenFile(j_uint64_t nStart, j_uint64_t nEnd)
{
	if (!m_fileid.empty() && m_fileid.c_str() != m_resid)
		CloseFile();

	if (m_bStart/* && !m_bPaused*/)
		return J_OK;

	//if (m_bPaused)
	//	PauseFile();

	if (m_pReader == NULL)
		m_pReader = JoFileReaderFactory->GetFileReader(m_nSocket, m_readerType.c_str(), m_resid.c_str());

	int nRet = m_pReader->SetTime(nStart, nEnd);
	if (nRet != J_OK)
		return nRet;

	if (m_mode == jo_push_mode)
		m_pReader->GetMediaData(0, 24*60*60*1000);

	m_fileid = m_resid;

	J_OS::LOGINFO("OpenFile::OpenFile socket =  %d OpenFile", m_nSocket.sock);

	return J_OK;
}

int CVodPlayObj::CloseFile()
{
	if (!m_bStart)
		return J_OK;

	m_bStart = false;
	JoFileReaderFactory->DelFileReader(m_nSocket);

	m_fileid.clear();
	J_OS::LOGINFO("CVodPlayObj::CloseFile socket =  %d CloseFile", m_nSocket.sock);

	return J_OK;
}