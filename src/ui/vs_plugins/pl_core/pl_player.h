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

// {BC81BC53-0189-4bbf-9970-62311AD1C1FC}
static const GUID IID_PlObj =
{ 0xbc81bc53, 0x189, 0x4bbf, { 0x99, 0x70, 0x62, 0x31, 0x1a, 0xd1, 0xc1, 0xfc } };

/// PowerOn基础对象接口.
struct PlObj
{
	/// 获得接口指针(尽量不使用,而使用更安全的POSA_QI宏).
	/// @param[in] iid 接口编号
	/// @param[out] pObj 得到接口指针
	/// @return RMIP返回码
	//virtual INT QueryInterface(const GUID& iid, void*& pObj) = 0;

	virtual ~PlObj(){};	
};

// {913FFF1A-8CAF-4893-856F-C935A1B7F474}
static const GUID IID_PlPlayer = 
{ 0x913fff1a, 0x8caf, 0x4893, { 0x85, 0x6f, 0xc9, 0x35, 0xa1, 0xb7, 0xf4, 0x74 } };

///播放器接口定义
struct PlPlayer : public PlObj
{
	///播放
	virtual BOOL Play(HWND hPlayWnd, const PL_PlayInfo &playInfo) = 0;
	virtual void	Play() = 0;								//断线重播
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

// {DE02101F-B275-4b56-875B-CD3B121ECE55}
static const GUID IID_PlFullScreen = 
{ 0xde02101f, 0xb275, 0x4b56, { 0x87, 0x5b, 0xcd, 0x3b, 0x12, 0x1e, 0xce, 0x55 } };

///全屏接口
struct PlFullScreen
{
	virtual void onFullScreen(HWND hNeedFullWnd) = 0;
};

// {C9D0792E-A4E1-42da-B509-D9BE61C426C8}
static const GUID IID_PlToolWin = 
{ 0xc9d0792e, 0xa4e1, 0x42da, { 0xb5, 0x9, 0xd9, 0xbe, 0x61, 0xc4, 0x26, 0xc8 } };

struct PlToolWin
{
	virtual void SetModel(int nModel) = 0;
	virtual void ShowControls(BOOL bShow) = 0;
	virtual void StopPlayer() = 0; 
	virtual BOOL AttachPlayer(PL_PlayParm *pPlayParm, void *parent) = 0;
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
};
