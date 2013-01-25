#include "x_errtype.h"
#include "x_thread_pool.h"
#include "x_log.h"

void CTask::SetTask(void *pUser, STaskAttr attr)
{
	m_pUser = pUser;
	m_attr = attr;
}

CThreadPool::CThreadPool()
{
	pthread_mutex_init(&m_threadMutex, NULL);

	m_threadInfo.pUser = this;
}

CThreadPool::CThreadPool(int nThreadNum)
{
	m_nThreadNum = nThreadNum;
	pthread_mutex_init(&m_threadMutex, NULL);
	sem_init(&m_threadSem, 0, nThreadNum);

	m_threadInfo.pUser = this;

	Create(nThreadNum);
}

CThreadPool::~CThreadPool()
{
	pthread_mutex_destroy(&m_threadMutex);
	sem_destroy(&m_threadSem);
}

int CThreadPool::AddTask(CTask *task, int gid)
{
	pthread_mutex_lock(&m_threadMutex);
	TaskInfo info;
	info.task = task;
	info.gid = gid;
	m_threadInfo.taskList.push_back(info);
	pthread_mutex_unlock(&m_threadMutex);
	sem_post(&m_threadSem);
	//printf(" CThreadPool::AddTask\n");

	return J_OK;
}

int CThreadPool::DelTask(CTask *task)
{
	pthread_mutex_lock(&m_threadMutex);
	TaskList::iterator it = m_threadInfo.taskList.begin();
	for (; it != m_threadInfo.taskList.end(); it++)
	{
		if (it->task == task)
		{
			m_threadInfo.taskList.erase(it);
			pthread_mutex_unlock(&m_threadMutex);
			return J_OK;
		}
	}
	pthread_mutex_unlock(&m_threadMutex);

	return J_NOT_EXIST;
}

int CThreadPool::DelAll(int gid)
{
	pthread_mutex_lock(&m_threadMutex);
	bool bFinished = false;
	bool bContinue = false;
	TaskList::iterator it;
	while (!bFinished)
	{
		bContinue = false;
		it = m_threadInfo.taskList.begin();
		for (; it != m_threadInfo.taskList.end(); it++)
		{
			//J_OS::LOGINFO("DelAll(int %d)", gid);
			if (it->gid == gid)
			{
				J_OS::LOGINFO("DelAll2(int %d)", m_threadInfo.taskList.size());
				m_threadInfo.taskList.erase(it);
				J_OS::LOGINFO("DelAll3(int %d)", m_threadInfo.taskList.size());
				bContinue = true;
				break;
			}
		}
		bFinished = !bContinue;
	}
	pthread_mutex_unlock(&m_threadMutex);

	return J_NOT_EXIST;
}

int CThreadPool::Create(int nThreadNum)
{
	if (nThreadNum != 0)
		m_nThreadNum = nThreadNum;

	int i;
	for (i = 0; i < m_nThreadNum; i++)
	{
		pthread_t tid = 0;
		pthread_create(&tid, NULL, CThreadPool::ThreadFunc, &m_threadInfo);
		pthread_detach(tid);
		m_vecIdleThread.push_back(tid);
	}

	return J_OK;
}

int CThreadPool::Destroy()
{
	ThreadVec::iterator it = m_vecIdleThread.begin();
	for (; it != m_vecIdleThread.end(); it++)
	{
		pthread_cancel(*it);
		//pthread_join(*it, NULL);
	}

	return J_OK;
}

void CThreadPool::OnThreadFunc(void *param)
{
	int nRet = J_OK;
	CTask *task = NULL;
	TaskInfo taskInfo;
	TaskList::iterator it;
	TaskList *taskList = NULL;
	pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
	while (true)
	{
		sem_wait(&m_threadSem);
		pthread_testcancel();
		pthread_mutex_lock(&m_threadMutex);
		taskList = static_cast< TaskList* >(param);
		if (taskList->size() == 0)
		{
			pthread_mutex_unlock(&m_threadMutex);
			continue;
		}

		taskInfo = taskList->front();
		taskList->pop_front();
		task = taskInfo.task;
		pthread_mutex_unlock(&m_threadMutex);

		nRet = task->Run(task->GetUser());
		if (nRet != J_OK)
		{
			DelAll(taskInfo.gid);
		}
		//printf("thid = %u\n", pthread_self());

		pthread_mutex_lock(&m_threadMutex);
		if (!task->GetAttribute().needDel)
			taskList->push_back(taskInfo);
		else
			delete task;
		if (!taskList->empty())
		{
			//printf("thid = %u\n", pthread_self());
			sem_post(&m_threadSem);
		}
		pthread_mutex_unlock(&m_threadMutex);
	}
}




