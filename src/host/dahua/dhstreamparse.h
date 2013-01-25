#ifndef NEW_MP4_H
#define NEW_MP4_H

#define DHSTREAMPARSER_API /*__declspec(dllexport)*/extern "C"
#define CALLMETHOD

#define SAMPLE_FREQ_4000	1
#define SAMPLE_FREQ_8000	2
#define SAMPLE_FREQ_11025	3
#define SAMPLE_FREQ_16000	4
#define SAMPLE_FREQ_20000	5
#define SAMPLE_FREQ_22050	6
#define SAMPLE_FREQ_32000	7
#define SAMPLE_FREQ_44100	8
#define SAMPLE_FREQ_48000	9

#define INFOCOUNT_MAX_SIZE		200
#define MAX_BUFFER_SIZE 1028196

// Stream type:
#define DH_STREAM_UNKNOWN			0
#define DH_STREAM_MPEG4				1
#define DH_STREAM_DHPT				3
#define DH_STREAM_NEW				4
#define DH_STREAM_HB				5
#define DH_STREAM_AUDIO				6
#define  DH_STREAM_PS              7
#define  DH_STREAM_DHSTD            8
#define  DH_STREAM_ASF              9
// Frame Type and SubType
#define DH_FRAME_TYPE_UNKNOWN		0
#define DH_FRAME_TYPE_VIDEO			1
#define DH_FRAME_TYPE_AUDIO			2
#define DH_FRAME_TYPE_DATA			3

#define DH_FRAME_TYPE_VIDEO_I_FRAME	0
#define DH_FRAME_TYPE_VIDEO_P_FRAME	1
#define DH_FRAME_TYPE_VIDEO_B_FRAME	2
#define DH_FRAME_TYPE_VIDEO_S_FRAME	3
#define DH_FRAME_TYPE_DATA_TEXT    5
#define DH_FRAME_TYPE_DATA_INTL    6

// Encode type:
#define DH_ENCODE_UNKNOWN				0
#define DH_ENCODE_VIDEO_MPEG4			1
#define DH_ENCODE_VIDEO_H264			2
#define DH_ENCODE_VIDEO_JPEG             3
#define DH_ENCODE_AUDIO_PCM8			7	// 8BITS,8K
#define DH_ENCODE_AUDIO_G729			8
#define DH_ENCODE_AUDIO_IMA				9
#define DH_ENCODE_AUDIO_PCM_MULAW		10
#define DH_ENCODE_AUDIO_G721			11
#define DH_ENCODE_AUDIO_PCM8_VWIS		12	// 16BITS,8K
#define DH_ENCODE_AUDIO_ADPCM			13	// 16BITS,8K/16K
#define DH_ENCODE_AUDIO_G711A			14	// 16BITS,8K
#define DH_ENCODE_AUDIO_TALK           30
#define STREAMPARSER_RESET_REFIND       0
#define STREAMPARSER_RESET_CONTINUE     1

extern "C"
{

typedef struct 
{
	unsigned char* pHeader;  //包含头的数据指针
	unsigned char* pContent; //真正数据的偏移
	unsigned long nLength; //数据长度(包括头部)
	unsigned long nFrameLength; //数据长度.
	
	unsigned int nType; // VIDEO, AUDIO, DATA
	unsigned int nSubType; // I-FRAME, P-FRAME, etc.
	
	unsigned int nEncodeType; // MPEG4/H264, PCM, MSADPCM, etc.
	// 只有I帧才有的数据
	unsigned long nYear;
	unsigned long nMonth;
	unsigned long nDay;
	unsigned long nHour;
	unsigned long nMinute;
	unsigned long nSecond;
	unsigned long nTimeStamp;
	
	unsigned int  nFrameRate;	//帧率
	int			  nWidth;  //图象宽度
	int			  nHeight; //图象高度
	unsigned long nRequence; //序列号
	// 音频才有的数据
	unsigned int nChannels;
	unsigned int nBitsPerSample;
	unsigned int nSamplesPerSecond;
	
	unsigned long nParam1;		// 扩展用
	unsigned long nParam2;		// 扩展用
	
} DH_FRAME_INFO;

typedef void * PARSERHANDLE;
typedef unsigned long PARSERMSG;

#define STREAM_MSG_ERROR			1		// 发生错误
#define STREAM_DISCONTINUITY		2		// 时间不连续
#define STREAM_ENCODE_CHANGED		3		// 图像编码变更
#define STREAM_SIZE_CHANGED			4		// 码流大小变更
#define STREAM_FRAMERATE_CHANGED	5		// 帧率发生变化
#define STREAM_MSG_GET_ONE_FRAME	9		// 获取一帧数据(异步)

typedef unsigned long (* DHSP_CALLBACK)( \
	PARSERHANDLE hHandle, \
	PARSERMSG msg, \
	unsigned long dwParam1, \
	unsigned long dwParam2, \
	unsigned long dwUserData);


	
DHSTREAMPARSER_API PARSERHANDLE 
DHSP_Init(DHSP_CALLBACK msg_cb, unsigned long dwUser);

DHSTREAMPARSER_API int 
DHSP_Free(PARSERHANDLE hHandle);

DHSTREAMPARSER_API int 
DHSP_InputData(PARSERHANDLE hHandle, unsigned char *byData, unsigned long dwLength);

DHSTREAMPARSER_API DH_FRAME_INFO * 
DHSP_GetNextFrame(PARSERHANDLE hHandle);

DHSTREAMPARSER_API DH_FRAME_INFO * 
DHSP_GetNextKeyFrame(PARSERHANDLE hHandle);

DHSTREAMPARSER_API void 
DHSP_Reset(PARSERHANDLE hHandle, int nFlag);

}
#endif // DHSTREAMPARSER_H
