#ifndef __HIKSTREAM_H_
#define __HIKSTREAM_H_
#ifdef WIN32
#include "x_asio_win.h"
#else
#include "x_asio.h"
#endif
#include "Hikv3Parser.h"

class CHikv3StreamBase : public J_MediaStream
                     , public J_AsioUser
{};

class CHikv3Stream : public J_BaseVideoStream<CHikv3StreamBase>
{
public:
	CHikv3Stream(void *pTCPSocket, j_string_t resid, char *pHeader);
	~CHikv3Stream();

public:
	///J_VideoStream
	virtual int Startup();
	virtual int Shutdown();
	///AsioUser
	virtual j_result_t OnAccept(const J_AsioDataBase *pAsioData, int nRet) { return 0; }
	virtual j_result_t OnRead(const J_AsioDataBase *pAsioData, int nRet) { return 0; }
	virtual j_result_t OnWrite(const J_AsioDataBase *pAsioData, int nRet) { return 0; }
	virtual j_result_t OnBroken(const J_AsioDataBase *pAsioData, int nRet) { return 0; }

private:
	static void *WorkThread(void *param)
	{
		(static_cast<CHikv3Stream *>(param))->OnWork();
		return (void *)0;
	}
	void OnWork();

private:
	int m_nSocket;

	pthread_t m_recvThread;
	bool m_bStartup;
	char *m_pRecvBuff;//[100 * 1024];
	void *m_pTCPSocket;

	CHikv3Parser m_parser;
	std::string m_resid;
};

#endif //~__HIKSTREAM_H_
