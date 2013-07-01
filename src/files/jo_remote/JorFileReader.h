#ifndef __JOR_FILE_READER_H_
#define __JOR_FILE_READER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
#include "x_socket.h"
#include "x_thread.h"

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
	virtual int SetTime(j_uint64_t s_time, j_uint64_t e_time);
	virtual int SetPosition(int nPos);
	virtual int GetMediaData(j_uint64_t beginTime, int nIval);

private:
	int OpenFile(j_uint64_t s_time, j_uint64_t e_time);
	void CloseFile();
#ifdef WIN32
	static unsigned X_JO_API WorkThread(void *pUser)
#else
	static void *WorkThread(void *pUser)
#endif
	{
		CJorFileReader *pThis = (CJorFileReader *)pUser;
			pThis->OnWork();
		return 0;
	}
	void OnWork();

private:
	J_OS::CTCPSocket *m_recvSocket;
	j_string_t m_resid;
	CJorFileHelper m_jorHelper;
	j_boolean_t m_bPaused;
	J_OS::TLocker_t m_locker;
	
	CJoThread m_thread;
	J_OS::CTLock m_mux;
	J_OS::CXCond m_cond;
	j_int32_t m_lastTime;
	CRingBuffer *m_buffer;
	j_boolean_t m_bRun;
};

#endif //~__JOR_FILE_READER_H_
