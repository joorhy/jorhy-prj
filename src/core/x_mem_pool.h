#ifndef __X_MEM_POOL_H_
#define __X_MEM_POOL_H_
#include "j_common.h"
#include "x_lock.h"

struct J_MEM_NODE
{
	j_uint32_t size;
	J_MEM_NODE *prev;
	J_MEM_NODE *next;
	j_char_t *p;
};

class JO_API CXMemPool
{
public:
	CXMemPool();
	~CXMemPool();

public:
	j_result_t Create(j_uint32_t nSize);
	j_void_t Destroy();
	j_void_t *Alloc(j_uint32_t nSize);
	j_void_t Free(j_void_t *p);

private:
	J_MEM_NODE *FindFreeNode(j_uint32_t nSize);
	J_MEM_NODE *FindBusyNode(j_void_t *p);
	void AddList(J_MEM_NODE **pList, J_MEM_NODE *pNode);
	void DeleteList(J_MEM_NODE **pList, J_MEM_NODE *pNode);
	J_MEM_NODE *SplitMem(J_MEM_NODE **pNode, j_int32_t nSize);
	void MergerMem();

private:
	j_char_t *m_pMemory;
	j_uint32_t m_nMemSize;
	J_MEM_NODE *m_pBusyList;
	J_MEM_NODE *m_pFreeList;
	J_OS::CTLock m_locker;
};

#endif //~__X_MEM_POOL_H_