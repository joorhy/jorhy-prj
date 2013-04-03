#pragma once
#include "btkbase.h"
#include "BTKAudioOutput.h"
#include "BTKVideoOutput.h"
#include "BTKThread.h"
#include "DataStruct.h"

class BTKRender : public BTKBase
{
public:
	BTKRender(void *control);
	~BTKRender(void);

	BTK_RESULT CreateVout(btk_video_out_t &vParm);	//创建视频显示类
	BTK_RESULT CreateAout(btk_audio_out_t &aParm);	//创建音频显示类
	BTK_RESULT RunVout();			//创建video显示线程
	BTK_RESULT RunAout();			//创建audio显示线程
	BTK_RESULT SetHwnd(HWND hwnd);
	BTK_RESULT GetHwnd(HWND &hwnd);
	BTK_RESULT TakeSnapshot(char *path_name);
	BTK_RESULT SetTime(btk_mtime_t time);

protected:

	//audio stuff
	BTKThread		m_aThread;
	BTKAudioOutput	*m_aOut;

	//video stuff
	BTKThread		m_vThread;
	BTKVideoOutput	*m_vOut;

	btk_buffer_t		m_vhead;
	btk_video_format_t	m_vformat;
	char				*m_vdata;
	BTKMutexLock		m_vLock;


	//control instance
	void		*m_control;
	HWND		m_hwnd;


private:
	//audio output
	static unsigned BTKAPI AoutThread(void *parm);
	BTK_RESULT AoutLoop();


	//video output
	static unsigned BTKAPI VoutThread(void *parm);
	BTK_RESULT VoutLoopPush();

	BTK_RESULT VoutLoopPull(); 
	BTK_RESULT GetNextFrame(char *data,btk_video_format_t &t,btk_buffer_t &head);		//only for pull model
	BTK_RESULT DisplayNextFrame(btk_mtime_t last_time,btk_mtime_t now_time);
};
