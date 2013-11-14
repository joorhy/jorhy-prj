#ifndef __X_ASIO_H_
#define __X_ASIO_H_
#include "j_includes.h"
#include "j_type.h"
#include "x_lock.h"
#include "x_socket.h"
#include "x_thread.h"

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
	static unsigned X_JO_API WorkThread(void *param)
	{
		(static_cast<CXAsio *>(param))->OnWork();
		return 0;
	}
	void OnWork();
	static unsigned X_JO_API ListenThread(void *param)
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
	 HANDLE m_hCompletionPort; 
	 CJoThread m_listenThread;
};

JO_DECLARE_SINGLETON(XAsio)

#endif //~__X_ASIO_H_
