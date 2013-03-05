/*
 * Attention:
 * 以"r_"为前缀的是收到的数据结构
 * 以"s_"为前缀的是要发送的数据结构
 */


#ifndef _X_SDK_DEF_H_
#define _X_SDK_DEF_H_
#include "j_includes.h"

using namespace std;


struct _cha						/*通道描述*/
{
	int cha;						/*通道号,enc_cha的id*/
	string resid;					/*资源唯一编码*/
	int ms;						/*是否支持多码流*/
};

struct _res						/*前端描述*/
{
	int id;						/*encoder的id*/
	int type;						/*视频前端类型*/
	string ip;						/**/
	int port;						/**/
	string user;					/**/
	string pass;					/**/
	vector<_cha> chanum;			/*通道号的数组对象*/
};

struct _parm
{
	string store;					/*存储路径*/
	int segment_h;				/*历史录像分段大小(秒)*/
	int segment_a;				/*告警录像分段大小(秒)*/
	vector<_res> resnum;			/*res的数组对象*/
};


/**********************************************************************************************************/
									/*
									 *SS 向 MC 请求通讯，返回的数据结构
									 */
/*服务器注册初始化*/
struct r_register
{
	int cmd;			/*命令类型，功能编号*/
	int rst;			/*命令返回值，0为成功，非0为错误代码*/
	_parm parm;		/*返回参数*/
};


struct r_devconfig
{
	int rst;			/*命令返回值，0为成功，1资源错误， 2无权限, 3资源不满足, 4暂时锁定*/
	struct
	{
		int id;				/*encoder 的 id*/
		string type;		/*编码器类型*/
		string ip;			/*编码器ip*/
		int 	port;		/*编码器端口*/
		string user;		/*编码器用户名*/
		string pass;		/*编码器密码*/
		int 	cha;		/*编码器通道号*/
		string resid;		/*resid*/
		int 	ms;			/*是否支持多码流*/
		int		store;		/*是否前端存储*/
	}parm;
};

struct r_historyfile
{
	int rst;			/*命令返回值，0为成功，1资源错误， 2无权限, 3资源不满足, 4暂时锁定*/
	struct
	{
		int		dvr;				/*0:NVR, 1:DVR*/
		vector<string> files;			/*NVR文件绝对路径,文件列表的顺序是较早时间的文件在前面，较晚的文件在后面*/
	}parm;
};

struct s_fileinfo
{
	string file;
	time_t		stime;
	time_t		etime;
};
struct s_record
{
	string resid;
	vector<s_fileinfo> filenum;
};
/***********************************************************************************************************/

/***********************************************************************************************************/
										/*
										 * MC 向 SS 请求通讯，SS收到的数据结构
										 */

/*录像控制  cmd=101*/
struct r_recordcol
{
	int act;				/*1=启动录像, 2=停止录像*/
	string resid;
	int ms;		/*用来标示使用那个码流来进行录像，如果指定的resid已经开始录像使用act=1可以改变录像码流*/
};

/*cmd=102*/
struct r_DVRrecord
{
	string resid;
	time_t stime;
	time_t etime;
};

/*cmd=103*/
struct r_cameracol
{
  /*
   * 1:上			2:下 			3:左				4:右
   * 5:左上			6:右上			7:左下			8:右下
   * 9:预置点设定	10:预置点清除	11:预置点调用
   * 12:放大			13:缩小
   */
	string resid;
	int action;
	int value;				/*0~255 表示速度或者预置点的编号*/
};

/*cmd=104*/
struct r_filemove
{
	string resid;
	int type;
	string files;				/*文件绝对路径。 files是可选的因为录像文件可能存放在前端，根据type进行标示*/
	time_t stime;
	time_t etime;
	string dist;				/*迁移至的路径*/
};

/*cmd=105*/
struct r_rcd_search
{
	string resid;
	time_t begin_time;			/*开始时间*/
	time_t end_time;			/*结束时间*/				
};



/***********************************************************************************************************/
#endif //~_X_SDK_DEF_H_
