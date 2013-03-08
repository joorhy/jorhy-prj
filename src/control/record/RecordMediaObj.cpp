#include "x_adapter_manager.h"
#include "RecordMediaObj.h"
#include "x_config.h"
#include "x_manager_factory.h"

#define DATA_BUFF_SIZE (1024 * 1024)
#define HEAD_BUFF_SIZE (1024 * 1024)
CStreamRecord::CStreamRecord()
{
	m_nSocket = 1;
	m_bStart = false;
	m_fdHead = NULL;
	m_fdBody = NULL;
	m_bStartRecord = false;
	m_bStartPre = false;
	m_nPacketLen = 0;
	m_pDataBuff = new char[DATA_BUFF_SIZE];
	m_headBuff = new char[HEAD_BUFF_SIZE];
	m_fileInfo.stime = 0;
	m_resid.clear();
	m_nHeaderOffset = 0;

	J_OS::LOGINFO("CStreamRecord::CStreamRecord created");
}

CStreamRecord::~CStreamRecord()
{
    if (m_headBuff != NULL)
        delete m_headBuff;

	if (m_fdHead != NULL)
		fclose(m_fdHead);

	if (m_fdBody != NULL)
		fclose(m_fdBody);

	if (m_pDataBuff != NULL)
		delete m_pDataBuff;

	J_OS::LOGINFO("CStreamRecord::CStreamRecord distroyed");
}

int CStreamRecord::StartRecord(const char *pResid)
{
	if (m_bStart == true)
		return J_OK;

	if (m_resid.empty())
		m_resid = pResid;

    Init();
	int nRet = StartPreRecord(pResid, 0, false);
	if (nRet < 0)
	{
		J_OS::LOGINFO("CStreamRecord::StartPreRecord StartRecord error ret = %d", nRet);
		return nRet;
	}

	m_bStart = true;
	if (CreateFile(NULL) != J_OK)
		return J_FILE_ERROR;

	J_OS::LOGINFO("CStreamRecord::StartRecord socket =  %d start", m_nSocket);

	return J_OK;
}

int CStreamRecord::StopRecord(const char *pResid)
{
	if (m_bStart)
	{
		m_bStart = false;

		int nRet = J_OK;
		if (m_bStartPre)
			nRet= StopPreRecord(pResid, false);
		else
			nRet= StopPreRecord(pResid, true);

		if (nRet < 0)
		{
			J_OS::LOGINFO("CStreamRecord::StopRecord StopRecord error ret = %d", nRet);
			return nRet;
		}

		m_bStartRecord = false;
		CloseFile();

		//J_Release(this);

		J_OS::LOGINFO("CStreamRecord::StopRecord socket =  %d stop", m_nSocket);
	}

	return J_OK;
}

int CStreamRecord::StartPreRecord(const char *pResid, int nStreamType, int nTimeLen, bool bPreRecord)
{
	if (m_bStartPre)
		return J_OK;

	J_Add_Ref(this);

	int nRet = CAdapterManager::Instance()->StartVideo(pResid, nStreamType, m_nSocket);
	if (nRet < 0)
	{
		J_OS::LOGINFO("CStreamRecord::StartPreRecord StartVideo error ret = %d", nRet);
		return nRet;
	}

	nRet = CAdapterManager::Instance()->GetRingBuffer(pResid, nStreamType, m_nSocket, m_pRingBuffer);
	if (nRet < 0)
	{
		J_OS::LOGINFO("CStreamRecord::StartPreRecord GetRingBuffer error ret = %d", nRet);
		return nRet;
	}
	m_pRingBuffer->ResetBufferSize(nTimeLen * 512 * 1024);
	m_pRingBuffer->SetPreFrameNum(nTimeLen * 25);

	m_bStartPre = bPreRecord;

	return J_OK;
}

int CStreamRecord::StopPreRecord(const char *pResid, int nStreamType, bool isStopVideo)
{
	if (!isStopVideo)
		return J_OK;

	int nRet = CAdapterManager::Instance()->StopVideo(pResid, nStreamType, m_nSocket);
	if (nRet < 0)
	{
		J_OS::LOGINFO("CStreamRecord::StopPreRecord StopVideo error ret = %d", nRet);
		return nRet;
	}

	if (m_bStartPre)
		m_bStartPre = false;

	return J_OK;
}

int CStreamRecord::OnWriteVideo()
{
    J_StreamHeader streamHeader = {0};
    int nRet = m_pRingBuffer->PopBuffer(m_pDataBuff, streamHeader);
    if (nRet == J_OK && streamHeader.dataLen > 0)
    {
        if (streamHeader.frameType == jo_media_broken)
        {
            CloseFile();
            //m_fileInfo.etime = streamHeader.timeStamp / 1000;
            m_record.filenum.push_back(m_fileInfo);
			//J_OS::LOGINFO(m_fileInfo.file.c_str());
            GetRecordNotice(m_record, CXConfig::GetUrl());
            m_fileInfo.stime = streamHeader.timeStamp / 1000;
            m_record.filenum.clear();
            return J_DEV_BROKEN;
        }

        ParserAndSave(m_pDataBuff, streamHeader);
    }

	return J_OK;
}

