#pragma once
#include "j_player.h"
#include "BTKControl.h"
#include <string>
#include "BeyondLock.h"

class BTKPlayer :public JoPlayer
{
public:
	BTKPlayer(int nWorkMode,void *pFactorUser);
	~BTKPlayer(void);

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

private:
	static void BTKAPI EndCBK(void *pdata);

private:
	BTKControl	*m_player;
	std::string m_lastMrl;
	void *m_pFactor;
	HWND m_hwnd;
	BeyondLock m_lock;
};
