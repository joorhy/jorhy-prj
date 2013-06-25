#include "x_asio.h"
#include "x_errtype.h"
#include "j_module.h"
#include "x_socket.h"

CRdAsio::CRdAsio(int)
{
	m_bStarted = false;
}

CRdAsio::~CRdAsio()
{

}

int CRdAsio::Init()
{
	if (!m_bStarted)
	{
#ifdef WIN32
		FD_ZERO(&m_fdSet); 
		m_timeout.tv_sec = 1;
		m_timeout.tv_usec = 0;
#else
		m_epoll_fd = 0;
		m_epoll_fd = epoll_create(JO_MAX_ASIOSIZE);
#endif
		m_bStarted = true;
		j_thread_parm parm = {0};
		parm.entry = CRdAsio::WorkThread;
		parm.data = this;
		m_workThread.Create(parm);
	}
	return J_OK;
}

void CRdAsio::Deinit()
{
	if (m_bStarted)
	{
		m_bStarted = false;
		m_workThread.Release();

#ifdef WIN32
		FD_ZERO(&m_fdSet); 
#else
		if (m_epoll_fd != 0)
		{
			close (m_epoll_fd);
			m_epoll_fd = 0;
		}
#endif
	}
}

int CRdAsio::Listen(J_AsioDataBase *pAsioData)
{
	TLock(m_listen_locker);
	if (pAsioData->ioUser != NULL)
	{
		j_socket_t nSocket;
		nSocket.sock = socket(AF_INET, SOCK_STREAM, 0);
		int retval;
		setsockopt(nSocket.sock, SOL_SOCKET, SO_REUSEADDR, &retval, sizeof(int));
		J_OS::CTCPSocket tcpSocket;
		if (tcpSocket.Listen(nSocket, pAsioData->ioAccept.peerPort, 1024, false) != J_OK)
			return J_UNKNOW;
			
		m_evListen.events = EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP/* | EPOLLET*/;
		m_evListen.data.fd = nSocket.sock;

		if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, nSocket.sock, &m_evListen) < 0)
		{
			J_OS::LOGERROR("CRdAsio::Listen epoll set insertion error");
			return J_UNKNOW;
		}
		m_listenMap[nSocket] = pAsioData;
	}

	TUnlock(m_listen_locker);
	return J_OK;
}

int CRdAsio::AddUser(j_socket_t nSocket, J_AsioUser *pUser)
{
	TLock(m_user_locker);
#ifdef WIN32
	FD_SET(nSocket.sock, &m_fdSet);
#else
	m_evAsio.events = EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP;
	m_evAsio.data.fd = nSocket.sock;

	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, nSocket.sock, &m_evAsio) < 0)
	{
		J_OS::LOGERROR("CRdAsio::AddUser epoll set insertion error");
		return J_SOCKET_ERROR;
	}
#endif
	EnableKeepalive(nSocket);
	m_userMap[nSocket] = pUser;

	J_OS::LOGINFO("CRdAsio::AddUser epoll set insertion sucess fd = %d", nSocket.sock);
	TUnlock(m_user_locker);

	return J_OK;
}

void CRdAsio::DelUser(j_socket_t nSocket)
{
	TLock(m_user_locker);
#ifdef WIN32
#else
	m_evAsio.events = EPOLLIN | EPOLLRDHUP;
	m_evAsio.data.fd = nSocket.sock;
	epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, nSocket.sock, &m_evAsio);
#endif
	AsioUserMap::iterator it = m_userMap.find(nSocket);
	if (it != m_userMap.end())
		m_userMap.erase(it);
		
	J_OS::LOGINFO("CRdAsio::DelUser epoll set insertion sucess fd = %d", nSocket.sock);
	TUnlock(m_user_locker);
}

