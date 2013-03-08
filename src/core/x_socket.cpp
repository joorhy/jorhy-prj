#include "x_socket.h"

#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>

#define IO_DATA_LEN	65535

namespace J_OS
{

CTCPSocket::CTCPSocket()
: m_handle(INVALID_HANDLE)
{
	signal(SIGPIPE, SIG_IGN);

	m_handle = socket(AF_INET, SOCK_STREAM, 0);
	m_bNeedClose = true;
	//J_OS::LOGINFO("CTCPSocket::CTCPSocket created, handle = %d", m_handle);
}

CTCPSocket::CTCPSocket(int nSocket)
{
	m_handle = nSocket;
	m_bNeedClose = false;
}

CTCPSocket::CTCPSocket(int nPort, int nListenNum)
{
	signal(SIGPIPE, SIG_IGN);

	m_handle = socket(AF_INET, SOCK_STREAM, 0);
	m_bNeedClose = true;
	Listen(nPort, nListenNum, false);
	//J_OS::LOGINFO("CTCPSocket::CTCPSocket created and listen, handle = %d", m_handle);
}

CTCPSocket::CTCPSocket(const char *pAddr, int nPort)
: m_handle(INVALID_HANDLE)
{
	signal(SIGPIPE, SIG_IGN);

	m_handle = socket(AF_INET, SOCK_STREAM, 0);
	m_bNeedClose = true;
	Connect(pAddr, nPort);
	//J_OS::LOGINFO("CTCPSocket::CTCPSocket created and connect, handle = %d", m_handle);
}

CTCPSocket::~CTCPSocket()
{
	if (m_bNeedClose && m_handle != INVALID_HANDLE)
		close(m_handle);


	//J_OS::LOGINFO("CTCPSocket::~CTCPSocket destroyed, handle = %d", m_handle);
	m_handle = INVALID_HANDLE;
}

int CTCPSocket::Listen(unsigned short nPort, int nListenNum, bool bBlock)
{
	if (!bBlock)
		SetNonblocking();

	struct sockaddr_in sin_addr;
	bzero(&sin_addr, sizeof(sin_addr));
	sin_addr.sin_family = AF_INET;
	sin_addr.sin_port = htons(nPort);
	sin_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_handle, (struct sockaddr *)&sin_addr, sizeof(struct sockaddr)) == -1)
    {
    	J_OS::LOGERROR("CTCPSocket bind error, port = %d", nPort);

        return J_SOCKET_ERROR;
    }

    if (listen(m_handle, nListenNum) == -1)
    {
    	J_OS::LOGERROR("CTCPSocket listen error, port = %d", nPort);

    	return J_SOCKET_ERROR;
    }
    J_OS::LOGINFO("CTCPSocket::Listen sucess, handle = %d", m_handle);

	return J_OK;
}

int CTCPSocket::Connect(const char *pAddr, unsigned short nPort/*, struct timeval *tv*/)
{
    if (m_handle == INVALID_HANDLE)
    {
        m_handle = socket(AF_INET, SOCK_STREAM, 0);
    }
    SetNonblocking();

	struct sockaddr_in sin_addr;
	sin_addr.sin_family = AF_INET;
	sin_addr.sin_port = htons(nPort);
	sin_addr.sin_addr.s_addr = inet_addr(pAddr);
    if (connect(m_handle, (struct sockaddr *)&sin_addr, sizeof(sin_addr)) == -1)
    {
        close(m_handle);
        m_handle = INVALID_HANDLE;

        J_OS::LOGERROR("CTCPSocket connect error, ip = %s, port = %d", pAddr, nPort);
        return J_SOCKET_ERROR;
    }

	//SetNonblocking();
	SetKeepAlive();

	return J_OK;
}

int CTCPSocket::Disconnect()
{
	if (m_bNeedClose && m_handle != INVALID_HANDLE)
		close(m_handle);
	m_handle = INVALID_HANDLE;

	return J_OK;
}

int CTCPSocket::Read(char *pBuff, int nLen)
{
	return Read(m_handle, pBuff, nLen);
}

