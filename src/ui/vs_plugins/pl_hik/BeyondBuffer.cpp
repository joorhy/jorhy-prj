#include "StdAfx.h"
#include "BeyondBuffer.h"

BeyondBuffer::BeyondBuffer(int nBuffSize)
:m_pBegin(NULL)
,m_pEnd(NULL)
,m_pReadPoint(NULL)
,m_pWritePoint(NULL)
{
	m_nBuffSize = nBuffSize;
	if(NULL == m_pBegin)
	{
		m_pBegin = new char[m_nBuffSize];
	}
	m_pEnd = m_pBegin + m_nBuffSize;
	m_pReadPoint = m_pBegin;
	m_pWritePoint = m_pReadPoint;
	m_nReadableSize = 0;

}

BeyondBuffer::~BeyondBuffer(void)
{
	if(NULL != m_pBegin)
	{
		delete m_pBegin;
		m_pBegin = NULL;
	}
}

BOOL BeyondBuffer::PopBuffer(char *OUT_Buffer,StreamHeader &OUT_Header)
{
	m_lock.Lock();
	if(m_nReadableSize == 0)
	{
		m_lock.Unlock();
		return FALSE;
	}

	if(m_pEnd - m_pReadPoint < sizeof(StreamHeader))
	{
		int leftLen = m_pEnd - m_pReadPoint;
		memcpy(&OUT_Header,m_pReadPoint,leftLen);
		m_pReadPoint = m_pBegin;
		memcpy((&OUT_Header) + leftLen,m_pReadPoint,sizeof(StreamHeader) - leftLen);
		m_pReadPoint += sizeof(StreamHeader) - leftLen;
	}
	else
	{
		memcpy(&OUT_Header,m_pReadPoint,sizeof(StreamHeader));
		m_pReadPoint += sizeof(StreamHeader);
	}

	if(m_pEnd - m_pReadPoint < OUT_Header.datalen)
	{
		int leftLen = m_pEnd - m_pReadPoint;
		memcpy(OUT_Buffer,m_pReadPoint,leftLen);
		m_pReadPoint = m_pBegin;
		memcpy(OUT_Buffer + leftLen,m_pReadPoint,OUT_Header.datalen - leftLen);
		m_pReadPoint += OUT_Header.datalen - leftLen;
	}
	else
	{
		memcpy(OUT_Buffer,m_pReadPoint,OUT_Header.datalen);
		m_pReadPoint += OUT_Header.datalen;
	}
	m_nReadableSize -= (OUT_Header.datalen + sizeof(StreamHeader));
	m_lock.Unlock();

	return TRUE;
	
}

BOOL BeyondBuffer::PushBuffer(char *IN_Buffer,StreamHeader &IN_Header)
{
	m_lock.Lock();
	if(m_nBuffSize - m_nReadableSize < (sizeof(StreamHeader) + IN_Header.datalen))	
	{
		m_lock.Unlock();
		return FALSE;
	}

	if(m_pEnd - m_pWritePoint < sizeof(StreamHeader))
	{
		int leftLen = m_pEnd - m_pWritePoint;
		memcpy(m_pWritePoint,&IN_Header,leftLen);
		m_pWritePoint = m_pBegin;
		memcpy(m_pWritePoint,(&IN_Header) + leftLen,sizeof(StreamHeader) - leftLen);
		m_pWritePoint += (sizeof(StreamHeader) - leftLen);
	}
	else
	{
		memcpy(m_pWritePoint,&IN_Header,sizeof(StreamHeader));
		m_pWritePoint += sizeof(StreamHeader);
	}

	if(m_pEnd - m_pWritePoint < IN_Header.datalen)
	{
		int leftLen = m_pEnd - m_pWritePoint;
		memcpy(m_pWritePoint,IN_Buffer,leftLen);
		m_pWritePoint = m_pBegin;
		memcpy(m_pWritePoint,IN_Buffer + leftLen,IN_Header.datalen - leftLen);
		m_pWritePoint += (IN_Header.datalen - leftLen);
	}
	else
	{
		memcpy(m_pWritePoint,IN_Buffer,IN_Header.datalen);
		m_pWritePoint += IN_Header.datalen;
	}
	m_nReadableSize += (sizeof(StreamHeader) + IN_Header.datalen);
	m_lock.Unlock();
	return TRUE;
}

BOOL BeyondBuffer::ResetBuffSize(int nSize)
{
	m_lock.Lock();
	/*if (nSize <= m_nBuffSize)
		return TRUE;*/
	if(m_pBegin != NULL)
	{
		delete m_pBegin;
		m_pBegin = NULL;
	}
	m_pBegin = new char[nSize];
	m_nBuffSize = nSize;
	m_pEnd = m_pBegin;
	m_nReadableSize = 0;
	m_pReadPoint = m_pWritePoint = m_pBegin;
	m_lock.Unlock();
	return TRUE;
}

BOOL BeyondBuffer::IncreaseBuffSize(int nSize)
{
	m_lock.Lock();
	if(m_pBegin == NULL)
	{
		return FALSE;
	}
	char *pBuff = new char[m_nBuffSize + nSize];
	if(m_pReadPoint < m_pWritePoint)
	{
		memcpy(pBuff,m_pReadPoint,m_pWritePoint-m_pReadPoint);
	}
	else if(m_nReadableSize > 0)
	{
		int leftLen = m_pEnd-m_pReadPoint;
		memcpy(pBuff,m_pReadPoint,leftLen);
		m_pReadPoint = m_pBegin;
		memcpy(pBuff + leftLen,m_pReadPoint,m_nReadableSize - leftLen);
	}

	delete m_pBegin;
	m_nBuffSize += nSize;
	m_pBegin = pBuff;
	m_pEnd = m_pBegin + m_nBuffSize;
	m_pReadPoint = m_pBegin;
	m_pWritePoint = m_pBegin + m_nReadableSize;

	m_lock.Unlock();
	return TRUE;
}

BOOL BeyondBuffer::FlushBuff()
{
	m_lock.Lock();
	if(m_pBegin == NULL)
		return FALSE;
	m_pReadPoint = m_pBegin;
	m_pWritePoint = m_pBegin;
	m_nReadableSize = 0;
	m_lock.Unlock();
	return TRUE;
}