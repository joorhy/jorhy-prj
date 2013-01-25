#include "x_tree.h"
#include "x_resource.h"
#include "jo_media_obj.h"
#include "x_video.h"
#include "x_rcd_slider.h"
#include "x_rcdctl.h"
#include "x_window.h"
#include "jo_frame.h"
#include "x_xml_stream.h"

#include <string>
#include <wx/xml/xml.h>

BEGIN_EVENT_TABLE(CXTree, wxTreeCtrl)
    EVT_SIZE(CXTree::OnSize)
    EVT_TREE_ITEM_ACTIVATED(ID_USR_TREECTRL, CXTree::OnTreeItemActivated)
    EVT_TREE_ITEM_RIGHT_CLICK(ID_USR_TREECTRL, CXTree::OnTreeItemRightClick)
    EVT_MENU(Menu_Media_Close, CXTree::OnMediaClose)
    EVT_MENU(Menu_Window_Close, CXTree::OnWindowClose)
	EVT_MENU(Menu_Search_History, CXTree::OnSearchHistory)
END_EVENT_TABLE()

CXTree::CXTree(wxWindow *parent)
    : wxTreeCtrl(parent, ID_USR_TREECTRL, wxDefaultPosition, wxDefaultSize
            , wxBORDER_NONE | wxTR_HIDE_ROOT | wxTR_SINGLE | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT)
{
    SetBackgroundColour(wxColor(226, 237, 241));

    m_titleBmp.LoadFile(wxString::FromUTF8("./images/tabview_middle.png"), wxBITMAP_TYPE_PNG);
    m_imageList = new wxImageList(500, 300);
    m_imageList->Add(wxBitmap(wxString::FromUTF8("./images/icon/server.png"), wxBITMAP_TYPE_PNG));
    m_imageList->Add(wxBitmap(wxString::FromUTF8("./images/icon/camera.png"), wxBITMAP_TYPE_PNG));

    m_menu = new wxMenu;
	m_nMode = 1;
	m_pFrame = GetParent()->GetParent();

    AssignImageList(m_imageList);
}

CXTree::~CXTree()
{

}

void CXTree::OnSize(wxSizeEvent& event)
{
    //event.Skip();
    SetSize(0, m_titleBmp.GetHeight(), 251
            , GetParent()->GetSize().GetHeight()-m_titleBmp.GetHeight());
    UpdatePlayer();
}

void CXTree::OnTreeItemActivated(wxTreeEvent& event)
{
	wxTreeItemId treeItemId = event.GetItem();
	CMediaObj *pObj = dynamic_cast<CMediaObj *>(GetItemData(treeItemId));
	if (pObj != NULL)
	{
		CVideoDlg *pVideoDlg = dynamic_cast<CVideoDlg *>
			(((CBrFrame *)m_pFrame)->GetVideoDlg());
		if (pVideoDlg != NULL && m_nMode == 1)
		{
			wxWindow *pWindow = pVideoDlg->GetIdleWin();
			if (pWindow != NULL && pObj->Invoke(pWindow) == 0)
			{
				pVideoDlg->SetBusyWin(pWindow);
				m_treeItemIdMap[pWindow] = treeItemId;
				((CVideoWin *)pWindow->GetParent())->SetResid(pObj->GetResid());
			}
		}
	}
	else
	{
		if (IsExpanded(treeItemId))
			Toggle(treeItemId);
		else
			ExpandAllChildren(treeItemId);
	}
}

void CXTree::OnTreeItemRightClick(wxTreeEvent& event)
{
    m_treeItemId = event.GetItem();

    wxMenuItemList itemList = m_menu->GetMenuItems();
    wxMenuItemList::iterator iter;
    for (iter = itemList.begin(); iter != itemList.end(); ++iter)
    {
        wxMenuItem *current = *iter;
        m_menu->Remove(current);
    }
    m_menu->Append(Menu_Media_Close, wxString::FromUTF8("关闭"));
    m_menu->Break();
	if (m_nMode == 2)
	{
		m_menu->Append(Menu_Search_History, wxString::FromUTF8("检索历史"));
	}
    //m_menu->Enable(Menu_Media_Close, true);

    PopupMenu(m_menu);
}

void CXTree::OnMediaClose(wxCommandEvent& event)
{
	wxWindow *pWindow = NULL;
    CVideoDlg *pVideoDlg = dynamic_cast<CVideoDlg *>(((CBrFrame *)m_pFrame)->GetVideoDlg());

    CMediaObj *pObj = dynamic_cast<CMediaObj *>(GetItemData(m_treeItemId));
    if (pObj != NULL)
    {
        while ((pWindow = pObj->Close()) != NULL)
        {
            pVideoDlg->SetIdleWin(pWindow);
            m_treeItemIdMap.erase(pWindow);
        }
    }
}

