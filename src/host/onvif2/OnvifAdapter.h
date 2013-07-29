#ifndef __ONVIFADAPTER_H_
#define __ONVIFADAPTER_H_
#include "j_includes.h"
#include "x_module_manager_def.h"

//Lyc
#include "Onvif/OnvifPTZ.h"

class COnvifAdapterBase : public J_DevAdapter
{};

class COnvifAdapter : public J_BaseAdapter<COnvifAdapterBase>
{
	friend class COnvifChannel;
    public:
        COnvifAdapter(int nDvrId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword);
        ~COnvifAdapter();

        static int Maker(J_Obj *&pObj, int nDrvId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
        {
            pObj = new COnvifAdapter(nDrvId, pAddr, nPort, pUsername, pPassword);
            return J_OK;
        }

    public:
        ///J_VideoAdapter
        virtual J_DevStatus GetStatus() const;
        virtual int Broken();
        virtual int MakeChannel(const char *pResid, J_Obj *&pObj, J_Obj *pOwner, int nChannel, int nStream, int nMode);

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

	//Lyc
	public:
		/** Onvif设备控制 */
		COnvifPTZ m_OnvifPtz;

		/** RTSP视频流地址 */
		string m_RtspUrl;		

	//Lyc
	public:
		/**
		*  @author      雷银春(yo7@foxmail.com)
		*  @date        2013/07/22 14:21
		*  @brief       初始化Onvif控制器
		*  @param[in]   szIp Onvif目标设备Ip地址
		*  @return      成功返回true，否则为false
		*/
		bool InitOnif(const char * szIp)
		{
			if (!m_OnvifPtz.InitCore(szIp))
				return false;
			if (!m_OnvifPtz.GetMediaProfile())
				return false;
			m_OnvifPtz.GetRtspUrl(m_RtspUrl);
			m_OnvifPtz.InitPTZ();

			return true;
		}
};
#endif //~__ONVIFADAPTER_H_
