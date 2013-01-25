#ifndef __JO_BROWSER_H_
#define __JO_BROWSER_H_

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/app.h>
class jo_browser : public wxApp
{
    public:
        jo_browser();
        ~jo_browser();
    public:
        virtual bool OnInit();
        virtual int OnRun();
        virtual int OnExit();

    private:
        wxDialog *m_login_dlg;
        wxFrame *m_br_frame;
};

#endif // __JO_BROWSER_H_
