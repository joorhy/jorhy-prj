#ifndef __JOADAPTER_H_
#define __JOADAPTER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"

class CJoAdapterBase : public J_DevAdapter
{};

class CJoAdapter : J_BaseAdapter<CJoAdapterBase>
{
	friend class CJoChannel;
    public:
        CJoAdapter(int nDvrId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword);
        ~CJoAdapter();

        static int Maker(J_Obj *&pObj, int nDrvId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
        {
            pObj = new CJoAdapter(nDrvId, pAddr, nPort, pUsername, pPassword);
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
        J_DevStatus m_status;
        char m_remoteIP[16];
        int  m_remotePort;
        char m_username[64];
        char m_password[64];
};

#endif //~__JOADAPTER_H_
