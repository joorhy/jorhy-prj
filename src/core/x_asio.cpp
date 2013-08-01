#include "x_asio.h"
#include "x_errtype.h"
#include "j_module.h"
#include "x_socket.h"

JO_IMPLEMENT_SINGLETON(XAsio)

CXAsio::CXAsio()
{
	m_bStarted = false;
}

CXAsio::~CXAsio()
{

}

int CXAsio::Init()
{
	if (!m_bStarted)
	{
		m_epoll_fd = 0;
		m_epoll_fd = epoll_create(JO_MAX_ASIOSIZE);

		m_bStarted = true;
		j_thread_parm parm = {0};
		parm.entry = CXAsio::WorkThread;
		parm.data = this;
		m_workThread.Create(parm);
	}
	return J_OK;
}

void CXAsio::Deinit()
{
	if (m_bStarted)
	{
		m_bStarted = false;
		m_workThread.Release();

		if (m_epoll_fd != 0)
		{
			close (m_epoll_fd);
			m_epoll_fd = 0;
		}
	}
}

int CXAsio::Listen(J_AsioDataBase *pAsioData)
{
	if (pAsioData->ioUser != NULL)
	{
		j_socket_t nSocket;
		nSocket.sock = socket(AF_INET, SOCK_STREAM, 0);
		int retval;
		setsockopt(nSocket.sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&retval, sizeof(int));
		J_OS::CTCPSocket tcpSocket;
		if (tcpSocket.Listen(nSocket, pAsioData->ioAccept.peerPort, 1024, false) != J_OK)
			return J_UNKNOW;

		m_listenSocket = nSocket;
		m_listenAsioData = pAsioData;
		
		
		m_evListen.events = EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP/* | EPOLLET*/;
		m_evListen.data.fd = m_listenSocket.sock;

		if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, m_listenSocket.sock, &m_evListen) < 0)
		{
			J_OS::LOGERROR("CXService::Start epoll set insertion error");
			return J_UNKNOW;
		}
		
		/*j_thread_parm parm = {0};
		parm.entry = CXAsio::ListenThread;
		parm.data = this;
		m_workThread.Create(parm);*/
	}
	return J_OK;
}

int CXAsio::AddUser(j_socket_t nSocket, J_AsioUser *pUser)
{
	m_evAsio.events = EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP;
	m_evAsio.data.fd = nSocket.sock;

	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, nSocket.sock, &m_evAsio) < 0)
	{
		J_OS::LOGERROR("CRdAsio::AddUser epoll set insertion error");
		return J_SOCKET_ERROR;
	}
	EnableKeepalive(nSocket);
	//J_OS::LOGINFO("TLock(m_user_locker)");
	TLock(m_user_locker);
	m_userMap[nSocket] = pUser;
	TUnlock(m_user_locker);
	//J_OS::LOGINFO("TUnlock(m_user_locker)");

	J_OS::LOGINFO("CXAsio::AddUser epoll set insertion sucess fd = %d", nSocket.sock);

	return J_OK;
}

void CXAsio::DelUser(j_socket_t nSocket)
{
	m_evAsio.events = EPOLLIN | EPOLLRDHUP;
	m_evAsio.data.fd = nSocket.sock;
	epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, nSocket.sock, &m_evAsio);

	j_close_socket(nSocket.sock);
	AsioUserMap::iterator it = m_userMap.find(nSocket);
	if (it != m_userMap.end())
	{
		//J_OS::LOGINFO("TLock(m_user_locker)");
		TLock(m_user_locker);
		m_userMap.erase(it);
		TUnlock(m_user_locker);
		//J_OS::LOGINFO("TUnlock(m_user_locker)");
	}
		
	J_OS::LOGINFO("CXAsio::DelUser epoll set insertion sucess fd = %d", nSocket.sock);
	
	//J_OS::LOGINFO("TLock(m_read_locker)");
	TLock(m_read_locker);
	AsioDataMap::iterator itData = m_readMap.find(nSocket);
	if (itData != m_readMap.end())
	{
		J_AsioDataBase *pDataBase = NULL;
		while (!itData->second.empty())
		{
			pDataBase = itData->second.front();
			itData->second.pop();
			if (pDataBase->ioRead.buf != NULL)
			{
				delete pDataBase->ioRead.buf;
				pDataBase->ioRead.buf = NULL;
			}
			delete pDataBase;
		}
		m_readMap.erase(itData);
	}
	TUnlock(m_read_locker);
	//J_OS::LOGINFO("TUnlock(m_read_locker)");
	
	//J_OS::LOGINFO("TLock(m_write_locker)");
	TLock(m_write_locker);
	AsioDataMap::iterator itData2 = m_writeMap.find(nSocket);
	if (itData2 != m_writeMap.end())
	{
		J_AsioDataBase *pDataBase = NULL;
		while (!itData2->second.empty())
		{
			pDataBase = itData2->second.front();
			itData2->second.pop();
			if (pDataBase->ioWrite.buf != NULL)
				delete pDataBase->ioWrite.buf;
			delete pDataBase;
		}
		m_writeMap.erase(itData2);
	}
	TUnlock(m_write_locker);
	//J_OS::LOGINFO("TUnlock(m_write_locker)");
}

