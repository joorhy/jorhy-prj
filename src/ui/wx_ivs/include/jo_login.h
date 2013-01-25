#ifndef __JO_LOGIN_H_
#define __JO_LOGIN_H_

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/button.h>
#include <wx/statline.h>

class CLoginDlg : public wxDialog
{
    public:
        CLoginDlg(wxDialog *parent, const wxString& title);
        ~CLoginDlg();

    protected:
        wxStaticText *m_staticTextServer;
        wxTextCtrl *m_textServer;
        wxStaticText *m_staticTextUser;
        wxTextCtrl *m_textUser;
        wxStaticText *m_staticTextPassw;
        wxTextCtrl *m_textPassw;
        wxButton* m_btnLogin;
        wxButton* m_btnCancel;

    private:
        void OnClose(wxCloseEvent& event);
        void OnLogin(wxCommandEvent& event);
        void OnCancel(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};

#endif // __JO_LOGIN_H_
