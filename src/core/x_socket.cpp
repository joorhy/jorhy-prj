#include "x_socket.h"

#define IO_DATA_LEN	65535
namespace J_OS
{

CTCPSocket::CTCPSocket()
{
	m_handle.sock = j_invalid_socket_val;
#ifdef WIN32
	WSADATA wsaData; 
	WSAStartup(MAKEWORD(2,2), &wsaData);
	m_handle.sock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
#else
	m_handle.sock = socket(AF_INET, SOCK_STREAM, 0);
	signal(SIGPIPE, SIG_IGN);
#endif

	m_bNeedClose = true;
	//J_OS::LOGINFO("CTCPSocket::CTCPSocket created, handle = %d", m_handle);
}

CTCPSocket::CTCPSocket(j_socket_t socket)
{
	m_handle = socket;
	m_bNeedClose = false;
}

CTCPSocket::CTCPSocket(int nPort, int nListenNum)
{
#ifdef WIN32
	WSADATA wsaData; 
	WSAStartup(MAKEWORD(2,2), &wsaData);
	m_handle.sock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
#else
	signal(SIGPIPE, SIG_IGN);
	m_handle.sock = socket(AF_INET, SOCK_STREAM, 0);
#endif

	m_bNeedClose = true;
	Listen(nPort, nListenNum, false);
	//J_OS::LOGINFO("CTCPSocket::CTCPSocket created and listen, handle = %d", m_handle);
}

CTCPSocket::CTCPSocket(const char *pAddr, int nPort)
{
	m_handle.sock = j_invalid_socket_val;
#ifdef WIN32
	WSADATA wsaData; 
	WSAStartup(MAKEWORD(2,2), &wsaData);
	m_handle.sock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
#else
	signal(SIGPIPE, SIG_IGN);
	m_handle.sock = socket(AF_INET, SOCK_STREAM, 0);
#endif

	m_bNeedClose = true;
	Connect(pAddr, nPort);
	//J_OS::LOGINFO("CTCPSocket::CTCPSocket created and connect, handle = %d", m_handle);
}

CTCPSocket::~CTCPSocket()
{
	if (m_bNeedClose && m_handle.sock != j_invalid_socket_val)
		j_close_socket(m_handle.sock);

	//J_OS::LOGINFO("CTCPSocket::~CTCPSocket destroyed, handle = %d", m_handle);
	m_handle.sock = j_invalid_socket_val;
#ifdef WIN32
	WSACleanup();
#endif
}

int CTCPSocket::Listen(j_uint16_t nPort, j_int32_t nListenNum, j_boolean_t bBlock)
{
	return Listen(m_handle, nPort, nListenNum, bBlock);
}

int CTCPSocket::Listen(j_socket_t nSock, unsigned short nPort, int nListenNum, bool bBlock)
{
	if (!bBlock)
		SetNonblocking();

	struct sockaddr_in sin_addr;
#ifndef WIN32
	bzero(&sin_addr, sizeof(sin_addr));
#endif
	sin_addr.sin_family = AF_INET;
	sin_addr.sin_port = htons(nPort);
	sin_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(nSock.sock, (struct sockaddr *)&sin_addr, sizeof(struct sockaddr)) == -1)
    {
    	J_OS::LOGERROR("CTCPSocket bind error, port = %d", nPort);

        return J_SOCKET_ERROR;
    }

    if (listen(nSock.sock, nListenNum) == -1)
    {
    	J_OS::LOGERROR("CTCPSocket listen error, port = %d", nPort);

    	return J_SOCKET_ERROR;
    }
    J_OS::LOGINFO("CTCPSocket::Listen sucess, handle = %d", nSock.sock);

	return J_OK;
}

int CTCPSocket::Connect(const char *pAddr, unsigned short nPort/*, struct timeval *tv*/)
{
    if (m_handle.sock == j_invalid_socket_val)
    {
        m_handle.sock = socket(AF_INET, SOCK_STREAM, 0);
    }
    //SetNonblocking();

	struct sockaddr_in sin_addr;
	sin_addr.sin_family = AF_INET;
	sin_addr.sin_port = htons(nPort);
	sin_addr.sin_addr.s_addr = inet_addr(pAddr);
	if (connect(m_handle.sock, (struct sockaddr *)&sin_addr, sizeof(sin_addr)) == -1)
    {
		/*if (errno == EINPROGRESS || errno == EALREADY)
		{
			fd_set fdSet;
			FD_ZERO(&fdSet);
			FD_SET(m_handle.sock, &fdSet);
			timeval tv;
			tv.tv_sec = 3;
			tv.tv_usec = 0;
			while(select(m_handle.sock + 1, &fdSet, NULL, NULL, &tv) < 0)
			{
				if (errno == EINTR)
					continue;
					
				J_OS::LOGERROR("CTCPSocket::Connect select error");
				j_close_socket(m_handle.sock);
				m_handle.sock = j_invalid_socket_val;
				return J_SOCKET_ERROR;
			}
		}*/
		j_close_socket(m_handle.sock);
        m_handle.sock = j_invalid_socket_val;

        J_OS::LOGERROR("CTCPSocket connect error, ip = %s, port = %d", pAddr, nPort);
        return J_SOCKET_ERROR;
    }

	SetNonblocking();
	SetKeepAlive();

	return J_OK;
}

int CTCPSocket::Disconnect()
{
	if (m_bNeedClose && m_handle.sock != j_invalid_socket_val)
		j_close_socket(m_handle.sock);

	m_handle.sock = j_invalid_socket_val;

	return J_OK;
}

int CTCPSocket::Read(char *pBuff, int nLen)
{
	return Read(m_handle, pBuff, nLen);
}

