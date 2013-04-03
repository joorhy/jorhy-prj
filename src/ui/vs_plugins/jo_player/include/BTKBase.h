#pragma once
#include "BTKCommon.h"

#ifdef   _BTKPLAYERCTRL 
#define   DLL_IMPORT           __declspec(dllexport) 
#else 
#define   DLL_IMPORT           __declspec(dllimport) 
#endif 

class BTKBase
{
public:
	BTKBase(void);
	~BTKBase(void);
};
