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
	virtual BTK_RESULT DropData(int num = 1) = 0;
	virtual BTK_RESULT Flush() = 0;
	virtual void WaitData() = 0;
	virtual int GetReadableSize() = 0;
	virtual int GetReadableNum() = 0;
	virtual BTK_RESULT SetReadType(bool bFront=true) = 0;		//读取数据的方向
	virtual BTK_RESULT SetReadPoint(bool bEnd=false) = 0;		//移动指针到末尾


protected:
	BTKRWLock m_lock;
	int m_bufferID;			//buffer 标志
	BTKSem	m_sem;

protected:
	BTKBuffer(int size);
	~BTKBuffer(void);
};
