#include "jo_sdk.h"
#include "x_errtype.h"

#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define JO_MAX_USER     1024

#include <wx/listimpl.cpp>
WX_DEFINE_LIST(RcdTimeList);

CXSdk::CXSdk()
{

}

CXSdk::~CXSdk()
{

}

int CXSdk::Login(const j_char_t *pAddr, j_int16_t nPort, const j_char_t *pUsername, const j_char_t *pPassword)
{
    //int nRet = sizeof(J_CtrlHead);
    J_CtrlPacket *pCtrlData = (J_CtrlPacket *)new j_char_t[sizeof(J_CtrlHead)+sizeof(J_LoginData)];
    MakeHeader((j_char_t *)pCtrlData, NULL, jo_login_req, jo_intact_pack, 0, sizeof(J_LoginData));
    J_LoginData *loginData = (J_LoginData *)pCtrlData->data;
    memset(pCtrlData->data, 0, sizeof(J_LoginData));
    memcpy(loginData->user_name, pUsername, strlen(pUsername));
    memcpy(loginData->pass_word, pPassword, strlen(pPassword));

    wxSocketClient *pSocket = new wxSocketClient();

    int sdkId = 0;
    wxIPV4address addr;
    addr.Hostname(wxString::FromUTF8(pAddr));
    addr.Service(nPort);
    if (pSocket->Connect(addr))
    {
        pSocket->Write(pCtrlData, sizeof(J_CtrlHead)+sizeof(J_LoginData));
        J_CtrlHead ctrl_head = {0};
        pSocket->Read(&ctrl_head, sizeof(J_CtrlHead));
        if (ctrl_head.ret == 0)
        {
            sdkId = GetIdleUser();
            if (sdkId > 0)
            {
                memcpy(m_usrMap[sdkId].ip_addr, pAddr, strlen(pAddr));
                m_usrMap[sdkId].port = nPort;
                m_usrMap[sdkId].is_active = true;
                memcpy(m_usrMap[sdkId].user_name, pUsername, strlen(pUsername));
                memcpy(m_usrMap[sdkId].pass_word, pPassword, strlen(pPassword));
                memcpy(m_usrMap[sdkId].id.usr_id, ctrl_head.user_id, sizeof(ctrl_head.user_id));
                m_sockMap[sdkId] = pSocket;
            }
        }
    }
    else
    {
        delete pSocket;
    }
    delete pCtrlData;

    return sdkId;
}

void CXSdk::Logout(int nUserID)
{
    if (m_usrMap[nUserID].is_active)
    {
        J_CtrlHead ctrl_head_req = {0};
        MakeHeader((char *)&ctrl_head_req, m_usrMap[nUserID].id.usr_id, jo_logout_req, jo_intact_pack, 0, sizeof(J_LoginData));

        m_sockMap[nUserID]->Write(&ctrl_head_req, sizeof(J_CtrlHead));
        J_CtrlHead ctrl_head_resp = {0};
        m_sockMap[nUserID]->Read(&ctrl_head_resp, sizeof(J_CtrlHead));
        if (ctrl_head_resp.ret == 0)
        {
            memset(&m_usrMap[nUserID], 0, sizeof(J_UserInfo));
            m_sockMap[nUserID]->Close();
            delete m_sockMap[nUserID];
            m_sockMap.erase(nUserID);
            PutIdleUser(nUserID);
        }
    }
}

char *CXSdk::GetResList(int nUserID)
{
    char *xml_data = NULL;
    J_CtrlHead getres_head_req = {0};
    MakeHeader((char *)&getres_head_req, m_usrMap[nUserID].id.usr_id, jo_list_res_req, jo_intact_pack, 0, sizeof(J_LoginData));

    m_sockMap[nUserID]->Write(&getres_head_req, sizeof(J_CtrlHead));
    J_CtrlHead getres_head_resp = {0};
    m_sockMap[nUserID]->Read(&getres_head_resp, sizeof(getres_head_resp));

    if (getres_head_resp.ret == 0)
    {
        if (getres_head_resp.flag == 0)
        {
            int nDataLen = ntohs(getres_head_resp.ex_length);
            xml_data = new char[nDataLen + 1];
            m_sockMap[nUserID]->Read(xml_data, nDataLen);
            xml_data[nDataLen] = '\0';
            return xml_data;
        }
    }
    return NULL;
}

