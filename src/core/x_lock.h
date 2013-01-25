#ifndef __X_LOCK_H_
#define __X_LOCK_H_

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>

namespace J_OS
{

///线程锁
#define TLocker_t CTLock
#define TLock(x) ((x)._Lock())
#define TUnlock(x) ((x)._Unlock())

class CTLock
{
public:
	CTLock();
    ~CTLock();
    CTLock &operator=(CTLock &other)
     {
    	 m_mut = other.m_mut;
    	 return *this;
     }

    void _Lock();
    void _Unlock();

private:
    pthread_mutex_t m_mut;
};

///进程锁
#define PLocker_t CPLock
#define PLock(x) (x)._Lock()
#define PUnlock(x) (x)._Unlock()

class CPLock
{
public:
	CPLock();
	~CPLock();

	void _Lock();
	void _Unlock();

private:
	int m_lockfd;
	struct flock m_flock;
};

///读写锁
#define RWLocker_t CRWLock
#define RLock(x) (x)._RLock()
#define WLock(x) (x)._WLock()
#define RWUnlock(x) (x)._Unlock()

class CRWLock
{
public:
	CRWLock();
	~CRWLock();

	void _RLock();
	void _WLock();
	void _Unlock();

private:
	pthread_rwlock_t m_rwlock;
};

///递归锁
#define RECLocker_t CRECLock
#define RECLock(x) (x)._Lock()
#define RECUnlock(x) (x)._Unlock()
class CRECLock
{
public:
	CRECLock();
	~CRECLock();

	typedef struct _PrivInfo
	{
		CTLock locker;
		pthread_t current_thread_locker;
		int locker_count;
	} PrivInfo;

	void _Lock();
	void _Unlock();

private:
	PrivInfo m_info;
};

}

#endif //~__X_LOCK_H_
