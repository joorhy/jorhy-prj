/***********************************************************************
** Copyright (C) Tongwei Video Technology Co.,Ltd. All rights reserved.
** Author       : YSW
** Date         : 2010-11-19
** Name         : dvrdvsconfig.h
** Version      : 1.0
** Description  :	描述DVR/DVS相关的一些基本特性
** Modify Record:
1:创建
***********************************************************************/
#ifndef __DVR_DVS_CONFIG_H__
#define __DVR_DVS_CONFIG_H__

#include "dvrdvstypedef.h"
//////////////////////////////////////////////////////////////////////////
const unsigned long DD_MAX_CAMERA_NUM	= 128;
const unsigned long DD_MAX_CAMERA_NUM_BYTE_LEN	= DD_MAX_CAMERA_NUM/8;
const unsigned long DD_MAX_SERIAL_NUMBER_LEN = 64;
const unsigned long DD_MAX_VERSION_BUF_LEN = 64;

const unsigned long	DD_MAX_NAME_LEN		= 64;	
const unsigned long	DD_MAX_NAME_BUF_LEN	= (DD_MAX_NAME_LEN * 2) + 4;

const unsigned long	DD_MAX_CAMERA_NAME_LEN		= 64;	
const unsigned long	DD_MAX_CAMERA_NAME_BUF_LEN	= (DD_MAX_CAMERA_NAME_LEN * 2) + 4;

const unsigned long DD_MAX_URL_LEN		= 256;
const unsigned long DD_MAX_URL_BUF_LEN	= DD_MAX_URL_LEN + 4;

const unsigned long DD_MAX_COLOR_CFG_NUM = 3;

const unsigned long DD_MAX_TEXT_LEN		= 64;
const unsigned long	DD_MAX_TEXT_BUF_LEN	= (DD_MAX_TEXT_LEN * 2) + 4;

const unsigned long DD_MAX_VIDEO_COVER_NUM = 3;

const unsigned long DD_MAX_USER_NAME_LEN	= 64;
const unsigned long DD_MAX_USER_NAME_BUF_LEN = (DD_MAX_USER_NAME_LEN * 2) + 4;
const unsigned long DD_MAX_PASSWORD_LEN		= 128;
const unsigned long DD_MAX_PASSWORD_BUF_LEN	= DD_MAX_PASSWORD_LEN + 4;

const unsigned long DD_MAX_PPPOE_ACCOUNT_LEN		= 128;
const unsigned long DD_MAX_PPPOE_ACCOUNT_BUF_LEN	= DD_MAX_PPPOE_ACCOUNT_LEN + 4;

const unsigned long DD_MAX_DDNS_ACCOUNT_LEN			= 128;
const unsigned long DD_MAX_DDNS_ACCOUNT_BUF_LEN		= DD_MAX_DDNS_ACCOUNT_LEN + 4;

const unsigned long DD_MAX_EMAIL_RECEIVE_ADDR_NUM = 3;

const unsigned long DD_MAX_MOTION_AREA_WIDTH_NUM = 1920/16;
const unsigned long DD_MAX_MOTION_AREA_HIGHT_NUM = ((1080/16) + 3) / 4;

const unsigned long DD_MAX_PRESET_NUM	= 128;
const unsigned long DD_MAX_CRUISE_NUM	= 32;
const unsigned long DD_MAX_TRACK_NUM	= 1;
const unsigned long DD_MAX_ACCOUNT_NUM	= 64;
const unsigned long DD_MAX_BUF_SIZE = 512*1024;
//////////////////////////////////////////////////////////////////////////

//设备信息：包含的内容，即可用于配置，也可用于查询设备信息
typedef struct _dd_device_info_
{
	unsigned long	iSize;		//本结构体长度

	unsigned long	deviceID;	//设备ID(0~255)
	char			deviceNo[DD_MAX_SERIAL_NUMBER_LEN];		//设备序列号，可能使用字母
	char			deviceName [DD_MAX_NAME_LEN];			//设备名称（注意考虑双字节字符）

	//以下为只读项
	//version
	char			firmwareVersion [DD_MAX_VERSION_BUF_LEN];
	char			firmwareBuildDate [DD_MAX_VERSION_BUF_LEN];
	char			hardwareVersion [DD_MAX_VERSION_BUF_LEN];
	char			kernelVersion [DD_MAX_VERSION_BUF_LEN];
	char			mcuVersion [DD_MAX_VERSION_BUF_LEN];

	//接口参数
	unsigned char	audioNum;
	unsigned char	localVideoInNum;
	unsigned char	netVideoInNum;
	unsigned char	sensorInNum;
	unsigned char	relayOutNum;

	unsigned char	rs232Num;
	unsigned char	rs485Num;
	unsigned char	networkPortNum;
	unsigned char	diskCtrlNum;
	unsigned char	DiskNum;
	unsigned char	vgaNum;
	unsigned char	usbNum;
}DD_DEVICE_INFO;

