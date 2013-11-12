#pragma once
#include "x_pl_base.h"
#include "x_pl_buffer.h"

class CXPlRecord : public J_PlBase
{
public:
	CXPlRecord(int nID);
	~CXPlRecord();

public:
	static CXPlRecord* CreateInstance(int nType);		
	static void ReleaseInstance(CXPlRecord **pInstance);

	virtual J_PL_RESULT Start(char *filename) = 0;
	virtual J_PL_RESULT InputData(char *IN_buf,int In_len,int nType, long long timeStamp) = 0;
	virtual J_PL_RESULT Stop() = 0;

public:
	int m_recodeID;
};