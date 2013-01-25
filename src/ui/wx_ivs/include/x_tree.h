#ifndef __X_TREE_CTRL_H_
#define __X_TREE_CTRL_H_

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <map>
#include <string>
#include <wx/treectrl.h>
#include <wx/imaglist.h>

class CXTree : public wxTreeCtrl
{
    public:
        CXTree(wxWindow *parent);
        ~CXTree();

    private:
        void OnSize(wxSizeEvent& event);
        void OnTreeItemActivated(wxTreeEvent& event);
        void OnTreeItemRightClick(wxTreeEvent& event);
        void OnMediaClose(wxCommandEvent& event);
        void OnWindowClose(wxCommandEvent& event);
		void OnSearchHistory(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()

    public:
        int AddTree(const char *pXmlStr);
        void DelTree();
        void UpdatePlayer();
		void SetMode(int mode) { m_nMode = mode; }
		void CloseAllVideo();
		void StartVideo(wxWindow *pWindow, wxTreeItemId itemId);
		
    private:
        wxBitmap m_titleBmp;
        wxImageList *m_imageList;

        wxTreeItemId m_root;
        wxTreeItemId m_level0;
        wxTreeItemId m_level1;

        wxMenu *m_menu;
        wxTreeItemId m_treeItemId;
		wxWindow *m_pFrame;

        typedef std::map<wxWindow *, wxTreeItemId> TreeItemIdMap;
        TreeItemIdMap m_treeItemIdMap;
		
		int m_nMode;
};

#endif // __X_TREE_CTRL_H_