typedef struct _dd_basic_config_
{
	unsigned long iSize;				//本结构体长度

	unsigned long videoFormat;			//视频制式，取值参考DD_VIDEO_FORMAT

	unsigned long videoOut;				//视频输出设备
	unsigned long videoOutResolution;	//输出分辨率，取值参考DD_VGA_RESOLUTION
	unsigned long VGARefresh;			//VGA刷新率
	unsigned long screensaver;			//屏保时间（零表示不开启）

	unsigned long deviceLanguage;		//系统语言
	unsigned long passwordCheck;		//是否开启密码检查

	unsigned long RecycleRecord;		//是否允许覆盖录像

	//以下为一些只读项
	unsigned long videoFormatMask;			//支持的视频制式掩码（只读），取值为DD_VIDEO_FORMAT定义数据的掩码组合
	unsigned long videoOutMask;				//支持的视频输出设备掩码（只读）
	unsigned long videoOutResolutionMask;	//支持的视频输出设备分辨率掩码（只读），取值为DD_VGA_RESOLUTION定义数据的掩码组合
	unsigned long languageMask;				//支持的语言掩码（只读）
}DD_BASIC_CONFIG;

typedef struct _dd_date_time_config
{
	unsigned long iSize;		//本结构体长度

	unsigned char dateFormat;	//日期格式，取值为DD_DATE_MODE
	unsigned char timeFormat;	//时间格式，12代表12小时制，24代表24小时制
	unsigned char timeZone;		//时区，取值为DD_TIME_ZOME_NAME

	unsigned char enableNTP;	//是否开启NTP同步服务
	unsigned short	ntpPort;	//NTP端口
	unsigned short	recv;
	char	ntpServerAddr[DD_MAX_URL_BUF_LEN];	//NTP服务器地址
}DD_DATE_TIME_CONFIG;

typedef struct _dd_daylight_info_
{
	unsigned char InMonth;		//第几月进入DST
	unsigned char InMday;		//第几日进入DST（日期方式有效）
	unsigned char OutMonth;		//第几月出DST
	unsigned char OutMday;		//第几日出DST（日期方式有效）

	unsigned char InWeekIndex;	//第几周进入DST（周方式有效）
	unsigned char InWday;		//星期几进入DST（周方式有效）
	unsigned char OutWeekIndex;	//第几周出DST（周方式有效）
	unsigned char OutWday;		//星期几出DST（周方式有效）

	unsigned short InYear;		//进入DST的年份，不定有用，但是放在此，刚好可以对齐结构体，所以保留。
	unsigned short OutYear;		//出DST的年份，不定有用，但是放在此，刚好可以对齐结构体，所以保留。

	unsigned short enable;		//是否开启夏令时功能
	unsigned short type;		//夏令时设置方式：周或者日期方式

	unsigned long InSecond;		//进入DST一天内的秒偏移（0～86399），可转换成时分秒
	unsigned long OutSecond;	//出DST一天内的秒偏移（0～86399），可转换成时分秒

	unsigned long offSet;		//夏令时的偏移量（0～86399）秒。

}DD_DAYLIGHT_INFO;

typedef struct _dd_live_video_group_
{
	unsigned short	holdTime;	//停留时间（秒）,零表示无效
	unsigned short	channelNum;	//有效通道数目（只读）

	unsigned long	splitMode;	//分割模式，取值参考DD_VIEW_SPLIT_MODE

	//各区域对应的通道编号，数组下标代表通道编号，元素值代表窗体区域编号
	//0xff表示该通道无效
	unsigned char	channel [DD_MAX_CAMERA_NUM]; //各区域对应的通道编号
}DD_LIVE_VIDEO_GROUP;

typedef struct _dd_live_audio_group_
{
	unsigned short holdTime;		//停留时间（秒）,零表示无效
	unsigned char volume;			//音量（0~100)
	unsigned char channel;			//通道编号
}DD_LIVE_AUDIO_GROUP;

typedef struct _dd_live_display_
{
	unsigned long iSize;			//本结构体长度

	unsigned long showTime;			//是否显示系统时间
	unsigned long showNetwork;		//是否显示网络状态
	unsigned long showHDD;			//是否显示硬盘信息
	unsigned long showUSB;			//是否显示移动存储器信息

	unsigned short	alarmInNum;		//报警输入数目（只读）
	unsigned short	alarmOutNum;	//报警输出数目（只读）
	unsigned long	showAlarmIn;	//是否显示报警输入信息	
	unsigned long	showAlarmOut;	//是否显示报警输出信息

	unsigned long cameraNum;		//有效通道数目（只读）
	unsigned char showCameraName [DD_MAX_CAMERA_NUM];	//是否显示通道名称
	unsigned char showRecordStatus [DD_MAX_CAMERA_NUM];	//是否显示录像状态
}DD_LIVE_DISPLAY;

