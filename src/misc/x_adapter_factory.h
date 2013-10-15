#ifndef __ADAPTERFACTORY_H_
#define __ADAPTERFACTORY_H_
#include "j_includes.h"
#include "x_singleton.h"
#include "x_timer.h"

typedef int (*J_MakeAdapterFun)(J_Obj *&, int, const char *, int, const char *, const char *);

class JO_API CAdapterFactory 
{
	typedef std::map<j_string_t, J_MakeAdapterFun> AdapterRegistMap;
	typedef std::map<j_string_t, J_Obj*> AdapterMap;				//存放所有DVR设备的对象
	typedef std::map<J_ChannelKey, J_Obj*> ChannelMap;			//存放所有Channel的对象

public:
	CAdapterFactory();
	~CAdapterFactory();

public:
	///注册Adapter类
	///@param[in] 	adapterType adapter 类型 1-海康,2-大华
	///@param[in] 	J_MakeAdapterFun Adapter的构造函数
	///@return 		参考x_error_type.h
	int RegisterAdapter(const char *adapterType, J_MakeAdapterFun pFun);

	///构造Adapter对象
	///@param[in] 	pResId 全局唯一的资源ID
	///@param[in]	nStreamType 码流类型 0-主码流, 1-子码流
	///@return 		参考x_error_type.h
	J_Obj *FatchAdapter(const char *pResId);

	///获取JoHost Channel对象
	///@param[in] 	pResId 全局唯一的资源ID
	///@param[in]	nStreamType 码流类型 0-主码流, 1-子码流
	///@param[in]	nDevId 设备ID号
	///@return 		NULL-获取失败,需要调用CreateInstence; 非空-对象的地址
	J_Obj *FatchChannel(const char *pResId, int nStreamType, j_int32_t nDevId);

	///构造Channel对象
	///@param[in] 	pResId 全局唯一的资源ID
	///@param[in]	nStreamType 码流类型 0-主码流, 1-子码流
	///@return 		参考x_error_type.h
	j_result_t ReleaseChannel(const char *pResId, int nStreamType);

	///构造设备适配器
	///@param[in]	pDevType 设备类型
	///@param[in]	nDevId 设备ID
	///@param[in]	pDevIp 设备IP
	///@param[in]	nDevPort 设备端口号
	///@param[in]	pUsername 用户名
	///@param[in]	pPasswd 密码
	///@return 		参考x_error_type.h
	j_result_t MakeAdapterDev(const char *pDevType, int nDevId, const char *pDevIp, int nDevPort, const char *pUsername, const char *pPasswd);

private:
	AdapterRegistMap m_adapterRegistMap;
	AdapterMap m_adapterMap;
	ChannelMap m_channelMap;
};
JO_DECLARE_SINGLETON(AdapterFactory)

#endif //~__ADAPTERFACTORY_H_
