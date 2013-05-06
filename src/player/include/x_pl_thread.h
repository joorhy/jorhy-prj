#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <process.h>
#endif

#include "x_pl_base.h"
#include "x_pl_common.h"

/*******************************Declear******************************/
class J_PlThreadMisc;
class J_PlMutexLock;
class J_PlSpinLock;
class J_PlCond;
class J_PlSem;
class J_PlRWLock;
class J_PlThread;
class J_PlTimer;

#ifdef _WIN32
typedef struct
{
	 CRITICAL_SECTION mutex;
}j_pl_mutex_t;
#endif

typedef struct
{
	HANDLE   handle;
}j_pl_cond_t;


typedef struct
{
	HANDLE handle;
}j_pl_sem_t;


typedef struct
{
	j_pl_entry_t entry;
	void *data;
	int priority;
}j_pl_thread_t;

typedef struct  
{
	CRITICAL_SECTION spin;
	bool bUsed;
}j_pl_spin_t;

typedef struct 
{
	unsigned long time;
	j_pl_entry_timer_t cbk;
}j_pl_timer_t;

/*********************************Extra*******************************/
class J_PlThreadMisc : public J_PlBase
{
public:
	static DWORD WaitForSingleObject(HANDLE handle,DWORD delay);
	static DWORD WaitForMultipleObject(DWORD count,const HANDLE *handles,DWORD delay);
	static DWORD Sleep(DWORD delay);
	/*** Clock ***/
	static j_pl_mtime_t MakeDate(void);
	static j_pl_lldiv_t lldiv(long long num, long long denom);
	static unsigned GetCPUCount();
};

/*****************************************mutex Lock********************/
class J_PlMutexLock : public J_PlBase
{
public:
	J_PlMutexLock(void);
	~J_PlMutexLock(void);

	void Lock();
	void Unlock();
	int Trylock();

private:
	j_pl_mutex_t m_mutex;
};

/*******************************Condition variables*********************/

class J_PlCond : public J_PlBase
{
public:
	J_PlCond();
	J_PlCond(BOOL bManualReset,BOOL bInitialState,LPCTSTR lpName);
	~J_PlCond();
	
	void Single();
	void Unsingle();
	void Broadcast();
	void Wait(J_PlMutexLock &mutex);
	int WaitTime(j_pl_mtime_t deadline,J_PlMutexLock &mutex);
	void Wait();
	int WaitTime(j_pl_mtime_t deadline);

private:
	j_pl_cond_t m_cond;
};

/******************************Semaphore******************************/
class J_PlSem : public J_PlBase
{
public:
	J_PlSem();
	J_PlSem(LONG InitCount,LONG MaxCount,LPCTSTR lpName);
	~J_PlSem();

	void Post();
	void Post(int n);
	void Wait();
	void WaitTime(int ms_time);			//等待多长时间
	void Wait(int times);			//等待多少次

private:
	j_pl_sem_t m_sem;
};

/***********************************Read/write locks********************************/
class J_PlRWLock : public J_PlBase
{
public:
	J_PlRWLock();
	~J_PlRWLock();

	void ReadLock();
	void ReadUnlock();
	void WriteLock();
	void WriteUnlock();
	void Unlock();

private:
	DWORD m_readers;
	DWORD m_writers;
	DWORD m_writer;
	J_PlMutexLock m_mutex;
	J_PlCond	m_wait;
};

/**********************************Threads*********************************/
class J_PlThread : public J_PlBase
{
public:
	J_PlThread();
	~J_PlThread();

	J_PL_RESULT Create(j_pl_thread_t &parm);
	J_PL_RESULT Suspend();
	J_PL_RESULT Resume();
	void Release();			//强行退出

private:
	j_pl_thread_t m_parm;
	HANDLE m_hThread;
};

class J_PlSpinLock
{
public:
	J_PlSpinLock(void);
	~J_PlSpinLock(void);

	void Lock();
	void Unlock();

private:
	j_pl_spin_t m_spin;
};


class J_PlTimer
{
public:
	J_PlTimer(void);
	~J_PlTimer(void);

	J_PL_RESULT Create(j_pl_timer_t &parm);

private:
	static void X_PL_API TimeCbk(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	UINT_PTR m_handle;
};