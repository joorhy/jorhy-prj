#ifndef _X_SDK_H_
#define _X_SDK_H_
#include "j_includes.h"
#include "json.h"
#include "x_sdk_def.h"
/*
 * describe:通过HTTP协议与服务器通信，通过post方法 ,返回值需要释放（delete）string
 *arguments:
 *			body: 加在body里面要发送的字符窜
 *			uri:通讯的地址
 *return: 服务器返回的消息里面的body部分
 */
char
*HttpCommunicate(char *body,char *uri);


/*
 *describe:流媒体服务器注册,返回值需要释放（delete）string
 *arguments:
 *			id:服务器端的标示id编号
 *			uri:通讯的地址 eg:http://192.168.1.10:8080/controller/request
 *return:设备信息
*/
r_register
*StreamServerResgister(int id,char *uri);


/*
 *describe:获取设备的配置信息，返回值需要释放（delete）string）
 *arguments:
 *			resid:资源唯一编码
 *			uri:通讯的地址
 *return:配置信息
 */
r_devconfig
*GetDevConfigByResid(char *resid,char *uri);

/*
 *describe:获取SS的配置信息，返回值需要释放（delete）string）
 *arguments:
 *			resid:资源唯一编码
 *			uri:通讯的地址
 *return:配置信息
 */
r_ssconfig
*GetSSConfigByResid(char *resid,char *uri);

/*
 *describe:获取实时点播权
 *arguments:
 *			resid:
 *			uid:
 *			uri:通讯的地址
 *return:是否获取点播权
 */
int
GetRealTimePermission(char *resid,char *uid,char *uri);


/*
 *describe:查询历史文件，返回值需要释放（delete）string
 *arguments:
 *			resid:
 *			uid:
 *			stime:开始时间
 *			etime:结束时间
 *			uri:通讯地址
 *return:历史文件信息
 */
r_historyfile
*GetHistoryFile(char *resid,char *uid,time_t stime,time_t etime,char *uri);


/*
 *describe:获取警告信息
 *arguments:
 *			resid:
 *			type:告警信息
 *			uri:通讯地址
 *return:是否成功
 */
int
GetWarningMsg(char *resid,int type,char *uri);


/*
 *describe:录像通知
 *arguments:
 *			record:录像的详细信息
 *			uri:通讯地址
 *return:是否成功
 */
int
GetRecordNotice(s_record &record,char *uri);



#endif //~_X_SDK_H_
