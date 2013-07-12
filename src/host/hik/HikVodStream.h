#ifndef __HIKVODSTREAM_H_
#define __HIKVODSTREAM_H_
#include "x_socket.h"
#include "x_timer.h"
#include "x_lock.h"
#include "x_time.h"
#include "HikAdapter.h"
#include "HikParser.h"
#include "HikType.h"

class CHikVodStream : public J_RemoteVodStream
{
public:
	CHikVodStream(J_Obj *pOwner, int nChannelNum);
	~CHikVodStream();

public:
	///J_VideoVod
	virtual int Play(time_t beginTime, time_t endTime, CRingBuffer *&pRingBuffer);
	virtual int Stop();
	virtual int Pause();
	virtual int SetSpeed(int nSpeed, bool bFlag);
	virtual int SetPos();

private:
	static void OnTimer(void *pUser)
	{
		(static_cast<CHikVodStream *>((void *)pUser))->ExchangeData();
	}
	void ExchangeData();

#ifdef WIN32
	static unsigned X_JO_API WorkThread(void *param)
#else
	static void *WorkThread(void *param)
#endif
	{
		(static_cast<CHikVodStream *>(param))->OnWork();
		return 0;
	}
	void OnWork();

#ifdef WIN32
	static unsigned X_JO_API ParserThread(void *param)
#else
	static void *ParserThread(void *param)
#endif
	{
		(static_cast<CHikVodStream *>(param))->OnParser();
		return 0;
	}
	void OnParser();
	void Convert2HikTime(time_t utcTime, HikTime &hikTime);

	FILE *CreateFile();
	void ClearnQue();

private:
	CRingBuffer *m_pRingBuffer;
	CHikAdapter *m_pAdapter;

	J_OS::CTCPSocket *m_recvSocket;
	J_OS::CTimer m_timer;

	CJoThread m_parserThread;
	CJoThread m_recvThread;
	j_boolean_t m_bPlay;
	j_char_t *m_pRecvBuff;
	j_char_t *m_pPackBuff;

	CHikParser m_parser;
	j_boolean_t m_bPaused;
	j_uint32_t m_fileTotleLen;

	FILE *m_pWrite;
	FILE *m_pRead;
	J_OS::TLocker_t m_fileLock;
	j_uint32_t m_fileLen;
	j_uint32_t m_readFileLen;

	j_int32_t m_nChannelNum;
	j_boolean_t m_bEndFile;
	j_boolean_t m_bFirstFile;

	j_uint32_t m_nLastRecvTime;	//单位 ms
	j_uint32_t m_nDuration;
	std::queue<j_string_t> m_fileQue;
	j_string_t m_curFileName;
};

#endif //~__HIKVODSTREAM_H_
