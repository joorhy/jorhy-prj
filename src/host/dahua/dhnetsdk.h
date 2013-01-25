
#ifndef DHNETSDK_H
#define DHNETSDK_H


#ifdef WIN32

#ifdef DHNETSDK_EXPORTS
#define CLIENT_API  __declspec(dllexport) 
#else
#define CLIENT_API  __declspec(dllimport)
#endif

#define CALLBACK __stdcall
#define CALL_METHOD  __stdcall  //__cdecl

#else	//linux

#define CLIENT_API	extern "C"
#define CALL_METHOD
#define CALLBACK

#define WORD	unsigned short
#define DWORD	unsigned long
#define LPDWORD	DWORD*
#define BOOL	int
#define TRUE	1
#define FALSE	0
#define BYTE	unsigned char
#define LONG	long
#define UINT	unsigned int
#define HDC		void*
#define HWND	void*
#define LPVOID	void*
#define NULL	0
typedef struct  tagRECT
{
     LONG left;
     LONG top;
     LONG right;
     LONG bottom;
} RECT;


#endif

#include "dhassistant.h"


#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 ** 常量定义
 ***********************************************************************/
#define DH_SERIALNO_LEN 			48			// 设备序列号字符长度
#define DH_MAX_DISKNUM 				256			// 最大硬盘个数
#define DH_MAX_SDCARDNUM			32			// 最大SD卡个数
#define DH_MAX_BURNING_DEV_NUM		32			// 最大刻录设备个数
#define DH_BURNING_DEV_NAMELEN		32			// 刻录设备名字最大长度
#define DH_MAX_LINK 				6
#define DH_MAX_CHANNUM 				16			// 最大通道个数
#define DH_MAX_ALARMIN 				128			// 最大报警输入个数
#define DH_MAX_ALARMOUT 			64			// 最大报警输出个数
#define DH_MAX_RIGHT_NUM			100			// 用户权限个数上限
#define DH_MAX_GROUP_NUM			20			// 用户组个数上限
#define DH_MAX_USER_NUM				200			// 用户个数上限
#define DH_RIGHT_NAME_LENGTH		32			// 权限名长度
#define DH_USER_NAME_LENGTH			8			// 用户名长度
#define DH_USER_PSW_LENGTH			8			// 用户密码长度
#define DH_MEMO_LENGTH				32			// 备注长度
#define DH_MAX_STRING_LEN			128
#define DH_DVR_SERIAL_RETURN		1			// 设备发送序列号回调
#define DH_DVR_DISCONNECT			-1			// 验证期间设备断线回调
#define MAX_STRING_LINE_LEN			6			// 最多六行
#define MAX_PER_STRING_LEN			20			// 每行最大长度
#define DH_MAX_MAIL_NAME_LEN		64			// 新的邮件结构体支持的用户名长度
#define DH_MAX_MAIL_PSW_LEN			64			// 新的邮件结构体支持的密码长度

// 远程配置结构体相关常量
#define DH_MAX_MAIL_ADDR_LEN		128			// 邮件发(收)地址最大长度
#define DH_MAX_MAIL_SUBJECT_LEN		64			// 邮件主题最大长度
#define DH_MAX_IPADDR_LEN			16			// IP地址字符串长度
#define DH_MACADDR_LEN				40			// MAC地址字符串长度
#define DH_MAX_URL_LEN				128			// URL字符串长度
#define DH_MAX_DEV_ID_LEN			48			// 机器编号最大长度
#define	DH_MAX_HOST_NAMELEN			64			// 主机名长度，
#define DH_MAX_HOST_PSWLEN			32			// 密码长度
#define DH_MAX_NAME_LEN				16			// 通用名字字符串长度
#define DH_MAX_ETHERNET_NUM			2			// 以太网口最大个数
#define	DH_DEV_SERIALNO_LEN			48			// 序列号字符串长度
#define DH_DEV_TYPE_LEN				32			// 设备类型字符串长度
#define DH_N_WEEKS					7			// 一周的天数	
#define DH_N_TSECT					6			// 通用时间段个数
#define DH_N_REC_TSECT				6			// 录像时间段个数
#define DH_N_COL_TSECT				2			// 颜色时间段个数	
#define DH_CHAN_NAME_LEN			32			// 通道名长度，DVR DSP能力限制，最多32字节		
#define DH_N_ENCODE_AUX				3			// 扩展码流个数	
#define DH_N_TALK					1			// 最多对讲通道个数
#define DH_N_COVERS					1			// 遮挡区域个数	
#define DH_N_CHANNEL				16			// 最大通道个数	
#define DH_N_ALARM_TSECT			2			// 报警提示时间段个数
#define DH_MAX_ALARMOUT_NUM			16			// 报警输出口个数上限
#define DH_MAX_AUDIO_IN_NUM			16			// 音频输入口个数上限
#define DH_MAX_VIDEO_IN_NUM			16			// 视频输入口个数上限
#define DH_MAX_ALARM_IN_NUM			16			// 报警输入口个数上限
#define DH_MAX_DISK_NUM				16			// 硬盘个数上限，暂定为16
#define DH_MAX_DECODER_NUM			16			// 解码器(485)个数上限	
#define DH_MAX_232FUNCS				10			// 232串口功能个数上限
#define DH_MAX_232_NUM				2			// 232串口个数上限
#define DH_MAX_DECPRO_LIST_SIZE		100			// 解码器协议列表个数上限
#define DH_FTP_MAXDIRLEN			240			// FTP文件目录最大长度
#define DH_MATRIX_MAXOUT			16			// 矩阵输出口最大个数
#define DH_TOUR_GROUP_NUM			6			// 矩阵输出组最大个数
#define DH_MAX_DDNS_NUM				10			// 设备支持的ddns服务器最大个数
#define DH_MAX_SERVER_TYPE_LEN		32			// ddns服务器类型，最大字符串长度
#define DH_MAX_DOMAIN_NAME_LEN		256			// ddns域名，最大字符串长度
#define DH_MAX_DDNS_ALIAS_LEN		32			// ddns服务器别名，最大字符串长度
#define DH_MOTION_ROW				32			// 动态检测区域的行数
#define DH_MOTION_COL				32			// 动态检测区域的列数
#define DH_STATIC_ROW				32			// 静态检测区域的行数
#define DH_STATIC_COL			    32			// 静态检测区域的列数
#define	DH_FTP_USERNAME_LEN			64			// FTP配置，用户名最大长度
#define	DH_FTP_PASSWORD_LEN			64			// FTP配置，密码最大长度
#define	DH_TIME_SECTION				2			// FTP配置，每天时间段个数
#define DH_FTP_MAX_PATH				240			// FTP配置，文件路径名最大长度
#define DH_INTERVIDEO_UCOM_CHANID	32			// 平台接入配置，U网通通道ID
#define DH_INTERVIDEO_UCOM_DEVID	32			// 平台接入配置，U网通设备ID
#define DH_INTERVIDEO_UCOM_REGPSW	16			// 平台接入配置，U网通注册密码
#define DH_INTERVIDEO_UCOM_USERNAME	32			// 平台接入配置，U网通用户名
#define DH_INTERVIDEO_UCOM_USERPSW	32			// 平台接入配置，U网通密码
#define DH_INTERVIDEO_NSS_IP		32			// 平台接入配置，中兴力维IP
#define DH_INTERVIDEO_NSS_SERIAL	32			// 平台接入配置，中兴力维serial
#define DH_INTERVIDEO_NSS_USER		32			// 平台接入配置，中兴力维user
#define DH_INTERVIDEO_NSS_PWD		50			// 平台接入配置，中兴力维password
#define DH_MAX_VIDEO_COVER_NUM		16			// 遮挡区域最大个数
#define DH_MAX_WATERMAKE_DATA		4096		// 水印图片数据最大长度
#define DH_MAX_WATERMAKE_LETTER		128			// 水印文字最大长度
#define DH_MAX_WLANDEVICE_NUM		10			// 最多搜索出的无线设备个数
#define DH_MAX_ALARM_NAME			64			// 地址长度
#define DH_MAX_REGISTER_SERVER_NUM	10			// 主动注册服务器个数
#define DH_SNIFFER_FRAMEID_NUM		6			// 6个FRAME ID 选项
#define DH_SNIFFER_CONTENT_NUM		4			// 每个FRAME对应的4个抓包内容
#define DH_SNIFFER_CONTENT_NUM_EX	8			// 每个FRAME对应的8个抓包内容
#define DH_SNIFFER_PROTOCOL_SIZE	20			// 协议名字长度
#define DH_MAX_PROTOCOL_NAME_LENGTH 20
#define DH_SNIFFER_GROUP_NUM		4			// 4组抓包设置
#define MAX_PATH_STOR				240			// 远程目录的长度
#define DH_ALARM_OCCUR_TIME_LEN		40			// 新的报警上传时间的长度
#define DH_VIDEO_OSD_NAME_NUM		64			// 叠加的名称长度，目前支持32个英文，16个中文
#define DH_VIDEO_CUSTOM_OSD_NUM		8			// 支持的自定义叠加的数目，不包含时间和通道
#define DH_CONTROL_AUTO_REGISTER_NUM 100        // 支持定向主动注册服务器的个数
#define DH_MMS_RECEIVER_NUM          100        // 支持短信接收者的个数
#define DH_MMS_SMSACTIVATION_NUM     100        // 支持短信发送者的个数
#define DH_MMS_DIALINACTIVATION_NUM  100        // 支持拨号发送者的个数
#define DH_MAX_ALARMOUT_NUM_EX		 32			// 报警输出口个数上限扩展
#define DH_MAX_VIDEO_IN_NUM_EX		 32			// 视频输入口个数上限扩展
#define DH_MAX_ALARM_IN_NUM_EX		 32			// 报警输入口个数上限
#define DH_MAX_IPADDR_OR_DOMAIN_LEN	 64			// IP地址字符串长度
#define MAX_OBJECT_LIST				 16			// 智能分析设备检测到的物体ID个数上限	
#define MAX_RULE_LIST				 16			// 智能分析设备规则个数上限
#define MAX_POLYGON_NUM				 16			// 多边形最大顶点个数

	
// 查询类型，对应CLIENT_QueryDevState接口
#define DH_DEVSTATE_COMM_ALARM		0x0001		// 查询普通报警状态(包括外部报警，视频丢失，动态检测)
#define DH_DEVSTATE_SHELTER_ALARM	0x0002		// 查询遮挡报警状态
#define DH_DEVSTATE_RECORDING		0x0003		// 查询录象状态
#define DH_DEVSTATE_DISK			0x0004		// 查询硬盘信息
#define DH_DEVSTATE_RESOURCE		0x0005		// 查询系统资源状态
#define DH_DEVSTATE_BITRATE			0x0006		// 查询通道码流
#define DH_DEVSTATE_CONN			0x0007		// 查询设备连接状态
#define DH_DEVSTATE_PROTOCAL_VER	0x0008		// 查询网络协议版本号，pBuf = int*
#define DH_DEVSTATE_TALK_ECTYPE		0x0009		// 查询设备支持的语音对讲格式列表，见结构体DHDEV_TALKFORMAT_LIST
#define DH_DEVSTATE_SD_CARD			0x000A		// 查询SD卡信息(IPC类产品)
#define DH_DEVSTATE_BURNING_DEV		0x000B		// 查询刻录机信息
#define DH_DEVSTATE_BURNING_PROGRESS 0x000C		// 查询刻录进度
#define DH_DEVSTATE_PLATFORM		0x000D		// 查询设备支持的接入平台
#define DH_DEVSTATE_CAMERA			0x000E		// 查询摄像头属性信息(IPC类产品)，pBuf = DHDEV_CAMERA_INFO *，可以有多个结构体
#define DH_DEVSTATE_SOFTWARE		0x000F		// 查询设备软件版本信息
#define DH_DEVSTATE_LANGUAGE        0x0010		// 查询设备支持的语音种类
#define DH_DEVSTATE_DSP				0x0011		// 查询DSP能力描述
#define	DH_DEVSTATE_OEM				0x0012		// 查询OEM信息
#define	DH_DEVSTATE_NET				0x0013		// 查询网络运行状态信息
#define DH_DEVSTATE_TYPE			0x0014		// 查询设备类型
#define DH_DEVSTATE_SNAP			0x0015		// 查询抓图功能属性(IPC类产品)
#define DH_DEVSTATE_RECORD_TIME		0x0016		// 查询最早录像时间和最近录像时间
#define DH_DEVSTATE_NET_RSSI        0x0017      // 查询无线网络信号强度，见结构体DHDEV_WIRELESS_RSS_INFO
#define DH_DEVSTATE_BURNING_ATTACH	0x0018		// 查询附件刻录选项
#define DH_DEVSTATE_BACKUP_DEV		0x0019		// 查询备份设备列表
#define DH_DEVSTATE_BACKUP_DEV_INFO	0x001a		// 查询备份设备详细信息
#define DH_DEVSTATE_BACKUP_FEEDBACK	0x001b		// 备份进度反馈
#define DH_DEVSTATE_ATM_QUERY_TRADE  0x001c		// 查询ATM交易类型
#define DH_DEVSTATE_SIP				0x001d		// 查询sip状态
#define DH_DEVSTATE_VICHILE_STATE	0x001e		// 查询车载wifi状态

// 配置类型，对应CLIENT_GetDevConfig和CLIENT_SetDevConfig接口
#define DH_DEV_DEVICECFG			0x0001		// 设备属性配置
#define DH_DEV_NETCFG				0x0002		// 网络配置
#define DH_DEV_CHANNELCFG			0x0003		// 图象通道配置
#define DH_DEV_PREVIEWCFG 			0x0004		// 预览参数配置
#define DH_DEV_RECORDCFG			0x0005		// 录像配置
#define DH_DEV_COMMCFG				0x0006		// 串口属性配置
#define DH_DEV_ALARMCFG 			0x0007		// 报警属性配置
#define DH_DEV_TIMECFG 				0x0008		// DVR时间配置
#define DH_DEV_TALKCFG				0x0009		// 对讲参数配置
#define DH_DEV_AUTOMTCFG			0x000A		// 自动维护配置		
#define	DH_DEV_VEDIO_MARTIX			0x000B		// 本机矩阵控制策略配置	
#define DH_DEV_MULTI_DDNS			0x000C		// 多ddns服务器配置
#define DH_DEV_SNAP_CFG				0x000D		// 抓图相关配置
#define DH_DEV_WEB_URL_CFG			0x000E		// HTTP路径配置
#define DH_DEV_FTP_PROTO_CFG		0x000F		// FTP上传配置
#define DH_DEV_INTERVIDEO_CFG		0x0010		// 平台接入配置，此时channel参数代表平台类型，
												// channel=4： 代表贝尔阿尔卡特；channel=10：代表中兴力维；channel=11：代表U网通
#define DH_DEV_VIDEO_COVER			0x0011		// 区域遮挡配置
#define DH_DEV_TRANS_STRATEGY		0x0012		// 传输策略配置，画质优先\流畅性优先
#define DH_DEV_DOWNLOAD_STRATEGY	0x0013		// 录象下载策略配置，高速下载\普通下载
#define DH_DEV_WATERMAKE_CFG		0x0014		// 图象水印配置
#define DH_DEV_WLAN_CFG				0x0015		// 无线网络配置
#define DH_DEV_WLAN_DEVICE_CFG		0x0016		// 搜索无线设备配置
#define DH_DEV_REGISTER_CFG			0x0017		// 主动注册参数配置
#define DH_DEV_CAMERA_CFG			0x0018		// 摄像头属性配置
#define DH_DEV_INFRARED_CFG 		0x0019		// 红外报警配置
#define DH_DEV_SNIFFER_CFG			0x001A		// Sniffer抓包配置
#define DH_DEV_MAIL_CFG				0x001B		// 邮件配置
#define DH_DEV_DNS_CFG				0x001C		// DNS服务器配置
#define DH_DEV_NTP_CFG				0x001D		// NTP配置
#define DH_DEV_AUDIO_DETECT_CFG		0x001E		// 音频检测配置
#define DH_DEV_STORAGE_STATION_CFG  0x001F      // 存储位置配置
#define DH_DEV_PTZ_OPT_CFG			0x0020		// 云台操作属性(已经废除，请使用CLIENT_GetPtzOptAttr获取云台操作属性)
#define DH_DEV_DST_CFG				0x0021      // 夏令时配置
#define DH_DEV_ALARM_CENTER_CFG		0x0022		// 报警中心配置
#define DH_DEV_VIDEO_OSD_CFG        0x0023		// 视频OSD叠加配置
#define DH_DEV_CDMAGPRS_CFG         0x0024		// CDMA\GPRS网络配置
#define DH_DEV_IPFILTER_CFG         0x0025		// IP过滤配置
#define DH_DEV_TALK_ENCODE_CFG      0x0026      // 语音对讲编码配置
#define DH_DEV_RECORD_PACKET_CFG    0X0027      // 录像打包长度配置
#define DH_DEV_MMS_CFG              0X0028		// 短信MMS配置 
#define DH_DEV_SMSACTIVATION_CFG	0X0029		// 短信激活无线连接配置
#define DH_DEV_DIALINACTIVATION_CFG	0X002A		// 拨号激活无线连接配置
#define DH_DEV_FILETRANS_STOP		0x002B		// 停止文件上传
#define DH_DEV_FILETRANS_BURN		0x002C		// 刻录文件上传
#define DH_DEV_SNIFFER_CFG_EX		0x0030		// 网络抓包配置
#define DH_DEV_DOWNLOAD_RATE_CFG	0x0031		// 下载速度限制
#define DH_DEV_PANORAMA_SWITCH_CFG	0x0032		// 全景切换报警配置
#define DH_DEV_LOST_FOCUS_CFG		0x0033		// 失去焦点报警配置
#define DH_DEV_ALARM_DECODE_CFG		0x0034		// 报警解码器配置
#define DH_DEV_VIDEOOUT_CFG         0x0035      // 视频输出参数配置
#define DH_DEV_POINT_CFG			0x0036		// 预制点使能配置
#define DH_DEV_IP_COLLISION_CFG     0x0037      // Ip冲突检测报警配置
#define DH_DEV_OSD_ENABLE_CFG		0x0038		// OSD叠加使能配置
#define DH_DEV_LOCALALARM_CFG 		0x0039		// 本地报警配置(结构体DH_ALARMIN_CFG_EX)
#define DH_DEV_NETALARM_CFG 		0x003A		// 网络报警配置(结构体DH_ALARMIN_CFG_EX)
#define DH_DEV_MOTIONALARM_CFG 		0x003B		// 动检报警配置(结构体DH_MOTION_DETECT_CFG_EX)
#define DH_DEV_VIDEOLOSTALARM_CFG 	0x003C		// 视频丢失报警配置(结构体DH_VIDEO_LOST_CFG_EX)
#define DH_DEV_BLINDALARM_CFG 		0x003D		// 视频遮挡报警配置(结构体DH_BLIND_CFG_EX)
#define DH_DEV_DISKALARM_CFG 		0x003E		// 硬盘报警配置(结构体DH_DISK_ALARM_CFG_EX)
#define DH_DEV_NETBROKENALARM_CFG 	0x003F		// 网络中断报警配置(结构体DH_NETBROKEN_ALARM_CFG_EX)
#define DH_DEV_ENCODER_CFG          0x0040      // 数字通道的前端编码器信息（混合DVR使用，结构体DEV_ENCODER_CFG）
#define DH_DEV_TV_ADJUST_CFG        0x0041      // TV调节配置（channel代表TV号(0开始)，类型结构体）
#define DH_DEV_ABOUT_VEHICLE_CFG	0x0042		// 车载相关配置，北京公交使用
#define DH_DEV_ATM_OVERLAY_ABILITY	0x0043		// 获取atm叠加支持能力信息
#define DH_DEV_ATM_OVERLAY_CFG		0x0044		// atm叠加配置，新atm特有
#define DH_DEV_DECODER_TOUR_CFG		0x0045		// 解码器解码轮巡配置
#define DH_DEV_SIP_CFG				0x0046		// SIP配置
#define DH_DEV_VICHILE_WIFI_AP_CFG	0x0047		// wifi ap配置
#define DH_DEV_STATICALARM_CFG      0X0048      // 静态报警配置 

#define DH_DEV_USER_END_CFG			1000

// 报警类型，对应CLIENT_StartListen接口
#define DH_COMM_ALARM				0x1100		// 常规报警(包括外部报警，视频丢失，动态检测)
#define DH_SHELTER_ALARM			0x1101		// 视频遮挡报警
#define DH_DISK_FULL_ALARM			0x1102		// 硬盘满报警
#define DH_DISK_ERROR_ALARM			0x1103		// 硬盘故障报警
#define DH_SOUND_DETECT_ALARM		0x1104		// 音频检测报警
#define DH_ALARM_DECODER_ALARM		0x1105		// 报警解码器报警

// 扩展报警类型，对应CLIENT_StartListenEx接口
#define DH_ALARM_ALARM_EX			0x2101		// 外部报警
#define DH_MOTION_ALARM_EX			0x2102		// 动态检测报警
#define DH_VIDEOLOST_ALARM_EX		0x2103		// 视频丢失报警
#define DH_SHELTER_ALARM_EX			0x2104		// 视频遮挡报警
#define DH_SOUND_DETECT_ALARM_EX	0x2105		// 音频检测报警
#define DH_DISKFULL_ALARM_EX		0x2106		// 硬盘满报警
#define DH_DISKERROR_ALARM_EX		0x2107		// 坏硬盘报警
#define DH_ENCODER_ALARM_EX			0x210A		// 编码器报警
#define DH_URGENCY_ALARM_EX			0x210B		// 紧急报警
#define DH_WIRELESS_ALARM_EX		0x210C		// 无线报警
#define DH_NEW_SOUND_DETECT_ALARM_EX 0x210D		// 新音频检测报警，报警信息的结构体见DH_NEW_SOUND_ALARM_STATE；
#define DH_ALARM_DECODER_ALARM_EX	0x210E		// 报警解码器报警
#define DH_DECODER_DECODE_ABILITY	0x210F		// 解码器：解码能力报警
#define DH_FDDI_DECODER_ABILITY		0x2110		// 光纤编码器状态报警
#define DH_PANORAMA_SWITCH_ALARM_EX	0x2111		// 切换场景报警
#define DH_LOSTFOCUS_ALARM_EX		0x2112		// 失去焦点报警
#define DH_OEMSTATE_EX				0x2113		// oem报停状态
#define DH_DSP_ALARM_EX				0x2114		// DSP报警
#define DH_ATMPOS_BROKEN_EX			0x2115		// atm和pos机断开报警， 0：连接断开 1：连接正常
#define DH_RECORD_CHANGED_EX		0x2116		// 录像状态变化报警
#define DH_CONFIG_CHANGED_EX		0x2117		// 配置发生变化报警
#define DH_DEVICE_REBOOT_EX			0x2118		// 设备重启报警
#define DH_STATIC_ALARM_EX          0x2122      // 静态检测报警
#define DH_PTZ_LOCATION_EX          0x2123      // 云台定位信息

// 事件类型
#define DH_CONFIG_RESULT_EVENT_EX	0x3000		// 修改配置的返回码；返回结构见DEV_SET_RESULT
#define DH_REBOOT_EVENT_EX			0x3001		// 设备重启事件；如果未发送重启命令，当前修改的配置不会立即生效
#define DH_AUTO_TALK_START_EX		0x3002		// 设备主动邀请开始语音对讲
#define DH_AUTO_TALK_STOP_EX		0x3003		// 设备主动停止语音对讲
#define DH_CONFIG_CHANGE_EX			0x3004		// 设备配置发生改变

// 报警上传功能的报警类型，对应CLIENT_StartService接口、NEW_ALARM_UPLOAD结构体.
#define DH_UPLOAD_ALARM				0x4000		// 外部报警		
#define DH_UPLOAD_MOTION_ALARM		0x4001		// 动态检测报警
#define DH_UPLOAD_VIDEOLOST_ALARM	0x4002		// 视频丢失报警
#define DH_UPLOAD_SHELTER_ALARM		0x4003		// 视频遮挡报警
#define DH_UPLOAD_SOUND_DETECT_ALARM 0x4004		// 音频检测报警
#define DH_UPLOAD_DISKFULL_ALARM	0x4005		// 硬盘满报警
#define DH_UPLOAD_DISKERROR_ALARM	0x4006		// 坏硬盘报警
#define DH_UPLOAD_ENCODER_ALARM		0x4007		// 编码器报警
#define DH_UPLOAD_DECODER_ALARM		0x400B		// 报警解码器报警
#define DH_UPLOAD_EVENT				0x400C		// 定时上传的

// 异步接口回调类型
#define RESPONSE_DECODER_CTRL_TV	0x00000001	// 对应CLIENT_CtrlDecTVScreen接口
#define RESPONSE_DECODER_SWITCH_TV	0x00000002	// 对应CLIENT_SwitchDecTVEncoder接口
#define RESPONSE_DECODER_PLAYBACK	0x00000003	// 对应CLIENT_DecTVPlayback接口

// 分辨率列表，用于与分辨率掩码进行与、或操作
#define	DH_CAPTURE_SIZE_D1			0x00000001
#define DH_CAPTURE_SIZE_HD1			0x00000002
#define DH_CAPTURE_SIZE_BCIF		0x00000004
#define DH_CAPTURE_SIZE_CIF			0x00000008
#define DH_CAPTURE_SIZE_QCIF		0x00000010	
#define DH_CAPTURE_SIZE_VGA			0x00000020	
#define DH_CAPTURE_SIZE_QVGA		0x00000040
#define DH_CAPTURE_SIZE_SVCD		0x00000080
#define DH_CAPTURE_SIZE_QQVGA		0x00000100
#define DH_CAPTURE_SIZE_SVGA		0x00000200
#define DH_CAPTURE_SIZE_XVGA		0x00000400
#define DH_CAPTURE_SIZE_WXGA		0x00000800
#define DH_CAPTURE_SIZE_SXGA		0x00001000
#define DH_CAPTURE_SIZE_WSXGA		0x00002000   
#define DH_CAPTURE_SIZE_UXGA		0x00004000
#define DH_CAPTURE_SIZE_WUXGA       0x00008000
#define DH_CAPTURE_SIZE_LFT         0x00010000
#define DH_CAPTURE_SIZE_720		    0x00020000
#define DH_CAPTURE_SIZE_1080		0x00040000
#define DH_CAPTURE_SIZE_1_3M		0x00080000
#define DH_CAPTURE_SIZE_2M			0x00100000
#define DH_CAPTURE_SIZE_5M			0x00200000

// 编码模式列表，用于与编码模式掩码进行与、或操作
#define DH_CAPTURE_COMP_DIVX_MPEG4	0x00000001
#define DH_CAPTURE_COMP_MS_MPEG4 	0x00000002
#define DH_CAPTURE_COMP_MPEG2		0x00000004
#define DH_CAPTURE_COMP_MPEG1		0x00000008
#define DH_CAPTURE_COMP_H263		0x00000010
#define DH_CAPTURE_COMP_MJPG		0x00000020
#define DH_CAPTURE_COMP_FCC_MPEG4	0x00000040
#define DH_CAPTURE_COMP_H264		0x00000080

// 报警联动动作，用于与报警联动动作掩码进行与、或操作
#define DH_ALARM_UPLOAD				0x00000001
#define DH_ALARM_RECORD				0x00000002
#define DH_ALARM_PTZ				0x00000004
#define DH_ALARM_MAIL				0x00000008
#define DH_ALARM_TOUR				0x00000010
#define DH_ALARM_TIP				0x00000020
#define DH_ALARM_OUT				0x00000040
#define DH_ALARM_FTP_UL				0x00000080
#define DH_ALARM_BEEP				0x00000100
#define DH_ALARM_VOICE				0x00000200
#define DH_ALARM_SNAP				0x00000400

// "恢复默认配置"掩码，可进行与、或操作
#define DH_RESTORE_COMMON			0x00000001	// 普通设置
#define DH_RESTORE_CODING			0x00000002	// 编码设置
#define DH_RESTORE_VIDEO			0x00000004	// 录像设置
#define DH_RESTORE_COMM				0x00000008	// 串口设置
#define DH_RESTORE_NETWORK			0x00000010	// 网络设置
#define DH_RESTORE_ALARM			0x00000020	// 报警设置
#define DH_RESTORE_VIDEODETECT		0x00000040	// 视频检测
#define DH_RESTORE_PTZ				0x00000080	// 云台控制
#define DH_RESTORE_OUTPUTMODE		0x00000100	// 输出模式
#define DH_RESTORE_CHANNELNAME		0x00000200	// 通道名称
#define DH_RESTORE_ALL				0x80000000	// 全部重置

// 云台属性列表
// 低四个字节掩码
#define PTZ_DIRECTION				0x00000001	// 方向
#define PTZ_ZOOM					0x00000002	// 变倍
#define PTZ_FOCUS					0x00000004	// 聚焦
#define PTZ_IRIS					0x00000008	// 光圈
#define PTZ_ALARM					0x00000010	// 报警功能
#define PTZ_LIGHT					0x00000020	// 灯光
#define PTZ_SETPRESET				0x00000040	// 设置预置点
#define PTZ_CLEARPRESET				0x00000080	// 清除预置点
#define PTZ_GOTOPRESET				0x00000100	// 转至预置点
#define PTZ_AUTOPANON				0x00000200	// 水平开始
#define PTZ_AUTOPANOFF				0x00000400	// 水平结束
#define PTZ_SETLIMIT				0x00000800	// 设置边界
#define PTZ_AUTOSCANON				0x00001000	// 自动扫描开始
#define PTZ_AUTOSCANOFF				0x00002000	// 自动扫描开停止
#define PTZ_ADDTOUR					0x00004000	// 增加巡航点
#define PTZ_DELETETOUR				0x00008000	// 删除巡航点
#define PTZ_STARTTOUR				0x00010000	// 开始巡航
#define PTZ_STOPTOUR				0x00020000	// 结束巡航
#define PTZ_CLEARTOUR				0x00040000	// 删除巡航
#define PTZ_SETPATTERN				0x00080000	// 设置模式
#define PTZ_STARTPATTERN			0x00100000	// 开始模式
#define PTZ_STOPPATTERN				0x00200000	// 停止模式
#define PTZ_CLEARPATTERN			0x00400000	// 清除模式
#define PTZ_POSITION				0x00800000	// 快速定位
#define PTZ_AUX						0x01000000	// 辅助开关
#define PTZ_MENU					0x02000000	// 球机菜单
#define PTZ_EXIT					0x04000000	// 退出球机菜单
#define PTZ_ENTER					0x08000000	// 确认
#define PTZ_ESC						0x10000000	// 取消
#define PTZ_MENUUPDOWN				0x20000000	// 菜单上下操作
#define PTZ_MENULEFTRIGHT			0x40000000	// 菜单左右操作
#define PTZ_OPT_NUM					0x80000000	// 操作的个数
// 高四个字节掩码
#define PTZ_DEV						0x00000001	// 云台控制
#define PTZ_MATRIX					0x00000002	// 矩阵控制

// 抓图视频编码类型
#define CODETYPE_MPEG4				0
#define CODETYPE_H264				1
#define CODETYPE_JPG				2

// 码流控制列表
#define DH_CAPTURE_BRC_CBR			0
#define DH_CAPTURE_BRC_VBR			1
//#define DH_CAPTURE_BRC_MBR		2

// 智能分析事件类型
#define EVENT_IVS_ALL						0x00000001		// 订阅所有事件
#define EVENT_IVS_CROSSLINEDETECTION		0x00000002		// 警戒线事件
#define EVENT_IVS_CROSSREGIONDETECTION		0x00000003		// 警戒区事件
#define EVENT_IVS_PASTEDETECTION			0x00000004		// 贴条事件
#define EVENT_IVS_LEFTDETECTION				0x00000005		// 物品遗留事件
#define EVENT_IVS_STAYDETECTION				0x00000006		// 停留事件
#define EVENT_IVS_WANDERDETECTION			0x00000007		// 徘徊事件
#define EVENT_IVS_PRESERVATION				0x00000008		// 物品保全事件
#define EVENT_IVS_MOVEDETECTION				0x00000009		// 移动事件
#define EVENT_IVS_TAILDETECTION				0x0000000A		// 尾随事件
#define EVENT_IVS_RIOTERDETECTION			0x0000000B		// 聚众事件
#define EVENT_IVS_FIREDETECTION				0x0000000C		// 火警事件
#define EVENT_IVS_SMOKEDETECTION			0x0000000D		// 烟雾报警事件
#define EVENT_IVS_FIGHTDETECTION			0x0000000E		// 斗殴事件
#define EVENT_IVS_FLOWSTAT					0x0000000F		// 流量统计事件
#define EVENT_IVS_NUMBERSTAT				0x00000010		// 数量统计事件
#define EVENT_IVS_CAMERACOVERDDETECTION		0x00000011		// 摄像头覆盖事件
#define EVENT_IVS_CAMERAMOVEDDETECTION		0x00000012		// 摄像头移动事件
#define EVENT_IVS_VIDEOABNORMALDETECTION	0x00000013		// 视频异常事件
#define EVENT_IVS_VIDEOBADDETECTION			0x00000014		// 视频损坏事件
#define EVENT_IVS_TRAFFICCONTROL			0x00000015		// 交通管制事件
#define EVENT_IVS_TRAFFICACCIDENT			0x00000016		// 交通事故事件
#define EVENT_IVS_TRAFFICJUNCTION			0x00000017		// 交通路口事件
#define EVENT_IVS_TRAFFICGATE				0x00000018		// 交通卡口事件
#define EVENT_TRAFFICSNAPSHOT				0x00000019		// 交通抓拍事件


