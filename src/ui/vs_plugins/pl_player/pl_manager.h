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
	BOOL	Play(HWND hWnd, char *pJsUrl, int nPlayMode, int nSteamType);			//网页调用 播放
	void		Stop(HWND hWnd = NULL);					//停止播放
	BOOL	Capture(HWND hWnd, char *pPath);								//抓图
	BOOL	SetSpeed(HWND hWnd, BOOL bSpeedUp);					//TRUE=快进，FALSE=快退
	BOOL	Record(HWND hWnd, char *pPath);								//录像
	void		Pause(HWND hWnd);													//暂停
	void		PlayOneByOne(HWND hWnd);									//单帧播放
	int		GetVolume(HWND hWnd);										//获得音量大小
	BOOL	SetVolume(HWND hWnd, int nVolume);						//设置音量大小
	BOOL	IsPlaying(HWND hWnd);											//是否在播放
	BOOL	VodStreamJump(HWND hWnd, char *js_time);				//历史流跳转
	BOOL	GetWndPlayParm(HWND hWnd, char *OUT_playerParm);
	void		Play();													//重连调用
	BOOL	SetOsdText(int stime,char *osdtext);		//osd文本设置
	BOOL	IsPaused();

	void		VodCallBack(HWND hWnd);											//历史播放时间条回调
	static BOOL RegisterCallBack(CALLBACK_onEvent funcAddr);
	void		onCallBack(unsigned int nType,int args[],unsigned int argCount);
	void		*GetRecntWnd()const;								//获得重连窗口
	void		StatusCallBack(HWND hPlayWnd);			//插件状态通知
	BOOL	SetUserData(HWND hWnd, void *pUser);							//设置用户数据，多个实例化用到
	void		AspectRatio(int width=0,int height=0);		//拉伸
	void		SleepPlayer(bool bSleep);

private:
	void		CreateMrl(int nPlayMode, int nSteamType,  char *pJsUrl, char *pUrl);					//生成播发MRL字串

private:
	PlayerMap m_playerMap;
	static CALLBACK_onEvent m_pFuncCallBk;				//回调函数指针
	int64_t		m_nLastTime;										//历史播放时间条回调函数时间值
	static int	m_nPlayerNum;									//目前有几个窗口在播放
	void			*m_waitStatus;										//重连窗口
	int			m_videoType;										//视频类型:std, custom
	int			m_nVodEndTime;
	void			*m_pUser;												//实例化对象指针dll
	HWND		m_hPlayWnd;
};
