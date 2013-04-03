#pragma once

enum btk_error_e
{
BTK_NO_ERROR	= 0,			//无措
BTK_ERROR_MRL,					//错误的mrl
BTK_ERROR_PTR,					//错误的point
BTK_ERROR_WINDOW_HWND,			//错误的window句柄
BTK_ERROR_UNKNOW,				//未知的错误
BTK_ERROR_FFMPEG,				//ffmpeg内部错误
BTK_ERROR_LIVE555,				//live555内部错误


//net work
BTK_ERROR_SOCKET = 100,			//Socket错误
BTK_ERROR_CONNECT,				//连接远程出错
BTK_ERROR_RECEIVE,				//socket接受出错
BTK_ERROR_WRITE,				//socket写数据
BTK_ERROR_RECEIVE_TIMEOUT,		//接收数据超时
BTK_ERROR_WRITE_TIMEOUT,		//发送数据超时

//input
BTK_ERROR_ACCESS_CREATE = 200,	//access 创建error
BTK_ERROR_THREAD_CREATE,		//thread create failed
BTK_ERROR_DEMUX_CREATE,			//demux创建error
BTK_ERROR_CONTROL,				//control error
BTK_ERROR_AUDIO_DECODE,			//audio decode create error
BTK_ERROR_VIDEO_DECODE,			//video decode create error
BTK_ERROR_NO_RENDER,			//no render
BTK_ERROR_VARIABLE,				//var error
BTK_ERROR_DEMUX_CONTROL,		// demux control error

//draw
BTK_ERROR_INIT_DDRAW = 300,		//初始化DDRAW失败
BTK_ERROR_NO_CAPS,				//没有DDcaps
BTK_ERROR_NO_CLIPPER,			//没有cliper
BTK_ERROR_PRIMARY_SURFACE,		//没有主页面
BTK_ERROR_CREATE_SURFACE,		//创建其他surface失败
BTK_ERROR_SURFACE_LOCK,			//lock surface error
BTK_ERROR_MISMATCH_PLANE,		//没有对应的平面
BTK_ERROR_SURFACE_BLT,			//blt picture error
BTK_ERROR_NO_SURFACE,			//没有surface

//decoder
BTK_ERROR_DECODE_INIT = 400,	//初始化decoder失败
BTK_ERROR_DECODE,				//decode 失败

//network
BTK_ERROR_NO_NETWORK = 500,		//没有正确的网络input

//buffer
BTK_ERROR_EMPTY_BUFFER = 600,	//空buffer
BTK_ERROR_FULL_BUFFER,			//buffer 已满

//access
BTK_ERROR_ACCESS_END,			//access结束
BTK_ERROR_ACCESS_ERROR,			//access出错
BTK_ERROR_ACCESS_CONTROL,		//access control error

//picture
BTK_ERROR_NO_PICTURE,			//没有图像
BTK_ERROR_FILENAME,				//错误的文件名
BTK_ERROR_PICTURE_SUPPORT,		//不支持的图像格式
BTK_ERROR_OPEN_FILE,			//打开文件错误
BTK_ERROR_LIBPNG,				//libpng 错误

//record
BTK_ERROR_STREAM,				//没有整确的stream
};	
