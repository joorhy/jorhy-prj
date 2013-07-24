#include "x_lock.h"

namespace J_OS
{

CTLock::CTLock()
{
#ifdef WIN32
	InitializeCriticalSection (&m_mutex.mutex);
#else
    pthread_mutex_init(&m_mutex.mutex, NULL);
#endif
}

CTLock::~CTLock()
{
#ifdef WIN32
	DeleteCriticalSection(&m_mutex.mutex);
#else
    pthread_mutex_destroy(&m_mutex.mutex);
#endif
}

void CTLock::_Lock()
{
#ifdef WIN32
	EnterCriticalSection (&m_mutex.mutex);
#else
    pthread_mutex_lock(&m_mutex.mutex);
#endif
}

void CTLock::_Unlock()
{
#ifdef WIN32
	LeaveCriticalSection (&m_mutex.mutex);
#else
    pthread_mutex_unlock(&m_mutex.mutex);
#endif
}

CXCond::CXCond()
{
#ifdef WIN32
	m_cond.handle = CreateEvent(NULL, FALSE, FALSE, NULL);
#else
	pthread_mutex_init(&m_cond.mutex, NULL);
	pthread_cond_init(&m_cond.handle, NULL);
#endif
}

CXCond::~CXCond()
{
#ifdef WIN32
	CloseHandle(m_cond.handle);
#else
	pthread_mutex_destroy(&m_cond.mutex);
	pthread_cond_destroy(&m_cond.handle);
#endif
}

void CXCond::Single()
{
#ifdef WIN32
	SetEvent(m_cond.handle);
#else
	pthread_cond_signal(&m_cond.handle);
#endif
}

void CXCond::Wait()
{
#ifdef WIN32
	WaitForSingleObject(m_cond.handle, INFINITE);
#else
	pthread_mutex_lock(&m_cond.mutex);
	pthread_cond_wait(&m_cond.handle, &m_cond.mutex);
	pthread_mutex_unlock(&m_cond.mutex);
#endif
}

void CXCond::Wait(CTLock &mutex)
{
		mutex._Unlock();
#ifdef WIN32
		WaitForSingleObject(m_cond.handle,INFINITE);
#else
		pthread_mutex_lock(&m_cond.mutex);
		pthread_cond_wait(&m_cond.handle, &m_cond.mutex);
		pthread_mutex_unlock(&m_cond.mutex);
#endif
		mutex._Lock();
}

j_result_t CXCond::TimeWait(CTLock &mutex, j_uint32_t sec, j_uint32_t nsec)
{
	int nRet = 1;
#ifdef WIN32
	WaitForSingleObject(m_cond.handle, sec * 1000);
#else
	struct timespec tspec = {0};
	tspec.tv_sec = time(0) + sec; 
	tspec.tv_nsec = nsec;
	pthread_mutex_lock(&m_cond.mutex);
	nRet = pthread_cond_timedwait(&m_cond.handle, &m_cond.mutex, &tspec);
	pthread_mutex_unlock(&m_cond.mutex);
#endif

	return nRet > 0 ? J_OK : J_UNKNOW;
}

CPLock::CPLock()
{
	m_lock.hFile = j_invalid_filemap_val;
#ifdef WIN32
	m_lock.hFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, TRUE, "p.txt");
	if (m_lock.hFile == j_invalid_filemap_val)
		m_lock.hFile  = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 256, "p.txt");
#else
	m_lock.hFile = open("p.txt", O_WRONLY|O_CREAT, 0777);
#endif
}

CPLock::~CPLock()
{
	if (m_lock.hFile != j_invalid_filemap_val)
#ifdef WIN32
		CloseHandle(m_lock.hFile);
#else
		close(m_lock.hFile);
#endif
}

void CPLock::_Lock()
{
#ifdef WIN32
	m_lock.flock = reinterpret_cast<char *>(MapViewOfFile(m_lock.hFile, FILE_MAP_ALL_ACCESS, 0, 0, 0));
#else
	m_lock.flock.l_type = F_WRLCK;
	m_lock.flock.l_whence = SEEK_SET;
	m_lock.flock.l_start = 0;
	m_lock.flock.l_len = 0;
	m_lock.flock.l_pid = getpid();

	fcntl(m_lock.hFile, F_SETLKW, &m_lock.flock);
#endif
}

void CPLock::_Unlock()
{
#ifdef WIN32
	UnmapViewOfFile(m_lock.flock);
#else
	fcntl(m_lock.hFile, F_SETLKW, F_UNLCK);
#endif
}

CRWLock::CRWLock()
{
	m_readers	= 0;
	m_writers	= 0;
	m_writer	= 0;
}

CRWLock::~CRWLock()
{

}

void CRWLock::_RLock()
{
	m_mutex._Lock();
	while(m_writer != 0)
	{
		assert(m_readers == 0);
		m_wait.Wait(m_mutex);
	}

	if(m_readers == ULONG_MAX)
		abort();
	m_readers++;
	m_mutex._Unlock();
}

void CRWLock::_RUnlock()
{
	m_mutex._Lock();
	assert (m_readers > 0);

	if(--m_readers == 0 && m_writers > 0)
		m_wait.Single();
	m_mutex._Unlock();
}

void CRWLock::_WLock()
{
	m_mutex._Lock();
	if(m_writers == ULONG_MAX)
		abort();

	m_writers++;
	/* Wait until nobody owns the lock in either way. */
	while(m_readers > 0 || m_writer != 0)
		m_wait.Wait(m_mutex);
	m_writers--;
	assert (m_writer == 0);
#ifdef WIN32
	m_writer = GetCurrentThreadId();
#else
	m_writer = pthread_self();
#endif
	m_mutex._Unlock();
}

void CRWLock::_WUnlock()
{
	m_mutex._Lock();
#ifdef WIN32
	assert (m_writer == GetCurrentThreadId ());
#else 
	assert (m_writer == pthread_self());
#endif
	assert (m_readers == 0);
	m_writer = 0;

	/* Let reader and writer compete. Scheduler decides who wins. */
	m_wait.Single();
	m_mutex._Unlock();
}

void CRWLock::_Unlock()
{
	if(m_writer != 0)
		_WUnlock();
	else
		_RUnlock();
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
#ifdef WIN32
	if (m_info.current_thread_locker == GetCurrentThread())
#else
	if (m_info.current_thread_locker == pthread_self())
#endif
		++m_info.locker_count;
	else
	{
		m_info.locker._Lock();
		m_info.locker_count = 1;
#ifdef WIN32
		m_info.current_thread_locker = GetCurrentThread();
#else
		m_info.current_thread_locker = pthread_self();
#endif
	}
}

void CRECLock::_Unlock()
{
#ifdef WIN32
	if (m_info.current_thread_locker == GetCurrentThread())
#else
	if (m_info.current_thread_locker == pthread_self())
#endif
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
