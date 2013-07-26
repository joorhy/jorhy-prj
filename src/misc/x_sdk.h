#ifndef _X_SDK_H_
#define _X_SDK_H_
#include "json.h"
#include "x_sdk_def.h"
#include "j_includes.h"
#include "x_http.h"

class JO_API CXSdk
{
public:
	CXSdk() {}
	~CXSdk() {}

public:
	///登录管理服务器
	///@param[in]		nId 媒体设备ID
	///@param[in]		pUrl 管理服务器URL
	///@param[out]	resInfo 资源信息
	///@return			参见j_errtype.h
	j_result_t Login(j_int32_t nId, j_char_t *pUrl, ResourceMap &resInfo);
	///获取资源信息
	///@param[in]		pResid 资源ID
	///@param[in]		pUrl 管理服务器URL
	///@param[out]	resInfo 资源信息
	///@return			参见j_errtype.h
	j_result_t GetResourceInfo(j_char_t *pResid, j_char_t *pUrl, J_ResourceInfo &resInfo);
	///获取流媒体服务器信息
	///@param[in]		pResid 资源ID
	///@param[in]		pUrl 管理服务器URL
	///@param[out]	ssInfo 流媒体服务器信息
	///@return			参见j_errtype.h
	j_result_t GetStreamServerInfo(j_char_t *pResid, j_char_t *pUrl, J_StreamServerInfo &ssInfo);
	///发送保活命令
	///@param[in]		nStreamServerId 流媒体服务器ID
	///@param[in]		pUrl 管理服务器URL
	///@return			参见j_errtype.h
	j_result_t KeepAlive(j_int32_t nStreamServerId, j_char_t *pUrl);

	///解析录像控制消息
	///@param[in]		pJsonStr Json命令参数字符串
	///@param[out]	ctrlObj 解析结果
	///@return			参见j_errtype.h
	j_result_t ParserRecordCtrl(const char *pJsonStr, J_ControlObj &ctrlObj);

private:
	char *HttpCommunicate(char *body,char *uri);
	int JsonGetInt(json_object *p_object, const char *p_key);
	char *JsonGetString(json_object *p_object, const char *p_key);
	json_object *JsonGetObj(json_object *p_object, const char *p_key);

private:
	CXHttp m_httpHelper;
};

JO_DECLARE_SINGLETON(XSdk)

#endif //~_X_SDK_H_
