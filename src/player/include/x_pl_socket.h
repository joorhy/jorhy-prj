#pragma once
#include "x_pl_base.h"
#include "x_pl_common.h"
#include "x_pl_error.h"

class J_PlSocket : public J_PlBase
{
public:
	J_PlSocket(void);
	J_PlSocket(const char *pAddr, int nPort);
	~J_PlSocket(void);

public:
	J_PL_RESULT NRead(char *pBuff, int nLen);
	J_PL_RESULT NWrite(const char *pBuff, int nLen);
	J_PL_RESULT BlockConnect(const char *pAddr, int nPort);
	J_PL_RESULT SetTimeOut(int nRcvMS = 0,int nSendMS = 0);		//Í¬²½³¬Ê±
	J_PL_RESULT AvaiableConnect();
	J_PL_RESULT NonblockConnect(const char *pAddr, int nPort,unsigned int unTimeout);

private:
	unsigned int m_hSocket;
	bool m_bConnecting;
};
