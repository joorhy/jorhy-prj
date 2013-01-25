#ifndef __TMTRANSEDEFINE_H__
#define __TMTRANSEDEFINE_H__

#define IP_LEN					24
#define NAME_LEN 				32
#define SERIALNO_LEN 			48
#define MACADDR_LEN 			6
#define MAX_ETHERNET 			2
#define PATHNAME_LEN 			128
#define PASSWD_LEN 				32
#define MAX_CHANNUM 			64
#define MAX_ALARMOUT 			64
#define MAX_TIMESEGMENT			4
#define MAX_PRESET				16
#define MAX_DAYS 				7
#define MAX_WEEKNAME			20
#define PHONENUMBER_LEN			32
#define MAX_DISKNUM 			16
#define MAX_WINDOW 				16
#define MAX_VGA 				1
#define MAX_USERNUM 			16
#define MAX_EXCEPTIONNUM		16
#define MAX_LINK 				6
#define MAX_ALARMIN 			64
#define MAX_VIDEOOUT 			4
#define MAX_NAMELEN				16
#define MAX_RIGHT				64
#define CARDNUM_LEN 			20
#define DECODER_NAME_LEN		20
#define MAX_MOTIONAREANUM		5
#define MAX_SERIALTRANS_LEN		128
#define MAX_CIRCLE_NUM			32
#define MAX_NTP_SERVERS			3
#define MAX_RS232NUM			6
#define CRUISE_MAX_LINE_NUMS	8
#define MAX_ALARMDEVICE			6
#define MAX_CIRCLECONNECTNUM	32
#define MAX_WINDOWNUM 			16

#define NET_IF_10M_HALF			1
#define NET_IF_10M_FULL			2
#define NET_IF_100M_HALF		3
#define NET_IF_100M_FULL		4
#define NET_IF_AUTO				5

#define DVS								3
#define DEC								4
#define HD_DEC							5
#define HD_NVR							6
#define HD_STORAGE						7
#define HD_TURN							8
#define HD_TVWALL						9
#define DVS_IPCAMERA					12
#define HD_IPCAMERA 					13
#define HD_IPCAMERA1 					14
#define HD_IPCAMERA2 					15
#define HD_IPCAMERA3 					16
#define HD_IPCAMERA4 					17
#define HD_NVS							21
#define HD_NVS1							22
#define	HD_SC110_CAM					23
#define ANALOG_CAM						31

#define HD_IPCAMERA_1M 					32
#define HD_IPCAMERA_2M 					33
#define HD_IPCAMERA_3M 					34
#define HD_IPCAMERA_5M 					35
#define HD_IPCAMERA_2M18				36
#define HD_IPCAMERA_2M16				37
#define HD_IPCAMERA_2M22				38
#define HD_IPCAMERA_D1					39
#define HD_IP38x38_2M					40
#define HD_IP38x38_1M					41
#define HD_IP38x38_D1					42
#define HD_IPCAMERA_2M1M				43
#define HD_IPCAMERA_2M1M16				44
#define HD_IPCAMERA_2M1M18				45
#define HD_IPCAMERA_2M1M22				46
#define HD_IPCAMERA_SAFE				47
#define HD_IPCAMERA_2MINTELLIGENT		48

typedef struct tmUserInfo_t
{
	unsigned int	dwSize;
	char			szUserName[32];
	char			szPassword[32];
	char			szMotifyPassword[32];
	unsigned short	wRemoteLevel;
	unsigned short	wRemoteLoginNum;
	unsigned int	dwRemoteRightHi;
	unsigned int	dwRemoteRightLo;
	unsigned int	dwUserIP;
	unsigned char	byMACAddr[6];
}tmUserInfo_t;

typedef struct tmUser_t
{
	unsigned int	dwSize;
	int				iUserCount;
	tmUserInfo_t	struUserInfo[16];
}tmUser_t;

typedef struct tmDeviceCfg_t
{
	unsigned int	dwSize;
	char			sDVSName[32];
	unsigned int	dwDVSID;
	unsigned int	dwRecycleRecord;
	unsigned int	dwVideoStandard;
	unsigned int	dwMicrophone;

	char			szSerialNumber[48];
	unsigned int	dwSoftwareVersion;
	unsigned int	dwSoftwareBuildDate;
	unsigned int	dwDSPSoftwareVersion;
	unsigned int	dwDSPSoftwareBuildDate;
	unsigned int	dwPanelVersion;
	unsigned int	dwHardwareVersion;
	unsigned char	byAlarmInPortNum;
	unsigned char	byAlarmOutPortNum;
	unsigned char	byRS232Num;
	unsigned char	byRS485Num;
	unsigned char	byNetworkPortNum;
	unsigned char	byDiskCtrlNum;
	unsigned char	byDiskNum;
	unsigned char	byDVSType;
	unsigned char	byChanNum;
	unsigned char	byStartChan;
	unsigned char	byDecordChans;
	unsigned char	byVGANum;
	unsigned char	byUSBNum;
	unsigned char	byFactory;
	union
	{
		unsigned short  wDeviceExternType;
		unsigned short	wAvFactory;
	}_TypeExtern;
	unsigned short	wAvPort;
}tmDeviceCfg_t;


typedef struct tmEthernet_t
{
	unsigned int	dwSize;
	char			sDVSIP[24];
	unsigned char	byDVSIPType;
	char			sDVSIPMask[24];
	unsigned char	byDVSIPMaskType;
	unsigned short	wDHCP;
	unsigned int	dwNetInterface;
	unsigned short	wDVSPort;
	unsigned short	wHttpPort;
	unsigned char	byMACAddr[6];
	unsigned char	byInitNetInterface;
	unsigned char	byReserves;
}tmEthernet_t;

typedef struct tmDDNS_t
{
	unsigned int		dwSize;
	char				sDDNSServerName[32];
	char				sDDNSServerName2[32];
	char				sDDNSName[32];
	char				sDDNSUser[32];
	char				sDDNSPassword[32];
}tmDDNS_t;

typedef struct tmNetCfg_t
{
	unsigned int		dwSize;
	tmEthernet_t		struEtherNet[2];
	char				sManageHostIP[24];
	unsigned char		bytemp1[2];
	unsigned short		wManageHostPort;
	unsigned int		dwManageHost;

	unsigned int		dwSyncTimeFromManageHost;

	char				sDNSIP[24];
	unsigned char		byTemp2;
	char				sDNSIP2[24];
	unsigned char		byTemp3;
	char				sMultiCastIP[24];
	unsigned char		byTemp4;
	char				sGatewayIP[24];
	unsigned char		byTemp5;
	
	char				sNFSIP[24];
	unsigned char		byTemp6;
	char				sNFSDirectory[128];

	unsigned int		dwPPPOE;
	char				sPPPoEUser[32];
	char				sPPPoEPassword[32];
	char				sPPPoEIP[24];
	unsigned char		byTemp7[4];

	unsigned int		dwDDNS;
	tmDDNS_t			struDDNS;

	char				sManaeHostUser[32];
	char				sManaeHostPassword[32];
	
	unsigned int		dwEnableRtsp;
	unsigned short		wRtspPort;
	unsigned short		wRtspMode;
	char				sMajorStream[32];
	char				sMinorStream[32];
}tmNetCfg_t;

typedef struct tagtmWifiCfg_t
{
	unsigned int		dwSize;
	unsigned char		byEnable;
	unsigned char		byDhcp;
	
	char				sIpAddr[16];
	char				sIpMaskAddr[16];
	char				sGatewayIP[16];
	char				sDNSIP1[16];
	char				sDNSIP2[16];
	
	char				sSsid[48];
	char				sKey[48];
	unsigned char		byKeyMgmt;
	unsigned char		byKeyType;
	unsigned char		byKeyIndex;
	unsigned char		byScanSsid;
	unsigned int		dwWpaPtkRekey;

	BYTE				byMACAddr[6];

	unsigned char		byKeyFormat;
	unsigned char		byTemp[3];
}tmWifiCfg_t;

typedef struct tmDDNSCfg_t
{
	unsigned int		dwSize;
	unsigned char		byDDNSEnable;
	unsigned char		byTemp[3];
	char				sDDNSServerName[32];
	char				sDDNSServerName2[32];
	char				sDDNSName[32];
	char				sDDNSUser[32];
	char				sDDNSPassword[32];
}tmDDNSCfg_t;

typedef struct tmNTPCfg_t
{
	unsigned int	dwSize;
	unsigned int	dwCount;
	unsigned int	dwIdx;		
	char			strNTPServer[MAX_NTP_SERVERS][PATHNAME_LEN];	
}tmNTPCfg_t;

typedef struct tmNTPCfgEx_t
{
	unsigned int	dwSize;
	unsigned int	dwEnableNtp;
	unsigned int	dwNtpTime;		
	char			strNTPServer[128];	
}tmNTPCfgEx_t;

typedef struct tmFTPCfg_t
{
	unsigned int	dwSize;	
	unsigned char	byUseFTP;
	char			strFTPServerIpAddr[128];
	unsigned char	byRecordStreamId;
	unsigned char	byRecordFormat;
	unsigned char	byEnableDirectory;
	unsigned int	dwServerPort;
	char			strFTPCliUserName[16];
	char			strFTPCliUserPass[16];
	unsigned int	dwFTPRecordFileSize;
	char			strDirectoryName[128];
}tmFTPCfg_t;

typedef struct tmSMTPCfg_t
{
	unsigned int	dwSize;	
	unsigned char	byUseSMTP;
	char			strSMTPServerIpAddr[128];
	unsigned char	byReserves[3];
	char			strSMTPCliUserName[16];
	char			strSMTPCliUserPass[16];
}tmSMTPCfg_t;

typedef struct tmLiveHeartCfg_t
{
	unsigned int		dwSize;
	unsigned char		byEnableLiveHeart;
	unsigned char		byLiveHeartMode;
	unsigned short		wLiveTime;
	char				sServerAddress[32];
	unsigned int		dwServerPort;
}tmLiveHeartCfg_t;

typedef struct tmStreamUpToServerCfg_t
{
	unsigned short		dwSize;
	unsigned char		byEnable;
	unsigned char		byTemp;
	char				sServerAddress[64];
	unsigned short		wControlPort;
	unsigned short		wStreamPort;
	unsigned short		wTalkPort;
	unsigned short		wTemp;
	char				sDeviceNumber[32];
}tmStreamUpToServerCfg_t;

//////////////////////////////////////////////////////////////////////////
typedef struct tmTimeCfg_t
{
	unsigned int	dwSize;
	unsigned short	wYear;
	unsigned short	wMonth;
	unsigned short	wDay;
	unsigned short	wDayOfWeek;
	unsigned short	wHour;
	unsigned short	wMinute;
	unsigned short	wSecond;
	short			wTimeZone;
	int				iDayLightTime;
}tmTimeCfg_t;

typedef struct tmTimeInfo_t
{
	unsigned short	wYear;			//��
	unsigned char	byMonth;		//��
	unsigned char	byDay;			//��
	unsigned char	byHour;			//ʱ
	unsigned char	byMinute;		//��
	unsigned char	bySecond;		//��
	unsigned char	byTemp;			//����
	unsigned int	dwMicroSecond;	//����	
}tmTimeInfo_t;

/* ʱ�䷶Χ */
typedef struct tmSchedTime_t
{
	unsigned int	dwSize;
	//��ʼʱ��
    unsigned char	byStartHour;
	unsigned char	byStartMin;
	//����ʱ��
	unsigned char	byStopHour;
	unsigned char	byStopMin;
}tmSchedTime_t;

/* �������?ʽ*/
#define NOACTION			0x00				/*����Ӧ*/
#define WARNONMONITOR		0x01				/*�������Ͼ���*/
#define WARNONAUDIOOUT		0x02				/*��������*/
#define UPTOCENTER			0x04				/*�ϴ�����*/
#define TRIGGERALARMOUT		0x08				/*�����������*/
#define UPTOCTRLCLIENT		0x10				/*�ϴ����ƿͻ���*/
#define UPTOAVCLIENT		0x20				/*�ϴ�����Ƶ�ͻ���*/
typedef struct tmHandleException_t
{
	unsigned char		byRelAlarmOutEnable[4];	/* �������������ЧbyRelAlarmOutEnable[0]Ϊ12�򱨾����0-3 */
	unsigned int		dwHandleType;			/*���?ʽ,���?ʽ��"��"���*/
	unsigned char		byRelAlarmOut[4];		//�������������ͨ��,�������������,Ϊ1��ʾ���������
}tmHandleException_t;


/* �������?�� */
typedef struct tmTransFer_t
{
	//ȡ��ṹ��С����
	unsigned char	byTransFerType;			/* ������������12ΪtmTransFer_tΪͨ������0-16, 13Ϊͨ����byChannel����*/
	unsigned char	byChannel;				/* ͨ����0-MAX_CHANNUM */
	unsigned char	byTemp[2];				/* ���� */
	unsigned char	byEnableRelRecordChan;	/* ����������¼��ͨ��,Ϊ1��ʾ������ͨ�� */
	unsigned char	byEnablePreset;			/* �Ƿ����Ԥ�õ� */
	unsigned char	byPresetNo;				/* ���õ���̨Ԥ�õ����,һ������������Ե��ö��ͨ������̨Ԥ�õ�*/
	unsigned char	byEnableCruise;			/* �Ƿ����Ѳ�� */
	unsigned char	byCruiseNo;				/* Ѳ�� */
	unsigned char	byEnablePtzTrack;		/* �Ƿ���ù켣 */
	unsigned char	byPTZTrack;				/* ���õ���̨�Ĺ켣��� */
	unsigned char	byEnableCaptureChan;	/* ����������ץͼͨ����Ϊ1��ʾ������ͨ�� */
}tmTransFer_t;

/* ͨ��ͼ��ṹ, �����壬������704*576 */
typedef struct tmAreaScope_t
{
	unsigned short	wAreaTopLeftX;		/* �����x��� */
	unsigned short	wAreaTopLeftY;		/* �����y��� */
	unsigned short	wAreaWidth;			/* ����Ŀ� */
	unsigned short	wAreaHeight;		/* ����ĸ� */
}tmAreaScope_t;
/* �ƶ���� */
typedef struct tmMotion_t
{
	unsigned int			dwSize;	
	unsigned char			byMotionScopeNum;							/*�������������С�ڻ����5*/
	tmAreaScope_t			struMotionScope[5];							/*�������704*576*/
	unsigned char			byMotionSensitive;							/*�ƶ����������, 0 - 5,Խ��Խ����*/
	unsigned char			byMotionThreshold;							/*�ƶ���ֵⷧ��Ϊ�����ƶ�����ĺ������ٷֱȣ�0-100����Ϊ0ʱֻҪ��һ������ƶ������ƶ�*/
																		/*��ԽСԽ����*/
	unsigned char			byEnableHandleMotion;						/*�Ƿ����ƶ����*/ 
	tmHandleException_t		strMotionHandleType;						/*���?ʽ*/
	tmSchedTime_t			struAlarmTime[7][4];						//����ʱ��
	tmTransFer_t			struAlarmTransFer[16];						//����ͨ��
}tmMotion_t;

/* �ƶ���� */
typedef struct tmVideoMotionCfg_t
{
	unsigned int			dwSize;	
	tmAreaScope_t			struMotionScope[5];							/*�������704*576*/
	unsigned char			byMotionScopeNum;							/*�������������С�ڻ����5*/	
	unsigned char			byMotionSensitive;							/*�ƶ����������, 0 - 5,Խ��Խ����*/
	unsigned char			byMotionThreshold;							/*�ƶ���ֵⷧ��Ϊ�����ƶ�����ĺ������ٷֱȣ�0-100����Ϊ0ʱֻҪ��һ������ƶ������ƶ�*/																		/*��ԽСԽ����*/
	unsigned char			byEnableHandleMotion;						/*�Ƿ����ƶ����*/ 
	tmHandleException_t		strMotionHandleType;						/*���?ʽ*/
	tmSchedTime_t			struAlarmTime[7][4];						//����ʱ��
	tmTransFer_t			struAlarmTransFer[16];						//����ͨ��
}tmVideoMotionCfg_t;

