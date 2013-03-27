/*************************************************************************
**                           streamAnalyzer 

**      (c) Copyright 1992-2004, ZheJiang Dahua Technology Stock Co.Ltd.
**                         All Rights Reserved
**
**	File  Name		: StreamAnalyzer.h
**	Description		: streamAnalyzer header
**	Modification	: 2010/07/13	yeym	Create the file
**************************************************************************/
#ifndef __STREAM_ANALYZER_H
#define __STREAM_ANALYZER_H
#define INOUT
#define IN
#define OUT

#ifndef _WIN32
#define __stdcall
#endif

//#include <windows.h>
#include <vector>
#include "platform.h"

#ifdef WIN32
#ifdef STREAMANALYZER_EXPORTS
#define ANALYZER_API __declspec(dllexport)
#else
#define ANALYZER_API __declspec(dllimport)
#endif
#else
#define ANALYZER_API
#endif

#ifndef NOERROR
#define NOERROR	0
#endif

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
// 帧类型
typedef enum _ANA_MEDIA_TYPE
{
	FRAME_TYPE_UNKNOWN = 0,			//帧类型不可知
	FRAME_TYPE_VIDEO,				//帧类型是视频帧
	FRAME_TYPE_AUDIO,				//帧类型是音频帧
	FRAME_TYPE_DATA					//帧类型是数据帧
}ANA_MEDIA_TYPE;

// 子类型
typedef enum _FRAME_SUB_TYPE
{
	TYPE_DATA_INVALID = -1,				//数据无效
	TYPE_VIDEO_I_FRAME = 0 ,			// I帧
	TYPE_VIDEO_P_FRAME,				// P帧
	TYPE_VIDEO_B_FRAME,				// B帧
	TYPE_VIDEO_S_FRAME,				// S帧
	TYPE_WATERMARK_TEXT,			//水印数据为TEXT类型
	TYPE_WATERMARK_JPEG,			//水印数据为JPEG类型
	TYPE_WATERMARK_BMP,				//水印数据为BMP类型
	TYPE_DATA_INTL,					//智能分析帧
	TYPE_VIDEO_JPEG_FRAME,
	TYPE_DATA_ITS					//its信息帧
}FRAME_SUB_TYPE;						

// 编码类型
typedef enum _ENCODE_TYPE
{
	ENCODE_VIDEO_UNKNOWN = 0,		//视频编码格式不可知
	ENCODE_VIDEO_MPEG4 ,			//视频编码格式是MPEG4
	ENCODE_VIDEO_HI_H264,			//视频编码格式是海思H264
	ENCODE_VIDEO_DH_H264,			//视频编码格式是大华码流H264
	ENCODE_VIDEO_JPEG,				//视频编码格式是标准JPEG
	ENCODE_VIDEO_INVALID,			//视频编码格式无效

	ENCODE_AUDIO_PCM = 7,			//音频编码格式是PCM8
	ENCODE_AUDIO_G729,				//音频编码格式是G729
	ENCODE_AUDIO_IMA,				//音频编码格式是IMA
	ENCODE_PCM_MULAW,				//音频编码格式是PCM MULAW
	ENCODE_AUDIO_G721,				//音频编码格式是G721
	ENCODE_PCM8_VWIS,				//音频编码格式是PCM8_VWIS
	ENCODE_MS_ADPCM,				//音频编码格式是MS_ADPCM
	ENCODE_AUDIO_G711A,				//音频编码格式是G711A
	ENCODE_AUDIO_AMR,				//音频编码格式是AMR
	ENCODE_AUDIO_PCM16,				//音频编码格式是PCM16
	ENCODE_AUDIO_G711U = 22,		//音频编码格式是G711U
	ENCODE_AUDIO_G723,				//音频编码格式是G723
	ENCODE_AUDIO_AAC = 26,			//音频编码格式是AAC
	ENCODE_AUDIO_TALK = 30,
	ENCODE_VIDEO_H263,
	ENCODE_VIDEO_PACKET
}ENCODE_TYPE;
		
