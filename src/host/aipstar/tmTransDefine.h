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
	unsigned short	wYear;			
	unsigned char	byMonth;		
	unsigned char	byDay;			
	unsigned char	byHour;		
	unsigned char	byMinute;	
	unsigned char	bySecond;	
	unsigned char	byTemp;		
	unsigned int	dwMicroSecond;	
}tmTimeInfo_t;

typedef struct tmSchedTime_t
{
	unsigned int	dwSize;
    unsigned char	byStartHour;
	unsigned char	byStartMin;
	unsigned char	byStopHour;
	unsigned char	byStopMin;
}tmSchedTime_t;


#define NOACTION			0x00			
#define WARNONMONITOR		0x01				
#define WARNONAUDIOOUT		0x02			
#define UPTOCENTER			0x04			
#define TRIGGERALARMOUT		0x08			
#define UPTOCTRLCLIENT		0x10		
#define UPTOAVCLIENT		0x20				
typedef struct tmHandleException_t
{
	unsigned char		byRelAlarmOutEnable[4];	
	unsigned int		dwHandleType;		
	unsigned char		byRelAlarmOut[4];		
}tmHandleException_t;


typedef struct tmTransFer_t
{
	unsigned char	byTransFerType;		
	unsigned char	byChannel;			
	unsigned char	byTemp[2];				
	unsigned char	byEnableRelRecordChan;	
	unsigned char	byEnablePreset;		
	unsigned char	byPresetNo;				
	unsigned char	byEnableCruise;		
	unsigned char	byCruiseNo;				
	unsigned char	byEnablePtzTrack;		
	unsigned char	byPTZTrack;				
	unsigned char	byEnableCaptureChan;	
}tmTransFer_t;


typedef struct tmAreaScope_t
{
	unsigned short	wAreaTopLeftX;		
	unsigned short	wAreaTopLeftY;		
	unsigned short	wAreaWidth;			
	unsigned short	wAreaHeight;	
}tmAreaScope_t;

typedef struct tmMotion_t
{
	unsigned int			dwSize;	
	unsigned char			byMotionScopeNum;						
	tmAreaScope_t			struMotionScope[5];							
	unsigned char			byMotionSensitive;						
	unsigned char			byMotionThreshold;							
																		
	unsigned char			byEnableHandleMotion;						
	tmHandleException_t		strMotionHandleType;						
	tmSchedTime_t			struAlarmTime[7][4];						
	tmTransFer_t			struAlarmTransFer[16];					
}tmMotion_t;

/* �ƶ���� */
typedef struct tmVideoMotionCfg_t
{
	unsigned int			dwSize;	
	tmAreaScope_t			struMotionScope[5];							
	unsigned char			byMotionScopeNum;							
	unsigned char			byMotionSensitive;							
	unsigned char			byMotionThreshold;							
	unsigned char			byEnableHandleMotion;						
	tmHandleException_t		strMotionHandleType;						
	tmSchedTime_t			struAlarmTime[7][4];						
	tmTransFer_t			struAlarmTransFer[16];						
}tmVideoMotionCfg_t;

typedef struct tmHideAlarm_t
{
	unsigned int			dwSize;
	unsigned char			byHideSensitive;			
	tmAreaScope_t			struHideAlarmArea;			
	unsigned char			byEnableHandleHideAlarm;	
	tmHandleException_t		strHideAlarmHandleType;		
	tmSchedTime_t			struAlarmTime[7][4];	
}tmHideAlarm_t;

typedef struct tmVideoHideCfg_t
{
	unsigned int			dwSize;
	tmAreaScope_t			struHideAlarmArea;			
	unsigned char			byHideSensitive;			
	unsigned char			byEnableHandleHideAlarm;	
	unsigned char			byTemp[2];
	tmHandleException_t		strHideAlarmHandleType;		
	tmSchedTime_t			struAlarmTime[7][4];		
}tmVideoHideCfg_t;

typedef struct tmViLost_t
{
	unsigned int			dwSize;
	unsigned char			byEnableHandleVILost;		
	tmHandleException_t		strVILostHandleType;		
	tmSchedTime_t			struAlarmTime[7][4];		
}tmViLost_t;

typedef struct tmVideoLostCfg_t
{
	unsigned int			dwSize;
	unsigned char			byEnableHandle;				
	unsigned char			byTemp[3];
	tmHandleException_t		strHandleType;			
	tmSchedTime_t			struAlarmTime[7][4];		
}tmVideoLostCfg_t;

typedef struct tmVideoMaskCfg_t
{
	unsigned int			dwSize;
	unsigned char			byEnableMask;				
	unsigned char			byTemp[3];
	tmAreaScope_t			struHideArea[4];			
}tmVideoMaskCfg_t;

typedef struct tmPicPreviewCfg_t
{
	unsigned int			dwSize;
	unsigned int			dwVideoFormat;				
	short					byBrightness;  				
	short					byContrast;    				
	short					bySaturation;  				
	short					byHue;    					
	short					byAcutance;					  
}tmPicPreviewCfg_t;

typedef struct tmPicPreviewInfo_t
{
	unsigned char	byBrightness;
	unsigned char	byContrast;
	unsigned char	bySaturation;
	unsigned char	byHue;
}tmPicPreviewInfo_t;

typedef struct tagPicModeScheduleInfo_t
{
	unsigned char		byStartHour;      
	unsigned char		byStartMin;
	unsigned char		byStopHour;
	unsigned char		byStopMin;
	
	unsigned char		byEnable;         
	unsigned char		byMode;  
	unsigned char		byAcutance;
	unsigned char		byReverse[1];     
}tmPicModeScheduleInfo_t;

typedef struct tagPicModeScheduleCfg_t
{
	unsigned int				dwSize ;
	tmPicPreviewInfo_t			struMode[4];                  
	tmPicModeScheduleInfo_t     struModeSched[4];   
	
}tmPicModeScheduleCfg_t;

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

typedef struct tmVideoOsdCfg_t
{
	unsigned int			dwSize;

	char					sChanName[64];				
	unsigned short			wShowNameTopLeftX;			
	unsigned short			wShowNameTopLeftY;			
	unsigned char			byShowChanName;			
	unsigned char			byNameCoordinateMode;		

	unsigned short			wShowTimeTopLeftX;		
	unsigned short			wShowTimeTopLeftY;			
	unsigned char			byShowTime;					
	unsigned char			byTimeType;					
														
	unsigned char			byShowWeek;					
	unsigned char			byWeekType;					
	unsigned char			byTimeCoordinateMode;	

	unsigned char			byOsdAttrib;				
	unsigned char			byFontMode;					
	unsigned char			byAlignMode;			
	unsigned char			byTemp[2];

	char					sShowText[256];				
	unsigned short			wShowTextTopLeftX;			
	unsigned short			wShowTextTopLeftY;			
	unsigned char			byShowText;					
	unsigned char			byTextCoordinateMode;										
}tmVideoOsdCfg_t;

