#pragma once
#include "x_pl_common.h"

#ifdef   JO_PLAYER_EXPORTS 
#define   JO_PL_API           __declspec(dllexport) 
#else 
#define   JO_PL_API           __declspec(dllimport) 
#endif 

class J_PlBase
{
public:
	J_PlBase(void);
	~J_PlBase(void);
};
