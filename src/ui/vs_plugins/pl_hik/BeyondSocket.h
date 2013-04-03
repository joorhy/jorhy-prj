#pragma once

#include <WinSock.h>

class BeyondSocket
{
public:
	BeyondSocket(void);
	BeyondSocket(SOCKET hSocket);
	BeyondSocket(const char *pAddr, int nPort);
	~BeyondSocket(void);

public:
	BOOL Connect(const char *pAddr, int nPort);
	int Read(char *OUT_pBuff, int nLen);
	int Write(const char *pBuff, int nLen);
	int Read_n(char *pBuff, int nLen);
	int Write_n(const char *pBuff, int nLen);
	BOOL EnableBlock(BOOL bEnable=TRUE);
	BOOL SetTimeOut(int nRcvMS = 0,int nSendMS = 0);		//Í¬²½³¬Ê±

private:
	SOCKET m_hSocket;
};
