#pragma once
#include "btkbase.h"
#include "BTKCommon.h"
#include "BTKError.h"


class BTKSockt : public BTKBase
{
public:
	BTKSockt(void);
	BTKSockt(const char *pAddr, int nPort);
	~BTKSockt(void);

public:
	BTK_RESULT NRead(char *pBuff, int nLen);
	BTK_RESULT NWrite(const char *pBuff, int nLen);
	BTK_RESULT BlockConnect(const char *pAddr, int nPort);
	BTK_RESULT SetTimeOut(int nRcvMS = 0,int nSendMS = 0);		//Í¬²½³¬Ê±
	BTK_RESULT AvaiableConnect();
	BTK_RESULT NonblockConnect(const char *pAddr, int nPort,unsigned int unTimeout);

private:
	unsigned int m_hSocket;
	bool m_bConnecting;
};
