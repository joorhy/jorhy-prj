#include "JofsFileReader.h"
#include "x_sdk.h"
#include "x_config.h"
#include "x_adapter_manager.h"
#include "x_manager_factory.h"
#include "x_vod_manager.h"

#define RECORD_INTERVAL	(24 * 60 * 60)
#define TIMER_INTERVAL	128
#define RECORD_BUFF_SIZE 	(1024 * 1024 * 5)
#define JO_FILE_INTERVAL	(120)		//秒

JO_IMPLEMENT_INTERFACE(FileReader, "jofs", CNvrFileReader::Maker)

CNvrFileReader::CNvrFileReader(const char *pResid)
{
	m_resid = pResid;
	m_bPaused = false;
	m_bGoNext = true;
	m_nScale = 1;
	m_pFileId = NULL;
	memset(&m_nextHeader, 0, sizeof(m_nextHeader));
	m_nextTimeStamp = 0;
	
	m_lastTime = 0;
	m_buffer = new CRingBuffer(0, RECORD_BUFF_SIZE);
	m_pBuffer = new char[RECORD_BUFF_SIZE];
	m_bRun = true;

	j_thread_parm parm = {0};
	parm.entry = CNvrFileReader::WorkThread;
	parm.data = this;
	m_thread.Create(parm);
	//m_timer.Create(TIMER_INTERVAL, CNvrFileReader::TimerThread, (unsigned long)this);
	J_OS::LOGINFO("CNvrFileReader::CNvrFileReader");
}

CNvrFileReader::~CNvrFileReader()
{
	m_bRun = false;
	m_thread.Release();
	j_sleep(1000);
	
	J_OS::LOGINFO("CNvrFileReader::~CloseFile");
	TLock(m_locker);
	if (m_buffer != NULL)
		delete m_buffer;
	if (m_pBuffer != NULL)
		delete m_pBuffer;
	J_OS::LOGINFO("CNvrFileReader::Lock(m_locker)");
	CloseFile();
	J_OS::LOGINFO("CNvrFileReader::TUnlock(m_locker)");
	TUnlock(m_locker);
	//m_timer.Destroy();
	J_OS::LOGINFO("CNvrFileReader::~CNvrFileReader");
}

int CNvrFileReader::GetContext(J_MediaContext *&mediaContext)
{
	J_MediaContext *pContext = (J_MediaContext *)malloc(sizeof(J_MediaContext) + 2 * sizeof(J_ContextData));
	if (pContext == NULL)
		return J_MEMORY_ERROR;
	pContext->forcc = JO_MAKE_FORCC('N', 'V', 'R', '0');
	pContext->len = 2 * sizeof(J_ContextData);
	pContext->num = 2;

	long curPosition = ftell(m_pFileId);
	J_StreamHeader streamHeader = {0};
	bool bVideoReady = false;
	bool bAudioReady = false;

	fseek(m_pFileId, sizeof(J_FileHeader), SEEK_SET);
	while (!bVideoReady || !bAudioReady)
	{
		fread(&streamHeader, 1, sizeof(streamHeader), m_pFileId);
		if (streamHeader.frameType == jo_video_i_frame)
		{
			long pos = ftell(m_pFileId);
			J_ContextData *contextVideo = (J_ContextData *)pContext->data;
			contextVideo->forcc = JO_MAKE_FORCC('H', '2', '6', '4');
			contextVideo->len = sizeof(contextVideo->cxt);
			contextVideo->cxt.len = sizeof(contextVideo->cxt.data);
			fread(contextVideo->cxt.data, 1, sizeof(contextVideo->cxt.data), m_pFileId);
			fseek(m_pFileId, pos, SEEK_SET);
			bVideoReady = true;
		}
		else if(streamHeader.frameType == jo_audio_frame)
		{
			long pos = ftell(m_pFileId);
			J_ContextData *contextAudio = (J_ContextData *)(pContext->data + sizeof(J_ContextData));
			contextAudio->forcc = JO_MAKE_FORCC('A', 'A', 'C', '0');
			contextAudio->len = sizeof(contextAudio->cxt);
			contextAudio->cxt.len = 7;
			memset(contextAudio->cxt.data, 0, sizeof(contextAudio->cxt.data));
			fread(contextAudio->cxt.data, 1, 7, m_pFileId);
			fseek(m_pFileId, pos, SEEK_SET);
			bAudioReady = true;
		}
		fseek(m_pFileId, streamHeader.dataLen, SEEK_CUR);
	}
	fseek(m_pFileId, curPosition, SEEK_SET);
	mediaContext = pContext;

	return J_OK;
}

