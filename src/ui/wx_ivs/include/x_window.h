#ifndef __X_WINDOW_H_
#define __X_WINDOW_H_

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <string>

class CVideoWin : public wxWindow
{
    public:
        CVideoWin(wxWindow *parent);
        ~CVideoWin();

    public:
        int SetWinNum(int nWinNum, int nPos);
        wxWindow *GetWindow() { return m_panel; }
        void SetResid(const char *pResid);
        const char *GetResid();

	public:
        void OnSize(wxSizeEvent& event);
		void OnPaint(wxPaintEvent &event);
        void OnRightDown(wxMouseEvent &event);
        void OnWindowClose(wxCommandEvent& event);
        void OnMouseLeftDown(wxMouseEvent &event);
        DECLARE_EVENT_TABLE()

    private:
        void Init();

    private:
        std::string m_resid;
        bool m_isSelected;
        int m_nWinNum;
        int m_nPos;
        wxPanel *m_panel;
        wxMenu *m_menu;
};

#endif // __X_WINDOW_H_
