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
	J_MEM_NODE *pNode = FindFreeNode(nSize);
	if (pNode != NULL)
	{
		DeleteFreeList(pNode, nSize);
		pNode->size = nSize;
		pNode->prev = NULL;
		pNode->next = NULL;
		AddBusyList(pNode);
		return pNode->p;
	}
	return NULL;
}

j_void_t CXMemPool::Free(j_void_t *p)
{

}

J_MEM_NODE *CXMemPool::FindBusyNode(j_void_t *p)
{
	J_MEM_NODE *pNode = m_pBusyList;
	for (; pNode != NULL; pNode = pNode->next)
	{
		if (pNode->p == p)
			return pNode;
	}
	return NULL;
}

J_MEM_NODE *CXMemPool::FindFreeNode(j_uint32_t nSize)
{
	J_MEM_NODE *pNode = m_pFreeList;
	for (; pNode != NULL; pNode = pNode->next)
	{
		if (pNode->size >= nSize)
			return pNode;
	}
	return NULL;
}

void CXMemPool::AddFreeList(J_MEM_NODE *pNode)
{
	if (m_pFreeList == NULL)
		m_pBusyList = pNode;
	else
	{
		J_MEM_NODE *pNodeFree = m_pFreeList;
		for (; pNodeFree != NULL; pNodeFree = pNodeFree->next)
		{
			if (pNodeFree->prev == NULL && pNode->p < pNodeFree->p)
			{
				m_pBusyList = pNode;
				pNode->prev = pNodeFree->prev;
				pNode->next = pNodeFree;
			}
			else if (pNodeFree->next == NULL && pNode->p > pNodeFree->p)
			{
				pNode->next = pNodeFree->next;
				pNodeFree->next = pNode;
			}
			else if (pNode->p > pNodeFree->p && pNode->p < pNodeFree->next->p)
			{
				pNode->prev = pNodeFree;
				pNode->next = pNodeFree->next;
				pNodeFree->next->prev = pNode;
				pNodeFree->next = pNode;
			}
		}
	}
	MergerMem();
}

void CXMemPool::DeleteFreeList(J_MEM_NODE *pNode, j_uint32_t nSize)
{
	if (pNode->size == nSize)
	{
		if (pNode->prev != NULL)
			pNode->prev->next = pNode->next;
		else
			m_pFreeList = pNode->next; 
	}
	else
	{
		J_MEM_NODE *pFreeNew = (J_MEM_NODE *)(pNode->p + nSize);
		pFreeNew->prev = NULL;
		pFreeNew->next = NULL;
		pFreeNew->size = pNode->size - nSize - sizeof(J_MEM_NODE);
		pFreeNew->p = (pNode->p + nSize + sizeof(J_MEM_NODE));

		if (pNode->prev != NULL)
			pNode->prev->next = pFreeNew;
		else
			m_pFreeList = pFreeNew;

		pFreeNew->prev = pNode->prev;
		pFreeNew->next = pNode->next;
	}
}

void CXMemPool::AddBusyList(J_MEM_NODE *pNode)
{
	if (m_pBusyList == NULL)
		m_pBusyList = pNode;
	else
	{
		J_MEM_NODE *pNodeBusy = m_pBusyList;
		for (; pNodeBusy != NULL; pNodeBusy = pNodeBusy->next)
		{
			if (pNodeBusy->prev == NULL && pNode->p < pNodeBusy->p)
			{
				m_pBusyList = pNode;
				pNode->prev = pNodeBusy->prev;
				pNode->next = pNodeBusy;
			}
			else if (pNodeBusy->next == NULL && pNode->p > pNodeBusy->p)
			{
				pNode->next = pNodeBusy->next;
				pNodeBusy->next = pNode;
			}
			else if (pNode->p > pNodeBusy->p && pNode->p < pNodeBusy->next->p)
			{
				pNode->prev = pNodeBusy;
				pNode->next = pNodeBusy->next;
				pNodeBusy->next->prev = pNode;
				pNodeBusy->next = pNode;
			}
		}
	}
}

void CXMemPool::DeleteBusyList(J_MEM_NODE *pNode)
{
	J_MEM_NODE *pNodeBusy = m_pBusyList;
	for (; pNodeBusy != NULL; pNodeBusy = pNodeBusy->next)
	{
		if (pNodeBusy->p == pNode->p)
		{
			pNodeBusy->prev->next = pNodeBusy->next;
			pNodeBusy->next->prev = pNodeBusy->prev;
			return;
		}
	}
}

void CXMemPool::MergerMem()
{
	J_MEM_NODE *pNode = m_pFreeList;
	for (; pNode != NULL; )
	{
		if (pNode->next != NULL)
		{
			if ((pNode->p + pNode->size) == (j_char_t *)pNode->next)
			{
				pNode->size = pNode->size + sizeof(J_MEM_NODE) + pNode->next->size;
				pNode->next = pNode->next->next;
			}
			else
				pNode = pNode->next;
		}
	}
}