/* �ڵ���������Ϊ704*576 */
typedef struct tmHideAlarm_t
{
	unsigned int			dwSize;
	unsigned char			byHideSensitive;			/* �ڵ������� ,0 - 5,Խ��Խ���� */
	tmAreaScope_t			struHideAlarmArea;			/* �ڵ����� */
	unsigned char			byEnableHandleHideAlarm;	/* �Ƿ����źŶ�ʧ���� */ 
	tmHandleException_t		strHideAlarmHandleType;		/* ���?ʽ */
	tmSchedTime_t			struAlarmTime[7][4];		/* ����ʱ�� */
}tmHideAlarm_t;
/* �ڵ�����������չΪ704*576 */
typedef struct tmVideoHideCfg_t
{
	unsigned int			dwSize;
	tmAreaScope_t			struHideAlarmArea;			/* �ڵ����� */
	unsigned char			byHideSensitive;			/* �ڵ������� ,0 - 5,Խ��Խ���� */
	unsigned char			byEnableHandleHideAlarm;	/* �Ƿ����źŶ�ʧ���� */ 
	unsigned char			byTemp[2];
	tmHandleException_t		strHideAlarmHandleType;		/* ���?ʽ */
	tmSchedTime_t			struAlarmTime[7][4];		/* ����ʱ�� */
}tmVideoHideCfg_t;

/* �źŶ�ʧ���� */
typedef struct tmViLost_t
{
	unsigned int			dwSize;
	unsigned char			byEnableHandleVILost;		/* �Ƿ����źŶ�ʧ���� */ 
	tmHandleException_t		strVILostHandleType;		/* ���?ʽ */
	tmSchedTime_t			struAlarmTime[7][4];		/* ����ʱ�� */
}tmViLost_t;

/* �źŶ�ʧ������չ */
typedef struct tmVideoLostCfg_t
{
	unsigned int			dwSize;
	unsigned char			byEnableHandle;				/* �Ƿ����źŶ�ʧ���� */ 
	unsigned char			byTemp[3];
	tmHandleException_t		strHandleType;				/* ���?ʽ */
	tmSchedTime_t			struAlarmTime[7][4];		/* ����ʱ�� */
}tmVideoLostCfg_t;

/* ��Ƶ�ڵ����� */
typedef struct tmVideoMaskCfg_t
{
	unsigned int			dwSize;
	unsigned char			byEnableMask;				/* �Ƿ������ڵ� ,0-��,1-�� ����Ϊ704*576*/
	unsigned char			byTemp[3];
	tmAreaScope_t			struHideArea[4];			/*�ڵ�����*/
}tmVideoMaskCfg_t;

/* ͼ��Ԥ������ */
typedef struct tmPicPreviewCfg_t
{
	unsigned int			dwSize;
	unsigned int			dwVideoFormat;				/*ֻ������Ƶ��ʽ 0-PAL 1-NTSC*/
	short					byBrightness;  				/*����,0-255*/
	short					byContrast;    				/*�Աȶ�,0-255*/	
	short					bySaturation;  				/*���Ͷ�,0-255 */
	short					byHue;    					/*ɫ��,0-255*/
	short					byAcutance;					/*���,0-255*/   
}tmPicPreviewCfg_t;

/* ͼ��Ԥ������ */
typedef struct tmPicPreviewInfo_t
{
	/*����,0-255*/
	unsigned char	byBrightness;
	/*�Աȶ�,0-255*/
	unsigned char	byContrast;
	/*���Ͷ�,0-255 */
	unsigned char	bySaturation;
  	/*ɫ��,0-255*/
	unsigned char	byHue;
}tmPicPreviewInfo_t;

/*ͼ��ģʽԤ��ƻ�*/
typedef struct tagPicModeScheduleInfo_t
{
	//ʱ�����Ϣ����ʼʱ
	unsigned char		byStartHour;      
	unsigned char		byStartMin;
	unsigned char		byStopHour;
	unsigned char		byStopMin;
	
	//�Ƿ����ñ�־: 0-������; 1-����
	unsigned char		byEnable;         
	//��Ƶģʽ����: 0-����ģʽ; 1-ǿ��ģʽ; 2-����ģʽ; 3-ҹ��ģʽ
	unsigned char		byMode;  
	//��չ�����(0-255)
	unsigned char		byAcutance;
	//����
	unsigned char		byReverse[1];     
}tmPicModeScheduleInfo_t;

typedef struct tagPicModeScheduleCfg_t
{
	unsigned int				dwSize ;
	//ͼ��ģʽ:0-����ģʽ; 1-ǿ��ģʽ; 2-����ģʽ; 3-ҹ��ģʽ
	tmPicPreviewInfo_t			struMode[4];                  
	//����0��1��2.3�ֱ����ĸ�ʱ���
	tmPicModeScheduleInfo_t     struModeSched[4];   
	
}tmPicModeScheduleCfg_t;

/*��ͼ��ɼ�ƫ��΢������ */
typedef struct tmVideoOffsetCfg_t
{
	unsigned int	dwSize;	

	unsigned char	byClearLeft;
	unsigned char	byClearTop;
	unsigned char	byClearRight;
	unsigned char	byClearBottom;

	short			offset_x;
	short			offset_y;
	short			offset_cx;
	short			offset_cy;
}tmVideoOffsetCfg_t;

/* ͼ��OSD�������� */
typedef struct tmVideoOsdCfg_t
{
	unsigned int			dwSize;

	char					sChanName[64];				/* ͨ���� */
	unsigned short			wShowNameTopLeftX;			/* ͨ�������ʾλ�õ�x��� */
	unsigned short			wShowNameTopLeftY;			/* ͨ�������ʾλ�õ�y��� */
	unsigned char			byShowChanName;				/* Ԥ����ͼ�����Ƿ���ʾͨ�����,0-����ʾ,1-��ʾ ����Ϊ704*576 */
	unsigned char			byNameCoordinateMode;		/* ���ģʽͨ��ģʽ*/
														/* 0-������Ͻǣ�1-������Ͻǣ�2-������½ǣ�3-������½�*/

	unsigned short			wShowTimeTopLeftX;			/* OSD��x��� */
	unsigned short			wShowTimeTopLeftY;			/* OSD��y��� */
	unsigned char			byShowTime;					/* Ԥ����ͼ�����Ƿ���ʾOSD,0-����ʾ,1-��ʾ*/
	unsigned char			byTimeType;					/* OSD����(��Ҫ�������ո�ʽ) */
														/* 0: xxxx/xx/xx xx:xx:xx ��/��/�� ʱ����*/
														/* 1: xx/xx/xxxx xx:xx:xx ��/��/�� ʱ����*/
														/* 2: xx:xx:xx ʱ����*/
														/* 3: xxxx-xx-xx xx:xx:xx ��-��-�� ʱ����*/
														/* 4: xx-xx-xxxx xx:xx:xx ��-��-�� ʱ����*/
	unsigned char			byShowWeek;					/* �Ƿ���ʾ���� */	
	unsigned char			byWeekType;					/* ��������0-���ģ�1-Ӣ�� */
	unsigned char			byTimeCoordinateMode;		/* ���ģʽʱ��ģʽ*/

	unsigned char			byOsdAttrib;				/* OSD����: */
														/* 0: ��͸�� */	
														/* 1: ��͸�� */	
														/* 2: ��͸������ */	
	unsigned char			byFontMode;					/* OSD������ģʽ0-Ĭ��ģʽ��1-�Ŵ�ģʽ */
	unsigned char			byAlignMode;				/* �ַ�������\n��������ʾ��ͷ�����뷽ʽ,0-�Ҷ��룬1-�м䣬2-�����*/
	unsigned char			byTemp[2];

	//��չ��ʾ�ı���
	char					sShowText[256];				/* ��չ�ı��� */
	unsigned short			wShowTextTopLeftX;			/* ��չ�ı�����ʾλ�õ�x��� */
	unsigned short			wShowTextTopLeftY;			/* ��չ�ı�����ʾλ�õ�y��� */
	unsigned char			byShowText;					/* Ԥ����ͼ�����Ƿ���ʾ��չ�ı���,0-����ʾ,1-��ʾ ����Ϊ704*576 */
	unsigned char			byTextCoordinateMode;		/* ���ģʽ*/
														/* 0-������Ͻǣ�1-������Ͻǣ�2-������½ǣ�3-������½�*/

}tmVideoOsdCfg_t;

/* ͼ����� */
typedef struct tmPicCfg_t
{
	unsigned int			dwSize;
	char					sChanName[32];
	unsigned int			dwVideoFormat;				/* ֻ������Ƶ��ʽ 0-PAL 1-NTSC*/

	//��ʾͨ����
	unsigned int			dwShowChanName;				/* Ԥ����ͼ�����Ƿ���ʾͨ�����,0-����ʾ,1-��ʾ ����Ϊ704*576 */
	unsigned short			wShowNameTopLeftX;			/* ͨ�������ʾλ�õ�x��� */
	unsigned short			wShowNameTopLeftY;			/* ͨ�������ʾλ�õ�y��� */
	unsigned char			byShowNamAttrib;			/* �������:͸�� */

	//�źŶ�ʧ����
	tmViLost_t				struVILost;
	//�ƶ����
	tmMotion_t				struMotion;	
	//�ڵ�����
	tmHideAlarm_t			struHideAlarm;
	//�ڵ�
	unsigned char			dwEnableHide;				/* �Ƿ������ڵ� ,0-��,1-�� ����Ϊ704*576*/
	tmAreaScope_t			struHideArea;				/*�ڵ�����*/

	unsigned int			dwShowOsd;					/* Ԥ����ͼ�����Ƿ���ʾOSD,0-����ʾ,1-��ʾ*/
	unsigned short			wOSDTopLeftX;				/* OSD��x��� */
	unsigned short			wOSDTopLeftY;				/* OSD��y��� */
	unsigned char			byOSDType;					/* OSD����(��Ҫ�������ո�ʽ) */
												/* 0: xxxx/xx/xx xx:xx:xx ������ ʱ����*/
												/* 1: xx/xx/xxxx xx:xx:xx ������ ʱ����*/
												/* 2: xx:xx:xx ʱ����*/
	unsigned char			byDispWeek;					/* �Ƿ���ʾ���� */	
	unsigned char			byOSDAttrib;				/* OSD����:͸�� */
												/* 0: ��͸�� */	
												/* 1: ��͸�� */	
	char					sWeekName[7][20];			//������ƣ�0Ϊ����һ��6Ϊ������

	unsigned char			byEnableStreamNum;			/*�Ƿ�֧��˫������0-��������1-˫�������˲��������NVSӲ������*/
}tmPicCfg_t;

//ѹ������
typedef struct tmCompression_t
{
	//�˽ṹֵ�޸�Ϊ�����ʽ��Ϊ�˱���һ�´�ֵ����Ϊ16
	//unsigned int	dwSize;
	//��Ƶ�����ʽ��0-BKMPEG4,1-H264,2-MJPEG,10-YPbPr,11-cvbs,12-hdmi,13-Digital
	unsigned char		byCompressFormat;

	//�ؼ�֡��� : 0x00 ��ʾʹ��Ĭ�ϣ�0xFF ��ʾȫ�ؼ�֡;����ֵ��ʾ�ؼ�֡֡���
	unsigned char		byKeyFrameInterval;

	//���õ�ȫ֡ʱ��ʾ��֡��
	unsigned char		byDisplayFrame;
	//����
	unsigned char		byTemp[1];

	//��������0-��Ƶ��,1-������
	unsigned char		byStreamType;

	//�ֱ���
	//0-CIF(352x288) 1-QCIF(176x144), 2-2CIF(704x288), 3-4CIF(704x576), 
	//4-QQCIF(88x72), 5-DCIF(512x384), 6-VGA(640x480), 7-QDICF(256x192), 8-QVGA(320x240),
	//9-800x600, 10-1024x768 11-1280x720, 12-D1(720x576),
	//13-1600x1200, 14-1440x1080, 15-1920x1080, 16-1280x1024, 17-1280x960
	//18-1920x1200, 19-2048x1152, 20-2048x1536, 21-2560x1440, 22-2592x1944
	//23-960x576
	unsigned char		byResolution;

	//��������0:������, 1:������, 2:������
	unsigned char		byBitrateType;

	//ͼ������ 0-��� 1-�κ� 2-�Ϻ� 3-һ�� 4-�ϲ� 5-�� 6-���	
	unsigned char		byPicQuality;

	//��Ƶ���� 0-���� 1-���� 2-32K 3-48k 4-64K 5-80K 6-96K 7-128K 8-160k 9-192K 10-224K 11-256K 12-320K
	// 13-384K 14-448K 15-512K 16-640K 17-768K 18-896K 19-1024K 20-1280K 21-1536K 22-1792K 23-2048K
	//���λ(32λ)�ó�1��ʾ���Զ�������, 0-31λ��ʾ����ֵ(MIN-16K MAX-8192K)��
	unsigned int		dwVideoBitrate; 

	//֡�� 0-ȫ��; 1-1/16; 2-1/8; 3-1/4; 4-1/2; 5-1; 6-2; 7-4; 8-6; 9-8; 10-10; 11-12; 12-16; 13-20;
	//��չ 14-1/15; 15-1/14: 16-1/13; 17-1/12; 18-1/11; 19-1/10; 20-1/9; 21-1/7; 22-1/6; 23-1/5; 24-1/3;
	unsigned int		dwVideoFrameRate;

}tmCompression_t;

typedef struct tmCompressionCfg_t
{
	unsigned int			dwSize;
	//¼����������
	tmCompression_t			struRecordPara;		
	//���紫������������
	tmCompression_t			struNetPara;
	//��3����������
	tmCompression_t			struThirdPara;
	//��ϱ����ʽ����������µı��뷽ʽ��������Ϊ0
	unsigned char			byFormatId;
	//����
	unsigned char			byTemp[3];
}tmCompressionCfg_t;

//������Ϣ
typedef struct tmStreamDescription_t
{
	unsigned char			byResolution;			//ͼ���С��ʽ����
	unsigned char			byFormat;				//�����ʽ
	unsigned char			byFrameRateNum;			//֡���б���
	unsigned char			byType;					//��������0-ѹ�����룬1-���ֻ�ģ�����
	unsigned char			byFramesRateList[32];	//֡���б�
	unsigned int			dwMaxBitRate;			//��������
	unsigned int			dwDisplayRatio;			//��ʾ����ȷ����*1000
}tmStreamDescription_t;

//����������ѯ
typedef struct tmCompressCapability_t
{
	char					sName[64];			//�����ʽ���,��1080P(H264) + D1(H264)
	unsigned char			byFormatId;			//�����ʽ
	unsigned char			byStreamCount;		//������
	unsigned char			byTemp[2];
	tmStreamDescription_t	struStreamFormat[4];//�����ı����ʽ
}tmCompressCapability_t;

typedef struct tmCompressCapabilityCfg_t
{
	unsigned int			dwSize;				//���ṹ��С
	unsigned int			dwCount;			//֧�ֵ�ѹ����ʽ��
	tmCompressCapability_t	struCapability[1];	//��ϱ����б?���������Զ���һ��
}tmCompressCapabilityCfg_t;

//��Ƶѹ�������ýṹ������������������ϵͳ������ͨ��
typedef struct tmAudioCfg_t
{
	//���ṹ��С
	unsigned int		dwSize;
	//��Ƶ�����ʽ��//0-MP2,1-AAC,2-MULAW/G.711,3-ALAW/G.711,4-G.721,4-G.722,5-G.723,10-G.7231,6-G.726,8-S16LE,9-G.721,10-G.7231
	unsigned char		byCompressFormat;
	//Ҫ����Ƶ�����0-�������1-�������2-������
	unsigned char		byChannelMode;
	//��Ƶѹ������Ĭ��0-Ĭ��,1-16K,2-24K,3-32K,4-40K,5-48K,6-56K,7-64K,8-128K,9-256K
	unsigned char		byBitRate;
	//��Ƶ������0-Ĭ��, 1-8000Hz, 2-16000Hz, 3-22050Hz, 4-44100Hz, 5-48000Hz
	unsigned char		bySamplesRate;
	//��Ƶ�Ŵ���*100,��1��ʾ0.01,100��ʾ1
	unsigned int		dwLampFactor;
}tmAudioCfg_t;
//��Ƶ�����ʽ�б�
#define TMCC_AUDIO_ENCTYPE_MP2		0x00
#define TMCC_AUDIO_ENCTYPE_AAC		0x01
#define TMCC_AUDIO_ENCTYPE_MULAW	0x02
#define TMCC_AUDIO_ENCTYPE_ALAW		0x03
#define TMCC_AUDIO_ENCTYPE_G721		0x04
#define TMCC_AUDIO_ENCTYPE_G722		0x05
#define TMCC_AUDIO_ENCTYPE_G723_24	0x06
#define TMCC_AUDIO_ENCTYPE_G723_40	0x07
#define TMCC_AUDIO_ENCTYPE_G726		0x08
#define TMCC_AUDIO_ENCTYPE_G729		0x09
#define TMCC_AUDIO_ENCTYPE_S16LE	0x0A


