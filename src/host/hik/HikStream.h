#ifndef __HIKSTREAM_H_
#define __HIKSTREAM_H_
#include "x_asio.h"
#include "HikParser.h"
#include "HikParser2.h"

class CHikStreamBase : public J_MediaStream
                     , public J_AsioUser
{};

class CHikStream : public J_BaseVideoStream<CHikStreamBase>
{
public:
	CHikStream(void *pTCPSocket, std::string resid);
	~CHikStream();

public:
	///J_VideoStream
	virtual int Startup();
	virtual int Shutdown();
	///AsioUser
	virtual int OnAccept(int nfd) { return J_OK; }
	virtual int OnRead(int nfd);
	virtual int OnWrite(int nfd) { return J_OK; }
	virtual int OnBroken(int nfd);
private:
	j_socket_t m_nSocket;

	pthread_t m_recvThread;
	bool m_bStartup;
	char *m_pRecvBuff;//[100 * 1024];
	void *m_pTCPSocket;

	CHikParser2 m_parser;
	std::string m_resid;

	J_OS::TLocker_t m_locker;
};

#endif //~__HIKSTREAM_H_
