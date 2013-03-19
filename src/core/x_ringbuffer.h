#ifndef __X_RINGBUFFER_H_
#define __X_RINGBUFFER_H_
#include "j_type.h"

///环形流队列
#define CACHE_FRAME_NUM 100
#define BUFFER_SIZE (1024 * 1024 * 5)

struct J_MEMNODE
{
	int nLen;
	char *pData;
};
#define J_MEMNODE_LEN (sizeof(J_MEMNODE))

class CRingBuffer
{
	public:
		CRingBuffer(int nCacheFrameNum = BUFFER_SIZE, int nBufferSize = BUFFER_SIZE);
		~CRingBuffer();

	public:
		int ResetBufferSize(int nBufferSize);
		int PushBuffer(const char *pBuffer, J_StreamHeader &streamHeader);
		int PopBuffer(char *pBuffer, J_StreamHeader &streamHeader);
		void SetPreFrameNum(int nFrameNum) {}

	private:
		void Read(char *pData, int nLen);
		void Write(const char *pData, int nLen);
		int GetIdleLength();
		void EraseBuffer();
		char *AddBuffer(char *pBuffer, int nLen);
		
	private:
		pthread_mutex_t m_mutex;
		pthread_cond_t m_cond;
	
		char *m_pBuffer;
		char *m_pBegin;
		char *m_pEnd;
		
		char *m_pWritePoint;
		char *m_pReadPoint;
		int m_nDataLen;
		
		J_MEMNODE m_Node;
};
typedef std::vector<CRingBuffer *>	j_vec_buffer_t;

#endif //~__X_RINGBUFFER_H_
