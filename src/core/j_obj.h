#ifndef __J_OBJ_H_
#define __J_OBJ_H_
#include "j_common.h"

struct J_Obj
{
	virtual ~J_Obj() {}
};

///原子操作 long型数据
inline long atomic_inc(long volatile *v)
{
#ifdef WIN32
	InterlockedExchangeAdd(v, 1);
#else
	__asm__ __volatile__("lock incl %0" : "+m"(*v));
#endif
	return *v;
}

inline long atomic_dec(long volatile *v)
{
#ifdef WIN32
	InterlockedExchangeAdd(v, -1);
#else
	__asm__ __volatile__("lock decl %0" : "+m"(*v));
#endif
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

#endif //~__J_OBJ_H_
