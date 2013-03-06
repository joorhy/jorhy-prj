#include "x_ptzctl.h"
#include "x_title.h"
#include "j_type.h"
#include "jo_frame.h"
#include "x_video.h"

#include <math.h>
#include <wx/tooltip.h>

BEGIN_EVENT_TABLE(CXPtzCtl, wxWindow)
    EVT_SIZE(CXPtzCtl::OnSize)
END_EVENT_TABLE()

CXPtzCtl::CXPtzCtl(wxWindow *parent)
: wxWindow(parent, wxID_ANY)
{
    SetBackgroundColour(wxColour(226, 237, 241));
    m_nSpeed = 0;
    m_nPreset = 0;
    m_nAux = 0;
    Init();
}

CXPtzCtl::~CXPtzCtl()
{

}

void CXPtzCtl::Init()
{
    //Title
    m_pTitleWin = new CXTitle(this, _("云镜控制"), wxString::FromUTF8("./images/icon/win_ptz.png"));
    //PTZ方向界面
    m_ptz = new CPtz(this);
    //速度调节
    m_slider = new CSlider(this);
    m_ptzSpeedText = new wxStaticText(this, wxID_ANY, _("云镜控制速度"));
    //镜头调节
    m_zoom = new CBtn(this, 1, wxString::FromUTF8("./images/ptz_zoom_in.png"),
                       wxString::FromUTF8("./images/ptz_zoom_out.png"));
    m_focus = new CBtn(this, 2, wxString::FromUTF8("./images/ptz_focus_zoom_in.png"),
                       wxString::FromUTF8("./images/ptz_focus_zoom_out.png"));
    m_iris = new CBtn(this, 3, wxString::FromUTF8("./images/ptz_aperture_zoom_in.png"),
                       wxString::FromUTF8("./images/ptz_aperture_zoom_out.png"));
    //预置位及辅助调节
    m_preset = new CBox(this, 5, wxString::FromUTF8("./images/ptz_set.png"),
                       wxString::FromUTF8("./images/ptz_view.png"));
    m_aux = new CBox(this, 6, wxString::FromUTF8("./images/ptz_aux_on.png"),
                   wxString::FromUTF8("./images/ptz_aux_off.png"));
}

void CXPtzCtl::PtzStart(int nCmd)
{
    int nUserId = ((CBrFrame *)GetParent())->GetUserId();
    std::string strResid = ((CVideoDlg *)((CBrFrame *)GetParent())->GetVideoDlg())->GetCurResid();
    if ((nCmd >= 1 && nCmd <= 8) || (nCmd >= 12 && nCmd <= 18))
    {
        CBrFrame::GetSdk().PtzControl(nUserId, strResid.c_str(), nCmd, m_nSpeed);
    }
    else if (nCmd >= 9 && nCmd <= 11)
    {
        CBrFrame::GetSdk().PtzControl(nUserId, strResid.c_str(), nCmd, m_nPreset);
    }
    else if (nCmd >= 19 && nCmd <= 20)
    {
        CBrFrame::GetSdk().PtzControl(nUserId, strResid.c_str(), nCmd, m_nAux);
    }
}

void CXPtzCtl::PtzStop(int nCmd)
{
    int nUserId = ((CBrFrame *)GetParent())->GetUserId();
    std::string strResid = ((CVideoDlg *)((CBrFrame *)GetParent())->GetVideoDlg())->GetCurResid();
    if ((nCmd >= 1 && nCmd <= 8) || (nCmd >= 12 && nCmd <= 18))
    {
        CBrFrame::GetSdk().PtzControl(nUserId, strResid.c_str(), nCmd, 0);
    }
}

void CXPtzCtl::OnSize(wxSizeEvent &event)
{
    event.Skip();
    int w = GetParent()->GetSize().GetWidth();
    int h = GetParent()->GetSize().GetHeight();
    SetSize(0, h - 196, 251, 196);
    wxPostEvent(m_pTitleWin, event);
    wxPostEvent(m_ptz, event);
    wxPostEvent(m_slider, event);
    m_ptzSpeedText->SetSize(11, 165, 100, 12);
    m_preset->SetSize(200, 30, 127, 23);
    m_aux->SetSize(200, 57, 127, 23);

    m_zoom->SetSize(118, 97, 127, 23);
    m_focus->SetSize(118, 125, 127, 23);
    m_iris->SetSize(118, 153, 127, 23);

    return;
}


