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
	virtual void OnAccept(const J_AsioDataBase &asioData, int nRet) {}
	virtual void OnRead(const J_AsioDataBase &asioData, int nRet);
	virtual void OnWrite(const J_AsioDataBase &asioData, int nRet) {}
	virtual void OnBroken(const J_AsioDataBase &asioData, int nRet);
private:
	enum 
	{
		HIK_READ_HEAD = 1,
		HIK_READ_PS_HEAD,
		HIK_READ_DATA,
	};
	j_socket_t m_nSocket;

	pthread_t m_recvThread;
	bool m_bStartup;
	char *m_pRecvBuff;//[100 * 1024];
	void *m_pTCPSocket;

	CHikParser2 m_parser;
	std::string m_resid;

	J_OS::TLocker_t m_locker;
	J_AsioDataBase m_asioData;
	j_int32_t m_nState;
	j_int32_t m_nOffset;
};

#endif //~__HIKSTREAM_H_
