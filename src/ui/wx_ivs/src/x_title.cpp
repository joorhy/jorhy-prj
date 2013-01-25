#include "x_title.h"

BEGIN_EVENT_TABLE(CXTitle, wxWindow)
    EVT_PAINT(CXTitle::OnPaint)
    EVT_SIZE(CXTitle::OnSize)
END_EVENT_TABLE()

CXTitle::CXTitle(wxWindow *parent, const wxString &title, const wxString &bm_name)
    : wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetBackgroundColour(wxColor(226, 237, 241));
    m_title = title;
    LoadBitmaps();
    m_leftBmp.LoadFile(bm_name, wxBITMAP_TYPE_PNG);
}

CXTitle::~CXTitle()
{

}

void CXTitle::LoadBitmaps()
{
    m_bgBmp[0].LoadFile(wxString::FromUTF8("./images/tabview_left.png"), wxBITMAP_TYPE_PNG);
    m_bgBmp[1].LoadFile(wxString::FromUTF8("./images/tabview_middle.png"), wxBITMAP_TYPE_PNG);
    m_bgBmp[2].LoadFile(wxString::FromUTF8("./images/tabview_right.png"), wxBITMAP_TYPE_PNG);
}

void CXTitle::OnPaint(wxPaintEvent& event)
{
    wxPaintDC *dc = new wxPaintDC(this);
    wxRect rc = GetClientRect();

    wxPen pen;
    pen.SetStyle(wxTRANSPARENT);
    dc->SetPen(pen);
    dc->SetBrush(m_bgBmp[1]);
    dc->DrawRectangle(m_bgBmp[1].GetWidth(), 0
                      , rc.GetWidth() - 2 * m_bgBmp[1].GetWidth(), m_bgBmp[1].GetHeight());
    dc->DrawBitmap(m_bgBmp[0], 0, 0, true);
    dc->DrawBitmap(m_bgBmp[2], rc.GetWidth() - m_bgBmp[2].GetWidth(), 0, true);

    dc->DrawBitmap(m_leftBmp, 5, 5, true);
    dc->DrawText(m_title, 25, 5);

    //fprintf(stderr, "OnPaint\n");

}

void CXTitle::OnSize(wxSizeEvent& event)
{
    //event.Skip();
    SetSize(0, 0, GetParent()->GetSize().GetWidth(), m_bgBmp[1].GetHeight());
    Refresh();

    //fprintf(stderr, "OnSize\n");
}
