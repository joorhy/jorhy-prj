#pragma once


#include "x_pl_base.h"
#include "x_pl_input.h"
#include "x_pl_transform.h"
#include "x_pl_render.h"
#include "x_pl_thread.h"
#include "x_pl_variable.h"
#include "x_pl_error.h"

class J_PlControl : public J_PlBase
{
public:
	JO_PL_API J_PlControl(void);
	JO_PL_API ~J_PlControl(void);
				
	//播放网络媒体
	JO_PL_API J_PL_RESULT InitPlayByNetwork(const char *psz_mrl,j_pl_work_type model=J_PL_PLAY_REALTIME);		
	//播放本地媒体
	JO_PL_API J_PL_RESULT InitPlayByPath(const char *psz_mrl,j_pl_work_type model=J_PL_PLAY_REALTIME);

	JO_PL_API J_PL_RESULT SetHwnd(HWND hwnd);
	JO_PL_API J_PL_RESULT GetHwnd(HWND &hwnd);
	JO_PL_API J_PL_RESULT Run();
	JO_PL_API J_PL_RESULT Pause();
	JO_PL_API J_PL_RESULT Stop();
	JO_PL_API J_PL_RESULT SetSpeed(j_pl_speed e);
	JO_PL_API J_PL_RESULT ToggelBackRun(bool bEnable);
	JO_PL_API J_PL_RESULT PlayNextFrame();
	JO_PL_API J_PL_RESULT SetVolume(int volume);
	JO_PL_API J_PL_RESULT GetVolume(int &volume);
	JO_PL_API J_PL_RESULT GetState(int &state);
	JO_PL_API J_PL_RESULT Snapshot(char *path_name);			//可以根据后缀名判断相应的模块
	JO_PL_API J_PL_RESULT ToggelRecord(char *path_name);
	JO_PL_API J_PL_RESULT SetDisplayCBK(j_pl_entry_display_t pCBK,void *pUser);
	JO_PL_API J_PL_RESULT SetEndCBK(j_pl_entry_end_t pCBK,void *pUser);
	JO_PL_API J_PL_RESULT SetPlayDirection(bool bFront=true);
	JO_PL_API J_PL_RESULT SetTime(j_pl_mtime_t time);

	JO_PL_API J_PL_BOOL	IsPlaying();
	JO_PL_API void		ResetCBK();
	JO_PL_API void		SleepPlayer(bool bEnable);			//睡眠播放器，将极大减小cpu消耗

protected:
	J_PL_RESULT CallBackStop();				//线程退出时调用，程序退出时会调用

protected:
	CXPlInput		*m_input;
	CXPlTransform	*m_tansfm;				//input create Transform
	CXPlRender		*m_render;				//decoder create render
	J_PlCond			m_switch;				//暂停播放开关
	J_PlCond			m_FrameSwitch;			//单帧播放信号

	J_PlVariable		*m_state;				//播放状态	int
	J_PlVariable		*m_displayTime;			//显示时间	int64
	J_PlVariable		*m_bForward;			//播放方向	bool
	J_PlVariable		*m_speed;				//播放速度	int
	J_PlVariable		*m_bSleep;				//睡眠播放	bool

	J_PlSem			m_AllClose;				//所有线程都关闭？
	J_PlSem			m_SafeClose;			//外部Stop的时候，Player安全关闭
	J_PlVariable		*m_ThreadNumer;			//工作的所有线程数量 int 

	j_pl_work_type	m_WorkModel;			//播放器工作模式

	friend class CXPlInput;
	friend class CXPlTransform;
	friend class CXPlRender;

protected:
	
	//display callback
	j_pl_entry_display_t	m_pDisplayCBK;
	void				*m_pDisplayData;

	//end callback
	j_pl_entry_end_t		m_pEndCBK;
	void				*m_pEndData;
};
