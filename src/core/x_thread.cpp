#include "x_thread.h"

CJoThread::CJoThread()
{
	memset(&m_parm,0,sizeof(m_parm));
	m_hThread = j_invalid_thread_val;
}

CJoThread::~CJoThread()
{
#ifdef WIN32
	CloseHandle(m_hThread);
#endif
}

j_result_t CJoThread::Create(j_thread_parm &parm)
{
	if(!parm.entry)
		return J_THREAD_CREATE_ERROR;

#ifdef WIN32
	m_hThread = (HANDLE)_beginthreadex(NULL, parm.stack_size, parm.entry, parm.data, CREATE_SUSPENDED, NULL);
#else
	pthread_attr_t  thr_attr;
	if (pthread_attr_init(&thr_attr) != 0)
		return J_THREAD_CREATE_ERROR;
	pthread_attr_setstacksize(&thr_attr, parm.stack_size);
	pthread_create(&m_hThread, &thr_attr, parm.entry, parm.data);
	pthread_attr_destroy(&thr_attr);
	pthread_detach(m_hThread);
#endif

	if(m_hThread == j_invalid_thread_val)
		return J_THREAD_CREATE_ERROR;
	if(parm.priority)
#ifdef WIN32
		SetThreadPriority (m_hThread,parm.priority);	//eg:THREAD_PRIORITY_NORMAL 
#else
		//linux 设置优先级
#endif

	Resume();
	return J_OK;
}

j_result_t CJoThread::Suspend()
{
#ifdef WIN32
	DWORD ret = 0;
	if(m_hThread)
		ret = SuspendThread(m_hThread);
#endif

	return J_OK;
}

j_result_t CJoThread::Resume()
{
#ifdef WIN32
	DWORD ret = 0;
	if(m_hThread)
		ret = ResumeThread (m_hThread);
#endif

	return J_OK;
}

void CJoThread::Release()
{
	if(m_hThread != j_invalid_thread_val)
	{
#ifdef WIN32
		//_endthreadex((uintptr_t)m_hThread);
		CloseHandle(m_hThread);
#else
		pthread_cancel(m_hThread);
#endif
		m_hThread = j_invalid_thread_val;
	}
}