#include "x_timer.h"
#include "x_errtype.h"
#include "x_log.h"

namespace J_OS
{

CTimer::CTimer()
{
	m_timerFunc = NULL;
	memset(&m_timerParam, 0, sizeof(j_thread_parm));
	m_bStart = false;
}

CTimer::~CTimer()
{

}

int CTimer::Create(unsigned int expires, J_TimerFunc timerFunc, void *pUser)
{
	if (!m_bStart)
	{
		m_bStart = true;
		m_nExpires = expires;
		m_timerFunc = timerFunc;
		m_pUser = pUser;
#ifdef WIN32
		m_event = CreateEvent(NULL, FALSE, FALSE, NULL);
#else
		memset(&m_event, 0, sizeof(m_event));
		socketpair(AF_UNIX, SOCK_STREAM, 0, m_event);
#endif
		m_timerParam.entry = CTimer::OnTimerFunc;
		m_timerParam.data = this;
		m_timerTread.Create(m_timerParam);
	}
	return J_OK;
}

int CTimer::Destroy()
{
	if (m_bStart)
	{
#ifdef WIN32
		SetEvent(m_event);
		CloseHandle(m_event);
#else
		send(m_event[1], "0", 1, MSG_NOSIGNAL);
		close(m_event[1]);
#endif
		m_bStart = false;
		m_timerTread.Release();
	}

	return J_OK;
}

void CTimer::OnTimer()
{
#ifndef WIN32
	fd_set fdSet;
	FD_ZERO(&fdSet);
	FD_SET(m_event[0], &fdSet);

	timeval tv;
#endif
	while (m_bStart)
	{
#ifdef WIN32
		if (WaitForSingleObject(m_event, m_nExpires) == WAIT_OBJECT_0)
		{
			J_OS::LOGERROR("CTimer::OnTimer() Timer WaitForSingleObject error");
			break;
		}
#else
		tv.tv_sec = m_nExpires / 1000;
		tv.tv_usec = (m_nExpires % 1000) * 1000;

		FD_ZERO(&fdSet);
		FD_SET(m_event[0], &fdSet);
		 
		if(select(m_event[0] + 1, &fdSet, NULL, NULL, &tv) < 0)
		{
			if (errno == EINTR)
				continue;
				
			J_OS::LOGERROR("CTimer::OnTimer() Timer select error");
			break;
		}
		if(FD_ISSET(m_event[0], &fdSet))
		{
			char end_buf;
			read(m_event[0], &end_buf, 1);
			close(m_event[0]);
			m_bStart = false;
			break;
		}
#endif
		m_timerFunc(m_pUser);
	}
}

}

