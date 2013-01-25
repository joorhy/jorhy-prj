#ifndef __X_SOCKET_H_
#define __X_SOCKET_H_

#include "x_errtype.h"
#include "x_log.h"

namespace J_OS
{
#define INVALID_HANDLE	(-1)

class CTCPSocket
{
public:
	CTCPSocket();
	CTCPSocket(int nSocket);
	CTCPSocket(int nPort, int nListenNum);
	CTCPSocket(const char *pAddr, int nPort);
	~CTCPSocket();

public:
	int Listen(unsigned short nPort, int nListenNum = 10, bool bBlock = true);
	int Connect(const char *pAddr, unsigned short nPort/*, struct timeval *tv = NULL*/);
	int Disconnect();
	int Read(char *pBuff, int nLen);
	int Read(int nSock, char *pBuff, int nLen);
	int Write(const char *pBuff, int nLen);
	int Write(int nSock, const char *pBuff, int nLen);
	int Read_n(char *pBuff, int nLen);
	int Write_n(const char *pBuff, int nLen);

	int SetNonblocking(int &nSock);
	int SetKeepAlive(int &nSock);
	int GetHandle() const { return m_handle; };
	int Init(int nSocket);

private:
	int SetNonblocking();
	int SetKeepAlive();

private:
	int m_handle;
	bool m_bNeedClose;
};

}


#endif // ~__X_SOCKET_H_