typedef struct tmPicCfg_t
{
	unsigned int			dwSize;
	char					sChanName[32];
	unsigned int			dwVideoFormat;				

	unsigned int			dwShowChanName;				
	unsigned short			wShowNameTopLeftX;			
	unsigned short			wShowNameTopLeftY;			
	unsigned char			byShowNamAttrib;			

	tmViLost_t				struVILost;
	tmMotion_t				struMotion;	
	tmHideAlarm_t			struHideAlarm;
	unsigned char			dwEnableHide;				
	tmAreaScope_t			struHideArea;				

	unsigned int			dwShowOsd;					
	unsigned short			wOSDTopLeftX;				
	unsigned short			wOSDTopLeftY;				
	unsigned char			byOSDType;					
	unsigned char			byDispWeek;					
	unsigned char			byOSDAttrib;				
	char					sWeekName[7][20];			

	unsigned char			byEnableStreamNum;			
}tmPicCfg_t;

typedef struct tmCompression_t
{
	unsigned char		byCompressFormat;
	unsigned char		byKeyFrameInterval;
	unsigned char		byDisplayFrame;
	unsigned char		byTemp[1];
	unsigned char		byStreamType;

	unsigned char		byResolution;
	unsigned char		byBitrateType;

	unsigned char		byPicQuality;
	unsigned int		dwVideoBitrate; 
	unsigned int		dwVideoFrameRate;
}tmCompression_t;

typedef struct tmCompressionCfg_t
{
	unsigned int			dwSize;
	tmCompression_t			struRecordPara;		
	tmCompression_t			struNetPara;
	tmCompression_t			struThirdPara;
	unsigned char			byFormatId;
	unsigned char			byTemp[3];
}tmCompressionCfg_t;

typedef struct tmStreamDescription_t
{
	unsigned char			byResolution;			
	unsigned char			byFormat;				
	unsigned char			byFrameRateNum;			
	unsigned char			byType;					
	unsigned char			byFramesRateList[32];	
	unsigned int			dwMaxBitRate;			
	unsigned int			dwDisplayRatio;			
}tmStreamDescription_t;

typedef struct tmCompressCapability_t
{
	char					sName[64];			
	unsigned char			byFormatId;		
	unsigned char			byStreamCount;		
	unsigned char			byTemp[2];
	tmStreamDescription_t	struStreamFormat[4];
}tmCompressCapability_t;

typedef struct tmCompressCapabilityCfg_t
{
	unsigned int			dwSize;				
	unsigned int			dwCount;			
	tmCompressCapability_t	struCapability[1];
}tmCompressCapabilityCfg_t;

typedef struct tmAudioCfg_t
{
	unsigned int		dwSize;
	unsigned char		byCompressFormat;
	unsigned char		byChannelMode;
	unsigned char		byBitRate;
	unsigned char		bySamplesRate;
	unsigned int		dwLampFactor;
}tmAudioCfg_t;

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

typedef struct tmCaptureImageCfg_t
{
	unsigned int		dwSize;
	unsigned char		byFormat;
	unsigned char		bySaveMode;
	unsigned char		byCaptureNum;
	unsigned char		byEnableDirectory;
	unsigned int		dwCaptureInterval;

	char				sFTPServerIpAddr[128];
	unsigned int		dwFTPServerPort;
	char				sFTPCliUserName[16];
	char				sFTPCliUserPass[16];
	
	char				sDirectoryName[128];
}tmCaptureImageCfg_t;
#define CAPTUREIMAGE_MODE_SAVE			0x00
#define CAPTUREIMAGE_MODE_FTP			0x01
#define CAPTUREIMAGE_MODE_SERVER		0x02
#define CAPTUREIMAGE_MODE_SAVEANDFTP	0x03
#define CAPTUREIMAGE_MODE_SAVEANDSERVER	0x04

typedef struct tmCaptureSchedCfg_t
{
	unsigned int				dwSize;
	tmSchedTime_t				struCaptureSched[MAX_DAYS][MAX_TIMESEGMENT];
	unsigned int				dwCaptureTime;					
	unsigned char				byCaptureStream;
	unsigned char				byEnableCapture;	
}tmCaptureSchedCfg_t;

/*----------------------------------------------------------------------*/

#define PTZ_REALTRANS			0	
#define PTZ_LIGHT_PWRON			2	
#define PTZ_WIPER_PWRON			3	
#define PTZ_FAN_PWRON			4
#define PTZ_HEATER_PWRON		5	
#define PTZ_AUX_PWRON			6

#define PTZ_FOCUS_AUTO			7	

#define PTZ_ZOOM_IN				11	
#define PTZ_ZOOM_OUT			12	
#define PTZ_FOCUS_NEAR			13
#define PTZ_FOCUS_FAR			14
#define PTZ_IRIS_ENLARGE		15
#define PTZ_IRIS_SHRINK			16
#define PTZ_UP					21
#define PTZ_DOWN				22
#define PTZ_LEFT				23
#define PTZ_RIGHT				24
#define PTZ_RIGHTUP				25
#define PTZ_RIGHTDOWN			26
#define PTZ_LEFTUP				27
#define PTZ_LEFTDOWN			28
#define PTZ_AUTO				29

#define PTZ_485INPUT			31	
#define PTZ_485OUTPUT			32	
#define PTZ_SET_KEEPWATCH		33	
#define PTZ_GOTO_KEEPWATCH		34	
#define PTZ_LOCK_KEEPWATCH		35
#define PTZ_UNLOCK_KEEPWATCH	36

#define PTZ_SET_PRESET			100	
#define PTZ_CLE_PRESET			101	
#define PTZ_GOTO_PRESET			102	

#define PTZ_STARTREC_TRACK		110	
#define PTZ_STOPREC_TRACK		111	
#define PTZ_STARTRUN_TRACK		112	
#define PTZ_STOPRUN_TRACK		113	

#define PTZ_STARTREC_CRUISE		120	
#define PTZ_STOPREC_CRUISE		121	
#define PTZ_STARTRUN_CRUISE		122	
#define PTZ_STOPRUN_CRUISE		123	

#define PTZ_INTEGRATE_CONTROL	124	

typedef struct tmDecoderCfg_t
{
	unsigned int			dwSize;
	unsigned int			dwBaudRate;				
	unsigned char			byDataBit;		
	unsigned char			byStopBit;		
	unsigned char			byParity;		
	unsigned char			byFlowcontrol;	
	unsigned short			wDecoderType;		
	unsigned short			wDecoderAddress;	
	char					szDecoderName[20];	
	unsigned short			wTrackStopTime;		
	unsigned char			bySetCruise[16];		
	unsigned char			bySetPreset[16];		
	unsigned char			bySetTrack[16];	
}tmDecoderCfg_t;

typedef struct tmDecoderInfo_t
{
	unsigned int			dwSize;
	char					szDecoderName[20];				
}tmDecoderInfo_t;

typedef struct tmPresetInfo_t
{
	char			szPresetName[32];		
	unsigned char	byEnable;			
	unsigned char	byTemp[3];				
}tmPresetInfo_t;

typedef struct tmPresetCfg_t
{
	unsigned int	dwSize;					
	tmPresetInfo_t	pPresetList[128];		
}tmPresetCfg_t;

typedef struct tmCruisePoint_t
{
	unsigned char	byEnable;				
	unsigned char	byPresetNo;				
	unsigned char	byCruiseSpeed;			
	unsigned char	byTemp;					
	unsigned int	dwStopTime;				
}tmCruisePoint_t;