//�����ץ�Ķ���
typedef struct tmCaptureImageCfg_t
{
	//���ṹ��С
	unsigned int		dwSize;
	//ͼ���ʽ��0-BMP, 1-JPEG, 2-H264, 3-YUVĿǰ����ֻ����1
	unsigned char		byFormat;
	//ץͼ���λ��0-���浽����Ӳ�̣�1-�ϴ���FTP������,2-ͨ��ͨ���ϴ�
	//3-���ر���ͬʱ�ϴ�FTP,4-���ر���ͬʱ�ϴ�����ͨ��
	unsigned char		bySaveMode;
	//ÿ�α���ץͼ��Ŀ1~5
	unsigned char		byCaptureNum;
	//�Ƿ�����ָ��Ŀ¼���
	unsigned char		byEnableDirectory;
	//ץͼ�ļ��ʱ�����
	unsigned int		dwCaptureInterval;

	//ץͼFTP����������
	//�������128�ֽ�
	char				sFTPServerIpAddr[128];

	//�������Ķ˿ڣ�ftpĬ��21
	unsigned int		dwFTPServerPort;

	//FTP�������û���
	char				sFTPCliUserName[16];

	//FTP�������û�����
	char				sFTPCliUserPass[16];
	
	//ץͼ�Ĵ��Ŀ¼
	char				sDirectoryName[128];
}tmCaptureImageCfg_t;
#define CAPTUREIMAGE_MODE_SAVE			0x00
#define CAPTUREIMAGE_MODE_FTP			0x01
#define CAPTUREIMAGE_MODE_SERVER		0x02
#define CAPTUREIMAGE_MODE_SAVEANDFTP	0x03
#define CAPTUREIMAGE_MODE_SAVEANDSERVER	0x04

//ץͼ�Ĳ���ʱ��
typedef struct tmCaptureSchedCfg_t
{
	//���ṹ��С
	unsigned int				dwSize;
	//ץͼʱ���
	tmSchedTime_t				struCaptureSched[MAX_DAYS][MAX_TIMESEGMENT];
	//ÿ��ץͼ�������ʱ�䣬��λ��
	unsigned int				dwCaptureTime;					
	//ץͼ����Ϊ������0-��������1-��������2-��3������3-��4����
	unsigned char				byCaptureStream;
	//�Ƿ����ò���ץͼ
	unsigned char				byEnableCapture;	
}tmCaptureSchedCfg_t;

/*----------------------------------------------------------------------*/

#define PTZ_REALTRANS			0	/* ͸����̨��ݴ��� */
#define PTZ_LIGHT_PWRON			2	/* ��ͨ�ƹ��Դ */
#define PTZ_WIPER_PWRON			3	/* ��ͨ��ˢ���� */
#define PTZ_FAN_PWRON			4	/* ��ͨ���ȿ��� */
#define PTZ_HEATER_PWRON		5	/* ��ͨ���������� */
#define PTZ_AUX_PWRON			6	/* ��ͨ�����豸���� */

#define PTZ_FOCUS_AUTO			7	/* �Զ��۽� */

#define PTZ_ZOOM_IN				11	/* �������ٶ�SS���(���ʱ��) */
#define PTZ_ZOOM_OUT			12	/* �������ٶ�SS��С(���ʱ�С) */
#define PTZ_FOCUS_NEAR			13	/* �������ٶ�SSǰ�� */
#define PTZ_FOCUS_FAR			14	/* �������ٶ�SS��� */
#define PTZ_IRIS_ENLARGE		15	/* ��Ȧ���ٶ�SS���� */
#define PTZ_IRIS_SHRINK			16	/* ��Ȧ���ٶ�SS��С */
#define PTZ_UP					21	/* ��̨��SS���ٶ����� */
#define PTZ_DOWN				22	/* ��̨��SS���ٶ��¸� */
#define PTZ_LEFT				23	/* ��̨��SS���ٶ���ת */
#define PTZ_RIGHT				24	/* ��̨��SS���ٶ���ת */
#define PTZ_RIGHTUP				25	/* ��̨��SS���ٶ������� */
#define PTZ_RIGHTDOWN			26	/* ��̨��SS���ٶ������� */
#define PTZ_LEFTUP				27	/* ��̨��SS���ٶ������� */
#define PTZ_LEFTDOWN			28	/* ��̨��SS���ٶ������� */
#define PTZ_AUTO				29	/* ��̨��SS���ٶ������Զ�ɨ�� */

#define PTZ_485INPUT			31	/* 485����������� */
#define PTZ_485OUTPUT			32	/* 485���������� */
#define PTZ_SET_KEEPWATCH		33	//���������
#define PTZ_GOTO_KEEPWATCH		34	//���������
#define PTZ_LOCK_KEEPWATCH		35	//����λ���ڲ����ٵ����Զ�����λ������PTZ_UNLOCK_KEEPWATCH�����ӶϿ��ظ�
#define PTZ_UNLOCK_KEEPWATCH	36	//������λ���ظ�ԭ���Զ�״̬

#define PTZ_SET_PRESET			100	// ����Ԥ�õ� 
#define PTZ_CLE_PRESET			101	// ���Ԥ�õ� 
#define PTZ_GOTO_PRESET			102	// ת��Ԥ�õ�

#define PTZ_STARTREC_TRACK		110	// ��ʼ¼�ƹ켣 
#define PTZ_STOPREC_TRACK		111	// ֹͣ¼�ƹ켣 
#define PTZ_STARTRUN_TRACK		112	// ���й켣
#define PTZ_STOPRUN_TRACK		113	// ֹͣ�켣

#define PTZ_STARTREC_CRUISE		120	// ��ʼ¼��Ѳ�� 
#define PTZ_STOPREC_CRUISE		121	// ֹͣ¼��Ѳ�� 
#define PTZ_STARTRUN_CRUISE		122	// ����Ѳ��
#define PTZ_STOPRUN_CRUISE		123	// ֹͣѲ��

#define PTZ_INTEGRATE_CONTROL	124	// ��̨�ۺϿ��ƣ�ͬʱ������ת�ͱ䱶��

//������
typedef struct tmDecoderCfg_t
{
	unsigned int			dwSize;
	unsigned int			dwBaudRate;				//������(bps)ֱ�ӱ�ʾ
													//�ѷ���0��50��1��75��2��110��3��150��4��300��5��600��6��1200��7��2400��8��4800��9��9600��10��19200�� 11��38400��12��57600��13��76800��14��115.2k;
	unsigned char			byDataBit;				// ����м�λ 0��5λ��1��6λ��2��7λ��3��8λ;
	unsigned char			byStopBit;				// ֹͣλ 0��1λ��1��1.5λ��2-2;
	unsigned char			byParity;				// У�� 0����У�飬1����У�飬2��żУ��;
	unsigned char			byFlowcontrol;			// 0���ޣ�1��������,2-Ӳ����	
	unsigned short			wDecoderType;			//����������,����
	unsigned short			wDecoderAddress;		/*��������ַ:0 - 255*/
	char					szDecoderName[20];		//���������	
	unsigned short			wTrackStopTime;			/*�켣���к���ʱʱ�䣬��λΪ��*/
	unsigned char			bySetCruise[16];		/* Ѳ���Ƿ�����: 0-û������,����ֵΪԤ�õ�� */
	unsigned char			bySetPreset[16];		/* Ԥ�õ��Ƿ�����0-û������,����ֵΪԤ�õ�� */
	unsigned char			bySetTrack[16];			/* �켣�Ƿ�����,0-û������,����ֵΪԤ�õ��*/
}tmDecoderCfg_t;

typedef struct tmDecoderInfo_t
{
	unsigned int			dwSize;
	char					szDecoderName[20];				//���������
}tmDecoderInfo_t;

/*
 *Ԥ�õ��½ṹ����
 */
typedef struct tmPresetInfo_t
{
	char			szPresetName[32];		/* Ԥ�õ���� */
	unsigned char	byEnable;				/* Ԥ�õ��Ƿ����� */
	unsigned char	byTemp[3];				/* ���� */
}tmPresetInfo_t;

typedef struct tmPresetCfg_t
{
	unsigned int	dwSize;					//���ṹ��С
	tmPresetInfo_t	pPresetList[128];		//Ԥ�õ��б�
}tmPresetCfg_t;

//////////////////////////////////////////////////////////
//////////////////////Ѳ���ĵ���Ϣ////////////////////////
//////////////////////////////////////////////////////////
typedef struct tmCruisePoint_t
{
	unsigned char	byEnable;				//�Ƿ�����0,1
	unsigned char	byPresetNo;				//Ԥ�õ��0-127
	unsigned char	byCruiseSpeed;			//Ѳ���ٶ�
	unsigned char	byTemp;					//����
	unsigned int	dwStopTime;				//ͣ��ʱ�䣬��λ��
}tmCruisePoint_t;

typedef struct tmCruiseInfo_t
{
	unsigned char	byEnableThisCruise;		//�Ƿ����ñ�Ѳ���켣
	unsigned char	byTemp[3];
	tmCruisePoint_t	struCruise[16];			//Ԥ�õ���Ϣ
}tmCruiseInfo_t;

//Ѳ������
typedef struct tmCruiseCfg_t
{
	unsigned int	dwSize;					//���ṹ��С
	tmCruiseInfo_t	struCruiseLine[CRUISE_MAX_LINE_NUMS];
}tmCruiseCfg_t;

typedef struct tmPtzSchedTime_t
{
	tmSchedTime_t	struSchedTime;
	unsigned char	byRunType;				//��������0-Ѳ����1-�켣
	unsigned char	byRunLine;				//���е���,0xFFΪ������	
	unsigned char	byTemp[2];
}tmPtzSchedTime_t;
//��̨������Ϣ
typedef struct tmPtzSchedCfg_t
{
	unsigned int		dwSize;										//���ṹ��С
	unsigned char		byEnableKeepWatch;							//�Ƿ����ÿ���λ0,1
	unsigned char		byEnableSchedTime;							//�Ƿ�����ʱ�䲼��
	unsigned short		dwKeepWatchCheckTime;						//(��)ֹͣ��̨����һ��ʱ���ʼ���õ��ÿ���λ������ϵͳ��������ÿ���λ
	tmPtzSchedTime_t	struSchedTime[MAX_DAYS][MAX_TIMESEGMENT];	//������ʱ��
	unsigned char		byLimitSpeed[64];							//Zoom��ÿ����ʾ�ٶ�0-��1����63-64��,������ֵΪ0�ǲ�����
	unsigned char		byDisplayPtzInfo;							//��������̨���Ƿ���ʾ��Ϣ(zoom����Ƕ�)
	unsigned char		byDisplayX;									//��Ϣ��ʾX���
	unsigned char		byDisplayY;									//��Ϣ��ʾY���
	unsigned char		byDisplayMode;								//��Ϣ��ʾ�ο�λ�ã��ο�OSD����
}tmPtzSchedCfg_t;

/*----------------------------------------------------------------------*/
//RS232����
typedef struct tmPPPCfg_t
{
	unsigned int	dwSize;
	char			sRemoteIP[24];						//Զ��IP��ַ
	unsigned char	byTemp1;
	char			sLocalIP[24];						//����IP��ַ
	unsigned char	byTemp2;
	char			sLocalIPMask[24];					//����IP��ַ����
	unsigned char	byTemp3;
	char			szUserName[32];						/* �û��� */
	char			szPassword[32];						/* ���� */
	unsigned char	byPPPMode;							//PPPģʽ, 0��������1������	
	unsigned char	byRedial;							//�Ƿ�ز�:0-��,1-��
	unsigned char	byRedialMode;						//�ز�ģʽ,0-�ɲ�����ָ��,1-Ԥ�ûز�����
	unsigned char	byDataEncrypt;						//��ݼ���,0-��,1-��
	unsigned char	byTemp4;							
	unsigned int	dwMTU;								//MTU
	char			sTelephoneNumber[32];				//�绰����
}tmPPPCfg_t;

typedef struct tmRS2322Cfg_t
{
	unsigned int		dwSize;
	unsigned int		dwBaudRate;			/* ������(bps)��0��50��1��75��2��110��3��150��4��300��5��600��6��1200��7��2400��8��4800��9��9600��10��19200�� 11��38400��12��57600��13��76800��14��115.2k; */
	unsigned char		byDataBit;				// ����м�λ 0��5λ��1��6λ��2��7λ��3��8λ;
	unsigned char		byStopBit;				// ֹͣλ 0��1λ,1��2λ;
	unsigned char		byParity;				// У�� 0����У��,1����У�飬2��żУ��;
	unsigned char		byFlowcontrol;			// 0����,1��������,2-Ӳ����
	unsigned int		dwWorkMode;			// ����ģʽ��0��խ����(232��������PPP����)��1������̨(232�������ڲ������)��2��͸��ͨ��
	tmPPPCfg_t			struPPPConfig;
}tmRS2322Cfg_t;
/*----------------------------------------------------------------------*/

//��������
typedef struct tmAlarmInCfg_t
{
	unsigned int			dwSize;
	char					sAlarmInName[32];							/* ��� */
	unsigned char			byAlarmType;								//����������,0������,1������
	unsigned char			byAlarmInHandle;							/* �Ƿ��� */
	tmHandleException_t		struAlarmHandleType;						/* ���?ʽ */
	tmSchedTime_t			struAlarmTime[7][4];						//����ʱ��
	tmTransFer_t			struAlarmTransFer[16];						//������16��ͨ������tmTransFer_t�ж���ͨ����
}tmAlarmInCfg_t;

//DVR�������320
typedef struct tmAlarmOutCfg_t
{
	unsigned int			dwSize;
	unsigned char			sAlarmOutName[32];							/* ��� */
	unsigned int			dwAlarmOutDelay;							/* �������ʱ��(-1Ϊ���ޣ��ֶ��ر�), ���� */
	tmSchedTime_t			struAlarmTime[7][4];						/* �����������ʱ��� */
	unsigned char			byAlarmType;								/* ����������,0������,1������ */
	unsigned char			byTemp[2];									/* ���� */
	unsigned char			dwSchedTimType;								/* �����������,0-��ʱ�䲼����1-Ĭ�Ͽ�ʼ���в�����2-���� */
}tmAlarmOutCfg_t;

//DVR��������
typedef struct tmAlarmCfg_t
{
	//���ṹ��С
	unsigned int	dwSize;			
				
	//�����ϴ�ʱ����(��λ��), Ϊ0��ʾֻҪ�����������������
	//���Ա����ϴ���Ч
	unsigned int	dwUpToTime;						

	//����������ʱʱ��										
	unsigned int	dwAlarmAudioTimeout;			
	//��̨���Ƴ�ʱ���������5��
	unsigned int	dwPtzControlTimeout;			
	//�������ӳ�ʱ���������5��
	unsigned int	dwConfigTimeout;				
	//����̨�������ӳ�ʱ���������5��
	unsigned int	dwSerialTimeout;				

	//����ϵͳ�?λ,ĿǰӲ����֧��
	unsigned char	byAllowSoftReset;				
	//�����������ӳ�ʱ���
	unsigned char	byAllowConfigTinmeout;			
	//�Ƿ�����������Զ���ʱ��λ����
	unsigned char	byAllowAutoReset;				
	//�������ò���ʱ���������ָʾ����
	unsigned char	byAllowConfigBeep;				

	//ѭ����ʽ��0Ϊ��ָ��ʱ��ѭ������ģʽΪϵͳ������ʼ��ʱ�ο�ʱ�䣻
	//����Ϊָ�������е�ָ��ʱ�临λ(1-31)
	unsigned char	byAutoResetMode;				
	//�����ϴ��������ͣ�0�ͻ�����Ҫ��¼��1�ͻ��˲���Ҫ��¼
	unsigned char	byAlarmToManagerType;			
	//¼���ļ���С���Է��Ӽ���0��ʾ��¼��
	unsigned char	byRecoderFileSize;				
	//�Ƿ������Զ�¼��Ϊ0�ر�(��������¼��)��Ϊ1һ��¼������ʱ������¼������������¼��
	unsigned char	byNormalRecoder;				
	
	//��DDNS������ע���ʱ��������λ�룬�������60��
	unsigned int	dwDDNSLoginTimeOut;				
	
	//byAutoResetMode==0ʱΪѭ��ʱ�䣬����Ϊ��λ��������ڵ���60����ϵͳ������ʼ����
	//byAutoResetMode!=0Ϊָ��ʱ���Զ���λ������ʼ�ο�ʱ�䣬����Ϊ��λ����һ���е�����(0-86400)
	unsigned int	dwAutoResetCircleTime;			
	//�Զ���λ��־���ӵ�λ��ʼ��һλ���һ������
	//0λΪ1��ʾ�������縴λ
	//1λΪ1��ʾ������Ƶ�ɼ���λ
	//31λΪ1��ʾ����ϵͳ��λ
	unsigned int	dwAutoResetFlags;			
	//���紫��ǿ������ʽ,0Ϊ�ͻ����ƶ���>0Ϊָ����С���䣬256-8192
	unsigned short	wTranstStreamSize;
	//�Ƿ�����д�ļ�״̬����ʾ
	unsigned char	byEnableWriteFileState;	
	//�Ƿ��ϴ��ļ�����״̬������������������Ҫ����UDP�˿�
	unsigned char	byUpFileStateToManager;
	//��־��������1-255,�����豸��
	unsigned char	byLogRemainDays;
	//�Ƿ�����SD��¼��
	unsigned char	byEnableSDCardRecord;
	//RTSP���紫���С,0ΪĬ��
	unsigned short	wRtpPacketSize;
}tmAlarmCfg_t;