typedef struct _dd_channel_config_
{
	unsigned long iSize;						//本结构体长度

	unsigned long hide;							//是否隐藏通道
	char	name [DD_MAX_CAMERA_NAME_BUF_LEN];	//通道名称
}DD_CHANNEL_CONFIG;

typedef struct _dd_video_color_
{
	unsigned long	startTime;		//此套色彩对应的开始时间（一天内相对时间）

	unsigned char	brightness;		//亮度
	unsigned char	hue;			//色度
	unsigned char	saturation;		//饱和度
	unsigned char	contrast;		//对比度
}DD_VIDEO_COLOR;

typedef struct _dd_video_color_config_
{
	unsigned long	iSize;			//本结构体长度

	unsigned long	usedNum;		//使用的方案数目，默认为一
	DD_VIDEO_COLOR	videoColor[DD_MAX_COLOR_CFG_NUM];	//色彩方案
}DD_VIDEO_COLOR_CONFIG;

typedef struct _dd_position_
{
	unsigned short x;		//横坐标
	unsigned short y;		//纵坐标
}DD_POSITION;

typedef struct _dd_area_
{
	unsigned short x;		//横坐标
	unsigned short y;		//纵坐标

	unsigned short cx;		//宽度
	unsigned short cy;		//高度
}DD_AREA;

typedef struct _dd_video_osd_config_
{
	unsigned long iSize;					//本结构体长度

	unsigned char enableCameraName;			//叠加通道名称
	unsigned char enableTimeStamp;			//叠加时间戳
	unsigned char enableTimeStampWithWeek;	//时间戳上加星期
	unsigned char enableDefineText;			//叠加自定义文本

	DD_POSITION cameraName;					//通道名称的位置
	DD_POSITION timeStamp;					//时间戳的位置
	DD_POSITION defineText;					//自定义文本的位置
	char text [DD_MAX_TEXT_BUF_LEN];		//自定义文本

	struct  
	{
		unsigned long	enable;				//区域覆盖是否有效
		DD_AREA			area;				//区域参数
	}cover[DD_MAX_VIDEO_COVER_NUM];			//覆盖的区域参数
}DD_VIDEO_OSD_CONFIG;

typedef struct _dd_encode_config_
{
	unsigned long iSize;		//本结构体长度

	unsigned short resolution;	//分辨率，取值参考DD_VIDEO_SIZE
	unsigned short rate;		//帧率
	unsigned short encodeType;	//编码类型，取值参考DD_VIDEO_ENCODE_MODE
	unsigned short quality;		//画质，取值参考DD_IMAGE_QUALITY

	unsigned short minBitrate;	//码流下限
	unsigned short maxBitrate;	//码流上限
}DD_ENCODE_CONFIG;

typedef struct _dd_record_config_
{
	unsigned long iSize;			//本结构体长度

	unsigned char bOnlyVideo;		//录制视频（仅视频）
	unsigned char bWithAudio;		//录制音频（基于录制视频的基础上）
	unsigned char bindAudioChannel;	//对应的音频通道（不一定和视频通道编号一致）
	unsigned char bRedundancy;		//是否冗余录制

	unsigned short preAlarmTime;	//警前录像时间
	unsigned short postAlarmTime;	//警后录像时间

	unsigned short expired;			//录像过期时间
	unsigned short recv;			//保留字节
}DD_RECORD_CONFIG;

//此结构体为（只读）内容，用于查询设备支持参数。
typedef struct _dd_record_config_mask_
{
	unsigned long iSize;

	unsigned char bindAudioChannel;	//是否支持视音频通道绑定
	unsigned char bRedundancy;		//是否支持冗余录制
	unsigned char recv1;
	unsigned char recv2;

	unsigned short minPreAlarmTime;	//最小警前录像时间
	unsigned short maxPreAlarmTime;	//最大警前录像时间

	unsigned short minPostAlarmTime;	//最小警后录像时间
	unsigned short maxPostAlarmTime;	//最大警后录像时间

	unsigned short minExpired;		//最小录像数据过期时间
	unsigned short maxExpired;		//最大录像数据过期时间
}DD_RECORD_CONFIG_MASK;

//日排程结构，24代表24小时，unsigned long long的每一位代表每一分钟的状态
typedef struct _dd_date_schedule_
{
	unsigned long long hour [24];
}DD_DATE_SCHEDULE;

//周排程结构，7表示每周7天的排程
typedef struct _dd_week_schedule_
{
	DD_DATE_SCHEDULE week[7];
}DD_WEEK_SCHEDULE;

