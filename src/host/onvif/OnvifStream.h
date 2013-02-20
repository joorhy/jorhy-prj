#ifndef __ONVIFSTREAM_H_
#define __ONVIFSTREAM_H_
#include "OnvifParser.h"
#include "x_asio.h"

class COnvifStreamBase : public J_MediaStream
    , public J_AsioUser
{};


class COnvifStream : public J_BaseVideoStream<COnvifStreamBase>
{
public:
	COnvifStream(void *pTCPSocket, std::string resid);
	~COnvifStream();

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
	int m_nSocket;
	bool m_bStartup;
	char *m_pRecvBuff;//[100 * 1024];
	void *m_pTCPSocket;

	COnvifParser m_parser;
	std::string m_resid;

	J_OS::TLocker_t m_locker;
};

#endif //~__ONVIFSTREAM_H_
