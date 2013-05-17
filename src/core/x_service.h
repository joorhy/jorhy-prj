#ifndef __X_SERVICE_H_
#define __X_SERVICE_H_
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <errno.h>

#include <map>
#include <vector>

#include "x_errtype.h"
#include "x_socket.h"
#include "x_timer.h"
#include "x_lock.h"

#define MAX_EPOLLSIZE 1024
struct ConnInfo
{
	int fd;
	int count;
};

template <typename TCPSerice>
class CXService
{
public:
	CXService()
	{
		m_bStarted = false;
		m_nPort = 6000;
	}
	virtual ~CXService()
	{
		Stop();
	}

	virtual int OnAccept(j_socket_t nSocket, const char *pAddr, short nPort) = 0;
	virtual int OnRead(j_socket_t nSocket) = 0;
	virtual int OnWrite(j_socket_t nSocket) = 0;
	virtual int OnBroken(j_socket_t nSocket) = 0;
	virtual j_socket_t GetSocketByResid(const char *pResid) = 0;

public:
	void Init()
	{
		m_epoll_fd = 0;
		m_workThread = 0;
		m_tcpSocket = NULL;
		m_nCurfds = 1;
	}

	int Start(int nPort)
	{
		if (m_bStarted)
			return J_OK;

		Init();
		m_nPort = nPort;
		m_tcpSocket = new J_OS::CTCPSocket();
		int retval;
		setsockopt(m_tcpSocket->GetHandle().sock, SOL_SOCKET, SO_REUSEADDR, &retval, sizeof(int));
		if (m_tcpSocket->Listen(nPort, 1024, false) != J_OK)
			return J_UNKNOW;

		m_epoll_fd = epoll_create(MAX_EPOLLSIZE);
		m_evListen.events = EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP/* | EPOLLET*/;
		m_evListen.data.fd = m_tcpSocket->GetHandle().sock;

		if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, m_tcpSocket->GetHandle().sock, &m_evListen) < 0)
		{
			J_OS::LOGERROR("CXService::Start epoll set insertion error");
			return J_UNKNOW;
		}
		//m_timer.Create(100, CXService::OnTimer, (unsigned long)this);

		m_bStarted = true;
		pthread_create(&m_workThread, NULL, WorkThread, this);
		pthread_detach(m_workThread);

		J_OS::LOGINFO("CXService::Start started port = %d", m_nPort);

		return J_OK;
	}
	int Stop()
	{
		m_bStarted = false;
		if (m_workThread != 0)
		{
			pthread_cancel(m_workThread);
			//pthread_join(m_workThread, NULL);
			m_workThread = 0;
		}

		if (m_epoll_fd != 0)
		{
			close (m_epoll_fd);
			m_epoll_fd = 0;
		}

		if (m_tcpSocket != NULL)
		{
			delete m_tcpSocket;
			m_tcpSocket = NULL;
		}
		//m_timer.Destroy();

		J_OS::LOGINFO("CXService::Stop stoped");

		return J_OK;
	}

	void Broken(j_socket_t nSocket, struct epoll_event &evBroken)
	{
		OnBroken(nSocket);
		epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, nSocket.sock, &evBroken);
		close(nSocket.sock);
		--m_nCurfds;
	}

	void ModifyListen()
	{
		m_evListen.events = EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP/* | EPOLLET*/;
		m_evListen.data.fd = m_tcpSocket->GetHandle().sock;

		if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, m_tcpSocket->GetHandle().sock, &m_evListen) < 0)
		{
			J_OS::LOGERROR("CXService::ModifyListen epoll set insertion error");
		}
	}

