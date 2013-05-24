#ifndef __X_RD_ASIO_H_
#define __X_RD_ASIO_H_
#include "j_includes.h"
#include "j_type.h"
#include "x_singleton.h"
#include "x_lock.h"
#include "x_socket.h"
#include "x_thread.h"

class JO_API CRdAsio : public SingletonTmpl<CRdAsio>
{
public:
	CRdAsio(int);
	~CRdAsio();

private:
	CRdAsio();

public:
	int Init();
	void Deinit();
	int AddUser(j_socket_t nSocket, J_AsioUser *pUser);
	void DelUser(j_socket_t nSocket);

private:
#ifdef WIN32
	static unsigned X_JO_API WorkThread(void *param)
#else
	static void *WorkThread(void *param)
#endif
	{
		(static_cast<CRdAsio *>(param))->OnWork();
		return 0;
	}
	void OnWork();
	void EnableKeepalive(j_socket_t nSocket);

private:
	typedef std::map<j_socket_t, J_AsioUser *> AsioMap;
	AsioMap m_asioMap;

	CJoThread m_workThread;
	J_OS::CTLock m_locker;

	j_boolean_t m_bStarted;
#ifdef WIN32
	fd_set m_fdSet;
	struct timeval m_timeout;
#else
	int m_epoll_fd;
	struct epoll_event m_evAsio;
	struct epoll_event m_evConnect[JO_MAX_ASIOSIZE];
#endif
};

#endif //~__X_RD_ASIO_H_
