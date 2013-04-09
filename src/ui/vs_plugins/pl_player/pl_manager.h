#pragma once

#include "windows.h"
#include "stdint.h"
#include "json.h"
#include "pl_type.h"
#include "pl_core.h"
#include "pl_player.h"
#include "pl_singleton.h"

class PL_API PlManager : public SingletonTmpl<PlManager>
{
public:
	PlManager();
	~PlManager();

public:
	BOOL	Play(HWND hWnd, char *js_playInfo);	//网页调用 播放
	void		Stop(HWND hWnd = NULL);					//停止播放
	BOOL	Capture(char *path);								//抓图
	BOOL	SetSpeed(BOOL bSpeedUp);					//TRUE=快进，FALSE=快退
	BOOL	Record(char *path);								//录像
	void		Pause();													//暂停
	void		PlayOneByOne();									//单帧播放
	int		GetVolume();										//获得音量大小
	BOOL	SetVolume(int nVolume);						//设置音量大小
	BOOL	IsPlaying();											//是否在播放
	BOOL	VodStreamJump(char *js_time);				//历史流跳转
	HWND GetPlayHwnd();										//得到播放窗口句柄
	BOOL	GetWndPlayParm(char *OUT_playerParm);
	void		Play();													//重连调用
	BOOL	SetOsdText(int stime,char *osdtext);		//osd文本设置
	BOOL	IsPaused();

	char		*GetJSInfo() const;									//获得json格式播放信息
	void		VodCallBack();											//历史播放时间条回调
	static BOOL RegisterCallBack(CALLBACK_onEvent funcAddr);
	void		onCallBack(unsigned int nType,int args[],unsigned int argCount);
	void		*GetRecntWnd()const;								//获得重连窗口
	void		StatusCallBack(HWND hPlayWnd);			//插件状态通知
	BOOL	SetUserData(void *pUser);							//设置用户数据，多个实例化用到
	void		AspectRatio(int width=0,int height=0);		//拉伸
	void		SleepPlayer(bool bSleep);

private:
	int		GetVideoType();										//判断视屏类型
	void		CreateMrl(char *OUT_playInfo);					//生成播发MRL字串

private:
	PlPlayer	*m_pPlayer;											//播放器实例
	static WorkModel m_playMode;							//播放器工作模式
	char			*m_jsPlayInfo;										//播放信息
	static CALLBACK_onEvent m_pFuncCallBk;				//回调函数指针
	int64_t		m_nLastTime;										//历史播放时间条回调函数时间值
	static int	m_nPlayerNum;									//目前有几个窗口在播放
	void			*m_waitStatus;										//重连窗口
	int			m_videoType;										//视频类型:std, custom
	int			m_nVodEndTime;
	void			*m_pUser;												//实例化对象指针dll
	HWND		m_hPlayWnd;
};
