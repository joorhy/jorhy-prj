#include "JospParser.h"
#include "x_md5.h"

#include "x_socket.h"

CJospParser::CJospParser()
{
	m_state = JOSP_HEAD;
	J_OS::LOGINFO("CJospParser::CJospParser()");
}

CJospParser::~CJospParser()
{
	J_OS::LOGINFO("CJospParser::~CJospParser()");
}

int CJospParser::AddUser(j_socket_t nSocket, const char *pAddr, short nPort)
{
	J_NetWorkInfo info = {0};
    memcpy(info.ip_addr, pAddr, strlen(pAddr));
    info.port = nPort;
    m_networkMap[nSocket] = info;
	return J_OK;
}

int CJospParser::ProcessRequest(J_AsioDataBase *pAsioData_in, J_AsioDataBase *pAsioData_out)
{
	if (m_state == JOSP_HEAD)
	{
		m_command = pAsioData_in->ioRead.buf[5] & 0xFF;
		pAsioData_in->ioRead.buf = pAsioData_in->ioRead.buf + sizeof(J_CtrlHead);
		pAsioData_in->ioRead.whole = true;
		switch(m_command)
		{
			case jo_login_req:
				pAsioData_in->ioRead.bufLen = sizeof(J_LoginData);
				break;
			case jo_logout_req: case jo_list_res_req:
				m_state = JOSP_DATA;
				goto parser_command;
			case jo_ptz_control_req:
				pAsioData_in->ioRead.bufLen = sizeof(J_PTZCtlData);
				break;
			case jo_rcd_search_req:
				pAsioData_in->ioRead.bufLen = sizeof(J_RecordData);
				break;
			default:
				fprintf(stderr, "CJospParser::ProcessRequest Unknow type = %d\n", m_command);
				break;
		}
		m_state = JOSP_DATA;
		return J_NOT_COMPLATE;
	}

parser_command:
    int nRet = J_OK;
	if (m_state == JOSP_DATA)
	{
		j_char_t *read_buff = pAsioData_in->ioRead.buf + sizeof(J_CtrlHead);
		switch(m_command)
		{
			case jo_login_req:
				nRet = OnLogin(pAsioData_in->ioHandle, read_buff, pAsioData_out);
				break;
			case jo_logout_req:
				nRet = OnLogout(read_buff, pAsioData_out);
				break;
			case jo_list_res_req:
				nRet = OnGetResList(read_buff, pAsioData_out);
				break;
			case jo_ptz_control_req:
				nRet = OnPtzControl(read_buff, pAsioData_out);
				break;
			case jo_rcd_search_req:
				nRet = OnRcdSearch(read_buff, pAsioData_out);
				break;
			default:
				fprintf(stderr, "CJospParser::ProcessRequest Unknow type = %d\n", read_buff[5]);
				break;
		}		
	}

    return nRet;
}

int CJospParser::DelUser(j_socket_t nSocket)
{
	J_NetWorkInfo netInfo = m_networkMap[nSocket];
    std::map<std::string, J_UserInfo>::iterator it = m_userMap.begin();
    for (; it!=m_userMap.end(); it++)
    {
        if (it->second.port == netInfo.port
            && memcpy(it->second.ip_addr, netInfo.ip_addr, strlen(netInfo.ip_addr)) == 0)
        {
            m_userMap.erase(it);
            break;
        }
    }
	m_networkMap.erase(nSocket);
	
    return J_OK;
}

int CJospParser::OnLogin(j_socket_t nSocket, const char *pRequest, J_AsioDataBase *pAsioData_out)
{
    J_CtrlPacket *ctrlHead = (J_CtrlPacket *)pRequest;
    J_LoginData *loninData = (J_LoginData *)(ctrlHead->data);
	j_char_t *pResponse = NULL;
    if (m_ivsManager.CheckUser(loninData->user_name, loninData->pass_word))
    {
        j_uuid_t userId;
        //uuid_generate(userId);
        MD5_CTX context;
        MD5Init(&context);
        MD5Update(&context, userId, sizeof(j_uuid_t));
        unsigned char md5[16];
        MD5Final(md5, &context);
        char userId_md5[33] = {0};
        for(int i=0; i<16; i++)
        {
            sprintf(&userId_md5[2*i], "%x", (md5[i] >> 4) & 0x0F);
            sprintf(&userId_md5[2*i+1], "%x", md5[i] & 0x0F);
        }
        //fprintf(stderr, "CJospHelper::OnLogin %s", userId_md5);
		pResponse = new char[sizeof(J_CtrlHead)];
        MakeHeader(pResponse, (char *)userId_md5, jo_login_rep, jo_intact_pack, 0, 0, J_OK);

		J_NetWorkInfo netInfo = m_networkMap[nSocket];
        J_UserInfo info = {0};
        memcpy(info.ip_addr, netInfo.ip_addr, strlen(netInfo.ip_addr));
        info.port = netInfo.port;
        memcpy(info.user_name, loninData->user_name, strlen(loninData->user_name));
        memcpy(info.pass_word, loninData->pass_word, strlen(loninData->pass_word));
        info.is_active = true;

        m_userMap[userId_md5] = info;
    }
    else
    {
        MakeHeader(pResponse, NULL, jo_login_rep, jo_intact_pack, 0, 0, 1);
    }
	pAsioData_out->ioWrite.buf = pResponse;
    pAsioData_out->ioWrite.bufLen = sizeof(J_CtrlHead);
	pAsioData_out->ioWrite.whole = true;

    return J_OK;
}

