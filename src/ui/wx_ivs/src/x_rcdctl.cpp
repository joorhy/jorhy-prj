#include "x_rcdctl.h"
#include "x_title.h"

BEGIN_EVENT_TABLE(CXRcdCtl, wxWindow)
	EVT_SIZE(CXRcdCtl::OnSize)
END_EVENT_TABLE()

CXRcdCtl::CXRcdCtl(wxWindow *parent)
: wxWindow(parent, wxID_ANY)
{
    SetBackgroundColour(wxColor(226, 237, 241));
    Init();
}

CXRcdCtl::~CXRcdCtl()
{

}

const wxDateTime &CXRcdCtl::GetDateTime() const
{
	return m_dateCtrl->GetDate();
}

void CXRcdCtl::SetDateTime(const wxDateTime &dataTime)
{
	m_dateCtrl->SetDate(dataTime);
	m_pRcdTime->SetDateTime(dataTime);
	m_pRcdTime->Refresh();
}

void CXRcdCtl::Init()
{
	//Title
    m_pTitleWin = new CXTitle(this, _("回放控制"), wxString::FromUTF8("./images/icon/win_rcdnav.png"));
	//回放控制
	m_pRcdCtrl = new RcdCtrl(this);
	//速度调节
    m_slider = new CSlider(this);
	//日期窗口
	m_dateCtrl = new wxCalendarCtrl(this, wxID_ANY, wxDefaultDateTime, 
		wxDefaultPosition, wxDefaultSize, wxCAL_SEQUENTIAL_MONTH_SELECTION);
	m_dateCtrl->SetBackgroundColour(wxColor(226, 237, 241));
	//时间显示域
	m_pRcdTime = new RcdTime(this);
	m_pRcdTime->SetDateTime(m_dateCtrl->GetDate());
}

void CXRcdCtl::OnSize(wxSizeEvent &event)
{
	event.Skip();
    int w = GetParent()->GetSize().GetWidth();
    int h = GetParent()->GetSize().GetHeight();
    SetSize(0, h - 310, 251, 310);
    wxPostEvent(m_pTitleWin, event);
	wxPostEvent(m_pRcdTime, event);
	m_dateCtrl->SetSize(0, 157, 251, 163);
}


BEGIN_EVENT_TABLE(CXRcdCtl::RcdTime, wxWindow)
    EVT_PAINT(CXRcdCtl::RcdTime::OnPaint)
	EVT_SIZE(CXRcdCtl::RcdTime::OnSize)
END_EVENT_TABLE()

CXRcdCtl::RcdTime::RcdTime(wxWindow* parent)
: wxWindow(parent, wxID_ANY)
{
	SetBackgroundColour(wxColour(226, 237, 241));
	Init();
}

CXRcdCtl::RcdTime::~RcdTime()
{
	
}

