#ifndef __JOSTREAM_H_
#define __JOSTREAM_H_
//#include "JoParser.h"
#include "x_asio.h"

class CJoStreamBase : public J_MediaStream
    , public J_AsioUser
{};


class CJoStream : public J_BaseVideoStream<CJoStreamBase>
{
public:
	CJoStream(void *pTCPSocket, std::string resid);
	~CJoStream();

public:
	///J_VideoStream
	virtual int Startup();
	virtual int Shutdown();
    ///AsioUser
    virtual int OnAccept(int nfd)
    {
        return J_OK;
    }
    virtual int OnRead(int nfd);
    virtual int OnWrite(int nfd)
    {
        return J_OK;
    }
    virtual int OnBroken(int nfd);

private:
	j_socket_t m_nSocket;
	bool m_bStartup;
	char *m_pRecvBuff;//[100 * 1024];
	void *m_pTCPSocket;

	//CJoParser m_parser;
	std::string m_resid;

	J_OS::TLocker_t m_locker;
};

#endif //~__JOSTREAM_H_