typedef struct _dd_network_ip_config_
{
	unsigned long iSize;			//本结构体长度

	unsigned long	useDHCP;		//是否使用动态网络地址

	unsigned long	IP;				//网络地址
	unsigned long	subnetMask;		//子网掩码
	unsigned long	gateway;		//网关

	unsigned long	preferredDNS;	//主网络域名服务器地址
	unsigned long	alternateDNS;	//从网络域名服务器地址

	unsigned long	usePPPoE;		//是否使用PPPoE
	char account[DD_MAX_PPPOE_ACCOUNT_BUF_LEN];	//PPPoE的帐号
	char password[DD_MAX_PASSWORD_BUF_LEN];		//PPPoE的密码
}DD_NETWORK_IP_CONFIG;

typedef struct _dd_network_advance_config_
{
	unsigned long iSize;			//本结构体长度

	unsigned char bMessagePort;		//是否支持消息端口（只读）
	unsigned char bAlarmPort;		//是否支持报警端口（只读）
	unsigned char bMultiCastIP;		//是否支持多播地址（只读）
	unsigned char bMTUByteNum;		//是否支持MTU字节数（只读）

	unsigned short httpPort;		//HTTP端口
	unsigned short datePort;		//数据端口
	unsigned short messagePort;		//消息命令端口
	unsigned short alarmPort;		//报警端口

	unsigned short maxOnlineUserNum;	//支持的最大在线用户数目（只读）
	unsigned short OnlineUserNum;		//在线用户数目

	unsigned long multiCastIP;		//多播地址
	unsigned long mtuByteNum;		//MTU字节数
}DD_NETWORK_ADVANCE_CONFIG;

typedef struct _dd_ddns_config_
{
	unsigned long iSize;			//本结构体长度

	unsigned short enable;			//是否启用DDNS
	unsigned short interval;		//上报更新周期

	unsigned long useDDNSServer;	//使用的DDNS服务器类型或者地址

	unsigned long userHostDomain;	//是否服务器主机域名

	char userName [DD_MAX_DDNS_ACCOUNT_BUF_LEN];	//DDNS帐号
	char password [DD_MAX_PASSWORD_BUF_LEN];		//DDNS密码

	char hostDomain [DD_MAX_URL_BUF_LEN];			//服务器主机域名（对应某个协议，可以指定服务器）
}DD_DDNS_CONFIG;

typedef struct _dd_ddns_server_info 
{
	unsigned char  DDNSID; /////对应的服务器ID   ID大于0对应的服务器名称才有效
	unsigned char  supportproperty;//支持的除用户名密码外的其它属性的MASK,NCFG_ENUM_DDNS_SUPPORT_PROPERTY
	unsigned char  noused[2];
	char           DDNSServerName[64];  ////DDNS服务器的地址
}DD_DDNS_SERVER_INFO;

typedef struct _dd_smtp_config_
{
	unsigned long iSize;				//本结构体长度

	unsigned short port;				//邮件服务端口
	unsigned short enableSSL;			//是否启用SSL检查

	char server [DD_MAX_URL_BUF_LEN];	//发送服务器地址

	char sendAddress [DD_MAX_URL_BUF_LEN];	//发送邮件地址
	char password [DD_MAX_PASSWORD_BUF_LEN];//帐号密码

	unsigned long enableRecvAddrNum;		//可用的接收地址数目（只读）
	char receiveAddress [DD_MAX_EMAIL_RECEIVE_ADDR_NUM][DD_MAX_URL_BUF_LEN];//接收地址列表
}DD_SMTP_CONFIG;

typedef struct _dd_auto_report_
{
	unsigned long   bUse;			//是否启用自动上报注册功能
	char			host[256];		//注册的平台服务器地址
	unsigned long	dwPort;			//注册的平台服务器端口
	unsigned long	ID;				//分配的注册ID
}DD_AUTO_REPORT;
typedef struct _dd_account_config_
{
	unsigned long iSize;			//本结构体长度

	unsigned long enable;			//是否启用该帐号
	unsigned long bindMAC;			//是否绑定物理地址
	unsigned long group;			//所属群组，取值参考DD_USER_GROUP

	char MAC [8];					//被绑定的物理地址
	char name [DD_MAX_USER_NAME_BUF_LEN];	//用户名称
	char password [DD_MAX_PASSWORD_BUF_LEN];//帐号密码

	//以下是权限的相关内容
	unsigned char logSearch;		//日志搜索权限
	unsigned char systemSetup;		//系统配置
	unsigned char fileManagement;	//文件管理
	unsigned char diskManagement;	//磁盘管理
	unsigned char remoteLogin;		//远程登入
	unsigned char twoWayAudio;		//语音对讲
	unsigned char systemMaintain;	//系统维护
	unsigned char OnlineUserManagement;	//在线用户管理
	unsigned char shutdown;			//关机或者重启
	unsigned char alarmOutCtrl;		//报警输出控制
	unsigned char netAlarm;			//网络报警
	unsigned char netSerialCtrl;	//网络串口控制
	
	unsigned char authLive;
	unsigned char authRecord;
	unsigned char authPlayback;
	unsigned char authBackup;
	unsigned char authPTZ;
	unsigned char netAuthView;
	unsigned char netauthRecord;
	unsigned char netauthPlayback;
	unsigned char netauthBackup;
	unsigned char netauthPTZ;
	unsigned char recv[2];

	unsigned char authLiveCH [DD_MAX_CAMERA_NUM_BYTE_LEN];          //现场预览通道
	unsigned char authRecordCH [DD_MAX_CAMERA_NUM_BYTE_LEN];		//本地手动录像
	unsigned char authPlaybackCH [DD_MAX_CAMERA_NUM_BYTE_LEN];		//本地检索及回放
	unsigned char authBackupCH [DD_MAX_CAMERA_NUM_BYTE_LEN];		//本地备份
	unsigned char authPTZCH [DD_MAX_CAMERA_NUM_BYTE_LEN];			//本地云台控制

	unsigned char netAuthViewCH [DD_MAX_CAMERA_NUM_BYTE_LEN];		//远程现场预览
	unsigned char netAuthRecordCH [DD_MAX_CAMERA_NUM_BYTE_LEN];		//远程手动录像
	unsigned char netAuthPlaybackCH [DD_MAX_CAMERA_NUM_BYTE_LEN];	//远程回放
	unsigned char netAuthBackupCH [DD_MAX_CAMERA_NUM_BYTE_LEN];		//远程备份
	unsigned char netAuthPTZCH [DD_MAX_CAMERA_NUM_BYTE_LEN];		//远程云台控制
}DD_ACCOUNT_CONFIG;

