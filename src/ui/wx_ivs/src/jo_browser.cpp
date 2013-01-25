#include "jo_browser.h"
#include "jo_login.h"
#include "jo_frame.h"

#include <wx/utils.h>

IMPLEMENT_APP(jo_browser);

jo_browser::jo_browser()
{
    m_login_dlg = NULL;
    m_br_frame = NULL;
}

jo_browser::~jo_browser()
{

}

bool jo_browser::OnInit()
{
    wxImage::AddHandler(new wxICOHandler);
    wxImage::AddHandler(new wxPNGHandler);
    m_login_dlg = new CLoginDlg(NULL, _("Login"));
    return true;
}

int jo_browser::OnRun()
{
    int i_code = m_login_dlg->ShowModal();
	if (i_code == wxID_CANCEL)
    {
        m_login_dlg->Destroy();
        delete m_login_dlg;
        m_login_dlg = NULL;
    }
    else if (i_code > 0)
    {
        m_login_dlg->Destroy();
        wxSleep(1);
        m_br_frame = new CBrFrame(NULL, _("Jo_Browser"), this, i_code);
        m_br_frame->Show();
        m_br_frame->Center();
        //m_br_frame->Maximize(true);
        //m_br_frame->ShowFullScreen(true);

        MainLoop();
    }

    return 0;
}


int jo_browser::OnExit()
{
    if (m_br_frame)
    {
        delete m_br_frame;
        m_br_frame = NULL;
    }

    return 0;
}
