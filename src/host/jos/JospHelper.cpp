#include "JospHelper.h"
#include "x_errtype.h"

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
		
int CJospHelper::OpenStream(J_OS::CTCPSocket *m_recvSocket, const char *pResid, int nStreamType)
{
	char temp_buff[2048] = {0};
	MakeHeader(temp_buff, NULL, jo_open_stream_req, jo_intact_pack, 0, sizeof(J_RealViewData));
	J_RealViewData *pRealViewData = (J_RealViewData *)(temp_buff + sizeof(J_CtrlHead));
	memcpy(pRealViewData->res_id, pResid, strlen(pResid));
	pRealViewData->stream_type = nStreamType;
	m_recvSocket->Write_n(temp_buff, strlen(temp_buff));
	
	J_CtrlHead ctrlHead = {0};
	m_recvSocket->Read_n((char *)&ctrlHead, sizeof(ctrlHead));
	if (ctrlHead.ret == 0)
	{
		int nExLength = ntohs(ctrlHead.ex_length);
		if (nExLength > 0)
			m_recvSocket->Read_n(temp_buff, nExLength);
			
		return J_OK;
	}
	
	return J_UNKNOW;
}

void CJospHelper::CloseStream(J_OS::CTCPSocket *m_recvSocket, const char *pResid)
{

}

int CJospHelper::MakeHeader(char *pBuffer, char *pUserID, unsigned char byCmd, unsigned char byFlag, unsigned short sqNum, unsigned short exLength, unsigned char byRet)
{
    J_CtrlHead *ctrlHeader = (J_CtrlHead *)pBuffer;
    memset(ctrlHeader, 0, sizeof(J_CtrlHead));
    memcpy(ctrlHeader->start_code, "JOSP", 4);
    ctrlHeader->version = 0x01;
    ctrlHeader->type = 0x00;       //TCP
    ctrlHeader->flag = byFlag;
    ctrlHeader->sq_num = htons(sqNum);
    ctrlHeader->cmd = byCmd;
    ctrlHeader->ret = byRet;
    ctrlHeader->reserved = 0x00;
    ctrlHeader->ex_length = htons(exLength);
    if (pUserID == NULL)
        memset(ctrlHeader->user_id, 0, sizeof(ctrlHeader->user_id));
    else
        memcpy(ctrlHeader->user_id, pUserID, sizeof(ctrlHeader->user_id));
    memset(ctrlHeader->crc, 0, sizeof(ctrlHeader->crc));

    return J_OK;
}