typedef struct _dd_trigger_alarm_out_
{
	unsigned char toBuzzer;					//触发蜂鸣器报警
	unsigned char ShowFullScreen;			//触发大画面报警（通道号，0xff为不触发）
	unsigned char sendEmail;				//发送邮件
	unsigned char toUploadToAlarmCentre;	//上传到报警中心

	unsigned long toAlarmOut;				//报警输出（比特位对应输出设备）
}DD_TRIGGER_ALARM_OUT;

typedef struct _dd_trigger_record_
{
	unsigned char snapCH [DD_MAX_CAMERA_NUM_BYTE_LEN];		//触发抓图
	unsigned char recordCH [DD_MAX_CAMERA_NUM_BYTE_LEN];	//触发录像
}DD_TRIGGER_RECORD;

typedef struct _dd_trigger_ptz_
{
	unsigned char toPTZType;	//联动类型（预置点、巡航线、轨迹）DD_PTZ_TYPE

	unsigned char toIndex;		//联动的（预置点、巡航线、轨迹）编号
	unsigned char backIndex;	//联动的返回（预置点、巡航线、轨迹）编号
	unsigned char recv;			//保留字节
}DD_TRIGGER_PTZ;

typedef struct _dd_sensor_config_
{
	unsigned long iSize;		//本结构体长度

	unsigned char	enable;		//是否启用侦测
	unsigned char	bNO;		//设备类型：常开或者常闭
	unsigned short	holdTime;	//延迟时间

	char name [DD_MAX_NAME_BUF_LEN];	//设备名称
}DD_SENSOR_CONFIG;

typedef struct _dd_motion_area_
{
	unsigned long sensitivity;		//灵敏度（0～7），数字越大灵敏度越高

	unsigned short widthNum;		//区域的横向栅格数目
	unsigned short heightNum;		//区域的纵向栅格数目

	//区域的栅格掩码数据，兼容1920x1080，每块8X8大小。
	unsigned char area [DD_MAX_MOTION_AREA_HIGHT_NUM][DD_MAX_MOTION_AREA_WIDTH_NUM];
}DD_MOTION_AREA;

typedef struct _dd_motion_config_
{
	unsigned long iSize;		//本结构体长度

	unsigned char	enable;		//是否启用移动侦测
	unsigned char	recv;		//保留字节

	unsigned short	holdTime;	//延迟时间

	DD_MOTION_AREA	area;		//区域设置
}DD_MOTION_CONFIG;

typedef struct _dd_buzzer_config_
{
	unsigned char enable;		//蜂鸣器启用开关
	unsigned char recv;			//保留字节

	unsigned short holdTime;	//延迟时间
}DD_BUZZER_CONFIG;

typedef struct _dd_relay_config_
{
	unsigned char enable;		//报警输出设备启用开关
	unsigned char recv;			//保留字节

	unsigned short holdTime;	//延迟时间

	char name [DD_MAX_NAME_BUF_LEN];	//设备名称
}DD_RELAY_CONFIG;

typedef struct _dd_serial_config_
{
	unsigned long baudRate;			//波特率
	unsigned long dataBit;			//数据位
	unsigned long stopBit;			//停止位
	unsigned long parity;			//奇偶校验位
	unsigned long dataFlowControl;	//数据流控制
}DD_SERIAL_CONFIG;

