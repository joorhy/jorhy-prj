#pragma once
#include "x_pl_control.h"
#include "pl_player.h"
#include "pl_lock.h"
#include "pl_err.h"
#include "pl_factory.h"
#include <string>

class PL_API JoPlayer :public PlPlayer
{
public:
	JoPlayer(int nWorkMode, HWND hWnd);
	~JoPlayer(void);

	static int Maker(PlPlayer *&pObj, int nWorkMode, HWND hWnd)
	{
		pObj = new JoPlayer(nWorkMode, hWnd);
		return PL_OK;
	}

public:
	virtual BOOL Play(HWND hPlayWnd, const PL_PlayInfo &playInfo);
	virtual BOOL RePlay();
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
	virtual BOOL VodStreamJump(const PL_PlayInfo &playInfo);
	virtual BOOL SetOSDText(int stime,char *osdText);
	virtual BOOL IsPaused();
	virtual void AspectRatio(int width=0,int height=0);
	virtual void SleepPlayer(bool bSleep);

private:
	static void X_PL_API EndCBK(void *pdata);
	static void X_PL_API DisplayCbFunc(void *pUser, j_pl_mtime_t frame_time)
	{
		JoPlayer *user = reinterpret_cast<JoPlayer*>(pUser);
		if(user)
			user->OnDisplayCbFunc(frame_time);
	}
	void OnDisplayCbFunc(j_pl_mtime_t frame_time);

private:
	J_PlControl	*m_player;
	std::string m_lastMrl;
	HWND m_pPlWnd;
	PlLock m_lock;
	j_pl_mtime_t m_lastFrameTime;
	PlLock m_lock2;
};
