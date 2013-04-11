#pragma once
#include "pl_player.h"
#include "pl_err.h"
#include "pl_factory.h"

#include "BeyondBuffer.h"
#include "BeyondRecv.h"

class PL_API HikPlayer :public PlPlayer
{
public:
	HikPlayer(int nWorkMode, HWND hWnd);
	~HikPlayer(void);

	static int Maker(PlPlayer *&pObj, int nWorkMode, HWND hWnd)
	{
		pObj = new HikPlayer(nWorkMode, hWnd);
		return PL_OK;
	}

public:
	virtual BOOL Play(HWND hPlayWnd, const PL_PlayInfo &playInfo);
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
	virtual BOOL VodStreamJump(const PL_PlayInfo &playInfo);
	virtual BOOL SetOSDText(int stime,char *osdText);
	virtual BOOL IsPaused();
	virtual void AspectRatio(int width=0,int height=0);
	virtual void SleepPlayer(bool bSleep);

	void *GetPlayFactor() const;

private:
	BOOL InitPlay(char *pHeader,int nHeadLen);
	BOOL StartPlay();
	static DWORD WINAPI PlayThread(void *parm);
	void InputData();

private:
	LONG m_port;
	HWND m_hPlayWnd;
	BeyondBuffer *m_pBuff;
	BeyondRecv *m_pRecv;
	BOOL m_bStart;
	BOOL m_bPause;
};