// 错误类型代号，对应CLIENT_GetLastError接口的返回值
#define _EC(x)						(0x80000000|x)
#define NET_NOERROR 				0			// 没有错误
#define NET_ERROR					-1			// 未知错误
#define NET_SYSTEM_ERROR			_EC(1)		// Windows系统出错
#define NET_NETWORK_ERROR			_EC(2)		// 网络错误，可能是因为网络超时
#define NET_DEV_VER_NOMATCH			_EC(3)		// 设备协议不匹配
#define NET_INVALID_HANDLE			_EC(4)		// 句柄无效
#define NET_OPEN_CHANNEL_ERROR		_EC(5)		// 打开通道失败
#define NET_CLOSE_CHANNEL_ERROR		_EC(6)		// 关闭通道失败
#define NET_ILLEGAL_PARAM			_EC(7)		// 用户参数不合法
#define NET_SDK_INIT_ERROR			_EC(8)		// SDK初始化出错
#define NET_SDK_UNINIT_ERROR		_EC(9)		// SDK清理出错
#define NET_RENDER_OPEN_ERROR		_EC(10)		// 申请render资源出错
#define NET_DEC_OPEN_ERROR			_EC(11)		// 打开解码库出错
#define NET_DEC_CLOSE_ERROR			_EC(12)		// 关闭解码库出错
#define NET_MULTIPLAY_NOCHANNEL		_EC(13)		// 多画面预览中检测到通道数为0
#define NET_TALK_INIT_ERROR			_EC(14)		// 录音库初始化失败
#define NET_TALK_NOT_INIT			_EC(15)		// 录音库未经初始化
#define	NET_TALK_SENDDATA_ERROR		_EC(16)		// 发送音频数据出错
#define NET_REAL_ALREADY_SAVING		_EC(17)		// 实时数据已经处于保存状态
#define NET_NOT_SAVING				_EC(18)		// 未保存实时数据
#define NET_OPEN_FILE_ERROR			_EC(19)		// 打开文件出错
#define NET_PTZ_SET_TIMER_ERROR		_EC(20)		// 启动云台控制定时器失败
#define NET_RETURN_DATA_ERROR		_EC(21)		// 对返回数据的校验出错
#define NET_INSUFFICIENT_BUFFER		_EC(22)		// 没有足够的缓存
#define NET_NOT_SUPPORTED			_EC(23)		// 当前SDK未支持该功能
#define NET_NO_RECORD_FOUND			_EC(24)		// 查询不到录象
#define NET_NOT_AUTHORIZED			_EC(25)		// 无操作权限
#define NET_NOT_NOW					_EC(26)		// 暂时无法执行
#define NET_NO_TALK_CHANNEL			_EC(27)		// 未发现对讲通道
#define NET_NO_AUDIO				_EC(28)		// 未发现音频
#define NET_NO_INIT					_EC(29)		// 网络SDK未经初始化
#define NET_DOWNLOAD_END			_EC(30)		// 下载已结束
#define NET_EMPTY_LIST				_EC(31)		// 查询结果为空
#define NET_ERROR_GETCFG_SYSATTR	_EC(32)		// 获取系统属性配置失败
#define NET_ERROR_GETCFG_SERIAL		_EC(33)		// 获取序列号失败
#define NET_ERROR_GETCFG_GENERAL	_EC(34)		// 获取常规属性失败
#define NET_ERROR_GETCFG_DSPCAP		_EC(35)		// 获取DSP能力描述失败
#define NET_ERROR_GETCFG_NETCFG		_EC(36)		// 获取网络配置失败
#define NET_ERROR_GETCFG_CHANNAME	_EC(37)		// 获取通道名称失败
#define NET_ERROR_GETCFG_VIDEO		_EC(38)		// 获取视频属性失败
#define NET_ERROR_GETCFG_RECORD		_EC(39)		// 获取录象配置失败
#define NET_ERROR_GETCFG_PRONAME	_EC(40)		// 获取解码器协议名称失败
#define NET_ERROR_GETCFG_FUNCNAME	_EC(41)		// 获取232串口功能名称失败
#define NET_ERROR_GETCFG_485DECODER	_EC(42)		// 获取解码器属性失败
#define NET_ERROR_GETCFG_232COM		_EC(43)		// 获取232串口配置失败
#define NET_ERROR_GETCFG_ALARMIN	_EC(44)		// 获取外部报警输入配置失败
#define NET_ERROR_GETCFG_ALARMDET	_EC(45)		// 获取动态检测报警失败
#define NET_ERROR_GETCFG_SYSTIME	_EC(46)		// 获取设备时间失败
#define NET_ERROR_GETCFG_PREVIEW	_EC(47)		// 获取预览参数失败
#define NET_ERROR_GETCFG_AUTOMT		_EC(48)		// 获取自动维护配置失败
#define NET_ERROR_GETCFG_VIDEOMTRX	_EC(49)		// 获取视频矩阵配置失败
#define NET_ERROR_GETCFG_COVER		_EC(50)		// 获取区域遮挡配置失败
#define NET_ERROR_GETCFG_WATERMAKE	_EC(51)		// 获取图象水印配置失败
#define NET_ERROR_SETCFG_GENERAL	_EC(55)		// 修改常规属性失败
#define NET_ERROR_SETCFG_NETCFG		_EC(56)		// 修改网络配置失败
#define NET_ERROR_SETCFG_CHANNAME	_EC(57)		// 修改通道名称失败
#define NET_ERROR_SETCFG_VIDEO		_EC(58)		// 修改视频属性失败
#define NET_ERROR_SETCFG_RECORD		_EC(59)		// 修改录象配置失败
#define NET_ERROR_SETCFG_485DECODER	_EC(60)		// 修改解码器属性失败
#define NET_ERROR_SETCFG_232COM		_EC(61)		// 修改232串口配置失败
#define NET_ERROR_SETCFG_ALARMIN	_EC(62)		// 修改外部输入报警配置失败
#define NET_ERROR_SETCFG_ALARMDET	_EC(63)		// 修改动态检测报警配置失败
#define NET_ERROR_SETCFG_SYSTIME	_EC(64)		// 修改设备时间失败
#define NET_ERROR_SETCFG_PREVIEW	_EC(65)		// 修改预览参数失败
#define NET_ERROR_SETCFG_AUTOMT		_EC(66)		// 修改自动维护配置失败
#define NET_ERROR_SETCFG_VIDEOMTRX	_EC(67)		// 修改视频矩阵配置失败
#define NET_ERROR_SETCFG_COVER		_EC(68)		// 修改区域遮挡配置失败
#define NET_ERROR_SETCFG_WATERMAKE	_EC(69)		// 修改图象水印配置失败
#define NET_ERROR_SETCFG_WLAN		_EC(70)		// 修改无线网络信息失败
#define NET_ERROR_SETCFG_WLANDEV	_EC(71)		// 选择无线网络设备失败
#define NET_ERROR_SETCFG_REGISTER	_EC(72)		// 修改主动注册参数配置失败
#define NET_ERROR_SETCFG_CAMERA		_EC(73)		// 修改摄像头属性配置失败
#define NET_ERROR_SETCFG_INFRARED	_EC(74)		// 修改红外报警配置失败
#define NET_ERROR_SETCFG_SOUNDALARM	_EC(75)		// 修改音频报警配置失败
#define NET_ERROR_SETCFG_STORAGE    _EC(76)		// 修改存储位置配置失败
#define NET_AUDIOENCODE_NOTINIT		_EC(77)		// 音频编码接口没有成功初始化
#define NET_DATA_TOOLONGH			_EC(78)		// 数据过长
#define NET_UNSUPPORTED				_EC(79)		// 设备不支持该操作
#define NET_DEVICE_BUSY				_EC(80)		// 设备资源不足
#define NET_SERVER_STARTED			_EC(81)		// 服务器已经启动
#define NET_SERVER_STOPPED			_EC(82)		// 服务器尚未成功启动
#define NET_LISTER_INCORRECT_SERIAL	_EC(83)		// 输入序列号有误
#define NET_QUERY_DISKINFO_FAILED	_EC(84)		// 获取硬盘信息失败
#define NET_ERROR_GETCFG_SESSION	_EC(85)		// 获取连接Session信息
#define NET_USER_FLASEPWD_TRYTIME	_EC(86)		// 输入密码错误超过限制次数
#define NET_LOGIN_ERROR_PASSWORD	_EC(100)	// 密码不正确
#define NET_LOGIN_ERROR_USER		_EC(101)	// 帐户不存在
#define NET_LOGIN_ERROR_TIMEOUT		_EC(102)	// 等待登录返回超时
#define NET_LOGIN_ERROR_RELOGGIN	_EC(103)	// 帐号已登录
#define NET_LOGIN_ERROR_LOCKED		_EC(104)	// 帐号已被锁定
#define NET_LOGIN_ERROR_BLACKLIST	_EC(105)	// 帐号已被列为黑名单
#define NET_LOGIN_ERROR_BUSY		_EC(106)	// 资源不足，系统忙
#define NET_LOGIN_ERROR_CONNECT		_EC(107)	// 登录设备超时，请检查网络并重试
#define NET_LOGIN_ERROR_NETWORK		_EC(108)	// 网络连接失败
#define NET_LOGIN_ERROR_SUBCONNECT	_EC(109)	// 登录设备成功，但无法创建视频通道，请检查网络状况
#define NET_RENDER_SOUND_ON_ERROR	_EC(120)	// Render库打开音频出错
#define NET_RENDER_SOUND_OFF_ERROR	_EC(121)	// Render库关闭音频出错
#define NET_RENDER_SET_VOLUME_ERROR	_EC(122)	// Render库控制音量出错
#define NET_RENDER_ADJUST_ERROR		_EC(123)	// Render库设置画面参数出错
#define NET_RENDER_PAUSE_ERROR		_EC(124)	// Render库暂停播放出错
#define NET_RENDER_SNAP_ERROR		_EC(125)	// Render库抓图出错
#define NET_RENDER_STEP_ERROR		_EC(126)	// Render库步进出错
#define NET_RENDER_FRAMERATE_ERROR	_EC(127)	// Render库设置帧率出错
#define NET_GROUP_EXIST				_EC(140)	// 组名已存在
#define	NET_GROUP_NOEXIST			_EC(141)	// 组名不存在
#define NET_GROUP_RIGHTOVER			_EC(142)	// 组的权限超出权限列表范围
#define NET_GROUP_HAVEUSER			_EC(143)	// 组下有用户，不能删除
#define NET_GROUP_RIGHTUSE			_EC(144)	// 组的某个权限被用户使用，不能出除
#define NET_GROUP_SAMENAME			_EC(145)	// 新组名同已有组名重复
#define	NET_USER_EXIST				_EC(146)	// 用户已存在
#define NET_USER_NOEXIST			_EC(147)	// 用户不存在
#define NET_USER_RIGHTOVER			_EC(148)	// 用户权限超出组权限
#define NET_USER_PWD				_EC(149)	// 保留帐号，不容许修改密码
#define NET_USER_FLASEPWD			_EC(150)	// 密码不正确
#define NET_USER_NOMATCHING			_EC(151)	// 密码不匹配
#define NET_ERROR_GETCFG_ETHERNET	_EC(300)	// 获取网卡配置失败
#define NET_ERROR_GETCFG_WLAN		_EC(301)	// 获取无线网络信息失败
#define NET_ERROR_GETCFG_WLANDEV	_EC(302)	// 获取无线网络设备失败
#define NET_ERROR_GETCFG_REGISTER	_EC(303)	// 获取主动注册参数失败
#define NET_ERROR_GETCFG_CAMERA		_EC(304)	// 获取摄像头属性失败
#define NET_ERROR_GETCFG_INFRARED	_EC(305)	// 获取红外报警配置失败
#define NET_ERROR_GETCFG_SOUNDALARM	_EC(306)	// 获取音频报警配置失败
#define NET_ERROR_GETCFG_STORAGE    _EC(307)	// 获取存储位置配置失败
#define NET_ERROR_GETCFG_MAIL		_EC(308)	// 获取邮件配置失败
#define NET_CONFIG_DEVBUSY			_EC(309)	// 暂时无法设置
#define NET_CONFIG_DATAILLEGAL		_EC(310)	// 配置数据不合法
#define NET_ERROR_GETCFG_DST        _EC(311)    // 获取夏令时配置失败
#define NET_ERROR_SETCFG_DST        _EC(312)    // 设置夏令时配置失败
#define NET_ERROR_GETCFG_VIDEO_OSD  _EC(313)    // 获取视频OSD叠加配置失败
#define NET_ERROR_SETCFG_VIDEO_OSD  _EC(314)    // 设置视频OSD叠加配置失败
#define NET_ERROR_GETCFG_GPRSCDMA   _EC(315)    // 获取CDMA\GPRS网络配置失败
#define NET_ERROR_SETCFG_GPRSCDMA   _EC(316)    // 设置CDMA\GPRS网络配置失败
#define NET_ERROR_GETCFG_IPFILTER   _EC(317)    // 获取IP过滤配置失败
#define NET_ERROR_SETCFG_IPFILTER   _EC(318)    // 设置IP过滤配置失败
#define NET_ERROR_GETCFG_TALKENCODE _EC(319)    // 获取语音对讲编码配置失败
#define NET_ERROR_SETCFG_TALKENCODE _EC(320)    // 设置语音对讲编码配置失败
#define NET_ERROR_GETCFG_RECORDLEN  _EC(321)    // 获取录像打包长度配置失败
#define NET_ERROR_SETCFG_RECORDLEN  _EC(322)    // 设置录像打包长度配置失败
#define	NET_DONT_SUPPORT_SUBAREA	_EC(323)	// 不支持网络硬盘分区
#define	NET_ERROR_GET_AUTOREGSERVER	_EC(324)	// 获取设备上主动注册服务器信息失败
#define	NET_ERROR_CONTROL_AUTOREGISTER		_EC(325)	// 主动注册重定向注册错误
#define	NET_ERROR_DISCONNECT_AUTOREGISTER	_EC(326)	// 断开主动注册服务器错误
#define NET_ERROR_GETCFG_MMS				_EC(327)	// 获取mms配置失败
#define NET_ERROR_SETCFG_MMS				_EC(328)	// 设置mms配置失败
#define NET_ERROR_GETCFG_SMSACTIVATION      _EC(329)	// 获取短信激活无线连接配置失败
#define NET_ERROR_SETCFG_SMSACTIVATION      _EC(330)	// 设置短信激活无线连接配置失败
#define NET_ERROR_GETCFG_DIALINACTIVATION	_EC(331)	// 获取拨号激活无线连接配置失败
#define NET_ERROR_SETCFG_DIALINACTIVATION	_EC(332)	// 设置拨号激活无线连接配置失败
#define NET_ERROR_GETCFG_VIDEOOUT           _EC(333)    // 查询视频输出参数配置失败
#define NET_ERROR_SETCFG_VIDEOOUT			_EC(334)	// 设置视频输出参数配置失败
#define NET_ERROR_GETCFG_OSDENABLE			_EC(335)	// 获取osd叠加使能配置失败
#define NET_ERROR_SETCFG_OSDENABLE			_EC(336)	// 设置osd叠加使能配置失败
#define NET_ERROR_SETCFG_ENCODERINFO        _EC(337)    // 设置数字通道前端编码接入配置失败
#define NET_ERROR_GETCFG_TVADJUST		    _EC(338)	// 获取TV调节配置失败
#define NET_ERROR_SETCFG_TVADJUST			_EC(339)	// 设置TV调节配置失败

#define NET_ERROR_CONNECT_FAILED			_EC(340)	// 请求建立连接失败
#define NET_ERROR_SETCFG_BURNFILE			_EC(341)	// 请求刻录文件上传失败
#define NET_ERROR_SNIFFER_GETCFG			_EC(342)	// 获取抓包配置信息失败
#define NET_ERROR_SNIFFER_SETCFG			_EC(343)	// 设置抓包配置信息失败
#define NET_ERROR_DOWNLOADRATE_GETCFG		_EC(344)	// 查询下载限制信息失败
#define NET_ERROR_DOWNLOADRATE_SETCFG		_EC(345)	// 设置下载限制信息失败
#define NET_ERROR_SEARCH_TRANSCOM			_EC(346)	// 查询串口参数失败
#define NET_ERROR_GETCFG_POINT				_EC(347)	// 获取预制点信息错误
#define NET_ERROR_SETCFG_POINT				_EC(348)	// 设置预制点信息错误
#define NET_SDK_LOGOUT_ERROR				_EC(349)    // SDK没有正常登出设备
#define NET_ERROR_GET_VEHICLE_CFG			_EC(350)	// 获取车载配置失败
#define NET_ERROR_SET_VEHICLE_CFG			_EC(351)	// 设置车载配置失败
#define NET_ERROR_GET_ATM_OVERLAY_CFG		_EC(352)	// 获取atm叠加配置失败
#define NET_ERROR_SET_ATM_OVERLAY_CFG		_EC(353)	// 设置atm叠加配置失败
#define NET_ERROR_GET_ATM_OVERLAY_ABILITY	_EC(354)	// 获取atm叠加能力失败
#define NET_ERROR_GET_DECODER_TOUR_CFG		_EC(355)	// 获取解码器解码轮巡配置失败
#define NET_ERROR_SET_DECODER_TOUR_CFG		_EC(356)	// 设置解码器解码轮巡配置失败
#define NET_ERROR_CTRL_DECODER_TOUR			_EC(357)	// 控制解码器解码轮巡失败
#define NET_GROUP_OVERSUPPORTNUM			_EC(358)	// 超出设备支持最大用户组数目
#define NET_USER_OVERSUPPORTNUM				_EC(359)	// 超出设备支持最大用户数目
#define NET_ERROR_GET_SIP_CFG				_EC(368)	// 获取SIP配置失败
#define NET_ERROR_SET_SIP_CFG				_EC(369)	// 设置SIP配置失败
#define NET_ERROR_GET_SIP_ABILITY			_EC(370)	// 获取SIP能力失败
#define NET_ERROR_GET_WIFI_AP_CFG			_EC(371)	// 获取WIFI ap配置失败
#define NET_ERROR_SET_WIFI_AP_CFG			_EC(372)	// 设置WIFI ap配置失败


/************************************************************************
 ** 枚举定义
 ***********************************************************************/
// 设备类型
enum NET_DEVICE_TYPE 
{
	NET_PRODUCT_NONE = 0,
	NET_DVR_NONREALTIME_MACE,					// 非实时MACE
	NET_DVR_NONREALTIME,						// 非实时
	NET_NVS_MPEG1,								// 网络视频服务器
	NET_DVR_MPEG1_2,							// MPEG1二路录像机
	NET_DVR_MPEG1_8,							// MPEG1八路录像机
	NET_DVR_MPEG4_8,							// MPEG4八路录像机
	NET_DVR_MPEG4_16,							// MPEG4十六路录像机
	NET_DVR_MPEG4_SX2,							// LB系列录像机
	NET_DVR_MEPG4_ST2,							// GB系列录像机
	NET_DVR_MEPG4_SH2,							// HB系列录像机
	NET_DVR_MPEG4_GBE,							// GBE系列录像机
	NET_DVR_MPEG4_NVSII,						// II代网络视频服务器
	NET_DVR_STD_NEW,							// 新标准配置协议
	NET_DVR_DDNS,								// DDNS服务器
	NET_DVR_ATM,								// ATM机
	NET_NB_SERIAL,								// 二代非实时NB系列机器
	NET_LN_SERIAL,								// LN系列产品
	NET_BAV_SERIAL,								// BAV系列产品
	NET_SDIP_SERIAL,							// SDIP系列产品
	NET_IPC_SERIAL,								// IPC系列产品
	NET_NVS_B,									// NVS B系列
	NET_NVS_C,									// NVS H系列
	NET_NVS_S,									// NVS S系列
	NET_NVS_E,									// NVS E系列
	NET_DVR_NEW_PROTOCOL,						// 从QueryDevState中查询设备类型,以字符串格式
	NET_NVD_SERIAL,								// 解码器
	NET_DVR_N5,									// N5
	NET_DVR_MIX_DVR,							// 混合DVR
	NET_SVR_SERIAL,								// SVR系列
	NET_SVR_BS,									// SVR-BS
	NET_NVR_SERIAL,								// NVR系列
	NET_DVR_N51,                                // N51
};

// 语言种类
typedef enum __LANGUAGE_TYPE
{
	DH_LANGUAGE_ENGLISH,						// 英文	
	DH_LANGUAGE_CHINESE_SIMPLIFIED,				// 简体中文	
	DH_LANGUAGE_CHINESE_TRADITIONAL,			// 繁体中文	
	DH_LANGUAGE_ITALIAN,						// 意大利文	
	DH_LANGUAGE_SPANISH,						// 西班牙文
	DH_LANGUAGE_JAPANESE,						// 日文版	
	DH_LANGUAGE_RUSSIAN,						// 俄文版		
	DH_LANGUAGE_FRENCH,							// 法文版		
	DH_LANGUAGE_GERMAN, 						// 德文版		
	DH_LANGUAGE_PORTUGUESE,						// 葡萄牙语	
	DH_LANGUAGE_TURKEY,							// 土尔其语	
	DH_LANGUAGE_POLISH,							// 波兰语	
	DH_LANGUAGE_ROMANIAN,						// 罗马尼亚	
	DH_LANGUAGE_HUNGARIAN,						// 匈牙利语	
	DH_LANGUAGE_FINNISH,						// 芬兰语	
	DH_LANGUAGE_ESTONIAN,						// 爱沙尼亚语	
	DH_LANGUAGE_KOREAN,							// 韩语	
	DH_LANGUAGE_FARSI,							// 波斯语 	
	DH_LANGUAGE_DANSK,							// 丹麦语
	DH_LANGUAGE_CZECHISH,						// 捷克文
	DH_LANGUAGE_BULGARIA,						// 保加利亚文
	DH_LANGUAGE_SLOVAKIAN,						// 斯洛伐克语
	DH_LANGUAGE_SLOVENIA,						// 斯洛文尼亚文
	DH_LANGUAGE_CROATIAN,						// 克罗地亚语
	DH_LANGUAGE_DUTCH,							// 荷兰语
	DH_LANGUAGE_GREEK,							// 希腊语
	DH_LANGUAGE_UKRAINIAN,						// 乌克兰语
	DH_LANGUAGE_SWEDISH,						// 瑞典语
	DH_LANGUAGE_SERBIAN,						// 塞尔维亚语
	DH_LANGUAGE_VIETNAMESE,						// 越南语
	DH_LANGUAGE_LITHUANIAN,						// 立陶宛语
	DH_LANGUAGE_FILIPINO,						// 菲律宾语
	DH_LANGUAGE_ARABIC,							// 阿拉伯语
	DH_LANGUAGE_CATALAN,						// 加泰罗尼亚语
	DH_LANGUAGE_LATVIAN,						// 拉脱维亚语
	DH_LANGUAGE_THAI,							// 泰语
	DH_LANGUAGE_HEBREW,							// 希伯来语
	DH_LANGUAGE_Bosnian,						// 波斯尼亚文
} DH_LANGUAGE_TYPE;

// 升级类型
typedef enum __EM_UPGRADE_TYPE
{
	DH_UPGRADE_BIOS_TYPE = 1,					// BIOS升级
	DH_UPGRADE_WEB_TYPE,						// WEB升级
	DH_UPGRADE_BOOT_YPE,						// BOOT升级
	DH_UPGRADE_CHARACTER_TYPE,					// 汉字库
	DH_UPGRADE_LOGO_TYPE,						// LOGO
	DH_UPGRADE_EXE_TYPE,						// EXE，例如播放器等
} EM_UPGRADE_TYPE;

// 录象类型(定时、动态检测、报警)
typedef enum __REC_TYPE
{
	DH_REC_TYPE_TIM = 0,
	DH_REC_TYPE_MTD,
	DH_REC_TYPE_ALM,
	DH_REC_TYPE_NUM,
} REC_TYPE;

// 网络类型 
typedef enum __GPRSCDMA_NETWORK_TYPE
{
	DH_TYPE_AUTOSEL = 0,						// 自动选择
	DH_TYPE_TD_SCDMA,							// TD-SCDMA网络 
	DH_TYPE_WCDMA,								// WCDMA网络
	DH_TYPE_CDMA_1x,							// CDMA 1.x网络
	DH_TYPE_EDGE,								// GPRS网络
	DH_TYPE_EVDO,								// EVDO网络
	DH_TYPE_WIFI,								// 无线
} EM_GPRSCDMA_NETWORK_TYPE;

// 接口类型，对应CLIENT_SetSubconnCallBack接口
typedef enum __EM_INTERFACE_TYPE
{
	DH_INTERFACE_OTHER = 0x00000000,			// 未知接口
	DH_INTERFACE_REALPLAY,						// 实时监视接口
	DH_INTERFACE_PREVIEW,						// 多画面预览接口
	DH_INTERFACE_PLAYBACK,						// 回放接口
	DH_INTERFACE_DOWNLOAD,						// 下载接口
} EM_INTERFACE_TYPE;

/////////////////////////////////监视相关/////////////////////////////////

// 预览类型，对应CLIENT_RealPlayEx接口
typedef enum _RealPlayType
{
	DH_RType_Realplay = 0,						// 实时预览
	DH_RType_Multiplay,							// 多画面预览
		
	DH_RType_Realplay_0,						// 实时监视-主码流，等同于DH_RType_Realplay
	DH_RType_Realplay_1,						// 实时监视-从码流1
	DH_RType_Realplay_2,						// 实时监视-从码流2
	DH_RType_Realplay_3,						// 实时监视-从码流3
		
	DH_RType_Multiplay_1,						// 多画面预览－1画面
	DH_RType_Multiplay_4,						// 多画面预览－4画面
	DH_RType_Multiplay_8,						// 多画面预览－8画面
	DH_RType_Multiplay_9,						// 多画面预览－9画面
	DH_RType_Multiplay_16,						// 多画面预览－16画面
	DH_RType_Multiplay_6,						// 多画面预览－6画面
	DH_RType_Multiplay_12,						// 多画面预览－12画面
} DH_RealPlayType;

/////////////////////////////////云台相关/////////////////////////////////

// 通用云台控制命令
typedef enum _PTZ_ControlType
{
	DH_PTZ_UP_CONTROL = 0,						// 上
	DH_PTZ_DOWN_CONTROL,						// 下
	DH_PTZ_LEFT_CONTROL,						// 左
	DH_PTZ_RIGHT_CONTROL,						// 右
	DH_PTZ_ZOOM_ADD_CONTROL,					// 变倍+
	DH_PTZ_ZOOM_DEC_CONTROL,					// 变倍-
	DH_PTZ_FOCUS_ADD_CONTROL,					// 调焦+
	DH_PTZ_FOCUS_DEC_CONTROL,					// 调焦-
	DH_PTZ_APERTURE_ADD_CONTROL,				// 光圈+
	DH_PTZ_APERTURE_DEC_CONTROL,				// 光圈-
    DH_PTZ_POINT_MOVE_CONTROL,					// 转至预置点
    DH_PTZ_POINT_SET_CONTROL,					// 设置
    DH_PTZ_POINT_DEL_CONTROL,					// 删除
    DH_PTZ_POINT_LOOP_CONTROL,					// 点间巡航
    DH_PTZ_LAMP_CONTROL							// 灯光雨刷
} DH_PTZ_ControlType;

// 云台控制扩展命令
typedef enum _EXTPTZ_ControlType
{
	DH_EXTPTZ_LEFTTOP = 0x20,					// 左上
	DH_EXTPTZ_RIGHTTOP,							// 右上
	DH_EXTPTZ_LEFTDOWN,							// 左下
	DH_EXTPTZ_RIGHTDOWN,						// 右下
	DH_EXTPTZ_ADDTOLOOP,						// 加入预置点到巡航 巡航线路 预置点值
	DH_EXTPTZ_DELFROMLOOP,						// 删除巡航中预置点 巡航线路 预置点值
    DH_EXTPTZ_CLOSELOOP,						// 清除巡航 巡航线路
	DH_EXTPTZ_STARTPANCRUISE,					// 开始水平旋转
	DH_EXTPTZ_STOPPANCRUISE,					// 停止水平旋转
	DH_EXTPTZ_SETLEFTBORDER,					// 设置左边界
	DH_EXTPTZ_SETRIGHTBORDER,					// 设置右边界
	DH_EXTPTZ_STARTLINESCAN,					// 开始线扫
    DH_EXTPTZ_CLOSELINESCAN,					// 停止线扫
    DH_EXTPTZ_SETMODESTART,						// 设置模式开始	模式线路
    DH_EXTPTZ_SETMODESTOP,						// 设置模式结束	模式线路
	DH_EXTPTZ_RUNMODE,							// 运行模式	模式线路
	DH_EXTPTZ_STOPMODE,							// 停止模式	模式线路
	DH_EXTPTZ_DELETEMODE,						// 清除模式	模式线路
	DH_EXTPTZ_REVERSECOMM,						// 翻转命令
	DH_EXTPTZ_FASTGOTO,							// 快速定位 水平坐标(8192) 垂直坐标(8192) 变倍(4)
	DH_EXTPTZ_AUXIOPEN,							// 辅助开关开 辅助点
	DH_EXTPTZ_AUXICLOSE,						// 辅助开关关 辅助点
	DH_EXTPTZ_OPENMENU = 0x36,					// 打开球机菜单
	DH_EXTPTZ_CLOSEMENU,						// 关闭菜单
	DH_EXTPTZ_MENUOK,							// 菜单确定
	DH_EXTPTZ_MENUCANCEL,						// 菜单取消
	DH_EXTPTZ_MENUUP,							// 菜单上
	DH_EXTPTZ_MENUDOWN,							// 菜单下
	DH_EXTPTZ_MENULEFT,							// 菜单左
	DH_EXTPTZ_MENURIGHT,						// 菜单右
	DH_EXTPTZ_ALARMHANDLE = 0x40,				// 报警联动云台 parm1：报警输入通道；parm2：报警联动类型1-预置点2-线扫3-巡航；parm3：联动值，如预置点号
	DH_EXTPTZ_MATRIXSWITCH = 0x41,				// 矩阵切换 parm1：监视器号(视频输出号)；parm2：视频输入号；parm3：矩阵号
	DH_EXTPTZ_LIGHTCONTROL,						// 灯光控制器
	DH_EXTPTZ_EXACTGOTO,						// 三维精确定位 parm1：水平角度(0~3600)；parm2：垂直坐标(0~900)；parm3：变倍(1~128)
	DH_EXTPTZ_RESETZERO,                        // 三维定位重设零位
	DH_EXTPTZ_UP_TELE = 0x70,					// 上 + TELE param1=速度(1-8)，下同
	DH_EXTPTZ_DOWN_TELE,						// 下 + TELE
	DH_EXTPTZ_LEFT_TELE,						// 左 + TELE
	DH_EXTPTZ_RIGHT_TELE,						// 右 + TELE
	DH_EXTPTZ_LEFTUP_TELE,						// 左上 + TELE
	DH_EXTPTZ_LEFTDOWN_TELE,					// 左下 + TELE
	DH_EXTPTZ_TIGHTUP_TELE,						// 右上 + TELE
	DH_EXTPTZ_RIGHTDOWN_TELE,					// 右下 + TELE
	DH_EXTPTZ_UP_WIDE,							// 上 + WIDE param1=速度(1-8)，下同
	DH_EXTPTZ_DOWN_WIDE,						// 下 + WIDE
	DH_EXTPTZ_LEFT_WIDE,						// 左 + WIDE
	DH_EXTPTZ_RIGHT_WIDE,						// 右 + WIDE
	DH_EXTPTZ_LEFTUP_WIDE,						// 左上 + WIDE
	DH_EXTPTZ_LEFTDOWN_WIDE,					// 左下 + WIDE
	DH_EXTPTZ_TIGHTUP_WIDE,						// 右上 + WIDE
	DH_EXTPTZ_RIGHTDOWN_WIDE,					// 右下 + WIDE
	DH_EXTPTZ_TOTAL,							// 最大命令值
} DH_EXTPTZ_ControlType;

