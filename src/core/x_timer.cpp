#include "x_timer.h"
#include "x_errtype.h"
#include "x_log.h"

#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

namespace J_OS
{

CTimer::CTimer()
{
	m_timerTread = 0;
	m_bStart = false;
}

CTimer::~CTimer()
{

}

int CTimer::Create(unsigned int expires, TimerFunc timerFunc, void *pUser)
{
	if (!m_bStart)
	{
		m_bStart = true;
		m_nExpires = expires;
		m_timerFunc = timerFunc;
		m_pUser = pUser;
		memset(&m_event, 0, sizeof(m_event));
		socketpair(AF_UNIX, SOCK_STREAM, 0, m_event);
		pthread_create(&m_timerTread, NULL, CTimer::OnTimerFunc, this);
	}
	return J_OK;
}

int CTimer::Destroy()
{
	if (m_bStart)
	{
		send(m_event[1], "0", 1, MSG_NOSIGNAL);
		close(m_event[1]);
		m_bStart = false;
		pthread_cancel(m_timerTread);
		//pthread_join(m_timerTread, NULL);
		pthread_detach(m_timerTread);
	}

	return J_OK;
}

void CTimer::OnTimer()
{
	fd_set fdSet;
	FD_ZERO(&fdSet);
	FD_SET(m_event[0], &fdSet);

	timeval tv;
	while (m_bStart)
	{
		tv.tv_sec = m_nExpires / 1000;
		tv.tv_usec = (m_nExpires % 1000) * 1000;

		FD_ZERO(&fdSet);
		FD_SET(m_event[0], &fdSet);
		if(select(m_event[0] + 1, &fdSet, NULL, NULL, &tv) < 0)
		{
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

		m_timerFunc(m_pUser);
	}
}

}