int CTCPSocket::Read(int nSock, char *pBuff, int nLen)
{
	int Read_times = 10;
read_begin:
	int nRecv = recv(nSock, pBuff, nLen, 0);
	if (nRecv <= 0)
	{
		J_OS::LOGERROR("CTCPSocket::Read nRecv = %d, errno = %d", nRecv, errno);
		if (errno == EINTR && Read_times > 0)
		{
			usleep(1000);
			--Read_times;
			goto read_begin;
		}
		else if (errno == EAGAIN && nRecv == 0)
		{
			usleep(1000);
			goto read_begin;
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

int CTCPSocket::Write(int nSock, const char *pBuff, int nLen)
{
write_begin:
	int nSend = send(nSock, pBuff, nLen, 0/*MSG_NOSIGNAL*/);
	if (nSend <= 0)
	{
		//J_OS::LOGERROR("CTCPSocket::Write nSend = %d, errno = %d", nSend, errno);
		if (errno == EINTR)
		{
			usleep(1000);
			goto write_begin;
		}
		else if (errno == EAGAIN && nSend == 0)
		{
			usleep(1000);
			goto write_begin;
		}
		else if (errno == EAGAIN)
		{
			return J_SOCK_TIMEO;
		}

		return J_SOCKET_ERROR;
	}

	return nSend;
	//return send(nSock, pBuff, nLen, MSG_WAITALL);
}

int CTCPSocket::SetNonblocking(int &nSock)
{
	/*if (fcntl(nSock, F_SETFL, fcntl(nSock, F_GETFD, 0) | O_NONBLOCK) == -1)
    {
    	J_OS::LOGERROR("CTCPSocket fcntl error, socket = %d ", nSock);
      return J_SOCKET_ERROR;
    }*/

	struct timeval timeout;
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	if (setsockopt(nSock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(struct timeval)) < 0)
	{
		close(nSock);
		nSock = INVALID_HANDLE;

		J_OS::LOGERROR("CTCPSocket setsockopt SNDTIMEO error");
		return J_SOCKET_ERROR;
	}

	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	if (setsockopt(nSock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval)) < 0)
	{
		close(nSock);
		nSock = INVALID_HANDLE;

		J_OS::LOGERROR("CTCPSocket setsockopt RCVTIMEO error");
		return J_SOCKET_ERROR;
	}

   return J_OK;
}

int CTCPSocket::SetKeepAlive(int &nSocket)
{
    //开启tcp探测
    int keepAlive = 1; 		// 开启keepalive属性
    int keepIdle = 3; 		// 如该连接在3秒内没有任何数据往来,则进行探测
    int keepInterval = 1;	// 探测时发包的时间间隔为2秒
    //int keepCount = 3; 		// 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.
    setsockopt(nSocket, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, sizeof(keepAlive));
    setsockopt(nSocket, SOL_TCP, TCP_KEEPIDLE, (void*)&keepIdle, sizeof(keepIdle));
    setsockopt(nSocket, SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
    return J_OK;
}

int CTCPSocket::Init(int nSocket)
{
	if (m_handle != INVALID_HANDLE)
		close(m_handle);

	m_handle = nSocket;
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
		nRet=  recv(m_handle, (char *)(pBuff  + nRecvLen), nTotleLen, 0);
		if (nRet <= 0)
		{
			J_OS::LOGERROR("CTCPSocket::Read_n nRead = %d", nRet);
			if ((errno == EAGAIN && nRet < 0) || errno == EINTR)
			{
				J_OS::LOGERROR("CTCPSocket::Read_n nRead2 = %d", nRet);
				usleep(10);
				continue;
			}
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
			nRet=  send(m_handle, (char *)(pBuff  + nSendLen), IO_DATA_LEN, MSG_NOSIGNAL);
		else
			nRet = send(m_handle, (char *)(pBuff + nSendLen), nTotleLen, MSG_NOSIGNAL);

		if (nRet <= 0)
		{
			if ((errno == EAGAIN && nRet == 0)|| errno == EINTR)
			{
			    J_OS::LOGERROR("CTCPSocket::Write_n");
				usleep(1000);
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



