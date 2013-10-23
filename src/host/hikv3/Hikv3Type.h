#ifndef __HikType_h_
#define	__HikType_h_

/* network SDK version
day  : bit 0 - 5
month: bit 6 - 9
year : bit 10 - 15
minor: bit 16 - 23
major: bit 24 - 31
*/
#define MAKE_NETSDK_VERSION(_major, _minor, year, month, day)	\
(	\
	(((_major)&0xff)<<24) | 	\
	(((_minor)&0xff)<<16) |	\
	((((year)-2000)&0x3f)<<10)	|\
	(((month)&0xf)<<6) |	\
	((day)&0x3f)	\
)

#define NETSDK_VERSION_V10   MAKE_NETSDK_VERSION(1, 0, 2004, 10, 4)
#define NETSDK_VERSION_V12   MAKE_NETSDK_VERSION(1, 2, 2005, 3, 15)
#define NETSDK_VERSION_V13   MAKE_NETSDK_VERSION(1, 3, 2005, 4, 1)
#define NETSDK_VERSION_V14   MAKE_NETSDK_VERSION(1, 4, 2005, 5, 30)
#define NETSDK_VERSION_V15   MAKE_NETSDK_VERSION(1, 5, 2005, 12, 28)
#define NETSDK_VERSION_V16   MAKE_NETSDK_VERSION(1, 6, 2006, 8, 14)
#define NETSDK_VERSION_V20   MAKE_NETSDK_VERSION(2, 0, 2006, 4, 27)
#define NETSDK_VERSION_V21   MAKE_NETSDK_VERSION(2, 1, 2006, 8, 14)
#define NETSDK_VERSION_V211  MAKE_NETSDK_VERSION(2, 1, 2007, 11, 18)
#define NETSDK_VERSION_V22   MAKE_NETSDK_VERSION(2, 2, 2008, 3, 14)
#define NETSDK_VERSION_V221  MAKE_NETSDK_VERSION(2, 2, 2009, 3, 17)
#define NETSDK_VERSION_V30   MAKE_NETSDK_VERSION(3, 0, 2008, 2, 28)
#define NETSDK_VERSION_V31   MAKE_NETSDK_VERSION(3, 1, 2009, 7, 30)

/*
 Hik command
 */
#define HIK_CMD_LOGIN           0x010000
#define HIK_CMD_LOGINEX         0x010010
#define HIK_CMD_LOGOUT          0x010100
#define HIK_CMD_USEREXCHANGE    0x010200

#define HIK_CMD_GET_DEVCFG      0x020000
#define HIK_CMD_SET_DEVCFG      0x020001

#define	HIK_CMD_VIDEO_TCP	0x030000
#define	HIK_CMD_VIDEO_UDP	0x030001
#define	HIK_CMD_VIDEO_MCAST     0x030002
#define	HIK_CMD_VIDEO_RTP       0x030003
#define HIK_CMD_DATA_EXCHANGE   0x030006

#define HIK_CMD_AUDIO_GET_CFG   0x110044
#define HIK_CMD_AUDIO_START     0x030500

#define HIK_CMD_PTZ_CTRL                0x030200
#define HIK_CMD_PTZ_CTRL_WITH_SPEED     0x030203

#define HIK_CMD_START_RECORD_FILE   0x030d00
#define HIK_CMD_STOP_RECORD_FILE    0x030d01

#define HIK_CMD_MAIN_MAKE_IFRAME 		0x090100	 	//主码流产生I帧
#define HIK_CMD_SUB_MAKE_IFRAME 		0x090101	 	//子码流产生I帧

#define	HIK_CMD_FIND_FILE					0x030100		//查找文件
#define	HIK_CMD_PLAYBYFILE				0x030101		//按文件回放，建立连接
#define	HIK_CMD_PLAYBYTIME				0x030102		//按时间回放，建立连接
#define HIK_CMD_FILE_EXCHANGE			0x030109		//交互命令
#define HIK_CMD_FIND_FILE_V3			0x111040		//搜索文件（V30版本）

#define	HIK_CMD_STARTPLAY				0x030103		//开始回放
#define	HIK_CMD_SETPOS					0x030105		//按文件回放,改变播放的进度
#define	HIK_CMD_PAUSE						0x030107		//暂停
#define	HIK_CMD_RESTART					0x030108		//重新开始
#define HIK_CMD_SETSPEED 	      0x03010d        //设置下载的速度(SDK_V30版本支持)

