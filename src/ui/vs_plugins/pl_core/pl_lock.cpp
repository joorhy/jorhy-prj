#include "StdAfx.h"
#include "pl_lock.h"

PlLock::PlLock()
{
	InitializeCriticalSection(&m_cs);
}

PlLock::~PlLock()
{
	DeleteCriticalSection(&m_cs);
}

void PlLock::Lock()
{
	EnterCriticalSection(&m_cs);
}

void PlLock::Unlock()
{
	LeaveCriticalSection(&m_cs);
}