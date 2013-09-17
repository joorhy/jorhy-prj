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
	void OnPlay(wxMouseEvent& evnet);
	void OnStop(wxMouseEvent& evnet);
	//wxObjectEventFunction

private:
	wxBoxSizer m_sizer;
	wxBoxSizer m_displaySizer;
	wxBoxSizer m_ctrlSizer;
	wxButton m_btnPlay;
	wxButton m_btnStop;
	wxWindow m_displayWindow;
	wxStaticText m_urlDesc;
	wxTextCtrl m_textUrl;

	CPlayManager m_playManager;
	j_int32_t m_streamId;
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
, m_displaySizer(wxHORIZONTAL)
, m_ctrlSizer(wxHORIZONTAL)
, m_btnPlay(this, wxID_ANY, wxT("Play"))
, m_btnStop(this, wxID_ANY, wxT("Stop"))
, m_textUrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(500, 20))
, m_urlDesc(this, wxID_ANY, wxT("播放地址:"))
, m_displayWindow(this, wxID_ANY)
{ 
	m_displayWindow.GetHandle();
	SetSize(wxSize(800, 800));
	CentreOnScreen();
	/* 添加、初始化窗口控件的地方*/ 
	m_ctrlSizer.AddSpacer(10);
	m_urlDesc.SetSize(wxSize(50, 15));
	m_ctrlSizer.Add(&m_urlDesc);
	m_ctrlSizer.AddSpacer(10);
	m_textUrl.SetValue(wxT("joh://192.168.1.12:8002?resid=121&username=admin&passwd=12345&stream_type=0"));
	m_ctrlSizer.Add(&m_textUrl);
	m_ctrlSizer.AddSpacer(60);
	m_ctrlSizer.Add(&m_btnPlay);
	m_ctrlSizer.AddSpacer(10);
	m_ctrlSizer.Add(&m_btnStop);

	m_displayWindow.SetSize(800, 600);
	m_displayWindow.SetBackgroundColour(wxColour(0, 0, 0));
	m_displaySizer.Add(&m_displayWindow);

	m_sizer.Add(&m_displaySizer);
	m_sizer.AddSpacer(50);
	m_sizer.Add(&m_ctrlSizer);
	SetSizer(&m_sizer);

	m_playManager.Init();
	m_btnPlay.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnPlay));
	m_btnStop.Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CStreamPlayer::OnStop));
} 

CStreamPlayer::~CStreamPlayer()
{
	m_playManager.Deinit();
}

void CStreamPlayer::OnPlay(wxMouseEvent& evnet)
{
	char desUrl[256] = {0};
	CStreamPlayer *pStreamPlayer = (CStreamPlayer *)GetParent();
	sprintf(desUrl, "jo_player://%d", (j_wnd_t)pStreamPlayer->m_displayWindow.GetHandle());
	pStreamPlayer->m_streamId = pStreamPlayer->m_playManager.OpenStream(pStreamPlayer->m_textUrl.GetValue(), desUrl);
}

void CStreamPlayer::OnStop(wxMouseEvent &evnet)
{
	((CStreamPlayer *)GetParent())->m_playManager.CloseStream(((CStreamPlayer *)GetParent())->m_streamId);
}
BEGIN_EVENT_TABLE(CStreamPlayer, wxDialog) 

/* 添加消息映射的地方：例如菜单响应
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout) 
MyFrame::OnAbout的声明格式是：
void OnAbout(wxCommandEvent& event); 
*/ 

END_EVENT_TABLE() 