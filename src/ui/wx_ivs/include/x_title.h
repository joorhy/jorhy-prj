#ifndef __X_TITLE_H_
#define __X_TITLE_H_

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class CXTitle : public wxWindow
{
    public:
        CXTitle(wxWindow *parent, const wxString &title, const wxString &bm_name);
        ~CXTitle();

    private:
        void OnPaint(wxPaintEvent& event);
        void OnSize(wxSizeEvent& event);
        DECLARE_EVENT_TABLE()

    private:
        void LoadBitmaps();

    private:
        wxBitmap m_bgBmp[3];
        wxBitmap m_leftBmp;
        wxString m_title;

        wxBitmapButton *m_btnMax;
        wxBitmapButton *m_btnMin;
        wxBitmapButton *m_btnClose;
};

#endif // __X_TITLE_H_
