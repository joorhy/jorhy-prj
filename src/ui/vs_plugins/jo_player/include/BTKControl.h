#pragma once


#include "btkbase.h"
#include "BTKInput.h"
#include "BTKTransform.h"
#include "BTKRender.h"
#include "BTKThread.h"
#include "BTKVariable.h"
#include "BTKError.h"


class BTKControl : public BTKBase
{
public:
	DLL_IMPORT BTKControl(void);
	DLL_IMPORT ~BTKControl(void);
				
	//播放网络媒体
	DLL_IMPORT BTK_RESULT InitPlayByNetwork(const char *psz_mrl,btk_work_type model=BTK_PLAY_REALTIME);		
	//播放本地媒体
	DLL_IMPORT BTK_RESULT InitPlayByPath(const char *psz_mrl,btk_work_type model=BTK_PLAY_REALTIME);

	DLL_IMPORT BTK_RESULT SetHwnd(HWND hwnd);
	DLL_IMPORT BTK_RESULT GetHwnd(HWND &hwnd);
	DLL_IMPORT BTK_RESULT Run();
	DLL_IMPORT BTK_RESULT Pause();
	DLL_IMPORT BTK_RESULT Stop();
	DLL_IMPORT BTK_RESULT SetSpeed(btk_speed_e e);
	DLL_IMPORT BTK_RESULT ToggelBackRun(bool bEnable);
	DLL_IMPORT BTK_RESULT PlayNextFrame();
	DLL_IMPORT BTK_RESULT SetVolume(int volume);
	DLL_IMPORT BTK_RESULT GetVolume(int &volume);
	DLL_IMPORT BTK_RESULT GetState(int &state);
	DLL_IMPORT BTK_RESULT Snapshot(char *path_name);			//可以根据后缀名判断相应的模块
	DLL_IMPORT BTK_RESULT ToggelRecord(char *path_name);
	DLL_IMPORT BTK_RESULT SetDisplayCBK(btk_entry_display_t pCBK,void *pUser);
	DLL_IMPORT BTK_RESULT SetEndCBK(btk_entry_end_t pCBK,void *pUser);
	DLL_IMPORT BTK_RESULT SetPlayDirection(bool bFront=true);
	DLL_IMPORT BTK_RESULT SetTime(btk_mtime_t time);

	DLL_IMPORT BTK_BOOL	IsPlaying();
	DLL_IMPORT void		ResetCBK();
	DLL_IMPORT void		SleepPlayer(bool bEnable);			//睡眠播放器，将极大减小cpu消耗

protected:
	BTK_RESULT CallBackStop();				//线程退出时调用，程序退出时会调用

protected:
	BTKInput		*m_input;
	BTKTransform	*m_tansfm;				//input create Transform
	BTKRender		*m_render;				//decoder create render
	BTKCond			m_switch;				//暂停播放开关
	BTKCond			m_FrameSwitch;			//单帧播放信号

	BTKVariable		*m_state;				//播放状态	int
	BTKVariable		*m_displayTime;			//显示时间	int64
	BTKVariable		*m_bForward;			//播放方向	bool
	BTKVariable		*m_speed;				//播放速度	int
	BTKVariable		*m_bSleep;				//睡眠播放	bool

	BTKSem			m_AllClose;				//所有线程都关闭？
	BTKSem			m_SafeClose;			//外部Stop的时候，Player安全关闭
	BTKVariable		*m_ThreadNumer;			//工作的所有线程数量 int 

	btk_work_type	m_WorkModel;			//播放器工作模式

	friend class BTKInput;
	friend class BTKTransform;
	friend class BTKRender;

protected:
	
	//display callback
	btk_entry_display_t	m_pDisplayCBK;
	void				*m_pDisplayData;

	//end callback
	btk_entry_end_t		m_pEndCBK;
	void				*m_pEndData;
};
