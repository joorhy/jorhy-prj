#ifndef __SAMSUNGSTREAM_H_
#define __SAMSUNGSTREAM_H_
#include "SamsungParser.h"
#include "x_asio.h"

class CSamsungStreamBase : public J_MediaStream
    , public J_AsioUser
{};

class CSamsungStream : public J_BaseVideoStream<CSamsungStreamBase>
{
public:
    CSamsungStream(void *pTCPSocket, std::string resid);
    ~CSamsungStream();

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

    CSamsungParser m_parser;
    std::string m_resid;

    J_OS::TLocker_t m_locker;
};

#endif //~__SAMSUNGSTREAM_H_
