#include "x_asio.h"
#include "x_errtype.h"
#include "j_module.h"
#include "x_socket.h"

JO_IMPLEMENT_SINGLETON(XAsio)
///
CXAsioClient::CXAsioClient()
{
	m_bStarted = false;
	m_epoll_fd = 0;
}

CXAsioClient::~CXAsioClient()
{

}

int CXAsioClient::Init(j_socket_t nSocket, J_AsioUser *pUser)
{
	if (!m_bStarted)
	{
		m_epoll_fd = 0;
		m_epoll_fd = epoll_create(JO_MAX_ASIOSIZE);

		m_bStarted = true;
		j_thread_parm parm = {0};
		parm.entry = CXAsioClient::WorkThread;
		parm.data = this;
		m_workThread.Create(parm);
	}
	m_evAsio.events = EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP;
	m_evAsio.data.fd = nSocket.sock;

	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, nSocket.sock, &m_evAsio) < 0)
	{
		J_OS::LOGERROR("CXAsioClient::Init epoll set insertion error");
		return J_SOCKET_ERROR;
	}
	m_nSocket = nSocket;
	EnableKeepalive(nSocket);
	m_pUser = pUser;
	
	return J_OK;
}

void CXAsioClient::Deinit()
{
	TLock(m_read_locker);
	AsioDataMap::iterator itData = m_readMap.find(m_nSocket);
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

	TLock(m_write_locker);
	AsioDataMap::iterator itData2 = m_writeMap.find(m_nSocket);
	if (itData2 != m_writeMap.end())
	{
		J_AsioDataBase *pDataBase = NULL;
		while (!itData2->second.empty())
		{
			pDataBase = itData2->second.front();
			itData2->second.pop();
			if (pDataBase->ioWrite.buf != NULL)
			{
				delete pDataBase->ioWrite.buf;
				pDataBase->ioWrite.buf = NULL;
			}
			delete pDataBase;
			pDataBase = NULL;
		}
		m_writeMap.erase(itData2);
	}
	TUnlock(m_write_locker);
	
	m_evAsio.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP | EPOLLERR | EPOLLHUP | EPOLLPRI/* | EPOLLET*/;
	m_evAsio.data.fd = m_nSocket.sock;
	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, m_nSocket.sock, &m_evAsio) == 0)
	{
		j_close_socket(m_nSocket.sock);
	}
	if (m_bStarted)
	{
		m_bStarted = false;
		//m_workThread.Release();

		//m_cond.Wait();
		/*if (m_epoll_fd != 0)
		{
			close (m_epoll_fd);
			m_epoll_fd = 0;
		}*/
	}
	J_OS::LOGINFO("CXAsio::DelUser epoll set insertion sucess fd = %d", m_nSocket.sock);
}

