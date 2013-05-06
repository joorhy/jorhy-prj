#include "StdAfx.h"
#include "VlcPlayer.h"
#include "pl_reconn.h"
#include "pl_type.h"
#include "pl_manager.h"
#include "pl_ctrl.h"
#include "vlc_picture.h"

const char *real_args[]= {"--no-video-title-show",				//关闭标题;
								 "--subsdec-encoding=UTF-8",		//字幕编码格式
								 "--text-renderer=Freetype",			//关闭标题
								 "--freetype-font=MingLiU",			//繁体字符集,包含全部中文字符
#ifdef _DEBUG
								"--file-logging",
								"-vvv",	
#else
								"--no-plugins-cache",
								"--no-xlib",
#endif
								"--no-media-library",
								"--one-instance",				//一个实例
								"--network-caching=300"};

const char *vod_args[] = {"--no-video-title-show",				//关闭标题;
								"--subsdec-encoding=UTF-8",		//字幕编码格式
								"--text-renderer=Freetype",			//关闭标题
								"--freetype-font=MingLiU",			//繁体字符集,包含全部中文字符
#ifdef _DEBUG
								"--file-logging",	
								"-vvv",	
#else
								"--no-plugins-cache",
								"--no-xlib",
#endif
								"--no-media-library",
								"--one-instance",				//一个实例
								"--ffmpeg-hw",							//硬件解码
								"--no-drop-late-frames",
								"--no-skip-frames"};

/**************static变量 初始化*****************/
libvlc_instance_t *VlcPlayer::m_pInstance = NULL;
float VlcPlayer::m_nSpeed[] = {0.1f,0.2f,0.4f,0.6f,
								1.0f,
								2.0f};
const char *const VlcPlayer::m_pszSpeedTip[] = {"慢放X8","慢放X6","慢放X4","慢放X2",
												"正常播放",
												"快进X2"};

/*********************回调函数*******************/
void VlcPlayer::PlayerCallBack(const libvlc_event_t *type, void *pUser)
{
	VlcPlayer *user = reinterpret_cast<VlcPlayer*>(pUser);
	if(!user)
		return;
	if(type->type == libvlc_MediaPlayerEndReached)
	{
		if(user->m_Model == STREAME_REALTIME)
		{
			PostMessage(user->m_pPlWnd, WM_OWN_START_WAIT, (WPARAM)user->m_pPlWnd, 0);
		}
		else
		{
			PostMessage(user->m_pPlWnd, WM_MEDIA_END_REACHED,0,0);
		}
	}
	if(type->type == libvlc_MediaPlayerPlaying)
	{
		user->SetPlayingState();
	}
	if(type->type == libvlc_MediaPlayerPositionChanged)
	{
		user->SetWndStyle(TRUE);
	}
}

void VlcPlayer::VLCDisplayCallBack(void *opaque,void *picture)
{
	VlcPlayer *user = reinterpret_cast<VlcPlayer*>(opaque);
	if(user)
		user->TimeBarCallback(picture);
}
/*********************类实现*********************/

VlcPlayer::VlcPlayer(int nWorkMode,  HWND hWnd)
{
	m_Model		= nWorkMode;
	m_manager	= NULL;
	m_play		= NULL;
	if (m_pInstance == NULL)
		InitPlay();
	m_nSpeedIndex = NORMALSPEED;
	m_times		= 0;
	m_displaytime = 0;
	m_pPlWnd = hWnd;
}

VlcPlayer::~VlcPlayer(void)
{
	//if (m_pInstance)
	//	libvlc_free(m_pInstance);
}

void VlcPlayer::InitPlay()
{
	if(m_Model == STREAME_REALTIME)
		m_pInstance = libvlc_new(sizeof(real_args) / sizeof(char *), real_args);
	else
		m_pInstance = libvlc_new(sizeof(vod_args) / sizeof(char *), vod_args);
}