BEGIN_EVENT_TABLE(CXPtzCtl::CPtz, wxWindow)
    EVT_SIZE(CXPtzCtl::CPtz::OnSize)
    EVT_PAINT(CXPtzCtl::CPtz::OnPaint)
    EVT_MOTION(CXPtzCtl::CPtz::OnMouseMotion)
    EVT_LEFT_DOWN(CXPtzCtl::CPtz::OnMouseLeftDown)
    EVT_LEFT_UP(CXPtzCtl::CPtz::OnMouseLeftUp)
    EVT_LEAVE_WINDOW(CXPtzCtl::CPtz::OnMouseLeaveWindow)
END_EVENT_TABLE()

#define PI (3.14159)
CXPtzCtl::CPtz::CPtz(wxWindow *parent)
: wxWindow(parent, wxID_ANY)
{
    SetBackgroundColour(wxColour(226, 237, 241));
    Init();
}

CXPtzCtl::CPtz::~CPtz()
{

}

void CXPtzCtl::CPtz::Init()
{
    m_ptzBmp.LoadFile(wxString::FromUTF8("./images/ptz.png"), wxBITMAP_TYPE_PNG);
    m_width = m_ptzBmp.GetWidth() / 20;
    m_height = m_ptzBmp.GetHeight();
    m_CurBmp = m_ptzBmp.GetSubBitmap(wxRect(0, 0, m_width, m_height));
}

int CXPtzCtl::CPtz::GetBmpIndex(float x, float y)
{
    int index = 0;
    double length = sqrt(x * x + y * y);
    if (length <= (m_width / 4))
    {
        index = 1;
    }
    else if (length > (m_width / 2))
    {
        index = 0;
    }
    else
    {
        if (x == 0)
        {
            if (y > 0)
                index = 3;
            else
                index = 11;
        }
        else if (x > 0)
        {
            float tanVal = y / x;
            if (tanVal >= tanf(67.5 * PI / 180))
                index = 3;
            else if (tanVal >= tanf(22.5 * PI / 180) && tanVal < tanf(67.5 * PI / 180))
                index = 5;
            else if (tanVal >= tanf(-22.5 * PI / 180) && tanVal < tanf(22.5 * PI / 180))
                index = 7;
            else if (tanVal >= tanf(-67.5 * PI / 180) && tanVal < tanf(-22.5 * PI / 180))
                index = 9;
            else if (tanVal < tanf(-67.5 * PI / 180))
                index = 11;
            else
                assert(false);
        }
        else
        {
            float test = tanf(45 * PI / 180);
            float test2 = tanf(100.5 * PI / 180);
            float tanVal = y / x;
            if (tanVal < tanf(112.5 * PI / 180))
                index = 3;
            else if (tanVal >= tanf(112.5 * PI / 180) && tanVal < tanf(157.5 * PI / 180))
                index = 17;
            else if (tanVal >= tanf(157.5 * PI / 180) && tanVal < tanf(-157.5 * PI / 180))
                index = 15;
            else if (tanVal >= tanf(-157.5 * PI / 180) && tanVal < tanf(-112.5 * PI / 180))
                index = 13;
            else if (tanVal > tanf(-112.5 * PI / 180))
                index = 11;
            else
                assert(false);
        }
    }
    return index;
}

