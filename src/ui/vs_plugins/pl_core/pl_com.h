#pragma once
#include "pl_core.h"

struct JoInterfaceEntry
{
	const GUID* piid;
	DWORD dw;

	typedef INT (*JoFQueryInterface)(void* pv, const GUID& guid, void*& pObj, DWORD dw);
	JoFQueryInterface pFunc; // NULL-登记簿结束, 1-offset, 其它-函数指针
};
extern "C" PL_API INT JoQueryInterface(void* pThis, const JoInterfaceEntry* entries, const GUID& iid, void*& pObj);

// 简单对象
#define _JO_SIMPLEMAPENTRY ((JoInterfaceEntry::JoFQueryInterface)1)

// 计算偏移量
#define JO_OFFSET_OF_CLASS(base, derived)	 ((DWORD)(static_cast<base*>((derived*)8))-8)

#define _JO_RETURN_QI_ENTRY()	return _entries

/// 开始各种接口的登记簿
/// @param[in] x 类名
#define JO_INTERFACE_BEGIN(x)								\
	typedef x _class;												\
	static const JoInterfaceEntry* _GetEntries(){					\
	static const JoInterfaceEntry _entries[] = {				\

/// 登记接口
/// @param[in] iclass 接口名
#define POSA_SIMPLE_INTERFACE_ENTRY(iclass)							\
{&IID_##iclass, JO_OFFSET_OF_CLASS(iclass, _class), _JO_SIMPLEMAPENTRY },

/// 结束各种接口的登记簿
#define JO_INTERFACE_END()										\
{ NULL, 0, NULL }										\
};															\
	_JO_RETURN_QI_ENTRY();									\
}																\
	virtual INT QueryInterface(const GUID& iid, void*& pObj)		\
{ return JoQueryInterface(this, _GetEntries(), iid, pObj); }