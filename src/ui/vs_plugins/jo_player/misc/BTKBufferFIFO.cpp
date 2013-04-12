#include "BTKBufferFIFO.h"
#include "..\include\BTKError.h"
#include "..\include\BTKLog.h"
#include "assert.h"

BTKBufferFIFO::BTKBufferFIFO(int size)
:BTKBuffer(size)
{
	m_bufferID		= BUFFER_LIFO;
	m_nBuffSize		= size;
	m_pBuffer			= new char[size];
	m_pBegin			= m_pBuffer;
	m_pEnd			= m_pBuffer + size;
	m_pWritePoint  = m_pReadPoint = m_pBegin;
	m_nDataLen		= 0;
	m_nDiscardedFrameNum = 0;
}

BTKBufferFIFO::~BTKBufferFIFO(void)
{
	m_lock.WriteLock();
	if (m_pBuffer)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}
	m_lock.WriteUnlock();
}

BTK_RESULT BTKBufferFIFO::Read(char *OUT_Buffer,char *OUT_extra,btk_buffer_t &OUT_Header)
{
	m_lock.ReadLock();
	if (m_nDataLen > 0)
	{
		memset(&m_Node, 0, sizeof(m_Node));
		Read((char *)&m_Node, J_MEMNODE_LEN);
		Read((char *)&OUT_Header, sizeof(btk_buffer_t));
		Read((char *)OUT_extra, OUT_Header.extrasize);
		Read(OUT_Buffer, m_Node.nLen - OUT_Header.extrasize);
		if (OUT_Header.datatype == 0)
		{
			btk_decode_t *pExHeader = (btk_decode_t *)OUT_extra;
			if (pExHeader->type != DECODE_I_FRAME)
				--m_nDiscardedFrameNum;
		}

		m_lock.ReadUnlock();
		return BTK_NO_ERROR;
	}
	m_lock.ReadUnlock();

	return BTK_ERROR_UNKNOW;
}

