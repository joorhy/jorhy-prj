#ifndef __ADAPTERFACTORY_H_
#define __ADAPTERFACTORY_H_
#include "j_includes.h"
#include "x_singleton.h"
#include "x_timer.h"

typedef int (*J_MakeAdapterFun)(J_Obj *&, int, const char *, int, const char *, const char *);

enum OBJ_TYPE
{
	OBJ_INIT = 0,		//初始化全部设备
	OBJ_ADAPTER,
	OBJ_CHANNEL
};

class JO_API CAdapterFactory 
{
	typedef std::map<j_string_t, J_MakeAdapterFun> AdapterRegistMap;
	typedef std::map<j_string_t, J_Obj*> AdapterMap;				//存放所有DVR设备的对象
	typedef std::map<J_ChannelKey, void*> ChannelMap;			//存放所有Channel的对象

public:
	CAdapterFactory();
	~CAdapterFactory();

public:
	///注册Adapter类
	///@param[in] 	adapterType adapter 类型 1-海康,2-大华
	///@param[in] 	J_MakeAdapterFun Adapter的构造函数
	///@return 		参考x_error_type.h
	int RegisterAdapter(const char *adapterType, J_MakeAdapterFun pFun);

	///构造Adapter和channel对象
	///@param[in] 	pResId 全局唯一的资源ID
	///@param[in]	nStreamType 码流类型 0-主码流, 1-子码流
	///@param[in] 	nType 操作类型 0-初始化全部Adapter, 1-构造Adapter, 2-构造Channel
	///@return 		参考x_error_type.h
	void *CreateInstance(const char *pResId, int nStreamType, OBJ_TYPE nType);

	///获取Adapter和channel对象
	///@param[in] 	pResId 全局唯一的资源ID
	///@param[in] 	nType 对象类型 1-Adapter, 2-Channel
	///@param[in]	nStreamType 码流类型 0-主码流, 1-子码流
	///@return 		NULL-获取失败,需要调用CreateInstence; 非空-对象的地址
	void *GetInstance(const char *pResId, OBJ_TYPE nType, int nStreamType);

	///构造Adapter和channel对象
	///@param[in] 	pResId 全局唯一的资源ID
	///@param[in]	nStreamType 码流类型 0-主码流, 1-子码流
	///@param[in] 	nType 操作类型 1-析构Adapter, 2-析构Channel
	///@return 		参考x_error_type.h
	int RemoveInstance(const char *pResId, OBJ_TYPE nType, int nStreamType);

private:
	static void TimerThread(void *pUser)
	{
		CAdapterFactory *pThis = static_cast<CAdapterFactory *>(pUser);
		if (pThis != NULL)
			pThis->OnTimer();
	}
	void OnTimer();

private:
	AdapterRegistMap m_adapterRegistMap;
	AdapterMap m_adapterMap;
	ChannelMap m_channelMap;

	J_OS::CTimer m_timer;
	typedef std::map<std::string, J_DeviceInfo> DeviceMap;
	DeviceMap m_devMap;
	bool m_bRegiste;
};
#endif //~__ADAPTERFACTORY_H_
