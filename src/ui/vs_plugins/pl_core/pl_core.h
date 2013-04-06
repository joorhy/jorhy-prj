#pragma once
#include "Windows.h"

// {00000000-0000-0000-0000-000000000000}
static const GUID JO_INVALID_GUID =
{ 0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };

typedef INT (*JoFMaker)(void);

/// 构造器登记项
struct JoMakerEntry
{
	enum
	{
		FLAG_REGISTERED				=(1<<0),
		FLAG_UINT64_DATA				=(1<<1),
		FLAG_TSTRING_DATA			=(1<<2),
		FLAG_GUID_DATA					=(1<<3),
		FLAG_STREAM_TYPE_DATA	=(1<<4),
	};

	const GUID* clsid; ///< 构造器构造的对象类CLSID
	INT retcode;  ///< 注册该entry时的返回值(RMIP值)（对于CLSID==IID_POMODULE_INIT，是相应初始化函数的返回值)
	JoFMaker fMaker; ///< 非最后一项时是构造器函数, 最后一项时指向下个登记簿

	/// 非最后一项时是选项(参见FLAG_xxx枚举)
	/// - 第0位: 1-已经注册, 0-尚未注册
	/// - 第1位: 1-data实际是UINT64类型, 0-不是
	/// - 第2位: 1-data实际是const TCHAR*类型, 0-不是
	/// - 第3位: 1-data实际是const GUID*类型, 0-不是
	/// - 第4位: 1-data实际是PoStreamType类型, 0-不是
	/// - 其它位保留
	DWORD flags;

	UINT64 data; ///< 根据clsid有不同的意思
	const DWORD* subclasses; ///< 所属子分类, 由一组DWORD的FourCC码组成, 以0结束; 最后一项时是部件名称
};

template<typename InT>
inline JoFMaker JoMakerCast(InT t) { return reinterpret_cast<JoFMaker>(t); }

template<typename InT>
inline UINT64 JoMakerDataCast(InT t) { return reinterpret_cast<UINT64>(t); }

/// 登记基于const TCHAR*索引的构造器
/// @param[in] clsid 类的CLSID
/// @param[in] MakerT 构造器的类型
/// @param[in] maker 构造器
/// @param[in] tstringKey 索引关键字
/// @param[in] subclasses 子分类(可以为NULL)
#define JO_ENTRY_BY_TSTRING(clsid, MakerT, maker, tstringKey, subclasses) \
{ clsid, 0,JoMakerCast<MakerT>(maker), JoMakerEntry::FLAG_TSTRING_DATA, JoMakerDataCast<const TCHAR*>(tstringKey), (subclasses) },

/// 开始各种构造器的登记簿
#define JO_BEGIN_MAKER() \
	static JoMakerEntry s_joMakers[] = {

/// Host构造器.
/// @param[in] iid 对象接口IID
/// @param[out] pObj 构造好的对象
/// @param[in] hostUrl Host的url
/// @return 0-成功, <0-RMIP出错码
typedef INT (*JoFMakeHost)(const GUID& iid, void*& pObj, const TCHAR* hostUrl);

/// 登记Host
/// @param[in] prefix url前缀(NULL表示支持任意前缀)
/// @param[in] maker Host的构造器
/// @param[in] subclasses 子分类(可以为NULL)
#define JO_ENTRY_HOST(prefix, maker, subclasses) \
	JO_ENTRY_BY_TSTRING(&CLSID_JoHost, JoFMakeHost, (maker), (prefix), (subclasses))

/// 结束各种构造器的登记簿
/// @param[in] partName 部件名(一般就是不带全路径和扩展名的文件名)
#define JO_END_MAKER(partName) \
{ &JO_INVALID_GUID, 0,NULL, 0, 0, (const DWORD*)partName }	\
};											\
static INT s_jo_dummy_init = JO_LINK_MODULE_MAKERS(s_poMakers);