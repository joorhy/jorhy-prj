#include "x_pl_buffer_fifo.h"
#include "x_pl_error.h"
#include "x_pl_log.h"
#include "assert.h"

CXPlBufferFIFO::CXPlBufferFIFO(int size)
:J_PlBuffer(size)
{
	m_bufferID		= BUFFER_FIFO;
	m_nBuffSize		= size;
	m_pBuffer			= new char[size];
	m_pBegin			= m_pBuffer;
	m_pEnd			= m_pBuffer + size;
	m_pWritePoint  = m_pReadPoint = m_pBegin;
	m_nDataLen		= 0;
	m_nDiscardedFrameNum = 0;
}

CXPlBufferFIFO::~CXPlBufferFIFO(void)
{
	m_lock.WriteLock();
	if (m_pBuffer)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}
	m_lock.WriteUnlock();
}

J_PL_RESULT CXPlBufferFIFO::Read(char *OUT_Buffer,char *OUT_extra,j_pl_buffer_t &OUT_Header)
{
	m_lock.ReadLock();
	if (m_nDataLen > 0)
	{
		memset(&m_Node, 0, sizeof(m_Node));
		Read((char *)&m_Node, J_MEMNODE_LEN);
		Read((char *)&OUT_Header, sizeof(j_pl_buffer_t));
		Read((char *)OUT_extra, OUT_Header.extrasize);
		Read(OUT_Buffer, m_Node.nLen - OUT_Header.extrasize);
		if (OUT_Header.datatype == 0)
		{
			j_pl_decode_t *pExHeader = (j_pl_decode_t *)OUT_extra;
			if (pExHeader->type != DECODE_I_FRAME)
				--m_nDiscardedFrameNum;
		}

		m_lock.ReadUnlock();
		return J_PL_NO_ERROR;
	}
	m_lock.ReadUnlock();

	return J_PL_ERROR_EMPTY_BUFFER;
}

J_PL_RESULT CXPlBufferFIFO::Write(char *IN_Buffer,char *IN_extra,j_pl_buffer_t &IN_Header)
{
	m_lock.WriteLock();
	if (IN_Header.datatype == 0)
	{
		j_pl_decode_t *pExHeader = (j_pl_decode_t *)IN_extra;
		if (pExHeader->type != DECODE_I_FRAME)
		{
			++m_nDiscardedFrameNum;
			//m_lock.WriteUnlock();
			//return J_PL_NO_ERROR;
		}
	}

	int nLen = IN_Header.datasize;
	while (GetIdleLength() < (nLen + J_MEMNODE_LEN +sizeof(j_pl_buffer_t) + IN_Header.extrasize))
	{
		if (m_nDataLen < 0)
		{
			//J_OS::LOGINFO("CRingBuffer::PushBuffer Buffer Error");
			m_lock.WriteUnlock();
			return J_PL_ERROR_UNKNOW;
		}
		EraseBuffer();
	}

	memset(&m_Node, 0, sizeof(m_Node));
	m_Node.nLen = nLen + IN_Header.extrasize;
	m_Node.pData = AddBuffer(m_pWritePoint, J_MEMNODE_LEN);
	Write((const char *)&m_Node, J_MEMNODE_LEN);
	Write((const char *)&IN_Header, sizeof(j_pl_buffer_t));
	Write((const char *)IN_extra, IN_Header.extrasize);
	Write(IN_Buffer, nLen);
	m_lock.WriteUnlock();
	m_sem.Post();

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlBufferFIFO::MoveNext()
{
	/*m_lock.WriteLock();

	m_pReadPoint = m_pSetpPoint;
	m_nReadableSize -= m_nStepSize;
	m_nReadableNum--;
	m_lock.WriteUnlock();*/
	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlBufferFIFO::Flush()
{
	/*m_lock.WriteLock();

	if(m_pBegin == NULL)
		return J_PL_NO_ERROR;
	m_pReadPoint	= m_pBegin;
	m_pWritePoint	= m_pBegin;
	m_pSetpPoint	= m_pBegin;
	m_nStepSize		= 0;
	m_nReadableSize = 0;
	m_nReadableNum	= 0;
	memset(m_pBegin,0,m_nBuffSize);

	m_lock.WriteUnlock();*/
	return J_PL_NO_ERROR;
}

void CXPlBufferFIFO::WaitData()
{
	m_sem.WaitTime(300);
}

void CXPlBufferFIFO::Read(char *pData, int nLen)
{		
	GetData(pData, nLen);
	m_pReadPoint = AddBuffer(m_pReadPoint, nLen);
	m_nDataLen -= nLen;
}

void CXPlBufferFIFO::Write(const char *pData, int nLen)
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

int CXPlBufferFIFO::GetData(char *pData, int nLen, int nOffset)
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

int CXPlBufferFIFO::GetIdleLength()
{
	return m_nBuffSize - m_nDataLen;
}

void CXPlBufferFIFO::EraseBuffer()
{
	int nMoveLen = 0;
	int nOffset = 0;
	int nDorpLen = 0;
	memset(&m_streamHeader, 0, sizeof(j_pl_buffer_t));
	memset(&m_Node, 0, J_MEMNODE_LEN);
	GetData((char *)&m_Node, J_MEMNODE_LEN);
	GetData((char *)&m_streamHeader, sizeof(j_pl_buffer_t), J_MEMNODE_LEN);
	nMoveLen = m_Node.nLen + J_MEMNODE_LEN + sizeof(j_pl_buffer_t);
	nDorpLen = m_Node.nLen + J_MEMNODE_LEN + sizeof(j_pl_buffer_t);

	m_pReadPoint = AddBuffer(m_pReadPoint, nDorpLen);
	m_nDataLen -= nDorpLen;

	//j_pl_info("CXBuffer::EraseBuffer() len = %d ex_len = %d, user = %u\n", m_Node.nLen, m_streamHeader.extrasize, this);
	//fprintf(stderr, "CXBuffer::EraseBuffer() len = %d\n", m_Node.nLen);
}

void CXPlBufferFIFO::MoveBuffer(int nOffset, int nLen)
{
	if (nOffset > 0 && nLen > 0)
	if (m_pEnd - m_pReadPoint <= nOffset)
	{
		memmove(m_pBegin + nOffset - (m_pEnd - m_pReadPoint) , m_pReadPoint, nLen);
	}
	else
		memmove(m_pReadPoint + nOffset, m_pReadPoint, nLen);
}

char *CXPlBufferFIFO::AddBuffer(char *pBuffer, int nLen)
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