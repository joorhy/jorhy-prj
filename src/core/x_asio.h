#ifndef __X_RD_ASIO_H_
#define __X_RD_ASIO_H_
#include "j_includes.h"
#include "j_type.h"
#include "x_singleton.h"
#include "x_lock.h"
#include "x_socket.h"

class CRdAsio : public SingletonTmpl<CRdAsio>
{
public:
	CRdAsio(int);
	~CRdAsio();

private:
	CRdAsio();

public:
	int Init();
	void Deinit();
	int AddUser(int nSocket, J_AsioUser *pUser);
	void DelUser(int nSocket);

private:
	static void *WorkThread(void *param)
	{
		(static_cast<CRdAsio *>(param))->OnWork();
		return (void *)0;
	}
	void OnWork();
	void EnableKeepalive(int nSocket);

private:
	typedef std::map<int, J_AsioUser *> AsioMap;
	AsioMap m_asioMap;

	pthread_t m_workThread;
	J_OS::CTLock m_locker;

	int m_epoll_fd;
	bool m_bStarted;
	struct epoll_event m_evAsio;
	struct epoll_event m_evConnect[JO_MAX_ASIOSIZE];
};

#endif //~__X_RD_ASIO_H_
