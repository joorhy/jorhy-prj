#ifndef __JO_SDK_H_
#define __JO_SDK_H_

#include "j_type.h"
#include <map>
#include <wx/socket.h>

#include <wx/list.h>
struct RcdTimeInfo
{
	time_t begin_time;
	time_t end_time;
};
WX_DECLARE_LIST(RcdTimeInfo, RcdTimeList);

typedef void (*PlayerCallbackFunc)(void *pUser);

class CXSdk
{
    public:
        CXSdk();
        ~CXSdk();

    public:
        int Login(const char *pAddr, short nPort, const char *pUsername, const char *pPassword);
        void Logout(int nUserID);
        char *GetResList(int nUserID);         //返回XML信息,需要手动释放
        int OpenStream(int nUserID, const char *pResid);
        void CloseStream(int nUserID, int nStreamID);
        int PtzControl(int nUserID, const char *pResid, int nCmd, int nParam = 0);
		int SearchRecord(int nUserID, const char *pResid, time_t begin, time_t end, RcdTimeList &timeList);

    private:
        int Init();
        void Deinit();
        int GetIdleUser();
        void PutIdleUser(int nUser);
        int MakeHeader(char *pBuff, char *pUserID, unsigned char byCmd, unsigned char byFlag, unsigned short sqNum, unsigned short exLength, unsigned char byRet = 0x00);

    private:
        std::map<unsigned int, J_UserInfo> m_usrMap;
        std::map<unsigned int, wxSocketClient *> m_sockMap;
};

#endif // __JO_SDK_H_
