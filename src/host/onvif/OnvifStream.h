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
	COnvifStream(void *pTCPSocket, j_string_t resid);
	~COnvifStream();

public:
	///J_VideoStream
	virtual int Startup();
	virtual int Shutdown();
    ///AsioUser
	virtual void OnAccept(const J_AsioDataBase *pAsioData, int nRet) {}
	virtual void OnRead(const J_AsioDataBase *pAsioData, int nRet);
	virtual void OnWrite(const J_AsioDataBase *pAsioData, int nRet) {}
	virtual void OnBroken(const J_AsioDataBase *pAsioData, int nRet);

private:
	enum 
	{
		ONVIF_READ_HEAD = 1,
		ONVIF_READ_DATA,
	};
	j_socket_t m_nSocket;
	j_boolean_t m_bStartup;
	j_char_t *m_pRecvBuff;//[100 * 1024];
	j_void_t *m_pTCPSocket;

	COnvifParser m_parser;
	j_string_t m_resid;

	J_OS::TLocker_t m_locker;
	J_AsioDataBase m_asioData;
	j_int32_t m_nState;
};

#endif //~__ONVIFSTREAM_H_
