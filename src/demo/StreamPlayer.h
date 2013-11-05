#ifndef __STREAMPLAYER_H_
#define __STREAMPLAYER_H_
#include <wx/wx.h>
#include <wx/statline.h>

//±ØÐë¼Ì³ÐwxApp 
class MyApp : public wxApp 
{ 
public: 
	//Èë¿Úº¯Êý
	virtual bool OnInit();  
}; 

//±ØÐë¼Ì³ÐwxFrame 
class CStreamPlayer : public wxDialog
{ 
public: 
	CStreamPlayer(const wxString& title);  
	~CStreamPlayer();
private: 
	//±ØÐë¼ÓÕâ¾ä£¬·ñÔòÏûÏ¢Ó³Éä»Ø±¨´í
	DECLARE_EVENT_TABLE() 
	void OnMouseLeftDown(wxMouseEvent &event);
	void OnPlay(wxMouseEvent& evnet);
	void OnStop(wxMouseEvent& evnet);
	void OnSize(wxSizeEvent &event);

public:
	void Play();
	void Stop();
	void SetForcus(wxObject *window);
	void ResizeWindow(wxObject *window);
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

	wxPanel *m_display1;
	wxPanel *m_display2;
	wxPanel *m_display3;
	wxPanel *m_display4;
	wxWindow *m_displayForcus;
	wxStaticText m_urlDesc;
	wxComboBox m_textUrl;

	CPlayManager m_playManager;
	j_int32_t m_streamId;
	std::map<wxWindow *, j_int32_t> m_playerMap;
}; 

#endif //~__STREAMPLAYER_H_