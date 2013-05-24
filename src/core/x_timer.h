#ifndef __X_TIMER_H_
#define __X_TIMER_H_
#include "x_thread.h"

namespace J_OS
{

typedef void (*J_TimerFunc)(void *pUser);

class JO_API CTimer
{
public:
	CTimer();
	~CTimer();

public:
	int Create(unsigned int expires, J_TimerFunc timerFunc, void *pUser);
	int Destroy();

private:
#ifdef WIN32
	static unsigned X_JO_API OnTimerFunc(void *pParam)
#else
	static void *OnTimerFunc(void *pParam)
#endif
	{
		CTimer *pThis = static_cast<CTimer *>(pParam);
		if (pThis != NULL)
			pThis->OnTimer();

		return 0;
	}
	void OnTimer();

private:
	CJoThread m_timerTread;
	bool m_bStart;
	unsigned int m_nExpires;
#ifdef WIN32
	HANDLE m_event;
#else
	int m_event[2];
#endif
	j_thread_parm m_timerParam;
	J_TimerFunc m_timerFunc;
	void *m_pUser;
};

}

#endif //~__X_TIMER_H_
