#pragma once
#include "btkbase.h"
#include "BTKDemux.h"
#include "BTKAccess.h"
#include "BTKThread.h"
#include "BTKBuffer.h"
#include "BTKTransform.h"

class BTKInput : public BTKBase
{
public:
	BTKInput(void);
	~BTKInput(void);

	BTK_RESULT Init(btk_cfg_t &cfg,void *control);		//init access
	BTK_RESULT Run();									//开始线程	
	BTK_RESULT ControlAccess(int type,va_list args);

private:
	BTK_RESULT InitDemux();				//init demux
	BTK_RESULT InitDecoder();			//init decoder

	static unsigned BTKAPI Thread(void *pdata);			//main loop
	BTK_RESULT ThreadLoopPush();						//线程执行函数(推模式)
	BTK_RESULT ThreadLoopPull();						//线程执行函数(拉模式)

private:		
	BTKDemux	*m_demux;
	BTKAccess	*m_access;
	BTKThread	m_thread;
	btk_thread_t m_threadParm;

protected:
	void		*m_control;
	BTKBuffer	*m_buffer;				//share with decoder
	BTKCond		m_pullSwitch;				//暂停播放开关(拉模式)

	friend class BTKTransform;
};
