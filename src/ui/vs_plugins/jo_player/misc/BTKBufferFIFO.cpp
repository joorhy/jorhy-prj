#include "BTKBufferFIFO.h"
#include "..\include\BTKError.h"
#include "..\include\BTKLog.h"

BTKBufferFIFO::BTKBufferFIFO(int size)
:BTKBuffer(size)
{
	m_bufferID		= BUFFER_FIFO;
	m_nBuffSize		= size;
	m_pBegin		= new char[m_nBuffSize];
	m_pEnd			= m_pBegin + m_nBuffSize;
	m_pReadPoint	= m_pBegin;
	m_pWritePoint	= m_pBegin;
	m_nReadableSize = 0;
	m_nReadableNum	= 0;
	memset(m_pBegin,0,m_nBuffSize);
}

BTKBufferFIFO::~BTKBufferFIFO(void)
{
	if(NULL != m_pBegin)
	{
		m_lock.WriteLock();
		delete m_pBegin;
		m_pBegin = NULL;
		m_lock.WriteUnlock();
	}
}

BTK_RESULT BTKBufferFIFO::Read(char *OUT_Buffer,char *OUT_extra,btk_buffer_t &OUT_Header)
{
	m_lock.ReadLock();
	
	if(m_nReadableSize == 0)
	{
		m_lock.ReadUnlock();
		return BTK_ERROR_EMPTY_BUFFER;
	}
	char *step = m_pReadPoint;
	//需要重置readpoint到begin  读OUT_Header信息
	if(m_pEnd - step < sizeof(btk_buffer_t))
	{
		int leftLen = m_pEnd - step;
		memcpy(&OUT_Header,step,leftLen);
		step = m_pBegin;
		memcpy((&OUT_Header) + leftLen,step,sizeof(btk_buffer_t) - leftLen);
		step += (sizeof(btk_buffer_t) - leftLen);
	}
	else
	{
		memcpy(&OUT_Header,step,sizeof(btk_buffer_t));
		step += sizeof(btk_buffer_t);
	}
	//btk_Info("datasize=%d	extrasize=%d\n",OUT_Header.datasize,OUT_Header.extrasize);
	//需要重置readpoint到begin 读OUT_extra信息
	if(m_pEnd - step < OUT_Header.extrasize)
	{
		int leftLen = m_pEnd - step;
		memcpy(OUT_extra,step,leftLen);
		step = m_pBegin;
		memcpy(OUT_extra + leftLen,step,OUT_Header.extrasize - leftLen);
		step += (OUT_Header.extrasize - leftLen);
	}
	else
	{
		memcpy(OUT_extra,step,OUT_Header.extrasize);
		step += OUT_Header.extrasize;
	}

	//需要重置readpoint到begin 读OUT_Buffer信息
	if(m_pEnd - step < OUT_Header.datasize)
	{
		int leftLen = m_pEnd - step;
		memcpy(OUT_Buffer,step,leftLen);
		step = m_pBegin;
		memcpy(OUT_Buffer + leftLen,step,OUT_Header.datasize - leftLen);
		step += (OUT_Header.datasize - leftLen);
	}
	else
	{
		memcpy(OUT_Buffer,step,OUT_Header.datasize);
		step += OUT_Header.datasize;
	}
	m_pSetpPoint = step;
	m_nStepSize = OUT_Header.datasize + OUT_Header.extrasize + sizeof(btk_buffer_t);
	m_lock.ReadUnlock();
	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferFIFO::Write(char *IN_Buffer,char *IN_extra,btk_buffer_t &IN_Header)
{
	m_lock.WriteLock();
	if(m_nBuffSize - m_nReadableSize < 
	(sizeof(btk_buffer_t) + IN_Header.datasize + IN_Header.extrasize))	
	{
		m_lock.WriteUnlock();
		return BTK_ERROR_FULL_BUFFER;
	}
	m_sem.Post();
	//需要重置writepoint到begin 写IN_Header信息
	if(m_pEnd - m_pWritePoint < sizeof(btk_buffer_t))
	{
		int leftLen = m_pEnd - m_pWritePoint;
		memcpy(m_pWritePoint,&IN_Header,leftLen);
		m_pWritePoint = m_pBegin;
		memcpy(m_pWritePoint,(&IN_Header) + leftLen,sizeof(btk_buffer_t) - leftLen);
		m_pWritePoint += (sizeof(btk_buffer_t) - leftLen);
	}
	else
	{
		memcpy(m_pWritePoint,&IN_Header,sizeof(btk_buffer_t));
		m_pWritePoint += sizeof(btk_buffer_t);
	}

	//需要重置writepoint到begin 写IN_extra信息
	if(m_pEnd - m_pWritePoint < IN_Header.extrasize)
	{
		int leftLen = m_pEnd - m_pWritePoint;
		memcpy(m_pWritePoint,IN_extra,leftLen);
		m_pWritePoint = m_pBegin;
		memcpy(m_pWritePoint,IN_extra + leftLen,IN_Header.extrasize - leftLen);
		m_pWritePoint += (IN_Header.extrasize - leftLen);
	}
	else
	{
		memcpy(m_pWritePoint,IN_extra,IN_Header.extrasize);
		m_pWritePoint += IN_Header.extrasize;
	}

	//需要重置writepoint到begin 写IN_Buffer信息
	if(m_pEnd - m_pWritePoint < IN_Header.datasize)
	{
		int leftLen = m_pEnd - m_pWritePoint;
		memcpy(m_pWritePoint,IN_Buffer,leftLen);
		m_pWritePoint = m_pBegin;
		memcpy(m_pWritePoint,IN_Buffer + leftLen,IN_Header.datasize - leftLen);
		m_pWritePoint += (IN_Header.datasize - leftLen);
	}
	else
	{
		memcpy(m_pWritePoint,IN_Buffer,IN_Header.datasize);
		m_pWritePoint += IN_Header.datasize;
	}
	m_nReadableSize += (IN_Header.datasize + IN_Header.extrasize + sizeof(btk_buffer_t));
	m_nReadableNum++;
	m_lock.WriteUnlock();
	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferFIFO::MoveNext()
{
	m_lock.WriteLock();

	m_pReadPoint = m_pSetpPoint;
	m_nReadableSize -= m_nStepSize;
	m_nReadableNum--;
	m_lock.WriteUnlock();
	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferFIFO::Flush()
{
	m_lock.WriteLock();

	if(m_pBegin == NULL)
		return BTK_NO_ERROR;
	m_pReadPoint	= m_pBegin;
	m_pWritePoint	= m_pBegin;
	m_pSetpPoint	= m_pBegin;
	m_nStepSize		= 0;
	m_nReadableSize = 0;
	m_nReadableNum	= 0;
	memset(m_pBegin,0,m_nBuffSize);

	m_lock.WriteUnlock();
	return BTK_NO_ERROR;
}

void BTKBufferFIFO::WaitData()
{
	m_sem.WaitTime(300);
}

int BTKBufferFIFO::GetReadableSize()
{
	int n = 0;
	m_lock.ReadLock();
	n = m_nReadableSize;
	m_lock.ReadUnlock();
	return n;
}

int BTKBufferFIFO::GetReadableNum()
{
	int n = 0;
	m_lock.ReadLock();
	n = m_nReadableNum;
	m_lock.ReadUnlock();
	return n;
}

BTK_RESULT BTKBufferFIFO::DropData(int num)
{
	m_lock.WriteLock();
	if(m_nReadableSize == 0)
	{
		m_lock.WriteLock();
		return BTK_ERROR_EMPTY_BUFFER;
	}
	btk_buffer_t tmp;

	for(int i=0;i<num;i++)
	{
		if(m_nReadableSize == 0)
		{
			m_lock.ReadUnlock();
			return BTK_NO_ERROR;
		}

		int leftLen;
		if(m_pEnd - m_pReadPoint < sizeof(btk_buffer_t))
		{
			leftLen = m_pEnd - m_pReadPoint;
			memcpy(&tmp,m_pReadPoint,leftLen);
			m_pReadPoint = m_pBegin;
			memcpy((&tmp) + leftLen,m_pReadPoint,sizeof(btk_buffer_t) - leftLen);
			m_pReadPoint += (sizeof(btk_buffer_t) - leftLen);
		}
		else
		{
			memcpy(&tmp,m_pReadPoint,sizeof(btk_buffer_t));
			m_pReadPoint += sizeof(btk_buffer_t);
		}

		if(m_pEnd - m_pReadPoint < tmp.extrasize)
		{
			leftLen = m_pEnd - m_pReadPoint;
			m_pReadPoint = m_pBegin;
			m_pReadPoint += (tmp.extrasize - leftLen);
		}
		else
			m_pReadPoint += tmp.extrasize;

		if(m_pEnd - m_pReadPoint < tmp.datasize)
		{
			leftLen = m_pEnd - m_pReadPoint;
			m_pReadPoint = m_pBegin;
			m_pReadPoint += (tmp.datasize - leftLen);
		}
		else
			m_pReadPoint += tmp.datasize;

		m_nReadableSize -= (tmp.datasize + tmp.extrasize + sizeof(btk_buffer_t));
		m_nReadableNum--;
	}

	m_lock.WriteUnlock();

	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferFIFO::SetReadType(bool bFront)
{
	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferFIFO::SetReadPoint(bool bEnd)
{
	return BTK_NO_ERROR;
}