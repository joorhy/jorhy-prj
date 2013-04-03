#include "StdAfx.h"
#include "BeyondLock.h"

BeyondLock::BeyondLock()
{
	InitializeCriticalSection(&m_cs);
}

BeyondLock::~BeyondLock()
{
	DeleteCriticalSection(&m_cs);
}

void BeyondLock::Lock()
{
	EnterCriticalSection(&m_cs);
}

void BeyondLock::Unlock()
{
	LeaveCriticalSection(&m_cs);
}