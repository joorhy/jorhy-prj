#include <string.h>

#include "j_module.h"
#include "x_ringbuffer.h"
#include "x_log.h"

CRingBuffer::CRingBuffer(int nCacheFrameNum, int nBufferSize)
: m_nBufferSize(0)
, m_pBuffer(NULL)
, m_nFrameNum(0)
{
	m_nBufferSize = nBufferSize;
	m_nCacheFrameNum = nCacheFrameNum;

	if (NULL == m_pBuffer)
	{
		m_pBuffer = new char[m_nBufferSize];
	}

	m_pBegin = m_pBuffer;
	m_pEnd = (char *)m_pBegin + m_nBufferSize;

	m_pHead = m_pBegin;
	m_pTail = m_pBegin;
}
CRingBuffer::~CRingBuffer()
{
	if (m_pBuffer != NULL)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}
}

int CRingBuffer::ResetBufferSize(int nBufferSize)
{
	if (nBufferSize <= m_nBufferSize)
		return 0;

	if (m_pBuffer != NULL)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}

	m_pBuffer = new char[nBufferSize];
	m_nBufferSize = nBufferSize;

	m_pBegin = m_pBuffer;
	m_pEnd = (char *)m_pBegin + m_nBufferSize;

	m_pHead = m_pBegin;
	m_pTail = m_pBegin;

	return 0;
}

int CRingBuffer::PushBuffer(const char *pBuffer, J_StreamHeader &streamHeader)
{
	WLock(m_rwLocker);
	while ((unsigned int)(m_pEnd - m_pTail) <= streamHeader.dataLen + sizeof(J_StreamHeader)
			|| (m_nFrameNum >= m_nCacheFrameNum
			&& (m_pTail - m_pHead > 0)))
	{
		int nTotleLen = m_pTail - m_pHead;
		J_StreamHeader tStreamHeader;
		memcpy(&tStreamHeader, m_pHead, sizeof(J_StreamHeader));
		m_pHead += tStreamHeader.dataLen + sizeof(J_StreamHeader);
		memmove(m_pBegin, m_pHead, nTotleLen - (tStreamHeader.dataLen + sizeof(J_StreamHeader)));
		m_pHead = m_pBegin;
		m_pTail -= (tStreamHeader.dataLen + sizeof(J_StreamHeader));

		if (tStreamHeader.frameType == J_VideoPFrame || tStreamHeader.frameType == J_VideoIFrame)
			--m_nFrameNum;
	}

	if (m_pEnd - m_pTail > (long)(streamHeader.dataLen + sizeof(J_StreamHeader)))
	{
		if (streamHeader.frameType == J_VideoPFrame || streamHeader.frameType == J_VideoIFrame)
			++m_nFrameNum;

		memcpy(m_pTail, &streamHeader, sizeof(J_StreamHeader));
		if (streamHeader.dataLen > 0)
            memcpy(m_pTail + sizeof(J_StreamHeader), pBuffer, streamHeader.dataLen);
		m_pTail += (streamHeader.dataLen + sizeof(J_StreamHeader));
		RWUnlock(m_rwLocker);

		return J_OK;
	}
	RWUnlock(m_rwLocker);

	return J_UNKNOW;
}

int CRingBuffer::PopBuffer(char *pBuffer, J_StreamHeader &streamHeader)
{
	RLock(m_rwLocker);
	int nTotleLen = m_pTail - m_pHead;
	if (m_pTail - m_pHead > 0)
	{
		memcpy(&streamHeader, m_pHead, sizeof(J_StreamHeader));
		memcpy(pBuffer, m_pHead + sizeof(J_StreamHeader), streamHeader.dataLen);
		m_pHead += streamHeader.dataLen + sizeof(J_StreamHeader);
		memmove(m_pBegin, m_pHead, nTotleLen - (streamHeader.dataLen + sizeof(J_StreamHeader)));
		m_pHead = m_pBegin;
		m_pTail -= (streamHeader.dataLen + sizeof(J_StreamHeader));

		if (streamHeader.frameType == J_VideoPFrame || streamHeader.frameType == J_VideoIFrame)
			--m_nFrameNum;

		RWUnlock(m_rwLocker);

		return J_OK;
	}
	RWUnlock(m_rwLocker);

	return J_UNKNOW;
}