void CXPtzCtl::CPtz::RefreshBmp(int x, int y, int state)
{
    int index = GetBmpIndex(x, y);
    int command = 0;
    switch (index)
    {
        case 1:
            SetToolTip(wxString::FromUTF8("自动"));
            command = jo_ptz_pan_auto;
            break;
        case 3:
            SetToolTip(wxString::FromUTF8("向上"));
            command = jo_ptz_up;
            break;
        case 5:
            SetToolTip(wxString::FromUTF8("右上"));
            command = jo_ptz_up_right;
            break;
        case 7:
            SetToolTip(wxString::FromUTF8("向右"));
            command = jo_ptz_right;
            break;
        case 9:
            SetToolTip(wxString::FromUTF8("右下"));
            command = jo_ptz_down_right;
            break;
        case 11:
            SetToolTip(wxString::FromUTF8("向下"));
            command = jo_ptz_down;
            break;
        case 13:
            SetToolTip(wxString::FromUTF8("左下"));
            command = jo_ptz_down_left;
            break;
        case 15:
            SetToolTip(wxString::FromUTF8("向左"));
            command = jo_ptz_left;
            break;
        case 17:
            SetToolTip(wxString::FromUTF8("左上"));
            command = jo_ptz_up_left;
            break;
    }
    if (state == 0)
    {
        m_CurBmp = m_ptzBmp.GetSubBitmap(wxRect(m_width * index, 0, m_width, m_height));
    }
    else if (state == 1)
    {
        ((CXPtzCtl *)GetParent())->PtzStart(command);
        m_CurBmp = m_ptzBmp.GetSubBitmap(wxRect(m_width * (index + 1), 0, m_width, m_height));
    }
    else if (state == 2)
    {
        ((CXPtzCtl *)GetParent())->PtzStop(command);
        m_CurBmp = m_ptzBmp.GetSubBitmap(wxRect(m_width * index, 0, m_width, m_height));
    }

    Refresh();
}

void CXPtzCtl::CPtz::OnPaint(wxPaintEvent& event)
{
    wxPaintDC *pDC = new wxPaintDC(this);
    wxPen pen;
    pen.SetStyle(wxTRANSPARENT);
    pDC->SetPen(pen);
    pDC->SetBrush(wxBrush(GetBackgroundColour()));
    pDC->DrawRectangle(0, 0, GetSize().GetWidth(), GetSize().GetHeight());
    pDC->DrawBitmap(m_CurBmp, 0, 0, true);
}

void CXPtzCtl::CPtz::OnSize(wxSizeEvent &event)
{
    SetSize(5, 30, m_width, m_height);

    return;
}

void CXPtzCtl::CPtz::OnMouseMotion(wxMouseEvent &event)
{
    wxPoint pst = event.GetPosition();
    RefreshBmp(pst.x - m_width / 2, m_height / 2 - pst.y, 0);
}

void CXPtzCtl::CPtz::OnMouseLeftDown(wxMouseEvent &event)
{
    wxPoint pst = event.GetPosition();
    RefreshBmp(pst.x - m_width / 2, m_height / 2 - pst.y, 1);
}

void CXPtzCtl::CPtz::OnMouseLeftUp(wxMouseEvent &event)
{
    wxPoint pst = event.GetPosition();
    RefreshBmp(pst.x - m_width / 2, m_height / 2 - pst.y, 2);
}

void CXPtzCtl::CPtz::OnMouseLeaveWindow(wxMouseEvent &event)
{
    RefreshBmp(m_width, m_height, 0);
}

BEGIN_EVENT_TABLE(CXPtzCtl::CSlider, wxControl)
    EVT_PAINT(CXPtzCtl::CSlider::OnPaint)
    EVT_SIZE(CXPtzCtl::CSlider::OnSize)
    EVT_MOTION(CXPtzCtl::CSlider::OnMouseMotion)
    EVT_LEFT_DOWN(CXPtzCtl::CSlider::OnMouseLeftDown)
    EVT_LEFT_UP(CXPtzCtl::CSlider::OnMouseLeftUp)
END_EVENT_TABLE()

CXPtzCtl::CSlider::CSlider(wxWindow *parent)
    : wxControl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetBackgroundColour(wxColor(226, 237, 241));
    Init();
}

CXPtzCtl::CSlider::~CSlider()
{

}

