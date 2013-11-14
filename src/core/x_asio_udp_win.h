#ifndef __X_ASIO_UDP_H_
#define __X_ASIO_UDP_H_
#include "j_includes.h"
#include "j_type.h"
#include "x_lock.h"
#include "x_socket.h"
#include "x_thread.h"

class JO_API CXUdpAsio
{
public:
	CXUdpAsio();
	~CXUdpAsio();

public:
	int Init(j_int32_t nPort, J_Obj *ioUser);
	void Deinit();
	int Read(J_AsioDataBase *pAsioData);
	int Write(J_AsioDataBase *pAsioData);

private:
	static unsigned X_JO_API WorkThread(void *param)
	{
		(static_cast<CXUdpAsio *>(param))->OnWork();
		return 0;
	}
	void OnWork();

private:
	typedef std::map<j_socket_t, J_AsioUser *>AsioUserMap;
	AsioUserMap m_userMap;
	j_socket_t m_listenSocket;
	J_AsioDataBase *m_listenAsioData;

	CJoThread m_workThread;
	J_OS::CTLock m_user_locker;
	J_OS::CTLock m_listen_locker;

	j_boolean_t m_bStarted;
	HANDLE m_hCompletionPort; 
	CJoThread m_listenThread;
};

JO_DECLARE_SINGLETON(XUdpAsio)

#endif //~__X_ASIO_UDP_H_