/*----------------------------------------------------------------------*/

#define ALARMTYPE_ALARMIN				0x00
#define ALARMTYPE_DISKFULL				0x01
#define ALARMTYPE_VIDEOLOST				0x02
#define ALARMTYPE_MOTION				0x03
#define ALARMTYPE_DISKNOTFORMAT			0x04
#define ALARMTYPE_DISKACCESS			0x05
#define ALARMTYPE_CAMREAHIDE			0x06
#define ALARMTYPE_VIDEOSTANDARD			0x07
#define ALARMTYPE_UNLAWFULACCESS		0x08
//�ϴ�������Ϣ156
typedef struct tmAlaramInfo_t
{
	unsigned int	dwSize;
	unsigned short  wAlarmType;							//0-�ź�������,1-Ӳ����,2-�źŶ�ʧ��3���ƶ���⣬4��Ӳ��δ��ʽ��,5-��дӲ�̳���,6-�ڵ�����,7-��ʽ��ƥ��, 8-�Ƿ�����
	unsigned short  wAlarmState;						//����״̬0-������1-��ʼ����
	unsigned int	dwAlarmChannel;						//��������˿�
	unsigned int	dwAlarmOutputNumber[4];				//��������˿ڶ�Ӧ������˿ڣ���һλ��Ϊ-1��ʾ��Ӧ��һ�����
	unsigned int	dwAlarmRelateChannel[16];			//��������˿ڶ�Ӧ��¼��ͨ������һλ��Ϊ-1��ʾ��Ӧ��һ·¼��
	unsigned int	dwDiskNumber[16];					//dwAlarmTypeΪ4ʱ,��һλ��Ϊ-1��ʾ�ĸ�Ӳ��
}tmAlaramInfo_t;

//�ϴ��������ı�����Ϣ
typedef struct tmToManagerAlarmInfo_t
{
	unsigned int		dwSize;
	tmAlaramInfo_t		struAlarmInfo;
	char				szDVSName[32];					//DVS���
	unsigned char		szSerialNumber[48];				//���������к�
	unsigned char		szServerGUID[16];				//������ΨһGUID
	unsigned char		byMACAddr[6];					//Զ�������ַ
	char				szServerIP[16];					//��������ַ
	char				szServerMask[24];				//��������ַ
	unsigned char		byTemp[4];
}tmToManagerAlarmInfo_t;
//�ϴ��������ĵ�ͼƬ��Ϣ����
typedef struct tmToManagerImageInfo_t
{
	unsigned int		dwSize;							//���ṹ��С
	struct
	{
		short			nWidth;							//ͼƬ��С��
		short			nHeight;						//ͼƬ��С��
		unsigned char	byBitCount;						//ͼ��λ��
		unsigned char	byRevolving;					//ͼ���Ƿ���ת
		unsigned char	byTemp[2];
	}image;
	BYTE				byTemp1[8];
	unsigned char		byMACAddr[6];					//Զ�������ַ
	unsigned char		byTemp2[2];						//����
	char				szServerIP[16];					//��������ַ
	unsigned char		byImageFmt;						//ͼƬ��ʽ,0-JPEG,1-JPEG2000,2-RGB555,3-RGB565,4-RGB24,
														//5-RGB32,6-YUV444,7-YUV422,8-YUV420,9-BKMPEG4,10-H264
	unsigned char		byCount;						//����ץͼ��Ҫץȡ����
	unsigned char		byIndex;						//��ǰͼƬ�����
	unsigned char		byImageMode;					//ץͼ��ģʽ0-��������ץͼ��1-�ƶ�����ץͼ��2-�ֶ�ץͼ
	unsigned char		byAlarmId;						//����ͨ��
	unsigned char		byChannelId;					//�����ͨ��
	unsigned char		byOtherInfo[2];					//����������Ǳ�������ô0��1��ʾ������״̬
	struct
	{
		short			nYear;
		unsigned char	nMonth;
		unsigned char	nDay;
		unsigned char	nDayOfWeek;
		unsigned char	nHour;
		unsigned char	nMinute;
		unsigned char	nSecond;
	}time;
	unsigned int		dwImageSize;					//ͼ���С��Ҳ���Ǳ��ṹ������ݴ�С
}tmToManagerImageInfo_t;
//�ϴ����ĵ������
//�豸�������
typedef struct tmToManagerLiveHeartInfo_t
{
	//���ṹ����
	unsigned int		dwSize;							
	//�豸����
	unsigned short		nDeviceType;					
	//�豸�ĳ���ID
	unsigned short		nFactoryId;						
	//�豸�˿�
	unsigned short		nDevicePort;					
	//�豸��ַ
	unsigned int		nDeviceAddress;					
	//������ΨһGUID
	unsigned char		nDeviceGUID[16];				
	//�豸��ͨ����
	unsigned char		nChannelCount;		
	//����������
	unsigned char		nAlarmInCount;
	//�����������
	unsigned char		nAlarmOutCount;
	//Ӳ����(������)
	unsigned char		nDiskCount;
	//�豸����������(D1,HDCMA)
	unsigned char		nDeviceSubType;
	//�豸����MARK��ַ����һ������
	unsigned char		nMarkAddress[6];	
	//�豸���
	char				nDeviceName[32];
}tmToManagerLiveHeartInfo_t;

//��ȫ��ʿ�豸������Ϣ����
typedef struct tmToManagerSafeGuardInfo_t
{
	//���ṹ����
	unsigned int		dwSize;				
	//�豸��ַ
	unsigned int		nDeviceAddress;	
	//�豸�˿�
	unsigned short		nDevicePort;					
	//�豸����MARK��ַ����һ������
	unsigned char		nMarkAddress[6];	
	
	//�豸��ͨ�е�״̬0-��ֹ��1-ͨ��
	unsigned char		byLightState;
	//�豸�ĶԽ���ť����1-�Խ�
	unsigned char		byTalkState;
	//�豸�Ĳ�����ť����0-û�а��£�1-����
	unsigned char		byBuFangState;
	//�豸�ĳ�����״̬0-û�а��£�1-����
	unsigned char		byCheFangState;
	//�豸�ı�����ť����0-û�а��£�1-����
	unsigned char		byAlarmState;	
	//�豸�ĺ���״̬0-û�д򿪣�1-��
	unsigned char		byInfraredState;
	//�豸����ˢ��
	unsigned char		byCardEnable;
	//����
	unsigned int		dwCardNo;
}tmToManagerSafeGuardInfo_t;


/* �������豸��Ϣ 256*/
typedef struct tmServerInfo_t
{
	unsigned int		dwSize;							//�ýṹ�Ĵ�С��������д
	unsigned char		bServerConnect;					//���������ӻ��ǶϿ�����
	char				szDVSName[32];					//DVS���
	unsigned char		szSerialNumber[48];				//���������к�
	unsigned char		szServerGUID[16];				//������ΨһGUID	
	unsigned char		byMACAddr[6];					//Զ�������ַ
	char				szServerIP[25];					//��������ַ
	char				szServerMask[25];				//��������ַ
	char				szCenterManagerIP[25];			//�������ĵ�ַ
	unsigned char		byCenterManager;				//�Ƿ�������������

	unsigned char		byAlarmInNum;					//���������뱨������
	unsigned char		byAlarmOutNum;					//�����������������
	unsigned short		wChannelNum;					//������ͨ����

	unsigned int		dwServerType;					//����������
	unsigned short		wDVSPort;						//�˿ں�
	unsigned short		wHttpPort;						//HTTP������
	unsigned int		dwGroupID;						//��������Ŷ˿ں�
	unsigned int		dwSoftwareVersion;				//����汾��,��16λ�����汾,��16λ�Ǵΰ汾
	unsigned int		dwPanelVersion;					//ǰ���汾,��16λ�����汾,��16λ�Ǵΰ汾
	unsigned int		dwHardwareVersion;				//Ӳ���汾,��16λ�����汾,��16λ�Ǵΰ汾
	unsigned int		dwFactoryNo;					//�������鳧�̱��
}tmServerInfo_t;

typedef struct tmServerInfoEx_t
{
	unsigned int		dwSize;							//�ýṹ�Ĵ�С��������д
	unsigned char		bServerConnect;					//���������ӻ��ǶϿ�����
	char				szDVSName[32];					//DVS���
	unsigned char		szSerialNumber[48];				//���������к�
	unsigned char		szServerGUID[16];				//������ΨһGUID	
	unsigned char		byMACAddr[6];					//Զ�������ַ
	char				szServerIP[25];					//��������ַ
	char				szServerMask[25];				//��������ַ
	char				szCenterManagerIP[25];			//�������ĵ�ַ
	unsigned char		byCenterManager;				//�Ƿ�������������

	unsigned char		byAlarmInNum;					//���������뱨������
	unsigned char		byAlarmOutNum;					//�����������������
	unsigned short		wChannelNum;					//������ͨ����

	unsigned int		dwServerType;					//����������
	unsigned short		wDVSPort;						//�˿ں�
	unsigned short		wHttpPort;						//HTTP������
	unsigned int		dwGroupID;						//��������Ŷ˿ں�
	unsigned int		dwSoftwareVersion;				//����汾��,��16λ�����汾,��16λ�Ǵΰ汾
	unsigned int		dwPanelVersion;					//ǰ���汾,��16λ�����汾,��16λ�Ǵΰ汾
	unsigned int		dwHardwareVersion;				//Ӳ���汾,��16λ�����汾,��16λ�Ǵΰ汾
	unsigned int		dwFactoryNo;					//�������鳧�̱��
	unsigned int		dwRunTime;						//������������ʱ��

	unsigned short		wCurrentDVSPort;				//��ǰ�����˿ں�
	unsigned short		wCurrentHttpPort;				//��ǰ����HTTP������
	unsigned int		dwCurrentServerIP;				//��ǰ����IP
	unsigned int		dwCurrentServerMask;			//��ǰ����IP����

	//�����¼�20090306
	unsigned int		dwServerGateWay;				//���������
	unsigned char		byEnableDhcp;					//DHCP����
	unsigned char		byEtherNet;						//����ID0-��һ�����磬1-�ڶ�������
	unsigned char		byWifi;							//�Ƿ���WIFI��ַ1ΪWIFI��ַ

}tmServerInfoEx_t;

//���÷�������ַ�ṹ����
typedef struct tmServerCfg_t
{
	unsigned int		dwSize;							//�ýṹ�Ĵ�С��������д
	tmServerInfo_t		pInfo[1];						//��������Ϣ
	unsigned int		dwMajorCommand;					//��������������
	unsigned int		dwMinorCommand;					//��������������
	char				szUserName[32];					//�����û���
	char				szPassword[32];					//���õĿ���
	int					iConfigMode;					//���ú�����0��ʾ�޶�����1��ʾ��������
	unsigned int		dwResverse;						/*����*/
	unsigned int		dwResverse1;					/*����*/
}tmServerCfg_t;

//���÷�������ַ�ṹ����
typedef struct tmServerExCfg_t
{
	unsigned int		dwSize;							//�ýṹ�Ĵ�С��������д
	tmServerInfo_t		pInfo[1];						//��������Ϣ
	unsigned int		dwMajorCommand;					//��������������
	unsigned int		dwMinorCommand;					//��������������
	char				szUserName[32];					//�����û���
	char				szPassword[32];					//���õĿ���
	unsigned char		iConfigMode;					//���ú�����0��ʾ�޶�����1��ʾ��������
	unsigned char		bControlAll;					//����ʱ�Ƿ����������豸
	unsigned char		bTemp[2];						//����
	unsigned int		dwResverse;						//ָʾ�Ƿ���tmServerCfg_t����չ�ṹ
														//0��ʾʹ��tmServerInfo_t������ݣ�1��ʾtmServerInfoEx_t�������
														//����ֵ��ʾ����ṹ
	unsigned int		dwResverse1;					//����
	tmServerInfoEx_t	pInfoEx[1];						//UPnp��������Ϣ����չ�޸�ֻ���޸�tmServerInfoEx_t�ṹ��
}tmServerExCfg_t;

//�ಥ���ýṹ����
typedef struct tmMultiServerCfg_t
{
	unsigned int		dwSize;							//�ýṹ�Ĵ�С��������д
	unsigned int		dwMajorCommand;					//��������������
	unsigned int		dwMinorCommand;					//��������������
	char				szUserName[32];					//�����û���
	char				szPassword[32];					//���õĿ���
	unsigned int		dwCompareSerialNumber;			//�Ƿ���Ҫƥ�����кţ�0-��ƥ�䣬�������У�1-ƥ��GUID����
	char				szSerialNumber[48];				//������Ψһ���к�
}tmMultiServerCfg_t;

//�豸״̬
typedef struct tmChannelState_t
{
	unsigned int		dwSize;
	unsigned char		byRecordStatic;				//ͨ���Ƿ���¼��,0-��¼��,1-¼��
	unsigned char		bySignalStatic;				//���ӵ��ź�״̬,0-��,1-�źŶ�ʧ
	unsigned char		byHardwareStatic;			//ͨ��Ӳ��״̬,0-��,1-�쳣,����DSP����
	unsigned char		reservedData;
	unsigned int		dwBitRate;					//ʵ������
	unsigned int		dwLinkNum;					//�ͻ������ӵĸ���
	unsigned int		dwClientIP[6];				//�ͻ��˵�IP��ַ
}tmChannelState_t;

typedef struct tmDiskState_t
{
	unsigned int		dwSize;
	unsigned int		dwVolume;							//Ӳ�̵�����
	unsigned int		dwFreeSpace;						//Ӳ�̵�ʣ��ռ�
	unsigned int		dwHardDiskStatic;					//Ӳ�̵�״̬,����,�,�����
}tmDiskState_t;

typedef struct tmUserState_t
{
	unsigned int		dwSize;
	char				szUserName[32];				//��¼�û���
	unsigned int		dwLoginNum;					//��¼��, ���Ϊ0��ʾ���û���¼
	unsigned int		dwLoginAddress[16];			//��¼��ַ
}tmUserState_t;

typedef struct tmWorkState_t
{
	unsigned int		dwSize;
	unsigned int		dwDeviceRunTime;				//�豸���ϴ�����������ʱ�䣬��λ��
	unsigned int		dwDeviceStatic; 				//�豸��״̬,0-��,1-CPUռ����̫��,����85%,2-Ӳ������,���紮������
	tmDiskState_t		struHardDiskStatic[16];			//Ӳ�̵�ǰ״̬ 
	tmChannelState_t	struChanStatic[16];				//ͨ����״̬
	tmUserState_t		struUserStatic[16];				//��¼�û���״̬
	unsigned char		byAlarmInStatic[16];			//�����˿ڵ�״̬,0-û�б���,1-�б���
	unsigned char		byAlarmOutStatic[4];			//��������˿ڵ�״̬,0-û�����,1-�б������

	//add by stone 20090508
	unsigned int		dwCpuClockFrequency;			//CPU��Ƶ��
	unsigned int		dwTotalMemorySize;				//�ܹ��ڴ��С
	unsigned int		dwFreeMemorySize;				//ʣ���ڴ��С
}tmWorkState_t;