void CXPtzCtl::CSlider::Init()
{
    m_leftBmp.LoadFile(wxString::FromUTF8("./images/slider_left.png"), wxBITMAP_TYPE_PNG);
    m_rightBmp.LoadFile(wxString::FromUTF8("./images/slider_right.png"), wxBITMAP_TYPE_PNG);
    m_centerBmp.LoadFile(wxString::FromUTF8("./images/slider_center.png"), wxBITMAP_TYPE_PNG);
    m_barBmp.LoadFile(wxString::FromUTF8("./images/slider_bar.png"), wxBITMAP_TYPE_PNG);
    m_width = 100;
    m_height = m_barBmp.GetHeight();
    m_bgWidth = m_leftBmp.GetWidth();
    m_bgHeight = m_centerBmp.GetHeight();
    m_barWidth = m_barBmp.GetWidth();
    m_isSelected = false;
    m_pos = m_width / 2;
    m_speed = 128;
    ((CXPtzCtl *)GetParent())->SetSpeed(m_speed);
}

void CXPtzCtl::CSlider::OnPaint(wxPaintEvent& event)
{
    wxPaintDC *dc = new wxPaintDC(this);
    wxPen pen;
    pen.SetStyle(wxTRANSPARENT);
    dc->SetPen(pen);

    dc->SetBrush(m_centerBmp);
    dc->DrawRectangle(m_bgWidth, m_height/2 - m_bgHeight/2, m_width - 2 * m_bgWidth, m_bgHeight);
    dc->DrawBitmap(m_leftBmp, 0, m_height/2 - m_bgHeight/2, true);
    dc->DrawBitmap(m_rightBmp, m_width - m_bgWidth, m_height/2 - m_bgHeight/2, true);
    dc->DrawBitmap(m_barBmp, m_pos - m_barWidth/2, 0, true);
}

void CXPtzCtl::CSlider::OnSize(wxSizeEvent& event)
{
    SetSize(5, 140, m_width, m_height);
}

void CXPtzCtl::CSlider::OnMouseMotion(wxMouseEvent &event)
{
    wxPoint pst = event.GetPosition();
    if (m_isSelected)
    {
        if (pst.x <= m_barWidth/2)
        {
            m_speed = 1;
            m_pos = m_barWidth/2;
        }
        else if (pst.x >= (100 - m_barWidth/2))
        {
            m_speed = 255;
            m_pos = 100 - m_barWidth/2;
        }
        else
        {
            m_speed = pst.x * 255 / 100;
            m_pos = pst.x;
        }
        ((CXPtzCtl *)GetParent())->SetSpeed(m_speed);
        SetToolTip(wxString::Format(wxT("%d"), m_speed));
        Refresh();
        //fprintf(stderr, "x = %s\n", "ss");
    }
}

void CXPtzCtl::CSlider::OnMouseLeftDown(wxMouseEvent &event)
{
    m_isSelected = true;
    SetToolTip(wxString::Format(wxT("%d"), m_speed));
    //fprintf(stderr, "selected = %d\n", m_isSelected);
}

void CXPtzCtl::CSlider::OnMouseLeftUp(wxMouseEvent &event)
{
    m_isSelected = false;
}

BEGIN_EVENT_TABLE(CXPtzCtl::CBtn, wxWindow)
    EVT_PAINT(CXPtzCtl::CBtn::OnPaint)
    EVT_MOTION(CXPtzCtl::CBtn::OnMouseMotion)
    EVT_LEFT_DOWN(CXPtzCtl::CBtn::OnMouseLeftDown)
    EVT_LEFT_UP(CXPtzCtl::CBtn::OnMouseLeftUp)
    EVT_LEAVE_WINDOW(CXPtzCtl::CBtn::OnMouseLeaveWindow)
END_EVENT_TABLE()

CXPtzCtl::CBtn::CBtn(wxWindow *parent, int flag, const wxString &lbmp, const wxString &rbmp)
: wxWindow(parent, wxID_ANY)
{
    SetBackgroundColour(wxColour(226, 237, 241));

    m_bmpBg.LoadFile(wxString::FromUTF8("./images/ptz_btn_bg.png"), wxBITMAP_TYPE_PNG);
    m_lbmp.LoadFile(lbmp, wxBITMAP_TYPE_PNG);
    m_rbmp.LoadFile(rbmp, wxBITMAP_TYPE_PNG);
    m_flag = flag;

    Init();
}

CXPtzCtl::CBtn::~CBtn()
{

}

