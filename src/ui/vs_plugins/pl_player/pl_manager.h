#pragma once

#include "windows.h"
#include "stdint.h"
#include "json.h"
#include "pl_type.h"
#include "pl_core.h"
#include "pl_player.h"
#include "pl_singleton.h"
#include <map>

class PL_API PlManager : public SingletonTmpl<PlManager>
{
	typedef std::map<HWND, PL_PlayerInfo>	PlayerMap;
public:
	PlManager();
	~PlManager();

public:
	BOOL	Play(HWND hWnd, const PL_PlayInfo &playInfo);			//网页调用 播放
	void		Stop(HWND hWnd);											//停止播放
	BOOL	Capture(HWND hWnd, char *pPath);								//抓图
	BOOL	SetSpeed(HWND hWnd, BOOL bSpeedUp);					//TRUE=快进，FALSE=快退
	BOOL	Record(HWND hWnd, char *pPath);								//录像
	void		Pause(HWND hWnd);													//暂停
	void		PlayOneByOne(HWND hWnd);										//单帧播放
	int		GetVolume(HWND hWnd);											//获得音量大小
	BOOL	SetVolume(HWND hWnd, int nVolume);						//设置音量大小
	BOOL	IsPlaying(HWND hWnd);												//是否在播放
	BOOL	VodStreamJump(HWND hWnd, const PL_PlayInfo &playInfo);				//历史流跳转
	BOOL	GetWndPlayParm(HWND hWnd, char *pPlayerParm);
	BOOL	GetPlayInfo(HWND hWnd, PL_PlayInfo &playInfo);
	void		Play(HWND hWnd);																			//重连调用
	BOOL	SetOsdText(HWND hWnd, int stime,char *osdtext);								//osd文本设置
	BOOL	IsPaused(HWND hWnd);

	void		VodCallBack(HWND hWnd);											//历史播放时间条回调
	BOOL	RegisterCallBack(NpnNotifyFunc funcAddr);
	void		NotifyNpn(HWND hWnd, UINT nType, int args[], UINT argCount);
	HWND	GetRecntWnd(HWND hWnd);								//获得重连窗口
	void		StatusCallBack(HWND hPlayWnd);			//插件状态通知
	BOOL	SetUserData(HWND hWnd, void *pUser);							//设置用户数据，多个实例化用到
	void		AspectRatio(HWND hWnd, int width=0,int height=0);		//拉伸
	void		SleepPlayer(HWND hWnd, bool bSleep);

private:
	void		CreateMrl(const PL_PlayInfo &playInfo);					//生成播发MRL字串

private:
	PlayerMap m_playerMap;
	NpnNotifyFunc m_pFuncCallBk;						//回调函数指针
	int64_t		m_nLastTime;									//历史播放时间条回调函数时间值
	int			m_nPlayNum;									//目前有几个窗口在播放
	int			m_nVodEndTime;
};