void CStreamRecord::ParserAndSave(const char *pData, J_StreamHeader &streamHeader)
{
	if (m_fileInfo.stime == 0)
		m_fileInfo.stime = streamHeader.timeStamp / 1000;

	J_RecordInfo recordInfo;
	CManagerFactory::Instance()->GetManager(CXConfig::GetConfigType())->GetRecordInfo(recordInfo);
	if (((time_t)(streamHeader.timeStamp / 1000) - m_fileInfo.stime) > (int32_t)recordInfo.timeInterval
        || m_nHeaderOffset + sizeof(m_frameHead) > HEAD_BUFF_SIZE)
	{
	    CloseFile();
		m_record.filenum.push_back(m_fileInfo);;
		GetRecordNotice(m_record, CXConfig::GetUrl());
		m_fileInfo.stime = streamHeader.timeStamp / 1000;
		m_record.filenum.clear();
		CreateFile(NULL);
	}

	bool bIsKeyFrame = (streamHeader.frameType == jo_video_i_frame);
	bool bIsVideo = (streamHeader.frameType == jo_video_i_frame || streamHeader.frameType == jo_video_p_frame);

	memset(&m_frameHead, 0, sizeof(m_frameHead));
	if (bIsKeyFrame && !m_bStartRecord)
		m_bStartRecord = true;
	if (streamHeader.dataLen > 0 && m_bStartRecord)
	{
		m_nPacketLen += streamHeader.dataLen + sizeof(streamHeader);
		if (bIsVideo)
		{
			m_frameHead.frameType = streamHeader.frameType;
			m_frameHead.length = m_nPacketLen;
			m_frameHead.offset = m_nFileOffset;
			m_frameHead.timeStamp = streamHeader.timeStamp;

			//m_nTimeStamp += 40;
			//存储索引信息
			//fwrite(&m_frameHead, 1, sizeof(m_frameHead), m_fdHead);
			memcpy(m_headBuff + m_nHeaderOffset, &m_frameHead, sizeof(m_frameHead));
			m_fileHead.length += sizeof(m_frameHead);
			m_nHeaderOffset += sizeof(m_frameHead);
			m_nPacketLen = 0;
		}
		//if (streamHeader.dataLen > 65535)
		//	printf("dataLen = %d\n", streamHeader.dataLen);
		//存储数据
		fwrite(&streamHeader, 1, sizeof(streamHeader), m_fdBody);
		m_nFileOffset += sizeof(streamHeader);
		m_fileBody.length += sizeof(streamHeader);
		fwrite(pData, 1, streamHeader.dataLen, m_fdBody);
		m_nFileOffset += streamHeader.dataLen;
		m_fileBody.length += streamHeader.dataLen;
	};
}

int CStreamRecord::CreateFile(char *pFileName)
{
	memset(m_fileName, 0, sizeof(m_fileName));
	memset(&m_fileHead, 0, sizeof(J_FileHeader));
	memset(&m_fileBody, 0, sizeof(J_FileHeader));

	memcpy(m_fileHead.type, "head", 4);
	memcpy(m_fileBody.type, "body", 4);

	sprintf(m_fileName, "%s_%s", m_resid.c_str(), CTime::Instance()->GetLocalTime().c_str());
	char fileName[256] = {0};
	sprintf(fileName, "%s/.temp/%s", m_vodDir, m_fileName);

	m_record.resid = m_resid;
	//m_fileInfo.file = fileName;
	//m_fileInfo.stime = time(0);

	m_fdBody = fopen(fileName, "wb+");
	if (m_fdBody == NULL)
	{
		J_OS::LOGERROR("CStreamRecord::CreateFile fopen error");
		return J_FILE_ERROR;
	}

	//if (pFileName != NULL)
	//{
	//	memcpy(pFileName, m_fileName, strlen(m_fileName));
	//}

	//预留NVRFileHeader存储空间
	fseek(m_fdBody, sizeof(J_FileHeader), SEEK_SET);
	m_nFileOffset = sizeof(J_FileHeader);
	m_nPacketLen = 0;

	return J_OK;
}

int CStreamRecord::CloseFile()
{
	if (m_fdBody == NULL/* || m_fdHead == NULL*/)
	{
		return J_FILE_ERROR;
	}

	//保存索引头信息
	fwrite(&m_fileHead, sizeof(J_FileHeader), 1, m_fdBody);
	fwrite(m_headBuff, 1, m_nHeaderOffset, m_fdBody);
	m_nHeaderOffset = 0;

	//保存数据头信息
	fseek(m_fdBody, 0, SEEK_SET);
	fwrite(&m_fileBody, 1, sizeof(J_FileHeader), m_fdBody);
	if (fclose(m_fdBody) != 0)
	{
		J_OS::LOGERROR("CStreamRecord::CloseFile fopen error");
	}
	m_fdBody = NULL;

	char oldFileName[256] = {0};
	char newFileName[256] = {0};
	char fileName[128] = {0};
	sprintf(oldFileName, "%s/.temp/%s", m_vodDir, m_fileName);
	std::string strETime;
	m_fileInfo.etime = CTime::Instance()->GetLocalTime(strETime);
	sprintf(fileName, "%s_%s.josf", m_fileName, strETime.c_str());
	sprintf(newFileName, "%s/%s", m_vodDir, fileName);

	//修改文件名
    m_file.RenameFile(oldFileName, newFileName);
    m_fileInfo.file = fileName;
	//J_OS::LOGINFO(m_fileInfo.file.c_str());

	return J_OK;
}

int CStreamRecord::Init()
{
    memset(m_vodDir, 0, sizeof(m_vodDir));
    J_RecordInfo recordInfo;
	CManagerFactory::Instance()->GetManager(CXConfig::GetConfigType())->GetRecordInfo(recordInfo);
	m_file.GetVodDir(recordInfo.vodPath, m_vodDir);
	char vodDirTemp[256] = {0};
	sprintf(vodDirTemp, "%s/.temp", m_vodDir);
	m_file.CreateDir(vodDirTemp);
	m_file.DeltmpByResid(vodDirTemp, m_resid.c_str());

    return J_OK;
}


