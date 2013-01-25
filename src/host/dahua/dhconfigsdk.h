
#ifndef DHCONFIGSDK_H
#define DHCONFIGSDK_H

#ifdef WIN32

#ifdef DHCONFIGSDK_EXPORTS
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


#endif


#ifdef __cplusplus
extern "C" {
#endif


/************************************************************************
 ** 常量定义
 ***********************************************************************/

#define MAX_CHANNEL_COUNT		8
#define MAX_VIDEO_CHANNEL_NUM	256					// 最大通道数256
#define MAX_CHANNELNAME_LEN		32					// 最大通道名称长度
#define MAX_VIDEOSTREAM_NUM		3					// 最大码流个数
#define MAX_VIDEO_COVER_NUM		16					// 最大遮挡区域个数
#define WEEK_DAY_NUM			7					// 一周的天数
#define MAX_REC_TSECT			6					// 录像时间段个数
#define MAX_WATERMARK_LEN		4096				// 数字水印数据最大长度
#define MAX_MOTION_ROW			32					// 动态检测区域的行数
#define MAX_MOTION_COL			32					// 动态检测区域的列数
#define MAX_IMAGESIZE_NUM		256					// 最大支持的分辨率个数
#define MAX_FPS_NUM				1024				// 最大支持的帧率个数
#define MAX_QUALITY_NUM			32					// 最大支持的画质个数
#define MAX_ADDRESS_LEN			256					// 最大的地址长度
#define MAX_USERNAME_LEN		64					// 最大用户名长度
#define MAX_PASSWORD_LEN		64					// 最大密码长度
#define MAX_DIRECTORY_LEN		256					// 文件夹名字字符串长度
#define MAX_NAS_TIME_SECTION	2					// 网络存储时间段个数
#define MAX_NAME_LEN			32					// 通用名字字符串长度
#define MAX_DECPRO_LIST_SIZE	100					// 解码器协议列表个数上限
#define MAX_SCENE_LIST_SIZE		16					// 视频分析设备支持的场景类型列表个数上限
#define MAX_OBJECT_LIST_SIZE	16					// 视频分析设备支持的检测物体类型列表个数上限
#define MAX_RULE_LIST_SIZE		16					// 视频分析设备支持的规则列表个数上限
#define MAX_MODULE_NUM			16					// 视频分析设备最大检测模块个数
#define MAX_RULE_NUM			16					// 视频分析设备最大规则个数
#define MAX_POLYGON_NUM			4					// 视频分析设备区域顶点个数上限
#define MAX_POLYLINE_NUM		2					// 视频分析设备折线顶点个数上限
#define MAX_VEHICLE_SIZE_LIST	4					// 视频分析设备车辆大小个数上限
#define MAX_VEHICLE_TYPE_LIST	4					// 视频分析设备车辆类型个数上限
#define MAX_PLATE_TYPE_LIST		32					// 视频分析设备车牌类型个数上限
	
	

/************************************************************************
 ** 配置命令 对应CLIENT_GetNewDevConfig和CLIENT_SetNewDevConfig接口
 ***********************************************************************/

#define CFG_CMD_ENCODE			"Encode"			// 图像通道属性配置(对应CFG_ENCODE_INFO)
#define CFG_CMD_RECORD			"Record"			// 定时录像配置(对应CFG_RECORD_INFO)
#define CFG_CMD_ALARMINPUT		"Alarm"				// 外部输入报警配置(对应CFG_ALARMIN_INFO)
#define CFG_CMD_NETALARMINPUT	"NetAlarm"			// 网络报警配置(对应CFG_NETALARMIN_INFO)
#define CFG_CMD_MOTIONDETECT	"MotionDetect"		// 动态检测报警配置(对应CFG_MOTION_INFO)
#define CFG_CMD_VIDEOLOST		"LossDetect"		// 视频丢失报警配置(对应CFG_VIDEOLOST_INFO)
#define CFG_CMD_VIDEOBLIND		"BlindDetect"		// 视频遮挡报警配置(对应CFG_SHELTER_INFO)
#define CFG_CMD_STORAGENOEXIST	"StorageNotExist"	// 无存储设备报警配置(对应CFG_STORAGENOEXIST_INFO)
#define CFG_CMD_STORAGEFAILURE	"StorageFailure"	// 存储设备访问出错报警配置(对应CFG_STORAGEFAILURE_INFO)
#define CFG_CMD_STORAGELOWSAPCE	"StorageLowSpace"	// 存储设备空间不足报警配置(对应CFG_STORAGELOWSAPCE_INFO)
#define CFG_CMD_NETABORT		"NetAbort"			// 网络断开报警配置(对应CFG_NETABORT_INFO)	
#define CFG_CMD_IPCONFLICT		"IPConflict"		// IP冲突报警配置(对应CFG_IPCONFLICT_INFO)
#define CFG_CMD_SNAPCAPINFO		"SnapInfo"			// 抓图能力查询(对应CFG_SNAPCAPINFO_INFO)
#define CFG_CMD_NAS				"NAS"				// 网络存储服务器配置(对应CFG_NAS_INFO)
#define CFG_CMD_PTZ				"Ptz"				// 云台配置(对应CFG_PTZ_INFO)
#define CFG_CMD_WATERMARK		"WaterMark"			// 视频水印配置(对应CFG_WATERMARK_INFO)
#define CFG_CMD_ANALYSEGLOBAL	"VideoAnalyseGlobal"// 视频分析全局配置(对应CFG_ANALYSEGLOBAL_INFO)
#define CFG_CMD_ANALYSEMODULE	"VideoAnalyseModule"// 物体的检测模块配置(对应CFG_ANALYSEMODULES_INFO)
#define CFG_CMD_ANALYSERULE		"VideoAnalyseRule"	// 视频分析规则配置(对应CFG_ANALYSERULES_INFO)


/************************************************************************
 ** 能力集命令 
 ***********************************************************************/

#define CFG_CAP_CMD_VIDEOANALYSE "devVideoAnalyse.getCaps"	// 视频分析能力集(对应CFG_CAP_ANALYSE_INFO)


/************************************************************************
 ** 配置信息(每个结构体都有能力信息，以区分不同设备程序版本和不同型号设备)
 ***********************************************************************/

//-----------------------------图像通道属性-------------------------------

// 画质
typedef enum tagCFG_IMAGE_QUALITY
{
	IMAGE_QUALITY_Q10 = 1,							// 图像质量10%
	IMAGE_QUALITY_Q30,								// 图像质量30%
	IMAGE_QUALITY_Q50,								// 图像质量50%
	IMAGE_QUALITY_Q60,								// 图像质量60%
	IMAGE_QUALITY_Q80,								// 图像质量80%
	IMAGE_QUALITY_Q100,								// 图像质量100%
} CFG_IMAGE_QUALITY;

// 视频压缩格式
typedef enum tagCFG_VIDEO_COMPRESSION
{
	VIDEO_FORMAT_MPEG4,								// MPEG4
	VIDEO_FORMAT_MS_MPEG4,							// MS-MPEG4
	VIDEO_FORMAT_MPEG2,								// MPEG2
	VIDEO_FORMAT_MPEG1,								// MPEG1
	VIDEO_FORMAT_H263,								// H.263
	VIDEO_FORMAT_MJPG,								// MJPG
	VIDEO_FORMAT_FCC_MPEG4,							// FCC-MPEG4
	VIDEO_FORMAT_H264,								// H.264
} CFG_VIDEO_COMPRESSION;

// 码流控制模式
typedef enum tagCFG_BITRATE_CONTROL
{
	BITRATE_CBR,									// 固定码流
	BITRATE_VBR,									// 可变码流
} CFG_BITRATE_CONTROL;

// 分辨率枚举
typedef enum tagCFG_CAPTURE_SIZE
{
	IMAGE_SIZE_D1,								// 704*576(PAL)  704*480(NTSC)
	IMAGE_SIZE_HD1,								// 352*576(PAL)  352*480(NTSC)
	IMAGE_SIZE_BCIF,							// 704*288(PAL)  704*240(NTSC)
	IMAGE_SIZE_CIF,								// 352*288(PAL)  352*240(NTSC)
	IMAGE_SIZE_QCIF,							// 176*144(PAL)  176*120(NTSC)
	IMAGE_SIZE_VGA,								// 640*480
	IMAGE_SIZE_QVGA,							// 320*240
	IMAGE_SIZE_SVCD,							// 480*480
	IMAGE_SIZE_QQVGA,							// 160*128
	IMAGE_SIZE_SVGA,							// 800*592
	IMAGE_SIZE_XVGA,							// 1024*768
	IMAGE_SIZE_WXGA,							// 1280*800
	IMAGE_SIZE_SXGA,							// 1280*1024  
	IMAGE_SIZE_WSXGA,							// 1600*1024  
	IMAGE_SIZE_UXGA,							// 1600*1200
	IMAGE_SIZE_WUXGA,							// 1920*1200
	IMAGE_SIZE_LTF,								// 240*192
	IMAGE_SIZE_720,								// 1280*720
	IMAGE_SIZE_1080,							// 1920*1080
	IMAGE_SIZE_1_3M,							// 1280*960
	IMAGE_SIZE_NR  
} CFG_CAPTURE_SIZE;

// 视频格式
typedef struct tagCFG_VIDEO_FORMAT
{
	// 能力
	bool				abCompression;
	bool				abWidth;
	bool				abHeight;
	bool				abBitRateControl;
	bool				abBitRate;
	bool				abFrameRate;
	bool				abIFrameInterval;
	bool				abImageQuality;
	bool				abFrameType;

	// 信息
	CFG_VIDEO_COMPRESSION emCompression;			// 视频压缩格式
	int					nWidth;						// 视频宽度
	int					nHeight;					// 视频高度
	CFG_BITRATE_CONTROL	emBitRateControl;			// 码流控制模式
	int					nBitRate;					// 视频码流(kbps)
	int					nFrameRate;					// 视频帧率
	int					nIFrameInterval;			// I帧间隔(1-100)，比如50表示每49个B帧或P帧，设置一个I帧。
	CFG_IMAGE_QUALITY	emImageQuality;				// 图像质量
	int					nFrameType;					// 打包模式，0－DHAV，1－"PS"
} CFG_VIDEO_FORMAT;

// 视频编码参数
typedef struct tagCFG_VIDEOENC_OPT
{
	// 能力
	bool				abVideoEnable;
	bool				abAudioEnable;
	bool				abSnapEnable;

	// 信息
	BOOL				bVideoEnable;				// 视频使能
	CFG_VIDEO_FORMAT	stuVideoFormat;				// 视频格式
	BOOL				bAudioEnable;				// 音频使能
	BOOL				bSnapEnable;				// 定时抓图使能
} CFG_VIDEOENC_OPT;

// RGBA信息
typedef struct tagCFG_RGBA
{
	int					nRed;
	int					nGreen;
	int					nBlue;
	int					nAlpha;
} CFG_RGBA;

// 区域信息
typedef struct tagCFG_RECT
{
	int					nLeft;
	int					nTop;
    int					nRight;
    int					nBottom;				
} CFG_RECT;

// 区域顶点信息
typedef struct tagCFG_POLYGON
{
	int					nX; //0~8191
	int					nY;		
} CFG_POLYGON;

// 折线的端点信息
typedef struct tagCFG_POLYLINE
{
	int					nX; //0~8191
	int					nY;		
} CFG_POLYLINE;

// Size
typedef struct tagCFG_SIZE
{
	union
	{
		int				nWidth;			// 宽
		int				nArea;			// 面积
	};
	int					nHeight;		// 高
	
} CFG_SIZE;

// 遮挡信息
typedef struct tagCFG_COVER_INFO
{
	// 能力
	bool				abBlockType;
	bool				abEncodeBlend;
	bool				abPreviewBlend;

	// 信息
	CFG_RECT			stuRect;					// 覆盖的区域坐标
	CFG_RGBA			stuColor;					// 覆盖的颜色
	int					nBlockType;					// 覆盖方式；0－黑块，1－马赛克
	int					nEncodeBlend;				// 编码级遮挡；1－生效，0－不生效
	int					nPreviewBlend;				// 预览遮挡；1－生效，0－不生效
} CFG_COVER_INFO;

// 多区域遮挡配置
typedef struct tagCFG_VIDEO_COVER
{
	int                 nTotalBlocks;						// 支持的遮挡块数
	int					nCurBlocks;							// 已设置的块数
	CFG_COVER_INFO		stuCoverBlock[MAX_VIDEO_COVER_NUM];	// 覆盖的区域	
} CFG_VIDEO_COVER;

// OSD信息
typedef struct tagCFG_OSD_INFO
{
	// 能力
	bool				abShowEnable;

	// 信息
	CFG_RGBA			stuFrontColor;				// 前景颜色
	CFG_RGBA			stuBackColor;				// 背景颜色
	CFG_RECT			stuRect;					// 矩形区域
	BOOL				bShowEnable;				// 显示使能
} CFG_OSD_INFO;

// 画面颜色属性
typedef struct tagCFG_COLOR_INFO
{
	int					nBrightness;				// 亮度(0-100)
	int					nContrast;					// 对比度(0-100)
	int					nSaturation;				// 饱和度(0-100)
	int					nHue;						// 色度(0-100)
	int					nGain;						// 增益(0-100)
	BOOL				bGainEn;					// 增益使能
} CFG_COLOR_INFO;

// 图像通道属性信息
typedef struct tagCFG_ENCODE_INFO
{
	int                 nChannelID;							// 通道号(0开始)
	char				szChnName[MAX_CHANNELNAME_LEN];		// 通道名称
	CFG_VIDEOENC_OPT	stuMainStream[MAX_VIDEOSTREAM_NUM];	// 主码流，0－普通录像，1-动检录像，2－报警录像
	CFG_VIDEOENC_OPT	stuExtraStream[MAX_VIDEOSTREAM_NUM];// 辅码流，0－辅码流1，1－辅码流2，2－辅码流3
	CFG_VIDEOENC_OPT	stuSnapFormat[MAX_VIDEOSTREAM_NUM];	// 抓图，0－普通抓图，1－动检抓图，2－报警抓图
	DWORD				dwCoverAbilityMask;					// 区域遮盖能力掩码，按位分别是本地预览、录像及网络监视
	DWORD				dwCoverEnableMask;					// 区域遮盖使能掩码，按位分别是本地预览、录像及网络监视
	CFG_VIDEO_COVER		stuVideoCover;						// 区域覆盖
	CFG_OSD_INFO		stuChnTitle;						// 通道标题
	CFG_OSD_INFO		stuTimeTitle;						// 时间标题
	CFG_COLOR_INFO		stuVideoColor;						// 画面颜色
} CFG_ENCODE_INFO;

// 水印配置
typedef struct tagCFG_WATERMARK_INFO 
{
	int                 nChannelID;					// 通道号(0开始)
	BOOL				bEnable;					// 使能开关
	int					nStreamType;				// 码流类型(1～n)，0－所有码流
	int					nDataType;					// 数据类型，1－文字，2－图片
	char				pData[MAX_WATERMARK_LEN];	// 字符串水印数据
} CFG_WATERMARK_INFO;

//-------------------------------录象配置---------------------------------

// 时间段信息
typedef struct tagCFG_TIME_SECTION 
{
	DWORD				dwRecordMask;						// 录像掩码，按位分别为动态检测录像、报警录像、定时录像、Bit3~Bit15保留、Bit16动态检测抓图、Bit17报警抓图、Bit18定时抓图
	int					nBeginHour;
	int					nBeginMin;
	int					nBeginSec;
	int					nEndHour;
	int					nEndMin;
	int					nEndSec;	
} CFG_TIME_SECTION;

// 定时录像配置信息
typedef struct tagCFG_RECORD_INFO
{
	int                 nChannelID;					// 通道号(0开始)
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT]; // 时间表
	int					nPreRecTime;				// 预录时间，为零时表示关闭(0~300)
	BOOL				bRedundancyEn;				// 录像冗余开关
	int					nStreamType;				// 0－主码流，1－辅码流1，2－辅码流2，3－辅码流3
} CFG_RECORD_INFO;

