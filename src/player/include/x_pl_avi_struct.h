#pragma once
#include "x_pl_common.h"

typedef struct
{
	FOURCC fcc;	// 必须为‘avih’
	DWORD  cb;			// 本数据结构的大小，不包括最初的8个字节（fcc和cb两个域）
	DWORD  dwMicroSecPerFrame;   // 视频帧间隔时间（以毫秒为单位）  
	DWORD  dwMaxBytesPerSec;     // 这个AVI文件的最大数据率    
	DWORD  dwPaddingGranularity; // 数据填充的粒度     
	DWORD  dwFlags;				// AVI文件的全局标记，比如是否含有索引块等 
	DWORD  dwTotalFrames;		// 总帧数     
	DWORD  dwInitialFrames;		// 为交互格式指定初始帧数（非交互格式应该指定为0） 
	DWORD  dwStreams;			// 本文件包含的流的个数  
	DWORD  dwSuggestedBufferSize; // 建议读取本文件的缓存大小（应能容纳最大的块）  
	DWORD  dwWidth;				// 视频图像的宽（以像素为单位）  
	DWORD  dwHeight;			// 视频图像的高（以像素为单位）   
	DWORD  dwReserved[4];		// 保留
} MainAVIHeader;

typedef struct 
{
	FOURCC fcc;				// 必须为‘strh’      
	DWORD  cb;				// 本数据结构的大小，不包括最初的8个字节（fcc和cb两个域） 
	FOURCC fccType;			// 流的类型：‘auds’（音频流）、‘vids’（视频流）、                    //‘mids’（MIDI流）、‘txts’（文字流）
	FOURCC fccHandler;		// 指定流的处理者，对于音视频来说就是解码器   
	DWORD  dwFlags;			// 标记：是否允许这个流输出？调色板是否变化？     
	WORD   wPriority;		// 流的优先级（当有多个相同类型的流时优先级最高的为默认流）  
	WORD   wLanguage;      
	DWORD  dwInitialFrames;	// 为交互格式指定初始帧数     
	DWORD  dwScale;			// 这个流使用的时间尺度      
	DWORD  dwRate;     
	DWORD  dwStart;			// 流的开始时间     
	DWORD  dwLength;		// 流的长度（单位与dwScale和dwRate的定义有关）    
	DWORD  dwSuggestedBufferSize; // 读取这个流数据建议使用的缓存大小     
	DWORD  dwQuality;		// 流数据的质量指标（0 ~ 10,000）     
	DWORD  dwSampleSize;	// Sample的大小      
	struct 
	{         
		short int left;         
		short int top;          
		short int right;          
		short int bottom; 
	}rcFrame;					// 指定这个流（视频流或文字流）在视频主窗口中的显示位置              
								// 视频主窗口由AVIMAINHEADER结构中的dwWidth和dwHeight决定
} AVIStreamHeader;

typedef struct 
{   
	WORD  wFormatTag;    
	WORD  nChannels;    
	DWORD nSamplesPerSec;    
	DWORD nAvgBytesPerSec;    
	WORD  nBlockAlign;    
	WORD  wBitsPerSample;    
	WORD  cbSize;  
}WaveFormatEX;