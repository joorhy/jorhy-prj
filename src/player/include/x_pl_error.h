#pragma once

enum J_PL_ERROR_e
{
J_PL_NO_ERROR	= 0,			//无措
J_PL_ERROR_MRL,					//错误的mrl
J_PL_ERROR_PTR,					//错误的point
J_PL_ERROR_WINDOW_HWND,			//错误的window句柄
J_PL_ERROR_UNKNOW,				//未知的错误
J_PL_ERROR_FFMPEG,				//ffmpeg内部错误
J_PL_ERROR_LIVE555,				//live555内部错误


//net work
J_PL_ERROR_SOCKET = 100,			//Socket错误
J_PL_ERROR_CONNECT,				//连接远程出错
J_PL_ERROR_RECEIVE,				//socket接受出错
J_PL_ERROR_WRITE,				//socket写数据
J_PL_ERROR_RECEIVE_TIMEOUT,		//接收数据超时
J_PL_ERROR_WRITE_TIMEOUT,		//发送数据超时

//input
J_PL_ERROR_ACCESS_CREATE = 200,	//access 创建error
J_PL_ERROR_THREAD_CREATE,		//thread create failed
J_PL_ERROR_DEMUX_CREATE,			//demux创建error
J_PL_ERROR_CONTROL,				//control error
J_PL_ERROR_AUDIO_DECODE,			//audio decode create error
J_PL_ERROR_VIDEO_DECODE,			//video decode create error
J_PL_ERROR_NO_RENDER,			//no render
J_PL_ERROR_VARIABLE,				//var error
J_PL_ERROR_DEMUX_CONTROL,		// demux control error

//draw
J_PL_ERROR_INIT_DDRAW = 300,		//初始化DDRAW失败
J_PL_ERROR_NO_CAPS,				//没有DDcaps
J_PL_ERROR_NO_CLIPPER,			//没有cliper
J_PL_ERROR_PRIMARY_SURFACE,		//没有主页面
J_PL_ERROR_CREATE_SURFACE,		//创建其他surface失败
J_PL_ERROR_SURFACE_LOCK,			//lock surface error
J_PL_ERROR_MISMATCH_PLANE,		//没有对应的平面
J_PL_ERROR_SURFACE_BLT,			//blt picture error
J_PL_ERROR_NO_SURFACE,			//没有surface

//decoder
J_PL_ERROR_DECODE_INIT = 400,	//初始化decoder失败
J_PL_ERROR_DECODE,				//decode 失败

//network
J_PL_ERROR_NO_NETWORK = 500,		//没有正确的网络input

//buffer
J_PL_ERROR_EMPTY_BUFFER = 600,	//空buffer
J_PL_ERROR_FULL_BUFFER,			//buffer 已满

//access
J_PL_ERROR_ACCESS_END,			//access结束
J_PL_ERROR_ACCESS_ERROR,			//access出错
J_PL_ERROR_ACCESS_CONTROL,		//access control error

//picture
J_PL_ERROR_NO_PICTURE,			//没有图像
J_PL_ERROR_FILENAME,				//错误的文件名
J_PL_ERROR_PICTURE_SUPPORT,		//不支持的图像格式
J_PL_ERROR_OPEN_FILE,			//打开文件错误
J_PL_ERROR_LIBPNG,				//libpng 错误

//record
J_PL_ERROR_STREAM,				//没有整确的stream
};	
