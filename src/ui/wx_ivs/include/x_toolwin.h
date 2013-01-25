#ifndef __X_TOOLWIN_H_
#define __X_TOOLWIN_H_

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class CXToolWin : public wxWindow
{
    public:
        CXToolWin(wxWindow *parent);
        ~CXToolWin();

    private:
        void OnEraseBackground(wxEraseEvent& event);
        void OnSize(wxSizeEvent& event);
		void OnMouseLeftDown(wxMouseEvent &event);
        DECLARE_EVENT_TABLE()

    private:
        wxBitmap m_bmpBg;
        wxBitmap m_bmpLine;
		wxBitmap m_bmpBgSelect;
        wxBitmap m_bmpLineLeft;
		wxBitmap m_bmpLineRight;
		
		int m_nCurTool;
};

#endif //~__X_TOOLWIN_H_