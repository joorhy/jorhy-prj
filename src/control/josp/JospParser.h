#ifndef __JOSPPARSER_H_
#define __JOSPPARSER_H_
#include "j_includes.h"
#include "JoissManager.h"
#include "MCManager.h"
#include "DeviceControl.h"
#include "x_module_manager_def.h"

class CJospParser : public J_CommandParser
{
    public:
        CJospParser();
        ~CJospParser();
		
		static int Maker(J_Obj *&pObj)
		{
			pObj = new CJospParser();
			return J_OK;
		}

	public:
		virtual int AddUser(j_socket_t nSocket, const char *pAddr, short nPort);
		virtual	int ProcessRequest(J_AsioDataBase *pAsioData_in, J_AsioDataBase *pAsioData_out);
		virtual	int DelUser(j_socket_t nSocket);

    private:
        int MakeHeader(char *pBuffer, char *pUserID, unsigned char byCmd, unsigned char byFlag, unsigned short sqNum, unsigned short exLength, unsigned char byRet = 0x00);
        int OnLogin(j_socket_t nSocket, const char *pRequest, J_AsioDataBase *pAsioData_out);
        int OnLogout(const char *pRequest, J_AsioDataBase *pAsioData_out);
        int OnGetResList(const char *pRequest, J_AsioDataBase *pAsioData_out);
        int OnPtzControl(const char *pRequest, J_AsioDataBase *pAsioData_out);
		int OnRcdSearch(const char *pRequest, J_AsioDataBase *pAsioData_out);

private:
		enum
		{
			JOSP_HEAD = 1,
			JOSP_DATA,
		};
        CJoissManager m_ivsManager;
		//CMCManager m_ivsManager;
        CDeviceControl m_deviceControl;
        j_map_user_info_t m_userMap;
		j_map_network_info_t m_networkMap;
		j_int32_t m_state;
		j_int32_t m_command;
};

#endif // __JOSPPARSER_H_
