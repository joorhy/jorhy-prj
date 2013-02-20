#include "x_buffer.h"
#include "x_errtype.h"

CXBuffer::CXBuffer(int nBuffSize)
{
	m_pBuffer = new char[nBuffSize];
	m_pBegin = m_pBuffer;
	m_pEnd = m_pBuffer + nBuffSize;
	m_pWritePoint = m_pReadPoint = m_pBegin;
	m_nDataLen = 0;
}

CXBuffer::~CXBuffer()
{
	m_locker.Lock();
	if (m_pBuffer)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}
	m_locker.Unlock();
}
	
int CXBuffer::PushData(const char *pData, int nLen)
{
	m_locker.Lock();
	while (GetIdleLength() < (nLen + J_MEMNODE_LEN))
	{
		if (m_nDataLen <= 0)
			return J_UNKNOW;
			
		EraseBuffer();
	}
		
	m_Node.nLen = nLen;
	m_Node.pData = AddBuffer(m_pWritePoint, J_MEMNODE_LEN);
	Write((const char *)&m_Node, J_MEMNODE_LEN);
	Write(pData, nLen);
	
	m_locker.Unlock();
	
	return J_OK;
}

int CXBuffer::PopData(char *pData)
{
	int nRetLen = 0;
	m_locker.Lock();
	if (m_nDataLen > 0)
	{
		Read((char *)&m_Node, J_MEMNODE_LEN);
		Read(pData, m_Node.nLen);
		nRetLen = m_Node.nLen;
	}
	m_locker.Unlock();
	
	return nRetLen; 
}

void CXBuffer::Read(char *pData, int nLen)
{
	if (m_pEnd - (char *)m_pReadPoint <= nLen)
	{
		int nLastLen = m_pEnd - (char *)m_pReadPoint - 1;
		memcpy(pData, m_pReadPoint, nLastLen);
		memcpy(pData + nLastLen, m_pBegin, nLen - nLastLen);
	}
	else
	{
		memcpy(pData, m_pReadPoint, nLen);
	}
	m_pReadPoint = AddBuffer(m_pReadPoint, nLen);
	m_nDataLen -= nLen;
}

void CXBuffer::Write(const char *pData, int nLen)
{
	if (m_pEnd - m_pWritePoint <= nLen)
	{
		int nLastLen = m_pEnd - m_pWritePoint - 1;
		memcpy(m_pWritePoint, pData, nLastLen);
		memcpy(m_pBegin, pData + nLastLen, nLen - nLastLen);
	}
	else
	{
		memcpy(m_pWritePoint, pData, nLen);
	}
	m_pWritePoint = AddBuffer(m_pWritePoint, nLen);
	m_nDataLen += nLen;
	//fprintf(stderr, "CXBuffer::Write len = %d\n", m_nDataLen);
}

int CXBuffer::GetIdleLength()
{
	return BUFFER_SIZE - m_nDataLen;
}

void CXBuffer::EraseBuffer()
{
	J_MEMNODE node = {0};
	Read((char *)&node, J_MEMNODE_LEN);
	m_pReadPoint = AddBuffer(m_pReadPoint, node.nLen);
	m_nDataLen -= node.nLen;
	//fprintf(stderr, "CXBuffer::EraseBuffer() len = %d\n", node.nLen);
}

char *CXBuffer::AddBuffer(char *pBuffer, int nLen)
{
	char *pNextBuff = NULL;
	if (m_pEnd - pBuffer <= nLen)
	{
		pNextBuff = m_pBegin + (nLen - (m_pEnd - pBuffer - 1));
	}
	else
	{
		pNextBuff = pBuffer + nLen;
	}
	return pNextBuff;
}