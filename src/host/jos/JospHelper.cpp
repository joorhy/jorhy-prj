#include "JospHelper.h"
#include "x_errtype.h"
#include "x_jo_sdk.h"

#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

CJospHelper::CJospHelper()
{
	m_nSeq = 0;
}

CJospHelper::~CJospHelper()
{
	
}
		
int CJospHelper::OpenStream(J_OS::CTCPSocket *recvSocket, const char *pResid, int nStreamType)
{
	char temp_buff[2048] = {0};
	CXJoSdk::Instance()->MakeReqHeader(temp_buff, NULL, jo_open_stream_req, jo_intact_pack, 0, sizeof(J_RealViewData));
	J_RealViewData *pRealViewData = (J_RealViewData *)(temp_buff + sizeof(J_CtrlHead));
	
	const char *pNextId = strstr(pResid, ".");
	memcpy(pRealViewData->res_id, pNextId + 1, strlen(pNextId + 1));
	pRealViewData->stream_type = htonl(nStreamType);
	recvSocket->Write_n(temp_buff, sizeof(J_CtrlHead) + sizeof(J_RealViewData));
	
	J_CtrlHead ctrlHead = {0};
	recvSocket->Read_n((char *)&ctrlHead, sizeof(J_CtrlHead));
	if (ctrlHead.ret == 0)
	{
		int nExLength = ntohs(ctrlHead.ex_length);
		if (nExLength > 0)
			recvSocket->Read_n(temp_buff, nExLength);
			
		return J_OK;
	}
	
	return J_UNKNOW;
}

void CJospHelper::CloseStream(J_OS::CTCPSocket *recvSocket, const char *pResid)
{

}