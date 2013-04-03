#pragma once

#ifndef BOOL
	typedef int BOOL;
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef STREAME_REALTIME
#define STREAME_REALTIME 0
#endif

#ifndef STREAME_FILE
#define STREAME_FILE	 1
#endif

#ifdef PL_CORE_EXPORTS
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif

/**************************************************/
class DLLAPI BeyondPlayer
{
public:
	BeyondPlayer();

public:
	virtual BOOL Play(HWND hPlayWnd,char *psz_mrl) = 0;
	virtual void Play() = 0;			//断线重播
	virtual void Stop() = 0;				//如果在播放，会停止当前播放，并开始新的播放
	virtual void Pause() = 0;
	virtual void PlayOneByOne() = 0;
	virtual int GetVolume() = 0;
	virtual BOOL SetVolume(int nVolume) = 0; // nVolume:0~~100
	virtual BOOL IsPlaying() = 0;
	virtual BOOL SetSpeed(BOOL bSpeedUp) = 0;
	virtual BOOL Capture(char *path) = 0;
	virtual BOOL Record(char *path) = 0;
	virtual int GetPlayStatus() = 0;
	virtual HWND GetPlayHwnd() = 0;
	virtual BOOL VodStreamJump(char *pNewTime_MRL) = 0;
	virtual BOOL SetOSDText(int stime,char *osdText) = 0;
	virtual BOOL IsPaused() = 0;
	virtual void AspectRatio(int width=0,int height=0) = 0;
	virtual void SleepPlayer(bool bSleep) = 0;

public:	
	int m_Model;			//工作模式
};