BOOL VlcPlayer::Play(HWND hPlayWnd, const PL_PlayInfo &playInfo)
{
	if(NULL == m_pInstance)
		return FALSE;

	m_pPlWnd = hPlayWnd;
	if(m_play != NULL)
	{
		Stop();
	}

	libvlc_media_t *media= libvlc_media_new_location(m_pInstance, playInfo.pUrl);
	m_play = libvlc_media_player_new_from_media(media);
	libvlc_video_set_key_input(m_play,FALSE);
	libvlc_video_set_mouse_input(m_play,FALSE);
	libvlc_media_player_set_hwnd(m_play,hPlayWnd);
	libvlc_audio_set_volume(m_play,0);
	AspectRatio();
	if(m_Model == STREAME_FILE)
		libvlc_video_set_callbacks_custom(m_play,VLCDisplayCallBack,this);
	AttachManager(libvlc_MediaPlayerPlaying,PlayerCallBack,this);
	libvlc_media_player_play(m_play);
	
	libvlc_state_t state;
	BOOL bRet;
	DWORD break_time = GetTickCount();
	while(true)
	{
		state = libvlc_media_player_get_state(m_play);
		if(state == libvlc_Error)
		{
			bRet = FALSE;
			break;
		}
		if(state == libvlc_Playing)
		{
			bRet = TRUE;
			break;
		}
		if(GetTickCount() - break_time > 2000)
		{
			bRet = FALSE;
			break;
		}
	}	
	//if (bRet)
	//	SetPlayingState();

	return bRet;
}

void VlcPlayer::Stop()
{
	if(NULL == m_play )
		return;

	libvlc_media_player_set_hwnd(m_play,NULL);
	libvlc_media_player_stop(m_play);
	libvlc_media_player_release(m_play);
	//libvlc_free(m_pInstance);
	//m_pInstance = NULL;
	m_play = NULL;
}

void VlcPlayer::Pause()
{
	if(m_play)
		libvlc_media_player_pause(m_play);
}

void VlcPlayer::PlayOneByOne()
{
	if(m_play)
		libvlc_media_player_next_frame(m_play);
}

int VlcPlayer::GetVolume()
{
	if(NULL == m_play)
		return 0;
	return libvlc_audio_get_volume(m_play);
}

