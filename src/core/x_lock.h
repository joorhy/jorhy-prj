#ifndef __X_LOCK_H_
#define __X_LOCK_H_

#include "j_common.h"

namespace J_OS
{
///线程锁
#define TLocker_t CTLock
#define TLock(x) ((x)._Lock())
#define TUnlock(x) ((x)._Unlock())

class JO_API CTLock
{
public:
	CTLock();
    ~CTLock();
    CTLock &operator=(CTLock &other)
     {
    	 m_mutex = other.m_mutex;
    	 return *this;
     }

    void _Lock();
    void _Unlock();

private:
	j_mutex_t m_mutex;
};

///条件变量
class JO_API CXCond
{
public:
	CXCond();
	~CXCond();

	void Single();
	void Wait();
	void Wait(CTLock &mutex);
	j_result_t TimeWait(CTLock &mutex, j_uint32_t sec, j_uint32_t nsec);

private:
	j_cond_t m_cond;
};

///进程锁
#define PLocker_t CPLock
#define PLock(x) (x)._Lock()
#define PUnlock(x) (x)._Unlock()

class JO_API CPLock
{
public:
	CPLock();
	~CPLock();

	void _Lock();
	void _Unlock();

private:
	j_filemap_t m_lock;
};

///读写锁
#define RWLocker_t CRWLock
#define RLock(x) (x)._RLock()
#define RUnlock(x) (x)._RUnlock()
#define WLock(x) (x)._WLock()
#define WUnlock(x) (x)._WUnlock()
#define RWUnlock(x) (x)._Unlock()

class JO_API CRWLock
{
public:
	CRWLock();
	~CRWLock();

	void _RLock();
	void _RUnlock();
	void _WLock();
	void _WUnlock();
	void _Unlock();

private:
	j_uint32_t m_readers;
	j_uint32_t m_writers;
	j_uint32_t m_writer;
	CTLock m_mutex;
	CXCond m_wait;
};

///递归锁
#define RECLocker_t CRECLock
#define RECLock(x) (x)._Lock()
#define RECUnlock(x) (x)._Unlock()
class JO_API CRECLock
{
public:
	CRECLock();
	~CRECLock();

	typedef struct _PrivInfo
	{
		CTLock locker;
		j_thread_t current_thread_locker;
		int locker_count;
	} PrivInfo;

	void _Lock();
	void _Unlock();

private:
	PrivInfo m_info;
};

}

#endif //~__X_LOCK_H_
