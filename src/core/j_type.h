#ifndef __J_TYPE_H_
#define __J_TYPE_H_
#include "j_common.h"

#define JO_MAKE_FORCC(ch0, ch1, ch2, ch3) 	((ch0 & 0xFF) | ((ch1 & 0xFF) << 8) | ((ch2 & 0xFF) << 16) | ((ch3 & 0xFF) << 24))

#define JO_MAX_ASIOSIZE 1024

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

//命令定义
enum J_JospCommand
{
	jo_login_req = 1,			//登录请求
	jo_login_rep,				//登录返回
	jo_logout_req,				//退出请求
	jo_logout_rep,				//退出返回
	jo_list_res_req,			//获得资源列表请求
	jo_list_res_rep,			//获得资源列表返回
	jo_open_stream_req,			//开始预览
	jo_open_stream_rep,			//预览返回
	jo_close_stream_req,		//停止预览
	jo_close_stream_rep,		//停止返回
	jo_ptz_control_req,			//云镜控制
	jo_ptz_control_rep,			//云镜控制返回
	jo_rcd_search_req,			//历史文件查询
	jo_rcd_search_rep,			//历史文件查询返回
	jo_open_file_req,			//打开历史视频
	jo_open_file_rep,			//打开历史视频返回
	jo_req_data_req,			//请求数据
	jo_req_data_rep,			//请求数据应答
};

///NVR 云台控制命令
enum J_PtzCommand
{
	jo_ptz_up = 1,			//向上旋转
	jo_ptz_down,			//向下旋转
	jo_ptz_left,			//向左旋转
	jo_ptz_right,			//向右旋转
	jo_ptz_up_left,			//左上旋转
	jo_ptz_up_right,		//右上旋转
	jo_ptz_down_left,		//左下旋转
	jo_ptz_down_right,		//右下旋转

	jo_ptz_pre_set,			//设置预置点
	jo_ptz_pre_clr,			//清除预置点
	jo_ptz_goto_pre,	    //转至预置点

	jo_ptz_zoom_in,			//倍率变大
	jo_ptz_room_out,		//倍率变小
	jo_ptz_focus_near,		//焦点调近
	jo_ptz_focus_far,		//焦点调远
	jo_ptz_iris_open,		//光圈变大
	jo_ptz_iris_close,		//光圈变小
	jo_ptz_pan_auto,        //自动扫描

	jo_ptz_aux_on,          //辅助设备打开
	jo_ptz_aux_off         	//辅助设备关闭
};

//拆包类型定义
enum J_PacketType
{
	jo_intact_pack = 0,
	jo_start_pack,
	jo_mid_pack,
	jo_end_pack
};

///NVR IO类型
enum J_IoType
{
	jo_io_read = 1,		//读标识
	jo_io_write			//写标识
};

///NVR 告警类型
enum J_AlarmType
{
	jo_video_lost = 1,		//视频丢失
	jo_video_motdet,		//移动侦测
	jo_video_hide,			//视频遮挡
	
	jo_rcd_auto = 101,		//自动录像
	jo_rcd_manual,
	jo_rcd_timing,
	jo_rcd_alarm,
};

///NVR命令集合
enum J_CommandType
{
	jo_start_real = 1,		//启动实时视频
	jo_stop_real,			//关闭实时视频
	jo_start_vod,			//播放录像文件
	jo_stop_vod,			//停止播放
	jo_pause_vod,			//暂停
	jo_settime_vod,			//设置播放时间
	jo_setpos_vod,			//设置播放位置
	jo_setscale_vod,		//设置播放速度
	jo_read_data,			//读取数据
	jo_start_voice,			//启动对讲
	jo_stop_voice			//关闭对讲
};

///帧类型
enum J_MediaType
{
	jo_media_unknow = 1,		//未知类型
	jo_media_head,				//视频头信息
	jo_video_i_frame,			//关键帧
	jo_video_b_frame,			//视频B帧
	jo_video_p_frame,			//视频P帧
	jo_audio_frame,				//音频帧
	jo_media_broken,			//视频断线
	jo_file_end,
	
	jo_video_normal = 100,
	jo_video_yuyv,
	jo_video_mjpeg,
};

///设备状态枚举
enum J_DevStatus
{
	jo_dev_ready = 1,
	jo_dev_broken,
};

///回放数据模式
enum J_GetDataMode
{
	jo_pull_mode = 1,
	jo_push_mode,
};

///帧头结构
struct J_StreamHeader
{
	j_uint32_t dataLen;			//数据长度
	j_uint32_t frameType;		//帧类型
	j_uint64_t timeStamp;		//时间戳
	j_uint32_t frameNum;
	//j_char_t data[1];			//帧数据
};

///NVR命令头结构
struct J_CmdHeader
{
	j_uint32_t cmd;
	j_uint32_t type;
	union
	{
		j_char_t resid[16];
		j_char_t fileid[16];
	};
};

///NVR命令回复结构
struct J_RetHeader
{
	j_uint32_t type;				//设备类型  1-hik
	j_uint32_t retCode;				//0-sucess; <0-error
};

///NVR存储文件的帧头
struct J_FrameHeader
{
	j_uint32_t frameType;		//见MediaType
	j_uint32_t length;			//帧数据长度
	j_uint32_t offset;			//相对于文件的偏移
	j_uint64_t timeStamp;		//相对时间戳
};

///NVR存储文件的文件格式
struct J_FileHeader
{
	j_char_t type[4];			//数据类型, body-音视频数据, head-头数据，存放一系列NVRFrameHeader
	j_uint32_t length;			//数据长度,不包含NVRFileHeader
};

