#include "VodMediaObj.h"
#include "x_filter_factory.h"
#include "x_filereader_factory.h"
#include "x_socket.h"

#define CLIENT_BUFFER_SIZE (1024 * 1024)

CVodMediaObj::CVodMediaObj(j_socket_t nSocket, J_Obj *pObj)
{
	m_nSocket = nSocket;
	m_bStart = false;
	m_pDataBuff = new char[CLIENT_BUFFER_SIZE];
	m_pConvetBuff = new char[CLIENT_BUFFER_SIZE];
	m_bPaused = false;
	m_pHeader = NULL;
	m_bSendHeader = true;
	m_sendSocket.Init(nSocket);
	m_pObj = pObj;
	m_pReader = NULL;
	
	m_nextFrameTime = 0;
	m_lastFrameTime = 0;
	m_lastFrameNum = 0;

	J_OS::LOGINFO("CVodMediaObj::CVodMediaObj created socket =  %d", m_nSocket.sock);
}

CVodMediaObj::~CVodMediaObj()
{
	if (m_pDataBuff != NULL)
		delete m_pDataBuff;
		
	if (m_pConvetBuff != NULL)
		delete m_pConvetBuff;

	J_OS::LOGINFO("CVodMediaObj::~CVodMediaObj destroyed socket =  %d", m_nSocket.sock);
}

int CVodMediaObj::Process(J_AsioDataBase &asioData)
{
	int nRet = J_OK;
	J_CommandFilter *videoCommand = dynamic_cast<J_CommandFilter *>(m_pObj);
	if (videoCommand != NULL)
	{
		if (asioData.ioCall == J_AsioDataBase::j_read_e)
		{
			m_resid = videoCommand->GetResid();
			switch(videoCommand->GetCommandType())
			{
			case jo_start_vod:
				nRet = OpenFile();
				J_OS::LOGINFO("CVodMediaObj::Process OpenFile socket =  %d ret = %d", m_nSocket.sock, nRet);
				break;
			case jo_pause_vod:
				nRet = PauseFile();
				break;
			case jo_settime_vod:
				nRet = SetTime();
				J_OS::LOGINFO("CVodMediaObj::Process OpenFile socket =  %d ret = %d", m_nSocket.sock, nRet);
				break;
			case jo_setpos_vod:
				nRet = SetScale();
				break;
			case jo_read_data:
				//nRet = ReadData();
				break;
			default:
				J_OS::LOGINFO("CVodMediaObj::Process CommandType unkown type =  %d", videoCommand->GetCommandType());
				break;
			}
		}
		else if (asioData.ioCall == J_AsioDataBase::j_write_e)
		{
			nRet = WriteData(asioData);
		}
		else
		{
			assert(false);
		}
	}

	return nRet;
}

int CVodMediaObj::Clearn()
{
	CloseFile();

	if (m_pObj)
	{
		JoFilterFactory->DelFilter(m_nSocket);
		m_pObj = NULL;
	}
	if (m_pReader)
	{
		JoFileReaderFactory->DelFileReader(m_nSocket);
		m_pReader = NULL;
	}

	J_OS::LOGINFO("CVodMediaObj::Clearn socket =  %d broken", m_nSocket.sock);
	//delete this;

	return J_OK;
}

int CVodMediaObj::Run(bool bFlag)
{
	m_bStart = bFlag;

	return J_OK;
}

int CVodMediaObj::OpenFile()
{
	if (!m_fileid.empty() && m_fileid.c_str() != m_resid)
		CloseFile();

	if (m_bStart && !m_bPaused)
		return J_OK;

	if (m_bPaused)
		PauseFile();

	if (m_pReader == NULL)
		m_pReader = JoFileReaderFactory->GetFileReader(m_nSocket
		, dynamic_cast<J_RequestFilter *>(m_pObj)->GetResourceType(), m_resid.c_str());
	
	J_VodCommandFilter *vodTimeCommand = dynamic_cast<J_VodCommandFilter *>(m_pObj);
	int nRet = m_pReader->SetTime(vodTimeCommand->GetBeginTime(), vodTimeCommand->GetEndTime());
	if (nRet != J_OK)
		return nRet;
		
	if (vodTimeCommand->GetMode() == jo_push_mode)
		m_pReader->GetMediaData(0, 24*60*60*1000);

	m_fileid = m_resid;

	J_OS::LOGINFO("CVodMediaObj::OpenFile socket =  %d OpenFile", m_nSocket.sock);

	return J_OK;
}

