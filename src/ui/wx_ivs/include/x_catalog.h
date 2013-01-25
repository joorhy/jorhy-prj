#ifndef __X_CATALOG_H_
#define __X_CATALOG_H_

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "x_tree.h"

class CCatalogDlg : public wxWindow
{
    public:
        CCatalogDlg(wxWindow *parent);
        ~CCatalogDlg();

    public:
        wxWindow *GetTreeWindow() { return m_pVideoTree; }
		void ChangeMode(int nMode, int h); 

    private:
        void OnSize(wxSizeEvent& event);
        DECLARE_EVENT_TABLE()

    private:
        void Init();
        void Deinit();

    private:
        wxWindow *m_pTitleWin;
        CXTree *m_pVideoTree;
		int m_nAdjustHeight;
		int m_nMode;
};

#endif // __X_CATALOG_H_