//��̨���Ʋ�������ƶ೤ʱ�䣬��ת�Ƕȵ�,��С����С��128�ֽ�
typedef struct tmPtzParameter_t
{	
	unsigned int		dwAutoStopTime;					//�Զ��Ͽ�ʱ�䣬���Ȧ����
	unsigned int		dwZoomValue;					//�䱶*1000(8192)
	unsigned int		dwVerticallyAngle;				//��ֱ�Ƕ�*1000(8192)
	unsigned int		dwHorizontallyAngle;			//ˮƽ�Ƕ�*1000(8192)
	unsigned char		byZoomMode;						//0-����1-��Զ��2-��Ա���
	unsigned char		byVerticallyMode;				//0-��ֱ���ϣ�1-��ֱ���£�2-���λ��
	unsigned char		byHorizontallyMode;				//0-ˮƽ����1-ˮƽ���ң�2-���λ��
	unsigned char		byControlMode;					//����ģʽ0-�Ƕȣ�1-��Բ���
}tmPtzParameter_t;

/*
�����㷽����
1����ͼ������Ϊ�ο�ԭ�㣬��ͼ�񻮷ֳ��ĸ����֣�����ڲο�ԭ�㣬�ֱ�Ϊ���ϡ����ϡ����¡����£������ҡ���Ϊ������Ϊ����
2���õ���ǰ��������ԭ���ֵ���ٳ��Ե�λ���ȣ��õ���Եı���ֵ���˱���ֵ�Ѿ������ķֱ����޹�
3����Ϊ�õ�����Ա���ֵһ��С�ڵ���1��Ϊ�˱���ΪС��ͳһ���õ��ı���ֵ����8192,���˻���ֵȡ����Ϊ�������뵽Э���Ӧ�ֽڡ�
�������£�
��ǰ�ֱ���Ϊ1024��768����ͼ�����ĵ����Ϊ(512,384)�����Ŀ��λ�����Ϊ(768,576),���֪Ŀ��λ�ô������ϣ������ֵΪ��
ˮƽ��
��768-512��/512 = 0.5���ٳ���8192����Ϊ4096����Ϊ���ұߣ�����Ϊ4096�������Ӧ�ֽڼ��ɡ�
��ֱ��
��576-384��/384 = 0.5���ٳ���8192����Ϊ4096����Ϊ���ϱߣ�����Ϊ-4096,�����Ӧ�ֽڼ��ɡ�
*/

//��̨���ƽṹ160�ֽ�
typedef struct tmPtzCommandCfg_t
{
	unsigned int			dwSize;						//�ýṹ��С���˽ṹʵ�ʴ�С���ܸ��
	unsigned int			dwPTZCommand;				//��̨��������
	unsigned int			dwPTZControl;				//���Ʋ����������Ԥ�õ����ΪԤ�õ��
	unsigned int			dwAddress;
	unsigned int			dwSpeed;
	int						iPTZCodeLen;				//PTZ�����볤��
	union
	{
		unsigned char		pPTZCodeBuf[128];			//����������ֵ������ֵ����1ʱ���ӵ�2����ֵ��ʼ
														//�Ļ���Ӧ����˽ṹ��
		tmPtzParameter_t	struParameter;				//��̨����
	}data;
}tmPtzCommandCfg_t;

//��̨��ǰ��Ϣ��Ӧ����TMCC_MAJOR_CMD_PTZCONTROL/TMCC_MINOR_CMD_GETPTZINFO
typedef struct tmPtzIntegrateCfg_t
{
	unsigned int				dwSize;								//�ýṹ��С���˽ṹʵ�ʴ�С
	unsigned int				dwVerticallyStation;				//��ֱλ�þ�ԽǶ�*1000
	unsigned int				dwHorizontallyStation;				//ˮƽλ�þ�ԽǶ�*1000
	unsigned int				dwVerticallyVisualAngle;			//��ǰ���Ӵ�ֱ�Ƕ�*1000
	unsigned int				dwHorizontallyVisualAngle;			//��ǰ����ˮƽ�Ƕ�*1000
	unsigned int				dwZoomValue;						//��ǰ�ı䱶��*1000
	unsigned char				byControlMode;						//����ģʽ0-�Ƕȣ�1-��Բ���
	unsigned char				byTemp[3];
}tmPtzIntegrateCfg_t;

//����Ӳ����Ϣ�ṹ
typedef struct tmDriveInfo_t
{
	unsigned char				byInit;								//Ӳ���Ƿ��ʼ��
	unsigned char				byReset;							//��ʼ��Ӳ��ʱʹ��
	unsigned char				byTemp[2];							//����
	unsigned int				dwDriveType;						//Ӳ������
	unsigned int				dwTotalSpace;						//Ӳ���ܿռ�
	unsigned int				dwUsefullSpace;						//���ÿռ��С
}tmDriveInfo_t;

//����Ӳ�̽ṹ
typedef struct tmDriveCfg_t
{
	unsigned int				dwSize;								//�ýṹ��С
	unsigned int				dwDriveCount;						//Ӳ�̸���
	tmDriveInfo_t				struDisk[16];						//Ӳ����Ϣ
}tmDriveCfg_t;	
#define TMCC_DRIVE_UNKNOWN			0x00
#define TMCC_DRIVE_NO_ROOT_DIR		0x01
#define TMCC_DRIVE_REMOVABLE		0x02
#define TMCC_DRIVE_FIXED			0x03
#define TMCC_DRIVE_REMOTE			0x04
#define TMCC_DRIVE_CDROM			0x05
#define TMCC_DRIVE_RAMDISK			0x06
#define TMCC_DRIVE_SDRAM			0x07

//��Ƶ��������ʹ������TMCC_MAJOR_CMD_VIDEOINCFG/TMCC_MINOR_CMD_VIDEOIN
typedef struct tmVideoInCfg_t
{
	//�ýṹ��С
	unsigned int				dwSize;
	
	//50/60Hz,0-auto, 1:50Hz,2-60Hz
	unsigned char				byAntiFlickerMode;
	//0:VIDEO_COLOR_STYLE_FOR_PC 1:VIDEO_COLOR_STYLE_FOR_TV;
	unsigned char				byVideoColorStyle;	
	//��Ƶ������ת0-normal,1-180,2-90,3-270,4-vflip,5-hflip
	unsigned char				byRotaeAngle180;
	//��ת��ģʽ0-�Զ���1-��ɫ��2-�ڰ�
	unsigned char				byColorTransMode;

	//����ģʽȡֵ��Χ0=1/25,1=1/30,2=1/50,3=1/60,4=1/100,5=1/120,6=1/240,7=1/480,8=1/960,9=1/1024
	//10=�Զ�,11-1/4,12-1/8,13-1/15,14-1/180,15-1/2000,16-1/4000,17-1/10000
	unsigned char				byShutterSpeed;
	//AGC����0=42dB,32=36dB,64=30dB,96=24dB,128=18dB,160=12dB,192=6dB,224-�Զ�
	unsigned char               byAgc;	
	//�����л�ģʽ: 0��ʾ�Զ��л�ģʽ,1��ʾ��ʱ�л����л�ʱ������涨��
	//2��ʾʹ�ñ��������л�,0xFFΪ�ֶ�����ģʽ
	unsigned char               byIRShutMode;
	//��Ȧ�ع�0-F1.6;1-F2.2��0xFF-�Զ�;
	unsigned char				byExposure;

	//�����ʱ��͹ر�ʱ��
	unsigned char               byIRStartHour;
	unsigned char               byIRStartMin;
	unsigned char               byIRStopHour;
	unsigned char               byIRStopMin;

	//0x00-�ɱ���Զ��ع�,0x10-�ɱ���Զ��ع�R1,0x20-�ɱ���Զ��ع�R2,
	//0x01-�ɱ���Զ��ع�+,0x11-�ɱ���Զ��ع�R+1,0x21-�ɱ���Զ��ع�R+2,0x31-�ɱ���Զ��ع�R+3,
	//�ֶ�ѡ��:ģʽ0x07-�Կ������ȣ�0x08-�ع����ȣ�0x09-�Զ���������
	unsigned char				byModeSwitch;	
	//��ƽ�����0-�ر�,1-�Զ�,2-�׳��,3-D4000,4-D5000,5-�չ�,6-����,7-�����,8-ӫ���,9-ӫ���H,10-ˮ��,0xFF-�ֶ�
	unsigned char				byWhiteBalance;
	//�?̬ģʽ0-��,1-�Զ�,2-�ڲ�ģʽ1X,3-�ڲ�ģʽ2X,4-�ڲ�ģʽ3X,5-�ڲ�ģʽ4X, 0xFF-Ĭ��
	unsigned char				byWdr;
	//���ⲹ��0-�أ�1-��
	unsigned char				byBlc;
	
	//��ƽ���ֶ�ֵ����λK
	unsigned int				dwWhiteBalanceVal;
	//3D����0~255
	unsigned char				byMctfStrength;
	//�˹�Ƭ����0-��������1-������2-˲������3-˲�䷴��
	unsigned char				byIRType;
	//�л��˹�Ƭ�Ƿ���Ʊ���������ƺ����(����������Ӻ����)
	unsigned char				byIRCutTriggerAlarmOut;

	//�˹�Ƭ����ʱ״̬(ֻ���ֶ�ģʽ��Ч)
	unsigned char				byIRCutStat;
	//�ع�ˮƽ( 10 ~ 200 )
	unsigned char				byExposureLevel;

	//�ڰ�ģʽ�Զ��л��ķ�ֵ��ֻ�����Զ�ģʽ��Ч
	unsigned char				byColorTransMin;
	unsigned char				byColorTransMax;
}tmVideoInCfg_t;
//�ع�ģʽ
#define EXPOSURE_MODE_AUTOR				0x00
#define EXPOSURE_MODE_AUTOREX			0x01
#define EXPOSURE_MODE_MANUALBYSHUTTER	0x07
#define EXPOSURE_MODE_MANUALBYAPERTURE	0x08
#define EXPOSURE_MODE_MANUALBYAGC		0x09
#define EXPOSURE_MODE_AUTOR1			0x10
#define EXPOSURE_MODE_AUTOR2			0x20
#define EXPOSURE_MODE_AUTOR1EX			0x11
#define EXPOSURE_MODE_AUTOR2EX			0x21
#define EXPOSURE_MODE_AUTOR3EX			0x31
//�����л�ģʽ
#define IRSHUT_MODE_AUTO				0x00
#define IRSHUT_MODE_SCHEDTIME			0x01
#define IRSHUT_MODE_ALARMIN				0x02
#define IRSHUT_MODE_MANUAL				0xFF


//��ͷ��Ȧ��������
typedef struct tmApertureCfg_t
{
	//�ýṹ��С
	unsigned int				dwSize;

	//��Ȧ����0-�ֶ���Ȧ��1-�Զ���Ȧ��(һ�����Ч)
	unsigned char				byApertureType;
	//����
	unsigned char				byTemp[3];
	//��Ȧ��ƽ��ֵ(��ͬ��ͷ��һ���)
	unsigned int				dwDutyBalance;
}tmApertureCfg_t;

//��Ƶ������ýṹʹ������TMCC_MAJOR_CMD_VIDEOOUTCFG/TMCC_MINOR_CMD_VIDEOOUT
typedef struct tmVideoOutCfg_t
{
	//�ýṹ��С
	unsigned int				dwSize;
	//�Ƿ�������Ƶ���
	unsigned char				byEnableVideoOut;
	//��Ƶ���ģʽ��֧��YPbPr,
	//0xFF:Ĭ��˫��������ģ�����
	//0-YPbPr(720p output,onlyģ�����,����ģ����������), 
	//1-YPbPr(480p/576p out,������), 
	//2-YPbPr(480i/576i out������),
	//3-CVBS(480i/576i out������),��ʱ��֧��
	unsigned char				byVideoOutMode;
	//���ˢ����
	unsigned char				byRenovator;
	//����
	unsigned char				byResverse;

	//��Ƶ����ֱ���
	unsigned short				wWidth;
	unsigned short				wHeight;	
	
}tmVideoOutCfg_t;

/*��ͼ��ɼ�ƫ��΢������ */
typedef struct tmVideoEptzCfg_t
{
	unsigned int	dwSize;	

	unsigned char	byClearLeft;
	unsigned char	byClearTop;
	unsigned char	byClearRight;
	unsigned char	byClearBottom;

	short			offset_x;
	short			offset_y;
	short			offset_cx;
	short			offset_cy;
}tmVideoEptzCfg_t;

//ȫ��¼���������(�ӽṹ)
typedef struct tmRecordDay_t
{
	//�Ƿ�ȫ��¼�� 0-�� 1-��
	unsigned char	byAllDayRecord;	
	//0:��ʱ¼��1:�ƶ���⣬2:����¼��3:����|������4:����&����, 5:�����, 6: ����¼��, 7:�ֶ�¼��
	unsigned char	byRecordType;
	//����
	unsigned char	byTemp[2];
}tmRecordDay_t;

//ʱ���¼���������(�ӽṹ)
typedef struct tmRecordSched_t
{
	//¼��ʱ��
	tmSchedTime_t	struRecordTime;
	//0:��ʱ¼��1:�ƶ���⣬2:����¼��3:����|������4:����&����, 5:�����, 6: ����¼��, 7:�ֶ�¼��
	unsigned char	byRecordType;
	//����
	char			byTemp[3];
}tmRecordSched_t;

//ͨ������¼���������
typedef struct tmRecordCfg_t
{
	//���ṹ��С
	unsigned int				dwSize;
	//ȫ��¼��
	tmRecordDay_t				struRecordAllDay[MAX_DAYS];
	//¼��ʱ���
	tmRecordSched_t				struRecordSched[MAX_DAYS][MAX_TIMESEGMENT];
	//������ʱ(��λ:�룬>=10��)��¼���ļ���С��tmAlarmCfg.byRecoderFileSize
	unsigned int				dwRecordTime;					
	//Ԥ¼ʱ��(��λ:��)
	unsigned int				dwPreRecordTime;				
	//¼�񱣴���ʱ��(��λ:��)
	unsigned int				dwRecorderDuration;				
	//�Ƿ�����¼��,��Ҫ���˫���ݣ�0/1
	unsigned char				byRedundancyRec;
	//¼��ʱ����������ʱ�Ƿ��¼��Ƶ���
	unsigned char				byAudioRec;
	//¼������Ϊ������0-��������1-��������2-��3������3-��4����
	unsigned char				byRecordStream;
	//�Ƿ�����¼��
	unsigned char				byEnableRecord;	
}tmRecordCfg_t;

//ͨ��FTP¼��������ã�FTP���òο�tmFTPCfg_t�ṹ����
typedef struct tmFtpRecordCfg_t
{
	//���ṹ��С
	unsigned int				dwSize;
	//ȫ��¼��
	tmRecordDay_t				struRecordAllDay[MAX_DAYS];
	//¼��ʱ���
	tmRecordSched_t				struRecordSched[MAX_DAYS][MAX_TIMESEGMENT];
	//������ʱ(��λ:�룬>=10��)��¼���ļ���С��tmAlarmCfg.byRecoderFileSize
	unsigned int				dwRecordTime;	
	//Ԥ¼ʱ��(��λ:��)
	unsigned int				dwPreRecordTime;			
	//¼��ʱ����������ʱ�Ƿ��¼��Ƶ���
	unsigned char				byAudioRec;
	//¼������Ϊ������
	unsigned char				byRecordStream;
	//�Ƿ�����¼��
	unsigned char				byEnableRecord;
	//����
	unsigned char				byTemp;	
}tmFtpRecordCfg_t;