enum
{
	DH_ERROR_NOFIND_HEADER = -20, 	//数据信息不足,如没有帧头
	DH_ERROR_FILE, 					//文件操作失败
	DH_ERROR_MM, 					//内存操作失败
	DH_ERROR_NOOBJECT, 				//不存在相应的对象
	DH_ERROR_ORDER, 				//接口调用次序不正确
	DH_ERROR_TIMEOUT, 				//处理超时
	DH_ERROR_EXPECPT_MODE, 			//接口调用不正确
	DH_ERROR_PARAMETER, 			//参数出错
	DH_ERROR_NOKNOWN, 				//错误原因未明
	DH_ERROR_NOSUPPORT, 			//不提供实现
	DH_ERROR_OVER,
	DH_ERROR_LOCKTIMEOUT,
	DH_NOERROR = NOERROR 			//没有错误
};


typedef enum _STREAM_TYPE
{
	DH_STREAM_UNKNOWN = 0,
	DH_STREAM_MPEG4,		
	DH_STREAM_DHPT =3,
	DH_STREAM_NEW,
	DH_STREAM_HB,
	DH_STREAM_AUDIO,
	DH_STREAM_PS,
	DH_STREAM_DHSTD,
	DH_STREAM_ASF,
	DH_STREAM_DHAV,
	DH_STREAM_3GPP,
	DH_STREAM_RAW,	
	DH_STREAM_TS,
}STREAM_TYPE;

enum
{
	E_STREAM_NOERROR = 0,		//数据校验无误
	E_STREAM_TIMESTAND,			//时间错误，未实现
	E_STREAM_LENGTH,			//长度信息出错
	E_STREAM_HEAD_VERIFY,		//未实现
	E_STREAM_VERIFY,			//数据校验失败
	E_STREAM_HEADER,			//数据没有帧头
	E_STREAM_NOKNOWN,			//不可知错误，未实现
	E_STREAM_LOSTFRAME,
	E_STREAM_WATERMARK
};

enum
{
	DEINTERLACE_PAIR = 0,
	DEINTERLACE_SINGLE,
	DEINTERLACE_NONE,
};
////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(1)

typedef struct _DHTIME								
{
	DWORD second		:6;					//	秒	1-60		
	DWORD minute		:6;					//	分	1-60		
	DWORD hour			:5;					//	时	1-24		
	DWORD day			:5;					//	日	1-31		
	DWORD month			:4;					//	月	1-12		
	DWORD year			:6;					//	年	2000-2063	
}DHTIME,*pDHTIME;
// 帧信息
typedef struct __ANA_FRAME_INFO
{
	ANA_MEDIA_TYPE		nType;				// 帧类型
	FRAME_SUB_TYPE	nSubType;			// 子类型
	STREAM_TYPE		nStreamType;		// 数据打包协议类型（DHAV）
	ENCODE_TYPE		nEncodeType;		// 编码类型

	uint8*	        pHeader;			// 包含帧头的数据指针
	uint32			nLength;			// 包含帧头的数据长度
	uint8*	        pFrameBody;			// 裸数据指针
	uint32			nBodyLength;		// 裸数据长度
	uint32			dwFrameNum;			// 帧序号－丢帧判断

	uint32			nDeinterlace;		// 解交错
	uint8			nFrameRate;			// 帧率
	uint8			nMediaFlag;				// 码流类型标记，h264解码用(0：大华码流；2：海思码流)
	uint16			nWidth;				// 分辨率
	uint16			nHeight;

	uint16			nSamplesPerSec;		// 采样率
	uint8			nBitsPerSample;		// 位数
	uint8			nChannels;

	// 时间日期
	uint16			nYear;	
	uint16			nMonth;
	uint16			nDay;
	uint16			nHour;
	uint16			nMinute;
	uint16			nSecond;
	uint32			dwTimeStamp;		// 时间戳 mktime返回数值
	
	uint32			Reserved[5];
	uint32			bValid;				// 数据校验－数字水印
} ANA_FRAME_INFO;


typedef	struct  __ANA_INDEX_INFO
{
	uint32	filePos;						//关键帧在文件中的偏移
	uint32	dwFrameNum;						//关键帧帧号
	uint32 dwFrameLen;						//关键帧帧长
	uint32 frameRate;						//帧率
	uint32	frameTime;						//关键帧时间
}ANA_INDEX_INFO;

//智能信息结构
#define  MAX_TRACKPOINT_NUM 10

typedef struct _ANA_IVS_POINT
{
	uint16 		x; 
	uint16 		y; 
	uint16		xSize;
	uint16		ySize;
	//轨迹点是物体外接矩形的中心，根据X，Y及XSize，YSize计算出的物体外接矩形坐标（left，top，right，bottom）：
	//RECT=(X-XSize, Y-YSize, X+XSize, Y+YSize)
	
}ANA_IVS_POINT; 

