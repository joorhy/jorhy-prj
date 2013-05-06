#include "x_pl_thread.h"
#include "x_pl_error.h"
#include "x_pl_log.h"
#include <stdio.h>
#include <assert.h>

J_PlMutexLock::J_PlMutexLock(void)
{
	InitializeCriticalSection (&m_mutex.mutex);
}

J_PlMutexLock::~J_PlMutexLock(void)
{
	DeleteCriticalSection(&m_mutex.mutex);
}

void J_PlMutexLock::Lock()
{
	EnterCriticalSection (&m_mutex.mutex);
}

void J_PlMutexLock::Unlock()
{
	LeaveCriticalSection (&m_mutex.mutex);
}

int J_PlMutexLock::Trylock()
{
	return TryEnterCriticalSection(&m_mutex.mutex);
}

/**************************Condition variables*****************************/
J_PlCond::J_PlCond()
{
	m_cond.handle = CreateEvent(NULL,		//安全属性
								TRUE,		//复位方式，TRUE为手动
								FALSE,		//初始状态，是否有信号
								NULL		//对象名字，大小写敏感
								);
}

J_PlCond::J_PlCond(BOOL bManualReset,BOOL bInitialState,LPCTSTR lpName)
{
	m_cond.handle = CreateEvent(NULL,bManualReset,bInitialState,lpName);
}

J_PlCond::~J_PlCond()
{
	CloseHandle(m_cond.handle);
}

void J_PlCond::Single()
{
	Broadcast();
}

void J_PlCond::Unsingle()
{
	ResetEvent (m_cond.handle);
}

void J_PlCond::Broadcast()
{
	SetEvent(m_cond.handle);
}

void J_PlCond::Wait(J_PlMutexLock &mutex)
{
	DWORD ret;
	do
	{
		mutex.Unlock();
		ret = J_PlThreadMisc::WaitForSingleObject(m_cond.handle,INFINITE);
		mutex.Lock();
	} while (ret == WAIT_IO_COMPLETION);

}
 
int J_PlCond::WaitTime(j_pl_mtime_t deadline,J_PlMutexLock &mutex)
{
	DWORD ret;
	do
	{
		j_pl_mtime_t total;
		total = J_PlThreadMisc::MakeDate();
		total = (deadline - total) / 1000;
		if( total < 0 )
			total = 0;
		mutex.Unlock();
		DWORD delay = (total > INT_MAX) ? INT_MAX : total;
		mutex.Lock();
		ret = J_PlThreadMisc::WaitForSingleObject(m_cond.handle,delay);
	} while (ret == WAIT_IO_COMPLETION);

	ResetEvent (m_cond.handle);
	return ret == WAIT_OBJECT_0;
}

void J_PlCond::Wait()
{
	DWORD ret;
	do
	{
		ret = J_PlThreadMisc::WaitForSingleObject(m_cond.handle,INFINITE);
	} while (ret == WAIT_IO_COMPLETION);
	//ResetEvent (m_cond.handle);
}

int J_PlCond::WaitTime(j_pl_mtime_t deadline)
{
	DWORD ret;
	do
	{
		j_pl_mtime_t total;
		total = J_PlThreadMisc::MakeDate();
		total = (deadline - total) / 1000;
		if( total < 0 )
			total = 0;
		DWORD delay = (total > INT_MAX) ? INT_MAX : total;
		ret = J_PlThreadMisc::WaitForSingleObject(m_cond.handle,delay);
	} while (ret == WAIT_IO_COMPLETION);

	//ResetEvent (m_cond.handle);
	return ret == WAIT_OBJECT_0;
}

/****************************Extra***********************************/
DWORD J_PlThreadMisc::WaitForSingleObject(HANDLE handle,DWORD delay)
{
	return J_PlThreadMisc::WaitForMultipleObject(1,&handle,delay);
}

