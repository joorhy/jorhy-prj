#include "x_reciver.h"
#include "x_errtype.h"
#include "j_type.h"
#include "x_decoder.h"
#include <arpa/inet.h>

enum
{
  // id for socket
  SOCKET_1 = 1001, 
  SOCKET_2, SOCKET_3, SOCKET_4, SOCKET_5,
  SOCKET_6, SOCKET_7, SOCKET_8, SOCKET_9,
  SOCKET_10, SOCKET_11, SOCKET_12, SOCKET_13,
  SOCKET_14, SOCKET_15, SOCKET_16, SOCKET_17,
  SOCKET_18, SOCKET_19, SOCKET_20, SOCKET_21,
  SOCKET_22, SOCKET_23, SOCKET_24, SOCKET_25
};

BEGIN_EVENT_TABLE(CXReciver, wxEvtHandler)
  EVT_SOCKET(SOCKET_1, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_2, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_3, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_4, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_5, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_6, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_7, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_8, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_9, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_10, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_11, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_12, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_13, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_14, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_15, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_16, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_17, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_18, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_19, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_20, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_21, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_22, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_23, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_24, CXReciver::OnSocketEvent)
  EVT_SOCKET(SOCKET_25, CXReciver::OnSocketEvent)
END_EVENT_TABLE()

SocketId_Info CXReciver::m_idInfo[25] = {
	{SOCKET_1, 1}, {SOCKET_2, 1}, {SOCKET_3, 1}, {SOCKET_4, 1}, {SOCKET_5, 1}, 
	{SOCKET_6, 1}, {SOCKET_7, 1}, {SOCKET_8, 1}, {SOCKET_9, 1}, {SOCKET_10, 1}, 
	{SOCKET_11, 1}, {SOCKET_12, 1}, {SOCKET_13, 1}, {SOCKET_14, 1}, {SOCKET_15, 1}, 
	{SOCKET_16, 1}, {SOCKET_17, 1}, {SOCKET_18, 1}, {SOCKET_19, 1}, {SOCKET_20, 1}, 
	{SOCKET_21, 1}, {SOCKET_22, 1}, {SOCKET_23, 1}, {SOCKET_24, 1}, {SOCKET_25, 1}
};

CXReciver::CXReciver(CXDecoder *decoder)
{
	m_pDecoder = decoder;
	m_pRecvBuff = new char[1024 * 1024];

	m_nSocketId = CXReciver::GetIdleId();
	m_sock = new wxSocketClient(m_nSocketId);
	m_sock->SetEventHandler(*this, m_nSocketId);
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
	CXReciver::SetIdleId(m_nSocketId);
}

void CXReciver::OnSocketEvent(wxSocketEvent& event)
{
	int x = sizeof(J_DataHead);
	int nDataLen = 0;
	int nRecvLen = 0;
	J_DataHead dataHead;
	switch(event.GetSocketEvent())
	{
	case wxSOCKET_INPUT: 
		memset(&dataHead, 0, sizeof(J_DataHead));
		m_sock->Read(&dataHead, sizeof(J_DataHead));
		if (memcmp(dataHead.start_code, "JOAV", 4) == 0)
		{
			nDataLen = 0;
			nDataLen = ntohl(dataHead.data_len);
			//fprintf(stderr, "recive_len = %d\n", nDataLen);
			while (nRecvLen < nDataLen)
			{
				m_sock->Read(m_pRecvBuff + nRecvLen, nDataLen - nRecvLen);
				nRecvLen += m_sock->LastCount();
				//fprintf(stderr, "recive_len = %d last_count = %d\n", nDataLen, m_sock->LastCount());
			}
			m_pDecoder->InputData(m_pRecvBuff, nDataLen);
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
	wxIPV4address addr;
    addr.Hostname(wxString::FromUTF8(pAddr));
    addr.Service(nPort);

	m_sock->Connect(addr, false);
	m_sock->WaitOnConnect(3);
		
	return 0;
}

void CXReciver::Disconnect()
{
	m_sock->Close();
}

int CXReciver::StartView(const char *pResid, int nStreamType)
{
	char write_buff[1024] = {0};
	MakeHeader(write_buff, NULL, jo_open_stream_req, jo_intact_pack, 0, sizeof(J_RealViewData));
	J_RealViewData *pRealViewData = (J_RealViewData *)(write_buff + sizeof(J_CtrlHead));
	memcpy(pRealViewData->res_id, "49"/*pResid*/, 2/*strlen(pResid)*/);
	pRealViewData->stream_type = nStreamType;
	
	m_sock->Write(write_buff, sizeof(J_CtrlHead) + sizeof(J_RealViewData));
		
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