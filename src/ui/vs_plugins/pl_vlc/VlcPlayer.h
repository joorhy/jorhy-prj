#pragma once
#include "BeyondPlayer.h"
#include "vlc.h"
#define SPEED_INDEX_NUM 6
#define NORMALSPEED		4

class VlcPlayer :public BeyondPlayer
{
public:
	VlcPlayer(int nWorkMode,void *pFactorUser);
	~VlcPlayer(void);

public:
	virtual BOOL Play(HWND hPlayWnd,char *psz_mrl);
	virtual void Play();
	virtual void Stop();
	virtual void Pause();
	virtual void PlayOneByOne();
	virtual int GetVolume();
	virtual BOOL SetVolume(int nVolume); // nVolume:0~~100
	virtual BOOL IsPlaying();
	virtual BOOL SetSpeed(BOOL bSpeedUp);
	virtual BOOL Capture(char *path);
	virtual BOOL Record(char *path);
	virtual int GetPlayStatus();
	virtual HWND GetPlayHwnd();
	virtual BOOL VodStreamJump(char *pNewTime_MRL);
	virtual BOOL SetOSDText(int stime,char *osdText);
	virtual BOOL IsPaused();
	virtual void AspectRatio(int width=0,int height=0);
	virtual void SleepPlayer(bool bSleep);

	void *GetPlayFactor() const;
	void TimeBarCallback(void *picture);
private:
	void InitPlay();
	BOOL AttachManager(int type,libvlc_callback_t pCallBack,void *pUser);
	BOOL DetachManager(int type,libvlc_callback_t pCallBack,void *pUser);
	static void PlayerCallBack(const libvlc_event_t *type, void *pUser);	//回调函数
	void SetPlayingState();				//设置播放时候的一些时间管理函数
	void SetWndStyle(BOOL bSetStyle);
	static void VLCDisplayCallBack(void *opaque,void *picture);

private:
	static libvlc_instance_t *m_pInstance;		
	libvlc_media_player_t *m_play;
	libvlc_event_manager_t *m_manager;
	void *m_pFactor;
	int m_nSpeedIndex;
	static float m_nSpeed[SPEED_INDEX_NUM];
	static const char *const m_pszSpeedTip[SPEED_INDEX_NUM];

	//给回调函数使用
	int64_t m_displaytime;		//目前帧的显示时间
	int		m_times;			//在当前帧率下，目前显示了多少帧，一秒清空一次
};