typedef struct tmCruiseInfo_t
{
	unsigned char	byEnableThisCruise;		
	unsigned char	byTemp[3];
	tmCruisePoint_t	struCruise[16];			
}tmCruiseInfo_t;

typedef struct tmCruiseCfg_t
{
	unsigned int	dwSize;					
	tmCruiseInfo_t	struCruiseLine[CRUISE_MAX_LINE_NUMS];
}tmCruiseCfg_t;

typedef struct tmPtzSchedTime_t
{
	tmSchedTime_t	struSchedTime;
	unsigned char	byRunType;				
	unsigned char	byRunLine;				
	unsigned char	byTemp[2];
}tmPtzSchedTime_t;

typedef struct tmPtzSchedCfg_t
{
	unsigned int		dwSize;										
	unsigned char		byEnableKeepWatch;						
	unsigned char		byEnableSchedTime;							
	unsigned short		dwKeepWatchCheckTime;						
	tmPtzSchedTime_t	struSchedTime[MAX_DAYS][MAX_TIMESEGMENT];	
	unsigned char		byLimitSpeed[64];							
	unsigned char		byDisplayPtzInfo;						
	unsigned char		byDisplayX;								
	unsigned char		byDisplayY;									
	unsigned char		byDisplayMode;								
}tmPtzSchedCfg_t;

typedef struct tmPPPCfg_t
{
	unsigned int	dwSize;
	char			sRemoteIP[24];						
	unsigned char	byTemp1;
	char			sLocalIP[24];						
	unsigned char	byTemp2;
	char			sLocalIPMask[24];					
	unsigned char	byTemp3;
	char			szUserName[32];						
	char			szPassword[32];						
	unsigned char	byPPPMode;							
	unsigned char	byRedial;							
	unsigned char	byRedialMode;					
	unsigned char	byDataEncrypt;						
	unsigned char	byTemp4;							
	unsigned int	dwMTU;								
	char			sTelephoneNumber[32];			
}tmPPPCfg_t;

typedef struct tmRS2322Cfg_t
{
	unsigned int		dwSize;
	unsigned int		dwBaudRate;			
	unsigned char		byDataBit;				
	unsigned char		byStopBit;			
	unsigned char		byParity;				
	unsigned char		byFlowcontrol;			
	unsigned int		dwWorkMode;		
	tmPPPCfg_t			struPPPConfig;
}tmRS2322Cfg_t;

typedef struct tmAlarmInCfg_t
{
	unsigned int			dwSize;
	char					sAlarmInName[32];						
	unsigned char			byAlarmType;								
	unsigned char			byAlarmInHandle;							
	tmHandleException_t		struAlarmHandleType;						
	tmSchedTime_t			struAlarmTime[7][4];						
	tmTransFer_t			struAlarmTransFer[16];						
}tmAlarmInCfg_t;

typedef struct tmAlarmOutCfg_t
{
	unsigned int			dwSize;
	unsigned char			sAlarmOutName[32];							
	unsigned int			dwAlarmOutDelay;							
	tmSchedTime_t			struAlarmTime[7][4];					
	unsigned char			byAlarmType;								
	unsigned char			byTemp[2];									
	unsigned char			dwSchedTimType;								
}tmAlarmOutCfg_t;

