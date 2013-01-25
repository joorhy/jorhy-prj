#ifndef __X_PLAYER_H_
#define __X_PLAYER_H_

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <string>
#include <wx/timer.h>
#include "j_type.h"

struct XWindowInfo
{
	uint32_t mode;
    uint32_t xid;
    uint32_t w;
    uint32_t h;
	time_t start;
	time_t end;
};

class CXReciver;
class CXDecoder;
class CXRender;
class CXPlayer : public wxEvtHandler
{
    public:
        CXPlayer(const char *pSvrAddr);
        ~CXPlayer();

    public:
        //开始预览
        int Start(const char *pResid, const XWindowInfo &winInfo);
        //停止预览
        int Stop();
	
        //设置窗口比例
        int AspectRatio(int w, int h);
		
		//注册回调函数
		void RegistCallback(void *func, void *pUser);

    private:
        int Init();
        bool IsPlaying();
        virtual bool ProcessEvent(wxEvent& event);

    private:
        std::string m_resid;
        std::string m_svrAddr;
        XWindowInfo m_winInfo;
        wxTimer m_timer;
		int m_nMode;
		void *m_cbFunc;
		void *m_pUser;
		CXReciver *m_pReciver;
		CXDecoder *m_pDecoder;
		CXRender *m_pRender;
};

#endif // __X_PLAYER_H_
