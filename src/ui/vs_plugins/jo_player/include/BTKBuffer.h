#pragma once
#include "btkbase.h"
#include "BTKThread.h"
#include "DataStruct.h"

class BTKBuffer : public BTKBase
{
public:
	static BTKBuffer *CreateInstance(buffer_type_e t,int size_buffer);
	static void ReleaseInstance(BTKBuffer **pInstance);

	virtual BTK_RESULT Read(char *OUT_Buffer,char *OUT_extra,btk_buffer_t &OUT_Header) = 0;
	virtual BTK_RESULT Write(char *IN_Buffer,char *IN_extra,btk_buffer_t &IN_Header) = 0;
	virtual BTK_RESULT MoveNext() = 0;
	virtual BTK_RESULT Flush() = 0;
	virtual void WaitData() = 0;

protected:
	BTKRWLock	m_lock;
	int				m_bufferID;			//buffer ±Í÷æ
	BTKSem		m_sem;

protected:
	BTKBuffer(int size);
	~BTKBuffer(void);
};
