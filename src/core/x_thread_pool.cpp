#include "x_errtype.h"
#include "x_thread_pool.h"
#include "x_log.h"

CThreadPool::CThreadPool(int)
{
	m_bShutDown = false;
}

CThreadPool::~CThreadPool()
{

}

int CThreadPool::AddTask(J_Task *task)
{
	//printf("lock out\n");
	pthread_mutex_lock(&m_threadMutex);
	//printf("unlock out\n");
	m_taskQueue.push(task);
	pthread_mutex_unlock(&m_threadMutex);
	
	pthread_cond_signal(&m_threadCond);

	return J_OK;
}

int CThreadPool::Create(int nThreadNum)
{
	m_bShutDown = false;
	pthread_mutex_init(&m_threadMutex, NULL);
	pthread_cond_init(&m_threadCond, NULL);

	int i;
	for (i = 0; i < nThreadNum; i++)
	{
		pthread_t tid = 0;
		pthread_create(&tid, NULL, CThreadPool::ThreadFunc, this);
		pthread_detach(tid);
	}

	return J_OK;
}

int CThreadPool::Destroy()
{
	if (m_bShutDown)
		return J_UNKNOW;
		
	m_bShutDown = true;
	pthread_cond_broadcast(&m_threadCond);
	
	pthread_mutex_destroy(&m_threadMutex);
	pthread_cond_destroy(&m_threadCond);

	return J_OK;
}

void CThreadPool::OnThreadFunc()
{
	pthread_mutex_lock (&m_threadMutex);
	if (m_taskQueue.empty() && !m_bShutDown)
	{
		//printf("thread %x is waiting\n", pthread_self());
		printf("lock in\n");
		pthread_cond_wait(&m_threadCond, &m_threadMutex);
		printf("unlock in\n");
	}
	
	if (m_bShutDown)
	{
		printf("thread exit\n");
		pthread_mutex_unlock(&m_threadMutex);
		pthread_exit(NULL);
	}
	
	J_Task *pTask = m_taskQueue.front();
	m_taskQueue.pop();
	//printf("m_taskList %d is waiting\n", m_taskList.size());
	pthread_mutex_unlock(&m_threadMutex);
	
	pTask->Run();
	//printf("thread %d is waiting\n", pTask->m_pParam);
	delete pTask;
}




