#pragma once
#pragma pack(show)		//显示当前packing aligment的字节数
#pragma pack(push)		//保存对齐状态
#pragma pack(4)			//设定为4字节对齐	

//cmd
#define JOSP_OPEN_STREAM				0x07        //开始预览
#define JOSP_OPEN_STREAM_RET			0x08        //预览应答

#define JOSP_OPEN_FILE						0x0F        //开始回放
#define JOSP_OPEN_FILE_RET				0x10        //回放应答
#define JOSP_REQ_DATA						0x11		//请求数据
#define	JOSP_REQ_DATA_RET				0x12		//应答

//JOSP 控制协议头 
struct JOSP_CtrlHead 
{ 
	unsigned char start_code[4];    //魔术字段 JOSP
	unsigned char version:4;        //版本号
	unsigned char type:2;           //协议类型 0-tcp, 1-udp
	unsigned char flag:2;           //分包标志 0-未分包, 1-开始, 2-中间, 3-结束包
	unsigned char cmd;              //命令
	unsigned short sq_num;          //包序号
	unsigned char ret;              //返回码头 0-无错误
	unsigned char reserved;
	unsigned short ex_length;       //扩展数据长度
	unsigned char user_id[32];      //用户ID
	unsigned char crc[4];           //校验码(循环冗余校验)
};

//JOSP 打开实时视频  
struct JOSP_OpenData 
{ 
	char res_id[32];		//资源ID
	int stream_type;		//码流类型 0-主码流,1-子码流
}; 

//JOSP 打开实时视频返回 
struct JOSP_OpenRetData 
{ 
	unsigned char media_code[4];	//媒体类型 JOMS
	//视频信息
	unsigned char iframe_interval;	//I帧间隔
	unsigned char fps;				//帧率
	unsigned short width;
	unsigned short height;

	//音频信息
}; 

//JOSP 打开历史视频
struct JOSP_OpenVod
{
	char res_id[32];						//资源ID
	unsigned int begin_time;		//开始时间
	unsigned int end_time;			//结束时间
};

//JOSP 打开历史视频返回 
struct JOSP_OpenVodRet 
{ 
	unsigned char media_code[4];	//媒体类型 JOMS
	//视频信息
	unsigned char iframe_interval;	//I帧间隔
	unsigned char fps;				//帧率
	unsigned short width;
	unsigned short height;

	//音频信息
}; 

//JOSP 请求媒体数据 
struct JOSP_RequestData 
{ 
	char res_id[32];						//资源ID
	unsigned int time_stamp;		//开始时间(0-无效)
	int time_interval;					//时间间隔(ms),视频有多长
}; 

//JOSP 请求媒体数据应答 
struct JOSP_RequestRetData
{ 
	int ret;					//返回码(0-成功)
}; 


//JOSP 数据头格式 
struct JOSP_DataHead 
{ 
	unsigned char start_code[4];	//魔术字段 JOAV
	unsigned int data_len;			//数据长度(不包括头)
	unsigned int frame_type;		//3-I帧,4-B帧,5-P帧,6-音频帧
	unsigned long frame_seq;		//帧序列号
	int b_last_frame;					//BOOL类型,结束标志
	int reserve;							//预留
	long long time_stamp;			//时间戳
}; 

#pragma pack(pop)				//恢复对齐状态