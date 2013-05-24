#ifndef _X_SDK_H_
#define _X_SDK_H_
#include "json.h"
#include "x_sdk_def.h"
#include "j_includes.h"

char *HttpCommunicate(char *body,char *uri);
r_register *StreamServerResgister(int id,char *uri);
r_devconfig *GetDevConfigByResid(char *resid,char *uri);
r_ssconfig *GetSSConfigByResid(char *resid,char *uri);
int GetRealTimePermission(char *resid,char *uid,char *uri);
r_historyfile *GetHistoryFile(char *resid,char *uid,time_t stime,time_t etime,char *uri);
int GetWarningMsg(char *resid,int type,char *uri);
int GetRecordNotice(s_record &record,char *uri);
#endif //~_X_SDK_H_
