#include "x_catalog.h"
#include "x_title.h"
#include "jo_sdk.h"
#include "jo_frame.h"

BEGIN_EVENT_TABLE(CCatalogDlg, wxWindow)
    EVT_SIZE(CCatalogDlg::OnSize)
END_EVENT_TABLE()

CCatalogDlg::CCatalogDlg(wxWindow *parent)
: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED | wxBORDER_DOUBLE)
{
    SetBackgroundColour(wxColor(242, 243, 247));
	m_nAdjustHeight = 238;
	m_nMode = 1;
    Init();
}

CCatalogDlg::~CCatalogDlg()
{
    Deinit();
}

void CCatalogDlg::Init()
{
    m_pTitleWin = new CXTitle(this, _("摄像机"), wxString::FromUTF8("./images/icon/win_camera.png"));
    m_pVideoTree = new CXTree(this);
    m_pVideoTree->AddTree(CBrFrame::GetSdk().GetResList(((CBrFrame *)GetParent())->GetUserId()));
}

void CCatalogDlg::Deinit()
{
    if (m_pTitleWin != NULL)
    {
        delete m_pTitleWin;
        m_pTitleWin = NULL;
    }

    if (m_pVideoTree != NULL)
    {
        m_pVideoTree->DelTree();
        delete m_pVideoTree;
        m_pVideoTree = NULL;
    }
}

void CCatalogDlg::OnSize(wxSizeEvent &event)
{
    //event.Skip();
    SetSize(0, 42, 251, GetParent()->GetSize().GetHeight() - m_nAdjustHeight);
    wxPostEvent(m_pTitleWin, event);
    wxPostEvent(m_pVideoTree, event);

    return;
}

void CCatalogDlg::ChangeMode(int nMode, int h)
{ 
	if (m_nMode != nMode)
	{
		m_nMode = nMode;
		m_nAdjustHeight = h; 
		m_pVideoTree->SetMode(nMode);
		m_pVideoTree->CloseAllVideo();
	}
} 
