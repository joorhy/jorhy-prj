#include <string.h>

#include "j_module.h"
#include "x_ringbuffer.h"
#include "x_log.h"

CRingBuffer::CRingBuffer(int nCacheFrameNum, int nBufferSize)
{
	m_pBuffer = new char[nBufferSize];
	m_pBegin = m_pBuffer;
	m_pEnd = m_pBuffer + nBufferSize;
	m_pWritePoint = m_pReadPoint = m_pBegin;
	m_nDataLen = 0;
}
CRingBuffer::~CRingBuffer()
{
	WLock(m_rwLocker);
	if (m_pBuffer)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}
	RWUnlock(m_rwLocker);
}

int CRingBuffer::ResetBufferSize(int nBufferSize)
{
	return 0;
}

int CRingBuffer::PushBuffer(const char *pBuffer, J_StreamHeader &streamHeader)
{
	WLock(m_rwLocker);
	int nLen = streamHeader.dataLen;
	while (GetIdleLength() < (nLen + J_MEMNODE_LEN))
	{
		if (m_nDataLen <= 0)
			return J_UNKNOW;
			
		EraseBuffer();
	}
		
	m_Node.nLen = nLen + sizeof(J_StreamHeader);
	m_Node.pData = AddBuffer(m_pWritePoint, J_MEMNODE_LEN);
	Write((const char *)&m_Node, J_MEMNODE_LEN);
	Write((const char *)&streamHeader, sizeof(J_StreamHeader));
	Write(pBuffer, nLen);
	RWUnlock(m_rwLocker);

	return J_UNKNOW;
}

int CRingBuffer::PopBuffer(char *pBuffer, J_StreamHeader &streamHeader)
{
	RLock(m_rwLocker);
	if (m_nDataLen > 0)
	{
		Read((char *)&m_Node, J_MEMNODE_LEN);
		Read((char *)&streamHeader, sizeof(J_StreamHeader));
		Read(pBuffer, m_Node.nLen - sizeof(J_StreamHeader));
		//nRetLen = m_Node.nLen;
	}
	RWUnlock(m_rwLocker);

	return J_OK;
}

void CRingBuffer::Read(char *pData, int nLen)
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

void CRingBuffer::Write(const char *pData, int nLen)
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

int CRingBuffer::GetIdleLength()
{
	return BUFFER_SIZE - m_nDataLen;
}

void CRingBuffer::EraseBuffer()
{
	J_MEMNODE node = {0};
	Read((char *)&node, J_MEMNODE_LEN);
	m_pReadPoint = AddBuffer(m_pReadPoint, node.nLen);
	m_nDataLen -= node.nLen;
	//fprintf(stderr, "CXBuffer::EraseBuffer() len = %d\n", node.nLen);
}

char *CRingBuffer::AddBuffer(char *pBuffer, int nLen)
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
