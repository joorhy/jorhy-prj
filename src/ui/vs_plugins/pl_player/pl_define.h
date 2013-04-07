#pragma once
#include "pl_manager.h"

typedef struct
{
	PlManager *pPlayer;
	int pVolume;
	BOOL pSound;
	BOOL bRecoder;
	DWORD dwUIT;
	BOOL bNeedShowCTRL;
	BOOL bPlayOneByOne;
}PlayParm;