#include "x_log.h"
#include "x_loadso.h"
#include "x_config.h"
#include "PlayManager.h"
#include "StreamPlayer.h"

//´´½¨MyAppÊµÀýµÄ´úÂëÔÚÕâÀïÃæ
IMPLEMENT_APP(MyApp) 
DECLARE_APP(MyApp) 

bool MyApp::OnInit() 
{ 
	//³õÊ¼»¯ÅäÖÃ²ÎÊý
	CXConfig::Init();

	///¼ÓÔØÄ£¿é
	CXLoadso loadSo;
	if (loadSo.JoLoadSo() != J_OK)
	{
		J_OS::LOGINFO("main loadSo JoLoadSo error");
		return 0;
	}
	//´´½¨Ò»¸ö¼Ì³Ð×ÔwxFrameµÄ´°¿Ú¶ÔÏó
	CStreamPlayer *dlg = new CStreamPlayer(wxT("StreamPlayer")); 
	dlg->Show(true); 

	return true; 
} 

CStreamPlayer::CStreamPlayer(const wxString& title)
: wxDialog(NULL,wxID_ANY,title) 
, m_sizer(wxVERTICAL)
, m_displaySizer1(wxHORIZONTAL)
, m_displaySizer2(wxHORIZONTAL)
, m_displaySizer(wxVERTICAL)
, m_ctrlSizer(wxHORIZONTAL)
, m_btnPlay(this, wxID_ANY, wxT("Play"))
, m_btnStop(this, wxID_ANY, wxT("Stop"))
, m_textUrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(550, 20))
, m_urlDesc(this, wxID_ANY, wxT("播放地址:"))
, m_displayWindow1(this, wxID_ANY)
, m_displayWindow2(this, wxID_ANY)
, m_displayWindow3(this, wxID_ANY)
, m_displayWindow4(this, wxID_ANY)
, m_displayForcus(NULL)
{
	//ÀúÊ·ÊÓÆµ
	//m_streamType = 1;

	m_displayWindow1.GetHandle();
	SetSize(wxSize(602, 662));
	CentreOnScreen();
	/* Ìí¼Ó¡¢³õÊ¼»¯´°¿Ú¿Ø¼þµÄµØ·½*/ 
	m_textUrl.Append(wxT("joh://192.168.1.88:8002?resid=121&username=admin&passwd=12345&stream_type=0"));
	m_textUrl.Append(wxT("joh://192.168.1.88:8002?resid=161&username=admin&passwd=12345&stream_type=0"));

	m_textUrl.SetSelection(0);

	m_displayWindow1.SetBackgroundColour(wxColour(0, 0, 0));
	m_displayWindow2.SetBackgroundColour(wxColour(0, 0, 0));
	m_displayWindow3.SetBackgroundColour(wxColour(0, 0, 0));
	m_displayWindow4.SetBackgroundColour(wxColour(0, 0, 0));
	
	m_playManager.Init();
	m_btnPlay.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnPlay));
	m_btnStop.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnStop));
	m_displayWindow1.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnMouseLeftDown));
	m_displayWindow2.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnMouseLeftDown));
	m_displayWindow3.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnMouseLeftDown));
	m_displayWindow4.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnMouseLeftDown));
	
	m_displayWindow1.Connect(wxEVT_SIZE, wxSizeEventHandler(CStreamPlayer::OnSize));
	m_displayWindow2.Connect(wxEVT_SIZE, wxSizeEventHandler(CStreamPlayer::OnSize));
	m_displayWindow3.Connect(wxEVT_SIZE, wxSizeEventHandler(CStreamPlayer::OnSize));
	m_displayWindow4.Connect(wxEVT_SIZE, wxSizeEventHandler(CStreamPlayer::OnSize));

	m_display1 = new wxPanel(&m_displayWindow1);
	m_display1->SetSize(0, 0);
	m_display1->SetBackgroundColour(wxColour(0, 0, 0));
	m_display1->CenterOnParent();
	m_display2 = new wxPanel(&m_displayWindow2);
	m_display2->SetSize(0, 0);
	m_display2->SetBackgroundColour(wxColour(0, 0, 0));
	m_display2->CenterOnParent();
	m_display3 = new wxPanel(&m_displayWindow3);
	m_display3->SetSize(0, 0);
	m_display3->SetBackgroundColour(wxColour(0, 0, 0));
	m_display3->CenterOnParent();
	m_display4 = new wxPanel(&m_displayWindow4);
	m_display4->SetSize(0, 0);
	m_display4->SetBackgroundColour(wxColour(0, 0, 0));
	m_display4->CenterOnParent();
 } 

