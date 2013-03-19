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
	
	pthread_mutex_init(&m_mutex, NULL);
	pthread_cond_init(&m_cond, NULL);
}
CRingBuffer::~CRingBuffer()
{
	pthread_mutex_lock(&m_mutex);
	if (m_pBuffer)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}
	pthread_mutex_unlock(&m_mutex);
	
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_cond);
}

int CRingBuffer::ResetBufferSize(int nBufferSize)
{
	return 0;
}

int CRingBuffer::PushBuffer(const char *pBuffer, J_StreamHeader &streamHeader)
{
	pthread_mutex_lock(&m_mutex);
	/*if (streamHeader.frameType != jo_video_i_frame)
	{
		pthread_mutex_unlock(&m_mutex);
		return J_OK;
	}*/
		
	int nLen = streamHeader.dataLen;
	while (GetIdleLength() < (nLen + J_MEMNODE_LEN + sizeof(J_StreamHeader)))
	{
		if (m_nDataLen < 0)
		{
			J_OS::LOGINFO("CRingBuffer::PushBuffer Buffer Error");
			pthread_mutex_unlock(&m_mutex);
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
	pthread_mutex_unlock(&m_mutex);
	//pthread_cond_signal(&m_cond);
	
	return J_UNKNOW;
}

int CRingBuffer::PopBuffer(char *pBuffer, J_StreamHeader &streamHeader)
{
	pthread_mutex_lock(&m_mutex);
	//if (m_nDataLen == 0)
	//	pthread_cond_wait(&m_cond, &m_mutex);
		
	if (m_nDataLen > 0)
	{
		memset(&m_Node, 0, sizeof(m_Node));
		Read((char *)&m_Node, J_MEMNODE_LEN);
		Read((char *)&streamHeader, sizeof(J_StreamHeader));
		Read(pBuffer, m_Node.nLen - sizeof(J_StreamHeader));
		//nRetLen = m_Node.nLen;
		pthread_mutex_unlock(&m_mutex);
		return J_OK;
	}
	pthread_mutex_unlock(&m_mutex);

	return J_NOT_COMPLATE;
}

void CRingBuffer::Read(char *pData, int nLen)
{		
	if (m_pEnd - (char *)m_pReadPoint <= nLen)
	{
		if (pData != NULL)
		{
			int nLastLen = m_pEnd - (char *)m_pReadPoint;
			memcpy(pData, m_pReadPoint, nLastLen);
			memcpy(pData + nLastLen, m_pBegin, nLen - nLastLen);
		}
	}
	else
	{
		if (pData != NULL)
			memcpy(pData, m_pReadPoint, nLen);
	}
	m_pReadPoint = AddBuffer(m_pReadPoint, nLen);
	m_nDataLen -= nLen;
}

void CRingBuffer::Write(const char *pData, int nLen)
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
	//fprintf(stderr, "CXBuffer::Write len = %d\n", m_nDataLen);
}

int CRingBuffer::GetIdleLength()
{
	return BUFFER_SIZE - m_nDataLen;
}

void CRingBuffer::EraseBuffer()
{
	J_StreamHeader streamHeader = {0};
	memset(&m_Node, 0, sizeof(m_Node));
	Read((char *)&m_Node, J_MEMNODE_LEN);
	Read((char *)&streamHeader, sizeof(J_StreamHeader));
	Read(NULL, m_Node.nLen - sizeof(J_StreamHeader));
	
	//fprintf(stderr, "CXBuffer::EraseBuffer() len = %d\n", m_Node.nLen);
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
