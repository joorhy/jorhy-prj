#include "x_video.h"

BEGIN_EVENT_TABLE(CVideoDlg, wxWindow)
	EVT_PAINT(CVideoDlg::OnPaint)
	EVT_MOVE(CVideoDlg::OnMove)
    EVT_SIZE(CVideoDlg::OnSize)
    EVT_LEFT_DOWN(CVideoDlg::OnMouseLeftDown)
END_EVENT_TABLE()

CVideoDlg::CVideoDlg(wxWindow *parent)
: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED | wxBORDER_DOUBLE)
{
    //SetBackgroundColour(wxColor(226, 237, 241));
    m_videoNum = 4;
    m_videoOldNum = 0;
	m_nAdjustHeight = 0;
    Init();
    ChangeMode(m_videoNum);
}

CVideoDlg::~CVideoDlg()
{
    ClearSizer();
}

int CVideoDlg::ChangeMode(int nWinNum, int h)
{
    m_videoNum = nWinNum;
	m_nAdjustHeight = h;
	m_forcusWin = NULL;

    return 0;
}

wxWindow *CVideoDlg::GetIdleWin()
{
    for (int i=0; i<m_videoNum; i++)
    {
        if (!m_videoWin[i].is_busy)
            return m_videoWin[i].video_win->GetWindow();
    }

    return NULL;
}

void CVideoDlg::IdleAll()
{
    for (int i=0; i<WIN_NUM; i++)
    {
        m_videoWin[i].is_busy = false;
    }
}

int CVideoDlg::SetBusyWin(const wxWindow *pWindow)
{
    for (int i=0; i<m_videoNum; i++)
    {
        if (m_videoWin[i].video_win->GetWindow() == pWindow)
        {
            m_videoWin[i].is_busy = true;
            return 0;
        }
    }

    return -1;
}

int CVideoDlg::SetIdleWin(const wxWindow *pWindow)
{
    for (int i=0; i<m_videoNum; i++)
    {
        if (m_videoWin[i].video_win->GetWindow() == pWindow)
        {
            m_videoWin[i].is_busy = false;
			m_videoWin[i].video_win->Refresh();
            return 0;
        }
    }

    return -1;
}

void CVideoDlg::Init()
{
    m_forcusWin = NULL;
    for (int i=0; i<WIN_NUM; i++)
    {
        m_videoWin[i].video_win = new CVideoWin(this);
        m_videoWin[i].is_busy = false;
        m_videoWin[i].video_win->Hide();
    }
}

void CVideoDlg::ClearSizer()
{
    int i = 0;
    int n = sqrt(m_videoOldNum);
    for (int x=0; x<n; x++)//行
    {
        for (int y=0; y<n; y++)//列
        {
            m_videoWin[i].video_win->Hide();
            ++i;
        }
    }
}

void CVideoDlg::WinLayout()
{
    if (m_videoNum != m_videoOldNum)
    {
		ClearSizer();
		
        int i = 0;
        int n = sqrt(m_videoNum);
        for (int x=0; x<n; x++)//行
        {
            for (int y=0; y<n; y++)//列
            {
                m_videoWin[i].video_win->SetWinNum(m_videoNum, i);
                m_videoWin[i].video_win->Show();
                ++i;
            }
        }
        m_videoOldNum = m_videoNum;
    }

}

void CVideoDlg::OnPaint(wxPaintEvent& event)
{
	//fprintf(stderr, "CVideoDlg::OnPaint \n");
}

void CVideoDlg::OnMove(wxMoveEvent& event)
{
	//fprintf(stderr, "CVideoDlg::OnMove \n");
	SelectWindow(m_forcusWin, true);
}

void CVideoDlg::OnSize(wxSizeEvent &event)
{
    event.Skip();
	fprintf(stderr, "CVideoDlg::OnSize %d, %d\n",GetParent()->GetSize().GetWidth() - 251
		, GetParent()->GetSize().GetHeight() - m_nAdjustHeight - 42);
    SetSize(251, 42, GetParent()->GetSize().GetWidth() - 251, GetParent()->GetSize().GetHeight() - m_nAdjustHeight - 42);
    WinLayout();
    for (int i=0; i<m_videoNum; i++)
	{
        wxPostEvent(m_videoWin[i].video_win, event);
	}
	SelectWindow(m_forcusWin, true);

    //fprintf(stderr, "CVideoDlg::OnSize \n");
}

void CVideoDlg::OnMouseLeftDown(wxMouseEvent &event)
{
    event.Skip();
    if (event.GetEventObject() != this)
    {
		wxWindow *curWin = (wxWindow *)event.GetEventObject();
		if (m_forcusWin != NULL && m_forcusWin != curWin)
        {
			SelectWindow(m_forcusWin, false);
        }
        m_forcusWin = curWin;
        ((CVideoDlg *)m_forcusWin->GetParent())->m_curResid = ((CVideoWin *)m_forcusWin)->GetResid();
		SelectWindow(m_forcusWin, true);
    }
    //fprintf(stderr, "CVideoDlg::OnMouseLeftDown %s\n", m_curResid.c_str());
}

void CVideoDlg::SelectWindow(wxWindow *pWindow, bool bSelected)
{
	//fprintf(stderr, "SelectWindow::OnPaint %d\n", bSelected);
	if (m_forcusWin != NULL)
	{
		wxRect rect = pWindow->GetScreenRect();
		wxScreenDC *pDC = new wxScreenDC();
		if (bSelected)
			pDC->SetPen(wxPen(wxColour(255,0,0), 2, wxSTIPPLE));
		else
			pDC->SetPen(wxPen(wxColor(226, 237, 241), 2, wxSTIPPLE));

		wxPoint pos1 = rect.GetTopLeft() - wxPoint(2, 2);
		wxPoint pos2 = rect.GetTopRight() - wxPoint(2, 2);
		wxPoint pos3 = rect.GetBottomLeft() - wxPoint(2, 2);
		wxPoint pos4 = rect.GetBottomRight() - wxPoint(2, 2);
		//fprintf(stderr, "%d-%d %d-%d %d-%d %d-%d\n", pos1.x, pos1.y, pos2.x, pos2.y,
		//				pos3.x, pos3.y, pos4.x, pos4.y);
		pDC->DrawLine(pos1.x, pos1.y, pos2.x, pos2.y);
		pDC->DrawLine(pos1.x, pos1.y, pos3.x, pos3.y);
		pDC->DrawLine(pos3.x, pos3.y, pos4.x, pos4.y);
		pDC->DrawLine(pos2.x, pos2.y, pos4.x, pos4.y);
	}
}
