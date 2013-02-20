#include "jo_frame.h"
#include "x_toolwin.h"
#include "x_catalog.h"
#include "x_video.h"
#include "x_ptzctl.h"
#include "x_rcdctl.h"
#include "x_rcd_slider.h"

#include <stdio.h>
#include <wx/treectrl.h>
#include <wx/sashwin.h>

CXSdk CBrFrame::m_sdk;

BEGIN_EVENT_TABLE(CBrFrame, wxFrame)
    EVT_CLOSE(CBrFrame::OnClose)
    EVT_MOVE(CBrFrame::OnMove)
    EVT_SIZE(CBrFrame::OnSize)
END_EVENT_TABLE()

CBrFrame::CBrFrame(wxFrame *parent, const wxString& title, wxApp *pApp, int userid)
    : wxFrame(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize/*, wxBORDER_THEME*/)
{
    wxIcon icoApp(wxString::FromUTF8("./images/icon/jo_browser.ico"), wxBITMAP_TYPE_ICO);
    SetIcon(icoApp);
	//SetForegroundColour(wxColor(242, 243, 247));
    SetBackgroundColour(wxColor(242, 243, 247));
    m_app = pApp;
    SetMinSize(wxSize(800, 600));

    m_userId = userid;
	m_nCurToolWin = 0;
	m_nOldToolWin = 1;

    Init();
}

CBrFrame::~CBrFrame()
{
    Deinit();
}

void CBrFrame::OnClose(wxCloseEvent &event)
{
    m_app->ExitMainLoop();
}

void CBrFrame::OnMove(wxMoveEvent &event)
{
    event.Skip();
	if (m_nCurToolWin == 0)//实时预览
	{
		//ShowRealView();
		//wxPostEvent(m_pCatalogDlg, event);
		//wxPostEvent(m_pPtzDlg, event);
		wxPostEvent(m_pVideoDlg, event);
	}
	else if (m_nCurToolWin == 1)//历史回放
	{
		//ShowHistoryUI();
		//wxPostEvent(m_pCatalogDlg, event);
		//wxPostEvent(m_pRcdDlg, event);
		wxPostEvent(m_pVideoDlg, event);
		//wxPostEvent(m_pRcdSlider, event);
	}
}

void CBrFrame::OnSize(wxSizeEvent &event)
{
    event.Skip();
    //fprintf(stderr, "CBrFrame w = %d, h = %d\n"
    //        , event.GetSize().GetWidth(), event.GetSize().GetHeight());
    SetSize(event.GetSize());
	wxPostEvent(m_pToolWin, event);
	
	if (m_nCurToolWin != m_nOldToolWin)
	{
		HideAll();
		if (m_nCurToolWin == 0)//实时预览
		{
			ShowRealView();
		}
		else if (m_nCurToolWin == 1)//历史回放
		{
			ShowHistoryUI();
		}
		m_nOldToolWin = m_nCurToolWin;
	}
	wxPostEvent(m_pCatalogDlg, event);
	wxPostEvent(m_pPtzDlg, event);
	wxPostEvent(m_pRcdDlg, event);
	wxPostEvent(m_pVideoDlg, event);
	wxPostEvent(m_pRcdSlider, event);
	Update();

    return;
}

void CBrFrame::OnSelectToolWin(int nToolWin)
{
	m_nCurToolWin = nToolWin;
	//HideAll();
	wxSizeEvent event(GetSize());
	wxPostEvent(this, event);
}

void CBrFrame::Init()
{
	m_pToolWin = new CXToolWin(this);
    m_pCatalogDlg = new CCatalogDlg(this);
    m_pPtzDlg = new CXPtzCtl(this);
	m_pRcdDlg = new CXRcdCtl(this);
    m_pVideoDlg = new CVideoDlg(this);
	m_pRcdSlider = new CXRcdSlider(this);
}

void CBrFrame::Deinit()
{
    if (m_pCatalogDlg != NULL)
    {
        delete m_pCatalogDlg;
        m_pCatalogDlg = NULL;
    }

    if (m_pVideoDlg != NULL)
    {
        delete m_pVideoDlg;
        m_pVideoDlg = NULL;
    }
	
	if (m_pPtzDlg != NULL)
    {
        delete m_pPtzDlg;
        m_pPtzDlg = NULL;
    }
	
	if (m_pToolWin != NULL)
    {
        delete m_pToolWin;
        m_pToolWin = NULL;
    }
}

void CBrFrame::HideAll()
{
	m_pCatalogDlg->Hide();
	m_pVideoDlg->Hide();
	m_pPtzDlg->Hide();
	m_pRcdDlg->Hide();
	m_pRcdSlider->Hide();
}

void CBrFrame::ShowRealView()
{
	m_pCatalogDlg->Show();
	m_pPtzDlg->Show();
	m_pVideoDlg->Show();
	
	//改变模式操作
	((CCatalogDlg *)m_pCatalogDlg)->ChangeMode(1, 238);
	((CVideoDlg *)m_pVideoDlg)->ChangeMode(1);
}

void CBrFrame::ShowHistoryUI()
{
	m_pCatalogDlg->Show();
	m_pRcdDlg->Show();
	m_pVideoDlg->Show();
	m_pRcdSlider->Show();
	
	//改变模式操作
	((CCatalogDlg *)m_pCatalogDlg)->ChangeMode(2, 310);
	((CVideoDlg *)m_pVideoDlg)->ChangeMode(1, 151);
}
