#ifndef __JO_MEDIA_OBJ_H_
#define __JO_MEDIA_OBJ_H_

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/treectrl.h>
#include <string>
#include <map>
#include "x_player.h"

class CMediaObj : public  wxTreeItemData
{
    public:
        CMediaObj(const char *pResid, const char *pSvrAddr);
        ~CMediaObj();

    public:
        int Invoke(wxWindow *pWindow, int nFlag = 1, time_t start = 0, time_t end = 0);
		void RegistCallback(wxWindow *pWindow, void *func, void *pUser);
        wxWindow *Close();
        void ClearAll();
        void UpdatePlayer();
        const char *GetResid() { return m_resid.c_str(); }

    private:
        std::string m_resid;
        std::string m_svrAddr;
        struct PlayerInfo
        {
            CXPlayer *pPlayer;
        };
        typedef std::map<wxWindow *, PlayerInfo> PlayerMap;
        PlayerMap m_playerMap;
};

#endif // __JO_MEDIA_OBJ_H_
