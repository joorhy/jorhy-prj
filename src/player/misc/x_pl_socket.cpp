#include "x_pl_socket.h"
#include <WinSock2.h>
#include "x_pl_default_config.h"
#include "x_pl_log.h"
#include <errno.h>
#include "MSTCPiP.h" 

#define IO_READ_SIZE 1400
#define READ_TIMES_EXIT 1

J_PlSocket::J_PlSocket(void)
{
	WSADATA wsaData;
	WSAStartup (MAKEWORD(2,2), &wsaData);  
	m_bConnecting = false;
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
}

J_PlSocket::J_PlSocket(const char *pAddr, int nPort)
{
	WSADATA wsaData;
	WSAStartup (MAKEWORD(2,2), &wsaData);  
	m_bConnecting = false;
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
	BlockConnect(pAddr, nPort);
}

J_PlSocket::~J_PlSocket(void)
{
	if (m_hSocket != INVALID_SOCKET)
	{
		shutdown(m_hSocket,SD_BOTH);			//importent
		closesocket(m_hSocket);
	}

	WSACleanup();
}

J_PL_RESULT J_PlSocket::NRead(char *OUT_pBuff, int nLen)
{
	if(!m_bConnecting)
		return J_PL_ERROR_CONNECT;

	int nTotleLen = nLen;
	int nRecvLen = 0;
	int timeout = 0;
	int error;

	//j_pl_error("nTotleLen = %d\n",nTotleLen);
	while (nTotleLen > 0)
	{
		int nRet  = 0;
		if (nTotleLen > IO_READ_SIZE)
			nRet=  recv(m_hSocket,OUT_pBuff  + nRecvLen,IO_READ_SIZE,0);
		else
			nRet = recv(m_hSocket,OUT_pBuff + nRecvLen,nTotleLen, 0);

		if(nRet == -1)
		{
			error = WSAGetLastError();
			switch (error)
			{
			case WSAEWOULDBLOCK:
			case WSAEINTR:
				Sleep(1);
				continue;
			case WSAETIMEDOUT:
				j_pl_error("Receive TimeOut\n");
				break;

			case WSAEMSGSIZE:			//udp only
			case WSAECONNRESET:
				j_pl_error("Receive Ret=%d,code=%d\n",nRet,WSAGetLastError());
				return J_PL_ERROR_RECEIVE;
			}
			j_pl_warn("Receive Ret=%d,code=%d\n",nRet,WSAGetLastError());
			if(++timeout >= READ_TIMES_EXIT)		//连续READ_TIMES_EXIT次没有收到数据，退出
				return J_PL_ERROR_RECEIVE;
		}
		else if(nRet == 0)
			break;
		else
			timeout = 0;

		nRecvLen += nRet;
		nTotleLen -= nRet;
	}
	if (nLen != nRecvLen)
		return J_PL_ERROR_RECEIVE;

	return nLen == nRecvLen ? J_PL_NO_ERROR : J_PL_ERROR_RECEIVE;
}

J_PL_RESULT J_PlSocket::NWrite(const char *pBuff, int nLen)
{
	if(!m_bConnecting)
		return J_PL_ERROR_CONNECT;

	int nTotleLen = nLen;
	int nSendLen = 0;
	while (nTotleLen > 0)
	{
		int nRet  = 0;
		if (nTotleLen > IO_READ_SIZE)
			nRet=  send(m_hSocket,(char *)(pBuff  + nSendLen),IO_READ_SIZE, 0);
		else
			nRet = send(m_hSocket,(char *)(pBuff + nSendLen),nTotleLen, 0);
		if (nRet == -1)
		{
			if(errno == EINTR)
				continue;
			j_pl_error("Write Ret=%d,code=%d\n",nRet,GetLastError());
			break;
		}

		nSendLen += nRet;
		nTotleLen -= nRet;
	}

	return nLen == nSendLen ? J_PL_NO_ERROR : J_PL_ERROR_WRITE;
}

