#ifndef __X_TABVIEW_H_
#define __X_TABVIEW_H_

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class CXTabView : public wxWindow
{
    public:
        CXTabView(wxWindow *parent);
        ~CXTabView();

    private:
        void OnPaint(wxPaintEvent& event);
        void OnSize(wxSizeEvent& event);
        DECLARE_EVENT_TABLE()

    private:
        wxBitmap m_bgBmp[3];
        wxBitmap m_bgBmp2[3];
};

#endif //~__X_TABVIEW_H_