void CXAsioClient::OnWork()
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
		usleep(1);
		nfds = epoll_wait(m_epoll_fd, m_evConnect, 1024, 200);
		if (nfds < 0)
		{
			if (errno == EINTR)
			{
				continue;
			}
			else
			{
				//J_OS::LOGINFO("errno = %d\n", errno);
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
			active_fd.sock = m_evConnect[i].data.fd;
			if ((m_evConnect[i].events & EPOLLRDHUP) && (m_evConnect[i].events & EPOLLIN))
			{
				//broken
				ProcessIoEvent(active_fd, J_AsioDataBase::j_disconnect_e);
				epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, active_fd.sock, &m_evConnect[i]);
			}
			else if (m_evConnect[i].events & EPOLLIN)
			{
				//read
				while(ProcessIoEvent(active_fd, J_AsioDataBase::j_read_e) == J_NOT_COMPLATE)
					usleep(1);
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
	
	if (m_epoll_fd != 0)
	{
		close (m_epoll_fd);
		m_epoll_fd = 0;
	}
	//m_cond.Single();
}
	
void CXAsioClient::EnableKeepalive(j_socket_t sock)
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

int CXAsioClient::Read(j_socket_t nSocket, J_AsioDataBase *pAsioData)
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

int CXAsioClient::Write(j_socket_t nSocket, J_AsioDataBase *pAsioData)
{
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

	return J_OK;
}

int CXAsioClient::ProcessIoEvent(j_socket_t nSocket, int nType)
{
	AsioDataMap::iterator itData;
	int nRet = 0;
	int nFinishLen = 0;
	J_AsioDataBase *pDataBase = NULL;
	switch (nType)
	{
		case J_AsioDataBase::j_read_e:
			TLock(m_read_locker);
			itData = m_readMap.find(nSocket);
			if (itData != m_readMap.end())
			{
				if (!itData->second.empty())
				{
					pDataBase = itData->second.front();
					itData->second.pop();
					int nReadLen = pDataBase->ioRead.bufLen;
					while (nReadLen > 0)
					{
						if (pDataBase->ioRead.whole)
						{
							nRet = recv(nSocket.sock, pDataBase->ioRead.buf + nFinishLen, nReadLen, 0);
							if (nRet <= 0)
							{
								if (nRet < 0 && errno == EINTR)
									continue;
									
								//J_OS::LOGINFO("sock = %d len = %d, errno = %d\n", nSocket.sock, nReadLen, errno);
								TUnlock(m_read_locker);
								J_AsioDataBase asioData;
								asioData.ioHandle = nSocket.sock;
								J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>(pDataBase->ioUser);
								pAsioUser->OnBroken(&asioData, J_SOCKET_ERROR);
								nRet = J_SOCKET_ERROR;
								TLock(m_read_locker);
								break;
							}
							nReadLen -= nRet;
							nFinishLen += nRet;
						}
						else
						{
							nRet = recv(nSocket.sock, pDataBase->ioRead.buf, pDataBase->ioRead.bufLen, 0);
							nFinishLen += nRet;
							break;
						}
					}
					if (nReadLen < 0)
					{
						while (strstr(pDataBase->ioRead.buf, pDataBase->ioRead.until_buf) == NULL)
						{
							nRet = recv(nSocket.sock, pDataBase->ioRead.buf + nFinishLen, 1, 0);
							if (nRet <= 0)
							{
								if (nRet < 0 && errno == EINTR)
									continue;
									
								//J_OS::LOGINFO("sock = %d len = %d, errno = %d\n", nSocket.sock, nReadLen, errno);
								TUnlock(m_read_locker);
								J_AsioDataBase asioData;
								asioData.ioHandle = nSocket.sock;
								J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>(pDataBase->ioUser);
								pAsioUser->OnBroken(&asioData, J_SOCKET_ERROR);
								nRet = J_SOCKET_ERROR;
								TLock(m_read_locker);
								break;
							}
							nFinishLen += nRet;
						}
					}
				}
			}
			else
			{
				TUnlock(m_read_locker);
				return J_NOT_COMPLATE;
			}
			TUnlock(m_read_locker);
			if (nRet > 0 && pDataBase != NULL)
			{
				pDataBase->ioRead.finishedLen = nFinishLen;
				pDataBase->ioHandle = nSocket.sock;
				pDataBase->ioCall = J_AsioDataBase::j_read_e;
				J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>((J_Obj *)pDataBase->ioUser);
				if (pAsioUser->OnRead(pDataBase, J_OK) != J_OK)
				{
					if (m_pUser != NULL)
					{
						J_AsioDataBase asioData;
						asioData.ioHandle = nSocket.sock;
						m_pUser->OnBroken(&asioData, J_SOCKET_ERROR);
					}
				}
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
				while (nWriteLen > 0)
				{
					nRet = send(nSocket.sock, pDataBase->ioWrite.buf + nFinishLen, nWriteLen, 0);
					if (nRet <= 0)
					{
						TUnlock(m_write_locker);
						J_AsioDataBase asioData;
						asioData.ioHandle = nSocket.sock;
						J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>(pDataBase->ioUser);
						pAsioUser->OnBroken(&asioData, J_SOCKET_ERROR);
						nRet = J_SOCKET_ERROR;
						TLock(m_write_locker);
						break;
					}
					nWriteLen -= nRet;
					nFinishLen += nRet;
				}
			}
			TUnlock(m_write_locker);
			if (pDataBase != NULL && nRet >= 0)
			{
				pDataBase->ioWrite.finishedLen = nFinishLen;
				pDataBase->ioHandle = nSocket.sock;
				pDataBase->ioCall = J_AsioDataBase::j_write_e;
				J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>(pDataBase->ioUser);
				pAsioUser->OnWrite(pDataBase, J_OK);
			}
			break;
		case J_AsioDataBase::j_disconnect_e:
		{
			if (m_pUser != NULL)
			{
				J_AsioDataBase asioData;
				asioData.ioHandle = nSocket.sock;
				m_pUser->OnBroken(&asioData, J_SOCKET_ERROR);
			}
			break;
		}
	}
		
	return J_OK;
}

///CXAsio
CXAsio::CXAsio()
{
	
}

CXAsio::~CXAsio()
{
	
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
		
		j_thread_parm parm = {0};
		parm.entry = CXAsio::ListenThread;
		parm.data = this;
		m_listenThread.Create(parm);
	}
	return J_OK;
}