J_PL_RESULT J_PlSocket::BlockConnect(const char *pAddr, int nPort)
{
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(nPort);
	sin.sin_addr.S_un.S_addr = inet_addr(pAddr);
	//SetTimeOut(3000,3000);
	if(connect( m_hSocket, (sockaddr *)&sin, sizeof(sin)) < 0)
		return J_PL_ERROR_CONNECT;

	m_bConnecting = true;
	return SetTimeOut(3000,3000);
}

J_PL_RESULT J_PlSocket::SetTimeOut(int nRcvMS,int nSendMS)
{
	DWORD dwError = 0L ;
	DWORD dwBytes;
	/*tcp_keepalive sKA_Settings = {0}, sReturned = {0} ;
	sKA_Settings.onoff					= 1 ;
	sKA_Settings.keepalivetime		= 500 ; // Keep Alive in 5.5 sec.
	sKA_Settings.keepaliveinterval	= 500 ; // Resend if No-Reply
	if (WSAIoctl(m_hSocket, SIO_KEEPALIVE_VALS, &sKA_Settings,
		sizeof(sKA_Settings), &sReturned, sizeof(sReturned), &dwBytes,
		NULL, NULL) != 0)
	{
		dwError = WSAGetLastError() ;
		return J_PL_ERROR_SOCKET;
	}*/
	if(nRcvMS > 0)
	{
		if(setsockopt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&nRcvMS, sizeof(nRcvMS)) == SOCKET_ERROR)
		{
			closesocket(m_hSocket);
			m_hSocket = INVALID_SOCKET;
			return J_PL_ERROR_SOCKET;
		}
	}
	if(nSendMS > 0)
	{
		if(setsockopt(m_hSocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&nSendMS, sizeof(nSendMS)) == SOCKET_ERROR)
		{
			closesocket(m_hSocket);
			m_hSocket = INVALID_SOCKET;
			return J_PL_ERROR_SOCKET;
		}
	}

	return J_PL_NO_ERROR;
}

J_PL_RESULT J_PlSocket::AvaiableConnect()
{
	if(m_bConnecting)
		return J_PL_NO_ERROR;
	return J_PL_ERROR_CONNECT;
}

J_PL_RESULT J_PlSocket::NonblockConnect(const char *pAddr, int nPort,unsigned int unTimeout)
{
	unsigned long ul = 1;
	if(ioctlsocket(m_hSocket,FIONBIO,(unsigned long*)&ul) == SOCKET_ERROR)
	{
		j_pl_error("socket:%d\n",WSAGetLastError());
		return J_PL_ERROR_SOCKET;
	}

	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(nPort);
	sin.sin_addr.S_un.S_addr = inet_addr(pAddr);

	int nRet = 0;
	if (connect( m_hSocket, (sockaddr *)&sin, sizeof(sin)) < 0)
	{
		nRet = WSAGetLastError();
		if (nRet != WSAEWOULDBLOCK)
			return J_PL_ERROR_SOCKET;
	}

	timeval	timeout = {0};
	fd_set   rset, wset;
	FD_ZERO(&rset);
	FD_ZERO(&wset);
	FD_SET(m_hSocket,&rset);
	wset = rset;
	//timeout.tv_sec = unTimeout;
	timeout.tv_usec = 100 * 1000;
	if((nRet = select(1,0,&rset,0,&timeout)) == 0)
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
		return J_PL_ERROR_SOCKET;
	}
	int len = 0;
	if (FD_ISSET(m_hSocket, &rset) || FD_ISSET(m_hSocket, &wset)) 
	{
		len = sizeof(nRet);
		if (getsockopt(m_hSocket, SOL_SOCKET, SO_ERROR, (char *)&nRet, &len) < 0)
			return J_PL_ERROR_SOCKET;   /* Solaris pending error */
	}
	else
	{
		j_pl_error("select error: sockfd not set \n");
		return J_PL_ERROR_SOCKET;
	}

	if (nRet) 
	{
		closesocket(m_hSocket);  /* just in case */
		return J_PL_ERROR_SOCKET;
	}

	ul = 0;
	if(ioctlsocket(m_hSocket,FIONBIO,(unsigned long*)&ul) == SOCKET_ERROR)
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
		return J_PL_ERROR_SOCKET;
	}
	
	m_bConnecting = true;
	return SetTimeOut(3000, 3000);
}