int CNvrFileReader::GetPacket(char *pBuffer, J_StreamHeader &streamHeader)
{
	TLock(m_locker);
	if (!m_bRun)
	{
		TUnlock(m_locker);
		return J_UNKNOW;
	}
	TUnlock(m_locker);
		
	int nRet = J_OK;
	if (m_bPaused)
	{
		streamHeader.dataLen = 0;
		streamHeader.frameType = jo_media_unknow;
		streamHeader.timeStamp = 0;
		streamHeader.frameNum = 0;
	}
	else
	{
		nRet = m_buffer->PopBuffer(pBuffer, streamHeader);
		if (nRet != J_OK)
		{
			streamHeader.dataLen = 0;
			streamHeader.frameType = jo_media_unknow;
			streamHeader.timeStamp = 0;
			streamHeader.frameNum = 0;
		}
	}
	return J_OK;
}

int CNvrFileReader::Pause()
{
	m_bPaused = !m_bPaused;

	return J_OK;
}

int CNvrFileReader::SetScale(float nScale)
{
	m_nScale = nScale;

	return J_OK;
}

int CNvrFileReader::SetTime(j_uint64_t s_time, j_uint64_t e_time)
{
	int nRet = J_OK;
	nRet = ListRecord(s_time, e_time);
	if (nRet != J_OK)
	{
		return nRet;
	}

	nRet = CalcPosition(s_time);
	if (nRet != J_OK)
	{
		return nRet;
	}
	m_bGoNext = true;
	m_nextTimeStamp = s_time * 1000;

	return J_OK;
}

int CNvrFileReader::SetPosition(j_int32_t nPos)
{
	return J_OK;
}

int CNvrFileReader::GetMediaData(j_uint64_t beginTime, j_int32_t nIval)
{
	TLock(m_locker);
	m_lastTime += nIval;
	m_cond.Single();
	TUnlock(m_locker);
	
	return J_OK;
}

int CNvrFileReader::ListRecord(j_uint64_t beginTime, j_uint64_t endTime)
{
	vecFileInfo.clear();
	j_result_t nResult = JoVodManager->SearchVodFiles(m_resid.c_str(), beginTime, endTime, vecFileInfo);
	if (nResult != J_OK)
	{
	    J_OS::LOGINFO("CNvrFileReader::ListRecord GetHistoryFile Error");
	    return J_DB_ERROR;
	}
	//J_OS::LOGINFO("CNvrFileReader::ListRecord No Files start=%d end=%d", beginTime, endTime);

	if (vecFileInfo.empty())
	{
		J_OS::LOGINFO("CNvrFileReader::ListRecord No Files start=%d end=%d", beginTime, endTime);
		return J_OK;
	}
	//测试用
	//m_fileVec.push_back("3_20130527113757533_20130527114000051.josf");
	//m_fileVec.push_back("3_20130527125825086_20130527130026235.josf");

	return J_OK;
}

int CNvrFileReader::OpenFile()
{
	if (vecFileInfo.size() < 1)
		return J_FILE_ERROR;

	CloseFile();
	m_frameMap.clear();
	m_iFrameMap.clear();
	j_vec_file_info_t::iterator it = vecFileInfo.begin();
	char fileName[512] = {0};
	char filePath[512] = {0};
	sprintf(fileName, "%s/%s/%s/%s", m_file.GetVodDir(CXConfig::GetVodPath(), filePath), m_resid.c_str()
		, JoTime->GetDate(it->tStartTime+JO_FILE_INTERVAL).c_str(), it->fileName.c_str());
	vecFileInfo.pop_front();

#ifdef WIN32
	if(_access(fileName, 0) != 0)
#else
	if (access(fileName, F_OK) != 0)
#endif
	{
		J_OS::LOGERROR("CNvrFileReader::OpenFile() file not found, filename = %s", fileName);
		return J_FILE_ERROR;
	}

	m_pFileId = fopen(fileName, "rb+");
	if (m_pFileId == NULL)
	{
		J_OS::LOGERROR("CNvrFileReader::OpenFile() fopen error");
		return J_FILE_ERROR;
	}

	J_FileHeader bodyHeader;
	fread(&bodyHeader, 1, sizeof(J_FileHeader), m_pFileId);
	if (memcmp(bodyHeader.type, "body", strlen("body")) != 0)
	{
		J_OS::LOGINFO("CNvrFileReader::OpenFile() body File Broken");
		return J_FILE_BROKEN;
	}

	fseek(m_pFileId, bodyHeader.length, SEEK_CUR);
	m_fileEnd = ftell(m_pFileId);
	//J_OS::LOGINFO("m_fileEnd = %d", m_fileEnd);

	J_FileHeader indexHeader;
	fread(&indexHeader, 1, sizeof(J_FileHeader), m_pFileId);
	if (memcmp(indexHeader.type, "head", strlen("head")) != 0)
	{
		J_OS::LOGINFO("CFileReader::OpenFileByName head File Broken");
		return J_FILE_BROKEN;
	}

	J_FrameHeader frameHeader;
	int nIndexLen = indexHeader.length;
	while (nIndexLen > (int)sizeof(J_FileHeader))
	{
		fread(&frameHeader, 1, sizeof(J_FrameHeader), m_pFileId);
		m_frameMap[frameHeader.timeStamp] = frameHeader;

		//存储关键帧索引
		if (frameHeader.frameType == jo_video_i_frame)
			m_iFrameMap[frameHeader.timeStamp] = frameHeader;
		nIndexLen -= sizeof(J_FileHeader);
	}
	fseek(m_pFileId, sizeof(J_FileHeader), SEEK_SET);

	return J_OK;
}