///文件信息
struct J_FileInfo
{
	j_time_t tStartTime;					//文件的开始时间
	j_time_t tStoptime;						//文件的结束时间
	j_string_t fileName;
};
typedef std::vector<J_FileInfo> j_vec_file_info_t;

///录像信息
struct J_RcdTimeInfo
{
	j_time_t begin_time;
	j_time_t end_time;
};

///媒体上下文信息
struct J_MediaContext
{
	j_uint32_t forcc;			//媒体类型
	j_uint32_t len;				//接下来的数据长度
	j_uint16_t num;				//流数量
	j_char_t data[1];			//扩展数据长度
};

///媒体上下文数据
struct J_ContextData
{
	j_uint32_t forcc;			//媒体类型
	j_uint32_t len;				//接下来的数据长度
	struct
	{
		j_int32_t len;
		j_char_t data[256];
	} cxt;
};

///前端设备信息结构
struct J_DeviceInfo
{
	j_int32_t devId;			//设备ID
	j_char_t devIp[16];			//设备IP地址
	j_uint16_t devPort;			//设备端口
	j_char_t devType[16];		//设备类型
	j_char_t userName[16];		//用户名
	j_char_t passWd[32];		//密码
	j_int32_t devStatus;		//设备状态
};

///通道信息结构
struct J_ChannelInfo
{
	j_int8_t  devId;				//所属设备ID
	j_int32_t channelNum;			//通道编号
	j_char_t resid[16];				//资源ID
	j_int32_t record_type;			//录像类型
};

///录像信息结构
struct J_RecordInfo
{
	j_char_t vodPath[256];				//录像路径
	j_uint32_t fileSize;				//文件大小
	j_uint32_t timeInterval;			//录像文件间隔  单位(毫秒)
	j_uint32_t preRecordTime;			//预录时间 单位(秒)
};

///通道ID类型
class J_ChannelKey
{
public:
	j_int32_t stream_type;
	j_string_t resid;

	j_boolean_t operator<(const J_ChannelKey &other) const
	{
		j_boolean_t b_ret = true;
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
    j_char_t start_code[4];		//魔术字段 JOSP
    j_char_t version:4;			//版本号
    j_char_t type:2;			//协议类型 0-tcp, 1-udp
    j_char_t flag:2;			//分包标志 0-未分包, 1-开始, 2-中间, 3-结束包
    j_uint8_t cmd;				//命令
    j_uint16_t sq_num;			//包序号
    j_uint8_t ret;				//返回码头 0-无错误
    j_uint8_t reserved;
    j_uint16_t ex_length;		//扩展数据长度
    j_char_t user_id[32];		//用户ID
    j_char_t crc[4];			//校验码(循环冗余校验)
};

///JOSP 控制协议数据包
struct J_CtrlPacket
{
    J_CtrlHead head;
    j_char_t data[1];
};

///JOSP 用户信息
struct J_UserInfo
{
    j_char_t ip_addr[16];
    j_int16_t port;
    j_boolean_t is_active;
    j_char_t user_name[16];
    j_char_t pass_word[16];
    union
    {
        j_char_t usr_id[32];
        j_char_t res_id[32];
    } id;
};
typedef std::map<j_string_t, J_UserInfo> j_map_user_info_t;

///JOSP 网络信息
struct J_NetWorkInfo
{
    j_char_t ip_addr[16];
    j_int16_t port;
};
typedef std::map<j_socket_t, J_NetWorkInfo> j_map_network_info_t;

///JOSP 登录数据
struct J_LoginData
{
    j_char_t user_name[16];
    j_char_t pass_word[16];
};

///JOSP 云镜控制数据
struct J_PTZCtlData
{
    j_char_t res_id[32];
    j_int16_t command;
    j_int16_t param;
};

///JOSP 录像查询数据
struct J_RecordData
{
	j_char_t res_id[32];
	j_time_t begin_time;
	j_time_t end_time;
};

///JOSP 实时视频预览
struct J_RealViewData
{
	j_char_t res_id[32];		//资源ID
	j_int32_t stream_type;		//码流类型 0-主码流,1-子码流
};

///JOSP 实时视频预览返回
struct J_RealViewRetData
{
	j_char_t media_code[4];		//媒体类型 JOMS
	//视频信息
	j_uint8_t i_frame_ival;		//I帧间隔
	j_uint8_t fps;				//帧率
	j_uint16_t width;			//视频宽度
	j_uint16_t height;			//视频高度
	//音频信息
};

///JOSP 历史视频点播
struct J_VodPlayData
{
	j_char_t res_id[32];		//资源ID
	j_time_t begin_time;		//开始时间
	j_time_t end_time;			//结束时间
};

///JOSP 历史视频点播返回
struct J_VodPlayRetData
{
	j_char_t media_code[4];		//媒体类型 JOMS
	//视频信息
	j_uint8_t i_frame_ival;		//I帧间隔
	j_uint8_t fps;				//帧率
	j_uint16_t width;			//视频宽度
	j_uint16_t height;			//视频高度
	//音频信息
};

///JOSP 请求数据
struct J_RequestData
{
	j_char_t res_id[32];		//资源ID
	j_time_t begin_time;		//开始时间
	j_uint32_t time_ival;		//时间间隔
};

///JOSP 数据头格式
struct J_DataHead
{
	j_char_t start_code[4];		//魔术字段 JOAV
	j_uint32_t data_len;		//数据长度(不包括头)
	j_uint32_t frame_type;		//3-I帧,4-B帧,5-P帧,6-音频帧
	j_uint32_t frame_seq;		//帧序列号
	j_int32_t b_last_frame;		//数据结束标准
	j_int32_t reserve;				//预留
	j_int64_t time_stamp;		//时间戳
};

#endif //~__J_TYPE_H_