void CXPtzCtl::CBtn::Init()
{
    m_lWidth = m_lbmp.GetWidth() / 4;
    m_rWidth = m_rbmp.GetWidth() / 4;
    m_height = m_bmpBg.GetHeight();
    m_lCurBmp = m_lbmp.GetSubBitmap(wxRect(0, 0, m_lWidth, m_height));
    m_rCurBmp = m_rbmp.GetSubBitmap(wxRect(0, 0, m_rWidth, m_height));
}

void CXPtzCtl::CBtn::RefreshBmp(int x, int y, int state)
{
    int nCommand = 0;
    if (x > 0 && x < m_lWidth)
    {
        switch (m_flag)
        {
            case 1:
                SetToolTip(wxString::FromUTF8("放大"));
                nCommand = jo_ptz_zoom_in;
                break;
            case 2:
                SetToolTip(wxString::FromUTF8("拉远"));
                nCommand = jo_ptz_focus_far;
                break;
            case 3:
                SetToolTip(wxString::FromUTF8("光圈打开"));
                nCommand = jo_ptz_iris_open;
                break;
        }
        if (state == 0)
        {
            m_lCurBmp = m_lbmp.GetSubBitmap(wxRect(m_lWidth, 0, m_lWidth, m_height));
        }
        else if (state == 1)
        {
            ((CXPtzCtl *)GetParent())->PtzStart(nCommand);
            m_lCurBmp = m_lbmp.GetSubBitmap(wxRect(m_lWidth * 2, 0, m_lWidth, m_height));
        }
        else if (state == 2)
        {
            ((CXPtzCtl *)GetParent())->PtzStop(nCommand);
            m_lCurBmp = m_lbmp.GetSubBitmap(wxRect(m_lWidth, 0, m_lWidth, m_height));
        }
        m_rCurBmp = m_rbmp.GetSubBitmap(wxRect(0, 0, m_rWidth, m_height));
    }
    else if (x > (127 - m_rWidth) && x < 127)
    {
        switch (m_flag)
        {
            case 1:
                SetToolTip(wxString::FromUTF8("缩小"));
                nCommand = jo_ptz_room_out;
                break;
            case 2:
                SetToolTip(wxString::FromUTF8("拉近"));
                nCommand = jo_ptz_focus_near;
                break;
            case 3:
                SetToolTip(wxString::FromUTF8("光圈关闭"));
                nCommand = jo_ptz_iris_close;
                break;
        }
        if (state == 0)
        {
            m_rCurBmp = m_rbmp.GetSubBitmap(wxRect(m_rWidth, 0, m_rWidth, m_height));
        }
        else if (state == 1)
        {
            ((CXPtzCtl *)GetParent())->PtzStart(nCommand);
            m_rCurBmp = m_rbmp.GetSubBitmap(wxRect(m_rWidth * 2, 0, m_rWidth, m_height));
        }
        else if (state == 2)
        {
            ((CXPtzCtl *)GetParent())->PtzStop(nCommand);
            m_rCurBmp = m_rbmp.GetSubBitmap(wxRect(m_rWidth, 0, m_rWidth, m_height));
        }
        m_lCurBmp = m_lbmp.GetSubBitmap(wxRect(0, 0, m_lWidth, m_height));
    }
    else
    {
        m_lCurBmp = m_lbmp.GetSubBitmap(wxRect(0, 0, m_lWidth, m_height));
        m_rCurBmp = m_rbmp.GetSubBitmap(wxRect(0, 0, m_rWidth, m_height));
    }

    Refresh();
}

void CXPtzCtl::CBtn::OnPaint(wxPaintEvent &event)
{
    wxPaintDC *pdc = new wxPaintDC(this);
    wxPen pen;
    pen.SetStyle(wxTRANSPARENT);

    pdc->SetPen(pen);
    pdc->DrawBitmap(m_bmpBg, 0, 0, true);
    pdc->DrawBitmap(m_lCurBmp, 0, 0, true);
    pdc->DrawBitmap(m_rCurBmp, 127 - m_rWidth, 0, true);
}

