#include "BTKBufferLIST.h"
#include "..\include\BTKError.h"
#include "..\include\BTKLog.h"


BTKBufferLIST::BTKBufferLIST(int size)
:BTKBuffer(size)
{
	m_bufferID		= BUFFER_LIST;
	m_nBuffSize		= size;
	m_pBegin		= new char[m_nBuffSize];
	m_pEnd			= m_pBegin + m_nBuffSize;
	m_readPoint		= 0;
	m_pWritePoint	= m_pBegin;
	m_nReadableSize = 0;
	m_bFront		= true;
	memset(m_pBegin,0,m_nBuffSize);
}

BTKBufferLIST::~BTKBufferLIST(void)
{
	if(NULL != m_pBegin)
	{
		m_lock.WriteLock();
		delete m_pBegin;
		m_pBegin = NULL;
		m_lock.WriteUnlock();
	}
}

BTK_RESULT BTKBufferLIST::Read(char *OUT_Buffer,char *OUT_extra,btk_buffer_t &OUT_Header)
{
	m_lock.ReadLock();
	if(m_nReadableSize == 0)
	{
		m_lock.ReadUnlock();
		return BTK_ERROR_EMPTY_BUFFER;
	}

	char *reader = m_readers[m_readPoint];

	//读OUT_Header
	memcpy(&OUT_Header,reader,sizeof(OUT_Header));
	reader += sizeof(OUT_Header);

	//读OUT_extra
	memcpy(OUT_extra,reader,OUT_Header.extrasize);
	reader += OUT_Header.extrasize;

	//读OUT_Buffer
	memcpy(OUT_Buffer,reader,OUT_Header.datasize);
	reader += OUT_Header.datasize;

	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferLIST::Write(char *IN_Buffer,char *IN_extra,btk_buffer_t &IN_Header)
{
	m_lock.WriteLock();
	if(m_pEnd - m_pWritePoint < IN_Header.datasize +IN_Header.extrasize +sizeof(IN_Header))
	{
		m_lock.WriteUnlock();
		return BTK_ERROR_FULL_BUFFER;
	}
	m_sem.Post();
	m_readers.push_back(m_pWritePoint);

	//写IN_Header信息
	memcpy(m_pWritePoint,&IN_Header,sizeof(IN_Header));
	m_pWritePoint += sizeof(IN_Header);

	//写IN_extra信息
	memcpy(m_pWritePoint,IN_extra,IN_Header.extrasize);
	m_pWritePoint += IN_Header.extrasize;

	//写IN_Buffer信息
	memcpy(m_pWritePoint,IN_Buffer,IN_Header.datasize);
	m_pWritePoint += IN_Header.datasize;

	m_nReadableSize += (sizeof(IN_Header) + IN_Header.extrasize + IN_Header.datasize);


	m_lock.WriteUnlock();
	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferLIST::MoveNext()
{
	m_lock.WriteLock();
	if(m_bFront)
	{
		if(m_readPoint < m_readers.size())
		{
			m_readPoint++;
		}
		else
			m_nReadableSize = 0;
	}
	else
	{
		if(m_readPoint > 0)
		{
			m_readPoint--;
		}
		else
			m_nReadableSize = 0;
	}
	m_lock.WriteUnlock();
	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferLIST::Flush()
{
	m_lock.WriteLock();
	
	m_readers.empty();
	m_readPoint		= 0;
	m_pWritePoint	= m_pBegin;
	m_nReadableSize = 0;
	memset(m_pBegin,0,m_nBuffSize);

	m_lock.WriteUnlock();
	return BTK_NO_ERROR;
}

void BTKBufferLIST::WaitData()
{
	m_sem.WaitTime(300);
}

int BTKBufferLIST::GetReadableSize()
{
	int n = 0;
	m_lock.ReadLock();
	n = m_nReadableSize;
	m_lock.ReadUnlock();
	return n;
}

int BTKBufferLIST::GetReadableNum()
{
	int n = 0;
	m_lock.ReadLock();
	n = m_readers.size();
	m_lock.ReadUnlock();
	return n;
}

BTK_RESULT BTKBufferLIST::DropData(int num)
{
	m_lock.WriteLock();
	if(m_nReadableSize == 0)
	{
		m_lock.WriteLock();
		return BTK_ERROR_EMPTY_BUFFER;
	}
	
	int n = m_readers.size();
	if(n <= num)
	{
		m_readers.empty();
		m_readPoint		= 0;
		m_pWritePoint	= m_pBegin;
		m_nReadableSize = 0;
		memset(m_pBegin,0,m_nBuffSize);
	}
	else
	{
		int level = n - num;
		for(int i=0;i<num;i++)
		{
			btk_buffer_t tmp_buf;
			char *tmp_reader = m_readers[n-1-i];
			memcpy(&tmp_buf,tmp_reader,sizeof(tmp_buf));
			m_nReadableSize -= (sizeof(tmp_buf) + tmp_buf.datasize + tmp_buf.extrasize);
			m_readers.pop_back();
		}
		if(level < m_readPoint)	//当前readpoint 在里面把它移到删除后最后一个
		{
			m_readPoint = level - 1;
		}
	}

	m_lock.WriteUnlock();

	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferLIST::SetReadType(bool bFront)
{
	m_lock.WriteLock();
	m_bFront = bFront;
	m_lock.WriteUnlock();

	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferLIST::SetReadPoint(bool bEnd)
{
	m_lock.WriteLock();
	
	if(bEnd)
	{
		m_readPoint = m_readers.size() - 1;
	}
	else
	{
		m_readPoint = 0;
	}

	m_lock.WriteUnlock();

	return BTK_NO_ERROR;
}
