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
	m_threadMutex._Lock();
	m_taskQueue.push(task);
	m_threadMutex._Unlock();
	
	m_threadCond.Single();

	return J_OK;
}

int CThreadPool::Create(int nThreadNum)
{
	m_bShutDown = false;

	int i;
	for (i = 0; i < nThreadNum; i++)
	{
		j_thread_parm parm = {0};
		parm.entry = CThreadPool::ThreadFunc;
		parm.data = this;
		m_thread.Create(parm);
	}

	return J_OK;
}

int CThreadPool::Destroy()
{
	if (m_bShutDown)
		return J_UNKNOW;
		
	m_bShutDown = true;
	m_threadCond.Single();
	
	return J_OK;
}

void CThreadPool::OnThreadFunc()
{
	m_threadMutex._Lock();
	if (m_taskQueue.empty() && !m_bShutDown)
	{
		m_threadCond.Wait(m_threadMutex);
	}
	
	if (m_bShutDown)
	{
		m_threadMutex._Unlock();
		m_thread.Release();
	}
	
	J_Task *pTask = m_taskQueue.front();
	m_taskQueue.pop();
	m_threadMutex._Unlock();
	
	pTask->Run();
	delete pTask;
}