void CXPtzCtl::CBtn::OnMouseMotion(wxMouseEvent &event)
{
    wxPoint pst = event.GetPosition();
    RefreshBmp(pst.x, pst.y, 0);
}

void CXPtzCtl::CBtn::OnMouseLeftDown(wxMouseEvent &event)
{
    wxPoint pst = event.GetPosition();
    RefreshBmp(pst.x, pst.y, 1);
}

void CXPtzCtl::CBtn::OnMouseLeftUp(wxMouseEvent &event)
{
    wxPoint pst = event.GetPosition();
    RefreshBmp(pst.x, pst.y, 2);
}

void CXPtzCtl::CBtn::OnMouseLeaveWindow(wxMouseEvent &event)
{
    RefreshBmp(0, 0, 0);
}

BEGIN_EVENT_TABLE(CXPtzCtl::CBox, wxWindow)
    EVT_PAINT(CXPtzCtl::CBox::OnPaint)
    EVT_MOTION(CXPtzCtl::CBox::OnMouseMotion)
    EVT_LEFT_DOWN(CXPtzCtl::CBox::OnMouseLeftDown)
    EVT_LEFT_UP(CXPtzCtl::CBox::OnMouseLeftUp)
    EVT_LEAVE_WINDOW(CXPtzCtl::CBox::OnMouseLeaveWindow)
END_EVENT_TABLE()

CXPtzCtl::CBox::CBox(wxWindow *parent, int flag, const wxString &lbmp, const wxString &rbmp)
    : wxWindow(parent, wxID_ANY)
{
    SetBackgroundColour(wxColour(226, 237, 241));
    m_lbmp.LoadFile(lbmp, wxBITMAP_TYPE_PNG);
    m_rbmp.LoadFile(rbmp, wxBITMAP_TYPE_PNG);
    m_flag = flag;

    Init();
}

CXPtzCtl::CBox::~CBox()
{

}

void CXPtzCtl::CBox::Init()
{
    wxArrayString choices;
    if (m_flag == 5)
    {
        for (int i=1; i<=10; i++)
        {
            choices.Add(wxString::Format(wxT("%d"), i));
        }
        m_comboBox = new wxComboBox(GetParent(), wxID_ANY, wxString::FromUTF8("预置位号")
            , wxDefaultPosition, wxDefaultSize, choices);
    }
    else if (m_flag == 6)
    {
        choices.Add(wxString::FromUTF8("灯光"));
        choices.Add(wxString::FromUTF8("雨刷"));
        choices.Add(wxString::FromUTF8("电源"));
        m_comboBox = new wxComboBox(GetParent(), wxID_ANY, wxString::FromUTF8("辅助开关")
            , wxDefaultPosition, wxDefaultSize, choices, wxCB_READONLY);
    }

    m_comboBox->SetBackgroundColour(GetBackgroundColour());
    m_width = m_lbmp.GetWidth() / 4;
    m_height = m_lbmp.GetHeight();
    m_comboxWidth = 127 - 2 * m_width;
    m_lCurBmp = m_lbmp.GetSubBitmap(wxRect(0, 0, m_width, m_height));
    m_rCurBmp = m_rbmp.GetSubBitmap(wxRect(0, 0, m_width, m_height));

    m_comboBox->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED,
            wxCommandEventHandler(CXPtzCtl::CBox::OnComboBox), NULL, this);
    m_comboBox->Connect( wxEVT_COMMAND_TEXT_UPDATED,
            wxCommandEventHandler(CXPtzCtl::CBox::OnText), NULL, this);
}