//-------------------------------报警配置---------------------------------

// 云台联动类型
typedef enum tagCFG_LINK_TYPE
{
	LINK_TYPE_NONE,						    		// 无联动
	LINK_TYPE_PRESET,								// 联动预置点
	LINK_TYPE_TOUR,									// 联动巡航
	LINK_TYPE_PATTERN,								// 联动轨迹
} CFG_LINK_TYPE;

// 联动云台信息
typedef struct tagCFG_PTZ_LINK
{
	CFG_LINK_TYPE		emType;						// 联动类型
	int					nValue;						// 联动取值分别对应预置点号，巡航号等等
} CFG_PTZ_LINK;

// 报警联动信息
typedef struct tagCFG_ALARM_MSG_HANDLE
{
	//能力
	bool				abRecordMask;
	bool				abRecordEnable;
	bool				abRecordLatch;
	bool				abAlarmOutMask;
	bool				abAlarmOutEn;
	bool				abAlarmOutLatch;	
	bool				abExAlarmOutMask;
	bool				abExAlarmOutEn;
	bool				abPtzLinkEn;
	bool				abTourMask;
	bool				abTourEnable;
	bool				abSnapshot;
	bool				abSnapshotEn;
	bool				abSnapshotPeriod;
	bool				abSnapshotTimes;
	bool				abTipEnable;
	bool				abMailEnable;
	bool				abMessageEnable;
	bool				abBeepEnable;
	bool				abVoiceEnable;
	bool				abMatrixMask;
	bool				abMatrixEnable;
	bool				abEventLatch;
	bool				abLogEnable;
	bool				abDelay;
	bool				abVideoMessageEn;
	bool				abMMSEnable;
	bool				abMessageToNetEn;
	bool				abTourSplit;
	bool				abSnapshotTitleEn;

	//信息
	int					nChannelCount;								// 设备的视频通道数
	int					nAlarmOutCount;								// 设备的报警输出个数
	DWORD				dwRecordMask[MAX_CHANNEL_COUNT];				// 录像通道掩码(按位)
	BOOL				bRecordEnable;								// 录像使能
	int					nRecordLatch;								// 录像延时时间(秒)
	DWORD				dwAlarmOutMask[MAX_CHANNEL_COUNT];			// 报警输出通道掩码
	BOOL				bAlarmOutEn;								// 报警输出使能
	int					nAlarmOutLatch;								// 报警输出延时时间(秒)
	DWORD				dwExAlarmOutMask[MAX_CHANNEL_COUNT];			// 扩展报警输出通道掩码
	BOOL				bExAlarmOutEn;								// 扩展报警输出使能
	CFG_PTZ_LINK		stuPtzLink[MAX_VIDEO_CHANNEL_NUM];			// 云台联动项
	BOOL				bPtzLinkEn;									// 云台联动使能
	DWORD				dwTourMask[MAX_CHANNEL_COUNT];				// 轮询通道掩码
	BOOL				bTourEnable;								// 轮询使能
	DWORD				dwSnapshot[MAX_CHANNEL_COUNT];				// 快照通道号掩码
	BOOL				bSnapshotEn;								// 快照使能
	int					nSnapshotPeriod;							// 连拍周期(秒)
	int					nSnapshotTimes;								// 连拍次数
	BOOL				bTipEnable;									// 本地消息框提示
	BOOL				bMailEnable;								// 发送邮件，如果有图片，作为附件
	BOOL				bMessageEnable;								// 上传到报警服务器
	BOOL				bBeepEnable;								// 蜂鸣
	BOOL				bVoiceEnable;								// 语音提示
	DWORD				dwMatrixMask[MAX_CHANNEL_COUNT];				// 联动视频矩阵通道掩码
	BOOL				bMatrixEnable;								// 联动视频矩阵
	int					nEventLatch;								// 联动开始延时时间(秒)，0－15
	BOOL				bLogEnable;									// 是否记录日志
	int					nDelay;										// 设置时先延时再生效，单位为秒
	BOOL				bVideoMessageEn;							// 叠加提示字幕到视频。叠加的字幕包括事件类型，通道号，秒计时。
	BOOL				bMMSEnable;									// 发送彩信使能
	BOOL				bMessageToNetEn;							// 消息上传给网络使能
	int					nTourSplit;									// 轮训时的分割模式 0: 1画面; 1: 8画面
	BOOL				bSnapshotTitleEn;							// 是否叠加图片标题
} CFG_ALARM_MSG_HANDLE;

