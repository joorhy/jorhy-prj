#pragma once
#include "pl_type.h"

struct PL_PlayParm
{
	int pVolume;
	BOOL pSound;
	BOOL bRecoder;
	DWORD dwUIT;
	BOOL bNeedShowCTRL;
	BOOL bPlayOneByOne;
};

///布局信息
struct PL_LayoutInfo
{
	BOOL bInit;
	int nMod;						//工作模式，1实时，2历史;
	int nLayout;					//布局方式， 1横向，2纵向，3、宫格;
	int nWindows;				//布局参数，不为宫格的时候是视频窗口的数量；为宫格的时候表示不同宫格的布局方式。
	//宫格布局模式：
	//0：单窗口、
	//1：四窗口(2×2)、
	//2：9窗口（3*3）。
	int nMax;						//窗口最大化方式：1：插件内最大化，2：全屏最大化。
	int nUid;						//用户ID；
	char imgPath[512];		//抓图存放路径；
	char mediaPath[512];	//本地录像路径
};

struct PL_PlayInfo
{
	int nStreamType;			//码流类型,0-海康，1-标准
	int nSubStreamType;		//码流子类型,0-主码流，1-辅码流
	int nPlayMode;				//播放模式，0-实时，1-历史
	int nId;							//Id: 窗口ID，当ID=0，按照该表格后面的说明进行播放；当ID>0，对指定ID的窗口进行播放。
	char strResid[256];			//资源唯一编码
	int nDevType;				//设备类型 0-NVR,1-DVR
	INT64 nStartTime;			//开始时间
	INT64 nEndTime;			//结束时间
	char strIpaddr[16];			//SS IP地址
	int nPort;						//SS端口 
	char	pUrl[512];
};

/// 基础对象接口.
struct PlObj
{
	virtual ~PlObj(){};	
};

///播放器接口定义
struct PlPlayer : public PlObj
{
	///播放
	virtual BOOL Play(HWND hPlayWnd, const PL_PlayInfo &playInfo) = 0;
	virtual BOOL	RePlay() = 0;								//断线重播
	virtual void	Stop() = 0;							//如果在播放，会停止当前播放，并开始新的播放
	virtual void	Pause() = 0;
	virtual void	PlayOneByOne() = 0;
	virtual int		GetVolume() = 0;
	virtual BOOL SetVolume(int nVolume) = 0;			// nVolume:0~~100
	virtual BOOL IsPlaying() = 0;
	virtual BOOL SetSpeed(BOOL bSpeedUp) = 0;
	virtual BOOL Capture(char *path) = 0;
	virtual BOOL Record(char *path) = 0;
	virtual int		GetPlayStatus() = 0;
	virtual HWND GetPlayHwnd() = 0;
	virtual BOOL VodStreamJump(const PL_PlayInfo &playInfo) = 0;
	virtual BOOL SetOSDText(int stime,char *osdText) = 0;
	virtual BOOL IsPaused() = 0;
	virtual void	AspectRatio(int width=0,int height=0) = 0;
	virtual void	SleepPlayer(bool bSleep) = 0;

public:	
	int m_Model;													//工作模式
};

///全屏接口
struct PlFullScreen
{
	virtual void onFullScreen(HWND hNeedFullWnd) = 0;
};

struct PlToolWin
{
	virtual void SetModel(int nModel) = 0;
	virtual void ShowControls(BOOL bShow) = 0;
	virtual void StopPlayer() = 0; 
	virtual BOOL AttachPlayer(PL_PlayParm *pPlayParm, void *parent) = 0;
	//virtual HWND GetPlWnd() = 0;
};

///播放器信息
class CWnd;
struct PL_PlayerInfo
{
	HWND			hWnd;				//窗口句柄
	PlPlayer		*pPlayer;			//播放器指针
	void				*pUser;				//用户
	CWnd			*pReconnWnd;	//重连窗口
	PL_PlayInfo	playInfo;			//url
	DWORD		dwPlayTime;		//播放持续时间
	BOOL			bPlay;				//播放标志
};
