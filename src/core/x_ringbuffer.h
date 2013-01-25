#ifndef __X_RINGBUFFER_H_
#define __X_RINGBUFFER_H_
#include "j_type.h"

///环形流队列
#define CACHE_FRAME_NUM 100
#define RING_BUFFER_SIZE (4 * 1024 * 1024)

class CRingBuffer
{
public:
	CRingBuffer(int nCacheFrameNum = CACHE_FRAME_NUM, int nBufferSize = RING_BUFFER_SIZE);
	~CRingBuffer();

public:
	int ResetBufferSize(int nBufferSize);
	int PushBuffer(const char *pBuffer, J_StreamHeader &streamHeader);
	int PopBuffer(char *pBuffer, J_StreamHeader &streamHeader);
	void SetPreFrameNum(int nFrameNum) { if (nFrameNum > CACHE_FRAME_NUM) m_nCacheFrameNum = nFrameNum; }

private:
	J_OS::RWLocker_t m_rwLocker;
	int m_nBufferSize;
	char *m_pBuffer;

	char *m_pBegin;		//内存开始地址
	char *m_pEnd;		//内存结束地址

	char *m_pHead;		//数据开始地址
	char *m_pTail;		//数据结束地址

	unsigned int m_nCacheFrameNum;
	unsigned int m_nFrameNum;
};

#endif //~__X_RINGBUFFER_H_
