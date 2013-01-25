#include "x_toolwin.h"
#include "jo_frame.h"

const char *tool_name[] = { "实时预览", "历史回放", "地	图", "日	志"};

BEGIN_EVENT_TABLE(CXToolWin, wxWindow)
    EVT_ERASE_BACKGROUND(CXToolWin::OnEraseBackground)
    EVT_SIZE(CXToolWin::OnSize)
	EVT_LEFT_DOWN(CXToolWin::OnMouseLeftDown)
END_EVENT_TABLE()

CXToolWin::CXToolWin(wxWindow *parent)
    : wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    m_bmpBg.LoadFile(wxString::FromUTF8("./images/toolwnd_bg.png"), wxBITMAP_TYPE_PNG);
    m_bmpLine.LoadFile(wxString::FromUTF8("./images/toolwnd_line.png"), wxBITMAP_TYPE_PNG);
    m_bmpBgSelect.LoadFile(wxString::FromUTF8("./images/toolwnd_bg_select.png"), wxBITMAP_TYPE_PNG);
    m_bmpLineLeft.LoadFile(wxString::FromUTF8("./images/toolwnd_line_left.png"), wxBITMAP_TYPE_PNG);
    m_bmpLineRight.LoadFile(wxString::FromUTF8("./images/toolwnd_line_right.png"), wxBITMAP_TYPE_PNG);
    
	m_nCurTool = 0;
}

CXToolWin::~CXToolWin()
{

}

void CXToolWin::OnEraseBackground(wxEraseEvent& event)
{
    wxDC *dc = event.GetDC();
    dc->SetBrush(m_bmpBg);
    wxPen pen;
    pen.SetStyle(wxTRANSPARENT);
    dc->SetPen(pen);
    dc->DrawRectangle(0, 0, GetParent()->GetSize().GetWidth(), m_bmpBg.GetHeight());
	dc->SetBrush(m_bmpBgSelect);
	dc->DrawRectangle(m_nCurTool * 120, 0, 120, m_bmpBg.GetHeight());
	wxFont font(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(wxColour(255, 255, 255));

	for (int i=0; i<4; i++)
	{
		if (i == m_nCurTool)
		{
			if (m_nCurTool == 0)
			{
				dc->DrawBitmap(m_bmpLineRight, 120 * (i+1), 0, true);
			}
			else if (m_nCurTool == i)
			{
				dc->DrawBitmap(m_bmpLineLeft, 120 * (i), 0, true);
			}
			else if ((m_nCurTool + 1) == i)
			{
				dc->DrawBitmap(m_bmpLineRight, 120 * (i+1), 0, true);
			}
		}
		else
		{
			dc->DrawBitmap(m_bmpLine, 120 * (i+1), 0, true);
		}
		dc->DrawText(wxString::FromUTF8(tool_name[i]), 120 * i + 30, 12);
	}
}

void CXToolWin::OnSize(wxSizeEvent& event)
{
	SetSize(0, 0, GetParent()->GetSize().GetWidth(), m_bmpBg.GetHeight());
    Refresh();
}

void CXToolWin::OnMouseLeftDown(wxMouseEvent &event)
{
	wxPoint pst = event.GetPosition();
	if (pst.x >= 0 && pst.x <= 480)
	{
		m_nCurTool = (pst.x - 1)/ 120;
		Refresh();
	}
	((CBrFrame *)GetParent())->OnSelectToolWin(m_nCurTool);
}