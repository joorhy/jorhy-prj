#include "BTKBufferLIFO.h"
#include "..\include\BTKError.h"
#include "..\include\BTKLog.h"

BTKBufferLIFO::BTKBufferLIFO(int size)
:BTKBuffer(size)
{
	m_bufferID		= BUFFER_LIFO;
	m_nBuffSize		= size;
	m_pBegin		= new char[m_nBuffSize];
	m_pEnd			= m_pBegin + m_nBuffSize;
	m_pReadPoint	= m_pBegin;
	m_pWritePoint	= m_pBegin;
	m_nReadableSize = 0;
	m_nReadableNum	= 0;
	memset(m_pBegin,0,m_nBuffSize);
}

BTKBufferLIFO::~BTKBufferLIFO(void)
{
	if(NULL != m_pBegin)
	{
		m_lock.WriteLock();
		delete m_pBegin;
		m_pBegin = NULL;
		m_lock.WriteUnlock();
	}
}

BTK_RESULT BTKBufferLIFO::Read(char *OUT_Buffer,char *OUT_extra,btk_buffer_t &OUT_Header)
{
	m_lock.ReadLock();

	if(m_nReadableSize == 0)
	{
		m_lock.ReadUnlock();
		return BTK_ERROR_EMPTY_BUFFER;
	}
	char *step = m_pReadPoint;
	//需要重置readpoint到begin  读OUT_Header信息
	memcpy(&OUT_Header,step - sizeof(btk_buffer_t),sizeof(btk_buffer_t));
	step -= sizeof(btk_buffer_t);

	//需要重置readpoint到begin 读OUT_extra信息
	memcpy(OUT_extra,step - OUT_Header.extrasize,OUT_Header.extrasize);
	step -= OUT_Header.extrasize;

	//需要重置readpoint到begin 读OUT_Buffer信息
	memcpy(OUT_Buffer,step - OUT_Header.datasize,OUT_Header.datasize);
	step -= OUT_Header.datasize;

	m_pSetpPoint = step;
	m_nStepSize = OUT_Header.datasize + OUT_Header.extrasize + sizeof(btk_buffer_t);
	m_lock.ReadUnlock();
	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferLIFO::Write(char *IN_Buffer,char *IN_extra,btk_buffer_t &IN_Header)
{
	m_lock.WriteLock();
	if(m_nBuffSize - m_nReadableSize < 
		(sizeof(btk_buffer_t) + IN_Header.datasize + IN_Header.extrasize))	
	{
		m_lock.WriteUnlock();
		return BTK_ERROR_FULL_BUFFER;
	}
	m_sem.Post();

	//需要重置writepoint到begin 写IN_Buffer信息
	memcpy(m_pWritePoint,IN_Buffer,IN_Header.datasize);
	m_pWritePoint += IN_Header.datasize;

	//需要重置writepoint到begin 写IN_extra信息
	memcpy(m_pWritePoint,IN_extra,IN_Header.extrasize);
	m_pWritePoint += IN_Header.extrasize;

	//需要重置writepoint到begin 写IN_Header信息
	memcpy(m_pWritePoint,&IN_Header,sizeof(btk_buffer_t));
	m_pWritePoint += sizeof(btk_buffer_t);


	m_pReadPoint = m_pWritePoint;
	m_nReadableSize += (IN_Header.datasize + IN_Header.extrasize + sizeof(btk_buffer_t));
	m_nReadableNum++;

	m_lock.WriteUnlock();
	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferLIFO::MoveNext()
{
	m_lock.WriteLock();

	m_pReadPoint = m_pSetpPoint;
	m_pWritePoint = m_pSetpPoint;
	m_nReadableSize -= m_nStepSize;
	m_nReadableNum--;
	m_lock.WriteUnlock();
	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferLIFO::Flush()
{
	m_lock.WriteLock();

	if(m_pBegin == NULL)
		return BTK_NO_ERROR;

	m_pReadPoint	= m_pBegin;
	m_pWritePoint	= m_pBegin;
	m_nReadableSize = 0;
	m_nReadableNum	= 0;
	memset(m_pBegin,0,m_nBuffSize);

	m_lock.WriteUnlock();
	return BTK_NO_ERROR;
}

void BTKBufferLIFO::WaitData()
{
	m_sem.WaitTime(300);
}

int BTKBufferLIFO::GetReadableSize()
{
	int n = 0;
	m_lock.ReadLock();
	n = m_nReadableSize;
	m_lock.ReadUnlock();
	return n;
}

int BTKBufferLIFO::GetReadableNum()
{
	int n = 0;
	m_lock.ReadLock();
	n = m_nReadableNum;
	m_lock.ReadUnlock();
	return n;
}

BTK_RESULT BTKBufferLIFO::DropData(int num)
{
	m_lock.WriteLock();
	if(m_nReadableSize == 0)
	{
		m_lock.ReadUnlock();
		return BTK_ERROR_EMPTY_BUFFER;
	}
	btk_buffer_t tmp;

	for(int i=0;i<num;i++)
	{
		if(m_nReadableSize == 0)
		{
			m_lock.WriteLock();
			return BTK_NO_ERROR;
		}

		int leftLen;
		memcpy(&tmp,m_pReadPoint,sizeof(btk_buffer_t));
		m_pReadPoint -= sizeof(btk_buffer_t);

		m_pReadPoint -= tmp.extrasize;

		m_pReadPoint -= tmp.datasize;

		m_nReadableSize -= (tmp.datasize + tmp.extrasize + sizeof(btk_buffer_t));
		m_nReadableNum--;
		m_pWritePoint = m_pReadPoint;
	}

	m_lock.WriteUnlock();

	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferLIFO::SetReadType(bool bFront)
{
	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferLIFO::SetReadPoint(bool bEnd)
{
	return BTK_NO_ERROR;
}