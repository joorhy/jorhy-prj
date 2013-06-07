#include <string.h>
#include <assert.h>

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
	m_nBufferSize = nBufferSize;
	J_OS::LOGINFO("CRingBuffer::CRingBuffer()");
}
CRingBuffer::~CRingBuffer()
{
	m_mutex._Lock();
	if (m_pBuffer)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}
	m_mutex._Unlock();
	J_OS::LOGINFO("CRingBuffer::~CRingBuffer()");
}

int CRingBuffer::ResetBufferSize(int nBufferSize)
{
	return 0;
}

int CRingBuffer::PushBuffer(const char *pBuffer, J_StreamHeader &streamHeader)
{
	m_mutex._Lock();
	if (streamHeader.frameType != jo_video_i_frame)
	{
		++m_nDiscardedFrameNum;
	}
		
	int nLen = streamHeader.dataLen;
	while (GetIdleLength() < (nLen + J_MEMNODE_LEN + sizeof(J_StreamHeader)))
	{
		if (m_nDataLen < 0)
		{
			J_OS::LOGINFO("CRingBuffer::PushBuffer Buffer Error");
			m_mutex._Unlock();
			return J_UNKNOW;
		}
			
		EraseBuffer();
	}
	
	memset(&m_Node, 0, sizeof(m_Node));
	m_Node.nLen = nLen + sizeof(J_StreamHeader);
	m_Node.pData = AddBuffer(m_pWritePoint, J_MEMNODE_LEN);
	Write((const char *)&m_Node, J_MEMNODE_LEN);
	Write((const char *)&streamHeader, sizeof(J_StreamHeader));
	Write(pBuffer, nLen);
	m_mutex._Unlock();
	
	return J_UNKNOW;
}

int CRingBuffer::PopBuffer(char *pBuffer, J_StreamHeader &streamHeader)
{
	m_mutex._Lock();
	if (m_nDataLen > 0)
	{
		memset(&m_Node, 0, sizeof(m_Node));
		Read((char *)&m_Node, J_MEMNODE_LEN);
		Read((char *)&streamHeader, sizeof(J_StreamHeader));
		Read(pBuffer, m_Node.nLen - sizeof(J_StreamHeader));
		if (streamHeader.frameType != jo_video_i_frame)
			--m_nDiscardedFrameNum;
			
		m_mutex._Unlock();
		return J_OK;
	}
	m_mutex._Unlock();

	return J_NOT_COMPLATE;
}

void CRingBuffer::Read(char *pData, int nLen)
{		
	GetData(pData, nLen);
	m_pReadPoint = AddBuffer(m_pReadPoint, nLen);
	m_nDataLen -= nLen;
}

void CRingBuffer::Write(const char *pData, int nLen)
{
	if (nLen > 0)
	{
		if (m_pEnd - m_pWritePoint <= nLen)
		{
			int nLastLen = m_pEnd - m_pWritePoint;
			memcpy(m_pWritePoint, pData, nLastLen);
			memcpy(m_pBegin, pData + nLastLen, nLen - nLastLen);
		}
		else
		{
			memcpy(m_pWritePoint, pData, nLen);
		}
		m_pWritePoint = AddBuffer(m_pWritePoint, nLen);
		m_nDataLen += nLen;
	}
	//fprintf(stderr, "CXBuffer::Write len = %d\n", m_nDataLen);
}

int CRingBuffer::GetData(char *pData, int nLen, int nOffset)
{
	char *pCurPoint = m_pReadPoint + nOffset;
	if (m_pEnd - (char *)pCurPoint <= nLen)
	{
		int nLastLen = m_pEnd - (char *)pCurPoint;
		memcpy(pData, pCurPoint, nLastLen);
		memcpy(pData + nLastLen, m_pBegin, nLen - nLastLen);
	}
	else
	{
		memcpy(pData, pCurPoint, nLen);
	}
	return nLen;
}

int CRingBuffer::GetIdleLength()
{
	return m_nBufferSize - m_nDataLen;
}

void CRingBuffer::EraseBuffer()
{
	int nMoveLen = 0;
	int nOffset = 0;
	memset(&m_streamHeader, 0, sizeof(m_streamHeader));
	memset(&m_Node, 0, sizeof(m_Node));
	GetData((char *)&m_Node, J_MEMNODE_LEN);
	GetData((char *)&m_streamHeader, sizeof(J_StreamHeader), J_MEMNODE_LEN);
	/*nMoveLen = m_Node.nLen + sizeof(m_Node);
	if (m_streamHeader.frameType == jo_video_i_frame && m_nDiscardedFrameNum > 0)
	{
		memset(&m_streamHeader, 0, sizeof(m_streamHeader));
		memset(&m_Node, 0, sizeof(m_Node));
		GetData((char *)&m_Node, J_MEMNODE_LEN, nMoveLen);
		GetData((char *)&m_streamHeader, sizeof(J_StreamHeader), nMoveLen + sizeof(m_Node));
		if (m_streamHeader.frameType == jo_video_i_frame)
			nMoveLen += m_Node.nLen + sizeof(m_Node);
		else
		{
			--m_nDiscardedFrameNum;
			nOffset = m_Node.nLen + sizeof(m_Node);
		}
	}
	MoveBuffer(nOffset, nMoveLen);*/

	m_pReadPoint = AddBuffer(m_pReadPoint, m_Node.nLen + sizeof(m_Node));
	m_nDataLen -= m_Node.nLen + sizeof(m_Node);
	
	//J_OS::LOGINFO("CXBuffer::EraseBuffer() len = %d\n", m_Node.nLen);
	//fprintf(stderr, "CXBuffer::EraseBuffer() len = %d\n", m_Node.nLen);
}

void CRingBuffer::MoveBuffer(int nOffset, int nLen)
{
	if (nOffset > 0)
		memmove(m_pReadPoint + nOffset, m_pReadPoint, nLen);
}

char *CRingBuffer::AddBuffer(char *pBuffer, int nLen)
{
	char *pNextBuff = NULL;
	if (m_pEnd - pBuffer <= nLen)
	{
		pNextBuff = m_pBegin + (nLen - (m_pEnd - pBuffer));
	}
	else
	{
		pNextBuff = pBuffer + nLen;
	}
	return pNextBuff;
}