int CXSdk::OpenStream(int nUserID, const char *pResid)
{
    return 0;
}

void CXSdk::CloseStream(int nUserID, int nStreamID)
{

}

int CXSdk::PtzControl(int nUserID, const char *pResid, int nCmd, int nParam)
{
    if (m_usrMap[nUserID].is_active)
    {
        J_CtrlPacket *pCtrlData = (J_CtrlPacket *)new char[sizeof(J_CtrlHead) + sizeof(J_PTZCtlData)];
        MakeHeader((char *)pCtrlData, m_usrMap[nUserID].id.usr_id, jo_ptz_control_req, jo_intact_pack, 0, sizeof(J_PTZCtlData));
        J_PTZCtlData *ptzCtrlData = (J_PTZCtlData *)pCtrlData->data;
        memset(pCtrlData->data, 0, sizeof(J_PTZCtlData));

        memcpy(ptzCtrlData->res_id, pResid, strlen(pResid));
        ptzCtrlData->command = nCmd;
        ptzCtrlData->param = nParam;

        m_sockMap[nUserID]->Write(pCtrlData, sizeof(J_CtrlHead) + sizeof(J_PTZCtlData));
        J_CtrlHead ctrl_head_resp = {0};
        m_sockMap[nUserID]->Read(&ctrl_head_resp, sizeof(J_CtrlHead));
        if (ctrl_head_resp.ret != 0)
        {
            //错误处理
        }
    }
    return 0;
}
j_result_t CXSdk::SearchRecord(j_int32_t nUserID, const j_char_t *pResid, j_time_t begin, j_time_t end, RcdTimeList &timeList)
{
	if (m_usrMap[nUserID].is_active)
    {
        J_CtrlPacket *pCtrlData = (J_CtrlPacket *)new char[sizeof(J_CtrlHead) + sizeof(J_RecordData)];
        MakeHeader((char *)pCtrlData, m_usrMap[nUserID].id.usr_id, jo_rcd_search_req, jo_intact_pack, 0, sizeof(J_RecordData));
        J_RecordData *rcdCtrlData = (J_RecordData *)pCtrlData->data;
		memset(pCtrlData->data, 0, sizeof(J_RecordData));

        memcpy(rcdCtrlData->res_id, pResid, strlen(pResid));
        rcdCtrlData->begin_time = begin;
        rcdCtrlData->end_time = end;

        m_sockMap[nUserID]->Write(pCtrlData, sizeof(J_CtrlHead) + sizeof(J_RecordData));
        J_CtrlHead ctrl_head_resp = {0};
        m_sockMap[nUserID]->Read(&ctrl_head_resp, sizeof(J_CtrlHead));
        if (ctrl_head_resp.ret == 0)
        {
			//数据解析
			int nTotleLen = ctrl_head_resp.ex_length;
			RcdTimeInfo *pInfo = NULL;
			pInfo = (RcdTimeInfo *)new char[nTotleLen];
			m_sockMap[nUserID]->Read(pInfo, nTotleLen);
			while (nTotleLen > 0)
			{
				timeList.push_back(pInfo);
				++pInfo;
				nTotleLen -= sizeof(RcdTimeInfo);
			}
        }
    }
	return 0;
}

int CXSdk::Init()
{
    for(int i=1; i<=JO_MAX_USER; i++)
    {
        J_UserInfo info = {0};
        m_usrMap[i] = info;
    }
    return J_OK;
}

void CXSdk::Deinit()
{
    for(int i=1; i<=JO_MAX_USER; i++)
    {
        Logout(i);
    }
    m_usrMap.clear();
}

int CXSdk::GetIdleUser()
{
    for(int i=1; i<=JO_MAX_USER; i++)
    {
        if (!m_usrMap[i].is_active)
        {
            m_usrMap[i].is_active = true;
            return i;
        }
    }

    return 0;
}

void CXSdk::PutIdleUser(int nUser)
{
    for(int i=1; i<=JO_MAX_USER; i++)
    {
        if (i == nUser)
        {
            m_usrMap[i].is_active = false;
            return;
        }
    }
}

int CXSdk::MakeHeader(char *pBuffer, char *pUserID, unsigned char byCmd, unsigned char byFlag, unsigned short sqNum, unsigned short exLength, unsigned char byRet)
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
