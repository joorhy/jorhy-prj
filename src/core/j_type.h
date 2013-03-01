#ifndef __J_TYPE_H_
#define __J_TYPE_H_
#include <sys/types.h>
#include <stdint.h>
#include <string>

#define JO_MAKE_FORCC(ch0, ch1, ch2, ch3) 	((ch0 & 0xFF) | ((ch1 & 0xFF) << 8) | ((ch2 & 0xFF) << 16) | ((ch3 & 0xFF) << 24))

///NVR 云台控制命令
#define 	JO_PTZ_UP				1	//向上旋转
#define 	JO_PTZ_DOWN				2	//向下旋转
#define 	JO_PTZ_LEFT				3	//向左旋转
#define 	JO_PTZ_RIGHT			4	//向右旋转
#define 	JO_PTZ_UP_LEFT			5	//左上旋转
#define 	JO_PTZ_UP_RIGHT		    6	//右上旋转
#define 	JO_PTZ_DOWN_LEFT		7	//左下旋转
#define 	JO_PTZ_DOWN_RIGHT		8	//右下旋转

#define 	JO_PTZ_PRE_SET			9	//设置预置点
#define 	JO_PTZ_PRE_CLR			10	//清除预置点
#define		JO_PTZ_GOTO_PRE	        11	//转至预置点

#define		JO_PTZ_ZOOM_IN			12	//倍率变大
#define		JO_PTZ_ZOOM_OUT		    13	//倍率变小
#define		JO_PTZ_FOCUS_NEAR		14	//焦点调近
#define		JO_PTZ_FOCUS_FAR		15	//焦点调远
#define 	JO_PTZ_IRIS_OPEN		16	//光圈变大
#define		JO_PTZ_IRIS_CLOSE		17	//光圈变小
#define     JO_PTZ_PAN_AUTO         18  //自动扫描

#define     JO_PTZ_AUX_ON           19  //辅助设备打开
#define     JO_PTZ_AUX_OFF          20  //辅助设备关闭

///协议状态
#define J_ProUnReady			0
#define J_ProParamOk			(1 << 0)
#define J_ProConnOk			    (1 << 1)
#define J_ProDataUnReady	    (1 << 2)
#define J_ProPlaying			(1 << 3)
#define J_ProPaused			    (1 << 4)

///JOSP协议相关定义
#define JO_SDK_VERSION      1
#define JO_PACKET_LEN       1500

//拆包类型定义
#define jo_intact_pack      0x00
#define jo_start_pack       0x01
#define jo_mid_pack         0x02
#define jo_end_pack         0x03

//命令定义
#define JO_LOGIN            0x01		//登录
#define JO_LOGIN_RET        0x02        //登录返回
#define JO_LOGOUT           0x03		//退出
#define JO_LOGOUT_RET       0x04		//退出返回
#define JO_GETRES           0x05		//获得资源列表
#define JO_GETRES_RET       0x06		//获得资源列表
#define JO_OPEN_STREAM      0x07		//开始预览
#define JO_OPEN_STREAM_RET  0x08		//预览返回
#define JO_CLOSE_STREM      0x09		//停止预览
#define JO_CLOSE_STREM_RET  0x0A		//停止返回
#define JO_PTZ_CONTROL      0x0B		//云镜控制
#define JO_PTZ_CONTROL_RET  0x0C		//云镜控制返回
#define JO_RCD_SEARCH		0x0D		//历史文件查询
#define JO_RCD_SEARCH_RET	0x0E		//历史文件查询返回
#define JO_OPEN_FILE		0x0F		//打开历史视频
#define JO_OPEN_FILE_RET	0x10		//打开历史视频返回
#define JO_REQ_DATA			0x11		//请求数据
#define JO_REQ_DATA_RET		0x12		//请求数据应答

#define JO_MAX_ASIOSIZE 1024

///NVR IO类型
enum J_IOType
{
	J_IoRead = 1,		//读标识
	J_IoWrite			//写标识
};

///NVR 告警类型
enum J_AlarmType
{
	J_VideoLost = 1,	//视频丢失
	J_VideoMotdet,		//移动侦测
	J_VideoHide			//视频遮挡
};

///NVR命令集合
enum J_CommandType
{
	J_START_REAL = 1,		//启动实时视频
	J_STOP_REAL,				//关闭实时视频
	J_START_VOD,				//播放录像文件
	J_STOP_VOD,				//停止播放
	J_PAUSE_VOD,				//暂停
	J_SETRTIME_VOD,			//设置播放时间
	J_SETPOS_VOD,			//设置播放位置
	J_SETSCALE_VOD,			//设置播放速度
	J_START_VOICE,			//启动对讲
	J_STOP_VOICE				//关闭对讲
};

///帧类型
enum J_MediaType
{
	J_MediaUnknow = 1,			//未知类型
	J_MediaHead,				//视频头信息
	J_VideoIFrame,				//关键帧
	J_VideoBFrame,				//视频B帧
	J_VideoPFrame,				//视频P帧
	J_AudioFrame,				//音频帧
	J_MediaBroken
};

///帧头结构
struct J_StreamHeader
{
	uint32_t dataLen;			//数据长度
	uint32_t frameType;			//帧类型
	uint64_t timeStamp;			//时间戳
	uint32_t frameNum;
	//char data[1];				//帧数据
};