typedef struct tmAlarmCfg_t
{
	unsigned int	dwSize;			
	unsigned int	dwUpToTime;															
	unsigned int	dwAlarmAudioTimeout;			
	unsigned int	dwPtzControlTimeout;			
	unsigned int	dwConfigTimeout;				
	unsigned int	dwSerialTimeout;				

	unsigned char	byAllowSoftReset;				
	unsigned char	byAllowConfigTinmeout;			
	unsigned char	byAllowAutoReset;				
	unsigned char	byAllowConfigBeep;				

	unsigned char	byAutoResetMode;				
	unsigned char	byAlarmToManagerType;			
	unsigned char	byRecoderFileSize;				
	unsigned char	byNormalRecoder;				

	unsigned int	dwDDNSLoginTimeOut;				
	
	unsigned int	dwAutoResetCircleTime;			
	unsigned int	dwAutoResetFlags;			
	unsigned short	wTranstStreamSize;
	unsigned char	byEnableWriteFileState;	
	unsigned char	byUpFileStateToManager;
	unsigned char	byLogRemainDays;
	unsigned char	byEnableSDCardRecord;
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

typedef struct tmAlaramInfo_t
{
	unsigned int	dwSize;
	unsigned short  wAlarmType;							
	unsigned short  wAlarmState;						
	unsigned int	dwAlarmChannel;						
	unsigned int	dwAlarmOutputNumber[4];				
	unsigned int	dwAlarmRelateChannel[16];			
	unsigned int	dwDiskNumber[16];				
}tmAlaramInfo_t;

typedef struct tmToManagerAlarmInfo_t
{
	unsigned int		dwSize;
	tmAlaramInfo_t		struAlarmInfo;
	char				szDVSName[32];					
	unsigned char		szSerialNumber[48];				
	unsigned char		szServerGUID[16];			
	unsigned char		byMACAddr[6];				
	char				szServerIP[16];				
	char				szServerMask[24];			
	unsigned char		byTemp[4];
}tmToManagerAlarmInfo_t;

typedef struct tmToManagerImageInfo_t
{
	unsigned int		dwSize;							
	struct
	{
		short			nWidth;						
		short			nHeight;						
		unsigned char	byBitCount;						
		unsigned char	byRevolving;					
		unsigned char	byTemp[2];
	}image;
	BYTE				byTemp1[8];
	unsigned char		byMACAddr[6];					
	unsigned char		byTemp2[2];						
	char				szServerIP[16];					
	unsigned char		byImageFmt;						
	unsigned char		byCount;						
	unsigned char		byIndex;						
	unsigned char		byImageMode;					
	unsigned char		byAlarmId;						
	unsigned char		byChannelId;					
	unsigned char		byOtherInfo[2];					
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
	unsigned int		dwImageSize;				
}tmToManagerImageInfo_t;

typedef struct tmToManagerLiveHeartInfo_t
{
	unsigned int		dwSize;							
	unsigned short		nDeviceType;					
	unsigned short		nFactoryId;						
	unsigned short		nDevicePort;					
	unsigned int		nDeviceAddress;					
	unsigned char		nDeviceGUID[16];				
	unsigned char		nChannelCount;		
	unsigned char		nAlarmInCount;
	unsigned char		nAlarmOutCount;
	unsigned char		nDiskCount;
	unsigned char		nDeviceSubType;
	unsigned char		nMarkAddress[6];	
	char				nDeviceName[32];
}tmToManagerLiveHeartInfo_t;

typedef struct tmToManagerSafeGuardInfo_t
{
	unsigned int		dwSize;				
	unsigned int		nDeviceAddress;	
	unsigned short		nDevicePort;					
	unsigned char		nMarkAddress[6];	
	
	unsigned char		byLightState;
	unsigned char		byTalkState;
	unsigned char		byBuFangState;
	unsigned char		byCheFangState;
	unsigned char		byAlarmState;	
	unsigned char		byInfraredState;
	unsigned char		byCardEnable;
	unsigned int		dwCardNo;
}tmToManagerSafeGuardInfo_t;

typedef struct tmServerInfo_t
{
	unsigned int		dwSize;							
	unsigned char		bServerConnect;					
	char				szDVSName[32];					
	unsigned char		szSerialNumber[48];				
	unsigned char		szServerGUID[16];				
	unsigned char		byMACAddr[6];					
	char				szServerIP[25];					
	char				szServerMask[25];				
	char				szCenterManagerIP[25];			
	unsigned char		byCenterManager;				

	unsigned char		byAlarmInNum;				
	unsigned char		byAlarmOutNum;				
	unsigned short		wChannelNum;				

	unsigned int		dwServerType;					
	unsigned short		wDVSPort;						
	unsigned short		wHttpPort;						
	unsigned int		dwGroupID;						
	unsigned int		dwSoftwareVersion;				
	unsigned int		dwPanelVersion;					
	unsigned int		dwHardwareVersion;				
	unsigned int		dwFactoryNo;					
}tmServerInfo_t;

typedef struct tmServerInfoEx_t
{
	unsigned int		dwSize;							
	unsigned char		bServerConnect;				
	char				szDVSName[32];					
	unsigned char		szSerialNumber[48];				
	unsigned char		szServerGUID[16];				
	unsigned char		byMACAddr[6];					
	char				szServerIP[25];					
	char				szServerMask[25];				
	char				szCenterManagerIP[25];			
	unsigned char		byCenterManager;				

	unsigned char		byAlarmInNum;					
	unsigned char		byAlarmOutNum;					
	unsigned short		wChannelNum;					

	unsigned int		dwServerType;					
	unsigned short		wDVSPort;						
	unsigned short		wHttpPort;						
	unsigned int		dwGroupID;						
	unsigned int		dwSoftwareVersion;				
	unsigned int		dwPanelVersion;					
	unsigned int		dwHardwareVersion;				
	unsigned int		dwFactoryNo;					
	unsigned int		dwRunTime;						

	unsigned short		wCurrentDVSPort;				
	unsigned short		wCurrentHttpPort;			
	unsigned int		dwCurrentServerIP;				
	unsigned int		dwCurrentServerMask;			

	unsigned int		dwServerGateWay;				
	unsigned char		byEnableDhcp;					
	unsigned char		byEtherNet;						
	unsigned char		byWifi;							

}tmServerInfoEx_t;

typedef struct tmServerCfg_t
{
	unsigned int		dwSize;							
	tmServerInfo_t		pInfo[1];						
	unsigned int		dwMajorCommand;					
	unsigned int		dwMinorCommand;			
	char				szUserName[32];					
	char				szPassword[32];				
	int					iConfigMode;				
	unsigned int		dwResverse;						
	unsigned int		dwResverse1;					
}tmServerCfg_t;

typedef struct tmServerExCfg_t
{
	unsigned int		dwSize;							
	tmServerInfo_t		pInfo[1];						
	unsigned int		dwMajorCommand;					
	unsigned int		dwMinorCommand;				
	char				szUserName[32];					
	char				szPassword[32];					
	unsigned char		iConfigMode;				
	unsigned char		bControlAll;				
	unsigned char		bTemp[2];					
	unsigned int		dwResverse;						
	unsigned int		dwResverse1;					
	tmServerInfoEx_t	pInfoEx[1];						
}tmServerExCfg_t;

typedef struct tmMultiServerCfg_t
{
	unsigned int		dwSize;							
	unsigned int		dwMajorCommand;					
	unsigned int		dwMinorCommand;					
	char				szUserName[32];					
	char				szPassword[32];					
	unsigned int		dwCompareSerialNumber;			
	char				szSerialNumber[48];				
}tmMultiServerCfg_t;

typedef struct tmChannelState_t
{
	unsigned int		dwSize;
	unsigned char		byRecordStatic;			
	unsigned char		bySignalStatic;				
	unsigned char		byHardwareStatic;			
	unsigned char		reservedData;
	unsigned int		dwBitRate;					
	unsigned int		dwLinkNum;					
	unsigned int		dwClientIP[6];				
}tmChannelState_t;

typedef struct tmDiskState_t
{
	unsigned int		dwSize;
	unsigned int		dwVolume;							
	unsigned int		dwFreeSpace;						
	unsigned int		dwHardDiskStatic;				
}tmDiskState_t;

typedef struct tmUserState_t
{
	unsigned int		dwSize;
	char				szUserName[32];				
	unsigned int		dwLoginNum;					
	unsigned int		dwLoginAddress[16];		
}tmUserState_t;

typedef struct tmWorkState_t
{
	unsigned int		dwSize;
	unsigned int		dwDeviceRunTime;				
	unsigned int		dwDeviceStatic; 				
	tmDiskState_t		struHardDiskStatic[16];		 
	tmChannelState_t	struChanStatic[16];				
	tmUserState_t		struUserStatic[16];				
	unsigned char		byAlarmInStatic[16];		
	unsigned char		byAlarmOutStatic[4];			

	unsigned int		dwCpuClockFrequency;			
	unsigned int		dwTotalMemorySize;			
	unsigned int		dwFreeMemorySize;				
}tmWorkState_t;

typedef struct tmPtzParameter_t
{	
	unsigned int		dwAutoStopTime;			
	unsigned int		dwZoomValue;				
	unsigned int		dwVerticallyAngle;				
	unsigned int		dwHorizontallyAngle;			
	unsigned char		byZoomMode;					
	unsigned char		byVerticallyMode;				
	unsigned char		byHorizontallyMode;			
	unsigned char		byControlMode;		
}tmPtzParameter_t;

typedef struct tmPtzCommandCfg_t
{
	unsigned int			dwSize;						
	unsigned int			dwPTZCommand;				
	unsigned int			dwPTZControl;			
	unsigned int			dwAddress;
	unsigned int			dwSpeed;
	int						iPTZCodeLen;			
	union
	{
		unsigned char		pPTZCodeBuf[128];														
		tmPtzParameter_t	struParameter;				
	}data;
}tmPtzCommandCfg_t;

typedef struct tmPtzIntegrateCfg_t
{
	unsigned int				dwSize;								
	unsigned int				dwVerticallyStation;				
	unsigned int				dwHorizontallyStation;				
	unsigned int				dwVerticallyVisualAngle;		
	unsigned int				dwHorizontallyVisualAngle;			
	unsigned int				dwZoomValue;						
	unsigned char				byControlMode;						
	unsigned char				byTemp[3];
}tmPtzIntegrateCfg_t;

typedef struct tmDriveInfo_t
{
	unsigned char				byInit;							
	unsigned char				byReset;						
	unsigned char				byTemp[2];							
	unsigned int				dwDriveType;						
	unsigned int				dwTotalSpace;					
	unsigned int				dwUsefullSpace;						
}tmDriveInfo_t;

typedef struct tmDriveCfg_t
{
	unsigned int				dwSize;							
	unsigned int				dwDriveCount;						
	tmDriveInfo_t				struDisk[16];						
}tmDriveCfg_t;	
#define TMCC_DRIVE_UNKNOWN			0x00
#define TMCC_DRIVE_NO_ROOT_DIR		0x01
#define TMCC_DRIVE_REMOVABLE		0x02
#define TMCC_DRIVE_FIXED			0x03
#define TMCC_DRIVE_REMOTE			0x04
#define TMCC_DRIVE_CDROM			0x05
#define TMCC_DRIVE_RAMDISK			0x06
#define TMCC_DRIVE_SDRAM			0x07

typedef struct tmVideoInCfg_t
{
	unsigned int				dwSize;

	unsigned char				byAntiFlickerMode;
	unsigned char				byVideoColorStyle;	
	unsigned char				byRotaeAngle180;
	unsigned char				byColorTransMode;
	unsigned char				byShutterSpeed;
	unsigned char               byAgc;	
	unsigned char               byIRShutMode;
	unsigned char				byExposure;

	unsigned char               byIRStartHour;
	unsigned char               byIRStartMin;
	unsigned char               byIRStopHour;
	unsigned char               byIRStopMin;

	unsigned char				byModeSwitch;	
	unsigned char				byWhiteBalance;
	unsigned char				byWdr;
	unsigned char				byBlc;
	
	unsigned int				dwWhiteBalanceVal;
	unsigned char				byMctfStrength;
	unsigned char				byIRType;
	unsigned char				byIRCutTriggerAlarmOut;

	unsigned char				byIRCutStat;
	unsigned char				byExposureLevel;

	unsigned char				byColorTransMin;
	unsigned char				byColorTransMax;
}tmVideoInCfg_t;

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
#define IRSHUT_MODE_AUTO				0x00
#define IRSHUT_MODE_SCHEDTIME			0x01
#define IRSHUT_MODE_ALARMIN				0x02
#define IRSHUT_MODE_MANUAL				0xFF

typedef struct tmApertureCfg_t
{
	unsigned int				dwSize;
	unsigned char				byApertureType;
	unsigned char				byTemp[3];
	unsigned int				dwDutyBalance;
}tmApertureCfg_t;

typedef struct tmVideoOutCfg_t
{
	unsigned int				dwSize;
	unsigned char				byEnableVideoOut;
	unsigned char				byVideoOutMode;
	unsigned char				byRenovator;
	unsigned char				byResverse;

	unsigned short				wWidth;
	unsigned short				wHeight;	
	
}tmVideoOutCfg_t;

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

typedef struct tmRecordDay_t
{
	unsigned char	byAllDayRecord;	
	unsigned char	byRecordType;
	unsigned char	byTemp[2];
}tmRecordDay_t;

typedef struct tmRecordSched_t
{
	tmSchedTime_t	struRecordTime;
	unsigned char	byRecordType;
	char			byTemp[3];
}tmRecordSched_t;

typedef struct tmRecordCfg_t
{
	unsigned int				dwSize;
	tmRecordDay_t				struRecordAllDay[MAX_DAYS];
	tmRecordSched_t				struRecordSched[MAX_DAYS][MAX_TIMESEGMENT];
	unsigned int				dwRecordTime;					
	unsigned int				dwPreRecordTime;				
	unsigned int				dwRecorderDuration;				
	unsigned char				byRedundancyRec;
	unsigned char				byAudioRec;
	unsigned char				byRecordStream;
	unsigned char				byEnableRecord;	
}tmRecordCfg_t;

typedef struct tmFtpRecordCfg_t
{
	unsigned int				dwSize;
	tmRecordDay_t				struRecordAllDay[MAX_DAYS];
	tmRecordSched_t				struRecordSched[MAX_DAYS][MAX_TIMESEGMENT];
	unsigned int				dwRecordTime;	
	unsigned int				dwPreRecordTime;			
	unsigned char				byAudioRec;
	unsigned char				byRecordStream;
	unsigned char				byEnableRecord;
	unsigned char				byTemp;	
}tmFtpRecordCfg_t;


typedef struct tmConnectCfg_t
{
	unsigned int				dwSize;								
	char						sRemoteIP[24];						
	unsigned char				byConnectMode;					
	char						sTurnServerIP[24];					
	unsigned char				byTemp2;
	char						szUserName[32];					
	char						szPassword[32];						
	unsigned short				wConnectPort;						
	unsigned short				wChannelID;							
	unsigned short				wStreamID;						
	unsigned short				wDelayTime;							
	unsigned char				byEnableTurnServer;					
	unsigned char				byStreamType;						
	unsigned char				byTransType;						
	unsigned char				byDisplay;						
	unsigned char				byTemp4[2];
}tmConnectCfg_t;

typedef struct tmConnectListCfg_t
{
	unsigned int               dwSize;								
	unsigned int               dwCount;							
	tmConnectCfg_t				pConnectList[1];					
}tmConnectListCfg_t;

typedef struct tmWindowsCfg_t
{
	unsigned int				dwSize;							
	unsigned char				byImageQuant;						
	unsigned char				byEnableState;						
	unsigned char				byEnableAudio;						
	unsigned char				byResverse;							
}tmWindowsCfg_t;

typedef struct tmDisplayCfg_t
{
	unsigned int				dwSize;								
	unsigned char				bySingleView;						
	unsigned char				byWindowID;						
	unsigned char				byResverse[2];
}tmDisplayCfg_t;

typedef struct tmLockCfg_t
{
	unsigned int				dwSize;
	unsigned char				byLocked;
	unsigned char				byResverse[3];
}tmLockCfg_t;

typedef struct tmWindowCapabilityCfg_t
{
	unsigned int				dwSize;

	int							iSwitchWindowNum;
	unsigned char				bySwitchWindowList[32];

	unsigned char				byCircleCount;
}tmWindowCapabilityCfg_t;

typedef struct tmAlarmDeviceCfg_t
{
	unsigned int				dwSize;								
	unsigned int				dwFactoryId;						
	char						sName[32];							
	char						sUserName[32];						
	char						sPassword[32];						
	char						sAddress[32];					
	unsigned short				wPort;								
	unsigned short				wAlarmInBase;						
	unsigned short				wAlarmInNum;						
	unsigned short				wAlarmOutBase;						
	unsigned short				wAlarmOutNum;						
	unsigned char				byEnable;							
	unsigned char				bySourceType;					
}tmAlarmDeviceCfg_t;

typedef struct tmAlarmDeviceListCfg_t
{
	unsigned int				dwSize;								
	unsigned int				dwCount;							
	tmAlarmDeviceCfg_t			pAlarmList[1];						
}tmAlarmDeviceListCfg_t;

typedef struct tmChannelCfg_t
{
	unsigned int				dwSize;								
	unsigned int				dwFactoryId;					
	char						sName[32];							
	char						sUserName[32];					
	char						sPassword[32];					
	char						sAddress[32];					
	char						sTurnAddress[32];				
	unsigned short				wPort;						
	unsigned short				wTurnPort;					
	unsigned char				byChannelID;					
	unsigned char				bySubStream;					
	unsigned char				byTurnServer;						
	unsigned char				byStreamType;						
	unsigned char				byTransType;						
	unsigned char				byEnable;							
	unsigned char				bySourceType;						
	unsigned char				byTemp;								
}tmChannelCfg_t;

typedef struct tmChannelListCfg_t
{
	unsigned int				dwSize;								
	unsigned int				dwCount;							
	tmChannelCfg_t				pChannelList[1];					
}tmChannelListCfg_t;

typedef struct tmRtspChannelNameInfo_t
{
	BYTE						byEnable;						
	BYTE						byTemp[3];						
	char						sName1[32];						
	char						sName2[32];						
	char						sName3[32];						
	char						sName4[32];						
}tmRtspChannelNameInfo_t;
typedef struct tmRtspChannelNameCfg_t
{
	unsigned int				dwSize;							
	unsigned int				dwCount;						
	tmRtspChannelNameInfo_t		struRtspName[1];				
}tmRtspChannelNameCfg_t;

typedef struct tmLogInfo_t
{
	unsigned int			dwSize;									
	struct
	{
		unsigned short		wYear;									
		unsigned char		byMonth;								
		unsigned char		byDay;									
		unsigned char		byHour;									
		unsigned char		byMinute;								
		unsigned char		bySecond;								
		unsigned char		byTemp;									
	}struLogTime;													
	char					sUserName[32];							
	char					sAddress[16];							
	unsigned char			byUserLoginType;						
	unsigned char			byMajorType;							
	unsigned char			byMinorType;							
	unsigned char			byTemp;									
    char					sInfo[4];								
}tmLogInfo_t;

typedef struct tmLogInfoListCfg_t
{
	unsigned int			dwSize;
	unsigned int			dwCount;
	tmLogInfo_t				struLogInfo;
}tmLogInfoListCfg_t;

typedef struct tmLogCfg_t
{
	unsigned int			dwSize;									
	tmTimeInfo_t			struStartTime;							
	tmTimeInfo_t			struStopTime;							
}tmLogCfg_t;

typedef struct tmTheodoliteCfg_t
{
	unsigned int			dwSize;									
	unsigned int			dwLongitude;							
	unsigned int			dwLatitude;								
}tmTheodoliteCfg_t;

typedef struct tmFindConditionCfg_t
{
	unsigned int			dwSize;			
	unsigned char			byChannel;		
	unsigned char			byFileType;		
	unsigned char			bySearchAllTime;
	unsigned char			bySearchImage;	
	tmTimeInfo_t			struStartTime;	
	tmTimeInfo_t			struStopTime;	
}tmFindConditionCfg_t;

typedef struct tmFindFileCfg_t
{
	unsigned int			dwSize;	
	char					sFileName[64];		
	unsigned char			byChannel;			
	unsigned char			byAlarmType;		
	unsigned short			wFactoryId;			
	tmTimeInfo_t			struStartTime;		
	tmTimeInfo_t			struStopTime;		
	unsigned int			dwFileTime;			
	unsigned int			dwFileSize;			
	unsigned char			byImage;			
	unsigned char			byFileFormat;		
	unsigned char			byTemp[2];
}tmFindFileCfg_t;

typedef struct tmFileAccessInterface_t
{
	HANDLE			(*Open)( const char* lpFileName, const char* lpMode, void* context );
	int				(*Close)(HANDLE hFile);
	unsigned int	(*Seek)( HANDLE hFile, int offset, int origin );
	int				(*Read)( HANDLE hFile, void* lpBuffer, int nRead );
	int				(*Write)( HANDLE hFile, void* lpBuffer, int nWrite );
	unsigned int	(*Size)( HANDLE hFile );
}tmFileAccessInterface_t;

typedef struct tmAvIndexEntry_t
{
    unsigned int	ckid;
    unsigned int	dwFlags;
    unsigned int	dwChunkOffset;
    unsigned int	dwChunkLength;
}tmAvIndexEntry_t;

#define AVIIF_LIST							0x00000001L
#define AVIIF_KEYFRAME						0x00000010L
#define AVIIF_NOTIME						0x00000100L
#define AVIIF_COMPUSE						0x0FFF0000L

typedef struct tmPlayConditionCfg_t
{
	unsigned int						dwSize;	
	unsigned short						wFactoryId;			
	unsigned char						byChannel;				
	unsigned char						byPlayImage;		
	union
	{
		struct
		{
			tmTimeInfo_t				struStartTime;		
			tmTimeInfo_t				struStopTime;		
			unsigned char				byCheckStopTime;	
		}time;
		struct
		{
			unsigned char				byAutoCreateIndex;	
			unsigned char				byAutoPlay;			
			unsigned char				byTemp[2];
			char						sFileName[128];		
			tmFileAccessInterface_t*	pFileCallBack;		
			void*						pFileContext;		
			tmAvIndexEntry_t*			pAvIndex;			
			int							iAvIndexCount;		
		}file;
	}info;
}tmPlayConditionCfg_t;

typedef struct tmDownloadFileCfg_t
{
	tmPlayConditionCfg_t	struCondition;		
	char					sFileName[128];		
}tmDownloadFileCfg_t;

#define PLAY_CONTROL_PLAY				0		
#define PLAY_CONTROL_STOP				1		
#define PLAY_CONTROL_PAUSE				2		
#define PLAY_CONTROL_FAST				3		
#define PLAY_CONTROL_SLOW				4		
#define PLAY_CONTROL_SEEKPOS			5		
#define PLAY_CONTROL_SEEKTIME			6		
#define PLAY_CONTROL_STEMP				7		
#define PLAY_CONTROL_SWITCH				8		
#define PLAY_CONTROL_MUTE				9		
#define PLAY_CONTROL_UPEND				10		
#define PLAY_CONTROL_GETAVINDEX			11		
#define PLAY_CONTROL_SETAVINDEX			12		
typedef struct tmPlayControlCfg_t
{
	unsigned int				dwSize;				
	unsigned int				dwCommand;														
	union
	{
		tmTimeInfo_t			struTime;			
		int						iPlayData;			
		int						iSpeed;				
		int						iEnableAudio;		
		int						iCurrentPosition;	
		unsigned int			dwCurrentTime;		
		BOOL					bForward;			
		BOOL					bClearDisplay;		

		struct
		{
			unsigned char		byAutoCreateIndex;	
			unsigned char		byAutoPlay;			
			unsigned char		byTemp[2];
			char				sFileName[128];		
		}file;
		struct
		{
			tmAvIndexEntry_t*	pAvIndex;			
			int					iAvIndexCount;		
			int					iAvIndexMaxCount;	
		}index;
	}control;
}tmPlayControlCfg_t;

typedef struct tmPlayStateCfg_t
{
	unsigned int			dwSize;				
	unsigned char			byCurrentState;		
	unsigned char			byResetTime;		
	unsigned char			byResetFile;		
	unsigned char			byTemp;				

	unsigned int			dwTotalFrames;		
	unsigned int			dwCurrentFrame;		

	unsigned int			dwTotalTimes;		
	unsigned int			dwCurrentTimes;		
	
	tmTimeInfo_t			struStartTime;		
}tmPlayStateCfg_t;

typedef struct tmPlayRealStreamCfg_t
{
	unsigned int			dwSize;	
	char					szAddress[32];		
	char					szTurnAddress[32];	
	int						iPort;				
	char					szUser[32];			
	char					szPass[32];			
	unsigned char			byChannel;			
	unsigned char			byStream;			
	unsigned char			byTranstType;		
	unsigned char			byReConnectNum;			
	int						iTranstPackSize;	
	int						iReConnectTime;		
	unsigned char			byTransProtocol;	
}tmPlayRealStreamCfg_t;

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

typedef struct tmRealStreamInfo_t
{
	unsigned int		dwSize;				

	unsigned char		byFrameType;		
	unsigned char		byNeedReset;		
	unsigned char		byKeyFrame;			
	unsigned char		byStreamNo;			

	unsigned int		dwFactoryId;		
	unsigned int		dwStreamTag;		
	unsigned int		dwStreamId;		
	union
	{
		int				iWidth;			
		int				iSamplesPerSec;	
	};
	union
	{
		int				iHeight;			
		int				iBitsPerSample;		
	};
	union
	{
		struct
		{
			short		iFrameRate;			
			short		iDisplayFrameRate;	
		}framerate;
		int				iChannels;			
	};
	
	union
	{
		unsigned int	nDisplayScale;
	};
	
	unsigned int		dwTimeStamp;	
	unsigned int		dwPlayTime;		
	unsigned int		dwBitRate;			

	BYTE*				pBuffer;		
	int					iBufferSize;	
	
	BYTE*				pBuffer2;	
	int					iBuffer2Size;	
}tmRealStreamInfo_t;


#define TMCC_MAJOR_CMD_USERCFG						0x101		
#define TMCC_MINOR_CMD_USER_INFO					0x01		
#define TMCC_MINOR_CMD_USER_SINGLEINFO				0x02		
#define TMCC_MINOR_CMD_USER_ADD						0x03		
#define TMCC_MINOR_CMD_USER_DELETE					0x04		
#define TMCC_MINOR_CMD_USER_MOTIFYPASSWORD			0x05		
#define TMCC_MINOR_CMD_USER_MOTIFYRIGHT				0x06		
#define TMCC_MINOR_CMD_USER_VERIFY					0x07		
#define TMCC_MINOR_CMD_USER_DATA					0x08		

#define TMCC_MAJOR_CMD_DEVICECFG					0x102		
#define TMCC_MAJOR_CMD_NETCFG						0x103		
#define TMCC_MINOR_CMD_LANNETCFG					0x00		
#define TMCC_MINOR_CMD_WIFINETCFG					0x01		

#define TMCC_MAJOR_CMD_PICCFG						0x104		
#define TMCC_MINOR_CMD_PIC							0x00		
#define TMCC_MINOR_CMD_OSD							0x01		
#define TMCC_MINOR_CMD_MASK							0x02		
#define TMCC_MINOR_CMD_LOST							0x03		
#define TMCC_MINOR_CMD_MOTION						0x04		
#define TMCC_MINOR_CMD_HIDEALARM					0x05		

#define TMCC_MAJOR_CMD_COMPRESSCFG					0x105		
#define TMCC_MINOR_CMD_COMPRESSCFG					0x00		
#define TMCC_MINOR_CMD_QUERYCOMPRESSCAPABILITY		0x01		

#define TMCC_MAJOR_CMD_RECORDCFG					0x106		
#define TMCC_MINOR_CMD_LOCALRECORDCFG				0x00		
#define TMCC_MINOR_CMD_FTPRECORDCFG 				0x01		


#define TMCC_MAJOR_CMD_DECODERCFG					0x107		
#define TMCC_MINOR_CMD_485CFG 						0x00		
#define TMCC_MINOR_CMD_CRUISECFG 					0x01		
#define TMCC_MINOR_CMD_PTZCFG						0x02		
#define TMCC_MINOR_CMD_PRESETCFG					0x03		

#define TMCC_MAJOR_CMD_RS232CFG 					0x108		
#define TMCC_MAJOR_CMD_ALARMINCFG 					0x109		
#define TMCC_MAJOR_CMD_ALARMOUTCFG 					0x10A		

#define TMCC_MAJOR_CMD_TIMECFG 						0x10B		
#define TMCC_MINOR_CMD_TIMECFG 						0x00		
#define TMCC_MINOR_CMD_ZONECFG 						0x01		
#define TMCC_MINOR_CMD_DAYLIGHTCFG 					0x02		

#define TMCC_MAJOR_CMD_PREVIEWCFG 					0x10C		
#define TMCC_MINOR_CMD_PREVIEWCOLORCFG 				0x00		
#define TMCC_MINOR_CMD_COMPRESSOFFSETCFG 			0x01		
#define TMCC_MINOR_CMD_PREVIEWOFFSETCFG 			0x02		
#define TMCC_MINOR_CMD_PICMODE						0x03        

#define TMCC_MAJOR_CMD_VIDEOOUTCFG 					0x10D		
#define TMCC_MINOR_CMD_VIDEOOUT						0x00		
#define TMCC_MINOR_CMD_CONNECTINFO					0x01		
#define TMCC_MINOR_CMD_ENUMCONNECTINFO				0x02		
#define TMCC_MINOR_CMD_WINDOWSINFO					0x03		
#define TMCC_MINOR_CMD_DISPLAYINFO					0x04		
#define TMCC_MINOR_CMD_LOCK							0x05		
#define TMCC_MINOR_CMD_CLEAR						0x06		
#define TMCC_MINOR_CMD_CONNECT						0x07		
#define TMCC_MINOR_CMD_DISCONNECT					0x08		
#define TMCC_MINOR_CMD_WINDOWCAPABILITY				0x09		

#define TMCC_MAJOR_CMD_EXCEPTIONCFG 				0x10E		
#define TMCC_MAJOR_CMD_SERVERMESSAGE				0x10F		
#define TMCC_MINOR_CMD_DEBUGINFO					0x01		
#define TMCC_MINOR_CMD_SERVERSTART 					0x02		
#define TMCC_MINOR_CMD_SERVERSTOP 					0x03		
#define TMCC_MINOR_CMD_SERVERALARM 					0x04		
#define TMCC_MINOR_CMD_SERVERWANTSYNCTIME			0x05		
#define TMCC_MINOR_CMD_SERVERIMAGE					0x06		
#define TMCC_MINOR_CMD_PTZCLOSEBYOTHERUSER			0x07		
#define TMCC_MINOR_CMD_PTZCLOSEBYTIMEOUT			0x08		
#define TMCC_MINOR_CMD_SERIALMESSAGE				0x09		
#define TMCC_MINOR_CMD_SERVERLIVEHEART				0x0A		
#define TMCC_MINOR_CMD_APERTUREREPAIRCOMPLETE		0x0B		
#define TMCC_MINOR_CMD_BADPIXREPAIRCOMPLETE			0x0C		
#define TMCC_MINOR_CMD_SAFEGUARDINFO				0x0D		

#define TMCC_MAJOR_CMD_PTZCONTROL 					0x110		
#define TMCC_MINOR_CMD_PTZGETDECODERLIST			0x00		
#define TMCC_MINOR_CMD_PTZOPEN 						0x01		
#define TMCC_MINOR_CMD_PTZOPENANDLOCK				0x02		
#define TMCC_MINOR_CMD_PTZCLOSE 					0x03		
#define TMCC_MINOR_CMD_PTZSENDCMD					0x04
#define TMCC_MINOR_CMD_PTZTRANS						0x05		
#define TMCC_MINOR_CMD_SERIALOPEN					0x06		
#define TMCC_MINOR_CMD_SERIALCLOSE					0x07		
#define TMCC_MINOR_CMD_SERIALSEND					0x08		
#define TMCC_MINOR_CMD_GETPTZINFO					0x09		
#define TMCC_MINOR_CMD_SERIALRECV					0x0A		

#define TMCC_MAJOR_CMD_SERVERCONTROL				0x111		
#define TMCC_MINOR_CMD_REMONTALARMIN				0x01		
#define TMCC_MINOR_CMD_OPENLIGHT					0x02		
#define TMCC_MINOR_CMD_CLOSELIGHT					0x03		
#define TMCC_MINOR_CMD_OPENBUZZER					0x04		
#define TMCC_MINOR_CMD_CLOSEBUZZER					0x05		
#define TMCC_MINOR_CMD_GETWORKSTATE					0x06		
#define TMCC_MINOR_CMD_REMONTCLOSEALARMOUT			0x07	
#define TMCC_MINOR_CMD_REMONTOPENALARMOUT			0x08		
#define TMCC_MINOR_CMD_RESET						0x09		
#define TMCC_MINOR_CMD_REMONTVIDEOMOTION			0x0A		
#define TMCC_MINOR_CMD_REMONTVIDEOLOST				0x0B		
#define TMCC_MINOR_CMD_REMONTVIDEOHIDE				0x0C		
#define TMCC_MINOR_CMD_REQUESTUPGRADE				0x0D		
#define TMCC_MINOR_CMD_OPENIRCUT					0x0E		
#define TMCC_MINOR_CMD_CLOSEIRCUT					0x0F	
#define TMCC_MINOR_CMD_MANUALCAPTURE				0x10		
#define TMCC_MINOR_CMD_AUTOAPERTUREREPAIR			0x11		
#define TMCC_MINOR_CMD_UPGRADEKEEPIP				0x12		
#define TMCC_MINOR_CMD_SYNCNTPSERVER				0x13		
#define TMCC_MINOR_CMD_STARTMANUALRECORD			0x14		
#define TMCC_MINOR_CMD_STOPMANUALRECORD				0x15		
#define TMCC_MINOR_CMD_HANDLE						0x16		
#define TMCC_MINOR_CMD_SAVECONFIGINFO				0x17		
#define TMCC_MINOR_CMD_CONTROLSAFEDOOR				0x18		

#define TMCC_MAJOR_CMD_ALARMCFG 					0x112		

#define TMCC_MAJOR_CMD_DISKCONTROL					0x113		
#define TMCC_MINOR_CMD_DRIVEINFO					0x01		
#define TMCC_MINOR_CMD_DRIVEINIT					0x02		

#define TMCC_MAJOR_CMD_NETCFGEX						0x114		
#define TMCC_MINOR_CMD_NTPCFG						0x00
#define TMCC_MINOR_CMD_FTPCFG						0x01
#define TMCC_MINOR_CMD_SMTPCFG						0x02
#define TMCC_MINOR_CMD_LIVEHEARTCFG					0x03		
#define TMCC_MINOR_CMD_DDNSCFG						0x04		
#define TMCC_MINOR_CMD_UPCFG						0x05		

#define TMCC_MAJOR_CMD_COMPRESSCFGA					0x115		
#define TMCC_MINOR_CMD_COMPRESSCFGA					0x00		

#define TMCC_MAJOR_CMD_VIDEOINCFG					0x116		
#define TMCC_MINOR_CMD_VIDEOIN						0x00		

#define TMCC_MAJOR_CMD_SHUTTERCFG					0x117

#define TMCC_MAJOR_CMD_CAPTUREIMAGECFG				0x118
#define TMCC_MINOR_CMD_CAPTUREIMAGECFG				0x00		
#define TMCC_MINOR_CMD_CAPTURESCHEDCFG				0x01		

#define TMCC_MAJOR_CMD_AUDIOCFG                     0x119

#define TMCC_MAJOR_CMD_CHANNELCFG                   0x11A       
#define TMCC_MINOR_CMD_SINGLECHANNEL                0x00        
#define TMCC_MINOR_CMD_ALLCHANNEL                   0x01        
#define TMCC_MINOR_CMD_SINGLERTSPNAME               0x02        
#define TMCC_MINOR_CMD_ALLRTSPNAME                  0x03        

#define TMCC_MAJOR_CMD_ALARMDEVICECFG               0x11B       
#define TMCC_MINOR_CMD_SINGLEALARMDEVICE            0x00        
#define TMCC_MINOR_CMD_ALLALARMDEVICE               0x01        

#define TMCC_MAJOR_CMD_LOGCFG						0x11C
#define TMCC_MINOR_CMD_ENUMLOG						0x00		
#define TMCC_MINOR_CMD_CLEARLOG						0x01		

#define TMCC_MAJOR_CMD_CONNECTCFG					0x11D
#define TMCC_MINOR_CMD_CONNECTLISTCFG				0x00		
#define TMCC_MINOR_CMD_CLEARCONNECT					0x01		

#define TMCC_MAJOR_CMD_THEODOLITECFG				0x11E

#define	TMCC_USERRIGHT_CONTROLPTZ					0x00000001	
#define	TMCC_USERRIGHT_MANUALREC					0x00000002	
#define	TMCC_USERRIGHT_PLAYBACK						0x00000004	
#define	TMCC_USERRIGHT_SETUP						0x00000008
#define	TMCC_USERRIGHT_LOOKSTAUS					0x00000010	
#define	TMCC_USERRIGHT_ADVANCE						0x00000020	
#define	TMCC_USERRIGHT_TALK							0x00000040	
#define	TMCC_USERRIGHT_PREVIEW						0x00000080	
#define	TMCC_USERRIGHT_ALARM						0x00000100	
#define	TMCC_USERRIGHT_CONTROLLOCAL					0x00000200	
#define	TMCC_USERRIGHT_SERIALPORT					0x00000400	
#define	TMCC_USERRIGHT_MOTIFYUSER					0x00000800	
#define	TMCC_USERRIGHT_MOTIFYSELFPASSWORD			0x00001000	
#define	TMCC_USERRIGHT_RTSPCONNECT					0x00002000	

#define	TMCC_PLAY_STATE_STOP						0			
#define	TMCC_PLAY_STATE_PAUSE						1			
#define	TMCC_PLAY_STATE_PLAY						2			
#define	TMCC_PLAY_STATE_FAST						3			
#define	TMCC_PLAY_STATE_SLOW						4			
#define	TMCC_PLAY_STATE_OPEN						5			
#define	TMCC_PLAY_STATE_SWITCH						6			
#define	TMCC_PLAY_STATE_FILEEND						7			
#define TMCC_PLAY_STATE_STREAMBUFFERRING			8			
#define TMCC_PLAY_STATE_ENCFMTCHANGE				9			

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
