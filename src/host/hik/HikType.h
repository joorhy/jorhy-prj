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
#define 	HIK_CMD_LOGIN           0x010000
#define 	HIK_CMD_LOGINEX         0x010010
#define 	HIK_CMD_LOGOUT          0x010100
#define 	HIK_CMD_USEREXCHANGE    0x010200

#define 	HIK_CMD_GET_DEVCFG      0x020000
#define 	HIK_CMD_SET_DEVCFG      0x020001

#define	HIK_CMD_VIDEO_TCP			0x030000
#define	HIK_CMD_VIDEO_UDP			0x030001
#define	HIK_CMD_VIDEO_MCAST     0x030002
#define	HIK_CMD_VIDEO_RTP       0x030003
#define 	HIK_CMD_DATA_EXCHANGE   0x030006

#define 	HIK_CMD_AUDIO_GET_CFG   0x110044
#define 	HIK_CMD_AUDIO_START     0x030500

#define 	HIK_CMD_PTZ_CTRL                0x030200
#define 	HIK_CMD_PTZ_CTRL_WITH_SPEED     0x030203

#define 	HIK_CMD_START_RECORD_FILE   		0x030d00
#define 	HIK_CMD_STOP_RECORD_FILE    		0x030d01

#define 	HIK_CMD_MAIN_MAKE_IFRAME 		0x090100	 	
#define 	HIK_CMD_SUB_MAKE_IFRAME 			0x090101	 	

#define		HIK_CMD_FIND_FILE					0x030100		
#define		HIK_CMD_PLAYBYFILE				0x030101		
#define		HIK_CMD_PLAYBYTIME				0x030102		
#define 	HIK_CMD_FILE_EXCHANGE			0x030109	
#define 	HIK_CMD_FIND_FILE_V3				0x111040		

#define		HIK_CMD_STARTPLAY				0x030103		
#define		HIK_CMD_SETPOS					0x030105		
#define		HIK_CMD_PAUSE					0x030107		
#define		HIK_CMD_RESTART				0x030108		
#define 	HIK_CMD_SETSPEED 	      	0x03010d    

/*建立报警上传通道*/
#define 	HIK_CMD_ALARMCHAN				0x030400		
#define 	HIK_CMD_ALARMCHAN_V30			0x111020	 
/*
 Hik Ptz sub command
 */
#define 	HIK_PTZ_PRESET_SET      8
#define 	HIK_PTZ_PRESET_CLR      9
#define 	HIK_PTZ_PRESET_MOV      39

#define 	HIK_PTZ_MOVE_UP             21
#define 	HIK_PTZ_MOVE_DOWN           22
#define 	HIK_PTZ_MOVE_LEFT           23
#define 	HIK_PTZ_MOVE_RIGHT          24
#define 	HIK_PTZ_MOVE_UP_LEFT        25
#define 	HIK_PTZ_MOVE_UP_RIGHT       26
#define 	HIK_PTZ_MOVE_DOWN_LEFT      27
#define 	HIK_PTZ_MOVE_DOWN_RIGHT     28

#define 	HIK_PTZ_ZOOM_IN             11
#define 	HIK_PTZ_ZOOM_OUT            12
#define 	HIK_PTZ_FOCUS_NEAR          13
#define 	HIK_PTZ_FOCUS_FAR           14
#define 	HIK_PTZ_IRIS_OPEN       	 15  	
#define 	HIK_PTZ_IRIS_CLOSE      	 16  	
/*
 values
 */
#define 	THIS_SDK_VERSION        NETSDK_VERSION_V10
#define 	HIK_SERIALNUM_LEN       48
#define 	HIK_NAME_LEN            32
#define 	HIK_MAX_LINK            6

/*
 returned code
 */
#define 	HIK_RET_OK              1
#define 	HIK_NO_SUPPORT			   13		
#define 	HIK_ERROR_DATA				14		
#define 	HIK_INVALID_ID          30		

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
	int channelNum;		
	int streamType;				
};

struct HikTime
{
	unsigned long ulYear;		
	unsigned long ulMonth;		
	unsigned long ulDay;			
	unsigned long ulHour;		
	unsigned long ulMinute; 	
	unsigned long ulSecond;	 	
};

struct HikFindFile
{
	int channelNum;				
	int fileType;					
	int lockState;					
	int needCardNum;				
	char cardNum[20];				
	HikTime beginTime;			
	HikTime endTime;				
};

#define EXCHANGE						2	
#define NEEDRECVFILEHEAD			19	
#define NEEDRECVDATA					20	
#define BYTIME_ALLFILEEND			21	
#define NEEDWAIT						25	
#define FILELISTOVER					26	
#define RECVFILEINFO					27	

struct HikFindFileRet
{
	int length;
	int state;
};

struct HikFileInfo
{
	char sFileName[32];				/* 文件名 */
	time_t tStartTime;				/* 文件的开始时间 */
	time_t tStoptime;					/* 文件的结束时间 */
	unsigned long ulFileSize;		/* 文件的大小 */
	char sCardNum[32];				/*卡号信息*/
	unsigned char byLocked;			/*1 表示文件已经被锁定，0表示正常的文件*/
	unsigned char buRes[3];			/*保留*/
};

typedef struct HikPlayByFileRet
{
	unsigned int fileLength;			
	unsigned int totleTime;				
	unsigned int totleFrame;			
	unsigned int headLength;		
} HikPlayByTimeHead;

struct HikPlayByTime
{
	int channelNum;			
	HikTime beginTime;		
	HikTime endTime;		
};

struct HikPlayByTimeRet
{
	char totleLen[8];	
	char reserve[16];		
	unsigned int headLength;	
};

struct HikRecvFileHead
{
	unsigned int length;				
	unsigned int state;			
};

struct HikPtzData
{
	unsigned int channelNum;	
	unsigned int cmd;					
	unsigned int param;				
};

struct HikRecvAlarmHead
{
	unsigned int length;
	unsigned int state;
};

struct HikAlarmInfo
{
	unsigned long ulAlarmType;				
	unsigned long ulAlarmInputNumber;	
	unsigned long ulAlarmOutputNumber;	
	unsigned long ulAlarmRelateChannel;	
	unsigned long ulChannel;				
	unsigned long ulDiskNumber;			
};

///语音对讲
#define 	HIK_GET_COMPRESSCFG_ADX			0x110042		
#define 	HIK_SET_COMPRESSCFG_ADX			0x110043		
#define	HIK_GET_COMPRESSCFG_AUD_EX		0x110044		
#define	HIK_START_VOICECOM				0x030500	
#define 	HIK_START_VOICECOM_V30			0x111030		

struct HikReserve4
{
	char reserve[4];
};

struct HikRecvVoiceHead
{
	unsigned int length;				
	unsigned int state;				
};

#endif //~ __HikType_h_