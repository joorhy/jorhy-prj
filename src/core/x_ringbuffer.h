#ifndef __X_RINGBUFFER_H_
#define __X_RINGBUFFER_H_
#include "j_type.h"
#include "x_lock.h"

///环形流队列
#define CACHE_FRAME_NUM 100
#define BUFFER_SIZE (1024 * 1024 * 5)

struct J_MEMNODE
{
	int nLen;
	char *pData;
};
#define J_MEMNODE_LEN (sizeof(J_MEMNODE))

class JO_API CRingBuffer
{
	public:
		CRingBuffer(int nCacheFrameNum = CACHE_FRAME_NUM, int nBufferSize = BUFFER_SIZE);
		~CRingBuffer();

	public:
		int ResetBufferSize(int nBufferSize);
		int PushBuffer(const char *pBuffer, J_StreamHeader &streamHeader);
		int PopBuffer(char *pBuffer, J_StreamHeader &streamHeader);
		void SetPreFrameNum(int nFrameNum) {}
		int GetIdleLength();

	private:
		void Read(char *pData, int nLen);
		void Write(const char *pData, int nLen);
		int GetData(char *pData, int nLen, int nOffset = 0);
		void EraseBuffer();
		void MoveBuffer(int nOffset, int nLen);
		char *AddBuffer(char *pBuffer, int nLen);
		
	private:
		J_OS::CTLock m_mutex;
	
		char *m_pBuffer;
		char *m_pBegin;
		char *m_pEnd;
		
		char *m_pWritePoint;
		char *m_pReadPoint;
		int m_nDataLen;
		
		J_MEMNODE m_Node;
		J_StreamHeader m_streamHeader;
		int m_nDiscardedFrameNum;		//非关键
		int m_nBufferSize;
};
typedef std::vector<CRingBuffer *>	j_vec_buffer_t;

#endif //~__X_RINGBUFFER_H_