// 外部报警配置
typedef struct tagCFG_ALARMIN_INFO
{
	int					nChannelID;									// 报警通道号(0开始)
	BOOL				bEnable;									// 使能开关
	char				szChnName[MAX_CHANNELNAME_LEN];				// 报警通道名称
	int					nAlarmType;									// 报警器类型，0：常闭，1：常开
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
} CFG_ALARMIN_INFO;

// 网络输入报警配置
typedef struct tagCFG_NETALARMIN_INFO 
{
	int					nChannelID;									// 报警通道号(0开始)
	BOOL				bEnable;									// 使能开关
	char				szChnName[MAX_CHANNELNAME_LEN];				// 报警通道名称
	int					nAlarmType;									// 报警器类型，0：常闭，1：常开
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
} CFG_NETALARMIN_INFO;

// 动态检测报警配置
typedef struct tagCFG_MOTION_INFO 
{
	int					nChannelID;									// 报警通道号(0开始)
	BOOL				bEnable;									// 使能开关
	int					nSenseLevel;								// 灵敏度1～6
	int					nMotionRow;									// 动态检测区域的行数
	int					nMotionCol;									// 动态检测区域的列数
	BYTE				byRegion[MAX_MOTION_ROW][MAX_MOTION_COL];	// 检测区域，最多32*32块区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
} CFG_MOTION_INFO;

