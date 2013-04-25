#pragma once
#include "x_pl_common.h"

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
	J_PL_VAR_BOOL	= 0,
	J_PL_VAR_INT,
	J_PL_VAR_STRING,		//空字符结尾 '\0' 
	J_PL_VAR_INT64,
};

enum j_pl_state
{
	J_PL_NORMAL	= 0,
	J_PL_PALYING,
	J_PL_PAUSE,
	J_PL_END,
	J_PL_ERROR,
};

enum j_pl_output_dev
{
	J_PL_DDRAW = 0,
	J_PL_DSOUND,
	J_PL_WINDOW_GDI,
};

enum j_pl_fourcc
{
	J_PL_CODEC_YV12  = J_PL_FOURCC('Y','V','1','2'),
	J_PL_CODEC_RGB32	= J_PL_FOURCC('R','V','3','2'),
};

enum j_pl_log_type
{
	J_PL_LOG_INFO=0, /**< Important information */
	J_PL_LOG_ERR,    /**< Error */
	J_PL_LOG_WARN,   /**< Warning */
	J_PL_LOG_DBG,    /**< Debug */
};

enum j_pl_picture_type
{
	J_PL_PNG		= 0,
	J_PL_JPEG,
};

enum  j_pl_work_type		//播放器工作模式
{
	J_PL_PLAY_REALTIME = 0,
	J_PL_PLAY_FILE,
};
enum  j_pl_speed
{
	J_PL_SPEED_SLOWEST = 0,			// 1/8	speed
	J_PL_SPEED_SLOWER,				// 1/4	speed
	J_PL_SPEED_SLOW,					// 1/2	speed
	J_PL_SPEED_NORMAL,				// normal speed
	J_PL_SPEED_FAST,					// 2	speed
	J_PL_SPEED_FASTER,				// 4	speed
	J_PL_SPEED_FASTEST,				// 8	speed
};

enum  j_pl_access_query
{
	ACCESS_SET_TIME = 0,			/*argl = int64_t */
	ACCESS_SET_BACKRUN,				/*argl = bool  倒着访问*/
	ACCESS_SET_SPEED,				/*argl = int	详见j_pl_speed*/
};