#include "SamsungAdapter.h"
#include "SamsungChannel.h"

CSamsungAdapter::CSamsungAdapter(int nDvrId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
{
    memset(m_remoteIP, 0, sizeof(m_remoteIP));
    memset(m_username, 0, sizeof(m_username));
    memset(m_password, 0, sizeof(m_password));

    m_remotePort = nPort;
    strcpy(m_remoteIP, pAddr);
    strcpy(m_username, pUsername);
    strcpy(m_password, pPassword);

    m_status = J_DevBroken;
    //定时检测设备状态
    UserExchange();
    m_timer.Create(5 * 1000, CSamsungAdapter::OnTimer, this);

    J_OS::LOGINFO("CSamsungAdapter::CSamsungAdapter(ip = %s, port = %d)", pAddr, nPort);
}

CSamsungAdapter::~CSamsungAdapter()
{
    m_timer.Destroy();
}

J_DevStatus CSamsungAdapter::GetStatus() const
{
    return J_DevReady;
}

int CSamsungAdapter::Broken()
{
    return J_OK;
}

int CSamsungAdapter::MakeChannel(const char *pResid, void *&pObj, void *pOwner, int nChannel, int nStream, int nMode)
{
    CSamsungChannel *pChannel = new CSamsungChannel(pResid, pOwner, nChannel, nStream,
            nMode);
    if (NULL == pChannel)
        return J_MEMORY_ERROR;

    pObj = pChannel;

    return J_OK;
}

int CSamsungAdapter::EnableAlarm()
{
    return J_OK;
}

int CSamsungAdapter::DisableAlarm()
{
    return J_OK;
}

int CSamsungAdapter::EventAlarm(int nDvrId, int nChannel, int nAlarmType)
{
    return J_OK;
}

int CSamsungAdapter::Login()
{
    if (m_status == J_DevReady)
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

    if (m_loginSocket.Write((char*) &login_req, sizeof(SNP_Login_req)) < 0)
        return J_INVALID_DEV;

    SNP_Login_res login_res = {0};
    int nReadLen = sizeof(SNP_Login_res);
    if (m_loginSocket.Read((char*) &login_res, nReadLen) < 0)
        return J_INVALID_DEV;

    if (login_res.continue_data.error == 0)
    {
        m_status = J_DevReady;
        m_controlId = login_res.continue_data.ctrlId;
    }

    return J_OK;
}

void CSamsungAdapter::Logout()
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
    if (m_loginSocket.Write((char*) &stop_req, sizeof(SNP_stop_req)) < 0)
    {
        J_OS::LOGINFO("CSamsungAdapter::Logout() error write");
        //return;
    }
    m_loginSocket.Disconnect();
    m_status = J_DevBroken;
}

int CSamsungAdapter::SendCommand(const char *pCommand, int nLen, int nRespLen)
{
    if (m_loginSocket.GetHandle() == -1)
        return J_SOCKET_ERROR;

    if (m_loginSocket.Write((char*)pCommand, nLen) < 0)
        return J_SOCKET_ERROR;

    char rep_buff[1024] = {0};
    if (m_loginSocket.Read((char*)rep_buff, nRespLen) < 0)
    {
        J_OS::LOGINFO("CSamsungAdapter::SendCommand() error read");
        return J_SOCKET_ERROR;
    }

    return J_OK;
}

void CSamsungAdapter::UserExchange()
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
    if (m_loginSocket.Write((char*) &condition_req, sizeof(SNP_condition_req)) < 0)
    {
        m_loginSocket.Disconnect();
        m_status = J_DevBroken;
        J_OS::LOGINFO("CSamsungAdapter::UserExchange() error write");
        return;
    }

    SNP_condition_rep condition_rep = {0};
    int nReadLen = sizeof(SNP_condition_rep);
    if (m_loginSocket.Read((char*) &condition_rep, nReadLen) < 0)
    {
        m_loginSocket.Disconnect();
        m_status = J_DevBroken;
        J_OS::LOGINFO("CSamsungAdapter::UserExchange() error read");
        return;
    }

    //J_OS::LOGINFO("CSamsungAdapter::UserExchange() End");
}