//建立报警上传通道
#define HIK_CMD_ALARMCHAN				0x030400		//建立报警上传通道(布防)
#define HIK_CMD_ALARMCHAN_V30			0x111020	    //建立报警上传通道
/*
 Hik Ptz sub command
 */
#define HIK_PTZ_PRESET_SET      8
#define HIK_PTZ_PRESET_CLR      9
#define HIK_PTZ_PRESET_MOV      39

#define HIK_PTZ_MOVE_UP             21
#define HIK_PTZ_MOVE_DOWN           22
#define HIK_PTZ_MOVE_LEFT           23
#define HIK_PTZ_MOVE_RIGHT          24
#define HIK_PTZ_MOVE_UP_LEFT        25
#define HIK_PTZ_MOVE_UP_RIGHT       26
#define HIK_PTZ_MOVE_DOWN_LEFT      27
#define HIK_PTZ_MOVE_DOWN_RIGHT     28

#define HIK_PTZ_ZOOM_IN             11
#define HIK_PTZ_ZOOM_OUT            12
#define HIK_PTZ_FOCUS_NEAR          13
#define HIK_PTZ_FOCUS_FAR           14
#define HIK_PTZ_IRIS_OPEN       	15  		/* 光圈以速度SS扩大 */
#define HIK_PTZ_IRIS_CLOSE      	16  		/* 光圈以速度SS缩小 */
/*
 values
 */
#define THIS_SDK_VERSION        NETSDK_VERSION_V10
#define HIK_SERIALNUM_LEN       48
#define HIK_NAME_LEN            32
#define HIK_MAX_LINK            6




/*
 returned code
 */
#define HIK_RET_OK              1
#define HIK_NO_SUPPORT			  13
#define HIK_INVALID_ID          30

/*
 Hik struct
 */
struct HikLoginHead
{
    unsigned long len;
    unsigned char protoType;
    unsigned char IPProtoType;
    unsigned char res1[2];
    unsigned long checkSum;
    unsigned long command;
    unsigned long DVRVersion;
    unsigned long res;
    unsigned long clientIP;
    unsigned char clientMAC[6];
    unsigned char res2[2];
};

struct HikCommHead
{
    unsigned long len;
    unsigned char protoType;
    unsigned char res1[3];
    unsigned long checkSum;
    unsigned long command;
    unsigned long clientIP;
    unsigned long userId;
    unsigned char clientMAC[6];
    unsigned char res2[2];
};

struct HikRetHead
{
    unsigned long len;
    unsigned long checkSum;
    unsigned long retVal;
    unsigned char res[4];
};


#define HIK_STREAM_PROTO_TCP        (1<<1)
#define HIK_STREAM_PROTO_UDP        (1<<2)
#define HIK_STREAM_PROTO_RTP        (1<<3)
#define HIK_STREAM_PROTO_MCAST      (1<<4)
#define HIK_STREAM_PROTO_RTSP_TCP   (1<<5)
#define HIK_STREAM_PROTO_RTSP_UDP   (1<<6)
#define HIK_STREAM_PROTO_RTSP_RTP   (1<<7)
#define HIK_STREAM_PROTO_RTSP_MCAST (1<<8)
struct HikLoginRet
{
    unsigned long userID;
    unsigned char serialNum[HIK_SERIALNUM_LEN];
    unsigned char devType;
    unsigned char nVideoChannel;
    unsigned char startChannel;
    unsigned char nAlarmIn;
    unsigned char nAlarmOut;
    unsigned char nDisk;
    unsigned char protocol;
    unsigned char nAudioChannel;
    unsigned char nIPChannel;
    unsigned char subProtocol;
    unsigned char res[30];
};

