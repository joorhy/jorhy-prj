#ifndef __JOR_FILE_READER_H_
#define __JOR_FILE_READER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
#include "x_socket.h"
#include <pthread.h>

#include "JorFileHelper.h"

class CJorFileReader : public J_FileReader
{
public:
	CJorFileReader(const char *pResid);
	~CJorFileReader();

    static int Maker(J_Obj *&pObj, const char *pResid)
	{
		pObj = new CJorFileReader(pResid);
		return J_OK;
	}

public:
	virtual int GetContext(J_MediaContext *&mediaContext);
	virtual int GetPacket(char *pBuffer, J_StreamHeader &streamHeader);
	virtual int Pause();
	virtual int SetScale(float nScale = 1);
	virtual int SetTime(uint64_t s_time, uint64_t e_time);
	virtual int SetPosition(int nPos);
	virtual int GetMediaData(j_uint64_t beginTime, int nIval);

private:
	int OpenFile(uint64_t s_time, uint64_t e_time);
	void CloseFile();
	static void *WorkThread(void *pUser)
	{
		CJorFileReader *pThis = (CJorFileReader *)pUser;
			pThis->OnWork();
		return (void *)0;
	}
	void OnWork();

private:
	J_OS::CTCPSocket *m_recvSocket;
	std::string m_resid;
	CJorFileHelper m_jorHelper;
	bool m_bPaused;
	J_OS::TLocker_t m_locker;
	
	pthread_t m_thread;
	pthread_mutex_t m_mux;
	pthread_cond_t m_cond;
	int m_lastTime;
	CRingBuffer *m_buffer;
	bool m_bRun;
};

FILEREADER_BEGIN_MAKER(jorf)
	FILEREADER_ENTER_MAKER("jorf", CJorFileReader::Maker)
FILEREADER_END_MAKER()

#endif //~__JOR_FILE_READER_H_
