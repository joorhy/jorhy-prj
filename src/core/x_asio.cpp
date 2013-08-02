#include "x_asio.h"
#include "x_errtype.h"
#include "j_module.h"
#include "x_socket.h"

JO_IMPLEMENT_SINGLETON(XAsio)
///
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
		m_bStarted = true;
	}
	return J_OK;
}

void CXAsio::Deinit()
{
	if (m_bStarted)
	{
		m_bStarted = false;
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
		
		j_thread_parm parm = {0};
		parm.entry = CXAsio::ListenThread;
		parm.data = this;
		m_workThread.Create(parm);
	}
	return J_OK;
}

int CXAsio::AddUser(j_socket_t nSocket, J_AsioUser *pUser)
{
	TLock(m_user_locker);
	m_userMap[nSocket] = pUser;
	TUnlock(m_user_locker);

	J_OS::LOGINFO("CXAsio::AddUser epoll set insertion sucess fd = %d", nSocket.sock);

	return J_OK;
}

void CXAsio::DelUser(j_socket_t nSocket)
{
	j_close_socket(nSocket.sock);
	TLock(m_user_locker);
	AsioUserMap::iterator it = m_userMap.find(nSocket);
	if (it != m_userMap.end())
	{
		m_userMap.erase(it);
	}
	TUnlock(m_user_locker);
		
	J_OS::LOGINFO("CXAsio::DelUser epoll set insertion sucess fd = %d", nSocket.sock);
}

void CXAsio::OnWork(J_AsioDataBase *pDataBase)
{
	if (pDataBase->ioCall == J_AsioDataBase::j_read_e)
	{
		j_sleep(1);
		J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>((J_Obj *)pDataBase->ioUser);
		if (pDataBase->ioRead.bufLen < 0)
		{
			pDataBase->ioRead.finishedLen += 1;
			if (strstr(pDataBase->ioRead.buf, pDataBase->ioRead.until_buf) == NULL)
				Read(pDataBase->ioHandle, pDataBase);
			else
				pAsioUser->OnRead(pDataBase, J_OK);
		}
		else
		{
			pDataBase->ioRead.finishedLen = pDataBase->ioRead.bufLen;
			pAsioUser->OnRead(pDataBase, J_OK);
		}
	}
	else if (pDataBase->ioCall == J_AsioDataBase::j_write_e)
	{
		//write
		j_sleep(1);
		//printf("%d = %d\n", pPerIoData->ioWrite.bufLen, dwBytesTransferred);
		pDataBase->ioWrite.finishedLen = pDataBase->ioWrite.bufLen;
		J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>((J_Obj *)pDataBase->ioUser);
		pAsioUser->OnWrite(pDataBase, J_OK);
	}
}