/////////////////////////////////////////////////////////
/////////////////////���������ýṹ����//////////////////
/////////////////////////////////////////////////////////
//��������������Ϣ������ͨ����Command�и��
typedef struct tmConnectCfg_t
{
	unsigned int				dwSize;								//�ýṹ��С
	char						sRemoteIP[24];						//Զ��IP��ַ
	unsigned char				byConnectMode;						//���ӵ�ģʽ0-Ĭ������ָ����Ϣ,1-ָ�����е�ͨ����(��Ҫ����豸�Ƿ�֧��)
	char						sTurnServerIP[24];					//ת����IP��ַ	
	unsigned char				byTemp2;
	char						szUserName[32];						/* �û��� */
	char						szPassword[32];						/* ���� */
	unsigned short				wConnectPort;						/* ���Ӷ˿� */
	unsigned short				wChannelID;							/* ���ӵ�ͨ���� */
	unsigned short				wStreamID;							/* ���ӵ������� */	
	unsigned short				wDelayTime;							/* ѭ��ʱ��(��)��������ڵ���10��*/
	unsigned char				byEnableTurnServer;					/* �Ƿ�����ת��������0-�رգ�1-���� */
	unsigned char				byStreamType;						/* ������������ */
	unsigned char				byTransType;						/* ���紫�䷽ʽ */
	unsigned char				byDisplay;							/* �Ƿ�������������ӣ���Ϊѭ������ʱ��Ч��������Ϊ�������� */
	unsigned char				byTemp4[2];
}tmConnectCfg_t;

//����ͨ���б���Ϣ
typedef struct tmConnectListCfg_t
{
	unsigned int               dwSize;								//�ṹ��С����Ҫ��ӳʵ�ʴ�Сsizeof(tmAlarmDeviceCfg_t)*dwCount+8
	unsigned int               dwCount;							//�����豸����
	tmConnectCfg_t				pConnectList[1];					//�����豸��Ϣ�б?�����Զ���һ������Ҫ���dwCount�ж�
}tmConnectListCfg_t;

//����ͨ������
typedef struct tmWindowsCfg_t
{
	unsigned int				dwSize;								// �ýṹ��С
	unsigned char				byImageQuant;						/* �������� */
	unsigned char				byEnableState;						/* �Ƿ���ʾ״̬ */
	unsigned char				byEnableAudio;						/* �Ƿ񲥷����� */
	unsigned char				byResverse;							/* ���� */
}tmWindowsCfg_t;
//��ʾ��������
typedef struct tmDisplayCfg_t
{
	unsigned int				dwSize;								//�ýṹ��С
	unsigned char				bySingleView;						/* �Ƿ񵥻�����ʾ */
	unsigned char				byWindowID;							/* ��Ҫ�Ŵ���ʾ�Ĵ��� */
	unsigned char				byResverse[2];
}tmDisplayCfg_t;
//��������Ϣ
typedef struct tmLockCfg_t
{
	unsigned int				dwSize;
	unsigned char				byLocked;
	unsigned char				byResverse[3];
}tmLockCfg_t;

//����������
typedef struct tmWindowCapabilityCfg_t
{
	//���ṹ��С
	unsigned int				dwSize;

	//ϵͳ֧�ִ����л���
	int							iSwitchWindowNum;
	//�����б�
	unsigned char				bySwitchWindowList[32];

	//ÿ����֧��Ѱ�е��������
	unsigned char				byCircleCount;
}tmWindowCapabilityCfg_t;

//NVR��ͨ�����ýṹ����
/////////////////////////////////////////////////////////////////////////////////////
//add by zzt 2010-6-25
//����NVR��ʹ�õ�ͨ����Ϣ

//������������豸��Ϣ
typedef struct tmAlarmDeviceCfg_t
{
	unsigned int				dwSize;								//�ýṹ��С
	unsigned int				dwFactoryId;						//�豸��ID
	char						sName[32];							//ͨ����
	char						sUserName[32];						//�û���
	char						sPassword[32];						//����
	char						sAddress[32];						//Զ��IP��ַ����������
	unsigned short				wPort;								//���Ӷ˿�
	unsigned short				wAlarmInBase;						//��������ͨ����ʼͨ����
	unsigned short				wAlarmInNum;						//��������ͨ����
	unsigned short				wAlarmOutBase;						//�������ͨ����ʼ��
	unsigned short				wAlarmOutNum;						//�������ͨ����
	unsigned char				byEnable;							//�Ƿ�����
	unsigned char				bySourceType;						//ֻ��,ͨ��ģʽ0-���أ�1-����
}tmAlarmDeviceCfg_t;

//ͨ���б���Ϣ
typedef struct tmAlarmDeviceListCfg_t
{
	unsigned int				dwSize;								//�ṹ��С����Ҫ��ӳʵ�ʴ�Сsizeof(tmAlarmDeviceCfg_t)*dwCount+8
	unsigned int				dwCount;							//�����豸����
	tmAlarmDeviceCfg_t			pAlarmList[1];						//�����豸��Ϣ�б?�����Զ���һ������Ҫ���dwCount�ж�
}tmAlarmDeviceListCfg_t;

//����ͨ����Ϣ
typedef struct tmChannelCfg_t
{
	unsigned int				dwSize;								//�ýṹ��С
	unsigned int				dwFactoryId;						//�豸��ID
	char						sName[32];							//ͨ����
	char						sUserName[32];						//�û���
	char						sPassword[32];						//����
	char						sAddress[32];						//Զ��IP��ַ����������
	char						sTurnAddress[32];					//ת������ַ
	unsigned short				wPort;								//���Ӷ˿�
	unsigned short				wTurnPort;							//ת�����˿�
	unsigned char				byChannelID;						//���ӵ�ͨ����
	unsigned char				bySubStream;						//�Ƿ�������
	unsigned char				byTurnServer;						//�Ƿ�����ת��������0-�رգ�1-����
	unsigned char				byStreamType;						//������������0-ֻ������Ƶ����1-��������Ƶ��
	unsigned char				byTransType;						//���紫�䷽ʽ0-�ڲ�Ĭ��Э�飬1-RTSPЭ��
	unsigned char				byEnable;							//��ͨ���Ƿ�����
	unsigned char				bySourceType;						//ֻ��,ͨ��ģʽ0-���أ�1-����
	unsigned char				byTemp;								//����
}tmChannelCfg_t;

//ͨ���б���Ϣ
typedef struct tmChannelListCfg_t
{
	unsigned int				dwSize;								//�ṹ��С����Ҫ��ӳʵ�ʴ�Сsizeof(tmChannelCfg_t)*dwCount+8
	unsigned int				dwCount;							//ͨ������
	tmChannelCfg_t				pChannelList[1];					//ͨ����Ϣ�б?�����Զ���һ������Ҫ���dwCount�ж�
}tmChannelListCfg_t;

//RTSP����ͨ����Ϣ
typedef struct tmRtspChannelNameInfo_t
{
	BYTE						byEnable;						//�Ƿ�����
	BYTE						byTemp[3];						//����
	char						sName1[32];						//��һ����������
	char						sName2[32];						//�ڶ�����������
	char						sName3[32];						//��������������
	char						sName4[32];						//��������������
}tmRtspChannelNameInfo_t;
typedef struct tmRtspChannelNameCfg_t
{
	unsigned int				dwSize;							//���ṹ��С
	unsigned int				dwCount;						//ͨ����
	tmRtspChannelNameInfo_t		struRtspName[1];				//RTSP����б�
}tmRtspChannelNameCfg_t;

//��־��Ϣ
typedef struct tmLogInfo_t
{
	unsigned int			dwSize;									//���ṹ��С
	struct
	{
		unsigned short		wYear;									//��
		unsigned char		byMonth;								//��
		unsigned char		byDay;									//��
		unsigned char		byHour;									//ʱ
		unsigned char		byMinute;								//��
		unsigned char		bySecond;								//��
		unsigned char		byTemp;									//����
	}struLogTime;													//��־��¼ʱ��
	char					sUserName[32];							//�������û���
	char					sAddress[16];							//Զ�������ַ
	unsigned char			byUserLoginType;						//�û���¼��ʽ0-���أ�1-����
	unsigned char			byMajorType;							//������ 0-ϵͳ, 1-����; 2-�쳣; 3-����; 0xff-ȫ��
	unsigned char			byMinorType;							//������ 0-ȫ��;
	unsigned char			byTemp;									//����
    char					sInfo[4];								//��־���ݣ������Զ���4���ֽ�
}tmLogInfo_t;

typedef struct tmLogInfoListCfg_t
{
	unsigned int			dwSize;
	unsigned int			dwCount;
	tmLogInfo_t				struLogInfo;
}tmLogInfoListCfg_t;

//��־����
typedef struct tmLogCfg_t
{
	unsigned int			dwSize;									//���ṹ��С
	tmTimeInfo_t			struStartTime;							//��־��ʼʱ��
	tmTimeInfo_t			struStopTime;							//��־����ʱ��
}tmLogCfg_t;

//�����γ�����ýṹ��������TMCC_MAJOR_CMD_THEODOLITECFG
typedef struct tmTheodoliteCfg_t
{
	unsigned int			dwSize;									//���ṹ��С
	unsigned int			dwLongitude;							//����*10000
	unsigned int			dwLatitude;								//γ��*10000
}tmTheodoliteCfg_t;

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////�ļ�����/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//�ļ�������������
typedef struct tmFindConditionCfg_t
{
	unsigned int			dwSize;			//���ṹ��С
	unsigned char			byChannel;		//������ͨ��
	unsigned char			byFileType;		//�������� 0xFF-ȫ����'N'-��ʱ��'M'-�ƶ���'A'-������'H'-�ֶ���'O'-����
	unsigned char			bySearchAllTime;//��������ʱ���ļ�
	unsigned char			bySearchImage;	//�Ƿ�����ͼƬ
	tmTimeInfo_t			struStartTime;	//�����Ŀ�ʼʱ��
	tmTimeInfo_t			struStopTime;	//�����Ľ���ʱ��
}tmFindConditionCfg_t;

//��������¼���ļ���Ϣ
typedef struct tmFindFileCfg_t
{
	unsigned int			dwSize;	
	char					sFileName[64];		//�ļ���
	unsigned char			byChannel;			//������ͨ��
	unsigned char			byAlarmType;		//�������� 0xFF-ȫ����'N'-��ʱ��'M'-�ƶ���'A'-������'H'-�ֶ���'O'-����
	unsigned short			wFactoryId;			//����ID
	tmTimeInfo_t			struStartTime;		//�ļ��Ŀ�ʼʱ��
	tmTimeInfo_t			struStopTime;		//�ļ��Ľ���ʱ��
	unsigned int			dwFileTime;			//�ļ�ʱ�䣬����
	unsigned int			dwFileSize;			//�ļ��Ĵ�С(�ֽڱ�ʾ������¼���ļ�����̫��)
	unsigned char			byImage;			//�ļ��Ƿ�ΪͼƬ
	unsigned char			byFileFormat;		//�ļ���ʽ
	unsigned char			byTemp[2];
}tmFindFileCfg_t;

//�ļ����Żص��ӿڶ���
//�ļ����ʽӿڻص��ṹ����
typedef struct tmFileAccessInterface_t
{
	HANDLE			(*Open)( const char* lpFileName, const char* lpMode, void* context );
	int				(*Close)(HANDLE hFile);
	unsigned int	(*Seek)( HANDLE hFile, int offset, int origin );
	int				(*Read)( HANDLE hFile, void* lpBuffer, int nRead );
	int				(*Write)( HANDLE hFile, void* lpBuffer, int nWrite );
	unsigned int	(*Size)( HANDLE hFile );
}tmFileAccessInterface_t;

//�ļ�����ṹ����
typedef struct tmAvIndexEntry_t
{
    unsigned int	ckid;
    unsigned int	dwFlags;
    unsigned int	dwChunkOffset;
    unsigned int	dwChunkLength;
}tmAvIndexEntry_t;
//������dwFlagsֵ
#define AVIIF_LIST							0x00000001L // chunk is a 'LIST'
#define AVIIF_KEYFRAME						0x00000010L // this frame is a key frame.
#define AVIIF_NOTIME						0x00000100L // this frame doesn't take any time
#define AVIIF_COMPUSE						0x0FFF0000L // these bits are for compressor use

//�ļ�������������
typedef struct tmPlayConditionCfg_t
{
	unsigned int						dwSize;	
	unsigned short						wFactoryId;			//����ID
	unsigned char						byChannel;			//ͨ��	
	unsigned char						byPlayImage;		//�Ƿ����ͼƬ
	union
	{
		struct
		{
			tmTimeInfo_t				struStartTime;		//�ļ��Ŀ�ʼʱ��
			tmTimeInfo_t				struStopTime;		//�ļ��Ľ���ʱ��
			unsigned char				byCheckStopTime;	//�Ƿ������ʱ��
		}time;
		struct
		{
			unsigned char				byAutoCreateIndex;	//�Ƿ��Զ��������
			unsigned char				byAutoPlay;			//�򿪺��Ƿ��Զ�����
			unsigned char				byTemp[2];
			char						sFileName[128];		//�ļ���
			tmFileAccessInterface_t*	pFileCallBack;		//�ļ����ʻص�����
			void*						pFileContext;		//�ļ�������ؾ��
			tmAvIndexEntry_t*			pAvIndex;			//�����
			int							iAvIndexCount;		//�����е�������
		}file;
	}info;
}tmPlayConditionCfg_t;

//�ļ�������������
typedef struct tmDownloadFileCfg_t
{
	tmPlayConditionCfg_t	struCondition;		//�ļ�����
	char					sFileName[128];		//�����ļ���
}tmDownloadFileCfg_t;


//Զ���ļ��򿪿��ƽṹ����
#define PLAY_CONTROL_PLAY				0		//����,��iPlayData��Ϊ���Ų���(0-������ǰ����,1-�ظ�Ĭ��)
#define PLAY_CONTROL_STOP				1		//ֹͣ
#define PLAY_CONTROL_PAUSE				2		//��ͣ,ע��ֱֹͣ�ӵ�����عرպ����
#define PLAY_CONTROL_FAST				3		//���,��iSpeed��Ϊ�ٶ�
#define PLAY_CONTROL_SLOW				4		//���,��iSpeed��Ϊ�ٶ�
#define PLAY_CONTROL_SEEKPOS			5		//seek,��iCurrentPosition
#define PLAY_CONTROL_SEEKTIME			6		//seek,��dwCurrentTime��Ϊʱ��
#define PLAY_CONTROL_STEMP				7		//stemp,��֡����
#define PLAY_CONTROL_SWITCH				8		//�л��ļ�,��szFileName��Ϊ�ļ���/��struTimeʱ��
#define PLAY_CONTROL_MUTE				9		//��Ƶ����,��iEnableAudio��Ϊ����
#define PLAY_CONTROL_UPEND				10		//����
#define PLAY_CONTROL_GETAVINDEX			11		//�õ������ļ�������
#define PLAY_CONTROL_SETAVINDEX			12		//���ò����ļ�������
typedef struct tmPlayControlCfg_t
{
	unsigned int				dwSize;				//���ṹ��С
	unsigned int				dwCommand;			//��������											
	union
	{
		tmTimeInfo_t			struTime;			//�ļ��Ŀ�ʼʱ��
		int						iPlayData;			//���Ų���
		int						iSpeed;				//���ŵ��ٶ�
		int						iEnableAudio;		//��Ƶ����
		int						iCurrentPosition;	//�µĲ���λ��(֡)
		unsigned int			dwCurrentTime;		//�µĲ���λ��(����)
		BOOL					bForward;			//ǰ��֡
		BOOL					bClearDisplay;		//�����ʾ

		struct
		{
			unsigned char		byAutoCreateIndex;	//�Ƿ��Զ��������
			unsigned char		byAutoPlay;			//�򿪺��Ƿ��Զ�����
			unsigned char		byTemp[2];
			char				sFileName[128];		//�л����ļ���
		}file;
		struct
		{
			tmAvIndexEntry_t*	pAvIndex;			//�����
			int					iAvIndexCount;		//�����е�������
			int					iAvIndexMaxCount;	//�������������
		}index;
	}control;
}tmPlayControlCfg_t;

//�����ļ��ĵ�ǰ��Ϣ
typedef struct tmPlayStateCfg_t
{
	unsigned int			dwSize;				//���ṹ��С
	unsigned char			byCurrentState;		//��ǰ����״̬
	unsigned char			byResetTime;		//��Ҫ��λʱ���
	unsigned char			byResetFile;		//��Ҫ��λʱ���
	unsigned char			byTemp;				//����

	unsigned int			dwTotalFrames;		//�ܹ�֡��
	unsigned int			dwCurrentFrame;		//��ǰ֡��

	unsigned int			dwTotalTimes;		//��ʱ��(����)
	unsigned int			dwCurrentTimes;		//��ǰʱ��(����)
	
	tmTimeInfo_t			struStartTime;		//��ǰ�����ļ��Ŀ�ʼʱ��
}tmPlayStateCfg_t;

