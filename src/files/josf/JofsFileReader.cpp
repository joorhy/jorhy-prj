#include "JofsFileReader.h"
#include "x_sdk.h"
#include "x_config.h"
#include "x_adapter_manager.h"
#include "x_manager_factory.h"

#define RECORD_INTERVAL	(24 * 60 * 60)
#define TIMER_INTERVAL	128

CNvrFileReader::CNvrFileReader(const char *pResid)
{
	m_resid = pResid;
	m_bPaused = false;
	m_bGoNext = true;
	m_nScale = 1;
	m_pFileId = NULL;
	memset(&m_nextHeader, 0, sizeof(m_nextHeader));
	m_nextTimeStamp = 0;

	//m_timer.Create(TIMER_INTERVAL, CNvrFileReader::TimerThread, (unsigned long)this);
	J_OS::LOGINFO("CNvrFileReader::CNvrFileReader");
}

CNvrFileReader::~CNvrFileReader()
{
	CloseFile();
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
	//TLock(m_locker);
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
		if (m_pFileId == NULL || ftell(m_pFileId) >= m_fileEnd)
		{
			nRet = OpenFile();
			if (nRet != J_OK)
			{
				//TLock(m_locker);
				return nRet;
			}
		}

		int nReadLen = 0;
		if (m_bGoNext)
		{
			nReadLen = fread(&m_nextHeader, 1, sizeof(m_nextHeader), m_pFileId);
			if (nReadLen == 0)
			{
				//J_OS::LOGINFO("offset = %d", ftell(m_pFileId));
				return J_OK;
			}
			m_bGoNext = false;
		}

		if (m_nextTimeStamp != 0
				&& m_nextHeader.timeStamp > m_nextTimeStamp
				&& m_nextHeader.timeStamp - m_nextTimeStamp > 120000)
			return J_FILE_END;

		m_nextTimeStamp = m_nextHeader.timeStamp;
		//if (m_nextTimeStamp >= m_nextHeader.timeStamp)
		{
			streamHeader = m_nextHeader;
			//streamHeader.timeStamp = CTime::Instance()->GetLocalTime(0);
			nReadLen = fread(pBuffer, 1, streamHeader.dataLen, m_pFileId);

			m_bGoNext = true;
		}
		//TUnlock(m_locker);
	}
	return nRet;
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

int CNvrFileReader::SetTime(uint64_t s_time, uint64_t e_time)
{
	//TLock(m_locker);
	int nRet = J_OK;
	nRet = ListRecord(s_time, e_time);
	if (nRet != J_OK)
	{
		//TUnlock(m_locker);
		return nRet;
	}

	nRet = CalcPosition(s_time);
	if (nRet != J_OK)
	{
		//TUnlock(m_locker);
		return nRet;
	}
	m_bGoNext = true;
	m_nextTimeStamp = s_time * 1000;

	//TUnlock(m_locker);
	return J_OK;
}

int CNvrFileReader::SetPosition(int nPos)
{
	return J_OK;
}

int CNvrFileReader::ListRecord(uint64_t beginTime, uint64_t endTime)
{
	r_historyfile *p_historyfile = GetHistoryFile((char *)m_resid.c_str(), (char *)"", beginTime, endTime, CXConfig::GetUrl());
	if (p_historyfile == NULL)
	{
	    J_OS::LOGINFO("CNvrFileReader::ListRecord GetHistoryFile Error");
	    return J_DB_ERROR;
	}
	m_fileVec.clear();

	if (p_historyfile->parm.files.empty())
		return J_OK;

	std::vector<std::string>::iterator it = p_historyfile->parm.files.begin();
	for(;it != p_historyfile->parm.files.end(); it++)
	{
		//J_OS::LOGINFO(it->c_str());
		m_fileVec.push_back(*it);
	}
	delete p_historyfile;

	return J_OK;
}

int CNvrFileReader::OpenFile()
{
	if (m_fileVec.size() < 1)
		return J_FILE_ERROR;

	CloseFile();
	m_frameMap.clear();
	m_iFrameMap.clear();
	std::list<std::string>::iterator it = m_fileVec.begin();
	char fileName[512] = {0};
	char filePath[512] = {0};
	J_RecordInfo recordInfo;
	CManagerFactory::Instance()->GetManager(CXConfig::GetConfigType())->GetRecordInfo(recordInfo);
	sprintf(fileName, "%s/%s", m_file.GetVodDir(recordInfo.vodPath, filePath), (*it).c_str());
	m_fileVec.pop_front();

	if (access(fileName, F_OK) != 0)
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

int CNvrFileReader::CalcPosition(uint64_t timeStamp, uint32_t interval)
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
	//printf("offset = %d %llu %llu\n", it->second.offset, it->second.timeStamp, timeStamp);
	//TLock(m_locker);
	m_nextTimeStamp = it->second.timeStamp;
	//TUnlock(m_locker);

	return J_OK;
}

void CNvrFileReader::OnTimer()
{
	//TLock(m_locker);
	m_nextTimeStamp += (uint32_t)(TIMER_INTERVAL / m_nScale);
	//TUnlock(m_locker);
}
