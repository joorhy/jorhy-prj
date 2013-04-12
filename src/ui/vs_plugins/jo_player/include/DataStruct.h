#pragma once
#include "DataDef.h"


struct protocol_t
{
	char *psz_name;
	int i_name;
}static const btk_protocol_values[] = {
								{"RYSP",PROTOCOL_RYSP},
								{"HTTP",PROTOCOL_HTTP},
								{"RTSP",PROTOCOL_RTSP},
								{0,	PROTOCOL_NONE},
								};
struct play_speed_t
{
	int key;
	float value;
}static const btk_speed_values[] = {
								{BTK_SPEED_SLOWEST,	0.125},
								{BTK_SPEED_SLOWER,	0.25},
								{BTK_SPEED_SLOW,	0.5},
								{BTK_SPEED_NORMAL,	1.0},
								{BTK_SPEED_FAST,	2.0},
								{BTK_SPEED_FASTER,	4.0},
								{BTK_SPEED_FASTEST,	8.0},
								};

struct btk_cfg_t
{
	int i_protocol;			//protocol_type_e
	btk_work_type i_real;	//是否是实时，access模块可以忽略该参数
	int i_port;
	char psz_ip[16];

	char psz_resource[256];		//file path or net resource 
};


struct btk_access_t
{
	int media_type;			//媒体封装格式,选择合适的demux
};

struct btk_buffer_t
{
	int datatype;			//0-原数据，1-视频数据(解码后)，2-音频数据(解码后)
	int datasize;			//实体数据
	int extrasize;			//额外的描述数据
};

struct btk_demux_t
{
	int media_type;			//媒体封装格式,选择合适的demux,详见demux_id_e
	int fps;
	btk_work_type i_real;	//是否是实时，access模块可以忽略该参数

	//视频
	unsigned int width;		//宽
	unsigned int height;	//高
	int iframe_interval;	//I帧间隔

};

//input->decode数据输出头
struct btk_decode_t			
{
	long long timestamp;
	int type;				//是否是音频或者视频 参见decode_type_e
	int size;
	int fps;
};

struct btk_transform_t
{	
	//视频
	int vType;			//参见codec_id_e
	unsigned int width;		//宽
	unsigned int height;	//高
	int iframe_interval;	//I帧间隔


	int aType;

};

//decode->output数据输出头
struct btk_audio_format_t
{
	long long timestamp;
	int size;
};

//decode->output数据输出头
struct btk_video_format_t
{
	long long timestamp;
	int size;
	int fps;
};

struct btk_audio_out_t		//for init audio output
{
	int type;
	int bit;
	int rate;
	int sample;
};

struct btk_video_out_t		//for init video output
{
	int VoutDev;			//显示模块 ddraw？
	int FourCCType;				//fourcc code
	int width;
	int height;
};