int CXAsio::AddUser(j_socket_t nSocket, J_AsioUser *pUser)
{
	TLock(m_user_locker);
	if (m_userMap.find(nSocket) == m_userMap.end())
	{
		m_userMap[nSocket] = new CXAsioClient();
		m_userMap[nSocket]->Init(nSocket, pUser);
	}
	TUnlock(m_user_locker);

	J_OS::LOGINFO("CXAsio::AddUser epoll set insertion sucess fd = %d", nSocket.sock);

	return J_OK;
}

void CXAsio::DelUser(j_socket_t nSocket)
{
	TLock(m_user_locker);
	AsioUserMap::iterator it = m_userMap.find(nSocket);
	if (it != m_userMap.end())
	{
		it->second->Deinit();
		delete it->second;
		m_userMap.erase(it);
	}
	TUnlock(m_user_locker);
}

int CXAsio::Read(j_socket_t nSocket, J_AsioDataBase *pAsioData)
{
	TLock(m_user_locker);
	AsioUserMap::iterator it = m_userMap.find(nSocket);
	if (it != m_userMap.end())
	{
		it->second->Read(nSocket, pAsioData);
	}
	TUnlock(m_user_locker);
}

int CXAsio::Write(j_socket_t nSocket, J_AsioDataBase *pAsioData)
{
	TLock(m_user_locker);
	AsioUserMap::iterator it = m_userMap.find(nSocket);
	if (it != m_userMap.end())
	{
		it->second->Write(nSocket, pAsioData);
	}
	TUnlock(m_user_locker);
}

void CXAsio::OnListen()
{
	j_socket_t active_fd;
	struct sockaddr_in connAddr;
	socklen_t connLen = sizeof(sockaddr_in);
	j_asio_handle connSocket;
	
	while (true)
	{
		if ((connSocket = accept(m_listenSocket.sock, (struct sockaddr *)&connAddr, &connLen)) == j_invalid_socket_val)
		{
			J_OS::LOGINFO("CXAsio::OnListen accept faild with error");
			return;
		}
		m_listenAsioData->ioAccept.subHandle = connSocket;
		m_listenAsioData->ioAccept.peerIP = connAddr.sin_addr.s_addr;
		m_listenAsioData->ioAccept.peerPort = connAddr.sin_port;
		active_fd.sock = connSocket;
		ProcessAccept(active_fd, m_listenAsioData);
	}
}

int CXAsio::ProcessAccept(j_socket_t nSocket, J_AsioDataBase *asioData)
{
	TLock(m_listen_locker);
	J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>(asioData->ioUser);
	pAsioUser->OnAccept(asioData, J_OK);
	TUnlock(m_listen_locker);
	return J_OK;
}