typedef struct _dd_ptz_config_
{
	unsigned long iSize;		//本结构体长度

	unsigned char enable;		//是否启用云台功能
	unsigned char address;		//地址
	unsigned char recv1;		//保留字节
	unsigned char recv2;		//保留字节

	unsigned long protocol;		//协议

	DD_SERIAL_CONFIG serial;	//串口
}DD_PTZ_CONFIG;

typedef struct _dd_ptz_protocol_info 
{
	unsigned long  protocolID;		//对应的协议类型ID
	unsigned long  protocolProperty;//支持的除ID、波特率之外的其它属性的MASK,比如是否支持轨迹等特殊属性
	char           ProtocolName[64];//协议名称
}DD_PTZ_PROTOCOL_INFO;

typedef struct _dd_ptz_preset_config_
{
	unsigned long iSize;		//本结构体长度

	//预置点掩码
	unsigned char enablePreset [DD_MAX_PRESET_NUM];
}DD_PTZ_PRESET_CONFIG;

//////////////////////////////////////////////////////////////////////////
typedef struct _dd_config_item_head_
{
	unsigned short	itemID;		//ID
	unsigned short	num;		//元素数目，比如多少个通道，每个通道对应一个元素
	unsigned short	subLen;		//每个元素的长度
	unsigned short recv;
	unsigned long	len;		//数据总长度
}DD_CONFIG_ITEM_HEAD;


typedef struct _dd_config_block_head_
{
	unsigned long	biSize;		//本结构体长度
	unsigned long	ItemNum;	//元素数目
	unsigned long	netcfgver;	//当前定义的版本号，设备端固定传输DD_CONFIG_VERSION，客户端根据需要动态判断
}DD_CONFIG_BLOCK_HEAD;

typedef struct _dd_config_item_head_ex_
{
	DD_CONFIG_ITEM_HEAD		item_head;
	unsigned long			start_pos;		//文件中偏移
}DD_CONFIG_ITEM_HEAD_EX;		

typedef struct _dd_config_block_info_
{
	DD_CONFIG_ITEM_HEAD_EX	itemHead;
	unsigned long			off;			//缓存中偏移
}DD_CONFIG_BLOCK_INFO;

//////////////////////////////////////////////////////////////////////////
const unsigned long		DD_CONFIG_VERSION	= 20101123;

