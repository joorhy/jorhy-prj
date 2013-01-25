#ifndef __X_VIDEO_H_
#define __X_VIDEO_H_

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "x_window.h"

#define WIN_NUM     25
#define LAYOUT_NUM  5

class CVideoDlg : public wxWindow
{
    public:
        CVideoDlg(wxWindow *parent);
        ~CVideoDlg();

    public:
        int ChangeMode(int nWinNum, int h = 0);
        wxWindow * GetIdleWin();
        void IdleAll();
        int SetBusyWin(const wxWindow *pWindow);
        int SetIdleWin(const wxWindow *pWindow);
        const char *GetCurResid() { return m_curResid.c_str(); }

	private:
		void OnPaint(wxPaintEvent& event);
		void OnMove(wxMoveEvent& event);
        void OnSize(wxSizeEvent& event);
        void OnMouseLeftDown(wxMouseEvent &event);
        DECLARE_EVENT_TABLE()

    private:
        void Init();
        void ClearSizer();
        void WinLayout();
		void SelectWindow(wxWindow *pWindow, bool bSelected);

    private:
        struct VideoWinInfo
        {
            CVideoWin *video_win;
            bool is_busy;
        };

        VideoWinInfo m_videoWin[WIN_NUM];
        int m_videoNum;
        int m_videoOldNum;
		int m_nAdjustHeight;
        wxWindow *m_forcusWin;
        std::string m_curResid;
};

#endif // __X_VIDEO_H_
