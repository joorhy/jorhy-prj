#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <process.h>
#endif

#include "BTKBase.h"
#include "BTKCommon.h"

/*******************************Declear******************************/
class BTKThreadMisc;
class BTKMutexLock;
class BTKSpinLock;
class BTKCond;
class BTKSem;
class BTKRWLock;
class BTKThread;
class BTKTimer;

#ifdef _WIN32
typedef struct
{
	 CRITICAL_SECTION mutex;
}btk_mutex_t;
#endif

typedef struct
{
	HANDLE   handle;
}btk_cond_t;


typedef struct
{
	HANDLE handle;
}btk_sem_t;


typedef struct
{
	btk_entry_t entry;
	void *data;
	int priority;
}btk_thread_t;

typedef struct  
{
	CRITICAL_SECTION spin;
	bool bUsed;
}btk_spin_t;

typedef struct 
{
	unsigned long time;
	btk_entry_timer_t cbk;
}btk_timer_t;

/*********************************Extra*******************************/
class BTKThreadMisc : public BTKBase
{
public:
	static DWORD WaitForSingleObject(HANDLE handle,DWORD delay);
	static DWORD WaitForMultipleObject(DWORD count,const HANDLE *handles,DWORD delay);
	static DWORD Sleep(DWORD delay);
	/*** Clock ***/
	static btk_mtime_t MakeDate(void);
	static btk_lldiv_t lldiv(long long num, long long denom);
	static unsigned GetCPUCount();
};

/*****************************************mutex Lock********************/
class BTKMutexLock : public BTKBase
{
public:
	BTKMutexLock(void);
	~BTKMutexLock(void);

	void Lock();
	void Unlock();
	int Trylock();

private:
	btk_mutex_t m_mutex;
};

/*******************************Condition variables*********************/

class BTKCond : public BTKBase
{
public:
	BTKCond();
	BTKCond(BOOL bManualReset,BOOL bInitialState,LPCTSTR lpName);
	~BTKCond();
	
	void Single();
	void Unsingle();
	void Broadcast();
	void Wait(BTKMutexLock &mutex);
	int WaitTime(btk_mtime_t deadline,BTKMutexLock &mutex);
	void Wait();
	int WaitTime(btk_mtime_t deadline);

private:
	btk_cond_t m_cond;
};

/******************************Semaphore******************************/
class BTKSem : public BTKBase
{
public:
	BTKSem();
	BTKSem(LONG InitCount,LONG MaxCount,LPCTSTR lpName);
	~BTKSem();

	void Post();
	void Post(int n);
	void Wait();
	void WaitTime(int ms_time);			//等待多长时间
	void Wait(int times);			//等待多少次

private:
	btk_sem_t m_sem;
};

/***********************************Read/write locks********************************/
class BTKRWLock : public BTKBase
{
public:
	BTKRWLock();
	~BTKRWLock();

	void ReadLock();
	void ReadUnlock();
	void WriteLock();
	void WriteUnlock();
	void Unlock();

private:
	DWORD m_readers;
	DWORD m_writers;
	DWORD m_writer;
	BTKMutexLock m_mutex;
	BTKCond	m_wait;
};

/**********************************Threads*********************************/
class BTKThread : public BTKBase
{
public:
	BTKThread();
	~BTKThread();

	BTK_RESULT Create(btk_thread_t &parm);
	BTK_RESULT Suspend();
	BTK_RESULT Resume();
	void Release();			//强行退出

private:
	btk_thread_t m_parm;
	HANDLE m_hThread;
};

class BTKSpinLock
{
public:
	BTKSpinLock(void);
	~BTKSpinLock(void);

	void Lock();
	void Unlock();

private:
	btk_spin_t m_spin;
};


class BTKTimer
{
public:
	BTKTimer(void);
	~BTKTimer(void);

	BTK_RESULT Create(btk_timer_t &parm);

private:
	static void BTKAPI TimeCbk(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	UINT_PTR m_handle;
};