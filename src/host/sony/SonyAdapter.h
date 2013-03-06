#ifndef __SONYADAPTER_H_
#define __SONYADAPTER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
#include "x_ping.h"

class CSonyAdapterBase : public J_DevAdapter
{};

class CSonyAdapter : J_BaseAdapter<CSonyAdapterBase>
{
	friend class CSonyChannel;
    public:
        CSonyAdapter(int nDvrId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword);
        ~CSonyAdapter();

        static int Maker(J_Obj *&pObj, int nDrvId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
        {
            pObj = new CSonyAdapter(nDrvId, pAddr, nPort, pUsername, pPassword);
            return J_OK;
        }

    public:
        ///J_VideoAdapter
        virtual J_DevStatus GetStatus() const;
        virtual int Broken();
        virtual int MakeChannel(const char *pResid, void *&pObj, void *pOwner, int nChannel, int nStream, int nMode);

    protected:
        char *GetRemoteIp() const { return (char *)m_remoteIP; }
        int GetRemotePort() const { return m_remotePort; }
        char *GetUser() const { return (char *)m_username; }
        char *GetPassword() const { return (char *)m_password; }

    private:
    	static void OnTimer(void *pUser)
        {
            (static_cast<CSonyAdapter *>(pUser))->UserExchange();
        }
        void UserExchange();

    private:
        J_DevStatus m_status;
        J_OS::CTimer m_timer;
        char m_remoteIP[16];
        int  m_remotePort;
        char m_username[64];
        char m_password[64];
        CXPing m_ping;
};

ADAPTER_BEGIN_MAKER(sony)
	ADAPTER_ENTER_MAKER("sony", CSonyAdapter::Maker)
ADAPTER_END_MAKER()

#endif //~__SONYADAPTER_H_
