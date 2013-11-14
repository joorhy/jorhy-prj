#pragma once
#include "j_includes.h"
#include "x_asio_udp_win.h"

class CNodeManager : public J_AsioUser
{
public:
	CNodeManager();
	~CNodeManager();

public:
	///J_AsioUser
	virtual j_result_t OnRead(const J_AsioDataBase *pAsioData, j_result_t nRet);
	virtual j_result_t OnWrite(const J_AsioDataBase *pAsioData, j_result_t nRet);

public:
	j_result_t Start(j_int32_t nPort);
	j_void_t Stop();

private:
	CXUdpAsio m_asio;
};