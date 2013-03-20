#ifndef __SAMSUNGADAPTER_H_
#define __SAMSUNGADAPTER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
#include "SansungDef.h"
#include "x_timer.h"
#include "x_socket.h"

class CSamsungAdapterBase : public J_DevAdapter
    , public J_DevInput
{};

class CSamsungAdapter : J_BaseAdapter<CSamsungAdapterBase>
{
    friend class CSamsungChannel;
public:
    CSamsungAdapter(j_int32_t nDvrId, const j_char_t *pAddr, j_int32_t nPort, const j_char_t *pUsername, const j_char_t *pPassword);
    ~CSamsungAdapter();

    static int Maker(J_Obj *&pObj, j_int32_t nDrvId, const j_char_t *pAddr, j_int32_t nPort, const j_char_t *pUsername, const j_char_t *pPassword)
    {
        pObj = new CSamsungAdapter(nDrvId, pAddr, nPort, pUsername, pPassword);
        return J_OK;
    }

public:
    ///J_VideoAdapter
    virtual J_DevStatus GetStatus() const;
    virtual j_result_t Broken();
    virtual j_result_t MakeChannel(const j_char_t *pResid, j_void_t *&pObj, j_void_t *pOwner, j_int32_t nChannel, j_int32_t nStream, j_int32_t nMode);
    ///J_AlarmAdapter
    virtual j_result_t EnableAlarm();
    virtual j_result_t DisableAlarm();
    virtual j_result_t EventAlarm(j_int32_t nDvrId, j_int32_t nChannel, j_int32_t nAlarmType);

protected:
    j_char_t *GetRemoteIp() const
    {
        return (j_char_t *)m_remoteIP;
    }
    j_int32_t GetRemotePort() const
    {
        return m_remotePort;
    }
    j_char_t *GetUser() const
    {
        return (j_char_t *)m_username;
    }
    j_char_t *GetPassword() const
    {
        return (j_char_t *)m_password;
    }
    j_uint8_t GetCtrlId() const
    {
        return m_controlId;
    }

    j_int32_t Login();
    j_void_t Logout();
    j_int32_t SendCommand(const j_char_t *pCommand, j_int32_t nLen, j_int32_t nRespLen);

private:
    static void OnTimer(void *pUser)
    {
        (static_cast<CSamsungAdapter *>(pUser))->UserExchange();
    }
    void UserExchange();

private:
    J_DevStatus m_status;
    j_char_t m_remoteIP[16];
    j_int32_t  m_remotePort;
    j_char_t m_username[64];
    j_char_t m_password[64];

    j_uint8_t m_controlId;
    J_OS::CTimer m_timer;
    J_OS::CTCPSocket m_loginSocket;
};

ADAPTER_BEGIN_MAKER(samsung)
ADAPTER_ENTER_MAKER("samsung", CSamsungAdapter::Maker)
ADAPTER_END_MAKER()

#endif //~__SAMSUNGADAPTER_H_