void CXTree::OnWindowClose(wxCommandEvent& event)
{
	wxWindow *pWindow = (wxWindow *)event.GetClientData();
    CVideoDlg *pVideoDlg = dynamic_cast<CVideoDlg *>(((CBrFrame *)m_pFrame)->GetVideoDlg());

    TreeItemIdMap::iterator it = m_treeItemIdMap.find(pWindow);
    if (it != m_treeItemIdMap.end())
    {
        CMediaObj *pObj = dynamic_cast<CMediaObj *>(GetItemData(it->second));
        if (pObj != NULL)
        {
            pObj->Invoke(pWindow, 0);
            pVideoDlg->SetIdleWin(pWindow);
            m_treeItemIdMap.erase(it);
        }
    }
}

void CXTree::OnSearchHistory(wxCommandEvent& event)
{
	wxDateTime dateTime = ((CXRcdCtl *)((CBrFrame *)m_pFrame)->GetRcdDlg())->GetDateTime();
	dateTime.SetHour(0);
	dateTime.SetMinute(0);
	dateTime.SetSecond(0);
	
	CMediaObj *pObj = dynamic_cast<CMediaObj *>(GetItemData(m_treeItemId));
    if (pObj != NULL)
    {
		RcdTimeList timeList;
		CBrFrame::GetSdk().SearchRecord(((CBrFrame *)m_pFrame)->GetUserId(), pObj->GetResid(), 
			dateTime.GetTicks() - (86400 * 2), dateTime.GetTicks() + (86400 * 3), timeList);
		CXRcdSlider *pRcdSlider = dynamic_cast<CXRcdSlider *>(((CBrFrame *)m_pFrame)->GetRcdSlider());
		if (pRcdSlider)
		{
			pRcdSlider->RefreshRecordInfo(timeList, pObj, m_treeItemId);
		}
	}
}

int CXTree::AddTree(const char *pXmlStr)
{
    if (pXmlStr != NULL)
	{
		m_root = AddRoot(wxString::FromUTF8(""));

		CXMLStream inputStream;
		inputStream.Ungetch(pXmlStr, strlen(pXmlStr));
		wxXmlDocument xmlDoc(inputStream);
		wxXmlNode *pServerNode = xmlDoc.GetRoot();
		while (pServerNode != NULL)
		{
			wxString value0;
			pServerNode->GetPropVal(wxString::FromUTF8("desc"), &value0);
			m_level0 = AppendItem(m_root, value0, 0);
			pServerNode->GetPropVal(wxString::FromUTF8("ipAddr"), &value0);
			wxXmlNode *pChannelNode = pServerNode->GetChildren();
			while (pChannelNode != NULL)
			{
				wxString value1;
				pChannelNode->GetPropVal(wxString::FromUTF8("desc"), &value1);
				m_level1 = AppendItem(m_level0, value1, 1);
				pChannelNode->GetPropVal(wxString::FromUTF8("id"), &value1);
				SetItemData(m_level1, new CMediaObj(value1.ToAscii(), value0.ToAscii()));
				pChannelNode = pChannelNode->GetNext();
			}
			pServerNode = pServerNode->GetNext();
		}
	}

    return 0;
}

void CXTree::DelTree()
{
	CloseAllVideo();
	DeleteAllItems();
}

void CXTree::UpdatePlayer()
{
    wxTreeItemIdValue srv_cookie = 0;
    wxTreeItemId srv_id = GetFirstChild(m_root, srv_cookie);
    while (srv_id.IsOk())
    {
        wxTreeItemIdValue cha_cookie;
        wxTreeItemId cha_id = GetFirstChild(srv_id, cha_cookie);
        while (cha_id.IsOk())
        {
            CMediaObj *pObj = dynamic_cast<CMediaObj *>(GetItemData(cha_id));
            if (pObj != NULL)
            {
                pObj->UpdatePlayer();
            }
            cha_id = GetNextChild(srv_id, cha_cookie);
        }
        srv_id = GetNextChild(m_root, srv_cookie);
    }
}

void CXTree::CloseAllVideo()
{
		wxTreeItemIdValue srv_cookie = 0;
    wxTreeItemId srv_id = GetFirstChild(m_root, srv_cookie);
    while (srv_id.IsOk())
    {
        wxTreeItemIdValue cha_cookie;
        wxTreeItemId cha_id = GetFirstChild(srv_id, cha_cookie);
        while (cha_id.IsOk())
        {
            CMediaObj *pObj = dynamic_cast<CMediaObj *>(GetItemData(cha_id));
            if (pObj != NULL)
            {
                pObj->ClearAll();
            }
            cha_id = GetNextChild(srv_id, cha_cookie);
        }
        srv_id = GetNextChild(m_root, srv_cookie);
    }
    CVideoDlg *pVideoDlg = dynamic_cast<CVideoDlg *>
                    (((CBrFrame *)m_pFrame)->GetVideoDlg());
    if (pVideoDlg != NULL)
    {
        pVideoDlg->IdleAll();
    }
}

void CXTree::StartVideo(wxWindow *pWindow, wxTreeItemId itemId)
{
	m_treeItemIdMap[pWindow] = itemId;
}