void CXRcdCtl::RcdTime::OnPaint(wxPaintEvent& event)
{
	wxPen pen;
    pen.SetStyle(wxTRANSPARENT);
    wxPaintDC *dc = new wxPaintDC(this);
    dc->SetPen(pen);
    dc->SetBrush(m_mBmpDate);
    dc->DrawRectangle(m_nBmpWidth, 0, 168 - 2 * m_nBmpWidth, m_nBmpHeight);
    dc->DrawBitmap(m_lBmpDate, 0, 0, true);
    dc->DrawBitmap(m_rBmpDate, 168 - m_nBmpWidth, 0, true);

    wxFont font(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(wxColour(255, 255, 255));
    wxString textDate(wxString::Format(_("%04d-%02d-%02d"), m_dateTime.GetYear(), 
				m_dateTime.GetMonth() + 1, m_dateTime.GetDay()));
	
    wxCoord w;
    wxCoord h;
    dc->GetTextExtent(textDate, &w, &h);
    dc->DrawLabel(textDate, wxRect((168 - w)/2, 5, w, h), wxALIGN_TOP);

    wxFont font2(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    dc->SetFont(font2);
    wxString textTime(wxString::Format(_("%02d:%02d:%02d"), m_dateTime.GetHour(), 
				m_dateTime.GetMinute(), m_dateTime.GetSecond()));
    dc->SetTextForeground(wxColour(255, 255, 255));
    dc->DrawLabel(textTime, GetClientRect(), wxALIGN_BOTTOM | wxALIGN_CENTER);	
}

void CXRcdCtl::RcdTime::OnSize(wxSizeEvent& event)
{
	SetSize(42, 26, 168, m_nBmpHeight);
    Refresh();
}

void CXRcdCtl::RcdTime::Init()
{
    m_lBmpDate.LoadFile(wxString::FromUTF8("./images/rcdtime_left.png"), wxBITMAP_TYPE_PNG);
    m_mBmpDate.LoadFile(wxString::FromUTF8("./images/rcdtime_middle.png"), wxBITMAP_TYPE_PNG);
    m_rBmpDate.LoadFile(wxString::FromUTF8("./images/rcdtime_right.png"), wxBITMAP_TYPE_PNG);	
	m_nBmpHeight = m_mBmpDate.GetHeight();
	m_nBmpWidth = m_lBmpDate.GetWidth();
}

BEGIN_EVENT_TABLE(CXRcdCtl::RcdCtrl, wxWindow)
    EVT_PAINT(CXRcdCtl::RcdCtrl::OnPaint)
	EVT_SIZE(CXRcdCtl::RcdCtrl::OnSize)
	EVT_MOTION(CXRcdCtl::RcdCtrl::OnMouseMotion)
    EVT_LEFT_DOWN(CXRcdCtl::RcdCtrl::OnMouseLeftDown)
    EVT_LEFT_UP(CXRcdCtl::RcdCtrl::OnMouseLeftUp)
	EVT_LEAVE_WINDOW(CXRcdCtl::RcdCtrl::OnMouseLeaveWindow)
END_EVENT_TABLE()

const char *RcdCtlDes[] = { "", "播放", "暂停", "跳到最前面","单帧向后", 
							"跳到现在", "单帧向前", "跳到最后面"};

CXRcdCtl::RcdCtrl::RcdCtrl(wxWindow* parent)
    : wxWindow(parent, wxID_ANY)
{
	m_nCurIndex = 0;
	m_isSelected = false;
    Init();
}

CXRcdCtl::RcdCtrl::~RcdCtrl()
{

}

void CXRcdCtl::RcdCtrl::Init()
{
    m_lbmpCtrl.LoadFile(wxString::FromUTF8("./images/vcontrol_left.png"), wxBITMAP_TYPE_PNG);
    m_mbmpCtrl.LoadFile(wxString::FromUTF8("./images/vcontrol_middle.png"), wxBITMAP_TYPE_PNG);
    m_rbmpCtrl.LoadFile(wxString::FromUTF8("./images/vcontrol_right.png"), wxBITMAP_TYPE_PNG);
    m_bmpCtrl[1].LoadFile(wxString::FromUTF8("./images/v_play.png"), wxBITMAP_TYPE_PNG);
    m_bmpCtrl[2].LoadFile(wxString::FromUTF8("./images/v_pause.png"), wxBITMAP_TYPE_PNG);
    m_bmpCtrl[3].LoadFile(wxString::FromUTF8("./images/v_prev.png"), wxBITMAP_TYPE_PNG);
    m_bmpCtrl[4].LoadFile(wxString::FromUTF8("./images/v_speed_down.png"), wxBITMAP_TYPE_PNG);
    m_bmpCtrl[5].LoadFile(wxString::FromUTF8("./images/rcd_now.png"), wxBITMAP_TYPE_PNG);
    m_bmpCtrl[6].LoadFile(wxString::FromUTF8("./images/v_speed_up.png"), wxBITMAP_TYPE_PNG);
	m_bmpCtrl[7].LoadFile(wxString::FromUTF8("./images/v_next.png"), wxBITMAP_TYPE_PNG);

	m_nWidth = m_bmpCtrl[1].GetWidth() / 4;
	m_nHeight = m_mbmpCtrl.GetHeight();
	m_bgWidth = m_lbmpCtrl.GetWidth();
}

void CXRcdCtl::RcdCtrl::RefreshRcdCtrl(int x, int y)
{
	if (x > m_bgWidth && x < 167 - m_bgWidth)
	{
		m_nCurIndex = ((x - m_bgWidth) / m_nWidth) + 1;
		if (m_isSelected)
		{
			m_bmpCurCtrl = m_bmpCtrl[m_nCurIndex].GetSubBitmap(wxRect(m_nWidth * 2, 0, m_nWidth, m_nHeight));
		}
		else
		{
			m_bmpCurCtrl = m_bmpCtrl[m_nCurIndex].GetSubBitmap(wxRect(m_nWidth, 0, m_nWidth, m_nHeight));
		}
		SetToolTip(wxString::FromUTF8(RcdCtlDes[m_nCurIndex]));
	}
	else
	{
		m_nCurIndex = 0;
	}
	Refresh();
}

void CXRcdCtl::RcdCtrl::OnPaint(wxPaintEvent &event)
{
    wxPen pen;
    pen.SetStyle(wxTRANSPARENT);
    wxPaintDC *ctrl_dc = new wxPaintDC(this);
    ctrl_dc->SetPen(pen);
    ctrl_dc->SetBrush(m_mbmpCtrl);
    ctrl_dc->DrawRectangle(m_bgWidth, 0, 167 - m_bgWidth * 2, m_nHeight);
    ctrl_dc->DrawBitmap(m_lbmpCtrl, 0, 0, true);	
	for (int i=1, n=0; i<=7; i++,n++)
	{
		if (m_nCurIndex > 0 && m_nCurIndex == i)
			ctrl_dc->DrawBitmap(m_bmpCurCtrl, m_bgWidth + n * m_nWidth, 0, true);
		else
			ctrl_dc->DrawBitmap(m_bmpCtrl[i], m_bgWidth + n * m_nWidth, 0, true);
	}
	ctrl_dc->DrawBitmap(m_rbmpCtrl, 167 - m_bgWidth, 0, true);
}

void CXRcdCtl::RcdCtrl::OnSize(wxSizeEvent& event)
{
	SetSize(42, 75, 167, m_nHeight);
    Refresh();
}

void CXRcdCtl::RcdCtrl::OnMouseMotion(wxMouseEvent &event)
{
    wxPoint pst = event.GetPosition();
	RefreshRcdCtrl(pst.x, pst.y);
}

void CXRcdCtl::RcdCtrl::OnMouseLeftDown(wxMouseEvent &event)
{
    m_isSelected = true;
	wxPoint pst = event.GetPosition();
	RefreshRcdCtrl(pst.x, pst.y);
}

void CXRcdCtl::RcdCtrl::OnMouseLeftUp(wxMouseEvent &event)
{
    m_isSelected = false;
    wxPoint pst = event.GetPosition();
	RefreshRcdCtrl(pst.x, pst.y);
}

void CXRcdCtl::RcdCtrl::OnMouseLeaveWindow(wxMouseEvent &event)
{
	m_isSelected = false;
	RefreshRcdCtrl(0, 0);
}

BEGIN_EVENT_TABLE(CXRcdCtl::CSlider, wxControl)
    EVT_PAINT(CXRcdCtl::CSlider::OnPaint)
    EVT_SIZE(CXRcdCtl::CSlider::OnSize)
    EVT_MOTION(CXRcdCtl::CSlider::OnMouseMotion)
    EVT_LEFT_DOWN(CXRcdCtl::CSlider::OnMouseLeftDown)
    EVT_LEFT_UP(CXRcdCtl::CSlider::OnMouseLeftUp)
END_EVENT_TABLE()

const char *RcdSpeed[] = { "1/8x", "1/4x", "1/2x", "1","2x", "4x", "8x"};
const int adjust_len = 14;

CXRcdCtl::CSlider::CSlider(wxWindow *parent)
    : wxControl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetBackgroundColour(wxColor(226, 237, 241));
    Init();
}

CXRcdCtl::CSlider::~CSlider()
{

}

void CXRcdCtl::CSlider::Init()
{
    m_leftBmp.LoadFile(wxString::FromUTF8("./images/slider_left.png"), wxBITMAP_TYPE_PNG);
    m_rightBmp.LoadFile(wxString::FromUTF8("./images/slider_right.png"), wxBITMAP_TYPE_PNG);
    m_centerBmp.LoadFile(wxString::FromUTF8("./images/slider_center.png"), wxBITMAP_TYPE_PNG);
    m_barBmp.LoadFile(wxString::FromUTF8("./images/slider_bar.png"), wxBITMAP_TYPE_PNG);
    m_width = 168 + 2 * adjust_len;
    m_height = m_barBmp.GetHeight();
    m_bgWidth = m_leftBmp.GetWidth();
    m_bgHeight = m_centerBmp.GetHeight();
    m_barWidth = m_barBmp.GetWidth();
    m_isSelected = false;
    m_pos = m_width / 2;
    //m_speed = 128;
    //((CXRcdCtl *)GetParent())->SetSpeed(m_speed);
}

void CXRcdCtl::CSlider::RefreshRcdSpeed(int x, int y)
{
	if (m_isSelected)
    {
        if (x >= 0 && x < 28)
        {
            m_speed = 1;
            m_pos = 14;
        }
        else if (x >= 28 && x < 56)
        {
            m_speed = 255;
            m_pos = 42;
        }
        else if (x >= 56 && x < 84)
        {
            m_speed = 255;
            m_pos = 70;
        }
		else if (x >= 84 && x < 112)
        {
            m_speed = 255;
            m_pos = 98;
        }
		else if (x >= 112 && x < 140)
        {
            m_speed = 255;
            m_pos = 126;
        }
		else if (x >= 140 && x < 168)
        {
            m_speed = 255;
            m_pos = 156;
        }
		else if (x >= 168 && x < 196)
        {
            m_speed = 255;
            m_pos = 184;
        }
        Refresh();
	}
}

void CXRcdCtl::CSlider::OnPaint(wxPaintEvent& event)
{
    wxPaintDC *dc = new wxPaintDC(this);
    wxPen pen;
    pen.SetStyle(wxTRANSPARENT);
    dc->SetPen(pen);

    dc->SetBrush(m_centerBmp);
    dc->DrawRectangle(m_bgWidth + adjust_len, m_height/2 - m_bgHeight/2, m_width - adjust_len * 2 - 2 * m_bgWidth, m_bgHeight);
    dc->DrawBitmap(m_leftBmp, adjust_len, m_height/2 - m_bgHeight/2, true);
    dc->DrawBitmap(m_rightBmp, m_width - m_bgWidth - adjust_len, m_height/2 - m_bgHeight/2, true);
    dc->DrawBitmap(m_barBmp, m_pos - m_barWidth/2, 0, true);
	
	wxFont font(6, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(wxColour(0, 0, 0));
	
	wxCoord w;
    wxCoord h;
	for (int i=0; i<7; i++)
	{
		dc->GetTextExtent(wxString::FromUTF8(RcdSpeed[i]), &w, &h);
		dc->DrawLabel(wxString::FromUTF8(RcdSpeed[i]), wxRect(i * 28 - w / 2 + adjust_len, m_height, w, h), wxALIGN_TOP);
	}
}

void CXRcdCtl::CSlider::OnSize(wxSizeEvent& event)
{
    SetSize(42 - adjust_len, 110, m_width, m_height * 2);
}

void CXRcdCtl::CSlider::OnMouseMotion(wxMouseEvent &event)
{
    wxPoint pst = event.GetPosition();
    RefreshRcdSpeed(pst.x, pst.y);
}

void CXRcdCtl::CSlider::OnMouseLeftDown(wxMouseEvent &event)
{
    m_isSelected = true;
	wxPoint pst = event.GetPosition();
    RefreshRcdSpeed(pst.x, pst.y);
}

void CXRcdCtl::CSlider::OnMouseLeftUp(wxMouseEvent &event)
{
    m_isSelected = false;
}