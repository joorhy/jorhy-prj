#ifndef __X_SOCKET_H_
#define __X_SOCKET_H_

#include "x_errtype.h"
#include "x_log.h"
#include "j_common.h"

namespace J_OS
{

class JO_API CTCPSocket
{
public:
	CTCPSocket();
	CTCPSocket(j_socket_t socket);
	CTCPSocket(j_int32_t nPort, j_int32_t nListenNum);
	CTCPSocket(const j_char_t *pAddr, j_int32_t nPort);
	~CTCPSocket();

public:
	int Listen(j_uint16_t nPort, j_int32_t nListenNum = 10, j_boolean_t bBlock = true);
	int Listen(j_socket_t nSock, j_uint16_t nPort, j_int32_t nListenNum = 10, j_boolean_t bBlock = true);
	int Connect(const j_char_t *pAddr, j_uint16_t nPort/*, struct timeval *tv = NULL*/);
	int Disconnect();
	int Read(j_char_t *pBuff, j_int32_t nLen);
	int Read(j_socket_t nSock, j_char_t *pBuff, j_int32_t nLen);
	int Write(const j_char_t *pBuff, j_int32_t nLen);
	int Write(j_socket_t nSock, const j_char_t *pBuff, j_int32_t nLen);
	int Read_n(j_char_t *pBuff, j_int32_t nLen);
	int Write_n(const j_char_t *pBuff, j_int32_t nLen);

	int SetNonblocking(j_socket_t &nSock);
	int SetKeepAlive(j_socket_t &nSock);
	j_socket_t GetHandle() const { return m_handle; }
	int Init(j_socket_t nSocket);

private:
	int SetNonblocking();
	int SetKeepAlive();

private:
	j_socket_t m_handle;
	j_boolean_t m_bNeedClose;
};

}


#endif // ~__X_SOCKET_H_
