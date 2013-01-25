#ifndef __J_OBJ_H_
#define __J_OBJ_H_

#include "x_errtype.h"
#include "x_ringbuffer.h"
#include "x_log.h"

struct J_Obj
{
	virtual ~J_Obj() {}
};

///原子操作 long型数据
inline long atomic_inc(long volatile *v)
{
	__asm__ __volatile__("lock incl %0" : "+m"(*v));
	return *v;
}

inline long atomic_dec(long volatile *v)
{
	__asm__ __volatile__("lock decl %0" : "+m"(*v));
	return *v;
}

///实现引用计数加减
template <typename CBsae>
class J_BaseAdapter : public CBsae
{
protected:
	J_BaseAdapter() : m_nRefCnt(0) {}
	virtual ~J_BaseAdapter() {}

protected:
	long IncRef()
	{
		return atomic_inc(&m_nRefCnt);
	}

	long DecRef()
	{
		return atomic_dec(&m_nRefCnt);
	}

	long GetRef()
	{
		return m_nRefCnt;
	}

protected:
	long m_nRefCnt;
};

#define J_Add_Ref(impl) impl->IncRef();
#define J_Release(impl)\
		if (impl->GetRef() > 1)\
			impl->DecRef();\
		else\
			delete impl;

template <typename CBase>
class J_BaseVideoStream : public CBase
{
protected:
	J_BaseVideoStream() {}
	~J_BaseVideoStream() {}

public:
	int AddRingBuffer(CRingBuffer *pRingBuffer)
	{
		TLock(m_vecLocker);
		m_vecRingBuffer.push_back(pRingBuffer);
		TUnlock(m_vecLocker);

		return J_OK;
	}

	int DelRingBuffer(CRingBuffer *pRingBuffer)
	{
		TLock(m_vecLocker);
		std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
		for (; it != m_vecRingBuffer.end(); it++)
		{
			if (*it == pRingBuffer)
			{
				m_vecRingBuffer.erase(it);
				TUnlock(m_vecLocker);

				return J_OK;
			}
		}
		TUnlock(m_vecLocker);
		return J_NOT_EXIST;
	}

	int RingBufferCount()
	{
		TLock(m_vecLocker);
		int count = m_vecRingBuffer.size();
		TUnlock(m_vecLocker);

		return  count;
	}

public:
	J_OS::TLocker_t m_vecLocker;
	std::vector<CRingBuffer *> m_vecRingBuffer;
};

#endif //~__J_OBJ_H_
