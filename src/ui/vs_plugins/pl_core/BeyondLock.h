#pragma once

#include <windows.h>

#ifdef PL_CORE_EXPORTS
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif

class DLLAPI BeyondLock
{
public:
	BeyondLock();
	void Lock(void);
	void Unlock(void);
	~BeyondLock();

private:
	CRITICAL_SECTION m_cs;
};