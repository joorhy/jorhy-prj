#ifndef __SONYSTREAM_H_
#define __SONYSTREAM_H_
#include "SonyParser.h"
#include "x_asio.h"

class CSonyStreamBase : public J_MediaStream
    , public J_AsioUser
{};


class CSonyStream : public J_BaseVideoStream<CSonyStreamBase>
{
public:
	CSonyStream(void *pTCPSocket, std::string resid);
	~CSonyStream();

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
	j_boolean_t m_bStartup;
	j_char_t *m_pRecvBuff;//[100 * 1024];
	j_void_t *m_pTCPSocket;

	CSonyParser m_parser;
	j_string_t m_resid;

	J_OS::TLocker_t m_locker;
};

#endif //~__SONYSTREAM_H_
