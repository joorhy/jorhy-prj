#ifndef __JOFS_FILE_READER_H_
#define __JOFS_FILE_READER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
#include "x_time.h"
#include "x_file.h"
#include "x_lock.h"
#include "x_timer.h"
#include "x_thread.h"

class CNvrFileReader : public J_FileReader
{
public:
	CNvrFileReader(const char *pResid);
	~CNvrFileReader();

    static int Maker(J_Obj *&pObj, const char *pResid)
	{
		pObj = new CNvrFileReader(pResid);
		return J_OK;
	}

public:
	virtual int GetContext(J_MediaContext *&mediaContext);
	virtual int GetPacket(j_char_t *pBuffer, J_StreamHeader &streamHeader);
	virtual int Pause();
	virtual int SetScale(float nScale = 1);
	virtual int SetTime(j_uint64_t s_time, j_uint64_t e_time);
	virtual int SetPosition(j_int32_t nPos);
	virtual int GetMediaData(j_uint64_t beginTime, j_int32_t nIval);

private:
	int ListRecord(j_uint64_t beginTime, j_uint64_t endTime);
	int OpenFile();
	void CloseFile();
	int CalcPosition(j_uint64_t timeStamp, j_uint32_t interval = 120);

	static void TimerThread(unsigned long ulUser)
	{
		CNvrFileReader *pThis = static_cast<CNvrFileReader *>((void *)ulUser);
		if (pThis != NULL)
			pThis->OnTimer();
	}
	void OnTimer();
#ifdef WIN32
	static unsigned X_JO_API WorkThread(void *pUser)
#else
	static void *WorkThread(void *pUser)
#endif
	{
		CNvrFileReader *pThis = (CNvrFileReader *)pUser;
			pThis->OnWork();
		return 0;
	}
	void OnWork();

private:
	j_vec_file_info_t vecFileInfo;
	typedef std::map<j_uint64_t, J_FrameHeader> FrameMap;
	FrameMap m_frameMap;
	FrameMap m_iFrameMap;
	j_string_t m_resid;
	J_OS::CTimer m_timer;
	J_OS::TLocker_t m_locker;

	CXFile m_file;
	FILE *m_pFileId;
	float m_nScale;
	j_boolean_t m_bPaused;
	j_boolean_t m_bGoNext;
	long m_fileEnd;
	J_StreamHeader m_nextHeader;
	volatile j_uint64_t m_nextTimeStamp;
	
	CJoThread m_thread;
	J_OS::CTLock m_mux;
	J_OS::CXCond m_cond;
	j_int32_t m_lastTime;
	CRingBuffer *m_buffer;
	j_char_t *m_pBuffer;
	j_boolean_t m_bRun;
};

#endif //~__JOFS_FILE_READER_H_
