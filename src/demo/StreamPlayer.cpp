#include "x_log.h"
#include "x_loadso.h"
#include "x_config.h"
#include "PlayManager.h"

#include <wx/wx.h>
#include <wx/statline.h>

//必须继承wxApp 
class MyApp : public wxApp 
{ 
public: 
	//入口函数
	virtual bool OnInit();  
}; 

//创建MyApp实例的代码在这里面
IMPLEMENT_APP(MyApp) 
DECLARE_APP(MyApp) 

//必须继承wxFrame 
class CStreamPlayer : public wxDialog
{ 
public: 
	CStreamPlayer(const wxString& title);  
	~CStreamPlayer();
private: 
	//必须加这句，否则消息映射回报错
	DECLARE_EVENT_TABLE() 
	void OnMouseLeftDown(wxMouseEvent &event);
	void OnPlay(wxMouseEvent& evnet);
	void OnStop(wxMouseEvent& evnet);

public:
	void Play();
	void Stop();
	void SetForcus(wxObject *window);
	//wxObjectEventFunction

private:
	wxBoxSizer m_sizer;
	wxBoxSizer m_displaySizer1;
	wxBoxSizer m_displaySizer2;
	wxBoxSizer m_displaySizer;
	wxBoxSizer m_ctrlSizer;
	wxButton m_btnPlay;
	wxButton m_btnStop;
	wxWindow m_displayWindow1;
	wxWindow m_displayWindow2;
	wxWindow m_displayWindow3;
	wxWindow m_displayWindow4;
	wxWindow *m_displayForcus;
	wxStaticText m_urlDesc;
	wxComboBox m_textUrl;

	CPlayManager m_playManager;
	j_int32_t m_streamId;
	std::map<wxWindow *, j_int32_t> m_playerMap;
}; 

bool MyApp::OnInit() 
{ 
	//初始化配置参数
	CXConfig::Init();

	///加载模块
	CXLoadso loadSo;
	if (loadSo.JoLoadSo() != J_OK)
	{
		J_OS::LOGINFO("main loadSo JoLoadSo error");
		return 0;
	}
	//创建一个继承自wxFrame的窗口对象
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
	//历史视频
	//m_streamType = 1;

	m_displayWindow1.GetHandle();
	SetSize(wxSize(805, 805));
	CentreOnScreen();
	/* 添加、初始化窗口控件的地方*/ 
	m_ctrlSizer.AddSpacer(10);
	m_urlDesc.SetSize(wxSize(50, 15));
	m_ctrlSizer.Add(&m_urlDesc);
	m_ctrlSizer.AddSpacer(10);
	m_textUrl.Append(wxT("joh://192.168.1.88:8002?resid=121&username=admin&passwd=12345&stream_type=0"));
	m_textUrl.Append(wxT("joh://192.168.1.88:8002?resid=161&username=admin&passwd=12345&stream_type=0"));

	m_textUrl.SetSelection(0);
	m_ctrlSizer.Add(&m_textUrl);
	m_ctrlSizer.AddSpacer(10);
	m_ctrlSizer.Add(&m_btnPlay);
	m_ctrlSizer.AddSpacer(10);
	m_ctrlSizer.Add(&m_btnStop);

	m_displayWindow1.SetSize(400, 300);
	m_displayWindow1.SetBackgroundColour(wxColour(0, 0, 0));
	m_displayWindow2.SetSize(400, 300);
	m_displayWindow2.SetBackgroundColour(wxColour(0, 0, 0));
	m_displayWindow3.SetSize(400, 300);
	m_displayWindow3.SetBackgroundColour(wxColour(0, 0, 0));
	m_displayWindow4.SetSize(400, 300);
	m_displayWindow4.SetBackgroundColour(wxColour(0, 0, 0));
	m_displaySizer1.Add(&m_displayWindow1);
	m_displaySizer1.AddSpacer(5);
	m_displaySizer1.Add(&m_displayWindow2);
	m_displaySizer2.Add(&m_displayWindow3);
	m_displaySizer2.AddSpacer(5);
	m_displaySizer2.Add(&m_displayWindow4);
	m_displaySizer.Add(&m_displaySizer1);
	m_displaySizer.AddSpacer(5);
	m_displaySizer.Add(&m_displaySizer2);

	m_sizer.Add(&m_displaySizer);
	m_sizer.AddSpacer(50);
	m_sizer.Add(&m_ctrlSizer);
	SetSizer(&m_sizer);
	
	m_playManager.Init();
	m_btnPlay.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnPlay));
	m_btnStop.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnStop));
	m_displayWindow1.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnMouseLeftDown));
	m_displayWindow2.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnMouseLeftDown));
	m_displayWindow3.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnMouseLeftDown));
	m_displayWindow4.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnMouseLeftDown));
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

void CStreamPlayer::Play()
{
	if (m_displayForcus != NULL && m_playerMap.find(m_displayForcus) == m_playerMap.end())
	{
		char desUrl[256] = {0};
		sprintf(desUrl, "jo_player://%d", (j_wnd_t)m_displayForcus->GetHandle());
		j_int32_t streamId = -1;
		//实时视频
		streamId = m_playManager.OpenStream(m_textUrl.GetValue(), desUrl);
		m_displayForcus->SetId(streamId);
		m_playerMap[m_displayForcus] = streamId;
	}
}

void CStreamPlayer::Stop()
{
	std::map<wxWindow *, j_int32_t>::iterator it = m_playerMap.find(m_displayForcus);
	if (it != m_playerMap.end())
	{
		//实时视频
		m_playManager.CloseStream(m_displayForcus->GetId());
		m_playerMap.erase(it);
	}
}

void CStreamPlayer::SetForcus(wxObject *window)
{
	m_displayForcus = dynamic_cast<wxWindow *>(window);
}
BEGIN_EVENT_TABLE(CStreamPlayer, wxDialog) 
/* 添加消息映射的地方：例如菜单响应*/
//EVT_LEFT_DOWN(CStreamPlayer::OnMouseLeftDown)
END_EVENT_TABLE() 