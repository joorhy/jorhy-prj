#include "x_reciver.h"
#include "x_errtype.h"
#include "j_type.h"
#include "x_decoder.h"
#include <arpa/inet.h>

enum
{
  // id for socket
  SOCKET_ID = 1001
};

BEGIN_EVENT_TABLE(CXReciver, wxEvtHandler)
  EVT_SOCKET(SOCKET_ID, CXReciver::OnSocketEvent)
END_EVENT_TABLE()

CXReciver::CXReciver(CXDecoder *decoder)
{
	m_bRun = false;
	m_pDecoder = decoder;
	m_pRecvBuff = new char[1024 * 1024];
	
	m_sock = new wxSocketClient();
	m_sock->SetEventHandler(*this, SOCKET_ID);
	m_sock->SetNotify(wxSOCKET_CONNECTION_FLAG |
                     wxSOCKET_INPUT_FLAG |
					 //wxSOCKET_OUTPUT_FLAG |
                     wxSOCKET_LOST_FLAG);
	//m_sock->SetFlags(wxSOCKET_WAITALL);
}

CXReciver::~CXReciver()
{
	if (m_pRecvBuff)
		delete m_pRecvBuff;
	
	delete m_sock;
}

void CXReciver::OnSocketEvent(wxSocketEvent& event)
{
	int x = sizeof(J_DataHead);
	int nDataLen;
	J_DataHead dataHead;
	switch(event.GetSocketEvent())
	{
	case wxSOCKET_INPUT: 
		memset(&dataHead, 0, sizeof(J_DataHead));
		m_sock->Read(&dataHead, sizeof(J_DataHead));
		if (memcmp(dataHead.start_code, "JOAV", 4) == 0)
		{
			nDataLen = 0;
			nDataLen = ntohs(dataHead.data_len);
			//fprintf(stderr, "recive_len = %d\n", nDataLen);
			if (nDataLen > 0)
			{
				m_sock->Read(m_pRecvBuff, nDataLen);
				static FILE *fp = NULL;
				if (fp == NULL)
					fp = fopen("test.h264", "wb+");
				fwrite (m_pRecvBuff, 1, nDataLen, fp);
				m_pDecoder->InputData(m_pRecvBuff, nDataLen);
			}
		}
		break;
	case wxSOCKET_LOST: 
		fprintf(stderr, ("wxSOCKET_LOST\n"));
		break;
	case wxSOCKET_CONNECTION: 
		fprintf(stderr, ("wxSOCKET_CONNECTION\n"));
		break;
	default: 
		fprintf(stderr, ("Unexpected event !\n"));
		break;
	}
}

int CXReciver::Connect(const char *pAddr, int nPort)
{
	m_bRun = true;
	wxIPV4address addr;
    addr.Hostname(wxString::FromUTF8(pAddr));
    addr.Service(nPort);

	m_sock->Connect(addr, false);
	m_sock->WaitOnConnect(3);
	
	//m_sock.SetTimeout(1);
	//m_sock.SetFlags(wxSOCKET_NOWAIT);
		
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
	
	m_sock->Write(write_buff, sizeof(J_CtrlHead) + sizeof(J_RealViewData));
	//if (m_sock->LastError() != wxSOCKET_NOERROR)
	//	return J_SOCKET_ERROR;
		
	J_CtrlHead ctrlHead = {0};
	m_sock->Read(&ctrlHead, sizeof(ctrlHead));
	if (ctrlHead.ret == 0)
	{
		int nExLength = ntohs(ctrlHead.ex_length);
		if (nExLength > 0)
			m_sock->Read(&write_buff, nExLength);
			
		m_sock->Notify(true);
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