DWORD J_PlThreadMisc::WaitForMultipleObject(DWORD count,const HANDLE *handles,DWORD delay)
{
	DWORD ret;
	if(count == 0)
	{
		ret = SleepEx(delay,TRUE);
		if(ret == 0)
			ret =  WAIT_TIMEOUT;
	}
	else
		ret = WaitForMultipleObjectsEx (count, handles, FALSE, delay, TRUE);

	if(ret == WAIT_FAILED)
		abort();
	return ret;
}

j_pl_mtime_t J_PlThreadMisc::MakeDate(void)
{
	LARGE_INTEGER counter, freq;
	if (!QueryPerformanceCounter (&counter) || !QueryPerformanceFrequency (&freq))
		abort();

	/* Convert to from (1/freq) to microsecond resolution */
	/* We need to split the division to avoid 63-bits overflow */
	j_pl_lldiv_t d = lldiv (counter.QuadPart, freq.QuadPart);

	return (d.quot * 1000000) + ((d.rem * 1000000) / freq.QuadPart);
}

j_pl_lldiv_t J_PlThreadMisc::lldiv(long long num, long long denom)
{
	j_pl_lldiv_t d = {num / denom, num % denom,};
	return d;
}

DWORD J_PlThreadMisc::Sleep(DWORD delay)
{
	DWORD ret = J_PlThreadMisc::WaitForMultipleObject(0,NULL,delay);
	return (ret != WAIT_TIMEOUT) ? ret : 0;
}

unsigned J_PlThreadMisc::GetCPUCount()
{
#ifndef UNDER_CE
	DWORD_PTR process;
	DWORD_PTR system;
	unsigned count = 0;

	if (GetProcessAffinityMask (GetCurrentProcess(), &process, &system))
	{
		while(system)
		{
			count += system & 1;
			count >>= 1;
		}
		return count;
	}
#endif
	return 1;
}

/*************************************Sem********************************/
J_PlSem::J_PlSem()
{
	m_sem.handle =  CreateSemaphore (NULL,0,INT_MAX,NULL);
}

J_PlSem::J_PlSem(LONG InitCount,LONG MaxCount,LPCTSTR lpName)
{
	m_sem.handle =  CreateSemaphore (NULL,InitCount,MaxCount,lpName);
}

J_PlSem::~J_PlSem()
{
	CloseHandle(m_sem.handle);
}

void J_PlSem::Post()
{
	ReleaseSemaphore (m_sem.handle,1,NULL);
}

void J_PlSem::Post(int n)
{
	if(n < 0)
		return;
	ReleaseSemaphore (m_sem.handle,n,NULL);
}

void J_PlSem::Wait()
{
	DWORD ret;

	do
	{
		ret = J_PlThreadMisc::WaitForSingleObject(m_sem.handle,INFINITE);
	}
	while (ret == WAIT_IO_COMPLETION);
}

void J_PlSem::WaitTime(int ms_time)
{
	DWORD ret;

	do
	{
		ret = J_PlThreadMisc::WaitForSingleObject(m_sem.handle,ms_time);
	}
	while (ret == WAIT_IO_COMPLETION);
}

void J_PlSem::Wait(int times)
{
	for(int i=0;i<times;i++)
		Wait();
}


/*********************************Read/write locks*************************************/
J_PlRWLock::J_PlRWLock()
{
	m_readers	= 0;
	m_writers	= 0;
	m_writer	= 0;
}

J_PlRWLock::~J_PlRWLock()
{
	
}

void J_PlRWLock::ReadLock()
{
	/* Recursive read-locking is allowed. With the infos available:
	*  - the loosest possible condition (no active writer) is:
	*     (m_writer != 0)
	*  - the strictest possible condition is:
	*     (m_writer != 0 || (m_readers == 0 && m_writers > 0))
	*  or (m_readers == 0 && (m_writer != 0 || m_writers > 0))
	*/
	m_mutex.Lock();
	while(m_writer != 0)
	{
		assert(m_readers == 0);
		m_wait.Wait(m_mutex);
	}

	if(m_readers == ULONG_MAX)
		abort();
	m_readers++;
	m_mutex.Unlock();
}

