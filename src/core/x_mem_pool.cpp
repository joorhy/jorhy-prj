#include "x_mem_pool.h"

CXMemPool::CXMemPool()
{
	m_pMemory = NULL;
	m_nMemSize = 0;
	m_pBusyList = NULL;
	m_pFreeList = NULL;;
}

CXMemPool::~CXMemPool()
{
	Destroy();
}

j_result_t CXMemPool::Create(j_uint32_t nSize)
{
	if (m_pMemory == NULL)
	{
		m_pMemory = new char[nSize];
		m_nMemSize = nSize;
		J_MEM_NODE *pFreeNode = (J_MEM_NODE *)m_pMemory;
		pFreeNode->size = nSize - sizeof(J_MEM_NODE);
		pFreeNode->p = m_pMemory + sizeof(J_MEM_NODE);
		pFreeNode->prev = NULL;
		pFreeNode->next = NULL;
		m_pFreeList = pFreeNode;
	}
	return J_OK;
}

j_void_t CXMemPool::Destroy()
{
	if (m_pMemory != NULL)
		delete m_pMemory;
}

j_void_t *CXMemPool::Alloc(j_uint32_t nSize)
{
	TLock(m_locker);
	J_MEM_NODE *pNode = FindFreeNode(nSize);
	void *pRetVal = NULL;
	if (pNode != NULL)
	{
		J_MEM_NODE *pFreeNode = SplitMem(&pNode, nSize);
		DeleteList(&m_pFreeList, pNode);
		AddList(&m_pFreeList, pFreeNode);
		AddList(&m_pBusyList, pNode);
		pRetVal = pNode->p;
	}
	TUnlock(m_locker);

	return pRetVal;
}

j_void_t CXMemPool::Free(j_void_t *p)
{
	if (p == NULL)
		return;

	TLock(m_locker);
	J_MEM_NODE *pNode = FindBusyNode(p);
	if (pNode != NULL)
	{
		DeleteList(&m_pBusyList, pNode);
		AddList(&m_pFreeList, pNode);
		MergerMem();
	}
	TUnlock(m_locker);
}

J_MEM_NODE *CXMemPool::FindBusyNode(j_void_t *p)
{
	J_MEM_NODE *pNode = m_pBusyList;
	while (pNode != NULL)
	{
		if (pNode->p == p)
			return pNode;
		pNode = pNode->next;
	}
	return NULL;
}

J_MEM_NODE *CXMemPool::FindFreeNode(j_uint32_t nSize)
{
	J_MEM_NODE *pNode = m_pFreeList;
	while (pNode != NULL)
	{
		if (pNode->size > (nSize + sizeof(J_MEM_NODE)))
			return pNode;
		pNode = pNode->next;
	}
	return NULL;
}

void CXMemPool::AddList(J_MEM_NODE **pList, J_MEM_NODE *pNode)
{
	if (*pList == NULL)
		*pList = pNode;
	else
	{
		J_MEM_NODE *pNodeFree = *pList;
		while (pNodeFree != NULL)
		{
			//前端插入
			if (pNodeFree->prev == NULL && pNode->p < pNodeFree->p)
			{
				*pList = pNode;
				pNode->prev = pNodeFree->prev;
				pNode->next = pNodeFree;
				pNodeFree->prev = *pList;
				break;
			}
			//后端插入
			else if (pNodeFree->next == NULL && pNode->p > pNodeFree->p)
			{
				pNode->next = pNodeFree->next;
				pNodeFree->next = pNode;
				pNode->prev = pNodeFree;
				break;
			}
			//中间插入
			else if (pNode->p > pNodeFree->p && pNode->p < pNodeFree->next->p)
			{
				pNode->prev = pNodeFree;
				pNode->next = pNodeFree->next;
				pNodeFree->next->prev = pNode;
				pNodeFree->next = pNode;
				break;
			}
			pNodeFree = pNodeFree->next;
		}
	}
}

void CXMemPool::DeleteList(J_MEM_NODE **pList, J_MEM_NODE *pNode)
{
	J_MEM_NODE *pNodeFree = *pList;
	while (pNodeFree != NULL)
	{
		if (pNodeFree->p == pNode->p)
		{
			//前端删除
			if (pNodeFree == *pList)
			{
				*pList = pNodeFree->next;
				break;
			}
			//后端删除
			else if (pNodeFree->next == NULL)
			{
				pNodeFree->prev->next = NULL;
				break;
			}
			//中间删除
			else
			{
				pNodeFree->prev->next = pNodeFree->next;
				pNodeFree->next->prev = pNodeFree->prev;
				break;
			}
		}
		pNodeFree = pNodeFree->next;
	}
}

J_MEM_NODE *CXMemPool::SplitMem(J_MEM_NODE **pNode, j_int32_t nSize)
{
	J_MEM_NODE *pNodeFree = NULL;
	if ((*pNode)->size > nSize + sizeof(J_MEM_NODE))
	{
		pNodeFree = (J_MEM_NODE *)((*pNode)->p + nSize);
		pNodeFree->size = (*pNode)->size - nSize - sizeof(J_MEM_NODE);
		pNodeFree->p =  (*pNode)->p + nSize + sizeof(J_MEM_NODE);
		pNodeFree->prev = NULL;
		pNodeFree->next = NULL;
		(*pNode)->size = nSize;
	}
	return pNodeFree;
}

void CXMemPool::MergerMem()
{
	J_MEM_NODE *pNode = m_pFreeList;
	while (pNode != NULL)
	{
		if (pNode->next != NULL)
		{
			if ((pNode->p + pNode->size) == (j_char_t *)pNode->next)
			{
				pNode->size = pNode->size + sizeof(J_MEM_NODE) + pNode->next->size;
				pNode->next = pNode->next->next;
				if (pNode->next != NULL)
					pNode->next->prev = pNode;
				continue;
			}
		}
		pNode = pNode->next;
	}
}