void CXPtzCtl::CBox::RefreshBmp(int x, int y, int state)
{
    int nCommand = 0;
    if (x > 0 && x < m_width)
    {
        switch (m_flag)
        {
            case 5:
                nCommand = jo_ptz_pre_set;
                SetToolTip(wxString::FromUTF8("设置预置位"));
                break;
            case 6:
                nCommand = jo_ptz_aux_on;
                SetToolTip(wxString::FromUTF8("打开辅助开关"));
                break;
        }
        if (state == 0)
        {
            m_lCurBmp = m_lbmp.GetSubBitmap(wxRect(m_width, 0, m_width, m_height));
        }
        else if (state == 1)
        {
            ((CXPtzCtl *)GetParent())->PtzStart(nCommand);
            m_lCurBmp = m_lbmp.GetSubBitmap(wxRect(m_width * 2, 0, m_width, m_height));
        }
        m_rCurBmp = m_rbmp.GetSubBitmap(wxRect(0, 0, m_width, m_height));
    }
    else if (x > m_width && x < m_width * 2)
    {
        switch (m_flag)
        {
            case 5:
                nCommand = jo_ptz_goto_pre;
                SetToolTip(wxString::FromUTF8("调用预置位"));
                break;
            case 6:
                nCommand = jo_ptz_aux_off;
                SetToolTip(wxString::FromUTF8("关闭辅助开关"));
                break;
        }
        if (state == 0)
        {
            m_rCurBmp = m_rbmp.GetSubBitmap(wxRect(m_width, 0, m_width, m_height));
        }
        else if (state == 1)
        {
            ((CXPtzCtl *)GetParent())->PtzStart(nCommand);
            m_rCurBmp = m_rbmp.GetSubBitmap(wxRect(m_width * 2, 0, m_width, m_height));
        }
        m_lCurBmp = m_lbmp.GetSubBitmap(wxRect(0, 0, m_width, m_height));
    }
    else
    {
        m_lCurBmp = m_lbmp.GetSubBitmap(wxRect(0, 0, m_width, m_height));
        m_rCurBmp = m_rbmp.GetSubBitmap(wxRect(0, 0, m_width, m_height));
    }

    Refresh();
}

void CXPtzCtl::CBox::UpdatePramValue()
{
    //fprintf(stderr, "CXPtzCtl::CBox::UpdatePramValue %d\n", m_flag);
    switch (m_flag)
    {
        case 5:
        {
            long pos = 0;
            m_comboBox->GetValue().ToLong(&pos);
            //fprintf(stderr, "CXPtzCtl::CBox::UpdatePramValue %d", pos);
            ((CXPtzCtl *)GetParent())->SetPreset(pos);
            break;
        }
        case 6:
            //fprintf(stderr, "CXPtzCtl::CBox::UpdatePramValue %d", m_comboBox->GetCurrentSelection());
            ((CXPtzCtl *)GetParent())->SetAux(m_comboBox->GetCurrentSelection() + 1);
            break;
    }
}

void CXPtzCtl::CBox::OnPaint(wxPaintEvent &event)
{
    if (m_flag == 5)
        m_comboBox->SetSize(118, 30, 80, 22);
    else if (m_flag == 6)
        m_comboBox->SetSize(118, 57, 80, 22);

    wxPaintDC *pdc = new wxPaintDC(this);
    wxPen pen;
    pen.SetStyle(wxTRANSPARENT);

    pdc->SetPen(pen);
    pdc->DrawBitmap(m_lCurBmp, 0, 0, true);
    pdc->DrawBitmap(m_rCurBmp, m_width, 0, true);
}

void CXPtzCtl::CBox::OnMouseMotion(wxMouseEvent &event)
{
    wxPoint pst = event.GetPosition();
    RefreshBmp(pst.x, pst.y, 0);
}

void CXPtzCtl::CBox::OnMouseLeftDown(wxMouseEvent &event)
{
    wxPoint pst = event.GetPosition();
    RefreshBmp(pst.x, pst.y, 1);
}

void CXPtzCtl::CBox::OnMouseLeftUp(wxMouseEvent &event)
{
    wxPoint pst = event.GetPosition();
    RefreshBmp(pst.x, pst.y, 0);
}

void CXPtzCtl::CBox::OnMouseLeaveWindow(wxMouseEvent &event)
{
    RefreshBmp(0, 0, 0);
}

void CXPtzCtl::CBox::OnComboBox(wxCommandEvent &event)
{
    //fprintf(stderr, "CXPtzCtl::CBox::OnComboBox %d\n", m_flag);
    UpdatePramValue();
}

void CXPtzCtl::CBox::OnText(wxCommandEvent &event)
{
    //fprintf(stderr, "CXPtzCtl::CBox::OnText\n");
    UpdatePramValue();
}
