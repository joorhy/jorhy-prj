#ifndef _X_SDK_H_
#define _X_SDK_H_
#include "json.h"
#include "x_sdk_def.h"
#include "j_includes.h"
#include "x_http.h"
#include "x_lock.h"

class JO_API CXSdk
{
public:
	CXSdk() {}
	~CXSdk() {}

public:
	///µÇÂ¼¹ÜÀí·þÎñÆ÷
	///@param[in]		nId Ã½ÌåÉè±¸ID
	///@param[in]		pUrl ¹ÜÀí·þÎñÆ÷URL
	///@param[out]	resInfo ×ÊÔ´ÐÅÏ¢
	///@return			²Î¼ûj_errtype.h
	j_result_t Login(j_int32_t nId, j_char_t *pUrl, ResourceMap &resInfo);
	///»ñÈ¡×ÊÔ´ÐÅÏ¢
	///@param[in]		pResid ×ÊÔ´ID
	///@param[in]		pUrl ¹ÜÀí·þÎñÆ÷URL
	///@param[out]	resInfo ×ÊÔ´ÐÅÏ¢
	///@return			²Î¼ûj_errtype.h
	j_result_t GetResourceInfo(j_char_t *pResid, j_char_t *pUrl, J_ResourceInfo &resInfo);
	///»ñÈ¡Á÷Ã½Ìå·þÎñÆ÷ÐÅÏ¢
	///@param[in]		pResid ×ÊÔ´ID
	///@param[in]		pUrl ¹ÜÀí·þÎñÆ÷URL
	///@param[out]	ssInfo Á÷Ã½Ìå·þÎñÆ÷ÐÅÏ¢
	///@return			²Î¼ûj_errtype.h
	j_result_t GetStreamServerInfo(j_char_t *pResid, j_char_t *pUrl, J_StreamServerInfo &ssInfo);
	///·¢ËÍ±£»îÃüÁî
	///@param[in]		nStreamServerId Á÷Ã½Ìå·þÎñÆ÷ID
	///@param[in]		pUrl ¹ÜÀí·þÎñÆ÷URL
	///@return			²Î¼ûj_errtype.h
	j_result_t KeepAlive(j_int32_t nStreamServerId, j_char_t *pUrl);

	///½âÎöÂ¼Ïñ¿ØÖÆÏûÏ¢
	///@param[in]		pJsonStr JsonÃüÁî²ÎÊý×Ö·û´®
	///@param[out]	ctrlObj ½âÎö½á¹û
	///@return			²Î¼ûj_errtype.h
	j_result_t ParserRecordCtrl(const char *pJsonStr, J_ControlObj &ctrlObj);

	///通知告警消息
	///@prarm[in]		alarmData告警数据
	///@param[in]		pUrl ¹ÜÀí·þÎñÆ÷URL
	///@return			参见j_errtype.h
	j_result_t NotifyAlarmInfo(const J_AlarmData &alarmData, j_char_t *pUrl);

private:
	char *HttpCommunicate(char *body,char *uri);
	int JsonGetInt(json_object *p_object, const char *p_key);
	char *JsonGetString(json_object *p_object, const char *p_key);
	json_object *JsonGetObj(json_object *p_object, const char *p_key);

private:
	J_OS::CTLock m_locker;
	CXHttp m_httpHelper;
};

JO_DECLARE_SINGLETON(XSdk)

#endif //~_X_SDK_H_