//��������Ų���ṹ����
//�ļ�������������
typedef struct tmPlayRealStreamCfg_t
{
	unsigned int			dwSize;	
	char					szAddress[32];		//���ӷ�������IP��ַ
	char					szTurnAddress[32];	//ת������ַ
	int						iPort;				//���������ӵĶ˿�
	char					szUser[32];			//��¼�û���
	char					szPass[32];			//��¼�û�����
	unsigned char			byChannel;			//ͨ��
	unsigned char			byStream;			//������
	unsigned char			byTranstType;		//��������
	unsigned char			byReConnectNum;		//��������	
	int						iTranstPackSize;	//������С
	int						iReConnectTime;		//������ʱ����
	unsigned char			byTransProtocol;	//����Э��0-�ڲ��Զ�,1-SONY,2-RTSP	
}tmPlayRealStreamCfg_t;

//����Ƶԭʼ֡��Ϣ
typedef struct tmAvImageInfo_t
{
	BOOL			video;
	union
	{
		BYTE*		yuv[4];
		BYTE*		buffer;
	}data;

	union
	{
		int			linesize[4];
		int			bufsize;
	}size;

	union
	{
		struct
		{
			short	width;
			short	height;
			int		framerate;
			BYTE	format;	
			BYTE	temp[3];
		}video;
		struct
		{
			int		samplespersec;
			BYTE	channels;
			BYTE	bitspersample;
		}audio;
		BYTE		temp[16];
	}format;

	int				key_frame;	
	unsigned int	timestamp;
}tmAvImageInfo_t;

//�������Ϣ
typedef struct tmRealStreamInfo_t
{
	unsigned int		dwSize;				//���ṹ��С

	unsigned char		byFrameType;		//֡����0-��Ƶ��1-��Ƶ��2-�����ͷ
	unsigned char		byNeedReset;		//�Ƿ���Ҫ��λ������
	unsigned char		byKeyFrame;			//�Ƿ�ؼ�֡
	unsigned char		byStreamNo;			//������

	unsigned int		dwFactoryId;		//����ID	
	unsigned int		dwStreamTag;		//������Tag
	unsigned int		dwStreamId;			//��ID
	union
	{
		int				iWidth;				//��Ƶ��
		int				iSamplesPerSec;		//��Ƶ������
	};
	union
	{
		int				iHeight;			//��Ƶ��
		int				iBitsPerSample;		//��Ƶ����λ��
	};
	union
	{
		struct
		{
			short		iFrameRate;			//֡��*1000
			short		iDisplayFrameRate;	//֡��*1000
		}framerate;
		int				iChannels;			//��Ƶ�������
	};
	
	//add by 2009-0429
	union
	{
		unsigned int	nDisplayScale;	//��ʾ����*1000
	};
	
	unsigned int		dwTimeStamp;	//ʱ���(��λ����)
	unsigned int		dwPlayTime;		//��֡����ʱ��(��λ����)
	unsigned int		dwBitRate;		//���������������С	

	BYTE*				pBuffer;		//��ݻ���
	int					iBufferSize;	//��ݴ�С
	
	BYTE*				pBuffer2;		//���2����
	int					iBuffer2Size;	//���2��С
}tmRealStreamInfo_t;


/*������붨��*/
//�û�����
#define TMCC_MAJOR_CMD_USERCFG						0x101		//�û��������������Ϣ
#define TMCC_MINOR_CMD_USER_INFO					0x01		//�����û���Ϣ
#define TMCC_MINOR_CMD_USER_SINGLEINFO				0x02		//�����û���Ϣ
#define TMCC_MINOR_CMD_USER_ADD						0x03		//����û�
#define TMCC_MINOR_CMD_USER_DELETE					0x04		//ɾ���û�
#define TMCC_MINOR_CMD_USER_MOTIFYPASSWORD			0x05		//�޸��û�����
#define TMCC_MINOR_CMD_USER_MOTIFYRIGHT				0x06		//�޸��û�Ȩ��
#define TMCC_MINOR_CMD_USER_VERIFY					0x07		//��֤�û�
#define TMCC_MINOR_CMD_USER_DATA					0x08		////�������չ��ݣ��������û������������ֻ�������

//��������������
#define TMCC_MAJOR_CMD_DEVICECFG					0x102		//�豸����
#define TMCC_MAJOR_CMD_NETCFG						0x103		//�������
#define TMCC_MINOR_CMD_LANNETCFG					0x00		//���������������
#define TMCC_MINOR_CMD_WIFINETCFG					0x01		//���������������

#define TMCC_MAJOR_CMD_PICCFG						0x104		//ȡͼ�����
#define TMCC_MINOR_CMD_PIC							0x00		//ȡͼ�����(�ϳɽṹ)
#define TMCC_MINOR_CMD_OSD							0x01		//ȡͼ��OSD����
#define TMCC_MINOR_CMD_MASK							0x02		//ȡͼ���ڸǲ���
#define TMCC_MINOR_CMD_LOST							0x03		//ȡͼ����Ƶ��ʧ����
#define TMCC_MINOR_CMD_MOTION						0x04		//ȡͼ���ƶ�������
#define TMCC_MINOR_CMD_HIDEALARM					0x05		//ȡͼ���ڵ���������

#define TMCC_MAJOR_CMD_COMPRESSCFG					0x105		//ѹ������
#define TMCC_MINOR_CMD_COMPRESSCFG					0x00		//���ñ������
#define TMCC_MINOR_CMD_QUERYCOMPRESSCAPABILITY		0x01		//��ѯ��������

#define TMCC_MAJOR_CMD_RECORDCFG					0x106		//¼��ʱ�����
#define TMCC_MINOR_CMD_LOCALRECORDCFG				0x00		//����¼������
#define TMCC_MINOR_CMD_FTPRECORDCFG 				0x01		//FTP¼������


//��̨����������
#define TMCC_MAJOR_CMD_DECODERCFG					0x107		
#define TMCC_MINOR_CMD_485CFG 						0x00		//485��������
#define TMCC_MINOR_CMD_CRUISECFG 					0x01		//Ѳ����������
#define TMCC_MINOR_CMD_PTZCFG						0x02		//��̨��������
#define TMCC_MINOR_CMD_PRESETCFG					0x03		//Ԥ�õ��������

#define TMCC_MAJOR_CMD_RS232CFG 					0x108		//232���ڲ���
#define TMCC_MAJOR_CMD_ALARMINCFG 					0x109		//�����������
#define TMCC_MAJOR_CMD_ALARMOUTCFG 					0x10A		//�����������

#define TMCC_MAJOR_CMD_TIMECFG 						0x10B		//DVRʱ��
#define TMCC_MINOR_CMD_TIMECFG 						0x00		//ʱ������
#define TMCC_MINOR_CMD_ZONECFG 						0x01		//ʱ������
#define TMCC_MINOR_CMD_DAYLIGHTCFG 					0x02		//����ʱ����

#define TMCC_MAJOR_CMD_PREVIEWCFG 					0x10C		//Ԥ������
#define TMCC_MINOR_CMD_PREVIEWCOLORCFG 				0x00		//��ɫ����
#define TMCC_MINOR_CMD_COMPRESSOFFSETCFG 			0x01		//Ԥ��ƫ�Ʋ���
#define TMCC_MINOR_CMD_PREVIEWOFFSETCFG 			0x02		//Ԥ��ƫ�Ʋ���
#define TMCC_MINOR_CMD_PICMODE						0x03        //����ͼ��ģʽ(add by zzt 2009-09-17)

//����������
#define TMCC_MAJOR_CMD_VIDEOOUTCFG 					0x10D		//��Ƶ�������
#define TMCC_MINOR_CMD_VIDEOOUT						0x00		//��Ƶ�������
#define TMCC_MINOR_CMD_CONNECTINFO					0x01		//����������Ϣ
#define TMCC_MINOR_CMD_ENUMCONNECTINFO				0x02		//�о�������Ϣ
#define TMCC_MINOR_CMD_WINDOWSINFO					0x03		//������Ϣ
#define TMCC_MINOR_CMD_DISPLAYINFO					0x04		//��������ʾ��Ϣ
#define TMCC_MINOR_CMD_LOCK							0x05		//��ǰ���ӣ���ʾ��ѭ������
#define TMCC_MINOR_CMD_CLEAR						0x06		//���ѭ���б?������ǰ����
#define TMCC_MINOR_CMD_CONNECT						0x07		//��ʼ����
#define TMCC_MINOR_CMD_DISCONNECT					0x08		//�Ͽ�����
#define TMCC_MINOR_CMD_WINDOWCAPABILITY				0x09		//���봰������

#define TMCC_MAJOR_CMD_EXCEPTIONCFG 				0x10E		//�쳣����
//����������Ϣ
#define TMCC_MAJOR_CMD_SERVERMESSAGE				0x10F		//��������Ϣ
#define TMCC_MINOR_CMD_DEBUGINFO					0x01		//������������Ϣ�����԰汾��Ч
#define TMCC_MINOR_CMD_SERVERSTART 					0x02		//����������
#define TMCC_MINOR_CMD_SERVERSTOP 					0x03		//�������˳�
#define TMCC_MINOR_CMD_SERVERALARM 					0x04		//�����ϴ��������ľ�����Ϣ��tmToManagerAlarmInfo_t
#define TMCC_MINOR_CMD_SERVERWANTSYNCTIME			0x05		//������ϣ��ͬ��ʱ��
#define TMCC_MINOR_CMD_SERVERIMAGE					0x06		//����������ͼƬ�ϴ�,������Ϣ��tmToManagerImageInfo_t
#define TMCC_MINOR_CMD_PTZCLOSEBYOTHERUSER			0x07		//��̨���Ʊ������û��ر�
#define TMCC_MINOR_CMD_PTZCLOSEBYTIMEOUT			0x08		//��̨����ʱ�䳬ʱ�ر�
#define TMCC_MINOR_CMD_SERIALMESSAGE				0x09		//���������صĴ������
#define TMCC_MINOR_CMD_SERVERLIVEHEART				0x0A		//�豸�������
#define TMCC_MINOR_CMD_APERTUREREPAIRCOMPLETE		0x0B		//��ȦУ�����
#define TMCC_MINOR_CMD_BADPIXREPAIRCOMPLETE			0x0C		//�����������޸����
#define TMCC_MINOR_CMD_SAFEGUARDINFO				0x0D		//��ȫ��ʿ�����ϴ��������ľ�����Ϣ��tmToManagerSafeGuardInfo_t

//��̨��������
#define TMCC_MAJOR_CMD_PTZCONTROL 					0x110		//��������̨�����봮�ڿ���
#define TMCC_MINOR_CMD_PTZGETDECODERLIST			0x00		//�õ���̨���ƽ�����Э��
#define TMCC_MINOR_CMD_PTZOPEN 						0x01		//����̨����
#define TMCC_MINOR_CMD_PTZOPENANDLOCK				0x02		//����̨���ƺ�����̨
#define TMCC_MINOR_CMD_PTZCLOSE 					0x03		//�ر���̨����
#define TMCC_MINOR_CMD_PTZSENDCMD					0x04		//������̨��������
#define TMCC_MINOR_CMD_PTZTRANS						0x05		//����͸���������
#define TMCC_MINOR_CMD_SERIALOPEN					0x06		//�򿪴���ͨ��ͨ��
#define TMCC_MINOR_CMD_SERIALCLOSE					0x07		//�ر�ͨ��ͨ��
#define TMCC_MINOR_CMD_SERIALSEND					0x08		//����ͨ��ͨ�����
#define TMCC_MINOR_CMD_GETPTZINFO					0x09		//��ȡ��ǰ��̨��Ϣ
#define TMCC_MINOR_CMD_SERIALRECV					0x0A		//����ͨ��ͨ�����

//�������Ļ����
#define TMCC_MAJOR_CMD_SERVERCONTROL				0x111		//Զ�̷���������
#define TMCC_MINOR_CMD_REMONTALARMIN				0x01		//�����ź��ϴ�������
#define TMCC_MINOR_CMD_OPENLIGHT					0x02		//������״̬�ƿ���
#define TMCC_MINOR_CMD_CLOSELIGHT					0x03		//������״̬�ƹر�
#define TMCC_MINOR_CMD_OPENBUZZER					0x04		//����������������
#define TMCC_MINOR_CMD_CLOSEBUZZER					0x05		//�������������ر�
#define TMCC_MINOR_CMD_GETWORKSTATE					0x06		//�õ�����������״̬
#define TMCC_MINOR_CMD_REMONTCLOSEALARMOUT			0x07		//�ֶ��رձ������
#define TMCC_MINOR_CMD_REMONTOPENALARMOUT			0x08		//�����򿪱������
#define TMCC_MINOR_CMD_RESET						0x09		//ϵͳ��λ
#define TMCC_MINOR_CMD_REMONTVIDEOMOTION			0x0A		//��Ƶ�ƶ������ź�
#define TMCC_MINOR_CMD_REMONTVIDEOLOST				0x0B		//��Ƶ��ʧ�����ź�
#define TMCC_MINOR_CMD_REMONTVIDEOHIDE				0x0C		//��Ƶ�ڵ������ź�
#define TMCC_MINOR_CMD_REQUESTUPGRADE				0x0D		//Զ������
#define TMCC_MINOR_CMD_OPENIRCUT					0x0E		//���˹�Ƭ
#define TMCC_MINOR_CMD_CLOSEIRCUT					0x0F		//�ر��˹�Ƭ
#define TMCC_MINOR_CMD_MANUALCAPTURE				0x10		//Զ���ֶ�ץͼ��������
#define TMCC_MINOR_CMD_AUTOAPERTUREREPAIR			0x11		//�Զ�����Focus��ֵ
#define TMCC_MINOR_CMD_UPGRADEKEEPIP				0x12		//�����IP��ַ��Ϣ
#define TMCC_MINOR_CMD_SYNCNTPSERVER				0x13		//ϵͳ����ͬ��NTP������
#define TMCC_MINOR_CMD_STARTMANUALRECORD			0x14		//���ֶ�¼��
#define TMCC_MINOR_CMD_STOPMANUALRECORD				0x15		//�ر��ֶ�¼��
#define TMCC_MINOR_CMD_HANDLE						0x16		//����
#define TMCC_MINOR_CMD_SAVECONFIGINFO				0x17		//����������Ϣ
#define TMCC_MINOR_CMD_CONTROLSAFEDOOR				0x18		//���ư�ȫ��ʿ��״̬��

#define TMCC_MAJOR_CMD_ALARMCFG 					0x112		//�����������

#define TMCC_MAJOR_CMD_DISKCONTROL					0x113		//���̴�������
#define TMCC_MINOR_CMD_DRIVEINFO					0x01		//�õ�����Ӳ����Ϣ
#define TMCC_MINOR_CMD_DRIVEINIT					0x02		//��ʼ������Ӳ��

//���������չ����
#define TMCC_MAJOR_CMD_NETCFGEX						0x114		//net1=SNTP+..����
#define TMCC_MINOR_CMD_NTPCFG						0x00
#define TMCC_MINOR_CMD_FTPCFG						0x01
#define TMCC_MINOR_CMD_SMTPCFG						0x02
#define TMCC_MINOR_CMD_LIVEHEARTCFG					0x03		//�����
#define TMCC_MINOR_CMD_DDNSCFG						0x04		//DDNS
#define TMCC_MINOR_CMD_UPCFG						0x05		//�豸�����ϴ�����

//ѹ��������չ����
#define TMCC_MAJOR_CMD_COMPRESSCFGA					0x115		//��չѹ������
#define TMCC_MINOR_CMD_COMPRESSCFGA					0x00		//ͼ��ѹ������

#define TMCC_MAJOR_CMD_VIDEOINCFG					0x116		//��Ƶ��������
#define TMCC_MINOR_CMD_VIDEOIN						0x00		//��������

#define TMCC_MAJOR_CMD_SHUTTERCFG					0x117

//ץͼ������
#define TMCC_MAJOR_CMD_CAPTUREIMAGECFG				0x118
#define TMCC_MINOR_CMD_CAPTUREIMAGECFG				0x00		//ץͼ������
#define TMCC_MINOR_CMD_CAPTURESCHEDCFG				0x01		//ʱ�䲼��������

//��Ƶ������������
#define TMCC_MAJOR_CMD_AUDIOCFG                     0x119

