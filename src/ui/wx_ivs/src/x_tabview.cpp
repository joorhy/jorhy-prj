#include "x_tabview.h"

BEGIN_EVENT_TABLE(CXTabView, wxWindow)
    EVT_PAINT(CXTabView::OnPaint)
    EVT_SIZE(CXTabView::OnSize)
END_EVENT_TABLE()

CXTabView::CXTabView(wxWindow *parent)
    : wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    m_bgBmp[0].LoadFile(wxString::FromUTF8("./images/tab_left.png"), wxBITMAP_TYPE_PNG);
    m_bgBmp[1].LoadFile(wxString::FromUTF8("./images/tab_center.png"), wxBITMAP_TYPE_PNG);
    m_bgBmp[2].LoadFile(wxString::FromUTF8("./images/tab_right.png"), wxBITMAP_TYPE_PNG);

    m_bgBmp2[0].LoadFile(wxString::FromUTF8("./images/tab_left2.png"), wxBITMAP_TYPE_PNG);
    m_bgBmp2[1].LoadFile(wxString::FromUTF8("./images/tab_center2.png"), wxBITMAP_TYPE_PNG);
    m_bgBmp2[2].LoadFile(wxString::FromUTF8("./images/tab_right2.png"), wxBITMAP_TYPE_PNG);
}

CXTabView::~CXTabView()
{

}

void CXTabView::OnPaint(wxPaintEvent& event)
{
    wxPaintDC *dc = new wxPaintDC(this);
    wxRect rc = GetClientRect();

    wxPen pen;
    pen.SetStyle(wxTRANSPARENT);
    dc->SetPen(pen);
    {
        dc->SetBrush(m_bgBmp[1]);
        dc->DrawRectangle(m_bgBmp[1].GetWidth(), 0
                          , rc.GetWidth() - 2 * m_bgBmp[1].GetWidth(), m_bgBmp[1].GetHeight());
        dc->DrawBitmap(m_bgBmp[0], 0, 0, true);
        dc->DrawBitmap(m_bgBmp[2], rc.GetWidth() - m_bgBmp[1].GetWidth(), 0, true);
    }
    /*{
        dc->SetBrush(m_bgBmp2[1]);
        dc->DrawRectangle(m_bgBmp2[1].GetWidth(), 0
                          , rc.GetWidth() - 2 * m_bgBmp2[1].GetWidth(), m_bgBmp2[1].GetHeight());
        dc->DrawBitmap(m_bgBmp2[0], 0, 0, true);
        dc->DrawBitmap(m_bgBmp2[2], rc.GetWidth() - m_bgBmp2[1].GetWidth(), 0, true);
    }*/
    //dc->DrawText(m_title, 5, 2);
}

void CXTabView::OnSize(wxSizeEvent& event)
{
    Layout();
}