#include "JorFileHelper.h"
#include "x_jo_sdk.h"

CJorFileHelper::CJorFileHelper()
{
	
}

CJorFileHelper::~CJorFileHelper()
{
	
}

int CJorFileHelper::OpenFile(J_OS::CTCPSocket *recvSocket, const char *pResid, j_time_t begin, j_time_t end)
{
	char temp_buff[2048] = {0};
	JoXJoSdk->MakeReqHeader(temp_buff, NULL, jo_open_file_req, jo_intact_pack, 0, sizeof(J_VodPlayData));
	J_VodPlayData *pVodPlayData = (J_VodPlayData *)(temp_buff + sizeof(J_CtrlHead));
	
	const char *pNextId = strstr(pResid, ".");
	if (pNextId != NULL)
		memcpy(pVodPlayData->res_id, pNextId + 1, strlen(pNextId + 1));
	else
		memcpy(pVodPlayData->res_id, pResid, strlen(pResid));
	pVodPlayData->begin_time = htonl(begin);
	pVodPlayData->end_time = htonl(end);
	recvSocket->Write_n(temp_buff, sizeof(J_CtrlHead) + sizeof(J_VodPlayData));
	
	J_CtrlHead ctrlHead = {0};
	recvSocket->Read_n((char *)&ctrlHead, sizeof(J_CtrlHead));
	if (ctrlHead.ret == 0)
	{
		int nExLength = ntohs(ctrlHead.ex_length);
		if (nExLength > 0)
			recvSocket->Read_n(temp_buff, nExLength);
			
		return J_OK;
	}
	return J_FILE_ERROR;
}

void CJorFileHelper::CloseFile(J_OS::CTCPSocket *recvSocket, const char *pResid)
{
	
}

int CJorFileHelper::ReadFile(J_OS::CTCPSocket *recvSocket, const char *pResid, j_time_t begin, int nIval)
{
	char temp_buff[2048] = {0};
	JoXJoSdk->MakeReqHeader(temp_buff, NULL, jo_req_data_req, jo_intact_pack, 0, sizeof(J_RequestData));
	J_RequestData *pRequestData = (J_RequestData *)(temp_buff + sizeof(J_CtrlHead));
	
	const char *pNextId = strstr(pResid, ".");
	if (pNextId != NULL)
		memcpy(pRequestData->res_id, pNextId + 1, strlen(pNextId + 1));
	else
		memcpy(pRequestData->res_id, pResid, strlen(pResid));
	pRequestData->begin_time = htonl(begin);
	pRequestData->time_ival = htonl(nIval);
	recvSocket->Write_n(temp_buff, sizeof(J_CtrlHead) + sizeof(J_RequestData));
	
	return J_OK;
	/*J_CtrlHead ctrlHead = {0};
	recvSocket->Read_n((char *)&ctrlHead, sizeof(J_CtrlHead));
	if (ctrlHead.ret == 0)
	{
		int nExLength = ntohs(ctrlHead.ex_length);
		if (nExLength > 0)
			recvSocket->Read_n(temp_buff, nExLength);
			
		return J_OK;
	}
	return J_SOCKET_ERROR;*/
}