void CRdAsio::OnWork()
{
#ifdef WIN32
#else
	int nfds = 0;
	int i = 0;
	j_socket_t active_fd;
	AsioListenMap::iterator itListen;
	struct sockaddr_in sonnAddr;
	socklen_t connLen;
	int connSocket;
	pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
	while (m_bStarted)
	{
		pthread_testcancel();
		nfds = epoll_wait(m_epoll_fd, m_evConnect, 1, 200);
		if (nfds < 0)
		{
			usleep(10);
			if (errno == EINTR)
			{
				continue;
			}
			else
				break;
		}

		for (i = 0; i < nfds; i++)
		{
			active_fd.sock = m_evConnect[i].data.fd;
			if ((itListen = m_listenMap.find(active_fd)) != m_listenMap.end())
			{
				//accept
				connLen = sizeof(struct sockaddr_in);
				connSocket = accept(active_fd.sock, (struct sockaddr *)&sonnAddr, &connLen);
				if (connSocket < 0)
				{
					J_OS::LOGERROR("CXService::OnThread accept error");
					continue;
				}
				itListen->second->ioAccept.subHandle = connSocket;
				itListen->second->ioAccept.peerIP = sonnAddr.sin_addr.s_addr;
				itListen->second->ioAccept.peerPort = sonnAddr.sin_port;
				active_fd.sock = connSocket;
				ProcessAccept(active_fd, itListen->second);
			}
			else if ((m_evConnect[i].events & EPOLLRDHUP) && (m_evConnect[i].events & EPOLLIN))
			{
				//broken
				ProcessIoEvent(active_fd, J_AsioDataBase::j_disconnect_e);
				epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, active_fd.sock, &m_evConnect[i]);
			}
			else if (m_evConnect[i].events & EPOLLIN)
			{
				//read
				ProcessIoEvent(active_fd, J_AsioDataBase::j_read_e);
				m_evAsio.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP | EPOLLERR | EPOLLHUP | EPOLLPRI/* | EPOLLET*/;
				m_evAsio.data.fd = m_evConnect[i].data.fd;
				epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, active_fd.sock, &m_evAsio);
			}
			else if (m_evConnect[i].events & EPOLLOUT)
			{
				//write
				ProcessIoEvent(active_fd, J_AsioDataBase::j_write_e);
				m_evAsio.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP | EPOLLERR | EPOLLHUP | EPOLLPRI/* | EPOLLET*/;
				m_evAsio.data.fd = m_evConnect[i].data.fd;
				epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, m_evConnect[i].data.fd, &m_evAsio);
			}
		}
	}
#endif
}

