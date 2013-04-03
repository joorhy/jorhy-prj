#include "..\..\include\BTKThread.h"
#include "..\..\include\BTKError.h"
#include "..\..\include\BTKLog.h"
#include <stdio.h>
#include <assert.h>

BTKMutexLock::BTKMutexLock(void)
{
	InitializeCriticalSection (&m_mutex.mutex);
}

BTKMutexLock::~BTKMutexLock(void)
{
	DeleteCriticalSection(&m_mutex.mutex);
}

void BTKMutexLock::Lock()
{
	EnterCriticalSection (&m_mutex.mutex);
}

void BTKMutexLock::Unlock()
{
	LeaveCriticalSection (&m_mutex.mutex);
}

int BTKMutexLock::Trylock()
{
	return TryEnterCriticalSection(&m_mutex.mutex);
}

/**************************Condition variables*****************************/
BTKCond::BTKCond()
{
	m_cond.handle = CreateEvent(NULL,		//安全属性
								TRUE,		//复位方式，TRUE为手动
								FALSE,		//初始状态，是否有信号
								NULL		//对象名字，大小写敏感
								);
}

BTKCond::BTKCond(BOOL bManualReset,BOOL bInitialState,LPCTSTR lpName)
{
	m_cond.handle = CreateEvent(NULL,bManualReset,bInitialState,lpName);
}

BTKCond::~BTKCond()
{
	CloseHandle(m_cond.handle);
}

void BTKCond::Single()
{
	Broadcast();
}

void BTKCond::Unsingle()
{
	ResetEvent (m_cond.handle);
}

void BTKCond::Broadcast()
{
	SetEvent(m_cond.handle);
}

void BTKCond::Wait(BTKMutexLock &mutex)
{
	DWORD ret;
	do
	{
		mutex.Unlock();
		ret = BTKThreadMisc::WaitForSingleObject(m_cond.handle,INFINITE);
		mutex.Lock();
	} while (ret == WAIT_IO_COMPLETION);

}
 
int BTKCond::WaitTime(btk_mtime_t deadline,BTKMutexLock &mutex)
{
	DWORD ret;
	do
	{
		btk_mtime_t total;
		total = BTKThreadMisc::MakeDate();
		total = (deadline - total) / 1000;
		if( total < 0 )
			total = 0;
		mutex.Unlock();
		DWORD delay = (total > INT_MAX) ? INT_MAX : total;
		mutex.Lock();
		ret = BTKThreadMisc::WaitForSingleObject(m_cond.handle,delay);
	} while (ret == WAIT_IO_COMPLETION);

	ResetEvent (m_cond.handle);
	return ret == WAIT_OBJECT_0;
}

void BTKCond::Wait()
{
	DWORD ret;
	do
	{
		ret = BTKThreadMisc::WaitForSingleObject(m_cond.handle,INFINITE);
	} while (ret == WAIT_IO_COMPLETION);
	//ResetEvent (m_cond.handle);
}

int BTKCond::WaitTime(btk_mtime_t deadline)
{
	DWORD ret;
	do
	{
		btk_mtime_t total;
		total = BTKThreadMisc::MakeDate();
		total = (deadline - total) / 1000;
		if( total < 0 )
			total = 0;
		DWORD delay = (total > INT_MAX) ? INT_MAX : total;
		ret = BTKThreadMisc::WaitForSingleObject(m_cond.handle,delay);
	} while (ret == WAIT_IO_COMPLETION);

	//ResetEvent (m_cond.handle);
	return ret == WAIT_OBJECT_0;
}

/****************************Extra***********************************/
DWORD BTKThreadMisc::WaitForSingleObject(HANDLE handle,DWORD delay)
{
	return BTKThreadMisc::WaitForMultipleObject(1,&handle,delay);
}

DWORD BTKThreadMisc::WaitForMultipleObject(DWORD count,const HANDLE *handles,DWORD delay)
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

btk_mtime_t BTKThreadMisc::MakeDate(void)
{
	LARGE_INTEGER counter, freq;
	if (!QueryPerformanceCounter (&counter) || !QueryPerformanceFrequency (&freq))
		abort();

	/* Convert to from (1/freq) to microsecond resolution */
	/* We need to split the division to avoid 63-bits overflow */
	btk_lldiv_t d = lldiv (counter.QuadPart, freq.QuadPart);

	return (d.quot * 1000000) + ((d.rem * 1000000) / freq.QuadPart);
}

btk_lldiv_t BTKThreadMisc::lldiv(long long num, long long denom)
{
	btk_lldiv_t d = {num / denom, num % denom,};
	return d;
}

DWORD BTKThreadMisc::Sleep(DWORD delay)
{
	DWORD ret = BTKThreadMisc::WaitForMultipleObject(0,NULL,delay);
	return (ret != WAIT_TIMEOUT) ? ret : 0;
}

