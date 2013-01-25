#ifndef __HIKPARSERDEF_H_
#define __HIKPARSERDEF_H_

#ifdef __cplusplus
	extern "C"{
#endif

#define FILE_HEAD			            		0
#define VIDEO_I_FRAME		            	1
#define VIDEO_B_FRAME		           	2
#define VIDEO_P_FRAME		            	3
#define AUDIO_PACKET		            		10
#define PRIVT_PACKET                    	11

#define HIK_H264_E_FRAME        	    (1 << 6)

#define ERROR_NOOBJECT                  -1
#define ERROR_NO                        0
#define ERROR_OVERBUF                   1
#define ERROR_PARAMETER                 2
#define ERROR_CALL_ORDER                3
#define ERROR_ALLOC_MEMORY              4
#define ERROR_OPEN_FILE                 5
#define ERROR_MEMORY                    11
#define ERROR_SUPPORT                   12
#define ERROR_UNKNOWN                   99



#ifndef __stdcall
#define __stdcall
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

typedef struct _PACKET_INFO
{
	int					nPacketType;
	char*				pPacketBuffer;
	unsigned int		dwPacketSize;

	int					nYear;
	int					nMonth;
	int					nDay;
	int					nHour;
	int					nMinute;
	int					nSecond;

	unsigned int		dwTimeStamp;

} PACKET_INFO;

typedef struct _PACKET_INFO_EX
{
	int						nPacketType;
	char*					pPacketBuffer;
	unsigned int			dwPacketSize;

	int						nYear;
	int						nMonth;
	int						nDay;
	int						nHour;
	int						nMinute;
	int						nSecond;

	unsigned int			dwTimeStamp;

	unsigned int			dwFrameNum;
	unsigned int			dwFrameRate;
	unsigned short			uWidth;
	unsigned short			uHeight;
	unsigned int			dwTimeStampHigh;
	unsigned int			dwFlag;
	unsigned int			dwFilePos;
	unsigned int			Reserved[4];

} PACKET_INFO_EX;

enum HeadType
{
	HIK_TYPE = 1,
	PACKHEAD_TYPE,
	PSM_TYPE,
	VIDEO_TYPE,
	AUDIO_TYPE,
	SKIP_TYPE,
	H264_TYPE,
	G722_1_TYPE
};

struct HikStreamHead
{
	unsigned int media_fourcc;
	unsigned short media_version;
	unsigned short device_id;

	unsigned short system_format;
	unsigned short video_format;

	unsigned short audio_format;
	unsigned char audio_channels;
	unsigned char audio_bits_per_sample;
	unsigned int audio_samplesrate;
	unsigned int audio_bitrate;
};

void * __stdcall HIKANA_CreateStreamEx(IN unsigned int dwSize, IN unsigned char * pHeader);
void   __stdcall HIKANA_Destroy(IN void * hHandle);
int   __stdcall HIKANA_InputData(IN void * hHandle, IN unsigned char * pBuffer, IN unsigned int dwSize);
int	   __stdcall HIKANA_GetOnePacketEx(IN void * hHandle, OUT PACKET_INFO_EX* pstPacket);
int   __stdcall HIKANA_ClearBuffer(IN void * hHandle);
int	   __stdcall HIKANA_GetRemainData(IN void * hHandle, IN unsigned char * pData, OUT unsigned int* pdwSize);
unsigned int  __stdcall HIKANA_GetLastErrorH(IN void * hHandle);

#ifdef __cplusplus
	}
#endif


#endif //~__HIKPARSERDEF_H_
