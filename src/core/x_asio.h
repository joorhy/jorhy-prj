#ifndef __X_RD_ASIO_H_
#define __X_RD_ASIO_H_
#include "j_includes.h"
#include "j_type.h"
#include "x_singleton.h"
#include "x_lock.h"
#include "x_socket.h"
#include "x_thread.h"
/////
class CXAsioClient
{
public:
	CXAsioClient();
	~CXAsioClient();

public:
	int Init(j_socket_t nSocket, J_AsioUser *pUser);
	void Deinit();
	int Read(j_socket_t nSocket, J_AsioDataBase *pAsioData);
	int Write(j_socket_t nSocket, J_AsioDataBase *pAsioData);
	
private:
	static void *WorkThread(void *param)
	{
		(static_cast<CXAsioClient *>(param))->OnWork();
		return 0;
	}
	void OnWork();

	void EnableKeepalive(j_socket_t nSocket);
	int ProcessIoEvent(j_socket_t nSocket, int nType);

private:
	typedef std::map<j_socket_t, std::queue<J_AsioDataBase *> >AsioDataMap;
	AsioDataMap m_readMap;
	AsioDataMap m_writeMap;

	CJoThread m_workThread;
	J_OS::CTLock m_read_locker;
	J_OS::CTLock m_write_locker;

	j_boolean_t m_bStarted;
	int m_epoll_fd;
	struct epoll_event m_evListen;
	struct epoll_event m_evAsio;
	struct epoll_event m_evConnect[JO_MAX_ASIOSIZE];
	
	J_AsioUser *m_pUser;
	j_socket_t m_nSocket;
	J_OS::CXCond m_cond;
};

class JO_API CXAsio
{
public:
	CXAsio();
	~CXAsio();
	
public:
	int Listen(J_AsioDataBase *pAsioData);
	int AddUser(j_socket_t nSocket, J_AsioUser *pUser);
	void DelUser(j_socket_t nSocket);
	int Read(j_socket_t nSocket, J_AsioDataBase *pAsioData);
	int Write(j_socket_t nSocket, J_AsioDataBase *pAsioData);
		
private:
	int ProcessAccept(j_socket_t nSocket, J_AsioDataBase *asioData);
	static void *ListenThread(void *param)
	{
		(static_cast<CXAsio *>(param))->OnListen();
		return 0;
	}
	void OnListen();
	
private:
	typedef std::map<j_socket_t, CXAsioClient *>AsioUserMap;
	AsioUserMap m_userMap;
	CJoThread m_listenThread;
	J_OS::CTLock m_listen_locker;
	j_socket_t m_listenSocket;
	J_AsioDataBase *m_listenAsioData;
	J_OS::CTLock m_user_locker;
};

JO_DECLARE_SINGLETON(XAsio)

#endif //~__X_RD_ASIO_H_