//NVRͨ����Ϣ��Ϣ�����������
#define TMCC_MAJOR_CMD_CHANNELCFG                   0x11A       //ͨ������������
#define TMCC_MINOR_CMD_SINGLECHANNEL                0x00        //���õ���ͨ����Ϣ(����/��ȡ)
#define TMCC_MINOR_CMD_ALLCHANNEL                   0x01        //��������ͨ����Ϣ(����/��ȡ)
#define TMCC_MINOR_CMD_SINGLERTSPNAME               0x02        //���õ���ͨ��RTSP���(����/��ȡ)
#define TMCC_MINOR_CMD_ALLRTSPNAME                  0x03        //��������ͨ��RTSP���(����/��ȡ)

//NVR�����ⱨ���豸
#define TMCC_MAJOR_CMD_ALARMDEVICECFG               0x11B       //�����豸����������
#define TMCC_MINOR_CMD_SINGLEALARMDEVICE            0x00        //���õ��������豸��Ϣ(����/��ȡ)
#define TMCC_MINOR_CMD_ALLALARMDEVICE               0x01        //�������б����豸��Ϣ(����/��ȡ)

//�豸��־����
#define TMCC_MAJOR_CMD_LOGCFG						0x11C
#define TMCC_MINOR_CMD_ENUMLOG						0x00		//ö��������־
#define TMCC_MINOR_CMD_CLEARLOG						0x01		//�����־

//��������������
#define TMCC_MAJOR_CMD_CONNECTCFG					0x11D
#define TMCC_MINOR_CMD_CONNECTLISTCFG				0x00		//��������
#define TMCC_MINOR_CMD_CLEARCONNECT					0x01		//����������

//�����γ�����������ӦtmTheodoliteCfg_t�ṹ
#define TMCC_MAJOR_CMD_THEODOLITECFG				0x11E


//////////////////////////////////////////////////////////////////////////////////////
/* �û�Ȩ�޶��� */
#define	TMCC_USERRIGHT_CONTROLPTZ					0x00000001	/*λ0: Զ�̿�����̨*/
#define	TMCC_USERRIGHT_MANUALREC					0x00000002	/*λ1: Զ���ֶ�¼��*/
#define	TMCC_USERRIGHT_PLAYBACK						0x00000004	/*λ2: Զ�̻ط�*/
#define	TMCC_USERRIGHT_SETUP						0x00000008	/*λ3: Զ�����ò�������*/
#define	TMCC_USERRIGHT_LOOKSTAUS					0x00000010	/*λ4: Զ�̲鿴״̬����־*/
#define	TMCC_USERRIGHT_ADVANCE						0x00000020	/*λ5: Զ�̸߼�����(���ʽ�����������ػ�)*/
#define	TMCC_USERRIGHT_TALK							0x00000040	/*λ6: Զ�̷��������Խ�*/
#define	TMCC_USERRIGHT_PREVIEW						0x00000080	/*λ7: Զ��Ԥ��*/
#define	TMCC_USERRIGHT_ALARM						0x00000100	/*λ8: Զ�����󱨾��ϴ����������*/
#define	TMCC_USERRIGHT_CONTROLLOCAL					0x00000200	/*λ9: Զ�̿��ƣ��������*/
#define	TMCC_USERRIGHT_SERIALPORT					0x00000400	/*λ10: Զ�̿��ƴ���*/
#define	TMCC_USERRIGHT_MOTIFYUSER					0x00000800	/*λ11: Զ���޸��û�*/
#define	TMCC_USERRIGHT_MOTIFYSELFPASSWORD			0x00001000	/*λ12: Զ���޸��û��Լ�������*/
#define	TMCC_USERRIGHT_RTSPCONNECT					0x00002000	/*λ13: Զ��RTSP����*/

//�����ļ���״̬
#define	TMCC_PLAY_STATE_STOP						0			//ֹͣ����
#define	TMCC_PLAY_STATE_PAUSE						1			//��ͣ����
#define	TMCC_PLAY_STATE_PLAY						2			//����
#define	TMCC_PLAY_STATE_FAST						3			//���
#define	TMCC_PLAY_STATE_SLOW						4			//���
#define	TMCC_PLAY_STATE_OPEN						5			//���ļ��ɹ�
#define	TMCC_PLAY_STATE_SWITCH						6			//�Ѿ��л��ļ�
#define	TMCC_PLAY_STATE_FILEEND						7			//�ļ�ȫ���������
#define TMCC_PLAY_STATE_STREAMBUFFERRING			8			//���ڻ������
#define TMCC_PLAY_STATE_ENCFMTCHANGE				9			//�����ʽ�ı�

//������Ƶ�����ʽ
#define TMCC_IMAGEOUT_FMT_420P						0
#define TMCC_IMAGEOUT_FMT_RGB15						1
#define TMCC_IMAGEOUT_FMT_RGB16						2
#define TMCC_IMAGEOUT_FMT_RGB24						3
#define TMCC_IMAGEOUT_FMT_RGB32						4
#define TMCC_IMAGEOUT_FMT_YUY2						5
#define TMCC_IMAGEOUT_FMT_YVYU						6
#define TMCC_IMAGEOUT_FMT_UYVY						7
#define TMCC_IMAGEOUT_FMT_420P2						8
#define TMCC_IMAGEOUT_FMT_422P						9
#define TMCC_IMAGEOUT_FMT_422P2						10
#define TMCC_IMAGEOUT_FMT_H264						11
#define TMCC_IMAGEOUT_FMT_MJPEG						12

#define TMCC_ERR_SUCCESS						    0x00000000
#define TMCC_ERR_HANDLE_INVALID						0xC0000001
#define TMCC_ERR_PARAMETER_INVALID					0xC0000002
#define TMCC_ERR_MEMORY_OUT							0xC0000003
#define TMCC_ERR_THREAD_CREATE						0xC0000004
#define TMCC_ERR_THREAD_START						0xC0000005
#define TMCC_ERR_THREAD_STOP						0xC0000006
#define TMCC_ERR_SOCKET_CREATE						0xC0000007
#define TMCC_ERR_SERVERNOCONFIG 					0xC0000008
#define TMCC_ERR_SERVEREXCEPTION 					0xC0000009
#define TMCC_ERR_USERNOTLOGIN 						0xC000000A
#define TMCC_ERR_NOTSETUP 						    0xC000000B
#define TMCC_ERR_NOTDISCONNECT					    0xC000000C
#define TMCC_ERR_NETWORK_FAIL_CONNECT			    0xC000000D
#define TMCC_ERR_NETWORK_SEND_ERROR				    0xC000000E
#define TMCC_ERR_NETWORK_RECV_ERROR				    0xC000000F
#define TMCC_ERR_NETWORK_RECV_TIMEOUT			    0xC0000010
#define TMCC_ERR_NETWORK_ERRORDATA				    0xC0000011
#define TMCC_ERR_NETWORK_SERVERNOSTART			    0xC0000012
#define	TMCC_ERR_OPERNOTFINISH					    0xC0000013
#define TMCC_ERR_NOENOUGH_BUF					    0xC0000014
#define TMCC_ERR_COMMAND_INVALID				    0xC0000015
#define TMCC_ERR_UPGRADEFILENOTOPEN				    0xC0000016
#define TMCC_ERR_UPGRADESIZELARG				    0xC0000017
#define TMCC_ERR_UPGRADEPARITY					    0xC0000018
#define TMCC_ERR_UPGRADEFILENOTREAD				    0xC0000019
#define TMCC_ERR_STRUCTSIZE						    0xC000001A
#define TMCC_ERR_DATACRC						    0xC000001B
#define	TMCC_ERR_USEREXIST						    0xC000001D
#define	TMCC_ERR_USERMAXNUM						    0xC000001E
#define TMCC_ERR_NOINIT 						    0xC000001F
#define TMCC_ERR_CHANNEL_ERROR 					    0xC0000020
#define TMCC_ERR_OVER_MAXLINK 					    0xC0000021
#define TMCC_ERR_VERSIONNOMATCH					    0xC0000022
#define TMCC_ERR_ORDER_ERROR					    0xC0000023
#define TMCC_ERR_OPERNOPERMIT					    0xC0000024
#define TMCC_ERR_COMMANDTIMEOUT					    0xC0000025
#define TMCC_ERR_ERRORSERIALPORT				    0xC0000026
#define TMCC_ERR_ERRORALARMPORT					    0xC0000027
#define TMCC_ERR_PARAMETER_ERROR 				    0xC0000028
#define TMCC_ERR_CHAN_EXCEPTION					    0xC0000029
#define TMCC_ERR_NODISK							    0xC000002A
#define TMCC_ERR_ERRORDISKNUM					    0xC000002B
#define TMCC_ERR_DISK_FULL						    0xC000002C
#define TMCC_ERR_DISK_ERROR						    0xC000002D
#define TMCC_ERR_NOSUPPORT						    0xC000002E
#define TMCC_ERR_BUSY							    0xC000002F
#define TMCC_ERR_MODIFY_FAIL					    0xC0000030
#define TMCC_ERR_PASSWORD_FORMAT_ERROR			    0xC0000031
#define TMCC_ERR_DISK_FORMATING					    0xC0000032
#define TMCC_ERR_DVRNORESOURCE					    0xC0000033
#define	TMCC_ERR_DVROPRATEFAILED				    0xC0000034
#define TMCC_ERR_OPENHOSTSOUND_FAIL 			    0xC0000035
#define TMCC_ERR_DVRVOICEOPENED 				    0xC0000036
#define	TMCC_ERR_TIMEINPUTERROR					    0xC0000037
#define	TMCC_ERR_NOSPECFILE						    0xC0000038
#define TMCC_ERR_CREATEFILE_ERROR				    0xC0000039
#define	TMCC_ERR_FILEOPENFAIL					    0xC000003A
#define	TMCC_ERR_GETPLAYTIMEFAIL				    0xC000003B
#define	TMCC_ERR_PLAYFAIL						    0xC000003C
#define TMCC_ERR_FILEFORMAT_ERROR				    0xC000003D
#define TMCC_ERR_DIR_ERROR						    0xC000003E
#define TMCC_ERR_ALLOC_RESOUCE_ERROR			    0xC000003F
#define TMCC_ERR_AUDIO_MODE_ERROR				    0xC0000040
#define TMCC_ERR_CREATESOCKET_ERROR				    0xC0000042
#define TMCC_ERR_SETSOCKET_ERROR				    0xC0000043
#define TMCC_ERR_MAX_NUM						    0xC0000044
#define TMCC_ERR_USERNOTEXIST					    0xC0000045
#define TMCC_ERR_WRITEFLASHERROR				    0xC0000046
#define TMCC_ERR_UPGRADEFAIL					    0xC0000047
#define TMCC_ERR_CARDHAVEINIT					    0xC0000048
#define TMCC_ERR_PLAYERFAILED					    0xC0000049
#define TMCC_ERR_MAX_USERNUM					    0xC000004A
#define TMCC_ERR_GETLOCALIPANDMACFAIL			    0xC000004B
#define TMCC_ERR_NOENCODEING					    0xC000004C
#define TMCC_ERR_IPMISMATCH						    0xC000004D
#define TMCC_ERR_MACMISMATCH					    0xC000004E
#define TMCC_ERR_UPGRADELANGMISMATCH			    0xC000004F
#define TMCC_ERR_PASSWORDVERIFY					    0xC0000050
#define TMCC_ERR_USERLOGIN						    0xC0000051
#define TMCC_ERR_CANNOTDELETEUSER				    0xC0000052
#define TMCC_ERR_MODALNOTEXIST					    0xC0000053
#define TMCC_ERR_SERVERSTARTTING				    0xC0000054
#define TMCC_ERR_CHANNELPTZOPEN					    0xC0000055
#define TMCC_ERR_PTZCONTROLNOTOPEN				    0xC0000056
#define TMCC_ERR_GETPTZCONTROL					    0xC0000057
#define TMCC_ERR_SERIALDATASIZE						0xC0000058
#define TMCC_ERR_PTZOPENED						    0xC0000059
#define TMCC_ERR_PTZLOCKED						    0xC000005A
#define TMCC_ERR_NOVOICEFUNCTION				    0xC000005B
#define TMCC_ERR_VOICEHAVECONNECT				    0xC000005C
#define TMCC_ERR_VOICENOTOPEN					    0xC000005D
#define TMCC_ERR_INUPGRADE						    0xC000005E
#define TMCC_ERR_ALARMINCHANNEL					    0xC000005F
#define TMCC_ERR_SERIALHAVEOPEN					    0xC0000060
#define TMCC_ERR_SERIALNOTOPEN					    0xC0000061
#define TMCC_ERR_NOTOPENUPGRADEMODAL				0xC0000062
#define TMCC_ERR_UPGRADEMODALNOSUPPORR				0xC0000063
#define TMCC_ERR_OPENUPGRADEMODALWRITE				0xC0000064
#define TMCC_ERR_UPGRADEMODALNOTREAD				0xC0000065
#define TMCC_ERR_HTTPPORTIS6000						0xC0000066
#define TMCC_ERR_VIDEOSTANDARD						0xC0000067
#define TMCC_ERR_DELETETODAYLOG						0xC0000068
#define TMCC_ERR_NOENOUGH_DATA						0xC0000069
#define TMCC_ERR_WRITEFILE							0xC000006A
#define TMCC_ERR_READFILE							0xC000006B
#define TMCC_ERR_FILEEND							0xC000006C
#define TMCC_ERR_FILEINDEX							0xC000006D
#define TMCC_ERR_CAPTUREIMAGE						0xC000006E

#define ERROR_CODE_HANDLE							0xC0000010
#define ERROR_CODE_INVALID_HANDLE					0xc0000010
#define ERROR_CODE_PARAM							0xC0000011
#define ERROR_CODE_CREATETHREAD						0xC0000012
#define ERROR_CODE_CREATESOCKET						0xC0000013
#define ERROR_CODE_OUTMEMORY						0xC0000014
#define ERROR_CODE_MORECHANNEL						0xC0000015
#define ERROR_CODE_CHANNELMAGIC_MISMATCH			0xc0000016
#define ERROR_CODE_CALLBACK_REGISTERED				0xc0000017
#define ERROR_CODE_QUEUE_OVERFLOW					0xc0000018
#define ERROR_CODE_STREAM_THREAD_FAILURE			0xc0000019
#define ERROR_CODE_THREAD_STOP_ERROR				0xc000001A
#define ERROR_CODE_NOT_SUPPORT						0xc000001B
#define ERROR_CODE_WAIT_TIMEOUT						0xc000001C
#define ERROR_CODE_INVALID_ARGUMENT					0xc000001D
#define ERROR_CODE_INVALID_INTERFACE				0xc000001E

#define ERROR_CODE_BEGINCONNECT						0xC0001000
#define ERROR_CODE_CONNECTSUCCESS					0xC0001001
#define ERROR_CODE_NETWORK							0xC0001002
#define ERROR_CODE_CONNECTERROR						0xC0001003
#define ERROR_CODE_CONNECTERROR_1000				0xC0001004
#define ERROR_CODE_SERVERSTOP						0xC0001005
#define ERROR_CODE_SERVERSTOP_1000					0xC0001006
#define ERROR_CODE_TIMEOUT							0xC0001007
#define ERROR_CODE_TIMEOUT_1000						0xC0001008
#define ERROR_CODE_SENDDATA							0xC0001009
#define ERROR_CODE_SENDDATA_1000					0xC000100A
#define ERROR_CODE_RECVDATA							0xC000100B
#define ERROR_CODE_RECVDATA_1000					0xC000100C

#define ERROR_CODE_CLOSECONNECT						0xC0010000
#define ERROR_CODE_SERVERNOSTART					0xC0010001
#define ERROR_CODE_SERVERERROR						0xC0010002
#define ERROR_CODE_CHANNELLIMIT 					0xC0010003
#define ERROR_CODE_SERVERLIMIT						0xC0010004
#define ERROR_CODE_SERVERREFUSE						0xC0010005
#define ERROR_CODE_IPLIMIT							0xC0010006
#define ERROR_CODE_PORTLIMIT						0xC0010007
#define ERROR_CODE_TYPEERROR						0xC0010008
#define ERROR_CODE_USERERROR						0xC0010009
#define ERROR_CODE_PASSWORDERROR					0xC001000A
#define ERROR_CODE_DONTTURN							0xC001000B
#define ERROR_CODE_VERSION							0xC0100000
#define ERROR_CODE_FACTORY							0xC0100001

#endif	/*__TMTRANSEDEFINE_H__*/
