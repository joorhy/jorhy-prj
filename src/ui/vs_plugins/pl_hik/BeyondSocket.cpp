#include "StdAfx.h"
#include "BeyondSocket.h"
#include "PlayerDataCenter.h"

BeyondSocket::BeyondSocket(void)
{
	WSADATA wsaData;
	WSAStartup (MAKEWORD(2,2), &wsaData);  

	m_hSocket = INVALID_SOCKET;
}

BeyondSocket::BeyondSocket(SOCKET hSocket)
{
	WSADATA wsaData;
	WSAStartup (MAKEWORD(2,2), &wsaData);  

	m_hSocket = hSocket;
}

BeyondSocket::BeyondSocket(const char *pAddr, int nPort)
{
	WSADATA wsaData;
	WSAStartup (MAKEWORD(2,2), &wsaData);  

	m_hSocket = INVALID_SOCKET;
	Connect(pAddr, nPort);
}

BeyondSocket::~BeyondSocket(void)
{
	if (m_hSocket != INVALID_SOCKET)
		closesocket(m_hSocket);

	WSACleanup();
}

BOOL BeyondSocket::Connect(const char *pAddr, int nPort)
{
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(m_hSocket == INVALID_SOCKET)
		return FALSE;
	/*if(!EnableBlock())
		return FALSE;*/

	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(nPort);
	sin.sin_addr.S_un.S_addr = inet_addr(pAddr);
	connect( m_hSocket, (sockaddr *)&sin, sizeof(sin));

	/*struct timeval connTimeout ;
	fd_set connSet;
	
	FD_ZERO(&connSet);
	FD_SET(m_hSocket, &connSet);
	connTimeout.tv_sec = 3;			//连接超时3秒
	connTimeout.tv_usec =0;
	if(select(0, &connSet, &connSet, 0, &connTimeout) <= 0)
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;

		return FALSE;
	} */
	SetTimeOut(3000,3000);
	return TRUE;
}

int BeyondSocket::Read(char *OUT_pBuff, int nLen)
{
	int nReadLen = 0;
	if((nReadLen = recv(m_hSocket,OUT_pBuff,nLen,0)) < 0 )
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}
	return nReadLen;
}

int BeyondSocket::Write(const char *pBuff, int nLen)
{
	int nWriteLen = 0;
	if ((nWriteLen = send(m_hSocket, pBuff, nLen, 0)) < 0)
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}

	return nWriteLen;
}

int BeyondSocket::Read_n(char *OUT_pBuff, int nLen)
{
	int nTotleLen = nLen;
	int nRecvLen = 0;
	while (nTotleLen > 0)
	{
		int nRet  = 0;
		if (nTotleLen > IO_READ_SIZE)
			nRet=  recv(m_hSocket, (char *)(OUT_pBuff  + nRecvLen), IO_READ_SIZE, 0);
		else
			nRet = recv(m_hSocket, (char *)(OUT_pBuff + nRecvLen), nTotleLen, 0);

		if (nRet <= 0)
			return -1;

		nRecvLen += nRet;
		nTotleLen -= nRet;
	}
	return nRecvLen;
}

int BeyondSocket::Write_n(const char *pBuff, int nLen)
{
	int sendvLen = 0;
	return sendvLen;
}

BOOL BeyondSocket::EnableBlock(BOOL bEnable)
{
	if(bEnable)
	{
		unsigned long ulConnect= 1;			//允许非阻塞
		if(ioctlsocket(m_hSocket, FIONBIO, (unsigned long*)&ulConnect) == 0)
			return TRUE;
		else
		{
			closesocket(m_hSocket);
			m_hSocket = INVALID_SOCKET;
		}
	}
	else
	{
		unsigned long ulConnect= 0;			//禁止非阻塞
		if(ioctlsocket(m_hSocket, FIONBIO, (unsigned long*)&ulConnect) == 0)
			return TRUE;
		else
		{
			closesocket(m_hSocket);
			m_hSocket = INVALID_SOCKET;
		}
	}
	return FALSE;
}

BOOL BeyondSocket::SetTimeOut(int nRcvMS,int nSendMS)
{
	EnableBlock(false);
	if(nRcvMS > 0)
	{
		if(setsockopt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&nRcvMS, sizeof(nRcvMS)) != 0)
		{
			closesocket(m_hSocket);
			m_hSocket = INVALID_SOCKET;
			return FALSE;
		}
	}
	if(nSendMS > 0)
	{
		if(setsockopt(m_hSocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&nSendMS, sizeof(nSendMS)) != 0)
		{
			closesocket(m_hSocket);
			m_hSocket = INVALID_SOCKET;
			return FALSE;
		}
	}
	return TRUE;
}