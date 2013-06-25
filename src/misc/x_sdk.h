#ifndef _X_SDK_H_
#define _X_SDK_H_
#include "json.h"
#include "x_sdk_def.h"
#include "j_includes.h"

JO_API char *HttpCommunicate(char *body,char *uri);
JO_API r_register *StreamServerResgister(int id,char *uri);
JO_API r_devconfig *GetDevConfigByResid(char *resid,char *uri);
JO_API r_ssconfig *GetSSConfigByResid(char *resid,char *uri);
JO_API int GetRealTimePermission(char *resid,char *uid,char *uri);
JO_API r_historyfile *GetHistoryFile(char *resid,char *uid,time_t stime,time_t etime,char *uri);
JO_API int GetWarningMsg(char *resid,int type,char *uri);
JO_API int GetRecordNotice(s_record &record,char *uri);
#endif //~_X_SDK_H_