// 视频丢失报警配置
typedef struct tagCFG_VIDEOLOST_INFO 
{
	int					nChannelID;									// 报警通道号(0开始)
	BOOL				bEnable;									// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
} CFG_VIDEOLOST_INFO;

// 视频遮挡报警配置
typedef struct tagCFG_SHELTER_INFO 
{
	int					nChannelID;									// 报警通道号(0开始)
	BOOL				bEnable;									// 使能开关
	int					nSenseLevel;								// 灵敏度
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
} CFG_SHELTER_INFO;

// 无存储设备报警配置
typedef struct tagCFG_STORAGENOEXIST_INFO 
{
	BOOL				bEnable;						// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_STORAGENOEXIST_INFO;

// 存储设备访问出错报警配置
typedef struct tagCFG_STORAGEFAILURE_INFO 
{
	BOOL				bEnable;						// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_STORAGEFAILURE_INFO;

// 存储设备空间不足报警配置
typedef struct tagCFG_STORAGELOWSAPCE_INFO 
{
	BOOL				bEnable;						// 使能开关
	int					nLowerLimit;					// 硬盘剩余容量下限，百分数(0~99)
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_STORAGELOWSAPCE_INFO;

// 网络断开报警配置
typedef struct tagCFG_NETABORT_INFO 
{
	BOOL				bEnable;						// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_NETABORT_INFO;

// IP冲突报警配置
typedef struct tagCFG_IPCONFLICT_INFO 
{
	BOOL				bEnable;						// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_IPCONFLICT_INFO;

//-------------------------------抓图配置能力---------------------------------
// 抓图配置能力
typedef struct tagCFG_SNAPCAPINFO_INFO  
{
	int					nChannelID;						// 抓图通道号(0开始)
	DWORD				dwIMageSizeNum;					// 支持的分别率信息
	CFG_CAPTURE_SIZE	emIMageSizeList[MAX_IMAGESIZE_NUM];
	DWORD				dwFramesPerSecNum;				// 支持的帧率信息
	int					nFramesPerSecList[MAX_FPS_NUM];
	DWORD				dwQualityMun;					// 支持的画质信息
	CFG_IMAGE_QUALITY	emQualityList[MAX_QUALITY_NUM];

	DWORD               dwMode;							// 模式,按位：第一位：定时；第二位：手动。
	DWORD               dwFormat;						// 图片格式模式,按位：第一位：bmp；第二位：jpg。
} CFG_SNAPCAPINFO_INFO;


//-------------------------------网络存储服务器配置---------------------------------
// 网络存储服务器配置
typedef struct tagCFG_CHANNEL_TIME_SECTION 
{
	CFG_TIME_SECTION stuTimeSection[WEEK_DAY_NUM][MAX_NAS_TIME_SECTION];//存储时间段
} CFG_CHANNEL_TIME_SECTION;

typedef struct tagCFG_NAS_INFO
{
	BOOL						bEnable;									// 使能开关
	int							nVersion;									// 网络存储服务器版本0=老的FTP，1=NAS存储
	int							nProtocol;									// 协议类型0=FTP 1=SMB
	char						szAddress[MAX_ADDRESS_LEN];					// IP地址或网络名
	int							nPort;										// 端口号
	char						szUserName[MAX_USERNAME_LEN];				// 帐户名
	char						szPassword[MAX_PASSWORD_LEN];				// 密码
	char						szDirectory[MAX_DIRECTORY_LEN];				// 共享的目录名
	int							nFileLen;									// 文件长度
	int							nInterval;									// 相邻文件时间间隔
	CFG_CHANNEL_TIME_SECTION	stuChnTime[MAX_VIDEO_CHANNEL_NUM];			// 存储时间段
} CFG_NAS_INFO;

//------------------------------云台配置--------------------------------------------
// 协议名
typedef struct tagCFG_PRONAME
{
	char				name[MAX_NAME_LEN];			// 协议名
} CFG_PRONAME;

// 串口基本属性
typedef struct tagCFG_COMM_PROP
{
	BYTE				byDataBit;					// 数据位；0：5，1：6，2：7，3：8
	BYTE				byStopBit;					// 停止位；0：1位，1：1.5位，2：2位
	BYTE				byParity;					// 校验位；0：无校验，1：奇校验；2：偶校验
	BYTE				byBaudRate;					// 波特率；0：300，1：600，2：1200，3：2400，4：4800，													
	                                                // 5：9600，6：19200，7：38400，8：57600，9：115200
} CFG_COMM_PROP;

// 云台配置
typedef struct tagCFG_PTZ_INFO
{
	// 能力
	bool				abMartixID;
	bool				abCamID;
	bool				abPTZType;

	// 信息
	int					nChannelID;								// 通道号(0开始)	
	CFG_PRONAME         stuDecProName[MAX_DECPRO_LIST_SIZE];	// 协议名列表(只读)
	int					nProName;								// 协议类型，对应"协议名列表"下标
	int					nDecoderAddress;						// 解码器地址；0 - 255
	CFG_COMM_PROP		struComm;
	int					nMartixID;								// 矩阵号
	int					nPTZType;								// 云台类型0-兼容，本地云台 1-远程网络云台
	int					nCamID;									// 摄像头ID
} CFG_PTZ_INFO;
  

//----------------------------------视频分析设备配置------------------------------------------
// 视频分析能力集
typedef struct tagCFG_CAP_ANALYSE_INFO
{
	int					nSupportedSceneNum;									// 支持的场景个数
	char				szSceneName[MAX_SCENE_LIST_SIZE][MAX_NAME_LEN];		// 支持的场景列表
	int					nMaxMoudles;										// 每通道支持最大分析模块数
	int					nSupportedObjectTypeNum;							// 支持的检测物体类型个数
	char				szObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];	// 支持的检测物体类型列表
	int					nMaxRules;											// 每通道支持最大规则条数
	int					nSupportedRulesNum;									// 支持的规则类型个数
	char				szRulesName[MAX_RULE_LIST_SIZE][MAX_NAME_LEN];		// 支持的规则类型列表
	int					nMaxStaffs;											// 支持的最大标尺个数
	int					nMaxPointOfLine;									// 折线最大顶点数
	int					nMaxPointOfRegion;									// 区域最大顶点数

} CFG_CAP_ANALYSE_INFO;


// 视频分析全局配置
typedef struct tagCFG_ANALYSEGLOBAL_INFO
{
	// 能力
	bool				abCameraHeight;
	bool				abCameraDistance;

	// 信息
	char				szSceneType[MAX_NAME_LEN];				// 应用场景,详见"支持的场景列表"
	double				CameraHeight;							// 摄像头离地高度	单位：米
	double				CameraDistance;							// 摄像头离地面检测区域中心的水平距离	单位：米

} CFG_ANALYSEGLOBAL_INFO;

// 不同区域各种类型物体的检测模块配置
typedef struct tagCFG_MODULE_INFO
{
	// 信息
	char				szObjectType[MAX_NAME_LEN];				// 物体类型,详见"支持的检测物体类型列表"
	bool				bSnapShot;								// 是否对识别物体抓图
	int					nDetectRegionPoint;						// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];		// 检测区域
	int					nTrackRegionPoint;						// 跟踪区域顶点数
	CFG_POLYGON			stuTrackRegion[MAX_POLYGON_NUM];		// 跟踪区域
	int					nFilterType;							// 过滤类型:0:"ByLength",1:"ByArea"
	CFG_SIZE			stuFilterMinSize;						// 物体最小尺寸 "ByLength"模式下表示宽高的尺寸，"ByArea"模式下宽表示面积，高无效。
	CFG_SIZE			stuFilterMaxSize;						// 物体最大尺寸 "ByLength"模式下表示宽高的尺寸，"ByArea"模式下宽表示面积，高无效。

} CFG_MODULE_INFO;

typedef struct tagCFG_ANALYSEMODULES_INFO
{
	int					nMoudlesNum;							// 检测模块数
	CFG_MODULE_INFO     stuModuleInfo[MAX_MODULE_NUM];			// 每个视频输入通道对应的各种类型物体的检测模块配置

} CFG_ANALYSEMODULES_INFO;

// 视频分析规则配置
// 规则类型为"CrossLineDetection"相应的警戒线规则配置
typedef struct tagCFG_CROSSLINE_INFO
{
	// 信息
	int					nDirection;								// 检测方向:0:由左至右;1:由右至左;2:两者都可以
	int					nDetectLinePoint;						// 警戒线顶点数
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];		// 警戒线
		
} CFG_CROSSLINE_INFO;

// 规则类型为"CrossRegionDetection"相应的警戒区规则配置
typedef struct tagCFG_CROSSREGION_INFO
{
	// 信息
	int					nDirection;								// 检测方向:0:Enter;1:Leave;2:Both
	int					nDetectRegionPoint;						// 警戒区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];		// 警戒区
		
} CFG_CROSSREGION_INFO;


// 通用规则配置,规则类型为以下类型时使用
// "PasteDetection" ATM贴条
// "LeftDetection" 物品遗留
// "Preservation" 物品保全
// "StayDetection" 停留
// "WanderDetection" 徘徊
// "MoveDetection" 运动
// "TailDetection" 尾随
// "RioterDetection" 聚众暴乱
// "FightDetection" 打架
// "FireDetection" 火焰
// "SmokeDetection" 烟雾
typedef struct tagCFG_GENERAL_INFO
{
	// 信息
	int					nMinDuration;							// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;						// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];		// 检测区域
		
} CFG_GENERAL_INFO;

// 规则类型为"FlowStat"相应的流量统计规则配置
typedef struct tagCFG_FLOWSTAT_INFO
{
	// 信息
	int					nUpperLimit;							// 流量上限	单位：个/秒，1~65535
	int					nPeriod;								// 上报周期	单位：秒，1~65535
	int					nDetectLinePoint;						// 检测线顶点数
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];		// 检测线
		
} CFG_FLOWSTAT_INFO;

// 规则类型为"NumberStat"相应的数量统计规则配置
typedef struct tagCFG_NUMBERSTAT_INFO
{
	// 信息
	int					nUpperLimit;							// 数量上限 单位：个，1~65535
	int					nPeriod;								// 上报周期	单位：秒，1~65535
	int					nDetectRegionPoint;						// 检测区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];		// 检测区
			
} CFG_NUMBERSTAT_INFO;

// 规则类型为"TrafficControl"相应的交通管制规则配置
typedef struct tagCFG_TRAFFICCONTROL_INFO 
{
	int					nDetectLinePoint;							            	// 检测线顶点数
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];			            	// 检测线
	CFG_TIME_SECTION	stuTimeSchedule[WEEK_DAY_NUM][MAX_REC_TSECT];           	// 限行时间表
	int					nVehicleSizeNum;							            	// 车辆大小类型个数
	char				szVehicleSizeList[MAX_VEHICLE_SIZE_LIST][MAX_NAME_LEN];		// 车辆大小类型列表"Light-duty":小型车;	"Medium":中型车; "Oversize":大型车
	int					nPlateTypeNum;												// 车牌类型个数
	char				szPlateTypesList[MAX_PLATE_TYPE_LIST][MAX_NAME_LEN];		// 车牌类型列表"Unknown" 未知; "Normal" 蓝牌黑牌; "Yellow" 黄牌; "DoubleYellow" 双层黄尾牌
																					// "Police" 警牌; "Armed" 武警牌; "Military" 部队号牌; "DoubleMilitary" 部队双层
																					// "SAR" 港澳特区号牌; "Trainning" 教练车号牌; "Personal" 个性号牌; "Agri" 农用牌
																					// "Embassy" 使馆号牌; "Moto" 摩托车号牌; "Tractor" 拖拉机号牌; "Other" 其他号牌
	int					nPlateNumber;												// 车牌单双号 0:单号; 1:双号; 2:单双号;
	
} CFG_TRAFFICCONTROL_INFO;

// 规则类型为"TrafficAccident"相应的交通事故规则配置
typedef struct tagCFG_TRAACCIDENT_INFO
{
	// 信息
	int					nDetectRegionPoint;							// 检测区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];			// 检测区
	
} CFG_TRAACCIDENT_INFO;


// 规则类型为"TrafficJunction"相应的路口规则配置
typedef struct tagCFG_TRAJUNCTION_INFO
{
	// 信息
	int					nLane;									// 车道编号
	int					nStopLinePoint;							// 停止线顶点数
	CFG_POLYLINE		stuStopLine[MAX_POLYLINE_NUM];			// 停止线
	int					nPreLinePoint;							// 前置线顶点数
	CFG_POLYLINE		stuPreLine[MAX_POLYLINE_NUM];			// 前置线
	int					nPostLinePoint;							// 后置线顶点数
	CFG_POLYLINE		stuPostLine[MAX_POLYLINE_NUM];			// 后置线
	int					nLeftLinePoint;							// 左车道线顶点数
	CFG_POLYLINE		stuLeftLine[MAX_POLYLINE_NUM];			// 左车道线
	int					nRightLinePoint;						// 右车道线顶点数
	CFG_POLYLINE		stuRightLine[MAX_POLYLINE_NUM];			// 右车道线
	int					nStopLightRegionPoint;					// 红灯区域顶点数
	CFG_POLYGON			stuStopLightRegion[MAX_POLYGON_NUM];	// 红灯区域
	int					nDirection;								// 车道方向 0:直行,1: 左转 2:左转直行 3:右转 4:右转直行
	bool				bTurnEn;								// 是否允许掉头
	int					nVehicleSizeNum;						// 车辆大小类型个数
	char				szVehicleSizeList[MAX_VEHICLE_SIZE_LIST][MAX_NAME_LEN];		// 车辆大小类型列表"Light-duty":小型车;	"Medium":中型车; "Oversize":大型车
	int					nVehicleTypeNum;						// 车辆类型个数
	char				szVehicleTypesList[MAX_VEHICLE_TYPE_LIST][MAX_NAME_LEN];	// 车辆类型列表"Bicycle":自行车; "Non-Motor":非机动车; "Bus":公共汽车; "Motor":机动车
		
} CFG_TRAJUNCTION_INFO;

// 规则类型为"TrafficGate"相应的卡口规则配置
typedef struct tagCFG_TRAFFICGATE_INFO
{
	// 信息
	int					nLane;									// 车道编号
	int					nDetectLinePoint1;						// 检测线1顶点数
	CFG_POLYLINE		stuDetectLine1[MAX_POLYLINE_NUM];		// 检测线1
	int					nDetectLinePoint2;						// 检测线2顶点数
	CFG_POLYLINE		stuDetectLine2[MAX_POLYLINE_NUM];		// 检测线2
	int					nLeftLinePoint;							// 左车道线顶点数
	CFG_POLYLINE		stuLeftLine[MAX_POLYLINE_NUM];			// 左车道线
	int					nRightLinePoint;						// 右车道线顶点数
	CFG_POLYLINE		stuRightLine[MAX_POLYLINE_NUM];			// 右车道线
	int					nSpeedWeight;							// 速度权重系数(最终车速=测量车速*权重系数)
	double				MetricDistance;							// 两条检测线实际距离,单位：米
	int					nSpeedUpperLimit;						// 速度上限 0表示不限上限 单位：km/h
	int					nSpeedLowerLimit;						// 速度下限 0表示不限下限 单位：km/h
	
} CFG_TRAFFICGATE_INFO;


typedef struct tagCFG_RULE_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];				// 规则名称,不同规则不能重名
	bool				bRuleEnable;							// 规则使能
	int					nObjectTypeNum;							// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	char				szRuleType[MAX_NAME_LEN];				// 规则类型,详见"支持的规则类型列表"
	CFG_CROSSLINE_INFO  stuCrossLineCfg;						// 警戒线规则配置,规则类型为"CrossLineDetection"时有效
	CFG_CROSSREGION_INFO stuCrossRegionCfg;						// 警戒区规则配置,规则类型为"CrossRegionDetection"时有效
	CFG_GENERAL_INFO	stuGeneralCfg;							// 规则类型为"PasteDetection","LeftDetection","Preservation",
																// "StayDetection","WanderDetection","MoveDetection","TailDetection",
																// "RioterDetection","FightDetection","FireDetection","SmokeDetection"时有效
	CFG_FLOWSTAT_INFO stuFlowStatCfg;							// 流量统计规则配置, 规则类型为"FlowStat"时有效
	CFG_NUMBERSTAT_INFO stuNumberStatCfg;						// 数量统计规则配置,规则类型为"NumberStat"时有效
	CFG_TRAFFICCONTROL_INFO stuTraControlCfg;					// 交通管制规则配置,规则类型为"TrafficControl"时有效
	CFG_TRAACCIDENT_INFO stuAccidentCfg;						// 交通事故规则配置,规则类型为"TrafficAccident"时有效
	CFG_TRAJUNCTION_INFO stuJunctionCfg;						// 路口规则配置,规则类型为"TrafficJunction"时有效
	CFG_TRAFFICGATE_INFO stuTrafficGateCfg;						// 卡口规则配置,规则类型为"TrafficGate"时有效

	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
	
} CFG_RULE_INFO;

typedef struct tagCFG_ANALYSERULES_INFO
{
	int					nRulesNum;								// 视频分析规则数
	CFG_RULE_INFO		stuRuleInfo[MAX_RULE_NUM];				// 每个视频输入通道对应的视频分析规则配置

} CFG_ANALYSERULES_INFO;

/************************************************************************
 ** 接口定义
 ***********************************************************************/

// 解析查询到的配置信息
CLIENT_API BOOL  CALL_METHOD CLIENT_ParseData(char* szCommand, char* szInBuffer, LPVOID lpOutBuffer, DWORD dwOutBufferSize, void* pReserved);

// 组成要设置的配置信息
CLIENT_API BOOL  CALL_METHOD CLIENT_PacketData(char* szCommand, LPVOID lpInBuffer, DWORD dwInBufferSize, char* szOutBuffer, DWORD dwOutBufferSize);


#ifdef __cplusplus
}
#endif

#endif // DHCONFIGSDK_H

