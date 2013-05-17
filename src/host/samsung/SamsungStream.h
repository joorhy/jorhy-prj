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
    CSamsungStream(j_void_t *pTCPSocket, j_string_t resid);
    ~CSamsungStream();

public:
    ///J_VideoStream
    virtual j_result_t Startup();
    virtual j_result_t Shutdown();
    ///AsioUser
    virtual j_result_t OnAccept(j_int32_t nfd)
    {
        return J_OK;
    }
    virtual j_result_t OnRead(j_int32_t nfd);
    virtual j_result_t OnWrite(j_int32_t nfd)
    {
        return J_OK;
    }
    virtual j_result_t OnBroken(j_int32_t nfd);

private:
    j_socket_t m_nSocket;
    j_boolean_t m_bStartup;
    j_char_t *m_pRecvBuff;//[100 * 1024];
    j_void_t *m_pTCPSocket;

    CSamsungParser m_parser;
    j_string_t m_resid;

    J_OS::TLocker_t m_locker;
};

#endif //~__SAMSUNGSTREAM_H_
