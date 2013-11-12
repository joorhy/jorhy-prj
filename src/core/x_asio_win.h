/** 
*  Copyright (c) 2013, xx科技有限公司 
*  All rights reserved. 
* 
*  @file				x_asio_win.h 
*  @author		Jorhy(joorhy@gmail.com) 
*  @date			2013/09/18 10:43 
*/  
#ifndef __X_ASIO_H_
#define __X_ASIO_H_
#include "j_includes.h"
#include "j_type.h"
#include "x_lock.h"
#include "x_socket.h"
#include "x_thread.h"

/** 
*  @author      Jorhy(joorhy@gmail.com) 
*  @date         2013/09/18 10:46 
*  @class        CXAsio 
*  @brief        异步IO
*  @note        无 
*/  
class JO_API CXAsio
{
public:
	CXAsio();
	~CXAsio();

public:
	int Init();
	void Deinit();
	int AddUser(j_socket_t nSocket, J_AsioUser *pUser);
	void DelUser(j_socket_t nSocket);
	int Listen(J_AsioDataBase *pAsioData);
	int Read(j_socket_t nSocket, J_AsioDataBase *pAsioData);
	int Write(j_socket_t nSocket, J_AsioDataBase *pAsioData);
	
private:
#ifdef WIN32
	static unsigned X_JO_API WorkThread(void *param)
#else
	static void *WorkThread(void *param)
#endif
	{
		(static_cast<CXAsio *>(param))->OnWork();
		return 0;
	}
	void OnWork();
#ifdef WIN32
	static unsigned X_JO_API ListenThread(void *param)
#else
	static void *ListenThread(void *param)
#endif
	{
		(static_cast<CXAsio *>(param))->OnListen();
		return 0;
	}
	void OnListen();

	void EnableKeepalive(j_socket_t nSocket);
	int ProcessAccept(j_socket_t nSocket, J_AsioDataBase *asioData);
	int ProcessIoEvent(j_socket_t nSocket, int nType);

private:
	typedef std::map<j_socket_t, J_AsioUser *>AsioUserMap;
	AsioUserMap m_userMap;
	j_socket_t m_listenSocket;
	J_AsioDataBase *m_listenAsioData;

	CJoThread m_workThread;
	J_OS::CTLock m_user_locker;
	J_OS::CTLock m_listen_locker;

	j_boolean_t m_bStarted;
#ifdef WIN32
	 HANDLE m_hCompletionPort; 
	 CJoThread m_listenThread;
#else
	int m_epoll_fd;
	struct epoll_event m_evListen;
	struct epoll_event m_evAsio;
	struct epoll_event m_evConnect[JO_MAX_ASIOSIZE];
#endif
};

JO_DECLARE_SINGLETON(XAsio)

#endif //~__X_ASIO_H_
