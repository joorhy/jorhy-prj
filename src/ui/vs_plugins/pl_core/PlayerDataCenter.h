#pragma once

#define REAL_BUFFSIZE (2 * 1024 * 1024)		//存放数据缓冲区大小:real
#define vod_BUFFSIZE (4 *1024 *1024)		//存放数据缓冲区大小:vod
#define DEFAULT_RECVBUFFSIZE (1024 * 1024)		//recv缓冲区大小
#define IO_READ_SIZE 1400				
#define REAL_PLAYERSIZE (1024 * 1024)		//播放器解码缓冲区大小:real
#define VOD_PLAYERSIZE (4 * 1024 * 1024)	//播放器解码缓冲区大小:vod

#define REAL_FRAMENUM 10						//播放器缓存大小:real
#define VOD_FRAMENUM 25							//播放器缓存大小:vod

//fourCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
	((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |   \
	((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))

#define HIKFOURCC MAKEFOURCC('H','I','K','0')

struct StreamHeader
{
	unsigned int datalen;		//帧数据长度
	unsigned long VideoTypeFCC;	//视频类型FourCC
	unsigned int datatype;		//数据类型
};

enum DataType
{
	VIDEO_HEAD = 0,
	VIDEO_DATA,
};
