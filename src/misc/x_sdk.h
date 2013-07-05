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

	char *HttpCommunicate(char *body,char *uri);
	r_register *StreamServerResgister(int id,char *uri);
	r_devconfig *GetDevConfigByResid(char *resid,char *uri);
	r_ssconfig *GetSSConfigByResid(char *resid,char *uri);
	int GetRealTimePermission(char *resid,char *uid,char *uri);
	r_historyfile *GetHistoryFile(char *resid,char *uid,time_t stime,time_t etime,char *uri);
	int GetWarningMsg(char *resid,int type,char *uri);
	int GetRecordNotice(s_record &record,char *uri);

private:
	int get_int(json_object *p_object, const char *p_key);
	char *get_string(json_object *p_object, const char *p_key);
	json_object *get_object(json_object *p_object, const char *p_key);

private:
	CXHttp m_httpHelper;
};

JO_DECLARE_SINGLETON(XSdk)

#endif //~_X_SDK_H_
