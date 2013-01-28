#include "jo_media_obj.h"
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <gdk/gdkx.h>

CMediaObj::CMediaObj(const char *pResid, const char *pSvrAddr)
{
    m_resid = pResid;
    m_svrAddr = pSvrAddr;
}

CMediaObj::~CMediaObj()
{

}

int CMediaObj::Invoke(wxWindow *pWindow, int nFlag, time_t start, time_t end)
{
    PlayerMap::iterator it = m_playerMap.find(pWindow);
    if (nFlag > 0 && pWindow != NULL)
    {
		
        if (it == m_playerMap.end())
        {
            XWindowInfo info = {0};
            info.window = GTK_WIDGET(pWindow->GetHandle())->window;
            info.w = pWindow->GetParent()->GetSize().GetWidth();
            info.h = pWindow->GetParent()->GetSize().GetHeight();
			//XImage *m_img = XGetImage(GDK_WINDOW_XDISPLAY(GTK_WIDGET(pWindow->GetHandle())->window), GDK_WINDOW_XID(GTK_WIDGET(pWindow->GetHandle())->window), 0, 0, info.w, info.h, 0, ZPixmap);
			info.mode = nFlag;
			info.start = start;
			info.end = start + 86400;

            PlayerInfo playerInfo;
            playerInfo.pPlayer = new CXPlayer(m_svrAddr.c_str());
            playerInfo.pPlayer->Start(m_resid.c_str(), info);
            m_playerMap[pWindow] = playerInfo;
        }
        else
        {
            it->second.pPlayer->AspectRatio(pWindow-> GetSize().GetWidth(), pWindow-> GetSize().GetHeight());
        }
    }
    else if (nFlag == 0)
    {
        if (it != m_playerMap.end())
        {
            it->second.pPlayer->Stop();
            delete it->second.pPlayer;
            m_playerMap.erase(it);
        }
    }

    //fprintf(stderr, "CMediaObj::Invoke %s %d\n", m_resid.c_str(), pWindow);

    //wxString cmd = wxString::Format
    //(wxT("mplayer -slave -quiet -wid %d http://192.168.1.54/alizee.mp4")
    // , info.xid);
    //wxExecute(cmd, wxEXEC_SYNC);

    return 0;
}

wxWindow *CMediaObj::Close()
{
    PlayerMap::iterator it = m_playerMap.begin();
    if (it != m_playerMap.end())
    {
        it->second.pPlayer->Stop();
        delete it->second.pPlayer;
        m_playerMap.erase(it);

        return it->first;
    }

    return NULL;
}

void CMediaObj::ClearAll()
{
    PlayerMap::iterator it = m_playerMap.begin();
    for (; it!=m_playerMap.end(); it++)
    {
        it->second.pPlayer->Stop();
        delete it->second.pPlayer;
    }
    m_playerMap.clear();
}

void CMediaObj::UpdatePlayer()
{
    PlayerMap::iterator it = m_playerMap.begin();
    for (; it!=m_playerMap.end(); it++)
    {
        wxWindow *pWindow = it->first->GetParent();
        it->second.pPlayer->AspectRatio(pWindow-> GetSize().GetWidth(), pWindow-> GetSize().GetHeight());
    }
}

void CMediaObj::RegistCallback(wxWindow *pWindow, void *func, void *pUser)
{
	PlayerMap::iterator it = m_playerMap.find(pWindow);
	if (it != m_playerMap.end())
	{
		it->second.pPlayer->RegistCallback(func, pUser);
	}
}