BTK_RESULT BTKBufferFIFO::Write(char *IN_Buffer,char *IN_extra,btk_buffer_t &IN_Header)
{
	m_lock.WriteLock();
	if (IN_Header.datatype == 0)
	{
		btk_decode_t *pExHeader = (btk_decode_t *)IN_extra;
		if (pExHeader->type != DECODE_I_FRAME)
		{
			//++m_nDiscardedFrameNum;
			m_lock.WriteUnlock();
			return BTK_NO_ERROR;
		}
	}

	int nLen = IN_Header.datasize;
	while (GetIdleLength() < (nLen + J_MEMNODE_LEN +sizeof(btk_buffer_t) + IN_Header.extrasize))
	{
		if (m_nDataLen < 0)
		{
			//J_OS::LOGINFO("CRingBuffer::PushBuffer Buffer Error");
			m_lock.WriteUnlock();
			return BTK_ERROR_UNKNOW;
		}
		EraseBuffer();
	}

	memset(&m_Node, 0, sizeof(m_Node));
	m_Node.nLen = nLen + IN_Header.extrasize;
	m_Node.pData = AddBuffer(m_pWritePoint, J_MEMNODE_LEN);
	Write((const char *)&m_Node, J_MEMNODE_LEN);
	Write((const char *)&IN_Header, sizeof(btk_buffer_t));
	Write((const char *)IN_extra, IN_Header.extrasize);
	Write(IN_Buffer, nLen);
	m_lock.WriteUnlock();
	m_sem.Post();

	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferFIFO::MoveNext()
{
	/*m_lock.WriteLock();

	m_pReadPoint = m_pSetpPoint;
	m_nReadableSize -= m_nStepSize;
	m_nReadableNum--;
	m_lock.WriteUnlock();*/
	return BTK_NO_ERROR;
}

BTK_RESULT BTKBufferFIFO::Flush()
{
	/*m_lock.WriteLock();

	if(m_pBegin == NULL)
		return BTK_NO_ERROR;
	m_pReadPoint	= m_pBegin;
	m_pWritePoint	= m_pBegin;
	m_pSetpPoint	= m_pBegin;
	m_nStepSize		= 0;
	m_nReadableSize = 0;
	m_nReadableNum	= 0;
	memset(m_pBegin,0,m_nBuffSize);

	m_lock.WriteUnlock();*/
	return BTK_NO_ERROR;
}

void BTKBufferFIFO::WaitData()
{
	m_sem.WaitTime(300);
}

void BTKBufferFIFO::Read(char *pData, int nLen)
{		
	GetData(pData, nLen);
	m_pReadPoint = AddBuffer(m_pReadPoint, nLen);
	m_nDataLen -= nLen;
}

void BTKBufferFIFO::Write(const char *pData, int nLen)
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

int BTKBufferFIFO::GetData(char *pData, int nLen, int nOffset)
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

int BTKBufferFIFO::GetIdleLength()
{
	return m_nBuffSize - m_nDataLen;
}

void BTKBufferFIFO::EraseBuffer()
{
	int nMoveLen = 0;
	int nOffset = 0;
	int nDorpLen = 0;
	memset(&m_streamHeader, 0, sizeof(btk_buffer_t));
	memset(&m_Node, 0, J_MEMNODE_LEN);
	GetData((char *)&m_Node, J_MEMNODE_LEN);
	GetData((char *)&m_streamHeader, sizeof(btk_buffer_t), J_MEMNODE_LEN);
	nMoveLen = m_Node.nLen + J_MEMNODE_LEN + sizeof(btk_buffer_t);
	if (m_streamHeader.datatype == 0)
	{
		if (m_nDiscardedFrameNum > 0)
		{
			btk_decode_t headerEx = {0};
			GetData((char *)&headerEx, sizeof(btk_decode_t), sizeof(btk_buffer_t) + J_MEMNODE_LEN);
			if (headerEx.type == DECODE_I_FRAME)
			{
				memset(&m_Node, 0, sizeof(m_Node));
				memset(&headerEx, 0, sizeof(btk_decode_t));
				GetData((char *)&m_Node, J_MEMNODE_LEN, nMoveLen);
				GetData((char *)&headerEx, sizeof(btk_decode_t), nMoveLen + J_MEMNODE_LEN + sizeof(btk_buffer_t));
				if (headerEx.type == DECODE_I_FRAME)
				{
					nMoveLen += m_Node.nLen + J_MEMNODE_LEN + sizeof(btk_buffer_t);
				}
				else
				{
					--m_nDiscardedFrameNum;
					nOffset = m_Node.nLen + J_MEMNODE_LEN + sizeof(btk_buffer_t);
					nDorpLen = m_Node.nLen + J_MEMNODE_LEN + sizeof(btk_buffer_t);
				}
			}

			int nCurOffset = nMoveLen;
			while (m_nDiscardedFrameNum > 0 && nCurOffset < m_nDataLen)
			{
				memset(&m_Node, 0, sizeof(m_Node));
				memset(&headerEx, 0, sizeof(btk_decode_t));
				GetData((char *)&m_Node, J_MEMNODE_LEN, nCurOffset);
				GetData((char *)&headerEx, sizeof(btk_decode_t), nCurOffset + J_MEMNODE_LEN + sizeof(btk_buffer_t));
				//btk_Info("BTKBufferFIFO::EraseBuffer() len = %d ex_len = %d, user = %u\n", m_Node.nLen, headerEx.type, this);
				if (headerEx.type == DECODE_I_FRAME)
					break;
				nCurOffset += m_Node.nLen + J_MEMNODE_LEN + sizeof(btk_buffer_t);
				nDorpLen += m_Node.nLen + J_MEMNODE_LEN + sizeof(btk_buffer_t);
				nOffset += m_Node.nLen + J_MEMNODE_LEN + sizeof(btk_buffer_t);
				--m_nDiscardedFrameNum;
			}
			MoveBuffer(nOffset, nMoveLen);
			btk_Info("CXBuffer::EraseBuffer() len = %d ex_len = %d, user = %u\n", m_Node.nLen, headerEx.type, this);
		}
		else
		{
			nDorpLen = m_Node.nLen + J_MEMNODE_LEN + sizeof(btk_buffer_t);
		}
	}
	else
	{
		nDorpLen = m_Node.nLen + J_MEMNODE_LEN + sizeof(btk_buffer_t);
	}

	m_pReadPoint = AddBuffer(m_pReadPoint, nDorpLen);
	m_nDataLen -= nDorpLen;

	//btk_Info("CXBuffer::EraseBuffer() len = %d ex_len = %d, user = %u\n", m_Node.nLen, m_streamHeader.extrasize, this);
	//fprintf(stderr, "CXBuffer::EraseBuffer() len = %d\n", m_Node.nLen);
}

void BTKBufferFIFO::MoveBuffer(int nOffset, int nLen)
{
	if (nOffset > 0 && nLen > 0)
	if (m_pEnd - m_pReadPoint <= nOffset)
	{
		memmove(m_pBegin + nOffset - (m_pEnd - m_pReadPoint) , m_pReadPoint, nLen);
	}
	else
		memmove(m_pReadPoint + nOffset, m_pReadPoint, nLen);
}

char *BTKBufferFIFO::AddBuffer(char *pBuffer, int nLen)
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