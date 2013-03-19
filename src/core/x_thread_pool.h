#ifndef __X_THREAD_POOL_H_
#define __X_THREAD_POOL_H_

#include "x_lock.h"
#include "j_module.h"
#include "x_singleton.h"

class CThreadPool : public SingletonTmpl<CThreadPool>
{
public:
	CThreadPool(int);
	~CThreadPool();
	
protected:
	CThreadPool() {}
	
public:
	///添加任务到线程池
	///@param task 将要添加的任务
	///@return 参见x_error_type.h
	int AddTask(J_Task *task);

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
		while (true)
		{
			CThreadPool *pThis = static_cast<CThreadPool *>(param);
			pThis->OnThreadFunc();
		}
		return (void *)0;
	}
	void OnThreadFunc();

private:
	j_queue_task m_taskQueue;
	pthread_mutex_t m_threadMutex;
	pthread_cond_t m_threadCond;
	bool m_bShutDown; 
};

#endif // __X_THREAD_POOL_H_