void CNvrFileReader::CloseFile()
{
	if (m_pFileId != NULL)
	{
		fclose(m_pFileId);
		m_pFileId = NULL;
	}
}

int CNvrFileReader::CalcPosition(j_uint64_t timeStamp, j_uint32_t interval)
{
	int nRet = J_OK;
	nRet = OpenFile();
	if (nRet != J_OK)
		return nRet;

	FrameMap::iterator it = m_iFrameMap.begin();
	if (it->second.timeStamp > ((timeStamp + interval) * 1000))
	{
	    J_OS::LOGINFO("CFileReader::CalcPosition J_OUT_RANGE");
		return J_OUT_RANGE;
	}

	for (; it != m_iFrameMap.end(); it++)
	{
		if(it->second.timeStamp >= (timeStamp * 1000))
		{
			if (it != m_iFrameMap.begin())
				--it;
			break;
		}
	}
	if (it == m_iFrameMap.end())
	{
		J_OS::LOGINFO("CFileReader::CalcPosition J_NO_RESOURCE");
		return CalcPosition(timeStamp, interval);
	}

	fseek(m_pFileId, it->second.offset, SEEK_SET);
	m_nextTimeStamp = it->second.timeStamp;

	return J_OK;
}

void CNvrFileReader::OnTimer()
{
	m_nextTimeStamp += (j_uint32_t)(TIMER_INTERVAL / m_nScale);
}

void CNvrFileReader::OnWork()
{
	int nRet = J_OK;
	J_StreamHeader streamHeader;
	while (m_bRun)
	{
		if (m_lastTime == 0)
		{
			/*TLock(m_mux);
			if (m_cond.TimeWait(m_mux, 1, 0) < 0)
			{
				streamHeader.dataLen = 0;
				streamHeader.frameType = jo_file_end;
				streamHeader.timeStamp = 0;
				streamHeader.frameNum = 0;
				m_buffer->PushBuffer(m_pBuffer, streamHeader);
				TUnlock(m_mux);
				return;
			}
			TUnlock(m_mux);*/
			j_sleep(1);
			continue;
		}
		if (m_buffer->GetIdleLength() != RECORD_BUFF_SIZE)
		{
			j_sleep(1);
			continue;
		}
		//J_OS::LOGINFO("1");
		TLock(m_locker);
		//J_OS::LOGINFO("2");
		if (m_pFileId == NULL || ftell(m_pFileId) >= m_fileEnd)
		{
			nRet = OpenFile();
			if (nRet != J_OK)
			{
				//未处理
				J_OS::LOGINFO("CNvrFileReader::OnWork() error %d", nRet);
				m_bRun = false;
				//J_OS::LOGINFO("3");
				TUnlock(m_locker);
				//J_OS::LOGINFO("4");
				break;
			}
		}

		int nReadLen = 0;
		if (m_bGoNext)
		{
			nReadLen = fread(&m_nextHeader, 1, sizeof(m_nextHeader), m_pFileId);
			if (nReadLen == 0)
			{
				//J_OS::LOGINFO("5");
				TUnlock(m_locker);
				//J_OS::LOGINFO("6");
				continue;
			}
			m_bGoNext = false;
		}

		if (m_nextTimeStamp != 0
				&& m_nextHeader.timeStamp > m_nextTimeStamp
				&& m_nextHeader.timeStamp - m_nextTimeStamp > 120000)
		{
			//未处理
			streamHeader.dataLen = 0;
			streamHeader.frameType = jo_file_end;
			streamHeader.timeStamp = 0;
			streamHeader.frameNum = 0;
		}
		m_nextTimeStamp = m_nextHeader.timeStamp;
		streamHeader = m_nextHeader;
		nReadLen = fread(m_pBuffer, 1, streamHeader.dataLen, m_pFileId);
		//J_OS::LOGINFO("7");
		TUnlock(m_locker);
		//J_OS::LOGINFO("8");
		
		m_buffer->PushBuffer(m_pBuffer, streamHeader);
		m_lastTime -= 40;
		m_bGoNext = true;
	}
}
