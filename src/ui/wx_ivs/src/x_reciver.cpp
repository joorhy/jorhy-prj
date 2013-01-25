#include "x_reciver.h"
#include "x_errtype.h"
#include "j_type.h"
#include "x_decoder.h"
#include <arpa/inet.h>

CXReciver::CXReciver(CXDecoder *decoder)
{
	m_bRun = false;
	m_pDecoder = decoder;
	m_pRecvBuff = new char[1024 * 1024];
}

CXReciver::~CXReciver()
{
	if (m_pRecvBuff)
		delete m_pRecvBuff;
}

void *CXReciver::Entry()
{
	int nDataLen;
	J_DataHead dataHead;
	while (m_bRun)
	{
		memset(&dataHead, 0, sizeof(J_DataHead));
		m_sock.Read(&dataHead, sizeof(J_DataHead));
		if (memcmp(dataHead.start_code, "JOAV", 4) == 0)
		{
			nDataLen = 0;
			nDataLen = ntohs(dataHead.data_len);
			if (nDataLen > 0)
			{
				m_sock.Read(m_pRecvBuff, nDataLen);
				if (m_sock.LastError() == wxSOCKET_NOERROR && m_pDecoder != NULL)
				{
					m_pDecoder->InputData(m_pRecvBuff, nDataLen);
				}
			}
		}
	}
	return NULL;
}

void CXReciver::OnExit()
{
	m_sock.Close();
	fprintf(stderr, "OnExit()\n");
}

int CXReciver::Connect(const char *pAddr, int nPort)
{
	m_bRun = true;
	wxIPV4address addr;
    addr.Hostname(wxString::FromUTF8(pAddr));
    addr.Service(nPort);
	if (!m_sock.Connect(addr))
		return -1;
		
	return 0;
}

void CXReciver::Disconnect()
{
	m_bRun = false;
}

int CXReciver::StartView(const char *pResid, int nStreamType)
{
	char write_buff[1024] = {0};
	MakeHeader(write_buff, NULL, JO_OPEN_STREAM, jo_intact_pack, 0, sizeof(J_RealViewData));
	J_RealViewData *pRealViewData = (J_RealViewData *)(write_buff + sizeof(J_CtrlHead));
	memcpy(pRealViewData->res_id, pResid, strlen(pResid));
	pRealViewData->stream_type = nStreamType;
	
	m_sock.Write(write_buff, sizeof(J_CtrlHead) + sizeof(J_RealViewData));
	if (m_sock.LastError() != wxSOCKET_NOERROR)
		return J_SOCKET_ERROR;
		
	J_CtrlHead ctrlHead = {0};
	m_sock.Read(&ctrlHead, sizeof(ctrlHead));
	if (ctrlHead.ret == 0)
	{
		int nExLength = ntohs(ctrlHead.ex_length);
		if (nExLength > 0)
			m_sock.Read(&write_buff, nExLength);
	}
	
	return J_OK;
}

void CXReciver::StopView()
{
	
}

int CXReciver::MakeHeader(char *pBuffer, char *pUserID, unsigned char byCmd, unsigned char byFlag, unsigned short sqNum, unsigned short exLength, unsigned char byRet)
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