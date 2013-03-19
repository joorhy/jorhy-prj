#ifndef __STREAMRECORD_H_
#define __STREAMRECORD_H_
#include "j_includes.h"
#include "x_sdk.h"
#include "x_time.h"
#include "x_file.h"
#include "x_thread_pool.h"

class CStreamRecordBase 
{};

class CStreamRecord : public J_BaseAdapter<CStreamRecordBase>
{
public:
	CStreamRecord();
	~CStreamRecord();

public:
	int StartRecord(const char *pResid);
	int StopRecord(const char *pResid);

	int StartPreRecord(const char *pResid, int nStreamType, int nTimeLen, bool bPreRecord = true);
	int StopPreRecord(const char *pResid, int nStreamType, bool isStopVideo = true);

    int OnWriteVideo();
	int OnRecord();

private:
	int CreateFile(char *pFileName);
	int CloseFile();
	int Init();
	void ParserAndSave(const char *pData, J_StreamHeader &streamHeader);

private:
	int m_nSocket;			//录像时,m_nSocket恒为0
	CRingBuffer *m_pRingBuffer;
	bool m_bStart;
	char *m_pDataBuff;
	//char *m_pPacketBuff;
	std::string m_resid;

	FILE *m_fdBody;
	FILE *m_fdHead;
	char *m_headBuff;
	char m_fileName[128];
	char m_vodDir[128];

	J_FileHeader m_fileHead;
	J_FileHeader m_fileBody;

	J_FrameHeader m_frameHead;
	unsigned long m_nFileOffset;
	unsigned long m_nHeaderOffset;
	//unsigned long m_nTimeStamp;	//单位毫秒

	int m_nPacketLen;
	bool m_bStartRecord;
	bool m_bStartPre;

	s_record m_record;
	s_fileinfo m_fileInfo;
	CXFile m_file;
};

class CRecordTask : public J_Task
{
	//friend class CStreamRecord;
	public:
		CRecordTask() { m_pParam = NULL; }
		~CRecordTask() {}
		/// J_Task
		virtual int Run()
		{
			CStreamRecord *pRecorder = static_cast<CStreamRecord *>(m_pParam);
			if (pRecorder)
				pRecorder->OnRecord();
				
			return 0;
		}
};

#endif // ~__STREAMRECORD_H_