struct HikDevConfig
{
    unsigned long dwSize;
    unsigned char sDVRName[HIK_NAME_LEN];
    unsigned long dwDVRID;
    unsigned long dwRecycleRecord;
    unsigned char sSerialNumber[HIK_SERIALNUM_LEN];
    unsigned long dwSoftwareVersion;
    unsigned long dwSoftwareBuildDate;
    unsigned long dwDSPSoftwareVersion;
    unsigned long dwDSPSoftwareBuildDate;
    unsigned long dwPanelVersion;
    unsigned long dwHardwareVersion;
    unsigned char byAlarmInPortNum;
    unsigned char byAlarmOutPortNum;
    unsigned char byRS232Num;
    unsigned char byRS485Num;
    unsigned char byNetworkPortNum;
    unsigned char byDiskCtrlNum;
    unsigned char byDiskNum;
    unsigned char byDVRType;
    unsigned char byChanNum;
    unsigned char byStartChan;
    unsigned char byDecordChans;
    unsigned char byVGANum;
    unsigned char byUSBNum;
    unsigned char byAuxoutNum;
    unsigned char byAudioNum;
    unsigned char byIPChanNum;
};

struct ViewSendData
{
	int channelNum;				//通道号
	int streamType;				//流类型 0-tcp,
};

struct HikTime
{
	unsigned long ulYear;		//年
	unsigned long ulMonth;		//月
	unsigned long ulDay;		//日
	unsigned long ulHour;		//时
	unsigned long ulMinute; 	//分
	unsigned long ulSecond;	 	//秒
};

struct HikFindFile
{
	int channelNum;				//通道号
	int fileType;					//文件类型
	int lockState;				//锁定状态
	int needCardNum;			//是否需要卡号
	char cardNum[20];			//卡号
	HikTime beginTime;		//开始时间
	HikTime endTime;			//结束时间
};

#define EXCHANGE						2	//交互命令, 每隔５秒给客户端发送命令
#define NEEDRECVFILEHEAD				19	//按时间回放时需要接收文件头
#define NEEDRECVDATA					20	//接收数据
#define BYTIME_ALLFILEEND				21	//按时间回放时全部文件放完
#define NEEDWAIT						25	//查找文件时需要等待
#define FILELISTOVER					26	//文件查找完毕
#define RECVFILEINFO					27	//接收文件信息

struct HikFindFileRet
{
	int length;
	int state;
};

struct HikFileInfo
{
	char sFileName[32];				/* 文件名 */
	time_t tStartTime;				/* 文件的开始时间 */
	time_t tStoptime;				/* 文件的结束时间 */
	unsigned long ulFileSize;		/* 文件的大小 */
	char sCardNum[32];					/*卡号信息*/
	unsigned char byLocked;			/*1 表示文件已经被锁定，0表示正常的文件*/
	unsigned char buRes[3];			/*保留*/
};

typedef struct HikPlayByFileRet
{
	unsigned int fileLength;			//文件长度
	unsigned int totleTime;				//文件总时间(秒)
	unsigned int totleFrame;			//文件总帧数
	unsigned int headLength;			//文件头长度
} HikPlayByTimeHead;

struct HikPlayByTime
{
	int channelNum;				//通道号
	HikTime beginTime;			//开始时间
	HikTime endTime;			//结束时间
};

struct HikPlayByTimeRet
{
	char totleLen[8];				//总长度,保留
	char reserve[16];				//保留
	unsigned int headLength;		//文件头长度
};

struct HikRecvFileHead
{
	unsigned int length;				//数据长度
	unsigned int state;					//接收状态
};

struct HikPtzData
{
	unsigned int channelNum;		//通道号
	unsigned int cmd;				//控制命令
	unsigned int param;				//参数
};

struct HikRecvAlarmHead
{
	unsigned int length;
	unsigned int state;
};

struct HikAlarmInfo
{
	unsigned long ulAlarmType;			/*0-信号量报警, 1-硬盘满, 2-信号丢失，3－移动侦测，4－硬盘未格式化,5-写硬盘出错,6-遮挡报警，7-制式不匹配, 8-非法访问*/
	unsigned long ulAlarmInputNumber;	/*按位,第0位对应第0个输入端口,dwAlarmType为0时需要设置*/
	unsigned long ulAlarmOutputNumber;	/*按位,第0位对应第0个输出端口, */
	unsigned long ulAlarmRelateChannel;	/*按位，第0位对应第0个通道*/
	unsigned long ulChannel;			/*按位,第0位对应第0个通道，dwAlarmType为2或3,6时需要设置*/
	unsigned long ulDiskNumber;			/*按位,第0位对应第0个硬盘,dwAlarmType为1,4,5时需要设置*/
};

#endif //~ __HikType_h_

