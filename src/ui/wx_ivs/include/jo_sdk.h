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
        j_result_t Login(const j_char_t *pAddr, j_int16_t nPort, const j_char_t *pUsername, const j_char_t *pPassword);
        j_void_t Logout(j_int32_t nUserID);
        j_char_t *GetResList(j_int32_t nUserID);         //返回XML信息,需要手动释放
        j_result_t OpenStream(j_int32_t nUserID, const j_char_t *pResid);
        j_void_t CloseStream(j_int32_t nUserID, j_int32_t nStreamID);
        j_result_t PtzControl(j_int32_t nUserID, const j_char_t *pResid, j_int32_t nCmd, j_int32_t nParam = 0);
		j_result_t SearchRecord(j_int32_t nUserID, const j_char_t *pResid, j_time_t begin, j_time_t end, RcdTimeList &timeList);

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