private:
	void EnableKeepalive(int nSocket)
	{
		//开启tcp探测
		int keepAlive = 1; 		// 开启keepalive属性
		int keepIdle = 1; 		// 如该连接在3秒内没有任何数据往来,则进行探测
		int keepInterval = 1;	// 探测时发包的时间间隔为1秒
		int keepCount = 3; 		// 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.
		setsockopt(nSocket, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, sizeof(keepAlive));
		setsockopt(nSocket, SOL_TCP, TCP_KEEPIDLE, (void*)&keepIdle, sizeof(keepIdle));
		setsockopt(nSocket, SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
		setsockopt(nSocket, SOL_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));
	}

	static void *WorkThread(void *param)
	{
		(static_cast<TCPSerice *>(param))->OnThread();
		return (void *)0;
	}
	void OnThread()
	{
		int nfds = 0;
		int i;
		int connSocket;
		struct sockaddr_in sonnAddr;
		socklen_t connLen;
		while (m_bStarted)
		{
			//printf("epoll_wait");
			usleep(1);
			nfds = epoll_wait(m_epoll_fd, m_evConnect, 1/*m_nCurfds > 1 ? m_nCurfds : 1*/, 200);
			if (nfds < 0)
			{
				//J_OS::LOGERROR("CXService::OnThread epoll error");
				usleep(10);
				if (errno == EINTR)
				{
					ModifyListen();
					continue;
				}
				else
					break;
			}
			else if (nfds == 0)
			{
				//J_OS::LOGERROR("nfds == 0 CXService::OnThread epoll error");
			}

			for (i = 0; i < nfds; i++)
			{
				if (m_evConnect[i].data.fd == m_tcpSocket->GetHandle().sock)
				{
					connLen = sizeof(struct sockaddr_in);
					connSocket = accept(m_tcpSocket->GetHandle().sock, (struct sockaddr *)&sonnAddr, &connLen);
					if (connSocket < 0)
					{
						J_OS::LOGERROR("CXService::OnThread accept error");
						continue;
					}
					//J_OS::LOGINFO("CXService::OnThread connect from ip = %s, port = %d, socket = %d, socket2 = %d"
					//		, inet_ntoa(sonnAddr.sin_addr), ntohs(sonnAddr.sin_port), connSocket, m_evConnect[i].data.fd);
					EnableKeepalive(connSocket);
					j_socket_t sock;
					sock.sock = connSocket;
					m_tcpSocket->SetNonblocking(sock);
					m_evListen.events = EPOLLIN /*| EPOLLOUT*/ | EPOLLRDHUP | EPOLLERR | EPOLLHUP | EPOLLPRI/* | EPOLLET*/;
					m_evListen.data.fd = connSocket;

					if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, connSocket, &m_evListen) < 0)
					{
						J_OS::LOGERROR("CXService::OnThread epoll set insertion error");
						continue;
					}
					RECLock(m_locker);
					ConnInfo info;
					info.fd = connSocket;
					info.count = 1;
					m_vecSocket.push_back(info);
					RECUnlock(m_locker);

					++m_nCurfds;
					sock.sock = connSocket;
					OnAccept(sock, inet_ntoa(sonnAddr.sin_addr), ntohs(sonnAddr.sin_port));

					m_evListen.events = EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP/* | EPOLLET*/;
					m_evListen.data.fd = m_evConnect[i].data.fd;
					epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, m_evConnect[i].data.fd, &m_evListen);
				}
				else
				{
					if ((m_evConnect[i].events & EPOLLIN) && (m_evConnect[i].events & EPOLLRDHUP))
					{
						RECLock(m_locker);
						j_socket_t sock;
						sock.sock = m_evConnect[i].data.fd;
						Broken(sock, m_evConnect[i]);
						VecSocket::iterator it = m_vecSocket.begin();
						for (; it != m_vecSocket.end(); it++)
						{
							if ((*it).fd == m_evConnect[i].data.fd)
							{
								m_vecSocket.erase(it);
								break;
							}
						}
						RECUnlock(m_locker);
					}
					else if (m_evConnect[i].events & EPOLLIN)
					{
						RECLock(m_locker);
						//if (m_evConnect[i].events & EPOLLRDNORM)
						//{
							//J_OS::LOGINFO("%x", m_evConnect[i].events);
							/*m_evListen.events = EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP | EPOLLRDNORM | EPOLLET;
							m_evListen.data.fd = m_evConnect[i].data.fd;
							epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, m_evConnect[i].data.fd, &m_evListen);

							RECUnlock(m_locker);
							continue;*/
						//}
						j_socket_t sock;
						sock.sock = m_evConnect[i].data.fd;
						if (OnRead(sock) < 0)
						{
							//J_OS::LOGINFO("ERROR %x", nRet);

							Broken(sock, m_evConnect[i]);
							VecSocket::iterator it = m_vecSocket.begin();
							for (; it != m_vecSocket.end(); it++)
							{
								if ((*it).fd == m_evConnect[i].data.fd)
								{
									m_vecSocket.erase(it);
									break;
								}
							}
						}
						else
						{
							m_evListen.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP | EPOLLERR | EPOLLHUP | EPOLLPRI/* | EPOLLET*/;
							m_evListen.data.fd = m_evConnect[i].data.fd;
							epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, m_evConnect[i].data.fd, &m_evListen);
						}
						RECUnlock(m_locker);
					}
					else if (m_evConnect[i].events & EPOLLOUT)
					{
						RECLock(m_locker);
						j_socket_t sock;
						sock.sock = m_evConnect[i].data.fd;
						if (OnWrite(sock) < 0)
						{
							Broken(sock, m_evConnect[i]);
							VecSocket::iterator it = m_vecSocket.begin();
							for (; it != m_vecSocket.end(); it++)
							{
								if ((*it).fd == m_evConnect[i].data.fd)
								{
									m_vecSocket.erase(it);
									break;
								}
							};
						}
						else
						{
							m_evListen.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP | EPOLLERR | EPOLLHUP | EPOLLPRI/* | EPOLLET*/;
							m_evListen.data.fd = m_evConnect[i].data.fd;
							epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, m_evConnect[i].data.fd, &m_evListen);
						}
						RECUnlock(m_locker);
					}
					else if (m_evConnect[i].events & (EPOLLERR | EPOLLHUP))
					{
						J_OS::LOGINFO("CXService::OnThread server error");
					}
					else
					{
						J_OS::LOGINFO("CXService::OnThread not possible to perform here");
					}
				}
			}
		}
		J_OS::LOGINFO("CXService::OnThread thread exit errno = %d", errno);
		epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, m_tcpSocket->GetHandle().sock, &m_evListen);
		close(m_epoll_fd);
		m_epoll_fd = 0;

		J_OS::LOGINFO("CXService::OnThread restart begin");
		Stop();
		J_OS::LOGINFO("CXService::OnThread restart doing");
		Start(m_nPort);
		J_OS::LOGINFO("CXService::OnThread restart sucess");
	}

	static void OnTimer(unsigned long user)
	{
		(static_cast<TCPSerice *>((void *)user))->StateDetection();
	}

	void StateDetection()
	{
	DetectionBegin:
		RECLock(m_locker);
		VecSocket::iterator it = m_vecSocket.begin();
		for (; it != m_vecSocket.end(); it++)
		{
			int nRet = recv((*it).fd, NULL, 0, 0);
			if (nRet <= 0)
			{
				if (nRet == 0/*errno == EAGAIN && nRet <= 0*/)
				{
					(*it).count = 0;
					continue;
				}
				J_OS::LOGERROR("nRet = %d", nRet);
				m_vecSocket.erase(it);
				Broken((*it).fd, m_evListen);
				RECUnlock(m_locker);
				goto DetectionBegin;
			}
		}
		RECUnlock(m_locker);
	}

private:
	int m_epoll_fd;
	bool m_bStarted;
	J_OS::CTCPSocket *m_tcpSocket;
	struct epoll_event m_evConnect[MAX_EPOLLSIZE];

	pthread_t m_workThread;
	int m_nPort;
	int m_nCurfds;
	//J_OS::CTimer m_timer;

public:
	struct epoll_event m_evListen;
	typedef std::vector<ConnInfo> VecSocket;
	VecSocket m_vecSocket;
	J_OS::RECLocker_t m_locker;
};

#endif //~__X_SERVICE_H_