void CRdAsio::EnableKeepalive(j_socket_t sock)
{
	//开启tcp探测
	int keepAlive = 1; 		// 开启keepalive属性
	setsockopt(sock.sock, SOL_SOCKET, SO_KEEPALIVE, (const char *)&keepAlive, sizeof(keepAlive));
#ifdef WIN32
	tcp_keepalive alive_in                = {0};
	tcp_keepalive alive_out              = {0};
	alive_in.keepalivetime                = 3000;                // 开始首次KeepAlive探测前的TCP空闭时间
	alive_in.keepaliveinterval			 = 1000;				// 两次KeepAlive探测间的时间间隔
	alive_in.onoff                             = TRUE;
	unsigned long ulBytesReturn = 0;
	WSAIoctl(sock.sock, SIO_KEEPALIVE_VALS, &alive_in, sizeof(alive_in), &alive_out, sizeof(alive_out), &ulBytesReturn, NULL, NULL);
#else
	int keepIdle = 3; 				// 如该连接在3秒内没有任何数据往来,则进行探测
	int keepInterval = 1;			// 探测时发包的时间间隔为2秒
	//int keepCount = 3; 		// 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.
	setsockopt(sock.sock, SOL_TCP, TCP_KEEPIDLE, (void*)&keepIdle, sizeof(keepIdle));
	setsockopt(sock.sock, SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
#endif
}

int CRdAsio::Read(j_socket_t nSocket, J_AsioDataBase *pAsioData)
{
	TLock(m_read_locker);
	AsioDataMap::iterator itData = m_readMap.find(nSocket);
	if (itData == m_readMap.end())
	{
		std::queue<J_AsioDataBase *> dataQ;
		dataQ.push(pAsioData);
		m_readMap[nSocket] = dataQ;
	}
	else
	{
		itData->second.push(pAsioData);
	}
	TUnlock(m_read_locker);
	return 0;
}

int CRdAsio::Write(j_socket_t nSocket, J_AsioDataBase *pAsioData)
{
	TLock(m_write_locker);
	AsioDataMap::iterator itData = m_writeMap.find(nSocket);
	if (itData == m_writeMap.end())
	{
		std::queue<J_AsioDataBase *> dataQ;
		dataQ.push(pAsioData);
		m_writeMap[nSocket] = dataQ;
		//if (pAsioData->ioWrite.bufLen > 0)
		//	printf("push 1 --- %d %s\n", (int)pAsioData, pAsioData->ioWrite.buf);
	}
	else
	{
		itData->second.push(pAsioData);
		//if (pAsioData->ioWrite.bufLen > 0)
		//	printf("push 2 --- %d %s\n", (int)pAsioData, pAsioData->ioWrite.buf);
	}
	TUnlock(m_write_locker);
	return J_OK;
}

int CRdAsio::ProcessAccept(j_socket_t nSocket, J_AsioDataBase *asioData)
{
	TLock(m_listen_locker);
	J_AsioUser *pAsioUser = static_cast<J_AsioUser *>(asioData->ioUser);
	pAsioUser->OnAccept(asioData, J_OK);
	TUnlock(m_listen_locker);
	return J_OK;
}

int CRdAsio::ProcessIoEvent(j_socket_t nSocket, int nType)
{
	AsioDataMap::iterator itData;
	int nRet = 0;
	J_AsioDataBase *pDataBase = NULL;
	switch (nType)
	{
		case J_AsioDataBase::j_read_e:
			TLock(m_read_locker);
			itData = m_readMap.find(nSocket);
			if (itData != m_readMap.end() && !itData->second.empty())
			{
				pDataBase = itData->second.front();
				itData->second.pop();
				int nReadLen = pDataBase->ioRead.bufLen;
				while (nReadLen > 0)
				{
					if (pDataBase->ioRead.whole)
					{
						nRet = recv(nSocket.sock, pDataBase->ioRead.buf, pDataBase->ioRead.bufLen, MSG_WAITALL);
						nReadLen -= nRet;
					}
					else
					{
						nRet = recv(nSocket.sock, pDataBase->ioRead.buf, pDataBase->ioRead.bufLen, 0);
						break;
					}
				}
			}
			TUnlock(m_read_locker);
			if (nRet > 0)
			{
				pDataBase->ioRead.finishedLen = nRet;
				pDataBase->ioHandle = nSocket.sock;
				pDataBase->ioCall = J_AsioDataBase::j_read_e;
				J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>((J_Obj *)pDataBase->ioUser);
				pAsioUser->OnRead(pDataBase, J_OK);
			}
			break;
		case J_AsioDataBase::j_write_e:
			TLock(m_write_locker);
			itData = m_writeMap.find(nSocket);
			if (itData != m_writeMap.end() && !itData->second.empty())
			{
				pDataBase = itData->second.front();
				itData->second.pop();
				int nWriteLen = pDataBase->ioWrite.bufLen;
				int nSendLen = 0;
				//if (nWriteLen > 0)
				//	printf("%s %d\n", pDataBase->ioWrite.buf, nWriteLen);
				while (nWriteLen > 0)
				{
					if (pDataBase->ioWrite.whole)
						nRet = send(nSocket.sock, pDataBase->ioWrite.buf + nSendLen, nWriteLen, 0);
					else 
						nRet = send(nSocket.sock, pDataBase->ioWrite.buf + nSendLen, nWriteLen, 0);
					
					if (nRet < 0)
					{
						//printf("nRet = %d \n", nRet);
						J_AsioDataBase asioData;
						asioData.ioHandle = nSocket.sock;
						J_AsioUser *pAsioUser = static_cast<J_AsioUser *>(pDataBase->ioUser);
						pAsioUser->OnBroken(&asioData, J_SOCKET_ERROR);
						break;
					}
					nWriteLen -= nRet;
					nSendLen += nRet;
				}
				//printf("%d \n", nWriteLen);
			}
			TUnlock(m_write_locker);
			if (pDataBase != NULL && nRet >= 0)
			{
				pDataBase->ioWrite.finishedLen = nRet;
				pDataBase->ioHandle = nSocket.sock;
				pDataBase->ioCall = J_AsioDataBase::j_write_e;
				J_AsioUser *pAsioUser = static_cast<J_AsioUser *>(pDataBase->ioUser);
				pAsioUser->OnWrite(pDataBase, J_OK);
			}
			break;
			
			case J_AsioDataBase::j_disconnect_e:
			{
				TLock(m_read_locker);
				AsioUserMap::iterator itUser = m_userMap.find(nSocket);
				if (itUser != m_userMap.end())
				{
					J_AsioDataBase asioData;
					asioData.ioHandle = nSocket.sock;
					J_AsioUser *pAsioUser = static_cast<J_AsioUser *>(itUser->second);
					pAsioUser->OnBroken(&asioData, J_SOCKET_ERROR);
					//m_userMap.erase(itUser);
				}
				TUnlock(m_read_locker);
				break;
			}
	}
		
	return J_OK;
}

