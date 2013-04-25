#pragma once
#include "x_pl_base.h"
#include "x_pl_buffer.h"

class CXPlRecord : public J_PlBase
{
public:
	CXPlRecord();
	~CXPlRecord();

	J_PL_RESULT Start(char *filename);
	J_PL_RESULT Stop();

private:
	J_PL_RESULT Init(char *filename);


private:
	
};