/////////////////////////////////日志相关/////////////////////////////////

// 日志查询类型
typedef enum _DH_LOG_QUERY_TYPE
{
	DHLOG_ALL = 0,								// 所有日志
	DHLOG_SYSTEM,								// 系统日志
	DHLOG_CONFIG,								// 配置日志
	DHLOG_STORAGE,								// 存储相关
	DHLOG_ALARM,								// 报警日志
	DHLOG_RECORD,								// 录象相关
	DHLOG_ACCOUNT,								// 帐号相关
	DHLOG_CLEAR,								// 清除日志
	DHLOG_PLAYBACK								// 回放相关
} DH_LOG_QUERY_TYPE;

// 日志类型
typedef enum _DH_LOG_TYPE
{
	DH_LOG_REBOOT = 0x0000,						// 设备重启
	DH_LOG_SHUT,								// 设备关机
	DH_LOG_UPGRADE = 0x0004,					// 设备升级
	DH_LOG_CONFSAVE = 0x0100,					// 保存配置
	DH_LOG_CONFLOAD,							// 读取配置
	DH_LOG_FSERROR = 0x0200,					// 文件系统错误
	DH_LOG_HDD_WERR,							// 硬盘写错误
	DH_LOG_HDD_RERR,							// 硬盘读错误
	DH_LOG_HDD_TYPE,							// 设置硬盘类型
	DH_LOG_HDD_FORMAT,							// 格式化硬盘
	DH_LOG_HDD_NOSPACE,							// 当前工作盘空间不足
	DH_LOG_HDD_TYPE_RW,							// 设置硬盘类型为读写盘
	DH_LOG_HDD_TYPE_RO,							// 设置硬盘类型为只读盘	
	DH_LOG_HDD_TYPE_RE,							// 设置硬盘类型为冗余盘
	DH_LOG_HDD_TYPE_SS,							// 设置硬盘类型为快照盘
	DH_LOG_HDD_NONE,							// 无硬盘记录
	DH_LOG_HDD_NOWORKHDD,						// 无工作盘(没有读写盘)
	DH_LOG_HDD_TYPE_BK,							// 设置硬盘类型为备份盘
	DH_LOG_HDD_TYPE_REVERSE,					// 设置硬盘类型为保留分区
	DH_LOG_ALM_IN = 0x0300,						// 外部输入报警开始
	DH_LOG_NETALM_IN,							// 网络报警输入
	DH_LOG_ALM_END = 0x0302,					// 外部输入报警停止
	DH_LOG_LOSS_IN,								// 视频丢失报警开始
	DH_LOG_LOSS_END,							// 视频丢失报警结束
	DH_LOG_MOTION_IN,							// 动态检测报警开始
	DH_LOG_MOTION_END,							// 动态检测报警结束
	DH_LOG_ALM_BOSHI,							// 报警器报警输入
	DH_LOG_NET_ABORT = 0x0308,					// 网络断开
	DH_LOG_NET_ABORT_RESUME,					// 网络恢复
	DH_LOG_CODER_BREAKDOWN,						// 编码器故障
	DH_LOG_CODER_BREAKDOWN_RESUME,				// 编码器故障恢复
	DH_LOG_BLIND_IN,							// 视频遮挡
	DH_LOG_BLIND_END,							// 视频遮挡恢复
	DH_LOG_ALM_TEMP_HIGH,						// 温度过高
	DH_LOG_ALM_VOLTAGE_LOW,						// 电压过低
	DH_LOG_ALM_BATTERY_LOW,						// 电池容量不足
	DH_LOG_ALM_ACC_BREAK,						// ACC断电
	DH_LOG_INFRAREDALM_IN = 0x03a0,				// 无线报警开始
	DH_LOG_INFRAREDALM_END,						// 无线报警结束
	DH_LOG_IPCONFLICT,							// IP冲突
	DH_LOG_IPCONFLICT_RESUME,					// IP恢复
	DH_LOG_SDPLUG_IN,							// SD卡插入
	DH_LOG_SDPLUG_OUT,							// SD卡拔出
	DH_LOG_NET_PORT_BIND_FAILED,				// 网络端口绑定失败
	DH_LOG_AUTOMATIC_RECORD = 0x0400,			// 自动录像
	DH_LOG_MANUAL_RECORD = 0x0401,				// 手动录象
	DH_LOG_CLOSED_RECORD,						// 停止录象
	DH_LOG_LOGIN = 0x0500,						// 登录
	DH_LOG_LOGOUT,								// 注销
	DH_LOG_ADD_USER,							// 添加用户
	DH_LOG_DELETE_USER,							// 删除用户
	DH_LOG_MODIFY_USER,							// 修改用户
	DH_LOG_ADD_GROUP,							// 添加用户组
	DH_LOG_DELETE_GROUP,						// 删除用户组
	DH_LOG_MODIFY_GROUP,						// 修改用户组
	DH_LOG_NET_LOGIN = 0x0508,					// 网络用户登录
	DH_LOG_CLEAR = 0x0600,						// 清除日志
	DH_LOG_SEARCHLOG,							// 查询日志
	DH_LOG_SEARCH = 0x0700,						// 录像查询
	DH_LOG_DOWNLOAD,							// 录像下载
	DH_LOG_PLAYBACK,							// 录像回放
	DH_LOG_BACKUP,								// 备份录像文件
	DH_LOG_BACKUPERROR,							// 备份录像文件失败

	DH_LOG_TYPE_NR = 7,
} DH_LOG_TYPE;

// 扩展日志类型，对应CLIENT_QueryLogEx接口，条件(int nType = 1；参数reserved = &nType)
typedef enum _DH_NEWLOG_TYPE
{
	DH_NEWLOG_REBOOT = 0x0000,					// 设备重启
	DH_NEWLOG_SHUT,								// 设备关机
	DH_NEWLOG_UPGRADE = 0x0004,					// 设备升级
	DH_NEWLOG_CONFSAVE = 0x0100,				// 保存配置
	DH_NEWLOG_CONFLOAD,							// 读取配置
	DH_NEWLOG_FSERROR = 0x0200,					// 文件系统错误
	DH_NEWLOG_HDD_WERR,							// 硬盘写错误
	DH_NEWLOG_HDD_RERR,							// 硬盘读错误
	DH_NEWLOG_HDD_TYPE,							// 设置硬盘类型
	DH_NEWLOG_HDD_FORMAT,						// 格式化硬盘
	DH_NEWLOG_HDD_NOSPACE,						// 当前工作盘空间不足
	DH_NEWLOG_HDD_TYPE_RW,						// 设置硬盘类型为读写盘
	DH_NEWLOG_HDD_TYPE_RO,						// 设置硬盘类型为只读盘	
	DH_NEWLOG_HDD_TYPE_RE,						// 设置硬盘类型为冗余盘
	DH_NEWLOG_HDD_TYPE_SS,						// 设置硬盘类型为快照盘
	DH_NEWLOG_HDD_NONE,							// 无硬盘记录日志
	DH_NEWLOG_HDD_NOWORKHDD,					// 无工作盘(没有读写盘)
	DH_NEWLOG_HDD_TYPE_BK,						// 设置硬盘类型为备份盘
	DH_NEWLOG_HDD_TYPE_REVERSE,					// 设置硬盘类型为保留分区
	DH_NEWLOG_ALM_IN = 0x0300,					// 外部输入报警开始
	DH_NEWLOG_NETALM_IN,						// 网络报警
	DH_NEWLOG_ALM_END = 0x0302,					// 外部输入报警停止
	DH_NEWLOG_LOSS_IN,							// 视频丢失报警开始
	DH_NEWLOG_LOSS_END,							// 视频丢失报警结束
	DH_NEWLOG_MOTION_IN,						// 动态检测报警开始
	DH_NEWLOG_MOTION_END,						// 动态检测报警结束
	DH_NEWLOG_ALM_BOSHI,						// 报警器报警输入
	DH_NEWLOG_NET_ABORT = 0x0308,				// 网络断开
	DH_NEWLOG_NET_ABORT_RESUME,					// 网络恢复
	DH_NEWLOG_CODER_BREAKDOWN,					// 编码器故障
	DH_NEWLOG_CODER_BREAKDOWN_RESUME,			// 编码器故障恢复
	DH_NEWLOG_BLIND_IN,							// 视频遮挡
	DH_NEWLOG_BLIND_END,						// 视频遮挡恢复
	DH_NEWLOG_ALM_TEMP_HIGH,					// 温度过高
	DH_NEWLOG_ALM_VOLTAGE_LOW,					// 电压过低
	DH_NEWLOG_ALM_BATTERY_LOW,					// 电池容量不足
	DH_NEWLOG_ALM_ACC_BREAK,					// ACC断电
	DH_NEWLOG_INFRAREDALM_IN = 0x03a0,			// 无线报警开始
	DH_NEWLOG_INFRAREDALM_END,					// 无线报警结束
	DH_NEWLOG_IPCONFLICT,						// IP冲突
	DH_NEWLOG_IPCONFLICT_RESUME,				// IP恢复
	DH_NEWLOG_SDPLUG_IN,						// SD卡插入
	DH_NEWLOG_SDPLUG_OUT,						// SD卡拔出
	DH_NEWLOG_NET_PORT_BIND_FAILED,				// 网络端口绑定失败
	DH_NEWLOG_AUTOMATIC_RECORD = 0x0400,		// 自动录象
	DH_NEWLOG_MANUAL_RECORD,					// 手动录象开
	DH_NEWLOG_CLOSED_RECORD,					// 停止录象
	DH_NEWLOG_LOGIN = 0x0500,					// 登录
	DH_NEWLOG_LOGOUT,							// 注销
	DH_NEWLOG_ADD_USER,							// 添加用户
	DH_NEWLOG_DELETE_USER,						// 删除用户
	DH_NEWLOG_MODIFY_USER,						// 修改用户
	DH_NEWLOG_ADD_GROUP,						// 添加用户组
	DH_NEWLOG_DELETE_GROUP,						// 删除用户组
	DH_NEWLOG_MODIFY_GROUP,						// 修改用户组
	DH_NEWLOG_NET_LOGIN = 0x0508,				// 网络用户登录
	DH_NEWLOG_CLEAR = 0x0600,					// 清除日志
	DH_NEWLOG_SEARCHLOG,						// 查询日志
	DH_NEWLOG_SEARCH = 0x0700,					// 录像查询
	DH_NEWLOG_DOWNLOAD,							// 录像下载
	DH_NEWLOG_PLAYBACK,							// 录像回放
	DH_NEWLOG_BACKUP,							// 备份录像文件
	DH_NEWLOG_BACKUPERROR,						// 备份录像文件失败
	
	DH_NEWLOG_TYPE_NR = 8,		
} DH_NEWLOG_TYPE;

///////////////////////////////语音对讲相关///////////////////////////////

// 语音编码类型
typedef enum __TALK_CODING_TYPE
{
	DH_TALK_DEFAULT = 0,						// 无头PCM
	DH_TALK_PCM = 1,							// 带头PCM
	DH_TALK_G711a,								// G711a
	DH_TALK_AMR,								// AMR
	DH_TALK_G711u,								// G711u
	DH_TALK_G726,								// G726
} DH_TALK_CODING_TYPE;

// 对讲方式
typedef enum __EM_USEDEV_MODE
{
	DH_TALK_CLIENT_MODE,						// 设置客户端方式进行语音对讲
	DH_TALK_SERVER_MODE,						// 设置服务器方式进行语音对讲
	DH_TALK_ENCODE_TYPE,						// 设置语音对讲编码格式
	DH_ALARM_LISTEN_MODE,						// 设置报警订阅方式
	DH_CONFIG_AUTHORITY_MODE,					// 设置通过权限进行配置管理
} EM_USEDEV_MODE;

// AMR编码类型
typedef enum __EM_ARM_ENCODE_MODE
{
	DH_TALK_AMR_AMR475 = 1,						// AMR475编码
	DH_TALK_AMR_AMR515,							// AMR515编码
	DH_TALK_AMR_AMR59,							// AMR59编码
	DH_TALK_AMR_AMR67,							// AMR67编码
	DH_TALK_AMR_AMR74,							// AMR74编码
	DH_TALK_AMR_AMR795,							// AMR795编码
	DH_TALK_AMR_AMR102,							// AMR102编码
	DH_TALK_AMR_AMR122,							// AMR122编码
} EM_ARM_ENCODE_MODE;

/////////////////////////////////控制相关/////////////////////////////////

// 控制类型，对应CLIENT_ControlDevice接口
typedef enum _CtrlType
{
	DH_CTRL_REBOOT = 0,							// 重启设备	
	DH_CTRL_SHUTDOWN,							// 关闭设备
	DH_CTRL_DISK,								// 硬盘管理
	DH_KEYBOARD_POWER = 3,						// 网络键盘
	DH_KEYBOARD_ENTER,
	DH_KEYBOARD_ESC,
	DH_KEYBOARD_UP,
	DH_KEYBOARD_DOWN,
	DH_KEYBOARD_LEFT,
	DH_KEYBOARD_RIGHT,
	DH_KEYBOARD_BTN0,
	DH_KEYBOARD_BTN1,
	DH_KEYBOARD_BTN2,
	DH_KEYBOARD_BTN3,
	DH_KEYBOARD_BTN4,
	DH_KEYBOARD_BTN5,
	DH_KEYBOARD_BTN6,
	DH_KEYBOARD_BTN7,
	DH_KEYBOARD_BTN8,
	DH_KEYBOARD_BTN9,
	DH_KEYBOARD_BTN10,
	DH_KEYBOARD_BTN11,
	DH_KEYBOARD_BTN12,
	DH_KEYBOARD_BTN13,
	DH_KEYBOARD_BTN14,
	DH_KEYBOARD_BTN15,
	DH_KEYBOARD_BTN16,
	DH_KEYBOARD_SPLIT,
	DH_KEYBOARD_ONE,
	DH_KEYBOARD_NINE,
	DH_KEYBOARD_ADDR,
	DH_KEYBOARD_INFO,
	DH_KEYBOARD_REC,
	DH_KEYBOARD_FN1,
	DH_KEYBOARD_FN2,
	DH_KEYBOARD_PLAY,
	DH_KEYBOARD_STOP,
	DH_KEYBOARD_SLOW,
	DH_KEYBOARD_FAST,
	DH_KEYBOARD_PREW,
	DH_KEYBOARD_NEXT,
	DH_KEYBOARD_JMPDOWN,
	DH_KEYBOARD_JMPUP,
	DH_TRIGGER_ALARM_IN = 100,					// 触发报警输入
	DH_TRIGGER_ALARM_OUT,						// 触发报警输出
	DH_CTRL_MATRIX,								// 矩阵控制
	DH_CTRL_SDCARD,								// SD卡控制(IPC产品)参数同硬盘控制
	DH_BURNING_START,							// 刻录机控制，开始刻录
	DH_BURNING_STOP,							// 刻录机控制，结束刻录
	DH_BURNING_ADDPWD,							// 刻录机控制，叠加密码(以'\0'为结尾的字符串，最大长度8位)
	DH_BURNING_ADDHEAD,							// 刻录机控制，叠加片头(以'\0'为结尾的字符串，最大长度1024字节，支持分行，行分隔符'\n')
	DH_BURNING_ADDSIGN,							// 刻录机控制，叠加打点到刻录信息(参数无)
	DH_BURNING_ADDCURSTOMINFO,					// 刻录机控制，自定义叠加(以'\0'为结尾的字符串，最大长度1024字节，支持分行，行分隔符'\n')
	DH_CTRL_RESTOREDEFAULT,						// 恢复设备的默认设置
	DH_CTRL_CAPTURE_START,						// 触发设备抓图
	DH_CTRL_CLEARLOG,							// 清除日志
	DH_TRIGGER_ALARM_WIRELESS = 200,			// 触发无线报警(IPC产品)
	DH_MARK_IMPORTANT_RECORD,					// 标识重要录像文件
	DH_CTRL_DISK_SUBAREA, 						// 网络硬盘分区	
	DH_BURNING_ATTACH,							// 刻录机控制，附件刻录.
	DH_BURNING_PAUSE,							// 刻录暂停
	DH_BURNING_CONTINUE,						// 刻录继续
	DH_BURNING_POSTPONE,						// 刻录顺延
	DH_CTRL_OEMCTRL,							// 报停控制
	DH_BACKUP_START,							// 设备备份开始
	DH_BACKUP_STOP,								// 设备备份停止
	DH_VIHICLE_WIFI_ADD,						// 车载手动增加WIFI配置
	DH_VIHICLE_WIFI_DEC,						// 车载手动删除WIFI配置
} CtrlType;

// IO控制命令，对应CLIENT_QueryIOControlState接口
typedef enum _IOTYPE
{
	DH_ALARMINPUT = 1,							// 控制报警输入
	DH_ALARMOUTPUT = 2,							// 控制报警输出
	DH_DECODER_ALARMOUT = 3,					// 控制报警解码器输出
	DH_WIRELESS_ALARMOUT = 5,					// 控制无线报警输出
	DH_ALARM_TRIGGER_MODE = 7,					// 报警触发方式（手动,自动,关闭），使用TRIGGER_MODE_CONTROL结构体
} DH_IOTYPE;

/////////////////////////////////配置相关/////////////////////////////////

// 分辨率枚举，供DH_DSP_ENCODECAP使用
typedef enum _CAPTURE_SIZE
{
	CAPTURE_SIZE_D1,							// 704*576(PAL)  704*480(NTSC)
	CAPTURE_SIZE_HD1,							// 352*576(PAL)  352*480(NTSC)
	CAPTURE_SIZE_BCIF,							// 704*288(PAL)  704*240(NTSC)
	CAPTURE_SIZE_CIF,							// 352*288(PAL)  352*240(NTSC)
	CAPTURE_SIZE_QCIF,							// 176*144(PAL)  176*120(NTSC)
	CAPTURE_SIZE_VGA,							// 640*480
	CAPTURE_SIZE_QVGA,							// 320*240
	CAPTURE_SIZE_SVCD,							// 480*480
	CAPTURE_SIZE_QQVGA,							// 160*128
	CAPTURE_SIZE_SVGA,							// 800*592
	CAPTURE_SIZE_XVGA,							// 1024*768
	CAPTURE_SIZE_WXGA,							// 1280*800
	CAPTURE_SIZE_SXGA,							// 1280*1024  
	CAPTURE_SIZE_WSXGA,							// 1600*1024  
	CAPTURE_SIZE_UXGA,							// 1600*1200
	CAPTURE_SIZE_WUXGA,							// 1920*1200
	CAPTURE_SIZE_LTF,							// 240*192
	CAPTURE_SIZE_720,							// 1280*720
	CAPTURE_SIZE_1080,							// 1920*1080
	CAPTURE_SIZE_1_3M,							// 1280*960
	CAPTURE_SIZE_2M,							// 1872*1408
	CAPTURE_SIZE_5M,							// 3744*1408
	CAPTURE_SIZE_NR  
} CAPTURE_SIZE;

// 配置文件类型，供CLIENT_ExportConfigFile接口使用
typedef enum __DH_CONFIG_FILE_TYPE
{
	DH_CONFIGFILE_ALL = 0,						// 全部配置文件
	DH_CONFIGFILE_LOCAL,						// 本地配置文件
	DH_CONFIGFILE_NETWORK,						// 网络配置文件
	DH_CONFIGFILE_USER,							// 用户配置文件
} DH_CONFIG_FILE_TYPE;

// NTP
typedef enum __DH_TIME_ZONE_TYPE
{
	DH_TIME_ZONE_0,								// {0, 0*3600,"GMT+00:00"}
	DH_TIME_ZONE_1,								// {1, 1*3600,"GMT+01:00"}
	DH_TIME_ZONE_2,								// {2, 2*3600,"GMT+02:00"}
	DH_TIME_ZONE_3,								// {3, 3*3600,"GMT+03:00"}
	DH_TIME_ZONE_4,								// {4, 3*3600+1800,"GMT+03:30"}
	DH_TIME_ZONE_5,								// {5, 4*3600,"GMT+04:00"}
	DH_TIME_ZONE_6,								// {6, 4*3600+1800,"GMT+04:30"}
	DH_TIME_ZONE_7,								// {7, 5*3600,"GMT+05:00"}
	DH_TIME_ZONE_8,								// {8, 5*3600+1800,"GMT+05:30"}
	DH_TIME_ZONE_9,								// {9, 5*3600+1800+900,"GMT+05:45"}
	DH_TIME_ZONE_10,							// {10, 6*3600,"GMT+06:00"}
	DH_TIME_ZONE_11,							// {11, 6*3600+1800,"GMT+06:30"}
	DH_TIME_ZONE_12,							// {12, 7*3600,"GMT+07:00"}
	DH_TIME_ZONE_13,							// {13, 8*3600,"GMT+08:00"}
	DH_TIME_ZONE_14,							// {14, 9*3600,"GMT+09:00"}
	DH_TIME_ZONE_15,							// {15, 9*3600+1800,"GMT+09:30"}
	DH_TIME_ZONE_16,							// {16, 10*3600,"GMT+10:00"}
	DH_TIME_ZONE_17,							// {17, 11*3600,"GMT+11:00"}
	DH_TIME_ZONE_18,							// {18, 12*3600,"GMT+12:00"}
	DH_TIME_ZONE_19,							// {19, 13*3600,"GMT+13:00"}
	DH_TIME_ZONE_20,							// {20, -1*3600,"GMT-01:00"}
	DH_TIME_ZONE_21,							// {21, -2*3600,"GMT-02:00"}
	DH_TIME_ZONE_22,							// {22, -3*3600,"GMT-03:00"}
	DH_TIME_ZONE_23,							// {23, -3*3600-1800,"GMT-03:30"}
	DH_TIME_ZONE_24,							// {24, -4*3600,"GMT-04:00"}
	DH_TIME_ZONE_25,							// {25, -5*3600,"GMT-05:00"}
	DH_TIME_ZONE_26,							// {26, -6*3600,"GMT-06:00"}
	DH_TIME_ZONE_27,							// {27, -7*3600,"GMT-07:00"}
	DH_TIME_ZONE_28,							// {28, -8*3600,"GMT-08:00"}
	DH_TIME_ZONE_29,							// {29, -9*3600,"GMT-09:00"}
	DH_TIME_ZONE_30,							// {30, -10*3600,"GMT-10:00"}
	DH_TIME_ZONE_31,							// {31, -11*3600,"GMT-11:00"}
	DH_TIME_ZONE_32,							// {32, -12*3600,"GMT-12:00"}
} DH_TIME_ZONE_TYPE;

typedef enum _SNAP_TYPE
{
	SNAP_TYP_TIMING = 0,
	SNAP_TYP_ALARM,
	SNAP_TYP_NUM,
} SNAP_TYPE;

/////////////////////////////////淘汰类型/////////////////////////////////

// 配置类型，目前使用该枚举的接口已淘汰，请不要使用
typedef enum _CFG_INDEX
{
    CFG_GENERAL = 0,							// 普通
	CFG_COMM,									// 串口
	CFG_NET,									// 网络
	CFG_RECORD,									// 录像
	CFG_CAPTURE,								// 图像设置
	CFG_PTZ,									// 云台
	CFG_DETECT,									// 动态检测
	CFG_ALARM,									// 报警
	CFG_DISPLAY,								// 显示
	CFG_RESERVED,								// 保留，使类型连贯
	CFG_TITLE = 10,								// 通道标题
	CFG_MAIL = 11,								// 邮件功能
	CFG_EXCAPTURE = 12,							// 预览图像设置
	CFG_PPPOE = 13,								// pppoe设置
	CFG_DDNS = 14,								// DDNS设置
	CFG_SNIFFER	= 15,							// 网络监视捕获设置
	CFG_DSPINFO	= 16,							// 编码能力信息
	CFG_COLOR = 126,							// 颜色配置信息
	CFG_ALL,									// 保留
} CFG_INDEX;


/************************************************************************
 ** 结构体定义
 ***********************************************************************/
// 时间
typedef struct 
{
	DWORD				dwYear;					// 年
	DWORD				dwMonth;				// 月
	DWORD				dwDay;					// 日
	DWORD				dwHour;					// 时
	DWORD				dwMinute;				// 分
	DWORD				dwSecond;				// 秒
} NET_TIME,*LPNET_TIME;

// 日志信息里的时间定义
typedef struct _DHDEVTIME
{
	DWORD				second		:6;			// 秒	1-60		
	DWORD				minute		:6;			// 分	1-60		
	DWORD				hour		:5;			// 时	1-24		
	DWORD				day			:5;			// 日	1-31		
	DWORD				month		:4;			// 月	1-12		
	DWORD				year		:6;			// 年	2000-2063	
} DHDEVTIME, *LPDHDEVTIME;

// 回调数据(异步接口)
typedef struct __NET_CALLBACK_DATA 
{
	int					nResultCode;			// 返回码；0：成功
	char				*pBuf;					// 接收数据，缓冲是由用户开辟的，从接口形参传入
	int					nRetLen;				// 接收长度
	LONG				lOperateHandle;			// 操作句柄
	void*				userdata;				// 操作对应用户参数
	char				reserved[16];
} NET_CALLBACK_DATA, *LPNET_CALLBACK_DATA;

///////////////////////////////监视相关定义///////////////////////////////

// 回调视频数据帧的帧参数结构体
typedef struct _tagVideoFrameParam
{
	BYTE				encode;					// 编码类型
	BYTE				frametype;				// I = 0, P = 1, B = 2...
	BYTE				format;					// PAL - 0, NTSC - 1
	BYTE				size;					// CIF - 0, HD1 - 1, 2CIF - 2, D1 - 3, VGA - 4, QCIF - 5, QVGA - 6 ,
												// SVCD - 7,QQVGA - 8, SVGA - 9, XVGA - 10,WXGA - 11,SXGA - 12,WSXGA - 13,UXGA - 14,WUXGA - 15, LFT - 16, 720 - 17, 1080 - 18
	DWORD				fourcc;					// 如果是H264编码则总为0，MPEG4这里总是填写FOURCC('X','V','I','D');
	DWORD				reserved;				// 保留
	NET_TIME			struTime;				// 时间信息
} tagVideoFrameParam;

// 回调音频数据帧的帧参数结构体
typedef struct _tagCBPCMDataParam
{
	BYTE				channels;				// 声道数
	BYTE				samples;				// 采样 0 - 8000, 1 - 11025, 2 - 16000, 3 - 22050, 4 - 32000, 5 - 44100, 6 - 48000
	BYTE				depth;					// 采样深度 取值8或者16等。直接表示
	BYTE				param1;					// 0 - 指示无符号，1-指示有符号
	DWORD				reserved;				// 保留
} tagCBPCMDataParam;

// 通道画面字幕叠加的数据结构
typedef struct _DH_CHANNEL_OSDSTRING
{
	BOOL				bEnable;				// 使能
	DWORD				dwPosition[MAX_STRING_LINE_LEN];	//各行字符的位置　用1-9整数表示，与小键盘位置对应
												//		7左上	8上		9右上
												//		4左		5中		6右
												//		1左下	2下		3右下
	char				szStrings[MAX_STRING_LINE_LEN][MAX_PER_STRING_LEN];	// 最多六行字符，每行最多20个字节
} DH_CHANNEL_OSDSTRING;

///////////////////////////////回放相关定义///////////////////////////////

// 录像文件信息
typedef struct
{
    unsigned int		ch;						// 通道号
    char				filename[128];			// 文件名
    unsigned int		size;					// 文件长度
    NET_TIME			starttime;				// 开始时间
    NET_TIME			endtime;				// 结束时间
    unsigned int		driveno;				// 磁盘号(区分网络录像和本地录像的类型，0－127表示本地录像，128表示网络录像)
    unsigned int		startcluster;			// 起始簇号
	BYTE				nRecordFileType;		// 录象文件类型  0：普通录象；1：报警录象；2：移动检测；3：卡号录象；4：图片
	BYTE                bImportantRecID;		// 0:普通录像 1:重要录像
	BYTE                bHint;					// 文件定位索引
	BYTE                bReserved;				// 保留
} NET_RECORDFILE_INFO, *LPNET_RECORDFILE_INFO;

// 最早录像时间
typedef struct  
{
	int					nChnCount;				// 通道数目
	NET_TIME			stuFurthestTime[16];	// 最早录像时间,有效值为前面0 到 (nChnCount-1)个.如果某通道没有录象的话，最早录象时间全为0
	BYTE				bReserved[384];			// 保留字段
} NET_FURTHEST_RECORD_TIME;

///////////////////////////////报警相关定义///////////////////////////////

// 普通报警信息
typedef struct
{
	int					channelcount;
	int					alarminputcount;
	unsigned char		alarm[16];				// 外部报警
	unsigned char		motiondection[16];		// 动态检测
	unsigned char		videolost[16];			// 视频丢失
} NET_CLIENT_STATE;

// 报警IO控制
typedef struct 
{
	unsigned short		index;					// 端口序号
	unsigned short		state;					// 端口状态
} ALARM_CONTROL;

// 触发方式
typedef struct
{
	unsigned short		index;					// 端口序号
	unsigned short		mode;					// 触发方式(0关闭1手动2自动);不设置的通道，sdk默认将保持原来的设置。
	BYTE				bReserved[28];			
} TRIGGER_MODE_CONTROL;

// 报警解码器控制
typedef struct 
{
	int					decoderNo;				// 报警解码器号，从0开始
	unsigned short		alarmChn;				// 报警输出口，从0开始
	unsigned short		alarmState;				// 报警输出状态；1：打开，0：关闭
} DECODER_ALARM_CONTROL;

// 报警上传功能的报警信息
typedef struct  
{
	DWORD				dwAlarmType;			// 报警类型，dwAlarmType = DH_UPLOAD_EVENT时，dwAlarmMask和bAlarmDecoderIndex是无效的
	DWORD				dwAlarmMask;			// 报警信息掩码，按位表示各报警通道状态
	char				szGlobalIP[DH_MAX_IPADDR_LEN];	// 客户端IP地址
	char				szDomainName[DH_MAX_DOMAIN_NAME_LEN];	// 客户端域名
	int					nPort;					// 报警上传时客户端连接的端口
	char				szAlarmOccurTime[DH_ALARM_OCCUR_TIME_LEN];	// 报警发生的时间
	BYTE				bAlarmDecoderIndex;		// 表示第几个报警解码器，dwAlarmType = DH_UPLOAD_DECODER_ALARM 才有效.
	BYTE				bReservedSpace[15];
} NEW_ALARM_UPLOAD;

// 录像状态变化报警信息
typedef struct
{
	int					nChannel;				// 录像通道号
	char				reserved[12];
} ALARM_RECORDING_CHANGED;

/////////////////////////////语音对讲相关定义/////////////////////////////

// 音频格式信息
typedef struct
{
	BYTE				byFormatTag;			// 编码类型，如0：PCM
	WORD				nChannels;				// 声道数
	WORD				wBitsPerSample;			// 采样深度			
	DWORD				nSamplesPerSec;			// 采样率
} DH_AUDIO_FORMAT, *LPDH_AUDIO_FORMAT;

/////////////////////////////用户管理相关定义/////////////////////////////

// 支持用户名最大长度为8位的设备，对应CLIENT_QueryUserInfo和CLIENT_OperateUserInfo接口
// 权限信息
typedef struct _OPR_RIGHT
{
	DWORD				dwID;
	char				name[DH_RIGHT_NAME_LENGTH];
	char				memo[DH_MEMO_LENGTH];
} OPR_RIGHT;

// 用户信息
typedef struct _USER_INFO
{
	DWORD				dwID;
	DWORD				dwGroupID;
	char				name[DH_USER_NAME_LENGTH];
	char				passWord[DH_USER_PSW_LENGTH];
	DWORD				dwRightNum;
	DWORD				rights[DH_MAX_RIGHT_NUM];
	char				memo[DH_MEMO_LENGTH];
	DWORD				dwReusable;				// 是否复用；1：复用，0：不复用
} USER_INFO;

// 用户组信息
typedef struct _USER_GROUP_INFO
{
	DWORD				dwID;
	char				name[DH_USER_NAME_LENGTH];
	DWORD				dwRightNum;
	DWORD				rights[DH_MAX_RIGHT_NUM];
	char				memo[DH_MEMO_LENGTH];
} USER_GROUP_INFO;