CStreamPlayer::~CStreamPlayer()
{
	m_playManager.Deinit();
}

void CStreamPlayer::OnPlay(wxMouseEvent& evnet)
{
	CStreamPlayer *pStreamPlayer = (CStreamPlayer *)GetParent();
	pStreamPlayer->Play();
}

void CStreamPlayer::OnStop(wxMouseEvent &evnet)
{
	CStreamPlayer *pStreamPlayer = (CStreamPlayer *)GetParent();
	pStreamPlayer->Stop();
}

void CStreamPlayer::OnMouseLeftDown(wxMouseEvent &event)
{
	//event.Skip();
	//wxPostEvent(GetParent(), event);
	CStreamPlayer *pStreamPlayer = (CStreamPlayer *)GetParent();
	pStreamPlayer->SetForcus(event.GetEventObject());
	//fprintf(stderr, "CStreamPlayer::OnMouseLeftDown %d %d\n", event.GetEventObject(), event.GetY());
	//fprintf(stderr, "CStreamPlayer::OnMouseLeftDown %d %d\n", &pStreamPlayer->m_displayWindow1, pStreamPlayer->m_displayWindow2.GetId());
}

void CStreamPlayer::OnSize(wxSizeEvent &event)
{
	CStreamPlayer *pStreamPlayer = (CStreamPlayer *)GetParent();
	pStreamPlayer->ResizeWindow(event.GetEventObject());
}

void CStreamPlayer::Play()
{
	if (m_displayForcus != NULL && m_playerMap.find(m_displayForcus) == m_playerMap.end())
	{
		char desUrl[256] = {0};
		int width = 0;
		int height = 0;
		m_displayForcus->GetParent()->GetSize(&width, &height);
		sprintf(desUrl, "jo_player://%d?width=%d&height=%d", (j_wnd_t)m_displayForcus->GetHandle(), width, height);
		j_int32_t streamId = -1;
		//ÊµÊ±ÊÓÆµ
		streamId = m_playManager.OpenStream(m_textUrl.GetValue().To8BitData(), desUrl);
		m_displayForcus->SetId(streamId);
		m_playerMap[m_displayForcus] = streamId;
	}
}

void CStreamPlayer::Stop()
{
	std::map<wxWindow *, j_int32_t>::iterator it = m_playerMap.find(m_displayForcus);
	if (it != m_playerMap.end())
	{
		//ÊµÊ±ÊÓÆµ
		m_playManager.CloseStream(m_displayForcus->GetId());
		m_playerMap.erase(it);
	}
}

void CStreamPlayer::SetForcus(wxObject *window)
{
	wxWindow *p = dynamic_cast<wxWindow *>(window);
	if (p == &m_displayWindow1)
	{
		m_displayForcus = m_display1;
	}
	else if (p == &m_displayWindow2)
	{
		m_displayForcus = m_display2;
	}
	else if (p == &m_displayWindow3)
	{
		m_displayForcus = m_display3;
	}
	else if (p == &m_displayWindow4)
	{
		m_displayForcus = m_display4;
	}
}

void CStreamPlayer::ResizeWindow(wxObject *window)
{
	wxWindow *p = dynamic_cast<wxWindow *>(window);
    int w = 300;
    int h = 300;
	if (p == &m_displayWindow1)
	{
		m_displayWindow1.SetSize(0, 0, w, h);
		m_display1->CenterOnParent();
	}
	else if (p == &m_displayWindow2)
	{
		m_displayWindow2.SetSize(w + 2, 0, w, h);
		m_display2->CenterOnParent();
	}
	else if (p == &m_displayWindow3)
	{
		m_displayWindow3.SetSize(0, h + 2, w, h);
		m_display3->CenterOnParent();
	}
	else if (p == &m_displayWindow4)
	{
		m_displayWindow4.SetSize(w + 2, h + 2, w, h);
		m_display4->CenterOnParent();
	}
	m_textUrl.SetSize(0, h * 2 + 10, 600, 10);
	m_btnPlay.SetSize(125, h * 2 + 35, 50, 25);
	m_btnStop.SetSize(427, h * 2 + 35, 50, 25);
}

BEGIN_EVENT_TABLE(CStreamPlayer, wxDialog) 
/* Ìí¼ÓÏûÏ¢Ó³ÉäµÄµØ·½£ºÀýÈç²Ëµ¥ÏìÓ¦*/
//EVT_LEFT_DOWN(CStreamPlayer::OnMouseLeftDown)
END_EVENT_TABLE() 