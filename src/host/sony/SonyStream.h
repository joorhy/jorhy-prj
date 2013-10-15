#ifndef __SONYSTREAM_H_
#define __SONYSTREAM_H_
#include "SonyParser.h"
#ifdef WIN32
#include "x_asio_win.h"
#else
#include "x_asio.h"
#endif

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
	virtual j_result_t OnAccept(const J_AsioDataBase *pAsioData, int nRet) { return 0; }
	virtual j_result_t OnRead(const J_AsioDataBase *pAsioData, int nRet);
	virtual j_result_t OnWrite(const J_AsioDataBase *pAsioData, int nRet) { return 0; }
	virtual j_result_t OnBroken(const J_AsioDataBase *pAsioData, int nRet);

private:
	j_socket_t m_nSocket;
	j_boolean_t m_bStartup;
	j_char_t *m_pRecvBuff;//[100 * 1024];
	j_void_t *m_pTCPSocket;
	J_AsioDataBase m_asioData;

	CSonyParser m_parser;
	j_string_t m_resid;

	J_OS::TLocker_t m_locker;
};

#endif //~__SONYSTREAM_H_
