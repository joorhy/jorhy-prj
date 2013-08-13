#include "x_asio_win.h"
#include "x_errtype.h"
#include "j_module.h"
#include "x_socket.h"

JO_IMPLEMENT_SINGLETON(XAsio)

CXAsio::CXAsio()
{
	m_bStarted = false;
	WSADATA wsaData; 
	WSAStartup(MAKEWORD(2,2), &wsaData);
	Init();
}

CXAsio::~CXAsio()
{
	Deinit();
	WSACleanup();
}

int CXAsio::Init()
{
	if (!m_bStarted)
	{
		m_hCompletionPort = INVALID_HANDLE_VALUE;
		if ((m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL)
		{
			J_OS::LOGINFO( "CRdAsio::Init() CreateIoCompletionPort failed with error: %d\n", GetLastError());
			return J_SOCKET_ERROR;
		} 
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

		if (m_hCompletionPort != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hCompletionPort);
			m_hCompletionPort = INVALID_HANDLE_VALUE;
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
	if (CreateIoCompletionPort((HANDLE)nSocket.sock, m_hCompletionPort, (DWORD)&nSocket, 0) == NULL)
	{
		J_OS::LOGINFO("CXAsio::AddUser CreateIoCompletionPort failed with error %d\n", WSAGetLastError());
		return J_SOCKET_ERROR;
	} 
	m_userMap[nSocket] = pUser;

	J_OS::LOGINFO("CXAsio::AddUser epoll set insertion sucess fd = %d", nSocket.sock);
	TUnlock(m_user_locker);

	return J_OK;
}

void CXAsio::DelUser(j_socket_t nSocket)
{
	TLock(m_user_locker);
	j_close_socket(nSocket.sock);
	AsioUserMap::iterator it = m_userMap.find(nSocket);
	if (it != m_userMap.end())
		m_userMap.erase(it);
		
	J_OS::LOGINFO("CXAsio::DelUser epoll set insertion sucess fd = %d", nSocket.sock);
	TUnlock(m_user_locker);
	
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
}

void CXAsio::OnWork()
{
	DWORD dwBytesTransferred;
	LPOVERLAPPED Overlapped;
	j_socket_t *pPerHandleData;
	J_AsioDataBase *pPerIoData;        
	DWORD SendBytes, RecvBytes;
	DWORD Flags;
	while (m_bStarted)
	{
		if (GetQueuedCompletionStatus(m_hCompletionPort, &dwBytesTransferred, (LPDWORD)&pPerHandleData, (LPOVERLAPPED *)&pPerIoData, 20) == 0)
		{
			DWORD dwError = GetLastError();
			if (dwError == ERROR_NETNAME_DELETED)
				ProcessIoEvent(pPerIoData->ioHandle, J_AsioDataBase::j_disconnect_e);
			else if (dwError != WAIT_TIMEOUT)
				J_OS::LOGINFO("CXAsio::OnWork GetQueuedCompletionStatus failed with error %d", dwError);
			continue;
		}
		// 检查数据传送完了吗
		if (dwBytesTransferred == 0)
		{
			J_OS::LOGINFO("CXAsio::OnWork Broken");
			ProcessIoEvent(pPerIoData->ioHandle, J_AsioDataBase::j_disconnect_e);
			continue;
		}  
		if (pPerIoData->ioCall == J_AsioDataBase::j_read_e)
		{
			//read
			//printf("%d = %d\n", pPerIoData->ioRead.bufLen, dwBytesTransferred);
			j_sleep(1);
			J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>((J_Obj *)pPerIoData->ioUser);
			if (pPerIoData->ioRead.bufLen < 0)
			{
				pPerIoData->ioRead.finishedLen += dwBytesTransferred;
				if (strstr(pPerIoData->ioRead.buf, pPerIoData->ioRead.until_buf) == NULL)
					Read(pPerIoData->ioHandle, pPerIoData);
				else
					pAsioUser->OnRead(pPerIoData, J_OK);
			}
			else
			{
				pPerIoData->ioRead.finishedLen += dwBytesTransferred;
				if (pPerIoData->ioRead.finishedLen < pPerIoData->ioRead.bufLen)
				{
					Read(pPerIoData->ioHandle, pPerIoData);
				}
				else
					pAsioUser->OnRead(pPerIoData, J_OK);
			}
		}
		else if (pPerIoData->ioCall == J_AsioDataBase::j_write_e)
		{
			//write
			j_sleep(1);
			assert(pPerIoData->ioWrite.bufLen == dwBytesTransferred);
			//printf("%d = %d\n", pPerIoData->ioWrite.bufLen, dwBytesTransferred);
			pPerIoData->ioWrite.finishedLen = dwBytesTransferred;
			J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>((J_Obj *)pPerIoData->ioUser);
			pAsioUser->OnWrite(pPerIoData, J_OK);
		}
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
	tcp_keepalive alive_in                = {0};
	tcp_keepalive alive_out              = {0};
	alive_in.keepalivetime                = 3000;                // 开始首次KeepAlive探测前的TCP空闭时间
	alive_in.keepaliveinterval			 = 1000;				// 两次KeepAlive探测间的时间间隔
	alive_in.onoff                             = TRUE;
	unsigned long ulBytesReturn = 0;
	WSAIoctl(sock.sock, SIO_KEEPALIVE_VALS, &alive_in, sizeof(alive_in), &alive_out, sizeof(alive_out), &ulBytesReturn, NULL, NULL);
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
	
	DWORD Flags = 0;
	WSABUF buf;
	DWORD dwFinishedLen = 0;
	DWORD dwError = SOCKET_ERROR;
	buf.len = pAsioData->ioRead.bufLen;
	pAsioData->ioHandle = nSocket.sock;
	if (pAsioData->ioRead.bufLen < 0)
	{
		buf.len = 1;
		buf.buf = pAsioData->ioRead.buf + pAsioData->ioRead.finishedLen;
		dwError = WSARecv(nSocket.sock, &buf, 1, (LPDWORD)&dwFinishedLen, &Flags, pAsioData, NULL);
	}
	else
	{
		buf.len = pAsioData->ioRead.bufLen - pAsioData->ioRead.finishedLen;
		buf.buf = pAsioData->ioRead.buf + pAsioData->ioRead.finishedLen;
		dwError = WSARecv(nSocket.sock, &buf, 1, (LPDWORD)&dwFinishedLen, &Flags, pAsioData, NULL);
	}
	if (dwError == SOCKET_ERROR)
	{
		dwError = WSAGetLastError();
		//if (dwError == WSAECONNABORTED || dwError == WSAECONNRESET)
		//{
		//	ProcessIoEvent(nSocket, J_AsioDataBase::j_disconnect_e);
		//}
		if (dwError != ERROR_IO_PENDING)
		{
			ProcessIoEvent(nSocket, J_AsioDataBase::j_disconnect_e);
			J_OS::LOGINFO("WSARecv error = %d", dwError);
		}
	}
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

	WSABUF buf;
	buf.buf = (CHAR *)pAsioData->ioWrite.buf;
	buf.len = pAsioData->ioWrite.bufLen;
	pAsioData->ioHandle = nSocket.sock;
	pAsioData->ioCall = J_AsioDataBase::j_write_e;
	//printf("%s\n", buf.buf);
	if (WSASend(nSocket.sock, &buf, 1, (LPDWORD)&pAsioData->ioWrite.finishedLen, 0, pAsioData, NULL) == SOCKET_ERROR)
	{
		DWORD dwError = WSAGetLastError();
		//if (dwError == WSAECONNABORTED || dwError == WSAECONNRESET)
		//{
		//	ProcessIoEvent(nSocket, J_AsioDataBase::j_disconnect_e);
		//}
		if (dwError != ERROR_IO_PENDING)
		{
			ProcessIoEvent(nSocket, J_AsioDataBase::j_disconnect_e);
			J_OS::LOGINFO("WSASend error = %d", dwError);
		}
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
						J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>(pDataBase->ioUser);
						pAsioUser->OnBroken(&asioData, J_SOCKET_ERROR);
						break;
					}
					nWriteLen -= nRet;
					nSendLen += nRet;
				}
			}
			TUnlock(m_write_locker);
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
		
	return J_OK;
}