// 用户信息表
typedef struct _USER_MANAGE_INFO
{
	DWORD				dwRightNum;				// 权限信息
	OPR_RIGHT			rightList[DH_MAX_RIGHT_NUM];
	DWORD				dwGroupNum;				// 用户组信息
	USER_GROUP_INFO		groupList[DH_MAX_GROUP_NUM];
	DWORD				dwUserNum;				// 用户信息
	USER_INFO			userList[DH_MAX_USER_NUM];
	DWORD				dwSpecial;				// 用户复用能力；1：支持用户复用，0：不支持用户复用
} USER_MANAGE_INFO;

// 支持用户名最大长度为8位或16位的设备，对应扩展接口CLIENT_QueryUserInfoEx和CLIENT_OperateUserInfoEx
#define DH_USER_NAME_LENGTH_EX		16			// 用户名长度
#define DH_USER_PSW_LENGTH_EX		16			// 密码

// 权限信息
typedef struct _OPR_RIGHT_EX
{
	DWORD				dwID;
	char				name[DH_RIGHT_NAME_LENGTH];
	char				memo[DH_MEMO_LENGTH];
} OPR_RIGHT_EX;

// 用户信息
typedef struct _USER_INFO_EX
{
	DWORD				dwID;
	DWORD				dwGroupID;
	char				name[DH_USER_NAME_LENGTH_EX];
	char				passWord[DH_USER_PSW_LENGTH_EX];
	DWORD				dwRightNum;
	DWORD				rights[DH_MAX_RIGHT_NUM];
	char				memo[DH_MEMO_LENGTH];
	DWORD				dwFouctionMask;			// 掩码，0x00000001 - 支持用户复用
	BYTE				byReserve[32];
} USER_INFO_EX;

// 用户组信息
typedef struct _USER_GROUP_INFO_EX
{
	DWORD				dwID;
	char				name[DH_USER_NAME_LENGTH_EX];
	DWORD				dwRightNum;
	DWORD				rights[DH_MAX_RIGHT_NUM];
	char				memo[DH_MEMO_LENGTH];
} USER_GROUP_INFO_EX;

// 用户信息表
typedef struct _USER_MANAGE_INFO_EX
{
	DWORD				dwRightNum;				// 权限信息
	OPR_RIGHT_EX		rightList[DH_MAX_RIGHT_NUM];
	DWORD				dwGroupNum;				// 用户组信息
	USER_GROUP_INFO_EX  groupList[DH_MAX_GROUP_NUM];
	DWORD				dwUserNum;				// 用户信息
	USER_INFO_EX		userList[DH_MAX_USER_NUM];
	DWORD				dwFouctionMask;			// 掩码；0x00000001 - 支持用户复用，0x00000002 - 密码修改需要校验
	BYTE				byNameMaxLength;		// 支持的用户名最大长度
	BYTE				byPSWMaxLength;			// 支持的密码最大长度
	BYTE				byReserve[254];
} USER_MANAGE_INFO_EX;

///////////////////////////////查询相关定义///////////////////////////////

// 设备支持语言种类
typedef struct _DH_LANGUAGE_DEVINFO
{
	DWORD				dwLanguageNum;			// 支持语言个数
	BYTE				byLanguageType[252];	// 枚举值，详见DH_LANGUAGE_TYPE
} DH_DEV_LANGUAGE_INFO, *LPDH_DEV_LANGUAGE_INFO;

// 硬盘信息
typedef struct
{
	DWORD				dwVolume;				// 硬盘的容量
	DWORD				dwFreeSpace;			// 硬盘的剩余空间
	BYTE				dwStatus;				// 硬盘的状态,0-休眠,1-活动,2-故障等；将DWORD拆成四个BYTE
	BYTE				bDiskNum;				// 硬盘号
	BYTE				bSubareaNum;			// 分区号
	BYTE				bSignal;				// 标识，0为本地 1为远程
} NET_DEV_DISKSTATE,*LPNET_DEV_DISKSTATE;

// 设备硬盘信息
typedef struct _DH_HARDDISK_STATE
{
	DWORD				dwDiskNum;				// 个数
	NET_DEV_DISKSTATE	stDisks[DH_MAX_DISKNUM];// 硬盘或分区信息
} DH_HARDDISK_STATE, *LPDH_HARDDISK_STATE;

typedef DH_HARDDISK_STATE	DH_SDCARD_STATE;	// SD卡，数据结构同硬盘信息

// 语音编码信息
typedef struct  
{
	DH_TALK_CODING_TYPE	encodeType;				// 编码类型
	int					nAudioBit;				// 位数，如8或16
	DWORD				dwSampleRate;			// 采样率，如8000或16000
	char				reserved[64];
} DHDEV_TALKDECODE_INFO;

// 设备支持的语音对讲类型
typedef struct 
{
	int					nSupportNum;			// 个数
	DHDEV_TALKDECODE_INFO type[64];				// 编码类型
	char				reserved[64];
} DHDEV_TALKFORMAT_LIST;

// 云台属性信息
#define  NAME_MAX_LEN 16
typedef struct 
{
	DWORD				dwHighMask;				// 操作的掩码高位
	DWORD				dwLowMask;				// 操作的掩码低位
	char				szName[NAME_MAX_LEN];	// 操作的协议名
	WORD				wCamAddrMin;			// 通道地址的最小值
	WORD				wCamAddrMax;			// 通道地址的最大值
	WORD				wMonAddrMin;			// 监视地址的最小值
	WORD				wMonAddrMax;			// 监视地址的最大值
	BYTE				bPresetMin;				// 预置点的最小值
	BYTE				bPresetMax;				// 预置点的最大值
	BYTE				bTourMin;				// 自动巡航线路的最小值
	BYTE				bTourMax;				// 自动巡航线路的最大值
	BYTE				bPatternMin;			// 轨迹线路的最小值
	BYTE				bPatternMax;			// 轨迹线路的最大值
	BYTE				bTileSpeedMin;			// 垂直速度的最小值
	BYTE				bTileSpeedMax;			// 垂直速度的最大值
	BYTE				bPanSpeedMin;			// 水平速度的最小值
	BYTE				bPanSpeedMax;			// 水平速度的最大值
	BYTE				bAuxMin;				// 辅助功能的最小值
	BYTE				bAuxMax;				// 辅助功能的最大值
	int					nInternal;				// 发送命令的时间间隔
	char				cType;					// 协议的类型
	BYTE				bReserved_1;			// 保留
	BYTE				bFuncMask;				// 协议功能掩码,按位表示,置１表示支持,第一位表示内置云台功能，其它７位暂时保留
	BYTE				bReserved_2;
	char				Reserved[4];
} PTZ_OPT_ATTR;

// 刻录机信息
typedef struct _NET_DEV_BURNING
{
	DWORD				dwDriverType;			// 刻录驱动器类型；0：DHFS，1：DISK，2：CDRW
	DWORD				dwBusType;				// 总线类型；0：USB，1：1394，2：IDE
	DWORD				dwTotalSpace;			// 总容量(KB)
	DWORD				dwRemainSpace;			// 剩余容量(KB)
	BYTE				dwDriverName[DH_BURNING_DEV_NAMELEN];	// 刻录驱动器名称
} NET_DEV_BURNING, *LPNET_DEV_BURNING;

// 设备刻录机信息
typedef struct _DH_BURNING_DEVINFO
{
	DWORD				dwDevNum;				// 刻录设备个数
	NET_DEV_BURNING		stDevs[DH_MAX_BURNING_DEV_NUM];	// 各刻录设备信息
} DH_BURNING_DEVINFO, *LPDH_BURNING_DEVINFO;

// 刻录进度
typedef struct _DH_BURNING_PROGRESS
{
	BYTE				bBurning;				// 刻录机状态；0：可以刻录，1：刻录机类型不对，是一个非光盘设备，
												// 2：未找到刻录机，3：有其它光盘在刻录，4：刻录机处于非空闲状态，即在备份、刻录或回放中
	BYTE				bRomType;				// 盘片类型；0：大华文件系统，1：移动硬盘或U盘，2：光盘
	BYTE				bOperateType;			// 操作类型；0：空闲，1：正在备份中，2：正在刻录中，3：正在进行光盘回放
	BYTE				bType;					// 备份或刻录过程状态；0：停止或结束，1：开始，2：出错，3：满，4：正在初始化
	NET_TIME			stTimeStart;			// 开始时间　
	DWORD				dwTimeElapse;			// 已刻录时间(秒)
	DWORD				dwTotalSpace;			// 光盘总容量
	DWORD				dwRemainSpace;			// 光盘剩余容量
	DWORD				dwBurned;				// 已刻录容量
	WORD				dwStatus;				// 保留
	WORD				wChannelMask;			// 正在刻录的通道掩码
} DH_BURNING_PROGRESS, *LPDH_BURNING_PROGRESS;

// 日志信息，对应接口CLIENT_QueryLog接口
typedef struct _DH_LOG_ITEM
{
    DHDEVTIME			time;					// 日期
    unsigned short		type;					// 类型
    unsigned char		reserved;				// 保留
    unsigned char		data;					// 数据
    unsigned char		context[8];				// 内容
} DH_LOG_ITEM, *LPDH_LOG_ITEM;

// 日志信息，对应扩展接口CLIENT_QueryLogEx，参数reserved(int nType=1;reserved=&nType;)
typedef struct _DH_NEWLOG_ITEM
{
	DHDEVTIME			time;					// 日期
	WORD				type;					// 类型
	WORD				data;					// 数据
	char				szOperator[8]; 			// 用户名
	BYTE				context[16];		    // 内容	
} DH_NEWLOG_ITEM, *LPDH_NEWLOG_ITEM;

// 日志信息，对应接口CLIENT_QueryDeviceLog接口
typedef struct _DH_DEVICE_LOG_ITEM
{
	int					nLogType;				// 日志类型
	DHDEVTIME			stuOperateTime;			// 日期
	char				szOperator[16]; 		// 操作者
	BYTE				bReserved[3];
	BYTE				bUnionType;				//  union结构类型,0:szLogContext；1:stuOldLog。
	union
	{
		char			szLogContext[64];		// 日志备注信息
		struct 
		{
			DH_LOG_ITEM		stuLog;				// 旧的日志结构体
			BYTE			bReserved[48];		// 保留
		}stuOldLog;
	};
	char				reserved[16];
} DH_DEVICE_LOG_ITEM, *LPDH_DEVICE_LOG_ITEM;

// 新日志信息结构，对应接口CLIENT_QueryDeviceLog接口
typedef struct _DH_DEVICE_LOG_ITEM_EX
{
	int					nLogType;				// 日志类型
	DHDEVTIME			stuOperateTime;			// 日期
	char				szOperator[16]; 		// 操作者
	BYTE				bReserved[3];
	BYTE				bUnionType;				//  union结构类型,0:szLogContext；1:stuOldLog。
	union
	{
		char			szLogContext[64];		// 日志备注信息
		struct 
		{
			DH_LOG_ITEM		stuLog;				// 旧的日志结构体
			BYTE			bReserved[48];		// 保留
		}stuOldLog;
	};
	char                szOperation[32];        // 具体的操作内容
	char				szDetailContext[1024];  // 详细日志信息描述
} DH_DEVICE_LOG_ITEM_EX, *LPDH_DEVICE_LOG_ITEM_EX;

// 录象日志信息，对应日志结构体里的context
typedef struct _LOG_ITEM_RECORD
{
	DHDEVTIME			time;					// 时间
	BYTE				channel;				// 通道
	BYTE				type;					// 录像类型
	BYTE				reserved[2];
} LOG_ITEM_RECORD, *LPLOG_ITEM_RECORD;

typedef struct _QUERY_DEVICE_LOG_PARAM
{
	DH_LOG_QUERY_TYPE	emLogType;				// 查询日志类型
	NET_TIME			stuStartTime;			// 查询日志的开始时间
	NET_TIME			stuEndTime;				// 查询日志的结束时间
	int					nStartNum;				// 在时间段中从第几条日志开始查询，开始第一次查询可设为0
	int					nEndNum;				// 一次查询中到第几条日志结束,日志返回条数的最大值为1024
	BYTE                nLogStuType;            // 日志数据结构体类型,0:表示DH_DEVICE_LOG_ITEM；1:表示DH_DEVICE_LOG_ITEM_EX
	BYTE				bReserved[47];
} QUERY_DEVICE_LOG_PARAM;

// 设备硬盘里的录象信息
typedef struct __DEV_DISK_RECORD_INFO 
{
	NET_TIME			stuBeginTime;			// 最早录象时间
	NET_TIME			stuEndTime;				// 最近录象时间
	char				reserved[128];
} DEV_DISK_RECORD_INFO;

///////////////////////////////控制相关定义///////////////////////////////

// 硬盘操作
typedef struct _DISKCTRL_PARAM
{
	DWORD				dwSize;					// 结构体大小，版本控制用
	int					nIndex;					// 为硬盘信息结构体DH_HARDDISK_STATE里的数组stDisks下标，从0开始
	int					ctrlType;				// 操作类型，
												// 0 - 清除数据, 1 - 设为读写盘, 2 - 设为只读盘
												// 3 - 设为冗余盘, 4 - 恢复错误, 5 - 设为快照盘，7 - 弹出SD卡（对SD卡操作有效）
} DISKCTRL_PARAM;

typedef struct  
{
	BYTE				bSubareaNum;			// 预分区的个数
	BYTE				bIndex;					// 为硬盘信息结构体DH_HARDDISK_STATE里的数组stDisks下标，从0开始
	BYTE				bSubareaSize[32];		// 分区大小（百分比）
	BYTE				bReserved[30];			// 保留
} DISKCTRL_SUBAREA;

// 报警状态
typedef struct _ALARMCTRL_PARAM
{
	DWORD				dwSize;
	int					nAlarmNo;				// 报警通道号，从0开始
	int					nAction;				// 1：触发报警，0：停止报警
} ALARMCTRL_PARAM;

// 矩阵控制
typedef struct _MATRIXCTRL_PARAM
{
	DWORD				dwSize;
	int					nChannelNo;				// 视频输入号，从0开始
	int					nMatrixNo;				// 矩阵输出号，从0开始
} MATRIXCTRL_PARAM;

// 刻录控制
typedef struct _BURNING_PARM
{
	int					channelMask;			// 通道掩码，按位表示要刻录的通道
	int					devMask;				// 刻录机掩码，根据查询到的刻录机列表，按位表示
} BURNNG_PARM;

// 附件刻录
typedef struct _BURNING_PARM_ATTACH
{
	BOOL				bAttachBurn;			// 是否为附件刻录，0:不是; 1:是
	BYTE				bReserved[12];			// 保留字段
} BURNING_PARM_ATTACH;

///////////////////////////////配置相关定义///////////////////////////////

//-------------------------------设备属性---------------------------------
// 设备信息
typedef struct
{
	BYTE				sSerialNumber[DH_SERIALNO_LEN];	// 序列号
	BYTE				byAlarmInPortNum;		// DVR报警输入个数
	BYTE				byAlarmOutPortNum;		// DVR报警输出个数
	BYTE				byDiskNum;				// DVR硬盘个数
	BYTE				byDVRType;				// DVR类型, 见枚举DHDEV_DEVICE_TYPE
	BYTE				byChanNum;				// DVR通道个数
} NET_DEVICEINFO, *LPNET_DEVICEINFO;

// 设备软件版本信息，高16位表示主版本号，低16位表示次版本号
typedef struct 
{
	DWORD				dwSoftwareVersion;
	DWORD				dwSoftwareBuildDate;
	DWORD				dwDspSoftwareVersion;
	DWORD				dwDspSoftwareBuildDate;
	DWORD				dwPanelVersion;
	DWORD				dwPanelSoftwareBuildDate;
	DWORD				dwHardwareVersion;
	DWORD				dwHardwareDate;
	DWORD				dwWebVersion;
	DWORD				dwWebBuildDate;
} DH_VERSION_INFO, *LPDH_VERSION_INFO;

// 设备软件版本信息，对应CLIENT_QueryDevState接口
typedef struct  
{
	char				szDevSerialNo[DH_DEV_SERIALNO_LEN];	// 序列号
	char				byDevType;				// 设备类型，见枚举DHDEV_DEVICE_TYPE
	char				szDevType[DH_DEV_TYPE_LEN];	// 设备详细型号，字符串格式，可能为空
	int					nProtocalVer;			// 协议版本号
	char				szSoftWareVersion[DH_MAX_URL_LEN];
	DWORD				dwSoftwareBuildDate;
	char				szDspSoftwareVersion[DH_MAX_URL_LEN];
	DWORD				dwDspSoftwareBuildDate;
	char				szPanelVersion[DH_MAX_URL_LEN];
	DWORD				dwPanelSoftwareBuildDate;
	char				szHardwareVersion[DH_MAX_URL_LEN];
	DWORD				dwHardwareDate;
	char				szWebVersion[DH_MAX_URL_LEN];
	DWORD				dwWebBuildDate;
	char				reserved[256];
} DHDEV_VERSION_INFO;

// DSP能力描述，对应CLIENT_GetDevConfig接口
typedef struct 
{
	DWORD				dwVideoStandardMask;	// 视频制式掩码，按位表示设备能够支持的视频制式
	DWORD				dwImageSizeMask;		// 分辨率掩码，按位表示设备能够支持的分辨率设置
	DWORD				dwEncodeModeMask;		// 编码模式掩码，按位表示设备能够支持的编码模式设置	
	DWORD				dwStreamCap;			// 按位表示设备支持的多媒体功能，
												// 第一位表示支持主码流
												// 第二位表示支持辅码流1
												// 第三位表示支持辅码流2
												// 第五位表示支持jpg抓图
	DWORD				dwImageSizeMask_Assi[8];// 表示主码流为各分辨率时，支持的辅码流分辨率掩码。
	DWORD				dwMaxEncodePower;		// DSP支持的最高编码能力 
	WORD				wMaxSupportChannel;		// 每块DSP支持最多输入视频通道数 
	WORD				wChannelMaxSetSync;		// DSP每通道的最大编码设置是否同步；0：不同步，1：同步
} DH_DSP_ENCODECAP, *LPDH_DSP_ENCODECAP;

// DSP能力描述，扩展类型，对应CLIENT_QueryDevState接口
typedef struct 
{
	DWORD				dwVideoStandardMask;	// 视频制式掩码，按位表示设备能够支持的视频制式
	DWORD				dwImageSizeMask;		// 分辨率掩码，按位表示设备能够支持的分辨率
	DWORD				dwEncodeModeMask;		// 编码模式掩码，按位表示设备能够支持的编码模式
	DWORD				dwStreamCap;			// 按位表示设备支持的多媒体功能，
												// 第一位表示支持主码流
												// 第二位表示支持辅码流1
												// 第三位表示支持辅码流2
												// 第五位表示支持jpg抓图
	DWORD				dwImageSizeMask_Assi[32];// 表示主码流为各分辨率时，支持的辅码流分辨率掩码。
	DWORD				dwMaxEncodePower;		// DSP支持的最高编码能力 
	WORD				wMaxSupportChannel;		// 每块DSP支持最多输入视频通道数 
	WORD				wChannelMaxSetSync;		// DSP每通道的最大编码设置是否同步；0：不同步，1：同步
	BYTE				bMaxFrameOfImageSize[32];// 不同分辨率下的最大采集帧率，与dwVideoStandardMask按位对应
	BYTE				bEncodeCap;				// 标志，配置时要求符合下面条件，否则配置不能生效；
												// 0：主码流的编码能力+辅码流的编码能力 <= 设备的编码能力，
												// 1：主码流的编码能力+辅码流的编码能力 <= 设备的编码能力，
												// 辅码流的编码能力 <= 主码流的编码能力，
												// 辅码流的分辨率 <= 主码流的分辨率，
												// 主码流和辅码流的帧率 <= 前端视频采集帧率
												// 2：N5的计算方法
												// 辅码流的分辨率 <= 主码流的分辨率
												// 查询支持的分辨率和相应最大帧率
	char				reserved[95];
} DHDEV_DSP_ENCODECAP, *LPDHDEV_DSP_ENCODECAP;

// 系统信息
typedef struct 
{
	DWORD				dwSize;
	/* 下面是设备的只读部分 */
	DH_VERSION_INFO		stVersion;
	DH_DSP_ENCODECAP	stDspEncodeCap;			// DSP能力描述
	BYTE				szDevSerialNo[DH_DEV_SERIALNO_LEN];	// 序列号
	BYTE				byDevType;				// 设备类型，见枚举DHDEV_DEVICE_TYPE
	BYTE				szDevType[DH_DEV_TYPE_LEN];	// 设备详细型号，字符串格式，可能为空
	BYTE				byVideoCaptureNum;		// 视频口数量
	BYTE				byAudioCaptureNum;		// 音频口数量
	BYTE				byTalkInChanNum;		// NSP
	BYTE				byTalkOutChanNum;		// NSP
	BYTE				byDecodeChanNum;		// NSP
	BYTE				byAlarmInNum;			// 报警输入口数
	BYTE				byAlarmOutNum;			// 报警输出口数
	BYTE				byNetIONum;				// 网络口数
	BYTE				byUsbIONum;				// USB口数量
	BYTE				byIdeIONum;				// IDE数量
	BYTE				byComIONum;				// 串口数量
	BYTE				byLPTIONum;				// 并口数量
	BYTE				byVgaIONum;				// NSP
	BYTE				byIdeControlNum;		// NSP
	BYTE				byIdeControlType;		// NSP
	BYTE				byCapability;			// NSP，扩展描述
	BYTE				byMatrixOutNum;			// 视频矩阵输出口数
	/* 下面是设备的可写部分 */
	BYTE				byOverWrite;			// 硬盘满处理方式(覆盖、停止)
	BYTE				byRecordLen;			// 录象打包长度
	BYTE				byDSTEnable;			// 是否实行夏令时 1-实行 0-不实行
	WORD				wDevNo;					// 设备编号，用于遥控
	BYTE				byVideoStandard;		// 视频制式:0-PAL,1-NTSC
	BYTE				byDateFormat;			// 日期格式
	BYTE				byDateSprtr;			// 日期分割符(0："."，1："-"，2："/")
	BYTE				byTimeFmt;				// 时间格式 (0-24小时，1－12小时)
	BYTE				byLanguage;				// 枚举值详见DH_LANGUAGE_TYPE
} DHDEV_SYSTEM_ATTR_CFG, *LPDHDEV_SYSTEM_ATTR_CFG;

// 修改设备配置返回信息
typedef struct
{
	DWORD				dwType;					// 类型(即GetDevConfig和SetDevConfig的类型)
	WORD				wResultCode;			// 返回码；0：成功，1：失败，2：数据不合法，3：暂时无法设置，4：没有权限
	WORD   				wRebootSign;			// 重启标志；0：不需要重启，1：需要重启才生效
	DWORD				dwReserved[2];			// 保留	
} DEV_SET_RESULT;

//DST(夏令时)配置
typedef struct  
{
	int					nYear;					// 年[200 - 2037]
	int					nMonth;					// 月[1 - 12]
	int					nHour;					// 小时 [0 - 23]
	int					nMinute;				// 分钟 [0 - 59]
	int					nWeekOrDay;				// [-1 - 4]0:表示使用按日期计算的方法
												// 1: 按周计算: 第一周,2: 第二周,3: 第三周,4: 第四周,-1: 最后一周
	union
	{
		int				iWeekDay;				// 周[0 - 6](nWeekOrDay：按周计算时)0:星期日, 1:星期一, 2:星期二,3:星期三,4:星期四,5:星期五,6:星期六
		int				iDay;					// 日期[1 - 31] (nWeekOrDay：按日期计算)
	};
	
	DWORD				dwReserved[8];			// 保留	
}DH_DST_POINT;

typedef struct  
{
	DWORD				dwSize;
	int					nDSTType;				// 夏令时定位方式 0:按日期定位方式, 1:按周定位方式
	DH_DST_POINT        stDSTStart;             // 开始夏令时
	DH_DST_POINT        stDSTEnd;				// 结束夏令时
	DWORD				dwReserved[16];			// 保留	
}DHDEV_DST_CFG;


// 自动维护配置
typedef struct
{
	DWORD				dwSize;
	BYTE				byAutoRebootDay;		// 自动重启；0：从不, 1：每天，2：每星期日，3：每星期一，......
	BYTE				byAutoRebootTime;		// 0：0:00，1：1:00，......23：23:00
	BYTE				byAutoDeleteFilesTime;	// 自动删除文件；0：从不，1：24H，2：48H，3：72H，4：96H，5：ONE WEEK，6：ONE MONTH
	BYTE				reserved[13];			// 保留位
} DHDEV_AUTOMT_CFG;

//-----------------------------图像通道属性-------------------------------

// 时间段结构															    
typedef struct 
{
	BOOL				bEnable;				// 当表示录像时间段时，按位表示三个使能，从低位到高位分别表示动检录象、报警录象、普通录象
	int					iBeginHour;
	int					iBeginMin;
	int					iBeginSec;
	int					iEndHour;
	int					iEndMin;
	int					iEndSec;
} DH_TSECT, *LPDH_TSECT;

// 区域；各边距按整长8192的比例
typedef struct {
   long					left;
   long					top;
   long					right;
   long					bottom;
} DH_RECT, *LPDH_RECT;

// 二维空间点
typedef struct {
   int					nx;
   int					ny;
} DH_POINT, *LPDH_POINT;


// OSD属性结构
typedef struct  tagENCODE_WIDGET
{
	DWORD				rgbaFrontground;		// 物件的前景；按字节表示，分别为红、绿、蓝和透明度
	DWORD				rgbaBackground;			// 物件的背景；按字节表示，分别为红、绿、蓝和透明度
	DH_RECT				rcRect;					// 位置
	BYTE				bShow;					// 显示使能
	BYTE				byReserved[3];
} DH_ENCODE_WIDGET, *LPDH_ENCODE_WIDGET;

// 通道音视频属性
typedef struct 
{
	// 视频参数
	BYTE				byVideoEnable;			// 视频使能；1：打开，0：关闭
	BYTE				byBitRateControl;		// 码流控制；参照常量"码流控制"定义
	BYTE				byFramesPerSec;			// 帧率
	BYTE				byEncodeMode;			// 编码模式；参照常量"编码模式"定义
	BYTE				byImageSize;			// 分辨率；参照常量"分辨率"定义
	BYTE				byImageQlty;			// 档次1-6
	WORD				wLimitStream;			// 限码流参数
	// 音频参数
	BYTE				byAudioEnable;			// 音频使能；1：打开，0：关闭
	BYTE				wFormatTag;				// 音频编码类型
	WORD				nChannels;				// 声道数
	WORD				wBitsPerSample;			// 采样深度	
	BYTE				bAudioOverlay;			// 音频叠加使能
	BYTE				bReserved_2;
	DWORD				nSamplesPerSec;			// 采样率
	BYTE				bIFrameInterval;		// I帧间隔帧数量，描述两个I帧之间的P帧个数，0-149
	BYTE				bScanMode;				// NSP
	BYTE				bReserved_3;
	BYTE				bReserved_4;
} DH_VIDEOENC_OPT, *LPDH_VIDEOENC_OPT;

// 画面颜色属性
typedef struct 
{
	DH_TSECT			stSect;
	BYTE				byBrightness;			// 亮度；0-100
	BYTE				byContrast;				// 对比度；0-100
	BYTE				bySaturation;			// 饱和度；0-100
	BYTE				byHue;					// 色度；0-100
	BYTE				byGainEn;				// 增益使能
	BYTE				byGain;					// 增益；0-100
	BYTE				byReserved[2];
} DH_COLOR_CFG, *LPDH_COLOR_CFG;

// 图像通道属性结构体
typedef struct 
{
	//DWORD				dwSize;
	WORD				dwSize;
	BYTE				bNoise;
	BYTE				bReserved;
	char				szChannelName[DH_CHAN_NAME_LEN];
	DH_VIDEOENC_OPT		stMainVideoEncOpt[DH_REC_TYPE_NUM];
	DH_VIDEOENC_OPT		stAssiVideoEncOpt[DH_N_ENCODE_AUX];		
	DH_COLOR_CFG		stColorCfg[DH_N_COL_TSECT];
	DH_ENCODE_WIDGET	stTimeOSD;
	DH_ENCODE_WIDGET	stChannelOSD;
	DH_ENCODE_WIDGET	stBlindCover[DH_N_COVERS];	// 单区域遮挡
	BYTE				byBlindEnable;			// 区域遮盖开关；0x00：不使能遮盖，0x01：仅遮盖设备本地预览，0x10：仅遮盖录像及网络预览，0x11：都遮盖
	BYTE				byBlindMask;			// 区域遮盖掩码；第一位：设备本地预览；第二位：录像(及网络预览) */
	BYTE				bVolume;				// 音量阀值(0~100可调)
	BYTE				bVolumeEnable;			// 音量阀值使能
} DHDEV_CHANNEL_CFG, *LPDHDEV_CHANNEL_CFG;

// 预览图像参数
typedef struct 
{
	DWORD				dwSize;
	DH_VIDEOENC_OPT		stPreView;
	DH_COLOR_CFG		stColorCfg[DH_N_COL_TSECT];
}DHDEV_PREVIEW_CFG;

//-------------------------------串口属性---------------------------------

// 串口基本属性
typedef struct
{
	BYTE				byDataBit;				// 数据位；0：5，1：6，2：7，3：8
	BYTE				byStopBit;				// 停止位；0：1位，1：1.5位，2：2位
	BYTE				byParity;				// 校验位；0：无校验，1：奇校验；2：偶校验
	BYTE				byBaudRate;				// 波特率；0：300，1：600，2：1200，3：2400，4：4800，
												// 5：9600，6：19200，7：38400，8：57600，9：115200
} DH_COMM_PROP;

// 485解码器配置
typedef struct
{ 
	DH_COMM_PROP		struComm;
	BYTE				wProtocol;				// 协议类型，对应"协议名列表"下标
	BYTE				bPTZType;				// 0-兼容，本地云台 1-远程网络云台,通过能力查询(见DEV_ENCODER_CFG)。
	BYTE				wDecoderAddress;		// 解码器地址；0 - 255
	BYTE 				byMartixID;				// 矩阵号
} DH_485_CFG;

// 232串口配置
typedef struct
{
	DH_COMM_PROP		struComm;
	BYTE				byFunction;				// 串口功能，对应"功能名列表"下标
	BYTE				byReserved[3];
} DH_RS232_CFG;

// 串口配置结构体
typedef struct
{
	DWORD				dwSize;

	DWORD				dwDecProListNum;				// 解码器协议个数
	char				DecProName[DH_MAX_DECPRO_LIST_SIZE][DH_MAX_NAME_LEN]; // 协议名列表
	DH_485_CFG			stDecoder[DH_MAX_DECODER_NUM];	// 各解码器当前属性

	DWORD				dw232FuncNameNum;		// 232功能个数
	char				s232FuncName[DH_MAX_232FUNCS][DH_MAX_NAME_LEN];	// 功能名列表
	DH_RS232_CFG		st232[DH_MAX_232_NUM];	// 各232串口当前属性
} DHDEV_COMM_CFG;

// 串口状态
typedef struct
{
	unsigned int		uBeOpened;
	unsigned int		uBaudRate;
	unsigned int		uDataBites;
	unsigned int		uStopBits;
	unsigned int		uParity;
	BYTE				bReserved[32];
} DH_COMM_STATE;

//-------------------------------录象配置---------------------------------

// 定时录象
typedef struct 
{
	DWORD				dwSize;
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];
	BYTE				byPreRecordLen;			// 预录时间，单位是s，0表示不预录
	BYTE				byRedundancyEn;			// 录像冗余开关
	BYTE                byRecordType;           // 录像码流类型：0-主码流 1-辅码流1 2-辅码流2 3-辅码流3
	BYTE				byReserved;
} DHDEV_RECORD_CFG, *LPDH_RECORD_CFG;

// NTP配置
typedef struct  
{
	BOOL				bEnable;				//	是否启用
	int					nHostPort;				//	NTP服务器默认端口为123
	char				szHostIp[32];			//	主机IP
	char				szDomainName[128];		//	域名
	int					nType;					//	不可设置，0：表示IP，1：表示域名，2：表示IP和域名
	int					nUpdateInterval;		//	更新时间(分钟)
	int					nTimeZone;				//	见DH_TIME_ZONE_TYPE
	char				reserved[128];
} DHDEV_NTP_CFG;

// FTP上传配置
typedef struct
{
	struct
	{
		DH_TSECT		struSect;				// 该时间段内的“使能”无效，可忽略
		BOOL			bMdEn;					// 上传动态检测录象
		BOOL			bAlarmEn;				// 上传外部报警录象
		BOOL			bTimerEn;				// 上传普通定时录像
		DWORD			dwRev[4];
	} struPeriod[DH_TIME_SECTION];
} DH_FTP_UPLOAD_CFG;