typedef enum dd_config_item_id
{
	DD_CONFIG_ITEM_SYSTEM_BASE=0x0100,
	DD_CONFIG_ITEM_DEVICE_INFO,				//DD_DEVICE_INFO
	DD_CONFIG_ITEM_SYSTEM_BASIC,			//DD_BASIC_CONFIG
	DD_CONFIG_ITEM_DATE_TIME,				//DD_DATE_TIME_CONFIG
	DD_CONFIG_ITEM_DAYLIGHT_INFO,			//DD_DAYLIGHT_INFO
	DD_CONFIG_ITEM_SYSTEM_END,

	DD_CONFIG_ITEM_LIVE_BASE=0x0200,
	DD_CONFIG_ITEM_LIVE_MAIN_CAMERA,		//DD_LIVE_VIDEO_GROUP * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_LIVE_SPOT_CAMERA,		//DD_LIVE_VIDEO_GROUP * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_LIVE_AUDIO,				//DD_LIVE_AUDIO_GROUP * AUDIO_INPUT_NUM
	DD_CONFIG_ITEM_LIVE_DISPLAY,			//DD_LIVE_DISPLAY
	DD_CONFIG_ITEM_LIVE_END,

	DD_CONFIG_ITEM_CHNN_BASE=0x0300,
	DD_CONFIG_ITEM_CHNN_CONFIG,				//DD_CHANNEL_CONFIG * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_VIDEO_COLOR,				//DD_VIDEO_COLOR_CONFIG * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_VIDEO_OSD,				//DD_VIDEO_OSD_CONFIG * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_CHNN_END,

	DD_CONFIG_ITEM_ENCODE_BASE=0x0400,
	DD_CONFIG_ITEM_ENCODE_MASK_MAJOR,		//DD_ENCODE_CONFIG
	DD_CONFIG_ITEM_ENCODE_MASK_MINOR,		//DD_ENCODE_CONFIG
	DD_CONFIG_ITEM_ENCODE_SCHEDULE,			//DD_ENCODE_CONFIG * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_ENCODE_ALARM,			//DD_ENCODE_CONFIG * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_ENCODE_NETWORK,			//DD_ENCODE_CONFIG * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_ENCODE_END,

	DD_CONFIG_ITEM_RECORD_BASE=0x0500,
	DD_CONFIG_ITEM_RECORD_MASK,				//DD_RECORD_CONFIG_MASK
	DD_CONFIG_ITEM_RECORD_SETUP,			//DD_RECORD_CONFIG * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_RECORD_SCHEDULE_SCHEDULE,//DD_WEEK_SCHEDULE * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_RECORD_SCHEDULE_MOTION,	//DD_WEEK_SCHEDULE * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_RECORD_SCHEDULE_SENSOR,	//DD_WEEK_SCHEDULE * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_RECORD_END,

	DD_CONFIG_ITEM_NETWORK_BASE=0x0600,
	DD_CONFIG_ITEM_NETWORK_IP,				//DD_NETWORK_IP_CONFIG
	DD_CONFIG_ITEM_NETWORK_ADVANCE,			//DD_NETWORK_ADVANCE_CONFIG
	DD_CONFIG_ITEM_NETWORK_DDNS,			//DD_DDNS_CONFIG
	DD_CONFIG_ITEM_DDNS_SERVER_INFO,		//DD_DDNS_SERVER_INFO
	DD_CONFIG_ITEM_NETWORK_SMTP,			//DD_SMTP_CONFIG
//2012-3-15增加DVR主动注册的功能
	DD_CONFIG_ITEM_AUTO_REPORT,				//DD_AUTO_REPORT
	DD_CONFIG_ITEM_NETWORK_END,

	DD_CONFIG_ITEM_ACCOUNT_BASE=0x0700,
	DD_CONFIG_ITEM_ACCOUNT,					//DD_ACCOUNT_CONFIG * MAX_USER_NUM
	DD_CONFIG_ITEM_ACCOUNT_END,

	DD_CONFIG_ITEM_SENSOR_BASE=0x0800,
	DD_CONFIG_ITEM_SENSOR_SETUP,			//DD_SENSOR_CONFIG * SENSOR_INPUT_NUM
	DD_CONFIG_ITEM_SENSOR_SCHEDULE,			//DD_WEEK_SCHEDULE * SENSOR_INPUT_NUM
	DD_CONFIG_ITEM_SENSOR_ALARM_OUT,		//DD_TRIGGER_ALARM_OUT * SENSOR_INPUT_NUM
	DD_CONFIG_ITEM_SENSOR_TO_RECORD,		//DD_TRIGGER_RECORD * SENSOR_INPUT_NUM
	DD_CONFIG_ITEM_SENSOR_TO_PTZ,			//(DD_TRIGGER_PTZ * VIDEO_INPUT_NUM) * SENSOR_INPUT_NUM
	DD_CONFIG_ITEM_SENSOR_END,

	DD_CONFIG_ITEM_MOTION_BASE=0x0900,
	DD_CONFIG_ITEM_MOTION_SETUP,			//DD_MOTION_CONFIG * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_MOTION_SCHEDULE,			//DD_WEEK_SCHEDULE * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_MOTION_ALARM_OUT,		//DD_TRIGGER_ALARM_OUT * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_MOTION_TO_RECORD,		//DD_TRIGGER_RECORD * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_MOTION_TO_PTZ,			//(DD_TRIGGER_PTZ * VIDEO_INPUT_NUM) * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_MOTION_END,

	DD_CONFIG_ITEM_SHELTER_BASE=0x0a00,
	DD_CONFIG_ITEM_SHELTER_SETUP,			//DD_MOTION_CONFIG * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_SHELTER_SCHEDULE,		//DD_WEEK_SCHEDULE * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_SHELTER_ALARM_OUT,		//DD_TRIGGER_ALARM_OUT * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_SHELTER_TO_RECORD,		//DD_TRIGGER_RECORD * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_SHELTER_TO_PTZ,			//(DD_TRIGGER_PTZ * VIDEO_INPUT_NUM) * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_SHELTER_END,

	DD_CONFIG_ITEM_VLOSS_BASE=0x0b00,
	DD_CONFIG_ITEM_VLOSS_SCHEDULE,			//DD_WEEK_SCHEDULE * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_VLOSS_ALARM_OUT,			//DD_TRIGGER_ALARM_OUT * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_VLOSS_TO_RECORD,			//DD_TRIGGER_RECORD * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_VLOSS_TO_PTZ,			//(DD_TRIGGER_PTZ * VIDEO_INPUT_NUM) * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_VLOSS_END,

	DD_CONFIG_ITEM_ALARM_OUT_BASE=0x0c00,
	DD_CONFIG_ITEM_RELAY_SETUP,				//DD_RELAY_CONFIG * RELAY_NUM
	DD_CONFIG_ITEM_RELAY_SCHEDULE,			//DD_WEEK_SCHEDULE * RELAY_NUM
	DD_CONFIG_ITEM_BUZZER_SETUP,			//DD_BUZZER_CONFIG
	DD_CONFIG_ITEM_BUZZER_SCHEDULE,			//DD_WEEK_SCHEDULE
	DD_CONFIG_ITEM_ALARM_OUT_END,

	DD_CONFIG_ITEM_PTZ_BASE=0x0d00,
	DD_CONFIG_ITEM_PTZ_SETUP,				//DD_PTZ_CONFIG * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_PTZ_PRESET,				//DD_PTZ_PRESET_CONFIG * VIDEO_INPUT_NUM
	DD_CONFIG_ITEM_PTZ_PROTOCOL_INFO,       //DD_PTZ_PROTOCOL_INFO
	DD_CONFIG_ITEM_PTZ_END,

	DD_DECODER_CONFIG_ITEM_BASE=0x0e00,
	DD_DECODER_CONFIG_DEVICE_INFO,			//DEC_DEVICE_CONFIG
	DD_DECODER_CONFIG_NETWORK_INFO,			//DEC_NETWORK_CONFIG
	DD_DECODER_CONFIG_NTP_INFO,				//DEC_ADVANCE_NETWORK
	DD_DECODER_CONFIG_DDNS_INFO,			//DEC_DDNS_INFO
	DD_DECODER_CONFIG_SENSOR_SETUP,			//DEC_SENSOR_SETUP* VIDEO_INPUT_NUM
	DD_DECODER_CONFIG_SENSOR_SCHEDULE,		//DEC_WEEK_SCHEDULE * VIDEO_INPUT_NUM
	DD_DECODER_CONFIG_OTHER_ALARMOUT,		//DEC_OTHER_ALARM* VIDEO_INPUT_NUM

	DD_CONFIG_ITEM_END
}DD_CONFIG_ITEM_ID;

