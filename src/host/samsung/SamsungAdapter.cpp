#include "SamsungAdapter.h"
#include "SamsungChannel.h"

JO_IMPLEMENT_INTERFACE(Adapter, "samsung", CSamsungAdapter::Maker)

CSamsungAdapter::CSamsungAdapter(j_int32_t nDvrId, const j_char_t *pAddr, j_int32_t nPort, const j_char_t *pUsername, const j_char_t *pPassword)
{
    memset(m_remoteIP, 0, sizeof(m_remoteIP));
    memset(m_username, 0, sizeof(m_username));
    memset(m_password, 0, sizeof(m_password));

    m_remotePort = nPort;
    strcpy(m_remoteIP, pAddr);
    strcpy(m_username, pUsername);
    strcpy(m_password, pPassword);

    m_status = jo_dev_broken;
    //定时检测设备状态
    UserExchange();
    m_timer.Create(3 * 1000, CSamsungAdapter::OnTimer, this);

    J_OS::LOGINFO("CSamsungAdapter::CSamsungAdapter(ip = %s, port = %d)", pAddr, nPort);
}

CSamsungAdapter::~CSamsungAdapter()
{
    m_timer.Destroy();
}

J_DevStatus CSamsungAdapter::GetStatus() const
{
    return jo_dev_ready;
}

j_result_t CSamsungAdapter::Broken()
{
    return J_OK;
}

j_result_t CSamsungAdapter::MakeChannel(const j_char_t *pResid, J_Obj *&pObj, J_Obj *pOwner, j_int32_t nChannel, j_int32_t nStream, j_int32_t nMode)
{
    CSamsungChannel *pChannel = new CSamsungChannel(pResid, pOwner, nChannel, nStream,
            nMode);
    if (NULL == pChannel)
        return J_MEMORY_ERROR;

    pObj = pChannel;

    return J_OK;
}

j_result_t CSamsungAdapter::EnableAlarm()
{
    return J_OK;
}

j_result_t CSamsungAdapter::DisableAlarm()
{
    return J_OK;
}

j_result_t CSamsungAdapter::EventAlarm(j_int32_t nDvrId, j_int32_t nChannel, j_int32_t nAlarmType)
{
    return J_OK;
}

j_result_t CSamsungAdapter::Login()
{
    if (m_status == jo_dev_ready)
        return J_OK;

    if (m_loginSocket.Connect(m_remoteIP, m_remotePort) != J_OK)
        return J_INVALID_DEV;

    SNP_Login_req login_req = {0};
    memcpy(login_req.packet_header.start_code, "SDVR",  4);
    login_req.packet_header.ex_channel =  0x00;
    login_req.packet_header.pkt_version = 0x20;
    login_req.packet_header.pkt_size =  0x0C;
    login_req.packet_header.control =  0x11;
    login_req.packet_header.payload =  0x71;
    login_req.packet_header.seq = 0x00;
    login_req.packet_header.ctrlId = 0x00;
    login_req.continue_header.ch =  0x14;
    login_req.continue_header.cs = 0x00;
    login_req.continue_data.ctrlId = 0x00;
    login_req.continue_data.type = 0x01;
    memcpy(login_req.continue_data.pass_word, m_password, strlen(m_password));
    memcpy(login_req.continue_data.user_name, m_username, strlen(m_username));

    if (m_loginSocket.Write((j_char_t*) &login_req, sizeof(SNP_Login_req)) < 0)
        return J_INVALID_DEV;

    SNP_Login_res login_res = {0};
    int nReadLen = sizeof(SNP_Login_res);
    if (m_loginSocket.Read((j_char_t*) &login_res, nReadLen) < 0)
        return J_INVALID_DEV;

    if (login_res.continue_data.error == 0)
    {
        m_status = jo_dev_ready;
        m_controlId = login_res.continue_data.ctrlId;
    }

    return J_OK;
}

j_void_t CSamsungAdapter::Logout()
{
    SNP_stop_req stop_req = {0};
    memcpy(stop_req.packet_header.start_code, "SDVR",  4);
    stop_req.packet_header.ex_channel =  0x00;
    stop_req.packet_header.pkt_version = 0x10;
    stop_req.packet_header.pkt_size =  0x0C;
    stop_req.packet_header.control =  0x19;
    stop_req.packet_header.payload =  0x75;
    stop_req.packet_header.seq = 0x00;
    stop_req.packet_header.ctrlId = m_controlId;
    stop_req.continue_header.ch =  0x0a;
    stop_req.continue_header.cs = 0x00;
    stop_req.data[0] = 0xFF;
    stop_req.data[1] = 0xFF;
    if (m_loginSocket.Write((j_char_t*) &stop_req, sizeof(SNP_stop_req)) < 0)
    {
        J_OS::LOGINFO("CSamsungAdapter::Logout() error write");
        //return;
    }
    m_loginSocket.Disconnect();
    m_status = jo_dev_broken;
}

j_result_t CSamsungAdapter::SendCommand(const j_char_t *pCommand, j_int32_t nLen, j_int32_t nRespLen)
{
    if (m_loginSocket.GetHandle().sock == j_invalid_socket_val)
        return J_SOCKET_ERROR;

    if (m_loginSocket.Write((j_char_t*)pCommand, nLen) < 0)
        return J_SOCKET_ERROR;

    j_char_t rep_buff[1024] = {0};
    if (m_loginSocket.Read((j_char_t*)rep_buff, nRespLen) < 0)
    {
        J_OS::LOGINFO("CSamsungAdapter::SendCommand() error read");
        return J_SOCKET_ERROR;
    }

    return J_OK;
}

j_void_t CSamsungAdapter::UserExchange()
{
    if (Login() != J_OK)
        return;

    SNP_condition_req condition_req = {0};
    memcpy(condition_req.packet_header.start_code, "SDVR",  4);
    condition_req.packet_header.ex_channel =  0x00;
    condition_req.packet_header.pkt_version = 0x10;
    condition_req.packet_header.pkt_size =  0x0C;
    condition_req.packet_header.control =  0x19;
    condition_req.packet_header.payload =  0x7D;
    condition_req.packet_header.seq = 0x00;
    condition_req.packet_header.ctrlId = m_controlId;
    condition_req.continue_header.ch =  0x0a;
    condition_req.continue_header.cs = 0x00;

    //J_OS::LOGINFO("CSamsungAdapter::UserExchange() Begin");
    if (m_loginSocket.Write((j_char_t*) &condition_req, sizeof(SNP_condition_req)) < 0)
    {
        m_loginSocket.Disconnect();
        m_status = jo_dev_broken;
        J_OS::LOGINFO("CSamsungAdapter::UserExchange() error write");
        return;
    }

    SNP_condition_rep condition_rep = {0};
    j_int32_t nReadLen = sizeof(SNP_condition_rep);
    if (m_loginSocket.Read((j_char_t*) &condition_rep, nReadLen) < 0)
    {
        m_loginSocket.Disconnect();
        m_status = jo_dev_broken;
        J_OS::LOGINFO("CSamsungAdapter::UserExchange() error read");
        return;
    }

    //J_OS::LOGINFO("CSamsungAdapter::UserExchange() End");
}