int CJospParser::OnLogout(const char *pRequest, J_AsioDataBase *pAsioData_out)
{
    J_CtrlHead *ctrlHead = (J_CtrlHead *)pRequest;
	j_char_t *pResponse = new char[sizeof(J_CtrlHead)];
    if (m_userMap.find((const char *)ctrlHead->user_id) != m_userMap.end())
    {
        MakeHeader(pResponse, (char *)ctrlHead->user_id, jo_logout_rep, jo_intact_pack, 0, 0, J_OK);
        m_userMap.erase((const char *)ctrlHead->user_id);
    }
    else
    {
        MakeHeader(pResponse, (char *)ctrlHead->user_id, jo_logout_rep, jo_intact_pack, 0, 0, 1);
    }
	pAsioData_out->ioWrite.buf = pResponse;
    pAsioData_out->ioWrite.bufLen = sizeof(J_CtrlHead);
	pAsioData_out->ioWrite.whole = true;

    return J_OK;
}

int CJospParser::OnGetResList(const char *pRequest, J_AsioDataBase *pAsioData_out)
{
    j_int32_t nRespLen = 0;
	j_char_t *pResponse = NULL;
    J_CtrlHead *resHead = (J_CtrlHead *)pRequest;
    if (m_userMap.find((const char *)resHead->user_id) != m_userMap.end())
    {
        const char *pXmlData = m_ivsManager.GetResList();
        nRespLen = strlen(pXmlData);
		pResponse = new char[sizeof(J_CtrlHead) + nRespLen];
        MakeHeader(pResponse, (char *)resHead->user_id, jo_list_res_rep, jo_intact_pack, 0, nRespLen, J_OK);
        memcpy(pResponse + sizeof(J_CtrlHead), pXmlData, nRespLen);
    }
    else
    {
		pResponse = new char[sizeof(J_CtrlHead)];
        MakeHeader(pResponse, (char *)resHead->user_id, jo_list_res_rep, jo_intact_pack, 0, 0, 1);
    }
    nRespLen += sizeof(J_CtrlHead);
	
	pAsioData_out->ioWrite.buf = pResponse;
    pAsioData_out->ioWrite.bufLen = nRespLen;
	pAsioData_out->ioWrite.whole = true;
    return J_OK;
}

int CJospParser::OnPtzControl(const char *pRequest, J_AsioDataBase *pAsioData_out)
{
    int nRet = J_OK;
	j_char_t *pResponse = new char[sizeof(J_CtrlHead)];
    J_CtrlPacket *ctrlHead = (J_CtrlPacket *)pRequest;
    J_PTZCtlData *ptzCtrlData = (J_PTZCtlData *)(ctrlHead->data);
    if (m_userMap.find((const char *)ctrlHead->head.user_id) != m_userMap.end())
    {
        nRet = m_deviceControl.PtzControl(ptzCtrlData->res_id, ptzCtrlData->command, ptzCtrlData->param);
        MakeHeader(pResponse, (char *)ctrlHead->head.user_id, jo_ptz_control_rep, jo_intact_pack, 0, 0, J_OK);
    }
    else
    {
        MakeHeader(pResponse, (char *)ctrlHead->head.user_id, jo_ptz_control_rep, jo_intact_pack, 0, 0, 1);
    }
	pAsioData_out->ioWrite.buf = pResponse;
    pAsioData_out->ioWrite.bufLen = sizeof(J_CtrlHead);
	pAsioData_out->ioWrite.whole = true;

    return nRet;
}

int CJospParser::OnRcdSearch(const char *pRequest, J_AsioDataBase *pAsioData_out)
{
	j_result_t nRet = J_OK;
	j_int32_t nRespLen = 0;
	j_char_t *pResponse = new char[100 *1024];
	
	J_CtrlPacket *ctrlHead = (J_CtrlPacket *)pRequest;
    J_RecordData *rcdCtrlData = (J_RecordData *)(ctrlHead->data);
    if (m_userMap.find((const char *)ctrlHead->head.user_id) != m_userMap.end())
    {
		nRespLen =  m_ivsManager.GetRcdList(rcdCtrlData->res_id, rcdCtrlData->begin_time,
			rcdCtrlData->end_time, pResponse + sizeof(J_CtrlHead));
		MakeHeader(pResponse, (char *)ctrlHead->head.user_id, jo_rcd_search_rep, jo_intact_pack, 0, nRespLen, J_OK);
    }
    else
    {
        MakeHeader(pResponse, (char *)ctrlHead->head.user_id, jo_rcd_search_rep, jo_intact_pack, 0, 0, 1);
    }
	nRespLen += sizeof(J_CtrlHead);
	
	pAsioData_out->ioWrite.buf = pResponse;
    pAsioData_out->ioWrite.bufLen = nRespLen;
	pAsioData_out->ioWrite.whole = true;
	
	return nRet;
}

int CJospParser::MakeHeader(char *pBuffer, char *pUserID, unsigned char byCmd, unsigned char byFlag, unsigned short sqNum, unsigned short exLength, unsigned char byRet)
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