typedef struct _ANA_IVS_OBJ
{
	uint32				obj_id;						// 物体id
	uint32				enable;						 // 0 表示删除物体  1表示物体轨迹信息有效
	ANA_IVS_POINT 	track_point[MAX_TRACKPOINT_NUM]; 
	uint32				trackpt_num;				// 物体个数，即track_point有效个数
}ANA_IVS_OBJ;

typedef struct _ANA_IVS_PrePos
{
	uint32				nPresetCount;			//预置点信息个数，单位: 1字节
	uint8*				pPresetPos;				//预置点信息指针
}ANA_IVS_PrePos;
#pragma  pack()


typedef enum  _IVS_METHOD
{
	IVS_track,									//分析智能帧物体移动轨迹信息
	IVS_Preset									//分析云台预置点信息
}IVS_METHOD;

enum CHECK_ERROR_LEVEL
{
	CHECK_NO_LEVEL = 0,
	CHECK_PART_LEVEL,
	CHECK_COMPLETE_LEVEL
};



typedef	HANDLE		ANA_HANDLE;
typedef PHANDLE		PANA_HANDLE;

/************************************************************************
 ** 接口定义
 ***********************************************************************/

// 创建码流分析器
ANALYZER_API int32	__stdcall ANA_CreateStream(IN DWORD dwSize,OUT PANA_HANDLE pHandle);

// 销毁码流分析器
ANALYZER_API void	__stdcall ANA_Destroy(IN ANA_HANDLE hHandle);

// 往码流分析器中送数据(返回已经传送进去相应的大小，当返回值！=dwSize，需要多次传送，并且需要调整相应的pBuffer	\
//						是为了防止当解码缓冲区小于客户给定的dwSize，反正死循环，或者丢数据	--YEYM 2010/5/19)
ANALYZER_API int32	__stdcall ANA_InputData(IN ANA_HANDLE hHandle, IN PBYTE pBuffer, IN DWORD dwSize);

// 从码流分析器中取帧数据(-1：失败；0：成功；1：缓冲区已空)
ANALYZER_API int32	__stdcall ANA_GetNextFrame(IN ANA_HANDLE hHandle, OUT ANA_FRAME_INFO* pstFrameInfo);

// 清除码流分析器中缓冲数据
ANALYZER_API BOOL	__stdcall ANA_ClearBuffer(IN ANA_HANDLE hHandle);

// 获取码流分析器中缓冲剩余数据
ANALYZER_API int32	__stdcall ANA_GetRemainData(IN ANA_HANDLE hHandle, IN PBYTE pData, INOUT DWORD* pSize);

// 获取错误码
ANALYZER_API int32	__stdcall ANA_GetLastError(IN ANA_HANDLE hHandle);

ANALYZER_API int32	__stdcall ANA_ParseIvsFrame(IN ANA_FRAME_INFO* pstFrameInfo,INOUT unsigned char* buffer,IN int len,IN IVS_METHOD type);

ANALYZER_API int32	__stdcall ANA_CreateFileIndexEx(IN ANA_HANDLE hHandle,IN struct timeval* tv = NULL,IN int flag = 0);

ANALYZER_API int32	__stdcall ANA_WaitForCreateIndexComplete(IN ANA_HANDLE hHandle);

ANALYZER_API int32	__stdcall ANA_CreateFile(const char* filePath,OUT PANA_HANDLE pHandle);

// 从码流分析器中取帧数据(-1：失败；0：成功；1：缓冲区已空)
ANALYZER_API int32	__stdcall ANA_GetNextAudio(IN ANA_HANDLE hHandle, OUT ANA_FRAME_INFO* pstFrameInfo);

ANALYZER_API int32	__stdcall ANA_ParseFile(IN ANA_HANDLE handle);

ANALYZER_API int32	__stdcall ANA_GetIndexByOffset(IN ANA_HANDLE handle,IN int offset,OUT ANA_INDEX_INFO*);

ANALYZER_API int32	__stdcall ANA_GetMediaFrame(IN ANA_HANDLE hHandle, OUT ANA_FRAME_INFO* pstFrameInfo);

ANALYZER_API int32	__stdcall ANA_Reset(IN ANA_HANDLE hHandle,IN int);

ANALYZER_API int32	__stdcall ANA_EnableError(IN ANA_HANDLE hHandle,IN int nEnableLevel);
#ifdef __cplusplus
}
#endif


#endif // __STREAM_ANALYZER_H