void CXAsio::OnWork()
{
	int nfds = 0;
	int i = 0;
	j_socket_t active_fd;
	struct sockaddr_in sonnAddr;
	socklen_t connLen;
	j_asio_handle connSocket;
	pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
	while (m_bStarted)
	{
		pthread_testcancel();
		//TLock(m_user_locker);
		nfds = epoll_wait(m_epoll_fd, m_evConnect, 1024, 200);
		//TUnlock(m_user_locker);
		if (nfds < 0)
		{
			usleep(10);
			if (errno == EINTR)
			{
				continue;
			}
			else
			{
				printf("errno = %d\n", errno);
				break;
			}
		}
		else if (nfds == 0)
		{
			continue;
			//J_OS::LOGERROR("nfds == 0 CXService::OnThread epoll error");
		}

		for (i = 0; i < nfds; i++)
		{
			if (m_evConnect[i].data.fd == m_listenSocket.sock)
			{
				OnListen();
			}
			else
			{
				active_fd.sock = m_evConnect[i].data.fd;
				if ((m_evConnect[i].events & EPOLLRDHUP) && (m_evConnect[i].events & EPOLLIN))
				{
					//broken
					ProcessIoEvent(active_fd, J_AsioDataBase::j_disconnect_e);
					//TLock(m_user_locker);
					epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, active_fd.sock, &m_evConnect[i]);
					//TUnlock(m_user_locker);
				}
				else if (m_evConnect[i].events & EPOLLIN)
				{
					//read
					ProcessIoEvent(active_fd, J_AsioDataBase::j_read_e);
					m_evAsio.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP | EPOLLERR | EPOLLHUP | EPOLLPRI/* | EPOLLET*/;
					m_evAsio.data.fd = m_evConnect[i].data.fd;
					//TLock(m_user_locker);
					epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, active_fd.sock, &m_evAsio);
					//TUnlock(m_user_locker);
				}
				else if (m_evConnect[i].events & EPOLLOUT)
				{
					//write
					ProcessIoEvent(active_fd, J_AsioDataBase::j_write_e);
					m_evAsio.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP | EPOLLERR | EPOLLHUP | EPOLLPRI/* | EPOLLET*/;
					m_evAsio.data.fd = m_evConnect[i].data.fd;
					//TLock(m_user_locker);
					epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, m_evConnect[i].data.fd, &m_evAsio);
					//TUnlock(m_user_locker);
				}
			}
		}
	}
}

void CXAsio::OnListen()
{
	j_socket_t active_fd;
	struct sockaddr_in sonnAddr;
	socklen_t connLen = sizeof(sockaddr_in);
	j_asio_handle connSocket;
	//while (true)
	{
		if ((connSocket = accept(m_listenSocket.sock, (struct sockaddr*)&sonnAddr, &connLen)) == j_invalid_socket_val)
		{
			J_OS::LOGERROR("CXAsio::OnListen WSAAccept() failed with error");
			return;
		} 
		m_listenAsioData->ioAccept.subHandle = connSocket;
		m_listenAsioData->ioAccept.peerIP = sonnAddr.sin_addr.s_addr;
		m_listenAsioData->ioAccept.peerPort = sonnAddr.sin_port;
		active_fd.sock = connSocket;
		ProcessAccept(active_fd, m_listenAsioData);
	}
}
	