///////////////////////////////////////


const unsigned long DEC_MAX_NAME_LEN = 64;
const unsigned long DEC_MAX_VERSION_BUF_LEN = 64;
const unsigned long DEC_MAX_BUF_LEN = (DEC_MAX_NAME_LEN * 2) + 4;

typedef struct _dec_device_config
{
	unsigned long	iSize;		//本结构体长度

	char			deviceName [DEC_MAX_NAME_LEN];			//设备名称（注意考虑双字节字符）
	unsigned long	channelNum;								//解码器通道总数
	unsigned long	productID;								//产品ID号
	unsigned long	productSubID;							//产品子ID号
	//以下为只读项
	//version
	unsigned long	softVersion;							//软件版本号
	char			mcuVersion [DEC_MAX_VERSION_BUF_LEN];			//MCU版本
	char			kernelVersion [DEC_MAX_VERSION_BUF_LEN];	//内核版本
	char			hardwareVersion [DEC_MAX_VERSION_BUF_LEN];	//硬件版本

}DEC_DEVICE_CONFIG;

typedef struct _dec_network_config
{	
	unsigned long	iSize;		//本结构体长度

	unsigned long	IP;				//网络地址
	unsigned long	subnetMask;		//子网掩码
	unsigned long	gateway;		//网关
	
	unsigned short httpPort;		//HTTP端口
	unsigned short decoderPort;			//解码器端口
	char MAC [8];					//被绑定的物理地址
	unsigned long multiCastIP;		//多播地址
	unsigned long bDHCP;

	unsigned long dns1;				//DNS1
	unsigned long dns2;				//DNS2
}DEC_NETWORK_CONFIG;

typedef struct _dec_advance_network
{
	unsigned long	iSize;		//本结构体长度

	unsigned char TimeZone; //时区
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
	unsigned char mday;
	unsigned char month;
	unsigned short year;//2008~2025
	
	bool	enableFlag;		//NTP使能标识
	char	name [132];			//NTP服务器的网址。
	int		NTP_Port;			//NTP服务器的端口
	int		syncInterval;		//同步的时间间隔。以小时为单位
}DEC_ADVANCE_NETWORK;

typedef struct _dec_sensor_setup_
{
	unsigned long iSize;		//本结构体长度

	unsigned char	enable;		//是否启用侦测
	unsigned char	bNO;		//设备类型：常开或者常闭
	unsigned short	holdTime;	//延迟时间

	char name [DEC_MAX_BUF_LEN];	//设备名称
	unsigned long  toBuzzer;			//触发蜂鸣器报警
	unsigned long  toAlarmOut;			//报警输出（比特位对应输出设备）
}DEC_SENSOR_SETUP;

typedef struct _dec_other_alarm_
{
	unsigned long iSize;					//本结构体长度

	unsigned long toBuzzerForIPConflict;	//IP冲突触发蜂鸣器
	unsigned long toAlarmOutForDisconnect;	//IP冲突报警输出（比特位对应输出设备）
	unsigned long toBuzzerForDisconnect;	//网络断开触发蜂鸣器
	unsigned long toAlarmOutForIPConflict;	//网络断开报警输出（比特位对应输出设备）
}DEC_OTHER_ALARM;

//日排程结构，24代表24小时，unsigned long long的每一位代表每一分钟的状态
typedef struct _dec_date_schedule_
{
	unsigned long long hour [24];
}DEC_DATE_SCHEDULE;

//周排程结构，7表示每周7天的排程
typedef struct _dec_week_schedule_
{
	DEC_DATE_SCHEDULE week[7];
}DEC_WEEK_SCHEDULE;

#endif //__DVR_DVS_CONFIG_H__