typedef struct
{
	DWORD				dwSize;
	BOOL				bEnable;							// 是否启用
	char				szHostIp[DH_MAX_IPADDR_LEN];		// 主机IP
	WORD				wHostPort;							// 主机端口
	char				szDirName[DH_FTP_MAX_PATH];			// FTP目录路径
	char				szUserName[DH_FTP_USERNAME_LEN];	// 用户名
	char				szPassword[DH_FTP_PASSWORD_LEN];	// 密码
	int					iFileLen;							// 文件长度
	int					iInterval;							// 相邻文件时间间隔
	DH_FTP_UPLOAD_CFG	struUploadCfg[DH_MAX_CHANNUM][DH_N_WEEKS];
	char 				protocol;							// 0-FTP 1-SMB
	char				NASVer;								// 网络存储服务器版本0=老的FTP(界面上显示时间段)，1=NAS存储(界面上屏蔽时间段)
	DWORD				dwFunctionMask;						// 功能能力掩码，按位表示，低16位(网络存储)依次表示FTP，SMB，NFS，高16位(本地存储)依次为DISK，U
	BYTE 				reserved[124];
} DHDEV_FTP_PROTO_CFG;

//-------------------------------网络配置---------------------------------

// 以太网配置
typedef struct 
{
	char				sDevIPAddr[DH_MAX_IPADDR_LEN];	// DVR IP 地址
	char				sDevIPMask[DH_MAX_IPADDR_LEN];	// DVR IP 地址掩码
	char				sGatewayIP[DH_MAX_IPADDR_LEN];	// 网关地址

	/*
	 * 1：10Mbps 全双工
	 * 2：10Mbps 自适应
	 * 3：10Mbps 半双工
	 * 4：100Mbps 全双工
	 * 5：100Mbps 自适应
	 * 6：100Mbps 半双工
	 * 7：自适应
	 */
	// 为了扩展将DWORD拆成四个
	BYTE				dwNetInterface;			// NSP
	BYTE				bTranMedia;				// 0：有线，1：无线
	BYTE				bValid;					// 按位表示，第一位：1：有效 0：无效；第二位：0：DHCP关闭 1：DHCP使能；第三位：0：不支持DHCP 1：支持DHCP
	BYTE				bDefaultEth;			// 是否作为默认的网卡 1：默认 0：非默认
	char				byMACAddr[DH_MACADDR_LEN];	// MAC地址，只读
} DH_ETHERNET; 

// 远程主机配置
typedef struct 
{
	BYTE				byEnable;				// 连接使能
	BYTE				byAssistant;            // 目前只对于PPPoE服务器有用，0：在有线网卡拨号；1：在无线网卡上拨号
	WORD				wHostPort;				// 远程主机 端口
	char				sHostIPAddr[DH_MAX_IPADDR_LEN];		// 远程主机 IP 地址		
	char				sHostUser[DH_MAX_HOST_NAMELEN];		// 远程主机 用户名
	char				sHostPassword[DH_MAX_HOST_PSWLEN];	// 远程主机 密码
} DH_REMOTE_HOST;

// 邮件配置
typedef struct 
{
	char				sMailIPAddr[DH_MAX_IPADDR_LEN];	// 邮件服务器IP地址
	WORD				wMailPort;				// 邮件服务器端口
	WORD				wReserved;				// 保留
	char				sSenderAddr[DH_MAX_MAIL_ADDR_LEN];	// 发送地址
	char				sUserName[DH_MAX_NAME_LEN];			// 用户名
	char				sUserPsw[DH_MAX_NAME_LEN];			// 用户密码
	char				sDestAddr[DH_MAX_MAIL_ADDR_LEN];	// 目的地址
	char				sCcAddr[DH_MAX_MAIL_ADDR_LEN];		// 抄送地址
	char				sBccAddr[DH_MAX_MAIL_ADDR_LEN];		// 暗抄地址
	char				sSubject[DH_MAX_MAIL_SUBJECT_LEN];	// 标题
} DH_MAIL_CFG;

// 网络配置结构体
typedef struct
{ 
	DWORD				dwSize; 

	char				sDevName[DH_MAX_NAME_LEN];	// 设备主机名

	WORD				wTcpMaxConnectNum;		// TCP最大连接数
	WORD				wTcpPort;				// TCP帧听端口
	WORD				wUdpPort;				// UDP侦听端口
	WORD				wHttpPort;				// HTTP端口号
	WORD				wHttpsPort;				// HTTPS端口号
	WORD				wSslPort;				// SSL端口号
	DH_ETHERNET			stEtherNet[DH_MAX_ETHERNET_NUM];	// 以太网口

	DH_REMOTE_HOST		struAlarmHost;			// 报警服务器
	DH_REMOTE_HOST		struLogHost;			// 日志服务器
	DH_REMOTE_HOST		struSmtpHost;			// SMTP服务器
	DH_REMOTE_HOST		struMultiCast;			// 多播组
	DH_REMOTE_HOST		struNfs;				// NFS服务器
	DH_REMOTE_HOST		struPppoe;				// PPPoE服务器
	char				sPppoeIP[DH_MAX_IPADDR_LEN]; // PPPoE注册返回的IP
	DH_REMOTE_HOST		struDdns;				// DDNS服务器
	char				sDdnsHostName[DH_MAX_HOST_NAMELEN];	// DDNS主机名
	DH_REMOTE_HOST		struDns;				// DNS服务器
	DH_MAIL_CFG			struMail;				// 邮件配置
} DHDEV_NET_CFG;

// 多ddns配置结构体
typedef struct
{
	DWORD				dwId;					// ddns服务器id号
	BOOL				bEnable;				// 使能，同一时间只能有一个ddns服务器处于使能状态
	char				szServerType[DH_MAX_SERVER_TYPE_LEN];	// 服务器类型，希网..
	char				szServerIp[DH_MAX_DOMAIN_NAME_LEN];		// 服务器ip或者域名
	DWORD				dwServerPort;			// 服务器端口
	char				szDomainName[DH_MAX_DOMAIN_NAME_LEN];	// dvr域名，如jeckean.3322.org
	char				szUserName[DH_MAX_HOST_NAMELEN];		// 用户名
	char				szUserPsw[DH_MAX_HOST_PSWLEN];			// 密码
	char				szAlias[DH_MAX_DDNS_ALIAS_LEN];			// 服务器别名，如"dahua inter ddns"
	DWORD				dwAlivePeriod;							// DDNS 保活时间
	char				reserved[256];
} DH_DDNS_SERVER_CFG;

typedef struct
{
	DWORD				dwSize;
	DWORD				dwDdnsServerNum;	
	DH_DDNS_SERVER_CFG	struDdnsServer[DH_MAX_DDNS_NUM];	
} DHDEV_MULTI_DDNS_CFG;

// 邮件配置结构体
typedef struct 
{
	char				sMailIPAddr[DH_MAX_DOMAIN_NAME_LEN];	// 邮件服务器地址(IP或者域名)
	char				sSubMailIPAddr[DH_MAX_DOMAIN_NAME_LEN];
	WORD				wMailPort;								// 邮件服务器端口
	WORD				wSubMailPort;
	WORD				wReserved;								// 保留
	char				sSenderAddr[DH_MAX_MAIL_ADDR_LEN];		// 发送地址
	char				sUserName[DH_MAX_MAIL_NAME_LEN];		// 用户名
	char				sUserPsw[DH_MAX_MAIL_NAME_LEN];			// 用户密码
	char				sDestAddr[DH_MAX_MAIL_ADDR_LEN];		// 目的地址
	char				sCcAddr[DH_MAX_MAIL_ADDR_LEN];			// 抄送地址
	char				sBccAddr[DH_MAX_MAIL_ADDR_LEN];			// 暗抄地址
	char				sSubject[DH_MAX_MAIL_SUBJECT_LEN];		// 标题
	BYTE				bEnable;								// 使能0:false,	1:true
	BYTE				bSSLEnable;								// SSL使能
	WORD				wSendInterval;							// 发送时间间隔,[0,3600]秒
	BYTE				bAnonymous;								// 匿名选项[0,1], 0表示FALSE,1表示TRUE.
	BYTE				bAttachEnable;							// 附件使能[0,1], 0表示FALSE,1表示TRUE.
	char				reserved[154];
} DHDEV_MAIL_CFG;

// DNS服务器配置
typedef struct  
{
	char				szPrimaryIp[DH_MAX_IPADDR_LEN];
	char				szSecondaryIp[DH_MAX_IPADDR_LEN];
	char				reserved[256];
} DHDEV_DNS_CFG;

// 录象下载策略配置
typedef struct
{
	DWORD				dwSize;
	BOOL				bEnable;				// TRUE：高速下载，FALSE：普通下载
}DHDEV_DOWNLOAD_STRATEGY_CFG;

// 网络传输策略配置
typedef struct
{
	DWORD				dwSize;
	BOOL				bEnable;
	int					iStrategy;				// 0：画质优先，1：流畅性优先，2：自动
}DHDEV_TRANSFER_STRATEGY_CFG;

// 设置登入时的相关参数
typedef struct  
{
	int					nWaittime;				// 等待超时时间(毫秒为单位)，为0默认5000ms
	int					nConnectTime;			// 连接超时时间(毫秒为单位)，为0默认1500ms
	int					nConnectTryNum;			// 连接尝试次数，为0默认1次
	int					nSubConnectSpaceTime;	// 子连接之间的等待时间(毫秒为单位)，为0默认10ms
	int					nGetDevInfoTime;		// 获取设备信息超时时间，为0默认1000ms
	int					nConnectBufSize;		// 每个连接接收数据缓冲大小(字节为单位)，为0默认250*1024
	int					nGetConnInfoTime;		// 获取子连接信息超时时间(毫秒为单位)，为0默认1000ms
	BYTE				bReserved[20];			// 保留字段
} NET_PARAM;

// 对应CLIENT_SearchDevices接口
typedef struct 
{
	char				szIP[DH_MAX_IPADDR_LEN];		// IP
	int					nPort;							// 端口
	char				szSubmask[DH_MAX_IPADDR_LEN];	// 子网掩码
	char				szGateway[DH_MAX_IPADDR_LEN];	// 网关
	char				szMac[DH_MACADDR_LEN];			// MAC地址
	char				szDeviceType[DH_DEV_TYPE_LEN];	// 设备类型
	BYTE				bReserved[32];					// 保留字节
} DEVICE_NET_INFO;

//-------------------------------报警属性---------------------------------

// 云台联动
typedef struct 
{
	int					iType;
	int					iValue;
} DH_PTZ_LINK, *LPDH_PTZ_LINK;

// 报警联动结构体
typedef struct 
{
	/* 消息处理方式，可以同时多种处理方式，包括
	 * 0x00000001 - 报警上传
	 * 0x00000002 - 联动录象
	 * 0x00000004 - 云台联动
	 * 0x00000008 - 发送邮件
	 * 0x00000010 - 本地轮巡
	 * 0x00000020 - 本地提示
	 * 0x00000040 - 报警输出
	 * 0x00000080 - Ftp上传
	 * 0x00000100 - 蜂鸣
	 * 0x00000200 - 语音提示
	 * 0x00000400 - 抓图
	*/

	/* 当前报警所支持的处理方式，按位掩码表示 */
	DWORD				dwActionMask;

	/* 触发动作，按位掩码表示，具体动作所需要的参数在各自的配置中体现 */
	DWORD				dwActionFlag;
	
	/* 报警触发的输出通道，报警触发的输出，为1表示触发该输出 */ 
	BYTE				byRelAlarmOut[DH_MAX_ALARMOUT_NUM];
	DWORD				dwDuration;				/* 报警持续时间 */

	/* 联动录象 */
	BYTE				byRecordChannel[DH_MAX_VIDEO_IN_NUM]; /* 报警触发的录象通道，为1表示触发该通道 */
	DWORD				dwRecLatch;				/* 录象持续时间 */

	/* 抓图通道 */
	BYTE				bySnap[DH_MAX_VIDEO_IN_NUM];
	/* 轮巡通道 */
	BYTE				byTour[DH_MAX_VIDEO_IN_NUM];

	/* 云台联动 */
	DH_PTZ_LINK			struPtzLink[DH_MAX_VIDEO_IN_NUM];
	DWORD				dwEventLatch;			/* 联动开始延时时间，s为单位，范围是0~15，默认值是0 */
	/* 报警触发的无线输出通道，报警触发的输出，为1表示触发该输出 */ 
	BYTE				byRelWIAlarmOut[DH_MAX_ALARMOUT_NUM];
	BYTE				bMessageToNet;
	BYTE                bMMSEn;                /*短信报警使能*/
	BYTE                bySnapshotTimes;       /*短信发送抓图张数 */
	BYTE				bMatrixEn;				/*!< 矩阵使能 */
	DWORD				dwMatrix;				/*!< 矩阵掩码 */			
	BYTE				bLog;					/*!< 日志使能，目前只有在WTN动态检测中使用 */
	BYTE				bSnapshotPeriod;		/*!<抓图帧间隔，每隔多少帧抓一张图片，一定时间内抓拍的张数还与抓图帧率有关。0表示不隔帧，连续抓拍。*/
	BYTE				byReserved[102];   
} DH_MSG_HANDLE;

// 外部报警
typedef struct
{
	BYTE				byAlarmType;			// 报警器类型，0：常闭，1：常开
	BYTE				byAlarmEn;				// 报警使能
	BYTE				byReserved[2];						
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE		struHandle;				// 处理方式
} DH_ALARMIN_CFG, *LPDHDEV_ALARMIN_CFG; 


// 动态检测报警
typedef struct 
{
	BYTE				byMotionEn;				// 动态检测报警使能
	BYTE				byReserved;
	WORD				wSenseLevel;			// 灵敏度
	WORD				wMotionRow;				// 动态检测区域的行数
	WORD				wMotionCol;				// 动态检测区域的列数
	BYTE				byDetected[DH_MOTION_ROW][DH_MOTION_COL]; // 检测区域，最多32*32块区域
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE		struHandle;				//处理方式
} DH_MOTION_DETECT_CFG;

// 视频丢失报警
typedef struct
{
	BYTE				byAlarmEn;				// 视频丢失报警使能
	BYTE				byReserved[3];
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE		struHandle;				// 处理方式
} DH_VIDEO_LOST_CFG;

// 图像遮挡报警
typedef struct
{
	BYTE				byBlindEnable;			// 使能
	BYTE				byBlindLevel;			// 灵敏度1-6
	BYTE				byReserved[2];
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE		struHandle;				// 处理方式
} DH_BLIND_CFG;

// 硬盘消息(内部报警)
typedef struct 
{
	BYTE				byNoDiskEn;				// 无硬盘时报警
	BYTE				byReserved_1[3];
	DH_TSECT			stNDSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE		struNDHandle;			// 处理方式

	BYTE				byLowCapEn;				// 硬盘低容量时报警
	BYTE				byLowerLimit;			// 容量阀值，0-99
	BYTE				byReserved_2[2];
	DH_TSECT			stLCSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE		struLCHandle;			// 处理方式

	BYTE				byDiskErrEn;			// 硬盘故障报警
	BYTE				bDiskNum;
	BYTE				byReserved_3[2];
	DH_TSECT			stEDSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE		struEDHandle;			// 处理方式
} DH_DISK_ALARM_CFG;

typedef struct
{
	BYTE				byEnable;
	BYTE				byReserved[3];
	DH_MSG_HANDLE		struHandle;
} DH_NETBROKEN_ALARM_CFG;

// 报警布防
typedef struct
{
	DWORD dwSize;
	DH_ALARMIN_CFG 		struLocalAlmIn[DH_MAX_ALARM_IN_NUM];
	DH_ALARMIN_CFG		struNetAlmIn[DH_MAX_ALARM_IN_NUM];
	DH_MOTION_DETECT_CFG struMotion[DH_MAX_VIDEO_IN_NUM];
	DH_VIDEO_LOST_CFG	struVideoLost[DH_MAX_VIDEO_IN_NUM];
	DH_BLIND_CFG		struBlind[DH_MAX_VIDEO_IN_NUM];
	DH_DISK_ALARM_CFG	struDiskAlarm;
	DH_NETBROKEN_ALARM_CFG	struNetBrokenAlarm;
} DHDEV_ALARM_SCHEDULE;

#define DECODER_OUT_SLOTS_MAX_NUM 		16
#define DECODER_IN_SLOTS_MAX_NUM 		16

// 报警解码器配置
typedef struct  
{
	DWORD				dwAddr;									// 报警解码器地址
	BOOL				bEnable;								// 报警解码器使能
	DWORD				dwOutSlots[DECODER_OUT_SLOTS_MAX_NUM];	// 现在只支持8个.
	int					nOutSlotNum;							// dwOutSlots数组有效元素个数.
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];
	DH_MSG_HANDLE		struHandle[DECODER_IN_SLOTS_MAX_NUM];	// 现在只支持8个.
	int					nMsgHandleNum;							// stuHandle数组有效元素个数.
	BYTE				bReserved[120];
} DH_ALARMDEC_CFG;

// 报警上传的配置
typedef struct  
{
	BYTE				byEnable;				// 上传使能
	BYTE				bReserverd;				// 保留
	WORD				wHostPort;				// 报警中心侦听端口
	char				sHostIPAddr[DH_MAX_IPADDR_LEN];		// 报警中心IP

	int					nByTimeEn;				// 定时上传使能，可以用来向中心上传IP或域名等
	int					nUploadDay;				/* 设置上传日期	
													"Never = 0", "Everyday = 1", "Sunday = 2", 
													"Monday = 3", Tuesday = 4", "Wednesday = 5",
													"Thursday = 6", "Friday = 7", "Saturday = 8"*/	
	int					nUploadHour;			// 设置上传时间 ,[0~23]点
	
	DWORD				dwReserved[300]; 		// 保留待扩展。
} ALARMCENTER_UP_CFG;

// 全景切换报警配置
typedef struct __DH_PANORAMA_SWITCH_CFG 
{
	BOOL				bEnable;				// 使能
	int					nReserved[5];			// 保留
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];
	DH_MSG_HANDLE		struHandle;				// 报警联动
} DH_PANORAMA_SWITCH_CFG;

typedef struct __ALARM_PANORAMA_SWITCH_CFG 
{
	int					nAlarmChnNum;			// 报警通道个数
	DH_PANORAMA_SWITCH_CFG stuPanoramaSwitch[DH_MAX_VIDEO_IN_NUM];
} ALARM_PANORAMA_SWITCH_CFG;

// 失去焦点报警配置
typedef struct __DH_LOST_FOCUS_CFG
{
	BOOL				bEnable;				// 使能
	int					nReserved[5];			// 保留
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];
	DH_MSG_HANDLE		struHandle;				// 报警联动
} DH_LOST_FOCUS_CFG;

typedef struct __ALARM_LOST_FOCUS_CFG 
{
	int					nAlarmChnNum;			// 报警通道个数
	DH_LOST_FOCUS_CFG stuLostFocus[DH_MAX_VIDEO_IN_NUM];
} ALARM_LOST_FOCUS_CFG;

// IP冲突检测报警配置
typedef struct __ALARM_IP_COLLISION_CFG
{
	BOOL				bEnable;				// 使能
	DH_MSG_HANDLE		struHandle;				// 报警联动
	int                 nReserved[300];			// 保留
} ALARM_IP_COLLISION_CFG;

//------------------------------多区域遮挡--------------------------------

// 遮挡信息
typedef struct __VIDEO_COVER_ATTR
{
	DH_RECT				rcBlock;				// 覆盖的区域坐标
	int					nColor;					// 覆盖的颜色
	BYTE				bBlockType;				// 覆盖方式；0：黑块，1：马赛克
	BYTE				bEncode;				// 编码级遮挡；1：生效，0：不生效
	BYTE				bPriview;				// 预览遮挡； 1：生效，0：不生效
	char				reserved[29];			// 保留
} VIDEO_COVER_ATTR;

// 多区域遮挡配置
typedef struct __DHDEV_VIDEOCOVER_CFG 
{
	DWORD				dwSize;
	char				szChannelName[DH_CHAN_NAME_LEN]; // 只读
	BYTE				bTotalBlocks;			// 支持的遮挡块数
	BYTE				bCoverCount;			// 已设置的遮挡块数
	VIDEO_COVER_ATTR	CoverBlock[DH_MAX_VIDEO_COVER_NUM]; // 覆盖的区域	
	char				reserved[30];			// 保留
}DHDEV_VIDEOCOVER_CFG;

////////////////////////////////IPC产品支持////////////////////////////////

// 配置无线网络信息
typedef struct 
{
	int					nEnable;				// 无线使能
	char				szSSID[36];				// SSID
	int					nLinkMode;				// 连接模式；0：auto，1：adhoc，2：Infrastructure
	int					nEncryption;			// 加密；0：off，2：WEP64bit，3：WEP128bit, 4:WPA-PSK-TKIP, 5: WPA-PSK-CCMP
	int					nKeyType;				// 0：Hex，1：ASCII
    int					nKeyID;					// 序号
	union
	{
		char			szKeys[4][32];			// 四组密码
		char			szWPAKeys[128];			// nEncryption为4、5时使用，传128长度，不用结束符。
	};
	int					nKeyFlag;
	char				reserved[12];
} DHDEV_WLAN_INFO;

// 选择使用某个无线设备
typedef struct  
{
	char				szSSID[36];
	int					nLinkMode;				// 连接模式；0：adhoc，1：Infrastructure
	int 				nEncryption;			// 加密；0：off，2：WEP64bit，3：WEP128bit
	char				reserved[48];
} DHDEV_WLAN_DEVICE;

// 搜索到的无线设备列表
typedef struct  
{
	DWORD				dwSize;
	BYTE				bWlanDevCount;			// 搜索到的无线设备个数
	DHDEV_WLAN_DEVICE	lstWlanDev[DH_MAX_WLANDEVICE_NUM];
	char				reserved[255];
} DHDEV_WLAN_DEVICE_LIST;

// 主动注册参数配置
typedef struct  
{
	char				szServerIp[32];			// 注册服务器IP
	int					nServerPort;			// 端口号
	char				reserved[64];
} DHDEV_SERVER_INFO;

typedef struct  
{
	DWORD				dwSize;
	BYTE				bServerNum;				// 支持的最大ip数
	DHDEV_SERVER_INFO	lstServer[DH_MAX_REGISTER_SERVER_NUM];
	BYTE				bEnable;				// 使能
	char				szDeviceID[32];			// 设备id
	char				reserved[94];
} DHDEV_REGISTER_SERVER;

// 摄像头属性
typedef struct __DHDEV_CAMERA_INFO
{
	BYTE				bBrightnessEn;			// 亮度可调；1：可，0：不可
	BYTE				bContrastEn;			// 对比度可调
	BYTE				bColorEn;				// 色度可调
	BYTE				bGainEn;				// 增益可调
	BYTE				bSaturationEn;			// 饱和度可调
	BYTE				bBacklightEn;			// 背光补偿 0表示不支持背光补偿,1表示支持一级补偿（开,关），2表示支持两级补偿（关,高,低），3表示支持三级补偿（关,高,中,低）
	BYTE				bExposureEn;			// 曝光选择:
												// 0:表示不支持曝光控制
												// 1:表示只支持自动曝光
												// n:曝光的等级数(1表示支持自动曝光 2~n表示支持的手动控制曝光的等级)
	BYTE				bColorConvEn;			// 自动彩黑转换可调
	BYTE				bAttrEn;				// 属性选项；1：可，0：不可
	BYTE				bMirrorEn;				// 镜像；1：支持，0：不支持
    BYTE				bFlipEn;				// 翻转；1：支持，0：不支持
	BYTE				iWhiteBalance;			// 白平衡 0-不支持白平衡，1-支持自动白平衡，2-支持预置白平衡（即情景模式） 3-支持自定义白平衡
	BYTE				iSignalFormatMask;		// 信号格式掩码，按位从低到高位分别为：0-Inside(内部输入) 1- BT656 2-720p 3-1080i  4-1080p  5-1080sF
	BYTE				bRotate90;				// 90度旋转 0-不支持 1-支持
    BYTE				bLimitedAutoExposure;   // 是否支持带时间上下限的自动曝光
    BYTE				bCustomManualExposure;  // 是否支持用户自定义手动曝光时间
	BYTE				bFlashAdjustEn;         // 是否支持闪光灯调节
	BYTE				bNightOptions;			// 是否支持夜晚选项
	BYTE                iReferenceLevel;    	// 是否支持参考电平设置   
	BYTE				bRev[117];				// 保留
} DHDEV_CAMERA_INFO;

//夜晚特殊配置选项，在晚上光线较暗时自动切换到夜晚的配置参数
typedef struct __DHDEV_NIGHTOPTIONS 
{
	BYTE  bEnable;								// 0-不切换，1-切换 
												// 大致日出和日落时间，日落之后日出之前，将采用夜晚特殊的配置。
												// 00:00:00 ~23:59:59
	BYTE  bSunriseHour;
	BYTE  bSunriseMinute;
	BYTE  bSunriseSecond;
	BYTE  bSunsetHour;
	BYTE  bSunsetMinute;
	BYTE  bSunsetSecond;  
	BYTE  bWhiteBalance ;						// 白平衡 0:Disabled,1:Auto 2:sunny 3:cloudy 4:home 5:office 6:night 7: Custom
	BYTE  bGainRed;								// 红色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE  bGainBlue;							// 绿色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE  bGainGreen;							// 蓝色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE  bGain;								// 0~100
	BYTE  bGainAuto;							// 0-不自动增益 1-自动增益
	BYTE  bBrightnessThreshold ;				// 亮度值 0~100
	BYTE  ReferenceLevel;                       // 电平参考值 0~100   
	BYTE  bExposureSpeed;						// 取值范围取决于设备能力集：0-自动曝光 1~n-1-手动曝光等级 n-带时间上下限的自动曝光 n+1-自定义时间手动曝光 (n表示支持的曝光等级数）
	float ExposureValue1;						// 自动曝光时间下限或者手动曝光自定义时间,毫秒为单位，取值0.1ms~80ms
	float ExposureValue2;						// 自动曝光时间上限,毫秒为单位，取值0.1ms~80ms
	BYTE res[16];								// 保留
} DHDEV_NIGHTOPTIONS;

// 摄像头属性配置
typedef struct __DHDEV_CAMERA_CFG 
{
	DWORD				dwSize;
	BYTE				bExposure;				// 曝光模式；取值范围取决于设备能力集：0-自动曝光，1-曝光等级1，2-曝光等级2…n-1最大曝光等级数 n带时间上下限的自动曝光 n+1自定义时间手动曝光 (n==bExposureEn）
	BYTE				bBacklight;				// 背光补偿：背光补偿等级取值范围取决于设备能力集，0-关闭，1-背光补偿强度1，2-背光补偿强度2…n-最大背光补偿等级数 
	BYTE				bAutoColor2BW;			// 日/夜模式；3-根据时间自动切换 2：开(黑白)，1：根据亮度启动切换，0：关(彩色)
	BYTE				bMirror;				// 镜像；1：开，0：关
	BYTE				bFlip;					// 翻转；1：开，0：关
	BYTE				bLensEn;				// 自动光圈功能能力: 1：支持；0 ：不支持
	BYTE				bLensFunction;			// 自动光圈功能: 1:开启自动光圈；0: 关闭自动光圈
	BYTE				bWhiteBalance;			// 白平衡 0:Disabled,1:Auto 2:sunny 3:cloudy 4:home 5:office 6:night 7: Custom
	BYTE				bSignalFormat;			// 信号格式0-Inside(内部输入) 1- BT656 2-720p 3-1080i  4-1080p  5-1080sF
	BYTE				bRotate90;				// 0-不旋转，1-顺时针90°，2-逆时针90°
	BYTE                bReferenceLevel;         // 电平参考值 0~100  
	BYTE                byReserve;              // 保留
	float				ExposureValue1;			// 自动曝光时间下限或者手动曝光自定义时间,毫秒为单位，取值0.1ms~80ms
	float				ExposureValue2;			// 自动曝光时间上限,毫秒为单位，取值0.1ms~80ms	
	DHDEV_NIGHTOPTIONS	stuNightOptions;		// 夜晚配置参数选项 
	BYTE				bGainRed;				// 红色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				bGainBlue;				// 绿色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				bGainGreen;				// 蓝色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				bFlashMode;				// 闪光灯工作模式，0-自动闪光，1-始终，2-根据亮度切换闪光
	BYTE				bFlashValue;			// 闪光灯工作值, 0-0us, 1-50us, 2-90us, 3-140us, 4-180us, 5-230us, 6-270us, 7-320us 8-亮度预设值，模式为2时有效
	BYTE				bFlashPole;				// 闪光灯触发模式0-低电平 1-高电平
	char				bRev[62];				// 保留
} DHDEV_CAMERA_CFG;

#define ALARM_MAX_NAME 64
// (无线)红外报警配置
typedef struct
{
	BOOL				bEnable;				// 报警输入使能
	char				szAlarmName[DH_MAX_ALARM_NAME];	// 报警输入名称
	int					nAlarmInPattern;		// 报警器输入波形
	int					nAlarmOutPattern;		// 报警输出波形
	char				szAlarmInAddress[DH_MAX_ALARM_NAME];// 报警输入地址
	int					nSensorType;			// 外部设备传感器类型常开 or 常闭
	int					nDefendEfectTime;		// 布撤防延时时间，在此时间后该报警输入有效
	int					nDefendAreaType;		// 防区类型 
	int					nAlarmSmoothTime;		// 报警平滑时间，即在此时间内如果只有一个报警输入连续输入两次则忽略掉后面一次
	char				reserved[128];
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];
	DH_MSG_HANDLE		struHandle;				// 处理方式
} DH_INFRARED_INFO;

// 无线遥控器配置
typedef struct 
{
	BYTE				address[ALARM_MAX_NAME];// 遥控器地址
	BYTE				name[ALARM_MAX_NAME];	// 遥控器名称
	BYTE				reserved[32];			// 保留字段
} DH_WI_CONFIG_ROBOT;

// 无线报警输出配置
typedef struct 
{
	BYTE				address[ALARM_MAX_NAME];// 报警输出地址
	BYTE				name[ALARM_MAX_NAME];	// 报警输出名称
	BYTE				reserved[32];			// 保留字段
} DH_WI_CONFIG_ALARM_OUT;

typedef struct  
{
	DWORD				dwSize;
	BYTE				bAlarmInNum;			// 无线报警输入数
	BYTE				bAlarmOutNum;			// 无线报警输出数
	DH_WI_CONFIG_ALARM_OUT AlarmOutAddr[16];	// 报警输出地址
	BYTE				bRobotNum;				// 遥控器个数
	DH_WI_CONFIG_ROBOT RobotAddr[16];			// 遥控器地址
	DH_INFRARED_INFO	InfraredAlarm[16];
	char				reserved[256];
} DH_INFRARED_CFG;

// 新音频检测报警信息
typedef struct
{
	int					channel;				// 报警通道号
	int					alarmType;				// 报警类型；0：音频值过低，1：音频值过高
	unsigned int		volume;					// 音量值
	char				reserved[256];
} NET_NEW_SOUND_ALARM_STATE;

typedef struct  
{
	int					channelcount;			// 报警的通道个数
	NET_NEW_SOUND_ALARM_STATE SoundAlarmInfo[DH_MAX_ALARM_IN_NUM];
} DH_NEW_SOUND_ALARM_STATE;

// 抓图功能属性结构体
typedef struct 
{
	int					nChannelNum;			// 通道号
	DWORD				dwVideoStandardMask;	// 分辨率(按位)，具体查看枚举CAPTURE_SIZE						
	int					nFramesCount;			// Frequence[128]数组的有效长度
	char				Frames[128];			// 帧率(按数值)
												// -25：25秒1帧；-24：24秒1帧；-23：23秒1帧；-22：22秒1帧
												// ……
												// 0：无效；1：1秒1帧；2：1秒2帧；3：1秒3帧
												// 4：1秒4帧；5：1秒5帧；17：1秒17帧；18：1秒18帧
												// 19：1秒19帧；20：1秒20帧
												// ……
												// 25: 1秒25帧
	int					nSnapModeCount;			// SnapMode[16]数组的有效长度
	char				SnapMode[16];			// (按数值)0：定时触发抓图，1：手动触发抓图
	int					nPicFormatCount;		// Format[16]数组的有效长度
	char 				PictureFormat[16];		// (按数值)0：BMP格式，1：JPG格式
	int					nPicQualityCount;		// Quality[32]数组的有效长度
	char 				PictureQuality[32];		// 按数值
												// 100：图象质量100%；80:图象质量80%；60:图象质量60%
												// 50:图象质量50%；30:图象质量30%；10:图象质量10%
	char 				nReserved[128];			// 保留
} DH_QUERY_SNAP_INFO;

