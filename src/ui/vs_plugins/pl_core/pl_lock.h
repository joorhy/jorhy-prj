#pragma once

#include <windows.h>
#include "pl_core.h"

class PL_API PlLock
{
public:
	PlLock();
	void Lock(void);
	void Unlock(void);
	~PlLock();

private:
	CRITICAL_SECTION m_cs;
};