BOOL VlcPlayer::SetVolume(int nVolume)
{
	if(NULL == m_play)
		return FALSE;
	int hRet = libvlc_audio_set_volume(m_play,nVolume);
	if(0 == hRet)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL VlcPlayer::IsPlaying()
{
	BOOL bRet = FALSE;
	if(m_play == NULL) return FALSE;
	libvlc_state_t state = libvlc_media_player_get_state(m_play);
	if(state == libvlc_Playing ||
		state == libvlc_Paused
		)
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL VlcPlayer::Capture(char *path)
{
	if(NULL == m_play) return FALSE;
	

	int nRet = libvlc_video_take_snapshot(m_play,0,path,0,0);
	return TRUE;
}

BOOL VlcPlayer::SetSpeed(BOOL bSpeedUp)
{
	if(NULL == m_play) return FALSE;

	if(bSpeedUp)
	{
		if(m_nSpeedIndex != SPEED_INDEX_NUM - 1)
		{
			m_nSpeedIndex++;
		}
	}
	else
	{
		if(m_nSpeedIndex != 0)
		{
			m_nSpeedIndex--;
		}
	}
	if(libvlc_media_player_set_rate(m_play,m_nSpeed[m_nSpeedIndex]) == -1)
		return FALSE;
	SetOSDText(2,(char*)m_pszSpeedTip[m_nSpeedIndex]);
	return TRUE;
}

BOOL VlcPlayer::Record(char *path)
{
	if(m_play == NULL) return FALSE;

	time_t t_locatime = time(NULL);
	tm *tm_locatime; 
	tm_locatime=localtime(&t_locatime);
	char locatime[256]	= {0};
	char path_name[512] = {0};
	sprintf(locatime,"RonYaoRecord-%d-%d-%d-%d_%d_%d.avi",
		tm_locatime->tm_year+1990,
		tm_locatime->tm_mon+1,
		tm_locatime->tm_mday,
		tm_locatime->tm_hour,
		tm_locatime->tm_min,
		tm_locatime->tm_sec);
	strcat(path_name,path); 
	strcat(path_name,locatime); 
	if(libvlc_video_toggle_record(m_play,path_name,NULL) == -1)
		return FALSE;
	/*char pTemp[64];
	int len = -1;
	memset(pTemp,0,sizeof(pTemp));
	len = libvlc_var_get_string(m_play,"input-record-path",pTemp);
	memset(pTemp,0,sizeof(pTemp));
	len = libvlc_var_get_string(m_play,"sout-record-dst-prefix",pTemp);
	*/
	return TRUE;
}

int VlcPlayer::GetPlayStatus()
{
	if(m_play == NULL)
		return -1;
	return libvlc_media_player_get_state(m_play);
}

HWND VlcPlayer::GetPlayHwnd()
{
	if(NULL == m_play)
		return NULL;
	return (HWND)libvlc_media_player_get_hwnd(m_play);
}

BOOL VlcPlayer::AttachManager(int type,libvlc_callback_t pCallBack,void *pUser)
{
	BOOL bRet = FALSE;

	if(m_play == NULL) 
		return FALSE;
	m_manager = libvlc_media_player_event_manager(m_play);
	if(!m_manager)
		return FALSE;
	if(!libvlc_event_attach(m_manager,type,pCallBack,pUser))
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL VlcPlayer::DetachManager(int type,libvlc_callback_t pCallBack,void *pUser)
{
	if(NULL == m_manager) 
		return FALSE;

	libvlc_event_detach(m_manager,type,pCallBack,pUser);
	return TRUE;
}

void VlcPlayer::SetPlayingState()		
{
	AttachManager(libvlc_MediaPlayerPositionChanged,PlayerCallBack,this);
	AttachManager(libvlc_MediaPlayerEndReached,PlayerCallBack,this);
}

void VlcPlayer::SetWndStyle(BOOL bSetStyle)
{
	HWND hMPWnd = GetPlayHwnd();
	DWORD s = GetWindowLong(hMPWnd, GWL_STYLE);
	if((s & WS_CLIPSIBLINGS) == WS_CLIPSIBLINGS)
		PostMessage(hMPWnd,WM_TRY_SET_MOUSE_HOOK,bSetStyle,0);
}

BOOL VlcPlayer::RePlay()
{
	if(m_play != NULL)
	{
		libvlc_media_player_stop(m_play);
		libvlc_media_player_play(m_play);
	}
	return TRUE;
}

void VlcPlayer::AspectRatio(int width,int height)
{
	if(m_play == NULL) return;
	char scale[32] = {0};
	if(height == 0 || width == 0)
	{
		//width = GetSystemMetrics(SM_CXSCREEN);
		//height = GetSystemMetrics(SM_CYSCREEN);
		RECT rect;
		GetWindowRect(GetPlayHwnd(),&rect);
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}
	sprintf(scale,"%d:%d",width,height);
	libvlc_video_set_aspect_ratio(m_play,scale);

};

BOOL VlcPlayer::VodStreamJump(const PL_PlayInfo &playInfo)
{
	if(m_play == NULL)
		return FALSE;
	HWND hwnd = GetPlayHwnd();
	SendMessage(hwnd,WM_OWN_ERASEBKGROUND,FALSE,0);
	m_nSpeedIndex = NORMALSPEED;
	return Play(hwnd, playInfo);
}

void *VlcPlayer::GetPlayFactor() const
{
	return NULL;
}

BOOL VlcPlayer::SetOSDText(int stime,char *osdText)
{
	int nRet = 0;
	int len = strlen(osdText);
	char *outstr = new char[len*2+1];
	memset(outstr,0,len*2+1);
	Convert(osdText,outstr,CP_ACP,CP_UTF8);
	nRet = libvlc_video_set_osd(m_play,1,0x06,stime*1000000,outstr);
	delete outstr;
	return nRet;
}

BOOL VlcPlayer::IsPaused()
{
	return GetPlayStatus() == libvlc_Paused ? TRUE : FALSE;
}

void VlcPlayer::TimeBarCallback(void *picture)
{
	picture_t * pdata = (picture_t*)picture;
	if(m_displaytime == pdata->date)
		return;
	m_displaytime = pdata->date;
	if(++m_times >= 25)
	{
		m_times = 0;
		PlManager::Instance()->VodCallBack(m_pPlWnd);
	}
}

void VlcPlayer::SleepPlayer(bool bSleep)
{

}

PLAYER_BEGIN_MAKER(pl_vlc)
	PLAYER_ENTER_MAKER("pl_vlc", VlcPlayer::Maker)
PLAYER_END_MAKER()