typedef struct 
{
	int					nChannelCount;			// 通道个数
	DH_QUERY_SNAP_INFO  stuSnap[DH_MAX_CHANNUM];
} DH_SNAP_ATTR_EN;


/* IP过滤功能配置 */
#define DH_IPIFILTER_NUM			200			// IP

// IP信息
typedef struct 
{
	DWORD				dwIPNum;				// IP个数
	char				SZIP[DH_IPIFILTER_NUM][DH_MAX_IPADDR_LEN]; // IP
	char				byReserve[32];			// 保留
} IPIFILTER_INFO;

// IP过滤配置结构体
typedef struct
{
	DWORD				dwSize;
	DWORD				dwEnable;				// 使能
	DWORD				dwType;					// 当前名单类型：0：白名单 1：黑名单（设备只能使一种名单生效，或者是白名单或者是黑名单）
	IPIFILTER_INFO		BannedIP;				// 黑名单
	IPIFILTER_INFO		TrustIP;				// 白名单
	char				byReserve[256];			// 保留
} DHDEV_IPIFILTER_CFG;

/*语音对讲编码配置*/
typedef struct
{
	DWORD				dwSize;
	int					nCompression;			// 压缩格式，枚举值，相见DH_TALK_CODING_TYPE，请根据设备支持的语音对讲类型设置压缩格式。
	int					nMode;					// 编码模式，枚举值，为0时表示该压缩格式不支持编码模式。
												// 根据压缩格式可以设置对应的编码格式，如
												// AMR详见EM_ARM_ENCODE_MODE
	char				byReserve[256];			// 保留
} DHDEV_TALK_ENCODE_CFG;

// 以下是mobile功能相关
// (事件触发多媒体彩信/短信发送)MMS配置结构体
typedef struct
{
	DWORD				dwSize;
	DWORD				dwEnable;				// 使能
	DWORD				dwReceiverNum;			// 短信接收者个数
	char				SZReceiver[DH_MMS_RECEIVER_NUM][32];	// 短信接收者，一般为手机号码
    BYTE                byType;					// 短信信息类型 0:MMS；1:SMS
	char                SZTitle[32];			// 短信信息标题
	char				byReserve[223];			// 保留
} DHDEV_MMS_CFG;

// (短信激活无线连接配置)
typedef struct  
{
	DWORD				dwSize;
	DWORD				dwEnable;				// 使能
	DWORD				dwSenderNum;			// 短信发送者个数
	char				SZSender[DH_MMS_SMSACTIVATION_NUM][32];	// 短信发送者，一般为手机号码
 	char				byReserve[256];			// 保留
}DHDEV_SMSACTIVATION_CFG;

// (拨号激活无线连接配置)
typedef struct  
{
	DWORD				dwSize;
	DWORD				dwEnable;				// 使能
	DWORD				dwCallerNum;			// 发送者个数
	char				SZCaller[DH_MMS_DIALINACTIVATION_NUM][32];	// 发送者, 一般为手机号码
 	char				byReserve[256];			// 保留
}DHDEV_DIALINACTIVATION_CFG;
// 以上是mobile功能相关


// 无线网络信号强度结构体
typedef struct
{
	DWORD				dwSize;
	DWORD				dwTDSCDMA;				// TD-SCDMA强度，范围：0－100
	DWORD				dwWCDMA;				// WCDMA强度，范围：0－100
	DWORD				dwCDMA1x;				// CDMA1x强度，范围：0－100
	DWORD				dwEDGE;					// EDGE强度，范围：0－100
	DWORD				dwEVDO;					// EVDO强度，范围：0－100
	int					nCurrentType;			// 当前类型
												// 0	设备不支持这一项
												// 1    TD_SCDMA
												// 2	WCDMA
												// 3	CDMA_1x
												// 4	EDGE
												// 5	EVDO
	char				byReserve[252];			// 保留
} DHDEV_WIRELESS_RSS_INFO;

typedef struct _DHDEV_SIP_CFG
{
	BOOL	bUnregOnBoot;						//Unregister on Reboot
	char	szAccoutName[64];					//Account Name
	char	szSIPServer[128];					//SIP Server
	char	szOutBoundProxy[128];				//Outbound Proxy
	DWORD	dwSIPUsrID;							//SIP User ID
	DWORD	dwAuthID;							//Authenticate ID
	char	szAuthPsw[64];						//Authenticate Password
	char	szSTUNServer[128];					//STUN Server
	DWORD	dwRegExp;							//Registration Expiration
	DWORD	dwLocalSIPPort;						//Local SIP Port
	DWORD	dwLocalRTPPort;						//Local RTP Port
	BYTE	bReserved[1024];					//reserved
} DHDEV_SIP_CFG;

typedef struct _DHDEV_SIP_STATE
{
	BOOL	bOnline;							//TRUE:online, FALSE:offline
	BYTE	bReserved[64];						//保留
}DHDEV_SIP_STATE;

/***************************** 云台预制点配置 ***********************************/
typedef struct _POINTEANBLE
{
	BYTE				bPoint;	//预制点的有效范围闭区间[1,80]，无效设置为0。
	BYTE				bEnable;	//是否有效,0无效，1有效
	BYTE				bReserved[2];
} POINTEANBLE;

typedef struct _POINTCFG
{
	char				szIP[DH_MAX_IPADDR_LEN];// ip
	int					nPort;					// 端口	
	POINTEANBLE			stuPointEnable[80];		// 预制点使能
	BYTE				bReserved[256];
}POINTCFG;

typedef struct _DHDEV_POINT_CFG
{
	int					nSupportNum;			// 只读参数，设置的时候需要返回给sdk，表示支持的预制点数
	POINTCFG			stuPointCfg[16];		// 二维下标表示通道号。要设置的点数值放在前nSupportNum个下标里面。
	BYTE				bReserved[256];			// 保留
}DHDEV_POINT_CFG;
////////////////////////////////车载DVR支持////////////////////////////////

// GPS信息(车载设备)
typedef struct _GPS_Info
{
    NET_TIME			revTime;				// 定位时间
	char				DvrSerial[50];			// 设备序列号
    double				longitude;				// 经度(单位是百万分之度，范围0-360度)
    double				latidude;				// 纬度(单位是百万分之度，范围0-180度)
    double				height;					// 高度(米)
    double				angle;					// 方向角(正北方向为原点，顺时针为正)
    double				speed;					// 速度(单位是海里，speed/1000*1.852公里/小时)
    WORD				starCount;				// 定位星数
    BOOL				antennaState;			// 天线状态(true 好，false 坏)
    BOOL				orientationState;		// 定位状态(true 定位，false 不定位)
} GPS_Info,*LPGPS_Info;

// 抓图参数结构体
typedef struct _snap_param
{
	unsigned int		Channel;				// 抓图的通道
	unsigned int		Quality;				// 画质；1~6
	unsigned int		ImageSize;				// 画面大小；0：QCIF，1：CIF，2：D1
	unsigned int		mode;					// 抓图模式；0：表示请求一帧，1：表示定时发送请求，2：表示连续请求
	unsigned int		InterSnap;				// 时间单位秒；若mode=1表示定时发送请求时，此时间有效
	unsigned int		CmdSerial;				// 请求序列号
	unsigned int		Reserved[4];
} SNAP_PARAMS, *LPSNAP_PARAMS;

// 抓图功能配置
typedef struct 
{
	DWORD				dwSize;
	BYTE				bTimingEnable;				// 定时抓图开关(报警抓图开关在各报警联动配置中体现)
	BYTE                bReserved;
	short	            PicTimeInterval;			// 定时抓图时间间隔，单位为秒,目前设备支持最大的抓图时间间隔为30分钟                           
	DH_VIDEOENC_OPT		struSnapEnc[SNAP_TYP_NUM]; // 抓图编码配置，现支持其中的分辨率、画质、帧率设置，帧率在这里是负数，表示一秒抓图的次数。
} DHDEV_SNAP_CFG;

//车载wifi状态
typedef struct  
{
	char	szSSID[128];							//SSID
	BOOL	bEnable;								//是否启用wifi功能, 0:不使能 1:使能
	int		nSafeType;								//校验类型
													//0:OPEN 
													//1:RESTRICTE
													//2:WEP
													//3:WPA
													//4:WPA2
													//5:WPA-PSK
													//6:WPA2-PSK
	int		nEncryprion;							//加密方式
													//0:OPEN
													//1:TKIP
													//2:WEP
													//3:AES
													//4:NONE(不校验)
	int		nStrength;								//AP站点信号
	char	szHostIP[128];							//主机地址
	char	szHostNetmask[128];						//主机掩码
	char	szHostGateway[128];						//主机网关
	BYTE	bReserved[1024];
} DHDEV_VEHICLE_WIFI_STATE;

typedef struct
{
	char	szSSID[128];							//SSID
	int		nPriority;								//优先级,(1-32)
	int		nSafeType;								//校验类型
													//0:OPEN 
													//1:RESTRICTE
													//2:WEP
													//3:WPA
													//4:WPA2
													//5:WPA-PSK
													//6:WPA2-PSK
	int		nEncryprion;							//加密方式
													//0:OPEN
													//1:TKIP
													//2:WEP
													//3:AES
													//4:NONE(不校验)
	char	szKey[128];								//连接密钥
	char	szHostIP[128];							//主机地址
	char	szHostNetmask[128];						//主机掩码
	char	szHostGateway[128];						//主机网关
	BYTE	bReserved[1024];
} DHDEV_VEHICLE_WIFI_CONFIG;

typedef struct 
{
	BOOL	bIsScan;								//0:非扫描wifi (手动添加的), 1扫描到的wifi
	char	szSSID[128];							//SSID
	int		nSafeType;								//校验类型
													//0:OPEN 
													//1:RESTRICTE
													//2:WEP
													//3:WPA
													//4:WPA2
													//5:WPA-PSK
													//6:WPA2-PSK
	int		nEncryprion;							//加密方式
													//0:OPEN
													//1:TKIP
													//2:WEP
													//3:AES
													//4:NONE(不校验)
	char	szKey[128];								//连接密钥
	int		nStrength;								//AP站点信号
	int		nMaxBitRate;							//AP站点的最大传输速率,带单位 只读
	int		nIsCnnted;								//是否连接成功只读
	int		nIsSaved;								//是否已经保存只读
	int		nPriority;								//优先级,(1-32)
	char	szHostIP[128];							//主机地址
	char	szHostNetmask[128];						//主机掩码
	char	szHostGateway[128];						//主机网关
	int		nWifiFreq;								//无线频率，采用通道标识
	BYTE	bReserved[1024];
}DHDEV_VEHICLE_SINGLE_WIFI_AP_CFG;

typedef struct 
{
	BOOL	bEnable;								//是否启用wifi功能, 0:不使能 1:使能
	int		nWifiApNum;								//DHDEV_VEHICLE_WIFI_AP_CFG结构体有效个数
	DHDEV_VEHICLE_SINGLE_WIFI_AP_CFG struWifiAp[64];//单个WIFI AP配置
	int	nReserved[512];								//保留
}DHDEV_VEHICLE_WIFI_AP_CFG;

//////////////////////////////////ATM支持//////////////////////////////////

typedef struct
{
	int					Offset;					// 标志位的位偏移
	int					Length;					// 标志位的长度
	char				Key[16];				// 标志位的值
} DH_SNIFFER_FRAMEID;

typedef struct 
{
	int					Offset;					// 标志位的位偏移
	int					Offset2;				// 目前没有应用
	int					Length;					// 标志位的长度
	int					Length2;				// 目前没有应用
	char				KeyTitle[24];			// 标题的值
} DH_SNIFFER_CONTENT;

// 网络抓包配置
typedef struct 
{
	DH_SNIFFER_FRAMEID	snifferFrameId;			// 每个FRAME ID 选项
	DH_SNIFFER_CONTENT	snifferContent[DH_SNIFFER_CONTENT_NUM];	// 每个FRAME对应的4个抓包内容
} DH_SNIFFER_FRAME;

// 每组抓包对应的配置结构
typedef struct
{
	char				SnifferSrcIP[DH_MAX_IPADDR_LEN];	// 抓包源地址		
	int					SnifferSrcPort;			// 抓包源端口
	char				SnifferDestIP[DH_MAX_IPADDR_LEN];	// 抓包目标地址
	int					SnifferDestPort;		// 抓包目标端口
	char				reserved[28];			// 保留字段
	DH_SNIFFER_FRAME	snifferFrame[DH_SNIFFER_FRAMEID_NUM];	// 6个FRAME 选项
	int					displayPosition;		// 显示位置
	int					recdChannelMask;		// 通道掩码
} DH_ATM_SNIFFER_CFG;

typedef struct  
{
	DWORD				dwSize;
	DH_ATM_SNIFFER_CFG	SnifferConfig[4];
	char				reserved[256];			// 保留字段
} DHDEV_SNIFFER_CFG;

typedef DH_SNIFFER_FRAMEID DH_SNIFFER_FRAMEID_EX;
typedef DH_SNIFFER_CONTENT DH_SNIFFER_CONTENT_EX;

// 网络抓包配置
typedef struct  
{
	DH_SNIFFER_FRAMEID	snifferFrameId;								// 每个FRAME ID 选项
	DH_SNIFFER_CONTENT	snifferContent[DH_SNIFFER_CONTENT_NUM_EX];	// 每个FRAME对应的8个抓包内容	
} DH_SNIFFER_FRAME_EX;

// 每组抓包对应的配置结构
typedef struct
{
	char				SnifferSrcIP[DH_MAX_IPADDR_LEN];					// 抓包源地址		
	int					SnifferSrcPort;										// 抓包源端口
	char				SnifferDestIP[DH_MAX_IPADDR_LEN];					// 抓包目标地址
	int					SnifferDestPort;									// 抓包目标端口
	DH_SNIFFER_FRAME_EX	snifferFrame[DH_SNIFFER_FRAMEID_NUM];				// 6个FRAME 选项
	int					displayPosition;									// 显示位置
	int					recdChannelMask;									// 通道掩码
	BOOL				bDateScopeEnable;									// 数据来源使能
	BOOL				bProtocolEnable;									// 协议使能
	char				szProtocolName[DH_SNIFFER_PROTOCOL_SIZE];			// 协议名字
	int					nSnifferMode;										// 抓包方式，0:net,1:232.
	char				reserved[256];
} DH_ATM_SNIFFER_CFG_EX;

// Atm交易类型查询返回结构体
#define ATM_MAX_TRADE_TYPE_NAME	64
#define ATM_MAX_TRADE_NUM		1024

typedef struct __DH_ATM_QUERY_TRADE   
{
	int					nTradeTypeNum;										// 实际交易类型数量
	int					nExceptionTypeNum;									// 实际异常事件数量
	char				szSupportTradeType[ATM_MAX_TRADE_NUM][ATM_MAX_TRADE_TYPE_NAME];    // 交易事件名数组
	char				szSupportExceptionType[ATM_MAX_TRADE_NUM][ATM_MAX_TRADE_TYPE_NAME];// 异常事件名数组
} DH_ATM_QUERY_TRADE, *LPDH_ATM_QUERY_TRADE;



/////////////////////////////////解码器支持/////////////////////////////////

// 解码器信息
typedef struct __DEV_DECODER_INFO 
{
	char			szDecType[64];			// 类型
	int				nMonitorNum;			// TV个数
	int				nEncoderNum;			// 解码通道个数
	BYTE			szSplitMode[16];		// 支持的TV画面分割数，以数组形式表示，0为结尾
	BYTE            bMonitorEnable[16];		// 各TV使能
	char			reserved[64];
} DEV_DECODER_INFO, *LPDEV_DECODER_INFO;

// 连接的编码器信息
typedef struct __DEV_ENCODER_INFO 
{
	char			szDevIp[DH_MAX_IPADDR_LEN];			// 前端DVR的IP地址
	WORD			wDevPort;							// 前端DVR的端口号
	BYTE			bDevChnEnable;                      // 解码通道使能
	BYTE			byEncoderID;						// 对应解码通道号
	char			szDevUser[DH_USER_NAME_LENGTH_EX];	// 用户名
	char			szDevPwd[DH_USER_PSW_LENGTH_EX];	// 密码
	int				nDevChannel;						// 通道号
	int				nStreamType;						// 码流类型，0：主码流；1：子码流; 2:snap
	BYTE			byConnType;							// 0：TCP；1：UDP；2：组播
	BYTE			byWorkMode;							// 0：直连；1：转发
	WORD			wListenPort;						// 指示侦听服务的端口，转发时有效
	DWORD			dwProtoType;						// 协议类型,
														// 0:兼容以前
														// 1:大华二代协议
														// 2:大华系统集成协议
														// 3:大华DSS协议
														// 4:大华rtsp协议
	char			szDevName[64];						// 前端设备名称
	BYTE            byVideoInType;                      // 该解码通道当前视频源类型:0-标清(SD),1-高清(HD),注:设备支持高清通道才有效		
	char			szDevIpEx[DH_MAX_IPADDR_OR_DOMAIN_LEN];// szDevIp扩展，前端DVR的IP地址(可以输入域名)
	BYTE            bySnapMode;                         //抓图模式(nStreamType==2时有效) 0：表示请求一帧,1：表示定时发送请求
	BYTE            byManuFactory;						//目标设备的生产厂商,0:Private(大华私有)
	BYTE            byDeviceType;                       //目标设备的设备类型,0:IPC
	BYTE            byDecodePolicy;                     //目标设备的解码策略,0:兼容以前
														// 1:实时等级高 2:实时等级中
														// 3:实时等级低 4:默认等级
														// 5:流畅等级高 6:流畅等级中
														// 7:流畅等级低

	char			reserved[47];
} DEV_ENCODER_INFO, *LPDEV_ENCODER_INFO;

// TV参数信息
typedef struct __DEV_DECODER_TV 
{
	int				nID;								// TV号
	BOOL			bEnable;							// 使能，开启或关闭
	int				nSplitType;							// 画面分割数
	DEV_ENCODER_INFO stuDevInfo[16];					// 各画面编码器信息
	char			reserved[16];
} DEV_DECODER_TV, *LPDEV_DECODER_TV;

// 解码器画面组合信息
typedef struct __DEC_COMBIN_INFO
{
	int				nCombinID;							// 组合ID
	int             nSplitType;							// 画面分割数 
	BYTE            bDisChn[16];						// 显示通道
	char			reserved[16];
} DEC_COMBIN_INFO, *LPDEC_COMBIN_INFO;

// 解码器轮巡信息
#define DEC_COMBIN_NUM 			32						// 轮巡组合个数
typedef struct __DEC_TOUR_COMBIN 
{
	int				nTourTime;							// 轮巡间隔(秒)
	int				nCombinNum;							// 组合个数
	BYTE			bCombinID[DEC_COMBIN_NUM];			// 组合表
	char			reserved1[32];
	BYTE			bCombinState[DEC_COMBIN_NUM];		// 组合项的使能状态，0：关；1：开
	char			reserved2[32];
} DEC_TOUR_COMBIN, *LPDEC_TOUR_COMBIN;

// 解码器回放类型
typedef enum __DEC_PLAYBACK_MODE
{
	Dec_By_Device_File = 0,								// 前端设备－按文件方式
	Dec_By_Device_Time,									// 前端设备－按时间方式
} DEC_PLAYBACK_MODE;

// 解码器回放控制类型
typedef enum __DEC_CTRL_PLAYBACK_TYPE
{
	Dec_Playback_Seek = 0,								// 拖动
	Dec_Playback_Play,									// 播放
	Dec_Playback_Pause,									// 暂停
	Dec_Playback_Stop,									// 停止
} DEC_CTRL_PLAYBACK_TYPE;

//轮巡控制类型
typedef enum __DEC_CTRL_TOUR_TYPE
{
	Dec_Tour_Stop = 0,									// 停止
	Dec_Tour_Start,										// 开始
	Dec_Tour_Pause,										// 暂停
	Dec_Tour_Resume,									// 恢复
} DEC_CTRL_TOUR_TYPE;

// 按文件回放前端设备条件
typedef struct __DEC_PLAYBACK_FILE_PARAM 
{
	char			szDevIp[DH_MAX_IPADDR_LEN];			// 前端DVR的IP地址
	WORD			wDevPort;							// 前端DVR的端口号
	BYTE			bDevChnEnable;                      // 解码通道使能
	BYTE			byEncoderID;						// 对应解码通道号
	char			szDevUser[DH_USER_NAME_LENGTH_EX];	// 用户名
	char			szDevPwd[DH_USER_PSW_LENGTH_EX];	// 密码
	NET_RECORDFILE_INFO stuRecordInfo;					// 录像文件信息
	char			reserved[12];
} DEC_PLAYBACK_FILE_PARAM, *LPDEC_PLAYBACK_FILE_PARAM;

// 按时间回放前端设备条件
typedef struct __DEC_PLAYBACK_TIME_PARAM 
{
	char			szDevIp[DH_MAX_IPADDR_LEN];			// 前端DVR的IP地址
	WORD			wDevPort;							// 前端DVR的端口号
	BYTE			bDevChnEnable;                      // 解码通道使能
	BYTE			byEncoderID;						// 对应解码通道号
	char			szDevUser[DH_USER_NAME_LENGTH_EX];	// 用户名
	char			szDevPwd[DH_USER_PSW_LENGTH_EX];	// 密码
	int				nChannelID;
	NET_TIME		startTime;
	NET_TIME		endTime;
	char			reserved[12];
} DEC_PLAYBACK_TIME_PARAM, *LPDEC_PLAYBACK_TIME_PARAM;

// 当前解码通道状态信息(包括通道状态，解码流信息等)
typedef struct __DEV_DECCHANNEL_STATE
{
	BYTE			byEncoderID;						// 对应解码通道号
	BYTE            byChnState;                         // 当前解码通道正在操作状态:0－空闲，1－实时监视，2－回放 3 - 轮巡
	BYTE			byFrame;                            // 当前数据帧率
	BYTE            byReserved;                         // 保留
	int				nChannelFLux;						// 解码通道数据总量
	int             nDecodeFlux;						// 解码数据量
	char            szResolution[16];                   // 当前数据分辨率
	char			reserved[256];
} DEV_DECCHANNEL_STATE, *LPDEV_DECCHANNEL_STATE;

// 设备TV输出参数信息
typedef struct __DEV_VIDEOOUT_INFO
{
	DWORD				dwVideoStandardMask;			// NSP,视频制式掩码，按位表示设备能够支持的视频制式(暂不支持)
	int					nVideoStandard;                 // NSP,当前的制式(暂不支持，请使用DHDEV_SYSTEM_ATTR_CFG的byVideoStandard对制式读取和配置)
	DWORD				dwImageSizeMask;				// 分辨率掩码，按位表示设备能够支持的分辨率
	int                 nImageSize;                     // 当前的分辨率
	char				reserved[256];
}DEV_VIDEOOUT_INFO, *LPDEV_VIDEOOUT_INFO;

// 调节TV输出
typedef struct __DEV_TVADJUST_CFG
{
	int					nTop;							// 上测边距（0－100）
	int					nBotton;						// 下测边距（0－100）
	int					nLeft;							// 左测边距（0－100）
	int                 nRight;							// 右测边距（0－100）
	int					reserved[32];
}DHDEV_TVADJUST_CFG, *LPDHDEV_TVADJUST_CFG;

// 解码轮巡配置
typedef struct __DEV_DECODER_TOUR_SINGLE_CFG
{
	char		szIP[128];								// 前端设备ip.例如"10.7.5.21". 保留对域名的支持.需要以'\0'结束.
	int			nPort;									// 前端设备端口.(0, 65535).
	int			nPlayChn;								// 请求前端设备通道[1, 16].
	int			nPlayType;								// 请求前端码流类型, 0:主码流; 1:辅码流.
	char		szUserName[32];							// 登陆前端设备的用户名,需要以'\0'结束.
	char		szPassword[32];							// 登陆前端设备的密码,需要以'\0'结束.
	int			nInterval;								// 轮巡间隔时间[10, 120],单位秒.
	BYTE		bReserved[64];							// 保留字节,留待扩展.
}DHDEV_DECODER_TOUR_SINGLE_CFG;

typedef struct __DEV_DECODER_TOUR_CFG
{
	int								nCfgNum;			// 配置结构体数目. 现在最大支持32个.具体支持数目可以通过能力查询.
	DHDEV_DECODER_TOUR_SINGLE_CFG	tourCfg[64];		// 轮询配置数组,有效结构体个数由成员"nCfgNum"指定. 保留32个留待扩展.
	BYTE							bReserved[256];		// 保留字节,留待扩展.
}DHDEV_DECODER_TOUR_CFG;

/////////////////////////////////智能支持/////////////////////////////////

// 视频分析物体信息结构体
typedef struct 
{
	int					nObjectID;						// 物体ID,每个ID表示一个唯一的物体
	char				szObjectType[128];				// 物体类型
	int					nConfidence;					// 置信度(0~255)，值越大表示置信度越高
	int					nAction;						// 物体动作:1:Appear 2:Move 3:Stay 4:Remove 5:Disappear 6:Split 7:Merge 8:Rename
	DH_RECT				BoundingBox;					// 包围盒
	DH_POINT			Center;							// 物体型心
	int					nPolygonNum;					// 多边形顶点个数
	DH_POINT			Contour[MAX_POLYGON_NUM];		// 较精确的轮廓多边形
	DWORD				rgbaMainColor;					// 物体主要颜色；按字节表示，分别为红、绿、蓝和透明度
    char				szText[128];						// 物体上相关的带0结束符文本，比如车牌，集装箱号等等
	BYTE				byReserved[256];   
} DH_MSG_OBJECT;

// 事件类型EVENT_IVS_CROSSLINEDETECTION(警戒线事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_CROSSLINE_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_CROSSLINE_INFO;

// 事件类型EVENT_IVS_CROSSREGIONDETECTION(警戒区事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_CROSSREGION_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_CROSSREGION_INFO;

// 事件类型EVENT_IVS_PASTEDETECTION(贴条事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_PASTE_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_PASTE_INFO;

// 事件类型EVENT_IVS_LEFTDETECTION(物品遗留事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_LEFT_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_LEFT_INFO;

// 事件类型EVENT_IVS_PRESERVATION(物品保全事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_PRESERVATION_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_PRESERVATION_INFO;

// 事件类型EVENT_IVS_STAYDETECTION(停留事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_STAY_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_STAY_INFO;

// 事件类型EVENT_IVS_WANDERDETECTION(徘徊事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_WANDER_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_WANDER_INFO;

// 事件类型EVENT_IVS_MOVEDETECTION(移动事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_MOVE_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_MOVE_INFO;

// 事件类型EVENT_IVS_TAILDETECTION(尾随事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_TAIL_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_TAIL_INFO;

// 事件类型EVENT_IVS_RIOTERDETECTION(聚众事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_RIOTER_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	int					nObjectNum;						// 检测到的物体个数
	DH_MSG_OBJECT		stuObjectIDs[MAX_OBJECT_LIST];	// 检测到的物体列表
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_RIOTERL_INFO;

// 事件类型EVENT_IVS_FIGHTDETECTION(斗殴事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_FIGHT_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	int					nObjectNum;						// 检测到的物体个数
	DH_MSG_OBJECT		stuObjectIDs[MAX_OBJECT_LIST];	// 检测到的物体列表
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_FIGHT_INFO;

// 事件类型EVENT_IVS_FIREDETECTION(火警事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_FIRE_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_FIRE_INFO;

// 事件类型EVENT_IVS_SMOKEDETECTION(烟雾报警事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_SMOKE_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_SMOKE_INFO;

// 事件类型EVENT_IVS_FLOWSTAT(流量统计事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_FLOWSTAT_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	int					nNumberLeft;					// 从左边穿越的人的个数
	int					nNumberRight;					// 从右边穿越的人的个数
	int					nUpperLimit;					// 设置的上限
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_FLOWSTAT_INFO;

// 事件类型EVENT_IVS_NUMBERSTAT(数量统计事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_NUMBERSTAT_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	int					nNumber;							// 区域内物体的个数
	int					nUpperLimit;					// 设置的上限
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_NUMBERSTAT_INFO;

// 事件类型EVENT_IVS_TRAFFICCONTROL(交通管制事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_TRAFFICCONTROL_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_TRAFFICCONTROL_INFO;

// 事件类型EVENT_IVS_TRAFFICACCIDENT(交通事故事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_TRAFFICACCIDENT_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	int					nObjectNum;						// 检测到的物体个数
	DH_MSG_OBJECT		stuObjectIDs[MAX_OBJECT_LIST];	// 检测到的物体列表
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_TRAFFICACCIDENT_INFO;

// 事件类型EVENT_IVS_TRAFFICJUNCTION(交通路口事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_TRAFFICJUNCTION_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	int					nLane;							// 对应车道号
	DWORD				dwBreakingRule;					// 违反规则掩码,第一位:闯红灯; 第二位:不按规定车道行驶; 第三位:逆行; 第四位：违章掉头
	NET_TIME			RedLightUTC;					// 红灯开始UTC时间
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_TRAFFICJUNCTION_INFO;


// 事件类型EVENT_IVS_TRAFFICGATE(交通卡口事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_TRAFFICGATE_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	DH_MSG_OBJECT		stuObject;						// 检测到的物体
	int					nLane;							// 对应车道号
	int					nSpeed;							// 车辆实际速度Km/h
	int					nSpeedUpperLimit;				// 速度上限 单位：km/h
	int					nSpeedLowerLimit;				// 速度下限 单位：km/h 
	BYTE				bReserved[256];					// 保留字节,留待扩展.

} DEV_EVENT_TRAFFICGATE_INFO;

//事件类型EVENT_TRAFFICSNAPSHOT(交通抓拍事件)对应的数据块描述信息
typedef struct tagDEV_EVENT_TRAFFICSNAPSHOT_INFO 
{
	int					nChannelID;						// 通道号
	char				szName[128];					// 事件名称
	double				PTS;							// 时间戳(单位是毫秒)
	NET_TIME			UTC;							// 事件发生的时间
	int					nEventID;						// 事件ID
	char                szTilt[256];                    // 事件详细信息
	long                lJpegSummaryPointer;            // 叠加到JPEG图片的摘要信息内存地址
    int                 nJpegSummaryLength;             // 摘要信息长度
	int                 nMark;                          // 底层产生的触发抓拍帧标记
	BYTE				bReserved[256];					// 保留字节,留待扩展
} DEV_EVENT_TRAFFICSNAPSHOT_INFO;


/////////////////////////////////特殊版本/////////////////////////////////

// 触发设备抓图，叠加卡号信息
typedef struct __NET_SNAP_COMMANDINFO 
{
	char				szCardInfo[16];			// 卡号信息
	char				reserved[64];			// 保留
} NET_SNAP_COMMANDINFO, LPNET_SNAP_COMMANDINFO;

typedef struct
{
	int					nChannelNum;			// 通道号
	char				szUseType[32];			// 通道用途
	DWORD				dwStreamSize;			// 流量大小(单位：kb/s)
	char				reserved[32];			// 保留
} DHDEV_USE_CHANNEL_STATE;

typedef struct 
{
	char				szUserName[32];			// 用户名
	char				szUserGroup[32];		// 用户组
	NET_TIME			time;					// 登入时间
	int					nOpenedChannelNum;		// 开启的通道个数
	DHDEV_USE_CHANNEL_STATE	channelInfo[DH_MAX_CHANNUM];
	char				reserved[64];
} DHDEV_USER_NET_INFO;

// 网络运行状态信息
typedef	struct 
{
	int					nUserCount;				// 用户数量
	DHDEV_USER_NET_INFO	stuUserInfo[32];
	char				reserved[256];
}DHDEV_TOTAL_NET_STATE;

// 图象水印配置
typedef struct __DHDEV_WATERMAKE_CFG 
{
	DWORD				dwSize;
	int					nEnable;				// 使能
	int					nStream;				// 码流(1～n)0-所有码流
	int					nKey;					// 数据类型(1-文字，2-图片)
	char				szLetterData[DH_MAX_WATERMAKE_LETTER];	//	文字
	char				szData[DH_MAX_WATERMAKE_DATA]; // 图片数据
	BYTE				bReserved[512];			// 保留
} DHDEV_WATERMAKE_CFG;

