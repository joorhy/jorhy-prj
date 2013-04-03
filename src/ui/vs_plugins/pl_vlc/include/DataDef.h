#pragma once
#include "BTKCommon.h"

enum protocol_type_e
{
	PROTOCOL_NONE = 0,

	PROTOCOL_RYSP,
	PROTOCOL_HTTP,
	PROTOCOL_RTSP,
};


enum buffer_type_e
{
	BUFFER_FIFO = 0,
	BUFFER_LIFO,
	BUFFER_LIST,
};

enum decode_type_e
{
	DECODE_AUDIO = 0,
	DECODE_B_FRAME,
	DECODE_I_FRAME,
	DECODE_P_FRAME,
};

/* Append new items at the end ONLY. */
enum codec_id_e
{
	CODE_UNKNOW = 0,
	CODE_H264,
	CODE_AAC,
};


/* Append new items at the end ONLY. */
enum demux_id_e
{
	DEMUX_RYSP = 0,
	DEMUX_TS,
	DEMUX_MP4,
	DEMUX_H264,
};

enum var_type_e
{
	BTK_VAR_BOOL	= 0,
	BTK_VAR_INT,
	BTK_VAR_STRING,		//空字符结尾 '\0' 
	BTK_VAR_INT64,
};

enum btk_state_e
{
	BTK_NORMAL	= 0,
	BTK_PALYING,
	BTK_PAUSE,
	BTK_END,
	BTK_ERROR,
};

enum btk_output_dev_e
{
	BTK_DDRAW = 0,
	BTK_DSOUND,
	BTK_WINDOW_GDI,
};

enum btk_fourcc_e
{
	BTK_CODEC_YV12  = BTK_FOURCC('Y','V','1','2'),
	BTK_CODEC_RGB32	= BTK_FOURCC('R','V','3','2'),
};

enum btk_log_type
{
	BTK_LOG_INFO=0, /**< Important information */
	BTK_LOG_ERR,    /**< Error */
	BTK_LOG_WARN,   /**< Warning */
	BTK_LOG_DBG,    /**< Debug */
};

enum btk_picture_type_e
{
	BTK_PNG		= 0,
	BTK_JPEG,
};

enum btk_work_type		//播放器工作模式
{
	BTK_PLAY_REALTIME = 0,
	BTK_PLAY_FILE,
};
enum btk_speed_e
{
	BTK_SPEED_SLOWEST = 0,			// 1/8	speed
	BTK_SPEED_SLOWER,				// 1/4	speed
	BTK_SPEED_SLOW,					// 1/2	speed
	BTK_SPEED_NORMAL,				// normal speed
	BTK_SPEED_FAST,					// 2	speed
	BTK_SPEED_FASTER,				// 4	speed
	BTK_SPEED_FASTEST,				// 8	speed
};

enum btk_access_query_e
{
	ACCESS_SET_TIME = 0,			/*argl = int64_t */
	ACCESS_SET_BACKRUN,				/*argl = bool  倒着访问*/
	ACCESS_SET_SPEED,				/*argl = int	详见btk_speed_e*/
};