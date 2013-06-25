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
	virtual void OnAccept(const J_AsioDataBase *pAsioData, int nRet) {}
	virtual void OnRead(const J_AsioDataBase *pAsioData, int nRet);
	virtual void OnWrite(const J_AsioDataBase *pAsioData, int nRet) {}
	virtual void OnBroken(const J_AsioDataBase *pAsioData, int nRet);

private:
	enum 
	{
		JO_READ_HEAD = 1,
		JO_READ_DATA,
	};
	j_socket_t m_nSocket;
	j_boolean_t m_bStartup;
	j_char_t *m_pRecvBuff;//[100 * 1024];
	void *m_pTCPSocket;

	//CJoParser m_parser;
	j_string_t m_resid;

	J_OS::TLocker_t m_locker;
	J_AsioDataBase m_asioData;
	j_int32_t m_nState;
	J_DataHead m_dataHead;
};

#endif //~__JOSTREAM_H_
