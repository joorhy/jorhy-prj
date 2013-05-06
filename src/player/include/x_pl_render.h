#pragma once
#include "x_pl_base.h"
#include "x_pl_audio_output.h"
#include "x_pl_video_output.h"
#include "x_pl_thread.h"
#include "x_pl_data_struct.h"

class CXPlRender : public J_PlBase
{
public:
	CXPlRender(void *control);
	~CXPlRender(void);

	J_PL_RESULT CreateVout(j_pl_video_out_t &vParm);	//创建视频显示类
	J_PL_RESULT CreateAout(j_pl_audio_out_t &aParm);	//创建音频显示类
	J_PL_RESULT RunVout();			//创建video显示线程
	J_PL_RESULT RunAout();			//创建audio显示线程
	J_PL_RESULT SetHwnd(HWND hwnd);
	J_PL_RESULT GetHwnd(HWND &hwnd);
	J_PL_RESULT TakeSnapshot(char *path_name);
	J_PL_RESULT SetTime(j_pl_mtime_t time);

protected:

	//audio stuff
	J_PlThread		m_aThread;
	CXPlAudioOutput	*m_aOut;

	//video stuff
	J_PlThread		m_vThread;
	CXPlVideoOutput	*m_vOut;

	j_pl_buffer_t		m_vhead;
	j_pl_video_format_t	m_vformat;
	char				*m_vdata;
	J_PlMutexLock		m_vLock;
	j_pl_thread_t m_vThreadParm;

	//control instance
	void		*m_control;
	HWND		m_hwnd;


private:
	//audio output
	static unsigned X_PL_API AoutThread(void *parm);
	J_PL_RESULT AoutLoop();


	//video output
	static unsigned X_PL_API VoutThread(void *parm);
	J_PL_RESULT VoutLoopPush();

	J_PL_RESULT VoutLoopPull(); 
	J_PL_RESULT GetNextFrame(char *data,j_pl_video_format_t &t,j_pl_buffer_t &head);		//only for pull model
	J_PL_RESULT DisplayNextFrame(j_pl_mtime_t last_time,j_pl_mtime_t now_time);
};