void J_PlRWLock::ReadUnlock()
{
	m_mutex.Lock();
	assert (m_readers > 0);

	if(--m_readers == 0 && m_writers > 0)
		m_wait.Single();
	m_mutex.Unlock();
}

void J_PlRWLock::WriteLock()
{
	m_mutex.Lock();
	if(m_writers == ULONG_MAX)
		abort();

	m_writers++;
	/* Wait until nobody owns the lock in either way. */
	while(m_readers > 0 || m_writer != 0)
		m_wait.Wait(m_mutex);
	m_writers--;
	assert (m_writer == 0);
	m_writer = GetCurrentThreadId();
	m_mutex.Unlock();
}

void J_PlRWLock::WriteUnlock()
{
	m_mutex.Lock();
	assert (m_writer == GetCurrentThreadId ());
	assert (m_readers == 0);
	m_writer = 0;

	/* Let reader and writer compete. Scheduler decides who wins. */
	m_wait.Broadcast();
	m_mutex.Unlock();
}

void J_PlRWLock::Unlock()
{
	if(m_writer != 0)
		WriteUnlock();
	else
		ReadUnlock();
}

/**********************************Threads*********************************/
J_PlThread::J_PlThread()
{
	memset(&m_parm,0,sizeof(m_parm));
	m_hThread = NULL;
}

J_PlThread::~J_PlThread()
{
	CloseHandle(m_hThread);
}

J_PL_RESULT J_PlThread::Create(j_pl_thread_t &parm)
{
	if(!parm.entry)
		return FALSE;
	m_hThread = (HANDLE)_beginthreadex(NULL,0,parm.entry,parm.data,CREATE_SUSPENDED,NULL);
	if(m_hThread == NULL)
		return J_PL_ERROR_THREAD_CREATE;

	if(parm.priority)
		SetThreadPriority (m_hThread,parm.priority);	//eg:THREAD_PRIORITY_NORMAL 

	Resume();
	return J_PL_NO_ERROR;
}

J_PL_RESULT J_PlThread::Suspend()
{
	DWORD ret = 0;
	if(m_hThread)
		ret = SuspendThread(m_hThread);
	return J_PL_NO_ERROR;
}

J_PL_RESULT J_PlThread::Resume()
{
	DWORD ret = 0;
	if(m_hThread)
		ret = ResumeThread (m_hThread);
	return J_PL_NO_ERROR;
}

void J_PlThread::Release()
{
	if(m_hThread)
	{
		_endthreadex((uintptr_t)m_hThread);
		CloseHandle(m_hThread);
		m_hThread = 0;
	}
}

/**********************************Spin Lock*********************************/
J_PlSpinLock::J_PlSpinLock()
{
	if(InitializeCriticalSectionAndSpinCount(&m_spin.spin,4000))
		m_spin.bUsed = true;
	else
		m_spin.bUsed = false;
}

J_PlSpinLock::~J_PlSpinLock()
{
	if(m_spin.bUsed)
	{
		DeleteCriticalSection(&m_spin.spin);
	}
}

void J_PlSpinLock::Lock()
{
	if(m_spin.bUsed)
	{
		EnterCriticalSection(&m_spin.spin);
	}
}

void J_PlSpinLock::Unlock()
{
	if(m_spin.bUsed)
	{
		LeaveCriticalSection(&m_spin.spin);
	}
}

/**********************************Timer*********************************/
J_PlTimer::J_PlTimer()
{

}

J_PlTimer::~J_PlTimer()
{
	KillTimer(NULL,m_handle);
}

J_PL_RESULT J_PlTimer::Create(j_pl_timer_t &parm)
{
	m_handle = SetTimer(NULL,NULL,parm.time,TimeCbk);
	return J_PL_NO_ERROR;
}

void X_PL_API J_PlTimer::TimeCbk(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	
}