///NVR命令头结构
struct J_CmdHeader
{
	uint32_t cmd;
	uint32_t type;
	union
	{
		char resid[16];
		char fileid[16];
	};
};

///NVR命令回复结构
struct J_RetHeader
{
	uint32_t type;					//设备类型  1-hik
	uint32_t retCode;				//0-sucess; <0-error
};

///NVR存储文件的帧头
struct J_FrameHeader
{
	uint32_t frameType;		//见MediaType
	uint32_t length;			//帧数据长度
	uint32_t offset;			//相对于文件的偏移
	uint64_t timeStamp;		//相对时间戳
};

///NVR存储文件的文件格式
struct J_FileHeader
{
	char type[4];				//数据类型, body-音视频数据, head-头数据，存放一系列NVRFrameHeader
	uint32_t length;			//数据长度,不包含NVRFileHeader
};

///文件信息
struct J_FileInfo
{
	time_t tStartTime;					/* 文件的开始时间 */
	time_t tStoptime;					/* 文件的结束时间 */
};

///设备状态枚举
enum J_DevStatus
{
	J_DevReady = 1,
	J_DevBroken
};

///媒体上下文信息
struct J_MediaContext
{
	uint32_t forcc;			//媒体类型
	uint32_t len;				//接下来的数据长度
	uint16_t num;				//流数量
	char data[1];				//扩展数据长度
};

///媒体上下文数据
struct J_ContextData
{
	uint32_t forcc;			//媒体类型
	uint32_t len;				//接下来的数据长度
	struct
	{
		int32_t len;
		char data[256];
	} cxt;
};

///前端设备信息结构
struct J_DeviceInfo
{
	int32_t devId;					//设备ID
	char devIp[16];			//设备IP地址
	uint16_t devPort;				//设备端口
	char devType[16];			//设备类型
	char userName[16];		//用户名
	char passWd[32];			//密码
	int32_t devStatus;				//设备状态
};

///通道信息结构
struct J_ChannelInfo
{
	char  devId;					//所属设备ID
	int32_t channelNum;			//通道编号
};

///录像信息结构
struct J_RecordInfo
{
	char vodPath[256];				//录像路径
	uint32_t fileSize;				//文件大小
	uint32_t timeInterval;			//录像文件间隔  单位(毫秒)
	uint32_t preRecordTime;			//预录时间 单位(秒)
};

///解析数据类型
enum
{
	J_VideoNormal = 0,
	J_VideoYuyv,
	J_VideoMjpeg
};

///通道ID类型
class J_ChannelKey
{
public:
	int32_t stream_type;
	std::string resid;

	bool operator<(const J_ChannelKey &other) const
	{
		bool b_ret = true;
		if (resid != other.resid)
			b_ret = resid < other.resid;
		else
			b_ret = stream_type < other.stream_type;

		return b_ret;
	}
};

///JOSP 控制协议头
struct J_CtrlHead
{
    char start_code[4];		//魔术字段 JOSP
    uint8_t version:4;		//版本号
    uint8_t type:2;			//协议类型 0-tcp, 1-udp
    uint8_t flag:2;			//分包标志 0-未分包, 1-开始, 2-中间, 3-结束包
    uint8_t cmd;			//命令
    uint16_t sq_num;		//包序号
    uint8_t ret;			//返回码头 0-无错误
    uint8_t reserved;
    uint16_t ex_length;		//扩展数据长度
    char user_id[32];		//用户ID
    uint8_t crc[4];			//校验码(循环冗余校验)
};

///JOSP 控制协议数据包
struct J_CtrlPacket
{
    J_CtrlHead head;
    char data[1];
};

///JOSP 用户信息
struct J_UserInfo
{
    char ip_addr[16];
    int16_t port;
    bool is_active;
    char user_name[16];
    char pass_word[16];
    union
    {
        char usr_id[32];
        char res_id[32];
    } id;
};

///JOSP 网络信息
struct J_NetWorkInfo
{
    char ip_addr[16];
    int16_t port;
};

///JOSP 登录数据
struct J_LoginData
{
    char user_name[16];
    char pass_word[16];
};

///JOSP 云镜控制数据
struct J_PTZCtlData
{
    char res_id[32];
    int16_t command;
    int16_t param;
};

///JOSP 录像查询数据
struct J_RecordData
{
	char res_id[32];
	time_t begin_time;
	time_t end_time;
};

///JOSP 实时视频预览
struct J_RealViewData
{
	char res_id[32];		//资源ID
	int32_t stream_type;		//码流类型 0-主码流,1-子码流
};

///JOSP 实时视频预览返回
struct J_RealViewRetData
{
	char media_code[4];		//媒体类型 JOMS
	//视频信息
	uint8_t i_frame_ival;	//I帧间隔
	uint8_t fps;			//帧率
	uint16_t width;			//视频宽度
	uint16_t height;		//视频高度
	//音频信息
};

///JOSP 数据头格式
struct J_DataHead
{
	char start_code[4];		//魔术字段 JOAV
	uint32_t data_len;		//数据长度(不包括头)
	uint32_t frame_type;	//3-I帧,4-B帧,5-P帧,6-音频帧
	int64_t time_stamp;		//时间戳
	uint32_t frame_seq;		//帧序列号
	int b_last_frame;		//数据结束标准
};

#endif //~__J_TYPE_H_
