#ifndef __JO_FRAME_H_
#define __JO_FRAME_H_

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "jo_sdk.h"

class CBrFrame : public wxFrame
{
    public:
        CBrFrame(wxFrame *frame, const wxString& title, wxApp *app, int userid);
        ~CBrFrame();

    public:
        int GetUserId() { return m_userId; }
        wxWindow *GetVideoDlg() { return m_pVideoDlg; }
        wxWindow *GetCatalogDlg() { return m_pCatalogDlg; }
		wxWindow *GetRcdDlg() { return m_pRcdDlg; }
		wxWindow *GetRcdSlider() { return m_pRcdSlider; }
        static CXSdk &GetSdk() { return m_sdk; }
		void OnSelectToolWin(int nToolWin);

    private:
        void OnClose(wxCloseEvent& event);
        void OnMove(wxMoveEvent& event);
        void OnSize(wxSizeEvent& event);
        DECLARE_EVENT_TABLE()

    private:
        void Init();
        void Deinit();
		void HideAll();
		void ShowRealView();
		void ShowHistoryUI();

    private:
        wxApp *m_app;
		wxWindow *m_pToolWin;
        wxWindow *m_pCatalogDlg;
        wxWindow *m_pPtzDlg;
		wxWindow *m_pRcdDlg;
        wxWindow *m_pVideoDlg;
		wxWindow *m_pRcdSlider;
		
        int m_userId;
		int m_nCurToolWin;
		int m_nOldToolWin;

        static CXSdk m_sdk;
};


#endif // __JO_FRAME_H_
