#include "JospFilter.h"
#include "x_string.h"
#include "x_socket.h"
#include "MuxFactory.h"

const int RATE = 1024;

CJospFilter::CJospFilter()
{
	m_muxFilter = NULL;
	m_nRetLen = 0;
	m_pRetBuff = new char[1024];
	memset(m_strResid, 0, sizeof(m_strResid));
}

CJospFilter::~CJospFilter()
{
	if (m_muxFilter)
		CMuxFactory::Instance()->DelMux(this);
	
	if (m_pRetBuff)
		delete m_pRetBuff;
}

int CJospFilter::Parser(int nSocket)
{
	J_OS::CTCPSocket readSocket(nSocket);
	J_CtrlHead ctrlHead = {0};
	int read_ret = readSocket.Read_n((char *)&ctrlHead, sizeof(J_CtrlHead));
	if (read_ret < 0)
		return J_SOCKET_ERROR;
	
	if (ctrlHead.cmd == JO_OPEN_STREAM)
	{
		J_RealViewData realViewData = {0};
		read_ret = readSocket.Read_n((char *)&realViewData, sizeof(J_RealViewData));
		if (read_ret < 0)
			return J_SOCKET_ERROR;
			
		m_nCommandType = J_START_REAL;
		m_nStreamType = realViewData.stream_type;
		memcpy(m_strResid, realViewData.res_id, strlen(realViewData.res_id));
		
		MakeHeader(m_pRetBuff, JO_OPEN_STREAM_RET, sizeof(J_RealViewRetData));
		J_RealViewRetData *pRetData = (J_RealViewRetData *)(m_pRetBuff + sizeof(J_CtrlHead));
		memcpy(pRetData->media_code, "JOMS", 4);
		pRetData->fps = 25;
		
		m_nRetLen = sizeof(J_CtrlHead) + sizeof(J_RealViewRetData);
	}
	m_muxFilter = CMuxFactory::Instance()->GetMux(this, "jos");

	return J_OK;
}

const char *CJospFilter::GetResourceType()
{
		return "jofs";
}

int CJospFilter::Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen)
{
	return m_muxFilter->Convert((const char *)pInputData, streamHeader, pOutputData, nOutLen, (void *)&RATE);
}

int CJospFilter::Complete(int nSocket)
{
	J_OS::CTCPSocket writeSocket(nSocket);
	if (writeSocket.Write_n((char *)m_pRetBuff, m_nRetLen) < 0)
	{
		J_OS::LOGERROR("CJospFilter::Complete Send Header error");
		return J_SOCKET_ERROR;
	}

	return J_OK;
}

int CJospFilter::MakeHeader(char *pBuffer, uint8_t byCmd, uint16_t exLength, uint8_t byRet)
{
	J_CtrlHead *ctrlHeader = (J_CtrlHead *)pBuffer;
    memset(ctrlHeader, 0, sizeof(J_CtrlHead));
    memcpy(ctrlHeader->start_code, "JOSP", 4);
    ctrlHeader->version = 0x01;
    ctrlHeader->type = 0x00;       //TCP
    ctrlHeader->flag = 0;
    ctrlHeader->sq_num = 0;
    ctrlHeader->cmd = byCmd;
    ctrlHeader->ret = byRet;
    ctrlHeader->reserved = 0x00;
    ctrlHeader->ex_length = htons(exLength);
	memset(ctrlHeader->user_id, 0, sizeof(ctrlHeader->user_id));
    memset(ctrlHeader->crc, 0, sizeof(ctrlHeader->crc));
	return J_OK;
}