unsigned BTKThreadMisc::GetCPUCount()
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
BTKSem::BTKSem()
{
	m_sem.handle =  CreateSemaphore (NULL,0,INT_MAX,NULL);
}

BTKSem::BTKSem(LONG InitCount,LONG MaxCount,LPCTSTR lpName)
{
	m_sem.handle =  CreateSemaphore (NULL,InitCount,MaxCount,lpName);
}

BTKSem::~BTKSem()
{
	CloseHandle(m_sem.handle);
}

void BTKSem::Post()
{
	ReleaseSemaphore (m_sem.handle,1,NULL);
}

void BTKSem::Post(int n)
{
	if(n < 0)
		return;
	ReleaseSemaphore (m_sem.handle,n,NULL);
}

void BTKSem::Wait()
{
	DWORD ret;

	do
	{
		ret = BTKThreadMisc::WaitForSingleObject(m_sem.handle,INFINITE);
	}
	while (ret == WAIT_IO_COMPLETION);
}

void BTKSem::WaitTime(int ms_time)
{
	DWORD ret;

	do
	{
		ret = BTKThreadMisc::WaitForSingleObject(m_sem.handle,ms_time);
	}
	while (ret == WAIT_IO_COMPLETION);
}

void BTKSem::Wait(int times)
{
	for(int i=0;i<times;i++)
		Wait();
}


/*********************************Read/write locks*************************************/
BTKRWLock::BTKRWLock()
{
	m_readers	= 0;
	m_writers	= 0;
	m_writer	= 0;
}

BTKRWLock::~BTKRWLock()
{
	
}

void BTKRWLock::ReadLock()
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

void BTKRWLock::ReadUnlock()
{
	m_mutex.Lock();
	assert (m_readers > 0);

	if(--m_readers == 0 && m_writers > 0)
		m_wait.Single();
	m_mutex.Unlock();
}

void BTKRWLock::WriteLock()
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

void BTKRWLock::WriteUnlock()
{
	m_mutex.Lock();
	assert (m_writer == GetCurrentThreadId ());
	assert (m_readers == 0);
	m_writer = 0;

	/* Let reader and writer compete. Scheduler decides who wins. */
	m_wait.Broadcast();
	m_mutex.Unlock();
}

void BTKRWLock::Unlock()
{
	if(m_writer != 0)
		WriteUnlock();
	else
		ReadUnlock();
}

/**********************************Threads*********************************/
BTKThread::BTKThread()
{
	memset(&m_parm,0,sizeof(m_parm));
	m_hThread = NULL;
}

BTKThread::~BTKThread()
{
	CloseHandle(m_hThread);
}

BTK_RESULT BTKThread::Create(btk_thread_t &parm)
{
	if(!parm.entry)
		return FALSE;
	m_hThread = (HANDLE)_beginthreadex(NULL,0,parm.entry,parm.data,CREATE_SUSPENDED,NULL);
	if(m_hThread == NULL)
		return BTK_ERROR_THREAD_CREATE;

	if(parm.priority)
		SetThreadPriority (m_hThread,parm.priority);	//eg:THREAD_PRIORITY_NORMAL 

	Resume();
	return BTK_NO_ERROR;
}

BTK_RESULT BTKThread::Suspend()
{
	DWORD ret = 0;
	if(m_hThread)
		ret = SuspendThread(m_hThread);
	return BTK_NO_ERROR;
}

BTK_RESULT BTKThread::Resume()
{
	DWORD ret = 0;
	if(m_hThread)
		ret = ResumeThread (m_hThread);
	return BTK_NO_ERROR;
}

void BTKThread::Release()
{
	if(m_hThread)
	{
		_endthreadex((uintptr_t)m_hThread);
		CloseHandle(m_hThread);
		m_hThread = 0;
	}
}

/**********************************Spin Lock*********************************/
BTKSpinLock::BTKSpinLock()
{
	if(InitializeCriticalSectionAndSpinCount(&m_spin.spin,4000))
		m_spin.bUsed = true;
	else
		m_spin.bUsed = false;
}

BTKSpinLock::~BTKSpinLock()
{
	if(m_spin.bUsed)
	{
		DeleteCriticalSection(&m_spin.spin);
	}
}

void BTKSpinLock::Lock()
{
	if(m_spin.bUsed)
	{
		EnterCriticalSection(&m_spin.spin);
	}
}

void BTKSpinLock::Unlock()
{
	if(m_spin.bUsed)
	{
		LeaveCriticalSection(&m_spin.spin);
	}
}

/**********************************Timer*********************************/
BTKTimer::BTKTimer()
{

}

BTKTimer::~BTKTimer()
{
	KillTimer(NULL,m_handle);
}

BTK_RESULT BTKTimer::Create(btk_timer_t &parm)
{
	m_handle = SetTimer(NULL,NULL,parm.time,TimeCbk);
	return BTK_NO_ERROR;
}

void BTKAPI BTKTimer::TimeCbk(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	
}