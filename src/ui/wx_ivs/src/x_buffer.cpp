#include "x_buffer.h"

CXBuffer::CXBuffer(int nBuffSize)
{
	m_pBuffer = new char[nBuffSize];
	m_pBegin = m_pBuffer;
	m_pEnd = m_pBuffer + nBuffSize;
	m_pBusyMem = NULL;
	m_pIdleMem = (J_MEMHEAD *)m_pBuffer;
	m_pIdleMem->nLen = nBuffSize - J_MEMHEAD_LEN;
	m_pIdleMem->pData = m_pBuffer + J_MEMHEAD_LEN;
	m_pIdleMem->pPrev = NULL;
	m_pIdleMem->pNext = NULL;
}

CXBuffer::~CXBuffer()
{
	delete m_pBuffer;
}
	
char *CXBuffer::LockBuffer(int nLen, bool bFlag)
{
	m_criticalSection.Enter();
	if (bFlag)
	{
		J_MEMHEAD *pIdleMem = m_pIdleMem;
		while (pIdleMem != NULL)
		{
			if (pIdleMem->nLen >= nLen)
			{
				AddBusyMem(pIdleMem, nLen);
			}
		}
	}
	else
	{

	}
	return NULL;
}

void CXBuffer::UnlockBuffer(bool bFlag)
{
	m_criticalSection.Leave();
}

void CXBuffer::AddBusyMem(J_MEMHEAD *pMemHead, int nLen)
{
	
}

void CXBuffer::AddIdleMem(J_MEMHEAD *pMemHead, int nLen)
{
	
}