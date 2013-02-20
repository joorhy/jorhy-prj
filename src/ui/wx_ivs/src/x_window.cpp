#include "x_window.h"
#include "jo_frame.h"
#include "x_catalog.h"
#include "x_resource.h"

BEGIN_EVENT_TABLE(CVideoWin, wxWindow)
    EVT_SIZE(CVideoWin::OnSize)
	EVT_PAINT(CVideoWin::OnPaint)
    EVT_RIGHT_DOWN(CVideoWin::OnRightDown)
    EVT_MENU(Menu_Window_Close, CVideoWin::OnWindowClose)
    EVT_LEFT_DOWN(CVideoWin::OnMouseLeftDown)
END_EVENT_TABLE()

CVideoWin::CVideoWin(wxWindow *parent)
: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED | wxBORDER_DOUBLE)
{
    SetBackgroundColour(wxColor(0, 0, 0));
    Init();
}

CVideoWin::~CVideoWin()
{
    if (m_panel)
        delete m_panel;
}

void CVideoWin::Init()
{
    m_isSelected = false;
    m_menu = new wxMenu;

    m_nWinNum = 2;
    m_nPos = 0;
    m_panel = new wxPanel(this);
    m_panel->SetBackgroundColour(GetBackgroundColour());
    m_panel->SetSize(0, 0, 0, 0);
    m_panel->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CVideoWin::OnMouseLeftDown));
}

int CVideoWin::SetWinNum(int nWinNum, int nPos)
{
    m_nWinNum = nWinNum;
    m_nPos = nPos;

    return 0;
}

void CVideoWin::SetResid(const char *pResid)
{
    m_resid = pResid;
}

const char *CVideoWin::GetResid()
{
    return m_resid.c_str();
}

void CVideoWin::OnSize(wxSizeEvent &event)
{
    event.Skip();
    int n = sqrt(m_nWinNum);
    int w = GetParent()->GetSize().GetWidth() / n;
    int h = GetParent()->GetSize().GetHeight() / n;
    SetSize(w * (m_nPos % n),
            h * (m_nPos / n),
            w - 2,
            h - 2);
    m_panel->CenterOnParent();
    //fprintf(stderr, "CVideoWin::OnSize %d:%d\n", w, h);
}

void CVideoWin::OnPaint(wxPaintEvent &event)
{
	
}

void CVideoWin::OnRightDown(wxMouseEvent &event)
{
    wxMenuItemList itemList = m_menu->GetMenuItems();
    wxMenuItemList::iterator iter;
    for (iter = itemList.begin(); iter != itemList.end(); ++iter)
    {
        wxMenuItem *current = *iter;
        m_menu->Remove(current);
    }
    m_menu->Append(Menu_Window_Close, wxString::FromUTF8("关闭视频"));
    m_menu->Enable(Menu_Window_Close, true);

    PopupMenu(m_menu);
}

void CVideoWin::OnWindowClose(wxCommandEvent& event)
{
    event.SetClientData(m_panel);
    wxPostEvent(((CCatalogDlg *)((CBrFrame *)GetParent()->GetParent())->GetCatalogDlg())->GetTreeWindow(), event);
}

void CVideoWin::OnMouseLeftDown(wxMouseEvent &event)
{
    event.Skip();
    m_isSelected = true;
    wxPostEvent(GetParent(), event);
    //fprintf(stderr, "CVideoWin::OnMouseLeftDown %d %d\n", event.GetEventObject(), this);
}
