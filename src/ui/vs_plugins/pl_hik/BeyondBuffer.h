#pragma once
#include "PlayerDataCenter.h"
#include "BeyondLock.h"

class BeyondBuffer
{
public:
	BeyondBuffer(int nBuffSize = REAL_BUFFSIZE);
	~BeyondBuffer(void);

public:
	BOOL PopBuffer(char *OUT_Buffer,StreamHeader &OUT_Header);		//TRUE=成功,FALSE=没数据
	BOOL PushBuffer(char *IN_Buffer,StreamHeader &IN_Header);		//TRUE=成功,FALSE=buffer已满
	BOOL ResetBuffSize(int nSize);					//重置buffer,数据将丢失
	BOOL IncreaseBuffSize(int nSize);				//增加buffer大小，保留未读数据
	BOOL FlushBuff();

private:
	int m_nBuffSize;		//总共buffer大小
	char *m_pBegin;
	char *m_pEnd;
	char *m_pReadPoint;
	char *m_pWritePoint;
	int m_nReadableSize;	//可读buffer大小

	BeyondLock m_lock;
};