// 存储位置设置结构体，每通道独立设置,每通道可以选择各种存储类型, 目前包括本地, 可移动, 远程存储.
typedef struct 
{
	DWORD				dwSize;
	DWORD				dwLocalMask;			// 本地存储掩码；按位表示：
												// 第一位：系统预录，第二位：定时录像，第三位：动检录像，
												// 第四位：报警录像，第五位：卡号录像，第六位：手动录像
	DWORD				dwMobileMask;			// 可移动存储掩码 存储掩码如本地存储掩码
	int					RemoteType;				// 远程存储类型 0: Ftp  1: Smb 
	DWORD				dwRemoteMask;			// 远程存储掩码 存储掩码如本地存储掩码
	DWORD				dwRemoteSecondSelLocal;	// 远程异常时本地存储掩码
	DWORD				dwRemoteSecondSelMobile;// 远程异常时可移动存储掩码
	char				SubRemotePath[MAX_PATH_STOR]; // 远程目录, 其中长度为240
	DWORD				dwFunctionMask;			// 功能屏蔽位，按位表示，bit0 = 1:屏蔽抓图事件触发存储位置功能
	DWORD				dwAutoSyncMask;			// 是否同步掩码;远程存储网络故障恢复后，自动将本地存储的数据同步到远程存储。
	BYTE				bAutoSyncRange;			// 从网络恢复的时刻开始，需要往前同步的数据时间范围，小时为单位。0:同步所有数据  1:1小时内的数据 n:n小时内的数据
	char				reserved[119];
} DH_STORAGE_STATION_CFG;

#define MAX_ALARM_DECODER_NUM 16
typedef struct  
{
	DWORD				dwAlarmDecoder;			// 现在最多支持8个报警输入口，留8位待以后扩展
	BYTE				bDecoderIndex;			// 表示第几个报警解码器
	BYTE				bReserved[3];
} ALARM_DECODER;

// 报警解码器报警
typedef struct
{
	int					nAlarmDecoderNum;
	ALARM_DECODER		stuAlarmDecoder[MAX_ALARM_DECODER_NUM];
	BYTE				bReserved[32];
} ALARM_DECODER_ALARM;

//DSP报警
typedef struct  
{
	BOOL				bError;			//0,DSP正常 1,DSP异常
	DWORD				dwErrorMask;	//按位表示，非0表示有此错误，0表示没有。(目前每次报警只有一位有效)
										//bit		DSP报警
										//1			DSP加载失败 
										//2			DSP错误
										//3			制式不对 
										//4			分辨率不支持
										//5			数据格式不支持
										//6			找不到I帧
	DWORD               dwDecChnnelMask;//按位表示，报警的解码通道号，dwErrorMask为DSP错误，制式不对，分辨率不支持，数据格式不支持时此项有效
	
	BYTE				bReserved[28];
}DSP_ALARM;

// 光纤编码能力报警
typedef struct  
{
	int		nFDDINum;
	BYTE	bAlarm[256];
} ALARM_FDDI_ALARM;

//云台定位信息报警
typedef struct
{
	int     nChannelID;             // 通道号 
	int     nPTZPan;                // 云台水平坐标
	int     nPTZTilt;               // 云台垂直坐标
	int     nPTZZoom;               // 云台变倍
	int     reserved[256];          // 保留字段
}ALARM_PTZ_LOCATION_INFO;

// 新音频检测报警配置
typedef struct
{
	BOOL				bEnable;				// 报警输入使能
	int					Volume_min;				// 音量的最小值
	int					Volume_max;				// 音量的最大值
	char				reserved[128];	
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	
	DH_MSG_HANDLE		struHandle;				// 处理方式
} DH_AUDIO_DETECT_INFO;

typedef struct  
{
	DWORD				dwSize;
	int					AlarmNum;
	DH_AUDIO_DETECT_INFO AudioDetectAlarm[DH_MAX_AUDIO_IN_NUM];
	char				reserved[256];
} DH_AUDIO_DETECT_CFG;

typedef struct
{
	BOOL				bTourEnable;			// 轮巡使能
	int					nTourPeriod;			// 轮巡间隔，单位秒, 5-300 
	DWORD				dwChannelMask;			// 轮巡的通道，掩码形式表示
	char				reserved[64];
}DH_VIDEOGROUP_CFG;

// 本机矩阵控制策略配置
typedef struct
{
	DWORD				dwSize;
	int					nMatrixNum;				// 矩阵个数(注：不允许修改)
	DH_VIDEOGROUP_CFG	struVideoGroup[DH_MATRIX_MAXOUT];
	char				reserved[32];
} DHDEV_VIDEO_MATRIX_CFG;   

// WEB路径配置
typedef struct 
{
	DWORD				dwSize;
	BOOL				bSnapEnable;			// 是否抓图
	int					iSnapInterval;			// 抓图周期
	char				szHostIp[DH_MAX_IPADDR_LEN]; // HTTP主机IP
	WORD				wHostPort;
	int					iMsgInterval;			// 状态消息发送间隔
	char				szUrlState[DH_MAX_URL_LEN];	// 状态消息上传URL
	char				szUrlImage[DH_MAX_URL_LEN];	// 图片上传Url
	char				szDevId[DH_MAX_DEV_ID_LEN];	// 机器的web编号
	BYTE				byReserved[2];
} DHDEV_URL_CFG;

// OEM查询
typedef struct  
{
	char				szVendor[DH_MAX_STRING_LEN];
	char				szType[DH_MAX_STRING_LEN];
	char				reserved[128];
} DHDEV_OEM_INFO;


//视频OSD叠加配置
typedef struct 
{ 
	DWORD	rgbaFrontground;		// 物件的前景；按字节表示，分别为红、绿、蓝和透明度
	DWORD	rgbaBackground;			// 物件的背景；按字节表示，分别为红、绿、蓝和透明度	
	RECT	rcRelativePos;			// 位置,物件边距与整长的比例*8191	
	BOOL	bPreviewBlend;			// 预览叠加使能	
	BOOL	bEncodeBlend;			// 编码叠加使能
	BYTE    bReserved[4];           // 保留
} DH_DVR_VIDEO_WIDGET;

typedef struct 
{
	DH_DVR_VIDEO_WIDGET	StOSD_POS; 								// OSD叠加的位置和背景色
	char 				SzOSD_Name[DH_VIDEO_OSD_NAME_NUM]; 		// OSD叠加的名称
}DH_DVR_VIDEOITEM;
 
// 每个通道的OSD信息
typedef struct 
{
	DWORD 				dwSize;
	DH_DVR_VIDEOITEM 	StOSDTitleOpt [DH_VIDEO_CUSTOM_OSD_NUM]; 	// 每个通道的OSD信息
	BYTE    			bReserved[16];                  		  // 保留
} DH_DVR_VIDEOOSD_CFG;

// 配置CDMA/GPRS网络信息
// 时间段结构															    
typedef struct 
{
	BYTE				bEnable;				  // 时间段使能，1表示该时间段有效，0表示该时间段无效。
	BYTE				bBeginHour;
	BYTE				bBeginMin;
	BYTE				bBeginSec;
	BYTE				bEndHour;
	BYTE				bEndMin;
	BYTE				bEndSec;
	BYTE    			bReserved;                //保留
} DH_3G_TIMESECT, *LPDH_3G_TIMESECT;

typedef struct 
{
	DWORD 				dwSize;
	BOOL				bEnable;					// 无线模块使能标志
	DWORD               dwTypeMask;                 // 设备支持网络类型掩码;按位表示,第一位;自动选择;
													// 第二位：TD-SCDMA网络；第三位：WCDMA网络;
													// 第四位：CDMA 1.x网络;第五位：CDMA2000网络;第六位：GPRS网络;
													// 第七位：EVDO网络;第八位：WIFI
	DWORD               dwNetType;                  // 当前的无线网络类型，为EM_GPRSCDMA_NETWORK_TYPE值
	char				szAPN[128];					// 接入点名称
	char				szDialNum[128];				// 拨号号码
	char				szUserName[128];			// 拨号用户名
	char				szPWD[128];					// 拨号密码
	
	/* 下面是设备的只读部分 */
	BOOL				iAccessStat;				// 无线网络注册状态
    char				szDevIP[16];				// 前端设备拨号IP，字符串, 包括'\0'结束符共16byte  
	char				szSubNetMask [16];			// 前端设备拨号子网掩码，字符串, 包括'\0'结束符共16byte 
	char				szGateWay[16];				// 前端设备拨号网关，字符串, 包括'\0'结束符共16byte 
	/* 上面是设备的只读部分 */
	int                 iKeepLive;					// 保活时间
	DH_3G_TIMESECT		stSect[DH_N_WEEKS][DH_N_TSECT];// 3G拨号时间段，有效时间段之内，开启拨号；有效时间段之外，关闭拨号。
	BYTE                byActivate;                  //是否需要被语音或短信激活
	char				Reserved[171];				// 保留字节，用于扩展
} DHDEV_CDMAGPRS_CFG;

// 录像打包长度配置
typedef struct  
{
	DWORD 				dwSize;
	int					nType;						// 0:按时间，1：按大小
	int					nValue;						// nType = 0时:单位分钟，nType = 1时:单位KB
	char				Reserved[128];				// 保留字节，用于扩展
} DHDEV_RECORD_PACKET_CFG;

// (定向)主动注册服务器信息
typedef struct __DEV_AUTOREGISTER_INFO 
{
	LONG			lConnectionID;						// 连接ID
	char			szServerIp[DH_MAX_IPADDR_LEN];		// 主动注册服务器的IP
	int				nPort;								// 主动注册服务器端口0- 65535
	int             nState;                             // 服务器的状态：0－注册失败；1-注册成功; 2-连接失败
	char			reserved[16];
} DEV_AUTOREGISTER_INFO;

typedef struct __DEV_SERVER_AUTOREGISTER 
{
	DWORD					dwSize;
	int						nRegisterSeverCount;											// 主动注册服务器个数
	DEV_AUTOREGISTER_INFO	stuDevRegisterSeverInfo[DH_CONTROL_AUTO_REGISTER_NUM];			// 各主动注册服务器信息
	char					reserved[256];
} DEV_SERVER_AUTOREGISTER, *LPDEV_SERVER_AUTOREGISTER;

// 附件刻录附件上传
typedef struct
{
	DWORD				dwSize;		
	char				szSourFile[MAX_PATH_STOR];	// 源文件路径
	int					nFileSize;					// 源文件大小，如果小于等于0，sdk自行计算文件大小.
	char				szBurnFile[MAX_PATH_STOR];	// 刻录后的文件名
	BYTE				bReserved[64];
} DHDEV_BURNFILE_TRANS_CFG;

// 郑州威科姆EC_U视频数据叠加使能配置
typedef struct 
{
	BOOL				bEnable;					// 使能
	int					nPort;						// 端口
	BYTE				bReserved[64];
} DHDEV_OSD_ENABLE_CFG;

// 车载相关配置:北京公交使用配置
typedef struct	
{
	BOOL				bAutoBootEnable;				//自动开机使能
	DWORD				dwAutoBootTime;					//每天自动开机时间点, 单位秒,从0算起.[0,82800]
	BOOL				bAutoShutDownEnable;			//自动关机使能
	DWORD				dwAutoShutDownTime;				//每天自动关机时间点, 单位秒,从0算起.[0,82800]
	DWORD				dwShutDownDelayTime;			//延时关机时间,单位秒.
	BYTE				bEventNoDisk;					//1,(Ignore:忽略); 2,(Reboot:重起系统)
	BYTE				bWifiEnable;					//是否支持车载无线模块.
	BYTE				bUpperSpeedEnable;				//是否使用超速判断
	BYTE				bReserved_1;					//4字节对齐
	DWORD				dwUpperSpeedValue;				//超速值开区间(1,1000).公里/小时
	BYTE				bReserved[504];					//reserved byte.
} DHDEV_ABOUT_VEHICLE_CFG;

// atm:查询叠加相关能力信息
typedef struct  
{
	DWORD				dwDataSource;					//1:Net(网络), 2:Com(串口), 3:Net&Com(网络和串口)
	char				szProtocol[32][33];				//协议名字,最大长度32(保留一个结束符).
	BYTE				bReserved[256];
} DHDEV_ATM_OVERLAY_GENERAL;
 
// atm:配置叠加设置
typedef struct 
{
	DWORD				dwDataSource;					//1:Net(网络), 2:Com(串口)
	char				szProtocol[33];					//协议名字，由DHDEV_ATM_OVERLAY_GENERAL返回
	BYTE				bReserved_1[3];
	DWORD				dwChannelMask;					//叠加的通道号，掩码表示。
	BYTE				bMode;							//1:Preview(预览叠加), 2:Encode(编码叠加), 3:Preview&Encode(预览和编码叠加)
	BYTE				bLocation;						//1:LeftTop(左上), 2:LeftBottom(左下), 3:RightTop(右上), 4:RightBottom(右下)
	BYTE				bReserved_2[258];
} DHDEV_ATM_OVERLAY_CONFIG;

#define DH_MAX_BACKUPDEV_NUM			16
#define DH_MAX_BACKUP_NAME				32

// 备份设备列表
typedef struct 
{
	int					nBackupDevNum;								// 实际的备份设备数量
	char				szBackupDevNames[DH_MAX_BACKUPDEV_NUM][DH_MAX_BACKUP_NAME]; // 备份设备的名称
} DHDEV_BACKUP_LIST, *LPDHDEV_BACKUP_LIST;

// 备份设备介质类型
typedef enum __BACKUP_TYPE
{
	BT_DHFS = 0,							// 大华文件系统
	BT_DISK,								// 移动硬盘
	BT_CDRW									// 光盘刻录
} DHDEV_BACKUP_TYPE;	

// 备份设备接口类型
typedef enum __BACKUP_BUS
{
	BB_USB = 0,								// usb接口
	BB_1394,								// 1394接口
	BB_IDE,									// ide接口
	BB_ESATA,								// esata接口
} DHDEV_BACKUP_BUS;	

typedef struct 
{
	char				szName[32];						// 设备名 
	BYTE				byType;							// 备份设备的介质类型 枚举值见BACKUP_TYPE
	BYTE				byBus;							// 备份设备的接口类型 枚举值见BACKUP_BUS
	UINT				nCapability;					// 总容量, 以kBytes为单位
	UINT				nRemain;						// 剩余容量,以kBytes为单位
	char				szDirectory[128];				// 远程备份的目录
} DHDEV_BACKUP_INFO, *LPDHDEV_BACKUP_INFO;

typedef struct 
{
	char				szName[32];						// 设备名 
	UINT				nCapability;					// 总容量, 以kBytes为单位
	UINT				nRemain;						// 当前备份剩余容量,以kBytes为单位
} DHDEV_BACKUP_FEEDBACK, *LPDHDEV_BACKUP_FEEDBACK;

#define  DH_MAX_BACKUPRECORD_NUM 1024

typedef struct  
{
	char				szDeviceName[DH_MAX_BACKUP_NAME];			//备份设备名称
	int					nRecordNum;									//备份记录数量
	NET_RECORDFILE_INFO	stuRecordInfo[DH_MAX_BACKUPRECORD_NUM];		//备份记录信息
} BACKUP_RECORD, *LPBACKUP_RECORD;

/////////////////////////////////平台接入/////////////////////////////////

// 平台接入配置 － U网通
typedef struct
{
    BOOL				bChnEn;
    char				szChnId[DH_INTERVIDEO_UCOM_CHANID];
} DH_INTERVIDEO_UCOM_CHN_CFG;

typedef struct
{
	DWORD				dwSize;
	BOOL				bFuncEnable;			// 接入功能使能
	BOOL				bAliveEnable;			// 心跳使能
	DWORD				dwAlivePeriod;			// 心跳周期，单位秒，0-3600
	char				szServerIp[DH_MAX_IPADDR_LEN]; // CMS的IP
	WORD				wServerPort;			// CMS的Port
    char				szRegPwd[DH_INTERVIDEO_UCOM_REGPSW]; // 注册密码
	char				szDeviceId[DH_INTERVIDEO_UCOM_DEVID];// 设备id
	char				szUserName[DH_INTERVIDEO_UCOM_USERNAME];
	char				szPassWord[DH_INTERVIDEO_UCOM_USERPSW];
    DH_INTERVIDEO_UCOM_CHN_CFG  struChnInfo[DH_MAX_CHANNUM]; // 通道id,en
} DHDEV_INTERVIDEO_UCOM_CFG;

// 平台接入配置 － 阿尔卡特
typedef struct
{
	DWORD				dwSize;
    unsigned short		usCompanyID[2];			// 公司ID，数值，不同的第三方服务公司，考虑4字节对齐，目前只用数组第一个
    char				szDeviceNO[32];			// 前端设备序列号，字符串，包括'\0'结束符共32byte
    char				szVSName[32];			// 前端设备名称，字符串，包括'\0'结束符共16byte
    char				szVapPath[32];			// VAP路径
    unsigned short		usTcpPort;				// TCP端口，数值：数值 1~65535 
    unsigned short		usUdpPort;				// UDP端口，数值：数值 1~65535
    bool				bCsEnable[4];			// 中心服务器使能标志，数值：true使能，false不使能，考虑4字节对齐，目前只用数组第一个
    char				szCsIP[16];				// 中心服务器IP地址，字符串，包括'\0'结束符共16byte
    unsigned short		usCsPort[2];			// 中心服务器端口，数值：数值 1~65535，考虑4字节对齐，目前只用数组第一个
    bool				bHsEnable[4];			// 心跳服务器使能标志，数值：true使能，false不使能，考虑4字节对齐，目前只用数组第一个
    char				szHsIP[16];				// 心跳服务器IP地址，字符串，包括'\0'结束符共16byte
    unsigned short		usHsPort[2];			// 心跳服务器端口，数值：数值 1~65535，考虑4字节对齐，目前只用数组第一个
    int					iHsIntervalTime;		// 心跳服务器间隔周期，数值(单位:秒)
    bool				bRsEnable[4];			// 注册服务器使能标志，数值：true使能，false不使能，考虑4字节对齐，目前只用数组第一个
    char				szRsIP[16];				// 注册服务器IP地址，字符串，包括'\0'结束符共16byte
    unsigned short		usRsPort[2];			// 注册服务器端口，数值：数值 1~65535，考虑4字节对齐，目前只用数组第一个
    int					iRsAgedTime;			// 注册服务器有效时间，数值(单位:小时)
    char				szAuthorizeServerIp[16];// 鉴权服务器IP
    unsigned short		usAuthorizePort[2];		// 鉴权服务器端口，考虑4字节对齐，目前只用数组第一个
    char				szAuthorizeUsername[32];// 鉴权服务器帐号
    char				szAuthorizePassword[36];// 鉴权服务器密码
    
    char				szIpACS[16];			// ACS(自动注册服务器) IP
    unsigned short		usPortACS[2];			// ACS Port，考虑4字节对齐，目前只用数组第一个
    char				szUsernameACS[32];		// ACS用户名
    char				szPasswordACS[36];		// ACS密码
    bool				bVideoMonitorEnabled[4];// DVS是否定期上报前端视频信号监控信息，数值：true使能，false不使能
    int					iVideoMonitorInterval;	// 上报周期(分钟)
    
    char				szCoordinateGPS[64];	// GPS坐标
    char				szPosition[32];			// 设备位置
    char				szConnPass[36];			// 设备接入码
} DHDEV_INTERVIDEO_BELL_CFG;

// 平台接入配置 － 中兴力维
typedef struct  
{
	DWORD				dwSize;
	unsigned short		nSevPort;				// 服务器端口，数值，数值1~65535
    char				szSevIp[DH_INTERVIDEO_NSS_IP]; // 服务器IP地址，字符串，包括'\0'结束符共32byte
    char				szDevSerial[DH_INTERVIDEO_NSS_SERIAL]; // 前端设备序列号，字符串，包括'\0'结束符共32byte
    char				szUserName[DH_INTERVIDEO_NSS_USER];
    char				szPwd[DH_INTERVIDEO_NSS_PWD];
} DHDEV_INTERVIDEO_NSS_CFG;


////////////////////////////////HDVR专用//////////////////////////////////
// 报警联动扩展结构体
typedef struct 
{
	/* 消息处理方式，可以同时多种处理方式，包括
	 * 0x00000001 - 报警上传
	 * 0x00000002 - 联动录象
	 * 0x00000004 - 云台联动
	 * 0x00000008 - 发送邮件
	 * 0x00000010 - 本地轮巡
	 * 0x00000020 - 本地提示
	 * 0x00000040 - 报警输出
	 * 0x00000080 - Ftp上传
	 * 0x00000100 - 蜂鸣
	 * 0x00000200 - 语音提示
	 * 0x00000400 - 抓图
	*/

	/* 当前报警所支持的处理方式，按位掩码表示 */
	DWORD				dwActionMask;

	/* 触发动作，按位掩码表示，具体动作所需要的参数在各自的配置中体现 */
	DWORD				dwActionFlag;
	
	/* 报警触发的输出通道，报警触发的输出，为1表示触发该输出 */ 
	BYTE				byRelAlarmOut[DH_MAX_ALARMOUT_NUM_EX];
	DWORD				dwDuration;				/* 报警持续时间 */

	/* 联动录象 */
	BYTE				byRecordChannel[DH_MAX_VIDEO_IN_NUM_EX]; /* 报警触发的录象通道，为1表示触发该通道 */
	DWORD				dwRecLatch;				/* 录象持续时间 */

	/* 抓图通道 */
	BYTE				bySnap[DH_MAX_VIDEO_IN_NUM_EX];
	/* 轮巡通道 */
	BYTE				byTour[DH_MAX_VIDEO_IN_NUM_EX];

	/* 云台联动 */
	DH_PTZ_LINK			struPtzLink[DH_MAX_VIDEO_IN_NUM_EX];
	DWORD				dwEventLatch;			/* 联动开始延时时间，s为单位，范围是0~15，默认值是0 */
	/* 报警触发的无线输出通道，报警触发的输出，为1表示触发该输出 */ 
	BYTE				byRelWIAlarmOut[DH_MAX_ALARMOUT_NUM_EX];
	BYTE				bMessageToNet;
	BYTE                bMMSEn;                /*短信报警使能*/
	BYTE                bySnapshotTimes;       /*短信发送抓图张数 */
	BYTE				bMatrixEn;				/*!< 矩阵使能 */
	DWORD				dwMatrix;				/*!< 矩阵掩码 */			
	BYTE				bLog;					/*!< 日志使能，目前只有在WTN动态检测中使用 */
	BYTE				bSnapshotPeriod;		/*!<抓图帧间隔，每隔多少帧抓一张图片，一定时间内抓拍的张数还与抓图帧率有关。0表示不隔帧，连续抓拍。*/
	BYTE				byReserved[510];   
} DH_MSG_HANDLE_EX;

// 外部报警扩展
typedef struct
{
	BYTE				byAlarmType;			// 报警器类型，0：常闭，1：常开
	BYTE				byAlarmEn;				// 报警使能
	BYTE				byReserved[2];						
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE_EX	struHandle;				// 处理方式
} DH_ALARMIN_CFG_EX, *LPDHDEV_ALARMIN_CFG_EX; 

// 动态检测报警
typedef struct 
{
	BYTE				byMotionEn;				// 动态检测报警使能
	BYTE				byReserved;
	WORD				wSenseLevel;			// 灵敏度
	WORD				wMotionRow;				// 动态检测区域的行数
	WORD				wMotionCol;				// 动态检测区域的列数
	BYTE				byDetected[DH_MOTION_ROW][DH_MOTION_COL]; // 检测区域，最多32*32块区域
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE_EX		struHandle;				//处理方式
} DH_MOTION_DETECT_CFG_EX;

// 静态检测报警 
typedef struct 
{
	BYTE				byStaticEn;				// 静态检测报警使能
	BYTE				byLatch;                // 检测延时    
	WORD				wSenseLevel;			// 灵敏度
	WORD				wStaticRow;				// 静态检测区域的行数
	WORD				wStaticCol;				// 静态检测区域的列数
	BYTE				byDetected[DH_STATIC_ROW][DH_STATIC_COL]; // 检测区域，最多32*32块区域
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE_EX	struHandle;				//处理方式
} DH_STATIC_DETECT_CFG_EX;

// 视频丢失报警
typedef struct
{
	BYTE				byAlarmEn;				// 视频丢失报警使能
	BYTE				byReserved[3];
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE_EX	struHandle;				// 处理方式
} DH_VIDEO_LOST_CFG_EX;

// 图像遮挡报警
typedef struct
{
	BYTE				byBlindEnable;			// 使能
	BYTE				byBlindLevel;			// 灵敏度1-6
	BYTE				byReserved[2];
	DH_TSECT			stSect[DH_N_WEEKS][DH_N_REC_TSECT];	//NSP
	DH_MSG_HANDLE_EX	struHandle;				// 处理方式
} DH_BLIND_CFG_EX;

// 硬盘消息(内部报警)
typedef struct 
{
	BYTE				byNoDiskEn;				// 无硬盘时报警
	BYTE				byReserved_1[3];
	DH_TSECT			stNDSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE_EX	struNDHandle;			// 处理方式
	
	BYTE				byLowCapEn;				// 硬盘低容量时报警
	BYTE				byLowerLimit;			// 容量阀值，0-99
	BYTE				byReserved_2[2];
	DH_TSECT			stLCSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE_EX	struLCHandle;			// 处理方式
	
	BYTE				byDiskErrEn;			// 硬盘故障报警
	BYTE				bDiskNum;
	BYTE				byReserved_3[2];
	DH_TSECT			stEDSect[DH_N_WEEKS][DH_N_REC_TSECT]; //NSP
	DH_MSG_HANDLE_EX	struEDHandle;			// 处理方式
} DH_DISK_ALARM_CFG_EX;

typedef struct
{
	BYTE				byEnable;
	BYTE				byReserved[3];
	DH_MSG_HANDLE_EX	struHandle;
} DH_NETBROKEN_ALARM_CFG_EX;

// 前端接入配置参数信息
typedef struct __DEV_ENCODER_CFG 
{
	int					nChannels;				// 数字通道个数
	DEV_ENCODER_INFO	stuDevInfo[32];			// 各数字通道的前端编码器信息
	BYTE				byHDAbility;			// 数字通道中最多可支持高清视频个数(为0表示不支持高清设置)
												// 注：如果支持高清设置，高清通道为0~N-1，若将N之后的数字通道设置为高清，有可能保存不成功
	BYTE				bTVAdjust;				// 设备是否支持TV调节, 0:不支持 1:支持.
	BYTE				bDecodeTour;			// 设备是否支持解码轮巡, 0:不支持 大于0:表示前端支持轮巡最大设备数.
	BYTE				bRemotePTZCtl;			// 指示是否支持远程云台控制。
	char				reserved[12];
} DEV_ENCODER_CFG, *LPDEV_ENCODER_CFG;

/////////////////////////////////淘汰类型/////////////////////////////////

// 查询设备工作状态通道信息，相关接口已淘汰，请不要使用
typedef struct
{
	BYTE				byRecordStatic;			// 通道是否在录像；0：不录像，1：手动录像，2：自动录象
	BYTE				bySignalStatic;			// 连接的信号状态；0：正常，1：信号丢失
	BYTE				byHardwareStatic;		// 通道硬件状态；0：正常，1：异常，例如DSP死掉
	char				reserve;
	DWORD				dwBitRate;				// 实际码率
	DWORD				dwLinkNum;				// 客户端连接的个数
	DWORD				dwClientIP[DH_MAX_LINK];// 客户端的IP地址
} NET_DEV_CHANNELSTATE, *LPNET_DEV_CHANNELSTATE;

// 查询设备工作状态，相关接口已淘汰，请不要使用
typedef struct
{
	DWORD				dwDeviceStatic;			// 设备的状态；0x00：正常，0x01：CPU占用过高，0x02：硬件错误
	NET_DEV_DISKSTATE	stHardDiskStatic[DH_MAX_DISKNUM]; 
	NET_DEV_CHANNELSTATE stChanStatic[DH_MAX_CHANNUM];	//通道的状态
	BYTE				byAlarmInStatic[DH_MAX_ALARMIN];//报警端口的状态；0：没有报警，1：有报警
	BYTE				byAlarmOutStatic[DH_MAX_ALARMOUT]; //报警输出端口的状态；0：没有输出，1：有报警输出
	DWORD				dwLocalDisplay;			// 本地显示状态；0：正常，1：不正常
} NET_DEV_WORKSTATE, *LPNET_DEV_WORKSTATE;

// 协议信息
typedef struct 
{
	char				protocolname[12];		// 协议名
	unsigned int		baudbase;				// 波特率
	unsigned char		databits;				// 数据位
	unsigned char		stopbits;				// 停止位
	unsigned char		parity;					// 校验位
	unsigned char		reserve;
} PROTOCOL_INFO, *LPPROTOCOL_INFO;

// 语音对讲参数配置
typedef struct 
{
	// 音频输入参数
	BYTE				byInFormatTag;			// 编码类型，如PCM
	BYTE				byInChannels;			// 声道数
	WORD				wInBitsPerSample;		// 采样深度					
	DWORD				dwInSamplesPerSec;		// 采样率

	// 音频输出参数
	BYTE				byOutFormatTag;			// 编码类型，如PCM
	BYTE				byOutChannels;			// 声道数
	WORD				wOutBitsPerSample;		// 采样深度				
	DWORD				dwOutSamplesPerSec;		// 采样率
} DHDEV_TALK_CFG, *LPDHDEV_TALK_CFG;

/************************************************************************
 ** 回调函数定义
 ***********************************************************************/