int CTCPSocket::Read(j_socket_t sock, char *pBuff, int nLen)
{
	int Read_times = 10;
read_begin:
	int nRecv = recv(sock.sock, pBuff, nLen, 0);
	if (nRecv <= 0)
	{
		J_OS::LOGERROR("CTCPSocket::Read nRecv = %d, errno = %d", nRecv, errno);
		if (errno == EINTR && nRecv < 0 && Read_times > 0)
		{
			j_sleep(1);
			--Read_times;
			goto read_begin;
		}
		else if (errno == EAGAIN && nRecv < 0)
		{
			j_sleep(1);
			goto read_begin;
		}
		else if (nRecv < 0)
		{
			return J_SOCKET_ERROR;
		}
		else if (errno == 0)
		{
		    nLen = 0;
		    return nRecv;
		}

		nLen = 0;
		return J_SOCKET_ERROR;
	}

	return nRecv;
	//return recv(nSock, pBuff, nLen, MSG_WAITALL);
}

int CTCPSocket::Write(const char *pBuff, int nLen)
{
	return Write(m_handle, pBuff, nLen);
}

int CTCPSocket::Write(j_socket_t sock, const char *pBuff, int nLen)
{
write_begin:
	int nSend = send(sock.sock, pBuff, nLen, 0/*MSG_NOSIGNAL*/);
	if (nSend < 0)
	{
		J_OS::LOGERROR("CTCPSocket::Write nSend = %d, errno = %d", nSend, errno);
		if (errno == EINTR)
		{
			j_sleep(1000);
			goto write_begin;
		}
		else if (errno == EAGAIN && nSend == 0)
		{
			j_sleep(1000);
			goto write_begin;
		}
		else if (errno == EAGAIN)
		{
			return J_SOCK_TIMEO;
		}

		return J_SOCKET_ERROR;
	}
	else if (nSend == 0)
		return J_SOCKET_ERROR;

	return nSend;
	//return send(nSock, pBuff, nLen, MSG_WAITALL);
}

int CTCPSocket::SetNonblocking(j_socket_t &sock)
{
	/*if (fcntl(nSock, F_SETFL, fcntl(nSock, F_GETFD, 0) | O_NONBLOCK) == -1)
    {
    	J_OS::LOGERROR("CTCPSocket fcntl error, socket = %d ", nSock);
      return J_SOCKET_ERROR;
    }*/

	struct timeval timeout;
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	if (setsockopt(sock.sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(struct timeval)) < 0)
	{
		j_close_socket(sock.sock);
		sock.sock = j_invalid_socket_val;

		J_OS::LOGERROR("CTCPSocket setsockopt SNDTIMEO error");
		return J_SOCKET_ERROR;
	}

	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	if (setsockopt(sock.sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval)) < 0)
	{
		j_close_socket(sock.sock);
		sock.sock = j_invalid_socket_val;

		J_OS::LOGERROR("CTCPSocket setsockopt RCVTIMEO error");
		return J_SOCKET_ERROR;
	}

   return J_OK;
}

int CTCPSocket::SetKeepAlive(j_socket_t &sock)
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
    return J_OK;
}

int CTCPSocket::Init(j_socket_t sock)
{
	if (m_handle.sock != j_invalid_socket_val)
		j_close_socket(m_handle.sock);

	m_handle = sock;
	m_bNeedClose = false;

	return J_OK;
}

int CTCPSocket::SetNonblocking()
{
    return SetNonblocking(m_handle);
}

int CTCPSocket::SetKeepAlive()
{
    return SetKeepAlive(m_handle);
}

int CTCPSocket::Read_n(char *pBuff, int nLen)
{
	int nTotleLen = nLen;
	int nRecvLen = 0;
	int nRet  = 0;
	while (nTotleLen > 0)
	{
		nRet=  recv(m_handle.sock, (char *)(pBuff  + nRecvLen), nTotleLen, 0);
		if (nRet <= 0)
		{
			J_OS::LOGERROR("CTCPSocket::Read_n nRead = %d", nRet);
			if ((errno == EAGAIN && nRet < 0) || (errno == EINTR && nRet < 0))
			{
				J_OS::LOGERROR("CTCPSocket::Read_n nRead2 = %d", nRet);
				j_sleep(1);
				continue;
			}
			J_OS::LOGINFO("QQQQQQQQQQQQQQQQQq");
			/*else if(errno == EAGAIN && nRet == 0)
			{
				J_OS::LOGINFO("QQQQQQQQQQQQQQQQQq");
				sleep(1);
			}*/
			return J_SOCKET_ERROR;
		}

		nRecvLen += nRet;
		nTotleLen -= nRet;
	}

	return nRecvLen;
}

int CTCPSocket::Write_n(const char *pBuff, int nLen)
{
	int nTotleLen = nLen;
	int nSendLen = 0;
	while (nTotleLen > 0)
	{
		int nRet  = 0;
		if (nTotleLen > IO_DATA_LEN)
			nRet = send(m_handle.sock, (char *)(pBuff  + nSendLen), IO_DATA_LEN, 0/*MSG_NOSIGNAL*/);
		else
			nRet = send(m_handle.sock, (char *)(pBuff + nSendLen), nTotleLen, 0/*MSG_NOSIGNAL*/);

		if (nRet <= 0)
		{
			if ((errno == EAGAIN && nRet < 0) || (errno == EINTR && nRet < 0))
			{
			    J_OS::LOGERROR("CTCPSocket::Write_n");
				j_sleep(1);
				continue;
			}

			return J_SOCKET_ERROR;
		}

		nSendLen += nRet;
		nTotleLen -= nRet;
	}

	return nSendLen;
}

}



