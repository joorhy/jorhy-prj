#pragma once
#include "x_pl_base.h"
#include "x_pl_thread.h"
#include "x_pl_data_struct.h"

class J_PlBuffer : public J_PlBase
{
public:
	static J_PlBuffer *CreateInstance(buffer_type_e t,int size_buffer);
	static void ReleaseInstance(J_PlBuffer **pInstance);

	virtual J_PL_RESULT Read(char *OUT_Buffer,char *OUT_extra,j_pl_buffer_t &OUT_Header) = 0;
	virtual J_PL_RESULT Write(char *IN_Buffer,char *IN_extra,j_pl_buffer_t &IN_Header) = 0;
	virtual J_PL_RESULT MoveNext() = 0;
	virtual J_PL_RESULT Flush() = 0;
	virtual void WaitData() = 0;

protected:
	J_PlRWLock	m_lock;
	int				m_bufferID;			//buffer ±Í÷æ
	J_PlSem		m_sem;

protected:
	J_PlBuffer(int size);
	~J_PlBuffer(void);
};