// 网络连接断开回调函数原形
typedef void (CALLBACK *fDisConnect)(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

// 网络连接恢复回调函数原形
typedef void (CALLBACK *fHaveReConnect)(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

// 动态子连接断开回调函数原形
typedef void (CALLBACK *fSubDisConnect)(EM_INTERFACE_TYPE emInterfaceType, BOOL bOnline, LONG lOperateHandle, LONG lLoginID, DWORD dwUser);

// 实时监视数据回调函数原形
typedef void (CALLBACK *fRealDataCallBack)(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser);

// 实时监视数据回调函数原形--扩展
typedef void (CALLBACK *fRealDataCallBackEx)(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LONG param, DWORD dwUser);

// 屏幕叠加回调函数原形
typedef void (CALLBACK *fDrawCallBack)(LONG lLoginID, LONG lPlayHandle, HDC hDC, DWORD dwUser);

// 回放数据回调函数原形
typedef int (CALLBACK *fDataCallBack)(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser);

// 回放进度回调函数原形
typedef void (CALLBACK *fDownLoadPosCallBack)(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser);

// 按时间回放进度回调函数原形
typedef void (CALLBACK *fTimeDownLoadPosCallBack) (LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo, DWORD dwUser);

// 消息回调函数原形
typedef BOOL (CALLBACK *fMessCallBack)(LONG lCommand, LONG lLoginID, char *pBuf, DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);

// 侦听服务器回调函数原形
typedef int (CALLBACK *fServiceCallBack)(LONG lHandle, char *pIp, WORD wPort, LONG lCommand, void *pParam, DWORD dwParamLen, DWORD dwUserData);

// 语音对讲的音频数据回调函数原形
typedef void (CALLBACK *pfAudioDataCallBack)(LONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag, DWORD dwUser);

// 升级设备程序回调函数原形
typedef void (CALLBACK *fUpgradeCallBack) (LONG lLoginID, LONG lUpgradechannel, int nTotalSize, int nSendSize, DWORD dwUser);

// 透明串口回调函数原形
typedef void (CALLBACK *fTransComCallBack) (LONG lLoginID, LONG lTransComChannel, char *pBuffer, DWORD dwBufSize, DWORD dwUser);

// 查询设备日志数据回调函数原形
typedef void (CALLBACK *fLogDataCallBack)(LONG lLoginID, char *pBuffer, DWORD dwBufSize, DWORD nTotalSize, BOOL bEnd, DWORD dwUser);

// 抓图回调函数原形
typedef void (CALLBACK *fSnapRev)(LONG lLoginID, BYTE *pBuf, UINT RevLen, UINT EncodeType, DWORD CmdSerial, DWORD dwUser);

// GPS信息订阅回调
typedef void (CALLBACK *fGPSRev)(LONG lLoginID, GPS_Info GpsInfo, DWORD dwUserData);

// 异步数据回调
typedef void (CALLBACK *fMessDataCallBack)(LONG lCommand, LPNET_CALLBACK_DATA lpData, DWORD dwUser);

// 文件传输回调
typedef void (CALLBACK *fTransFileCallBack)(LONG lHandle, int nTransType, int nState, int nSendSize, int nTotalSize, DWORD dwUser);

// 智能分析数据回调
typedef int  (CALLBACK *fAnalyzerDataCallBack)(LONG lAnalyzerHandle, DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser);


/************************************************************************
 ** 接口定义
 ***********************************************************************/

// SDK初始化
CLIENT_API BOOL CALL_METHOD CLIENT_Init(fDisConnect cbDisConnect, DWORD dwUser);

// SDK退出清理
CLIENT_API void CALL_METHOD CLIENT_Cleanup();

//------------------------------------------------------------------------

// 设置断线重连成功回调函数，设置后SDK内部断线自动重连
CLIENT_API void CALL_METHOD CLIENT_SetAutoReconnect(fHaveReConnect cbAutoConnect, DWORD dwUser);

// 设置动态子连接断线回调函数，目前SVR设备的监视和回放是短连接的。
CLIENT_API void CALL_METHOD CLIENT_SetSubconnCallBack(fSubDisConnect cbSubDisConnect, DWORD dwUser);

// 返回函数执行失败代码
CLIENT_API DWORD CALL_METHOD CLIENT_GetLastError(void);

// 设置连接设备超时时间和尝试次数
CLIENT_API void CALL_METHOD CLIENT_SetConnectTime(int nWaitTime, int nTryTimes);

// 设置登陆网络环境
CLIENT_API void CALL_METHOD CLIENT_SetNetworkParam(NET_PARAM *pNetParam);

// 获取SDK的版本信息
CLIENT_API DWORD CALL_METHOD CLIENT_GetSDKVersion();

//------------------------------------------------------------------------

// 向设备注册
CLIENT_API LONG CALL_METHOD CLIENT_Login(char *pchDVRIP, WORD wDVRPort, char *pchUserName, char *pchPassword, LPNET_DEVICEINFO lpDeviceInfo, int *error = 0);

// 扩展接口；nSpecCap = 0为TCP方式下的登入，nSpecCap = 2为主动注册的登入，nSpecCap = 3为组播方式下的登入，nSpecCap = 4为UDP方式下的登入，nSpecCap = 6为只建主连接下的登入，nSpecCap = 7为SSL加密
CLIENT_API LONG CALL_METHOD CLIENT_LoginEx(char *pchDVRIP, WORD wDVRPort, char *pchUserName, char *pchPassword, int nSpecCap, void* pCapParam, LPNET_DEVICEINFO lpDeviceInfo, int *error = 0);

// 向设备注销
CLIENT_API BOOL CALL_METHOD CLIENT_Logout(LONG lLoginID);

//------------------------------------------------------------------------

// 开始实时监视
CLIENT_API LONG CALL_METHOD CLIENT_RealPlay(LONG lLoginID, int nChannelID, HWND hWnd);

// 开始实时监视--扩展
CLIENT_API LONG CALL_METHOD CLIENT_RealPlayEx(LONG lLoginID, int nChannelID, HWND hWnd, DH_RealPlayType rType = DH_RType_Realplay);

// 多画面实时预览
CLIENT_API LONG CALL_METHOD CLIENT_MultiPlay(LONG lLoginID, HWND hWnd);

// 停止多画面实时预览
CLIENT_API BOOL CALL_METHOD CLIENT_StopMultiPlay(LONG lMultiHandle);

// 抓图；hPlayHandle为监视或回放句柄
CLIENT_API BOOL CALL_METHOD CLIENT_CapturePicture(LONG hPlayHandle, const char *pchPicFileName);

// 设置实时监视数据回调
CLIENT_API BOOL CALL_METHOD CLIENT_SetRealDataCallBack(LONG lRealHandle, fRealDataCallBack cbRealData, DWORD dwUser);

// 设置实时监视数据回调--扩展
CLIENT_API BOOL CALL_METHOD CLIENT_SetRealDataCallBackEx(LONG lRealHandle, fRealDataCallBackEx cbRealData, DWORD dwUser, DWORD dwFlag);

// 设置图象流畅性
CLIENT_API BOOL	CALL_METHOD CLIENT_AdjustFluency(LONG lRealHandle, int nLevel);

// 保存数据为文件
CLIENT_API BOOL CALL_METHOD CLIENT_SaveRealData(LONG lRealHandle, const char *pchFileName);

// 结束保存数据为文件
CLIENT_API BOOL CALL_METHOD CLIENT_StopSaveRealData(LONG lRealHandle);

// 设置图像属性
CLIENT_API BOOL CALL_METHOD CLIENT_ClientSetVideoEffect(LONG lPlayHandle, unsigned char nBrightness, unsigned char nContrast, unsigned char nHue, unsigned char nSaturation);

// 获取图像属性
CLIENT_API BOOL CALL_METHOD CLIENT_ClientGetVideoEffect(LONG lPlayHandle, unsigned char *nBrightness, unsigned char *nContrast, unsigned char *nHue, unsigned char *nSaturation);

// 设置屏幕叠加回调
CLIENT_API void CALL_METHOD CLIENT_RigisterDrawFun(fDrawCallBack cbDraw, DWORD dwUser);

// 打开声音
CLIENT_API BOOL CALL_METHOD CLIENT_OpenSound(LONG hPlayHandle);

// 设置音量；lPlayHandle为监视或回放句柄
CLIENT_API BOOL CALL_METHOD CLIENT_SetVolume(LONG lPlayHandle, int nVolume);

// 关闭声音
CLIENT_API BOOL CALL_METHOD CLIENT_CloseSound();

// 停止实时预览
CLIENT_API BOOL CALL_METHOD CLIENT_StopRealPlay(LONG lRealHandle);

// 停止实时预览--扩展
CLIENT_API BOOL CALL_METHOD CLIENT_StopRealPlayEx(LONG lRealHandle);

//------------------------------------------------------------------------

// 通用云台控制
CLIENT_API BOOL CALL_METHOD CLIENT_PTZControl(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, DWORD dwStep, BOOL dwStop);

// 大华云台控制
CLIENT_API BOOL CALL_METHOD CLIENT_DHPTZControl(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, unsigned char param1, unsigned char param2, unsigned char param3, BOOL dwStop);

// 大华云台控制扩展接口，支持三维快速定位
CLIENT_API BOOL CALL_METHOD CLIENT_DHPTZControlEx(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, LONG lParam1, LONG lParam2, LONG lParam3, BOOL dwStop);

//------------------------------------------------------------------------

// 查询时间段内是否有录像文件
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordTime(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char* pchCardid, BOOL *bResult, int waittime=1000);

// 查询时间段内的所有录像文件
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordFile(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char* pchCardid, LPNET_RECORDFILE_INFO nriFileinfo, int maxlen, int *filecount, int waittime=1000, BOOL bTime = FALSE);

// 查询最早录像时间
CLIENT_API BOOL CALL_METHOD CLIENT_QueryFurthestRecordTime(LONG lLoginID, int nRecordFileType, char *pchCardid, NET_FURTHEST_RECORD_TIME* pFurthrestTime, int nWaitTime);

// 开始查找录像文件
CLIENT_API LONG	CALL_METHOD CLIENT_FindFile(LONG lLoginID, int nChannelId, int nRecordFileType, char* cardid, LPNET_TIME time_start, LPNET_TIME time_end, BOOL bTime, int waittime);

// 查找录像文件
CLIENT_API int	CALL_METHOD CLIENT_FindNextFile(LONG lFindHandle,LPNET_RECORDFILE_INFO lpFindData);

// 结束录像文件查找
CLIENT_API BOOL CALL_METHOD CLIENT_FindClose(LONG lFindHandle);

// 按文件方式回放
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByRecordFile(LONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

// 按文件方式回放--扩展
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByRecordFileEx(LONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser, fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);

//按文件方式回放--控制抽帧帧率
CLIENT_API LONG CALL_METHOD CLIENT_FramCotrolPlayBackByRecordFile(LONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser, fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser, unsigned int nCutFrameRate);

// 按时间方式回放
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByTime(LONG lLoginID, int nChannelID, LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser);

// 按时间方式回放--扩展
CLIENT_API LONG CALL_METHOD CLIENT_PlayBackByTimeEx(LONG lLoginID, int nChannelID, LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser, fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);

//按时间方式回放--控制抽帧帧率
CLIENT_API LONG CALL_METHOD CLIENT_FramCotrolPlayBackByTime(LONG lLoginID, int nChannelID, LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser, fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser, unsigned int nCutFrameRate);

// 定位录像回放起始点
CLIENT_API BOOL CALL_METHOD CLIENT_SeekPlayBack(LONG lPlayHandle, unsigned int offsettime, unsigned int offsetbyte);

// 暂停或恢复录像回放
CLIENT_API BOOL CALL_METHOD CLIENT_PausePlayBack(LONG lPlayHandle, BOOL bPause);

// 快进录像回放
CLIENT_API BOOL CALL_METHOD CLIENT_FastPlayBack(LONG lPlayHandle);

// 慢进录像回放
CLIENT_API BOOL CALL_METHOD CLIENT_SlowPlayBack(LONG lPlayHandle);

// 步进录像回放
CLIENT_API BOOL CALL_METHOD CLIENT_StepPlayBack(LONG lPlayHandle, BOOL bStop);

// 设置回放帧速
CLIENT_API BOOL CALL_METHOD CLIENT_SetFramePlayBack(LONG lPlayHandle, int framerate);

// 获取回放帧速
CLIENT_API BOOL CALL_METHOD CLIENT_GetFramePlayBack(LONG lPlayHandle, int *fileframerate, int *playframerate);

// 恢复正常回放速度
CLIENT_API BOOL CALL_METHOD CLIENT_NormalPlayBack(LONG lPlayHandle);

// 获取回放OSD时间
CLIENT_API BOOL CALL_METHOD CLIENT_GetPlayBackOsdTime(LONG lPlayHandle, LPNET_TIME lpOsdTime, LPNET_TIME lpStartTime, LPNET_TIME lpEndTime);

// 停止录像回放
CLIENT_API BOOL CALL_METHOD CLIENT_StopPlayBack(LONG lPlayHandle);

// 下载录像文件
CLIENT_API LONG CALL_METHOD CLIENT_DownloadByRecordFile(LONG lLoginID,LPNET_RECORDFILE_INFO lpRecordFile, char *sSavedFileName, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

// 通过时间下载录像
CLIENT_API LONG CALL_METHOD CLIENT_DownloadByTime(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char *sSavedFileName, fTimeDownLoadPosCallBack cbTimeDownLoadPos, DWORD dwUserData);

// 查询录像下载进度
CLIENT_API BOOL CALL_METHOD CLIENT_GetDownloadPos(LONG lFileHandle, int *nTotalSize, int *nDownLoadSize);

// 停止录像下载
CLIENT_API BOOL CALL_METHOD CLIENT_StopDownload(LONG lFileHandle);

//------------------------------------------------------------------------

// 设置报警回调函数
CLIENT_API void CALL_METHOD CLIENT_SetDVRMessCallBack(fMessCallBack cbMessage,DWORD dwUser);

// 向设备订阅报警
CLIENT_API BOOL CALL_METHOD CLIENT_StartListen(LONG lLoginID);

// 向设备订阅报警--扩展
CLIENT_API BOOL CALL_METHOD CLIENT_StartListenEx(LONG lLoginID);

// 停止订阅报警
CLIENT_API BOOL CALL_METHOD CLIENT_StopListen(LONG lLoginID);

//------------------------------------------------------------------------

// 主动注册功能，启动服务；nTimeout参数已无效
CLIENT_API LONG CALL_METHOD CLIENT_ListenServer(char* ip, WORD port, int nTimeout, fServiceCallBack cbListen, DWORD dwUserData);

// 停止服务
CLIENT_API BOOL CALL_METHOD CLIENT_StopListenServer(LONG lServerHandle);

// 响应设备的注册请求
CLIENT_API BOOL CALL_METHOD CLIENT_ResponseDevReg(char *devSerial, char* ip, WORD port, BOOL bAccept);

//------------------------------------------------------------------------

// 报警上传功能，启动服务；dwTimeOut参数已无效
CLIENT_API LONG CALL_METHOD CLIENT_StartService(WORD wPort, char *pIp = NULL, fServiceCallBack pfscb = NULL, DWORD dwTimeOut = 0xffffffff, DWORD dwUserData = 0);

// 停止服务
CLIENT_API BOOL CALL_METHOD CLIENT_StopService(LONG lHandle);

//------------------------------------------------------------------------

// 设置语音对讲模式，客户端方式还是服务器方式
CLIENT_API BOOL CALL_METHOD CLIENT_SetDeviceMode(LONG lLoginID, EM_USEDEV_MODE emType, void* pValue);

// 打开语音对讲
CLIENT_API LONG CALL_METHOD CLIENT_StartTalkEx(LONG lLoginID, pfAudioDataCallBack pfcb, DWORD dwUser);

// 开始PC端录音
CLIENT_API BOOL CALL_METHOD CLIENT_RecordStart();

// 结束PC端录音
CLIENT_API BOOL CALL_METHOD CLIENT_RecordStop();

// 发送语音数据到设备
CLIENT_API LONG CALL_METHOD CLIENT_TalkSendData(LONG lTalkHandle, char *pSendBuf, DWORD dwBufSize);

// 解码音频数据
CLIENT_API void CALL_METHOD CLIENT_AudioDec(char *pAudioDataBuf, DWORD dwBufSize);

// 设置语音对讲的音量
CLIENT_API BOOL CALL_METHOD CLIENT_SetAudioClientVolume(LONG lTalkHandle, WORD wVolume);

// 停止语音对讲
CLIENT_API BOOL CALL_METHOD CLIENT_StopTalkEx(LONG lTalkHandle);

// 添加设备到广播组
CLIENT_API BOOL CALL_METHOD CLIENT_AudioBroadcastAddDev(LONG lLoginID);

// 从广播组中删除设备
CLIENT_API BOOL CALL_METHOD CLIENT_AudioBroadcastDelDev(LONG lLoginID);

// 音频编码--初始化(特定标准格式->大华格式)
CLIENT_API int  CALL_METHOD CLIENT_InitAudioEncode(DH_AUDIO_FORMAT aft);

// 音频编码--数据编码
CLIENT_API int	CALL_METHOD	CLIENT_AudioEncode(LONG lTalkHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen);

// 音频编码--完成退出
CLIENT_API int	CALL_METHOD	CLIENT_ReleaseAudioEncode();

//------------------------------------------------------------------------

// 查询设备日志
CLIENT_API BOOL CALL_METHOD CLIENT_QueryLog(LONG lLoginID, char *pLogBuffer, int maxlen, int *nLogBufferlen, int waittime=3000);

// 查询设备日志，以分页方式查询
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDeviceLog(LONG lLoginID, QUERY_DEVICE_LOG_PARAM *pQueryParam, char *pLogBuffer, int nLogBufferLen, int *pRecLogNum, int waittime=3000);

// 查道通道录像状态
CLIENT_API BOOL CALL_METHOD CLIENT_QueryRecordState(LONG lLoginID, char *pRSBuffer, int maxlen, int *nRSBufferlen, int waittime=1000);

// 查询设备状态
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDevState(LONG lLoginID, int nType, char *pBuf, int nBufLen, int *pRetLen, int waittime=1000);

// 查询系统能力信息
CLIENT_API BOOL CALL_METHOD CLIENT_QuerySystemInfo(LONG lLoginID, int nSystemType, char *pSysInfoBuffer, int maxlen, int *nSysInfolen, int waittime=1000);

// 获取通道码流
CLIENT_API LONG CALL_METHOD CLIENT_GetStatiscFlux(LONG lLoginID, LONG lPlayHandle);

// 获取云台信息
CLIENT_API BOOL  CALL_METHOD CLIENT_GetPtzOptAttr(LONG lLoginID,DWORD dwProtocolIndex,LPVOID lpOutBuffer,DWORD dwBufLen,DWORD *lpBytesReturned,int waittime=500);

//------------------------------------------------------------------------

// 重启设备
CLIENT_API BOOL CALL_METHOD CLIENT_RebootDev(LONG lLoginID);

// 关闭设备
CLIENT_API BOOL CALL_METHOD CLIENT_ShutDownDev(LONG lLoginID);

// 设备控制
CLIENT_API BOOL CALL_METHOD CLIENT_ControlDevice(LONG lLoginID, CtrlType type, void *param, int waittime = 1000);

// 设置通道录像状态
CLIENT_API BOOL CALL_METHOD CLIENT_SetupRecordState(LONG lLoginID, char *pRSBuffer, int nRSBufferlen);

// 查询IO状态
CLIENT_API BOOL CALL_METHOD CLIENT_QueryIOControlState(LONG lLoginID, DH_IOTYPE emType, 
                                           void *pState, int maxlen, int *nIOCount, int waittime=1000);

// IO控制
CLIENT_API BOOL CALL_METHOD CLIENT_IOControl(LONG lLoginID, DH_IOTYPE emType, void *pState, int maxlen);

// 强制I帧；nChannelID：通道号，nSubChannel：码流类型(0：主，1：子码流1)
CLIENT_API BOOL CALL_METHOD CLIENT_MakeKeyFrame(LONG lLoginID, int nChannelID, int nSubChannel=0);

//------------------------------------------------------------------------

// 查询用户信息
CLIENT_API BOOL CALL_METHOD CLIENT_QueryUserInfo(LONG lLoginID, USER_MANAGE_INFO *info, int waittime=1000);

// 查询用户信息--扩展
CLIENT_API BOOL CALL_METHOD CLIENT_QueryUserInfoEx(LONG lLoginID, USER_MANAGE_INFO_EX *info, int waittime=1000);

// 操作设备用户
CLIENT_API BOOL CALL_METHOD CLIENT_OperateUserInfo(LONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime=1000);

// 操作设备用户--扩展
CLIENT_API BOOL CALL_METHOD CLIENT_OperateUserInfoEx(LONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime=1000);

//------------------------------------------------------------------------

// 创建透明串口通道
CLIENT_API LONG CALL_METHOD CLIENT_CreateTransComChannel(LONG lLoginID, int TransComType, unsigned int baudrate, unsigned int databits, unsigned int stopbits, unsigned int parity, fTransComCallBack cbTransCom, DWORD dwUser);

// 透明串口发送数据
CLIENT_API BOOL CALL_METHOD CLIENT_SendTransComData(LONG lTransComChannel, char *pBuffer, DWORD dwBufSize);

// 释放通明串口通道
CLIENT_API BOOL CALL_METHOD CLIENT_DestroyTransComChannel(LONG lTransComChannel);

// 查询透明串口状态
CLIENT_API BOOL   CALL_METHOD CLIENT_QueryTransComParams(LONG lLoginID, int TransComType, DH_COMM_STATE* pCommState, int nWaitTime = 500);

//------------------------------------------------------------------------

// 开始升级设备程序
CLIENT_API LONG CALL_METHOD CLIENT_StartUpgrade(LONG lLoginID, char *pchFileName, fUpgradeCallBack cbUpgrade, DWORD dwUser);

// 开始升级设备程序--扩展
CLIENT_API LONG CALL_METHOD CLIENT_StartUpgradeEx(LONG lLoginID, EM_UPGRADE_TYPE emType, char *pchFileName, fUpgradeCallBack cbUpgrade, DWORD dwUser);

// 发送数据
CLIENT_API BOOL CALL_METHOD CLIENT_SendUpgrade(LONG lUpgradeID);

// 结束升级设备程序
CLIENT_API BOOL CALL_METHOD CLIENT_StopUpgrade(LONG lUpgradeID);

//------------------------------------------------------------------------

// 查询配置信息
CLIENT_API BOOL  CALL_METHOD CLIENT_GetDevConfig(LONG lLoginID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned,int waittime=500);

// 设置配置信息
CLIENT_API BOOL  CALL_METHOD CLIENT_SetDevConfig(LONG lLoginID, DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer, DWORD dwInBufferSize, int waittime=500);

// 新配置接口，查询配置信息(以Json格式，具体见配置SDK)
CLIENT_API BOOL CALL_METHOD CLIENT_GetNewDevConfig(LONG lLoginID, char* szCommand, int nChannelID, char* szOutBuffer, DWORD dwOutBufferSize, int *error, int waittime=500);

// 新配置接口，设置配置信息(以Json格式，具体见配置SDK)
CLIENT_API BOOL CALL_METHOD CLIENT_SetNewDevConfig(LONG lLoginID, char* szCommand, int nChannelID, char* szInBuffer, DWORD dwInBufferSize, int *error, int *restart, int waittime=500);

//------------------------------------------------------------------------

// 查询设备通道名称
CLIENT_API BOOL CALL_METHOD CLIENT_QueryChannelName(LONG lLoginID, char *pChannelName, int maxlen, int *nChannelCount, int waittime=1000);

// 设置设备通道名称
CLIENT_API BOOL  CALL_METHOD CLIENT_SetupChannelName(LONG lLoginID,char *pbuf, int nbuflen);

// 设置设备通道字符叠加
CLIENT_API BOOL  CALL_METHOD CLIENT_SetupChannelOsdString(LONG lLoginID, int nChannelNo, DH_CHANNEL_OSDSTRING* struOsdString, int nbuflen);

// 查询设备当前时间
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDeviceTime(LONG lLoginID, LPNET_TIME pDeviceTime, int waittime=1000);

// 设置设备当前时间
CLIENT_API BOOL CALL_METHOD CLIENT_SetupDeviceTime(LONG lLoginID, LPNET_TIME pDeviceTime);

// 设置设备限制码流
CLIENT_API BOOL CALL_METHOD CLIENT_SetMaxFlux(LONG lLoginID, WORD wFlux);

//------------------------------------------------------------------------

// 导入配置文件
CLIENT_API LONG CALL_METHOD CLIENT_ImportConfigFile(LONG lLoginID, char *szFileName, fDownLoadPosCallBack cbUploadPos, DWORD dwUserData, DWORD param=0);

// 停止导入配置文件
CLIENT_API BOOL CALL_METHOD CLIENT_StopImportCfgFile(LONG lImportHandle);

// 导出配置文件
CLIENT_API LONG CALL_METHOD CLIENT_ExportConfigFile(LONG lLoginID, DH_CONFIG_FILE_TYPE emConfigFileType, char *szSavedFilePath, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

// 停止导出配置文件
CLIENT_API BOOL CALL_METHOD CLIENT_StopExportCfgFile(LONG lExportHandle);

//------------------------------------------------------------------------

// 通过设备名字或者设备序列号向DDNS服务器查询设备IP
CLIENT_API BOOL CALL_METHOD CLIENT_GetDVRIPByResolveSvr(char *pchDVRIP, WORD wDVRPort, BYTE *sDVRName, WORD wDVRNameLen, BYTE *sDVRSerialNumber, WORD wDVRSerialLen, char* sGetIP);

// 搜索局域网内IPC、NVS等设备
CLIENT_API BOOL CALL_METHOD CLIENT_SearchDevices(char* szBuf, int nBufLen, int* pRetLen, DWORD dwSearchTime);

//------------------------------------------------------------------------

// 平台接入接口
CLIENT_API BOOL CALL_METHOD CLIENT_GetPlatFormInfo(LONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned,int waittime=500);
CLIENT_API BOOL CALL_METHOD CLIENT_SetPlatFormInfo(LONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpInBuffer, DWORD dwInBufferSize, int waittime=500);


///////////////////////////////车载设备接口///////////////////////////////

// 设置抓图回调函数
CLIENT_API void CALL_METHOD CLIENT_SetSnapRevCallBack(fSnapRev OnSnapRevMessage, DWORD dwUser);

// 抓图请求
CLIENT_API BOOL CALL_METHOD CLIENT_SnapPicture(LONG lLoginID, SNAP_PARAMS par);

// 设置GPS订阅回调函数
CLIENT_API void CALL_METHOD CLIENT_SetSubcribeGPSCallBack(fGPSRev OnGPSMessage, DWORD dwUser);

// GPS信息订阅
CLIENT_API BOOL CALL_METHOD CLIENT_SubcribeGPS (LONG lLoginID, BOOL bStart, LONG KeepTime, LONG InterTime);


//////////////////////////////解码器设备接口//////////////////////////////

// 查询解码器信息
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDecoderInfo(LONG lLoginID, LPDEV_DECODER_INFO lpDecInfo, int waittime=1000);

// 查询解码器当前TV信息
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDecoderTVInfo(LONG lLoginID, int nMonitorID, LPDEV_DECODER_TV lpMonitorInfo, int waittime=1000);

// 查询解码通道信息
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDecEncoderInfo(LONG lLoginID, int nEncoderID, LPDEV_ENCODER_INFO lpEncoderInfo, int waittime=1000);

// 设置解码器TV输出使能
CLIENT_API BOOL CALL_METHOD CLIENT_SetDecTVOutEnable(LONG lLoginID, BYTE *pDecTVOutEnable, int nBufLen, int waittime=1000);

//------------------------------------------------------------------------

// 设置异步回调函数
CLIENT_API BOOL CALL_METHOD CLIENT_SetOperateCallBack(LONG lLoginID, fMessDataCallBack cbMessData, DWORD dwUser);

// 控制解码器TV画面分割，接口为异步方式
CLIENT_API LONG CALL_METHOD CLIENT_CtrlDecTVScreen(LONG lLoginID, int nMonitorID, BOOL bEnable, int nSplitType, BYTE *pEncoderChannel, int nBufLen, void* userdata=NULL);

// 解码器TV画面切换，接口为异步方式
// 根据nMonitorID(TV号)、nWndID(画面号)转换为nEncoderID(解码通道)公式：nEncoderID＝nMonitorID*nSplitNum(分割数)+nWndID
CLIENT_API LONG CALL_METHOD CLIENT_SwitchDecTVEncoder(LONG lLoginID, int nEncoderID, LPDEV_ENCODER_INFO lpEncoderInfo, void* userdata=NULL);

//------------------------------------------------------------------------

// 增加画面组合
CLIENT_API int CALL_METHOD CLIENT_AddTourCombin(LONG lLoginID, int nMonitorID, int nSplitType, BYTE *pEncoderChannnel, int nBufLen, int waittime=1000);

// 删除画面组合
CLIENT_API BOOL CALL_METHOD CLIENT_DelTourCombin(LONG lLoginID, int nMonitorID, int nCombinID, int waittime=1000);

// 修改画面组合
CLIENT_API BOOL CALL_METHOD CLIENT_SetTourCombin(LONG lLoginID, int nMonitorID, int nCombinID, int nSplitType, BYTE *pEncoderChannel, int nBufLen, int waittime=1000);

// 查询画面组合，nCombinID范围0～32
CLIENT_API BOOL CALL_METHOD CLIENT_QueryTourCombin(LONG lLoginID, int nMonitorID, int nCombinID, LPDEC_COMBIN_INFO lpDecCombinInfo, int waittime=1000);

// 设置轮巡操作
CLIENT_API BOOL CALL_METHOD CLIENT_SetDecoderTour(LONG lLoginID, int nMonitorID, LPDEC_TOUR_COMBIN lpDecTourInfo, int waittime=1000);

// 查询轮巡操作
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDecoderTour(LONG lLoginID, int nMonitorID, LPDEC_TOUR_COMBIN lpDecTourInfo, int waittime=1000);

// 查询当前解码通道流信息
CLIENT_API BOOL CALL_METHOD CLIENT_QueryDecChannelFlux(LONG lLoginID, int nEncoderID, LPDEV_DECCHANNEL_STATE lpChannelStateInfo, int waittime=1000);

// 解码器控制轮巡
CLIENT_API BOOL CALL_METHOD CLIENT_CtrlDecoderTour(LONG lLoginID, int nMonitorID, DEC_CTRL_TOUR_TYPE emActionParam, int waittime = 1000);

//------------------------------------------------------------------------

typedef void (CALLBACK *fDecPlayBackPosCallBack)(LONG lLoginID, int nEncoderID, DWORD dwTotalSize, DWORD dwPlaySize, DWORD dwUser);

// 设置回放进度回调函数
CLIENT_API BOOL CALL_METHOD CLIENT_SetDecPlaybackPos(LONG lLoginID, fDecPlayBackPosCallBack cbPlaybackPos, DWORD dwUser);

// 解码器TV画面回放，接口为异步方式
CLIENT_API LONG CALL_METHOD CLIENT_DecTVPlayback(LONG lLoginID, int nEncoderID, DEC_PLAYBACK_MODE emPlaybackMode, LPVOID lpInBuffer, DWORD dwInBufferSize, void* userdata=NULL);

// 解码器TV画面回放控制
CLIENT_API BOOL CALL_METHOD CLIENT_CtrlDecPlayback(LONG lLoginID, int nEncoderID, DEC_CTRL_PLAYBACK_TYPE emCtrlType, int nValue, int waittime=1000);


///////////////////////////////智能设备接口///////////////////////////////

// 实时上传智能分析数据－图片
CLIENT_API LONG CALL_METHOD CLIENT_RealLoadPicture(LONG lLoginID, int nChannelID, DWORD dwAlarmType, fAnalyzerDataCallBack cbAnalyzerData, DWORD dwUser);

// 停止上传智能分析数据－图片
CLIENT_API BOOL CALL_METHOD CLIENT_StopLoadPic(LONG lAnalyzerHandle);


///////////////////////////////特殊版本接口///////////////////////////////

// 查询设备日志--扩展
CLIENT_API BOOL CALL_METHOD CLIENT_QueryLogEx(LONG lLoginID, DH_LOG_QUERY_TYPE logType, char *pLogBuffer, int maxlen, int *nLogBufferlen, void* reserved, int waittime=3000);

// 主动注册重定向功能，建立定向连接
CLIENT_API LONG CALL_METHOD CLIENT_ControlConnectServer(LONG lLoginID, char* RegServerIP, WORD RegServerPort, int TimeOut=3000);

// 连接主动注册
CLIENT_API BOOL CALL_METHOD CLIENT_ControlRegisterServer(LONG lLoginID, LONG ConnectionID, int waittime=1000);

// 断开定向连接
CLIENT_API BOOL CALL_METHOD CLIENT_ControlDisconnectRegServer(LONG lLoginID, LONG ConnectionID);

// 查询设备上主动注册服务器信息
CLIENT_API BOOL CALL_METHOD CLIENT_QueryControlRegServerInfo(LONG lLoginID, LPDEV_SERVER_AUTOREGISTER lpRegServerInfo, int waittime=2000);

// 文件上传接口
CLIENT_API LONG CALL_METHOD CLIENT_FileTransmit(LONG lLoginID, int nTransType, char* szInBuf, int nInBufLen, fTransFileCallBack cbTransFile, DWORD dwUserData, int waittime);

/////////////////////////////////淘汰接口/////////////////////////////////

// 查询系统服务器配置；该接口已淘汰，请使用CLIENT_GetDevConfig
CLIENT_API BOOL CALL_METHOD CLIENT_QueryConfig(LONG lLoginID, int nConfigType, char *pConfigbuf, int maxlen, int *nConfigbuflen, int waittime=1000);

// 设置系统服务器配置；该接口已淘汰，请使用CLIENT_SetDevConfig
CLIENT_API BOOL CALL_METHOD CLIENT_SetupConfig(LONG lLoginID, int nConfigType, char *pConfigbuf, int nConfigbuflen, int waittime=1000);

// 该接口已淘汰，请不要使用
CLIENT_API BOOL CALL_METHOD CLIENT_Reset(LONG lLoginID, BOOL bReset);

// 查询串口协议 － 该接口已淘汰，请使用CLIENT_GetDevConfig
CLIENT_API BOOL CALL_METHOD CLIENT_QueryComProtocol(LONG lLoginID, int nProtocolType, char *pProtocolBuffer, int maxlen, int *nProtocollen, int waittime=1000);

// 开始对讲；该接口已淘汰，请使用CLIENT_StartTalkEx
CLIENT_API BOOL CALL_METHOD CLIENT_StartTalk(LONG lRealHandle, BOOL bCustomSend=false);

// 结束对讲；该接口已淘汰，请使用CLIENT_StopTalkEx
CLIENT_API BOOL CALL_METHOD CLIENT_StopTalk(LONG lRealHandle);

// 发送自定义对讲数据；该接口已淘汰，请使用CLIENT_TalkSendData
CLIENT_API BOOL CALL_METHOD CLIENT_SendTalkData_Custom(LONG lRealHandle, char *pBuffer, DWORD dwBufSize);

// 设置实时预览缓冲大小
CLIENT_API BOOL CALL_METHOD CLIENT_SetPlayerBufNumber(LONG lRealHandle, DWORD dwBufNum);

// 通过时间下载文件
CLIENT_API BOOL CALL_METHOD CLIENT_GetFileByTime(LONG lLoginID, int nChannelID, LPNET_TIME lpStartTime, LPNET_TIME lpStopTime, char *sSavedFileName);

// 网络回放控制
CLIENT_API BOOL CALL_METHOD CLIENT_PlayBackControl(LONG lPlayHandle, DWORD dwControlCode, DWORD dwInValue, DWORD *lpOutValue);

// 查询设备工作状态 该接口已淘汰，请使用CLIENT_QueryDevState
CLIENT_API BOOL CALL_METHOD CLIENT_GetDEVWorkState(LONG lLoginID, LPNET_DEV_WORKSTATE lpWorkState, int waittime=1000);

// 异步查询设备日志
CLIENT_API BOOL CALL_METHOD CLIENT_QueryLogCallback(LONG lLoginID, fLogDataCallBack cbLogData, DWORD dwUser);



#ifdef __cplusplus
}
#endif

#endif // DHNETSDK_H










































