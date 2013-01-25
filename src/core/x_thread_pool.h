#ifndef __X_THREAD_POOL_H_
#define __X_THREAD_POOL_H_

#include "x_lock.h"

#include <list>
#include <vector>
#include <string>
#include <semaphore.h>

class CThreadPool;

struct STaskAttr
{
	int needDel;			//是否需要删除任务
};

class CTask
{
	friend class CThreadPool;
public:
	CTask() : m_pUser(NULL) {}
	~CTask() {}

public:
	///设置任务属性
	///@param pUser	用户参数
	///@param pAttr	任务属性
	void SetTask(void *pUser, STaskAttr attr);

	///任务的工作函数,由使用者实现
	///@param pUser 用户参数
	///@return 参见x_error_type.h
	virtual int Run(void *pUser) = 0;

protected:
	void *GetUser() const { return m_pUser; }
	STaskAttr &GetAttribute() { return m_attr; }

private:
	void *m_pUser;
	STaskAttr m_attr;
};

class CThreadPool
{
public:
	CThreadPool();
	CThreadPool(int nThreadNum);
	~CThreadPool();

public:
	///添加任务到线程池
	///@param task 将要添加的任务
	///@param gid 任务组ID
	///@return 参见x_error_type.h
	int AddTask(CTask *task, int gid);

	///从线程池删除一个任务
	///@param task 将要删除的任务
	///@return 参见x_error_type.h
	int DelTask(CTask *task);

	///从线程池删除一组任务
	///@param gid 将要删除任务的组ID
	///@return 参见x_error_type.h
	int DelAll(int gid);

	///创建线程池
	///@param nThreadNum 线程池中的线程数量
	///@return 参见x_error_type.h
	int Create(int nThreadNum);

	///销毁线程池
	///@return 参见x_error_type.h
	int Destroy();

private:
	static void *ThreadFunc(void *param)
	{
		ThreadInfo *pInfo = static_cast<ThreadInfo *>(param);
		pInfo->pUser->OnThreadFunc(&pInfo->taskList);

		return (void *)0;
	}
	void OnThreadFunc(void *param);

private:
	struct TaskInfo
	{
		CTask *task;
		int gid;
	};
	typedef std::list<TaskInfo> TaskList;
	typedef std::vector<pthread_t> ThreadVec;
	struct ThreadInfo
	{
		CThreadPool *pUser;
		TaskList taskList;
	} m_threadInfo;

	int m_nThreadNum;
	ThreadVec m_vecIdleThread;
	pthread_mutex_t m_threadMutex;
	sem_t m_threadSem;
};

#endif // __X_THREAD_POOL_H_