int CVodMediaObj::CloseFile()
{
	if (!m_bStart)
		return J_OK;

	m_bStart = false;
	JoFileReaderFactory->DelFileReader(m_nSocket);
	m_pHeader = NULL;

	m_fileid.clear();
	m_bSendHeader = true;
	J_OS::LOGINFO("CVodMediaObj::CloseFile socket =  %d CloseFile", m_nSocket.sock);

	return J_OK;
}

int CVodMediaObj::PauseFile()
{
	m_bStart = false;
	m_bPaused = !m_bPaused;
	m_pReader->Pause();

	return J_OK;
}

int CVodMediaObj::SetTime()
{
	J_VodCommandFilter *vodTimeCommand = dynamic_cast<J_VodCommandFilter *>(m_pObj);
	m_pReader->SetTime(vodTimeCommand->GetBeginTime(), vodTimeCommand->GetEndTime());

	return J_OK;
}

int CVodMediaObj::SetScale()
{
	J_VodCommandFilter *vodTimeCommand = dynamic_cast<J_VodCommandFilter *>(m_pObj);
	m_pReader->SetScale(vodTimeCommand->GetScale());

	return J_OK;
}

int CVodMediaObj::ReadData()
{
	J_VodCommandFilter *vodTimeCommand = dynamic_cast<J_VodCommandFilter *>(m_pObj);
	m_pReader->GetMediaData(0, 24*60*60*1000/*vodTimeCommand->GetEndTime() - vodTimeCommand->GetBeginTime()*/);

	return J_OK;
}

int CVodMediaObj::WriteData(J_AsioDataBase &asioData)
{
	if (!m_bStart)
	{
		asioData.ioWrite.buf = NULL;
		asioData.ioWrite.bufLen = 0;
		asioData.ioWrite.whole = false;
		asioData.ioCall = J_AsioDataBase::j_write_e;
		return J_OK;
	}

	int nRet = J_OK;
	memset(&m_streamHeader, 0, sizeof(m_streamHeader));
	nRet = m_pReader->GetPacket(m_pDataBuff, m_streamHeader);
	if (nRet == J_OK && m_streamHeader.dataLen > 0)
	{
		int nDataLen = 0;
		//m_streamHeader.timeStamp &= 0x1FFFFFF;
		J_RequestFilter *pAccess = dynamic_cast<J_RequestFilter *>(m_pObj);
		pAccess->Convert(m_pDataBuff, m_streamHeader, m_pConvetBuff, nDataLen);
		if (nDataLen > 0)
		{
			if (m_nextFrameTime <= 40)
			{
				m_lastFrameTime = m_streamHeader.timeStamp;
				if (m_streamHeader.frameType == jo_video_i_frame ||
					((m_streamHeader.frameType == jo_video_p_frame) && (m_streamHeader.frameNum == ++m_lastFrameNum)))
				{
					if (m_streamHeader.frameType == jo_video_i_frame)
						m_lastFrameNum = m_streamHeader.frameNum;

					//printf("%s %d %d\n", m_pConvetBuff, m_streamHeader.dataLen, sizeof(J_DataHead));
					asioData.ioWrite.buf = m_pConvetBuff;
					asioData.ioWrite.bufLen = nDataLen;
					asioData.ioWrite.whole = true;
					asioData.ioCall = J_AsioDataBase::j_write_e;
				}
				m_nextFrameTime = 0;
			}
			else
			{
				m_nextFrameTime -= m_streamHeader.timeStamp - m_lastFrameTime;
				asioData.ioWrite.buf = NULL;
				asioData.ioWrite.bufLen = 0;
				asioData.ioWrite.whole = false;
				asioData.ioCall = J_AsioDataBase::j_write_e;
				//usleep(1000);
				return J_OK;
			}
		}
	}
	else if (nRet < 0 || (nRet==J_OK && m_streamHeader.frameType==jo_file_end
									|| m_streamHeader.frameType==jo_media_broken))
	{
		return J_SOCKET_ERROR;
	}
	else
	{
		asioData.ioWrite.buf = NULL;
		asioData.ioWrite.bufLen = 0;
		asioData.ioWrite.whole = false;
		asioData.ioCall = J_AsioDataBase::j_write_e;
		//usleep(1);
		return J_OK;
	}
	return nRet;
}