void CXAsio::EnableKeepalive(j_socket_t sock)
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

int CXAsio::Read(j_socket_t nSocket, J_AsioDataBase *pAsioData)
{
	TLock(m_user_locker);
	AsioUserMap::iterator it = m_userMap.find(nSocket);
	if (it == m_userMap.end())
	{
		TUnlock(m_user_locker);
		return -1;
	}
	TUnlock(m_user_locker);
	
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

int CXAsio::Write(j_socket_t nSocket, J_AsioDataBase *pAsioData)
{
	TLock(m_user_locker);
	AsioUserMap::iterator it = m_userMap.find(nSocket);
	if (it == m_userMap.end())
	{
		TUnlock(m_user_locker);
		return -1;
	}
	TUnlock(m_user_locker);

	//J_OS::LOGINFO("TLock(m_write_locker);2");
	TLock(m_write_locker);
	AsioDataMap::iterator itData = m_writeMap.find(nSocket);
	if (itData == m_writeMap.end())
	{
		std::queue<J_AsioDataBase *> dataQ;
		dataQ.push(pAsioData);
		m_writeMap[nSocket] = dataQ;
	}
	else
	{
		itData->second.push(pAsioData);
	}
	TUnlock(m_write_locker);
	//J_OS::LOGINFO("TUnlock(m_write_locker);2");

	return J_OK;
}

int CXAsio::ProcessAccept(j_socket_t nSocket, J_AsioDataBase *asioData)
{
	TLock(m_listen_locker);
	J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>(asioData->ioUser);
	pAsioUser->OnAccept(asioData, J_OK);
	TUnlock(m_listen_locker);
	return J_OK;
}

int CXAsio::ProcessIoEvent(j_socket_t nSocket, int nType)
{
	AsioDataMap::iterator itData;
	int nRet = 0;
	J_AsioDataBase *pDataBase = NULL;
	switch (nType)
	{
		case J_AsioDataBase::j_read_e:
			//TLock(m_read_locker);
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
				if (nReadLen < 0)
				{
					j_int32_t n = 0;
					while (strstr(pDataBase->ioRead.buf, pDataBase->ioRead.until_buf) == NULL)
					{
						nRet = recv(nSocket.sock, pDataBase->ioRead.buf + n, 1, 0);
						n += nRet;
					}
					nRet = n;
				}
			}
			//TUnlock(m_read_locker);
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
			//J_OS::LOGINFO("TLock(m_write_locker);3");
			//TLock(m_write_locker);
			itData = m_writeMap.find(nSocket);
			//TUnlock(m_write_locker);
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
					
					if (nRet <= 0)
					{
						//printf("nRet = %d \n", nRet);
						J_AsioDataBase asioData;
						asioData.ioHandle = nSocket.sock;
						J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>(pDataBase->ioUser);
						pAsioUser->OnBroken(&asioData, J_SOCKET_ERROR);
						//TUnlock(m_write_locker);
						break;
					}
					nWriteLen -= nRet;
					nSendLen += nRet;
				}
			}
			//J_OS::LOGINFO("TUnlock(m_write_locker);3");
			if (pDataBase != NULL && nRet >= 0)
			{
				//if (pDataBase->ioWrite.buf != NULL)
				//	printf("%s \n", pDataBase->ioWrite.buf);
				pDataBase->ioWrite.finishedLen = nRet;
				pDataBase->ioHandle = nSocket.sock;
				pDataBase->ioCall = J_AsioDataBase::j_write_e;
				J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>(pDataBase->ioUser);
				pAsioUser->OnWrite(pDataBase, J_OK);
			}
			break;
		case J_AsioDataBase::j_disconnect_e:
		{
			J_AsioUser *pAsioUser = NULL;
			//TLock(m_user_locker);
			AsioUserMap::iterator itUser = m_userMap.find(nSocket);
			if (itUser != m_userMap.end())
			{
				pAsioUser = dynamic_cast<J_AsioUser *>(itUser->second);
				//m_userMap.erase(itUser);
			}
			//TUnlock(m_user_locker);
			if (pAsioUser != NULL)
			{
				J_AsioDataBase asioData;
				asioData.ioHandle = nSocket.sock;
				pAsioUser->OnBroken(&asioData, J_SOCKET_ERROR);
			}
			break;
		}
	}
		
	return J_OK;
}

