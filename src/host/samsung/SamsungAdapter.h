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
    CSamsungAdapter(int nDvrId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword);
    ~CSamsungAdapter();

    static int Maker(J_Obj *&pObj, int nDrvId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
    {
        pObj = new CSamsungAdapter(nDrvId, pAddr, nPort, pUsername, pPassword);
        return J_OK;
    }

public:
    ///J_VideoAdapter
    virtual J_DevStatus GetStatus() const;
    virtual int Broken();
    virtual int MakeChannel(const char *pResid, void *&pObj, void *pOwner, int nChannel, int nStream, int nMode);
    ///J_AlarmAdapter
    virtual int EnableAlarm();
    virtual int DisableAlarm();
    virtual int EventAlarm(int nDvrId, int nChannel, int nAlarmType);

protected:
    char *GetRemoteIp() const
    {
        return (char *)m_remoteIP;
    }
    int GetRemotePort() const
    {
        return m_remotePort;
    }
    char *GetUser() const
    {
        return (char *)m_username;
    }
    char *GetPassword() const
    {
        return (char *)m_password;
    }
    u_char GetCtrlId() const
    {
        return m_controlId;
    }

    int Login();
    void Logout();
    int SendCommand(const char *pCommand, int nLen, int nRespLen);

private:
    static void OnTimer(void *pUser)
    {
        (static_cast<CSamsungAdapter *>(pUser))->UserExchange();
    }
    void UserExchange();

private:
    J_DevStatus m_status;
    char m_remoteIP[16];
    int  m_remotePort;
    char m_username[64];
    char m_password[64];

    u_char m_controlId;
    J_OS::CTimer m_timer;
    J_OS::CTCPSocket m_loginSocket;
};

ADAPTER_BEGIN_MAKER(samsung)
ADAPTER_ENTER_MAKER("samsung", CSamsungAdapter::Maker)
ADAPTER_END_MAKER()

#endif //~__SAMSUNGADAPTER_H_
