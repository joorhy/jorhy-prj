#include "jo_login.h"
#include "x_errtype.h"
#include "jo_frame.h"

#include <wx/gbsizer.h>
#include <wx/colour.h>
#include <wx/string.h>

BEGIN_EVENT_TABLE(CLoginDlg, wxDialog)
    EVT_CLOSE(CLoginDlg::OnClose)
    EVT_BUTTON(wxID_OK, CLoginDlg::OnLogin)
    EVT_BUTTON(wxID_CANCEL, CLoginDlg::OnCancel)
END_EVENT_TABLE()

CLoginDlg::CLoginDlg(wxDialog *parent, const wxString &title)
    : wxDialog(parent, wxID_ANY, title)
{
    wxIcon icoApp(wxString::FromUTF8("./images/icon/jo_browser.ico"), wxBITMAP_TYPE_ICO);
    SetIcon(icoApp);

    SetBackgroundColour(wxColor(242, 243, 247));
    SetInitialSize(wxSize(500, 300));

    wxGridBagSizer *bCtrlSizer = new  wxGridBagSizer(3, 4);
    ///服务器信息
    m_staticTextServer = new wxStaticText(this, wxID_ANY, wxT("     服务器"), wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_textServer = new wxTextCtrl(this, wxID_ANY, wxT("192.168.1.106"), wxDefaultPosition, wxSize(200, -1), wxALIGN_LEFT);
    bCtrlSizer->Add(m_staticTextServer, wxGBPosition(0, 0), wxDefaultSpan, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT);
    bCtrlSizer->Add(m_textServer, wxGBPosition(0, 1), wxDefaultSpan, wxALIGN_CENTER_VERTICAL |  wxALIGN_RIGHT);

    ///用户名
    m_staticTextUser = new wxStaticText(this, wxID_ANY, wxT("用户名称"), wxDefaultPosition,  wxSize(100, -1), wxALIGN_RIGHT);
    m_textUser = new wxTextCtrl(this, wxID_ANY, wxT("admin"), wxDefaultPosition, wxSize(200, -1), wxALIGN_LEFT);
    bCtrlSizer->Add(m_staticTextUser, wxGBPosition(1, 0), wxDefaultSpan, wxALIGN_CENTER_VERTICAL |  wxALIGN_LEFT);
    bCtrlSizer->Add(m_textUser, wxGBPosition(1, 1), wxDefaultSpan, wxALIGN_CENTER_VERTICAL |  wxALIGN_RIGHT);

    ///密码
    m_staticTextPassw = new wxStaticText(this, wxID_ANY, wxT("          密码"), wxDefaultPosition,  wxSize(100, -1), wxALIGN_RIGHT);
    m_textPassw = new wxTextCtrl(this, wxID_ANY, wxT("admin"), wxDefaultPosition,  wxSize(200, -1), wxTE_PASSWORD | wxALIGN_LEFT);
    bCtrlSizer->Add(m_staticTextPassw, wxGBPosition(2, 0), wxDefaultSpan, wxALIGN_CENTER_VERTICAL |  wxALIGN_LEFT);
    bCtrlSizer->Add(m_textPassw, wxGBPosition(2, 1), wxDefaultSpan, wxALIGN_CENTER_VERTICAL |  wxALIGN_RIGHT);

    wxBoxSizer *btnSizer = new wxBoxSizer(wxHORIZONTAL);
    ///登录取消
    m_btnLogin = new wxButton(this, wxID_OK, wxT("登录"), wxDefaultPosition, wxDefaultSize, 0);
    m_btnLogin->SetDefault();
    m_btnCancel = new wxButton(this, wxID_CANCEL, wxT("取消"), wxDefaultPosition, wxDefaultSize, 0);
    btnSizer-> AddSpacer(240);
    btnSizer->Add(m_btnLogin, 0, wxALIGN_CENTER);
    btnSizer->AddSpacer(15);
    btnSizer->Add(m_btnCancel, 1, wxALIGN_CENTER);

    ///对话框
    wxBoxSizer* dlgSizer = new wxBoxSizer(wxVERTICAL);
    dlgSizer->AddSpacer(60);
    dlgSizer->Add(bCtrlSizer, 0, wxALIGN_CENTRE);
    //dlgSizer->AddSpacer(5);
    dlgSizer->Add(btnSizer, 1, wxALIGN_CENTRE);

    SetSizer(dlgSizer);
    Layout();
    CenterOnScreen();

    m_textServer->SetFocus();
}


CLoginDlg::~CLoginDlg()
{

}

void CLoginDlg::OnClose(wxCloseEvent &event)
{
    EndDialog(wxID_CANCEL);
}

void CLoginDlg::OnLogin(wxCommandEvent &event)
{
    wxString  serverIp = m_textServer->GetValue();
    wxString  userName = m_textUser->GetValue();
    wxString  passWord = m_textPassw->GetValue();
    int nRet = CBrFrame::GetSdk().Login(serverIp.ToAscii(), 8008, userName.ToAscii(), passWord.ToAscii());
    if (nRet > 0)
    {
        EndDialog(nRet);
    }
    else
    {
        wxMessageDialog *msgBox = new wxMessageDialog(this, wxString:: FromUTF8("登录失败!"), wxString:: FromUTF8(""), wxOK | wxICON_WARNING);
        msgBox->ShowModal();
        msgBox->CenterOnParent();
        msgBox->Destroy();
        delete msgBox;
    }
}

void CLoginDlg::OnCancel(wxCommandEvent &event)
{
    EndDialog(wxID_CANCEL);
}
