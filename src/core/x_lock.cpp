#include "x_lock.h"

namespace J_OS
{

CTLock::CTLock()
{
    pthread_mutex_init(&m_mut, NULL);
}

CTLock::~CTLock()
{
    pthread_mutex_destroy(&m_mut);
}

void CTLock::_Lock()
{
    pthread_mutex_lock(&m_mut);
}

void CTLock::_Unlock()
{
    pthread_mutex_unlock(&m_mut);
}

CPLock::CPLock()
: m_lockfd(-1)
{
	m_lockfd = open("p.txt", O_WRONLY|O_CREAT, 0777);
}

CPLock::~CPLock()
{
	if (m_lockfd > 0)
		close(m_lockfd);
}

void CPLock::_Lock()
{
	m_flock.l_type = F_WRLCK;
	m_flock.l_whence = SEEK_SET;
	m_flock.l_start = 0;
	m_flock.l_len = 0;
	m_flock.l_pid = getpid();

	fcntl(m_lockfd, F_SETLKW, &m_flock);
}

void CPLock::_Unlock()
{
	fcntl(m_lockfd, F_SETLKW, F_UNLCK);
}

CRWLock::CRWLock()
{
	pthread_rwlock_init(&m_rwlock, NULL);
}

CRWLock::~CRWLock()
{
	pthread_rwlock_destroy(&m_rwlock);
}

void CRWLock::_RLock()
{
	pthread_rwlock_rdlock(&m_rwlock);;
}

void CRWLock::_WLock()
{
	pthread_rwlock_wrlock(&m_rwlock);
}

void CRWLock::_Unlock()
{
	pthread_rwlock_unlock(&m_rwlock);
}

CRECLock::CRECLock()
{
	m_info.current_thread_locker = 0;
	m_info.locker_count = 0;
}

CRECLock::~CRECLock()
{

}

void CRECLock::_Lock()
{
	if (m_info.current_thread_locker == pthread_self())
		++m_info.locker_count;
	else
	{
		m_info.locker._Lock();
		m_info.locker_count = 1;
		m_info.current_thread_locker = pthread_self();
	}
}

void CRECLock::_Unlock()
{
	if (m_info.current_thread_locker == pthread_self())
	{
		if (m_info.locker_count == 1)
		{
			m_info.locker_count = 0;
			m_info.current_thread_locker = 0;
			m_info.locker._Unlock();
		}
		else
			--m_info.locker_count;
	}
}

}
