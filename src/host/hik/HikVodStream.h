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
	CHikVodStream(void *pOwner, int nChannelNum);
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
	static void *WorkThread(void *param)
	{
		(static_cast<CHikVodStream *>(param))->OnWork();
		return (void *)0;
	}
	void OnWork();
	static void *ParserThread(void *param)
	{
		(static_cast<CHikVodStream *>(param))->OnParser();
		return (void *)0;
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

	pthread_t m_parserThread;
	pthread_t m_recvThread;
	bool m_bPlay;
	char *m_pRecvBuff;
	char *m_pPackBuff;

	CHikParser m_parser;
	bool m_bPaused;
	unsigned int m_fileTotleLen;

	FILE *m_pWrite;
	FILE *m_pRead;
	J_OS::TLocker_t m_fileLock;
	unsigned long m_fileLen;
	unsigned long m_readFileLen;

	int m_nChannelNum;
	bool m_bEndFile;
	bool m_bFirstFile;

	unsigned int m_nLastRecvTime;	//单位 ms
	unsigned int m_nDuration;
	std::queue<std::string> m_fileQue;
	std::string m_curFileName;
};

#endif //~__HIKVODSTREAM_H_
