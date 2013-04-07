#pragma once

//自己测试
//#define APACHE_TEST

#ifndef BOOL
typedef int BOOL;
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef STREAME_REALTIME
#define STREAME_REALTIME 0
#endif

#ifndef STREAME_FILE
#define STREAME_FILE	 1
#endif

//ptz control
#define PTZ_UP			0
#define PTZ_DOWN		1
#define PTZ_LEFT		2
#define PTZ_RIGHT		3
#define PTZ_LEFT_UP		4
#define PTZ_RIGHT_UP	5
#define PTZ_LEFT_DOWN	6
#define PTZ_RIGHT_DOWN	7

//button default size
#define BUTTON_WIDTH 128			
#define BUTTON_HEIGHT 128

//toolbar min size
#define MINWINDOW_WIDTH 225
#define MINWINDOW_HEIGHT 30

//full model
#define FULL_PLUGIN		1
#define FULL_SCREEN		2

//windows layout flag
#define SF_ONE		0
#define SF_FOUR		1
#define SF_NINE		2
#define SF_SIXTEEN	3

//player parm
#define DEFAULT_VOLUME 80
#define CALLBACK_TIMER 1	//rtsp
#define CALLBACK_TIMER2 2	//http
#define TOOL_TIMER	3		//工具条定时器
#define ELAPSE_TIME	499		//定时器时间 以毫秒为单位
#define TOOLSTAYTIME 2000	//工具条停留时间
#define UPDATETOOLTIME	500	//更新工具条时间间隔
#define SHOWCTRLCOMMAND FALSE	//是否开启显示工具条
	
//CallBack Function Type
#define CALLBACK_PTZCTL 1 
#define CALLBACK_ONSTATE 2
#define CALLBACK_ONVOD 3

//get path type
#define PATH_LENGTH 512
#define IMAGEPATH 1
#define VIDEOPATH 2

//get windows parm type
#define FOCUS_WINDOW 1
#define ALL_WINDOW 2

//plugin work model
enum WorkModel
{
	REALMODEL = 1,
	VODMODEL
};

//Reconnect Parameter 
#define WAITSTATUS_TIME (2*1000)		//Time Interval
#define RESIZE_TIME		(100)		//Time Interval
#define MAX_POINTNUM 3			//point number
#define FONT_TYPE "宋体"		//字体


//button status
enum ButtonStatus 
{
	Status_Nromal = 0,
	Status_Over,
	Status_Down,
	Status_Disable
};

//extra message
#define WM_TRY_SET_MOUSE_HOOK			WM_USER+1
#define WM_MOUSE_EVENT_NOTIFY			WM_USER+2
#define WM_MOUSE_EVENT_NOTIFY_SUCCESS	0xFF
#define WM_PARENTCHANGE					WM_USER+3
#define WM_OWN_ERASEBKGROUND			WM_USER+4
#define WM_MEDIA_END_REACHED			WM_USER+5
#define WM_OWN_SETFOCUS					WM_USER+6
#define WM_OWN_KILLFOCUS				WM_USER+7
#define WM_OWN_START_WAIT				WM_USER+8			//wParam point to user

//custom protocol
#define CUSTOM_NAME "JOSP"
#define CUSTOM_PROTOCOL CUSTOM_NAME##"://"
#define CUSTOM_VERSION	CUSTOM_NAME##"/1.0 "

/*
*describe: np_plugin与PlayerDLL之间的消息传递
*parm:
*		nType:详见nType define
*		args:传递参数数组
*		argCount:传递参数个数
* return: 失败返回-1，成功返回0*/
typedef void(*CALLBACK_onEvent)(void *pUser,unsigned int nType,int args[],unsigned int argCount);

enum video_type
{
	HIK_VIDEO = 0,		//海康的视屏
	VLC_VIDEO ,			//标准的视屏
};