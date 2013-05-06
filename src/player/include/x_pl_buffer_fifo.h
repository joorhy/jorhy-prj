#pragma once
#include "x_pl_buffer.h"

struct J_MEMNODE
{
	int nLen;
	char *pData;
};
#define J_MEMNODE_LEN (sizeof(J_MEMNODE))

class CXPlBufferFIFO : public J_PlBuffer
{
public:
	CXPlBufferFIFO(int size);
	~CXPlBufferFIFO(void);

	virtual J_PL_RESULT Read(char *OUT_Buffer,char *OUT_extra,j_pl_buffer_t &OUT_Header);
	virtual J_PL_RESULT Write(char *IN_Buffer,char *IN_extra,j_pl_buffer_t &IN_Header);
	virtual J_PL_RESULT MoveNext();
	virtual J_PL_RESULT Flush();
	virtual void WaitData();

private:
private:
	void Read(char *pData, int nLen);
	void Write(const char *pData, int nLen);
	int GetData(char *pData, int nLen, int nOffset = 0);
	int GetIdleLength();
	void EraseBuffer();
	void MoveBuffer(int nOffset, int nLen);
	char *AddBuffer(char *pBuffer, int nLen);

private:
	char *m_pBuffer;
	char *m_pBegin;
	char *m_pEnd;

	char *m_pWritePoint;
	char *m_pReadPoint;
	int m_nBuffSize;
	int m_nDataLen;

	J_MEMNODE m_Node;
	j_pl_buffer_t m_streamHeader;
	int m_nDiscardedFrameNum;		//·Ç¹Ø¼ü
};