void CXAsio::OnListen()
{
	j_socket_t active_fd;
	struct sockaddr_in sonnAddr;
	socklen_t connLen = sizeof(sockaddr_in);
	j_asio_handle connSocket;
	while (true)
	{
		if ((connSocket = accept(m_listenSocket.sock, (struct sockaddr*)&sonnAddr, &connLen)) == j_invalid_socket_val)
		{
			if (errno == 4)
				continue;
				
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

	pAsioData->ioHandle = nSocket.sock;
	struct sigaction sig_act;
	//set up the signal handler
	memset (&sig_act, 0, sizeof(sig_act));
	sigemptyset(&sig_act.sa_mask);
	sig_act.sa_flags = SA_SIGINFO;
	sig_act.sa_sigaction = aio_completion_handler;

	if (pAsioData->ioRead.bufLen < 0)
	{
		pAsioData->aio_buf = pAsioData->ioRead.buf + pAsioData->ioRead.finishedLen;
		pAsioData->aio_nbytes = 1;//
	}
	else
	{
		pAsioData->aio_nbytes  = pAsioData->ioRead.bufLen;
		pAsioData->aio_buf = pAsioData->ioRead.buf;
	}
	//set up the AIO request
	pAsioData->aio_fildes = nSocket.sock;
	pAsioData->aio_offset = 0;
	pAsioData->context = this;
	
	//link the AIO request with the signal handler
	pAsioData->aio_sigevent.sigev_notify = SIGEV_SIGNAL;
	pAsioData->aio_sigevent.sigev_signo = SIGIO;
	pAsioData->aio_sigevent.sigev_value.sival_ptr = pAsioData;
	
	//map the signal to the signal handler
	sigaction(SIGIO, &sig_act, NULL);
	
	if (aio_read(pAsioData) < 0)
	{
		J_OS::LOGERROR("CXAsio::Read aio_read error");
		return J_UNKNOW;
	}

	return J_OK;
}

void CXAsio::aio_completion_handler( int signo, siginfo_t *info, void *context)
{
	if (info->si_signo == SIGIO)
	{
		J_AsioDataBase *req;
		req = (J_AsioDataBase *)info->_sifields._rt.si_sigval.sival_ptr;
		if (req != NULL)
		//if (req->ioCall == J_AsioDataBase::j_read_e || req->ioCall == J_AsioDataBase::j_write_e)
			((CXAsio *)req->context)->OnWork(req);
	}
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

	pAsioData->ioHandle = nSocket.sock;
	struct sigaction sig_act;
	//set up the signal handler
	memset (&sig_act, 0, sizeof(sig_act));
	sigemptyset(&sig_act.sa_mask);
	sig_act.sa_flags = SA_SIGINFO;
	sig_act.sa_sigaction = aio_completion_handler;

	//set up the AIO request
	pAsioData->aio_fildes = nSocket.sock;
	pAsioData->aio_buf = (void *)pAsioData->ioWrite.buf;
	pAsioData->aio_nbytes = pAsioData->ioWrite.bufLen;
	pAsioData->aio_offset = 0;
	pAsioData->context = this;
	
	//link the AIO request with the signal handler
	pAsioData->aio_sigevent.sigev_notify = SIGEV_SIGNAL;
	pAsioData->aio_sigevent.sigev_signo = SIGIO;
	pAsioData->aio_sigevent.sigev_value.sival_ptr = pAsioData;
	
	//map the signal to the signal handler
	sigaction(SIGIO, &sig_act, NULL);
	
	if (aio_write(pAsioData) < 0)
	{
		J_OS::LOGERROR("CXAsio::Write aio_write error");
		return J_UNKNOW;
	}

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
	int nResult = J_OK;
	int nRetVal = 0;
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
						nRetVal = recv(nSocket.sock, pDataBase->ioRead.buf, pDataBase->ioRead.bufLen, MSG_WAITALL);
						nReadLen -= nRetVal;
						if (nRetVal == 0)
						{
							nResult = J_SOCKET_ERROR;
							break;
						}
						else if (nRetVal < 0)
						{
							if (errno == EAGAIN || errno == EINTR)
								continue;
							else
							{
								nResult = J_SOCKET_ERROR;
								break;
							}
						}
					}
					else
					{
						nRetVal = recv(nSocket.sock, pDataBase->ioRead.buf, pDataBase->ioRead.bufLen, 0);
						if (nRetVal == 0)
						{
							nResult = J_SOCKET_ERROR;
						}
						else if (nRetVal < 0)
						{
							if (errno == EAGAIN || errno == EINTR)
								continue;
							else
							{
								nResult = J_SOCKET_ERROR;
							}
						}
						break;
					}
				}
				if (nReadLen < 0)
				{
					j_int32_t n = 0;
					while (strstr(pDataBase->ioRead.buf, pDataBase->ioRead.until_buf) == NULL)
					{
						nRetVal = recv(nSocket.sock, pDataBase->ioRead.buf + n, 1, 0);
						if (nRetVal == 0)
						{
							nResult = J_SOCKET_ERROR;
							break;
						}
						else if (nRetVal < 0)
						{
							if (errno == EAGAIN || errno == EINTR)
								continue;
							else
							{
								nResult = J_SOCKET_ERROR;
								break;
							}
						}
						n += nRetVal;
					}
					nRetVal = n;
				}
			}
			TUnlock(m_read_locker);
			if (nRetVal > 0)
			{
				pDataBase->ioRead.finishedLen = nRetVal;
				pDataBase->ioHandle = nSocket.sock;
				pDataBase->ioCall = J_AsioDataBase::j_read_e;
				J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>((J_Obj *)pDataBase->ioUser);
				nResult = pAsioUser->OnRead(pDataBase, J_OK);
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
				while (nWriteLen > 0)
				{
					if (pDataBase->ioWrite.whole)
						nRetVal = send(nSocket.sock, pDataBase->ioWrite.buf + nSendLen, nWriteLen, 0);
					else 
						nRetVal = send(nSocket.sock, pDataBase->ioWrite.buf + nSendLen, nWriteLen, 0);
					
					if (nRetVal == 0)
					{
						J_AsioDataBase asioData;
						asioData.ioHandle = nSocket.sock;
						J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>(pDataBase->ioUser);
						nResult = J_SOCKET_ERROR;
						break;
					}
					else if (nRetVal < 0)
					{
						if (errno == EAGAIN || errno == EINTR)
							continue;
						else
						{
							J_AsioDataBase asioData;
							asioData.ioHandle = nSocket.sock;
							J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>(pDataBase->ioUser);
							nResult = J_SOCKET_ERROR;
							break;
						}
					}
					nWriteLen -= nRetVal;
					nSendLen += nRetVal;
				}
			}
			TUnlock(m_write_locker);
			if (pDataBase != NULL && nResult >= 0)
			{
				pDataBase->ioWrite.finishedLen = nRetVal;
				pDataBase->ioHandle = nSocket.sock;
				pDataBase->ioCall = J_AsioDataBase::j_write_e;
				J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>(pDataBase->ioUser);
				nResult = pAsioUser->OnWrite(pDataBase, J_OK);
			}
			break;
		case J_AsioDataBase::j_disconnect_e:
		{
			J_AsioUser *pAsioUser = NULL;
			TLock(m_user_locker);
			AsioUserMap::iterator itUser = m_userMap.find(nSocket);
			if (itUser != m_userMap.end())
			{
				pAsioUser = dynamic_cast<J_AsioUser *>(itUser->second);
				//m_userMap.erase(itUser);
			}
			TUnlock(m_user_locker);
			if (pAsioUser != NULL)
			{
				J_AsioDataBase asioData;
				asioData.ioHandle = nSocket.sock;
				pAsioUser->OnBroken(&asioData, J_SOCKET_ERROR);
			}
			break;
		}
	}
		
	return nResult;
}

