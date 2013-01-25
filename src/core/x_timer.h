#ifndef __X_TIMER_H_
#define __X_TIMER_H_
#include <pthread.h>

namespace J_OS
{

typedef void (*TimerFunc)(void *pUser);

class CTimer
{
public:
	CTimer();
	~CTimer();

public:
	int Create(unsigned int expires, TimerFunc timerFunc, void *pUser);
	int Destroy();

private:
	static void *OnTimerFunc(void *pParam)
	{
		CTimer *pThis = static_cast<CTimer *>(pParam);
		if (pThis != NULL)
			pThis->OnTimer();

		return (void *)0;
	}
	void OnTimer();

private:
	pthread_t m_timerTread;
	bool m_bStart;
	unsigned int m_nExpires;
	int m_event[2];
	TimerFunc m_timerFunc;
	void *m_pUser;
};

}

#endif //~__X_TIMER_H_
