
#ifndef _DVR_NET_SDK_H_
#define _DVR_NET_SDK_H_

#include "dvrdvstypedef.h"
#include "dvrdvsconfig.h"
#include "dvrdvsdefine.h"

#ifdef WIN32

#define CALL_METHOD __stdcall

#ifdef __cplusplus
#define __EXTERN_C extern "C"
#else
#define __EXTERN_C extern
#endif

#ifdef DVR_NET_SDK_EXPORTS
#define NET_SDK_API __EXTERN_C __declspec(dllexport)
#else
#define NET_SDK_API __EXTERN_C __declspec(dllimport)
#endif

#else

#define CALL_METHOD
#define NET_SDK_API

#endif

//LastError����
typedef enum
{
	NET_SDK_SUCCESS,
	NET_SDK_PASSWORD_ERROR,
	NET_SDK_NOENOUGH_AUTH,
	NET_SDK_NOINIT,
	NET_SDK_CHANNEL_ERROR,
	NET_SDK_OVER_MAXLINK,
	NET_SDK_LOGIN_REFUSED,
	NET_SDK_VERSION_NOMATCH,
	NET_SDK_NETWORK_FAIL_CONNECT,
	NET_SDK_NETWORK_NOT_CONNECT,
	NET_SDK_NETWORK_SEND_ERROR,
	NET_SDK_NETWORK_RECV_ERROR,
	NET_SDK_NETWORK_RECV_TIMEOUT,
	NET_SDK_NETWORK_ERRORDATA,
	NET_SDK_ORDER_ERROR,
	NET_SDK_OPER_BY_OTHER,
	NET_SDK_OPER_NOPERMIT,
	NET_SDK_COMMAND_TIMEOUT,
	NET_SDK_ERROR_SERIALPORT,
	NET_SDK_ERROR_ALARMPORT,
	NET_SDK_PARAMETER_ERROR,
	NET_SDK_CHAN_EXCEPTION,
	NET_SDK_NODISK,
	NET_SDK_ERROR_DISKNUM,
	NET_SDK_DISK_FULL,
	NET_SDK_DISK_ERROR,
	NET_SDK_NOSUPPORT,
	NET_SDK_BUSY,
	NET_SDK_MODIFY_FAIL,
	NET_SDK_PASSWORD_FORMAT_ERROR,
	NET_SDK_DISK_FORMATING,
	NET_SDK_DVR_NORESOURCE,
	NET_SDK_DVR_OPRATE_FAILED,
	NET_SDK_OPEN_HOSTSOUND_FAIL,
	NET_SDK_DVR_VOICEOPENED,
	NET_SDK_TIME_INPUTERROR,
	NET_SDK_NOSPECFILE,
	NET_SDK_CREATEFILE_ERROR,
	NET_SDK_FILEOPENFAIL,
	NET_SDK_OPERNOTFINISH,
	NET_SDK_GETPLAYTIMEFAIL,
	NET_SDK_PLAYFAIL,
	NET_SDK_FILEFORMAT_ERROR,
	NET_SDK_DIR_ERROR,
	NET_SDK_ALLOC_RESOURCE_ERROR,
	NET_SDK_AUDIO_MODE_ERROR,
	NET_SDK_NOENOUGH_BUF,
	NET_SDK_CREATESOCKET_ERROR,
	NET_SDK_SETSOCKET_ERROR,
	NET_SDK_MAX_NUM,
	NET_SDK_USERNOTEXIST,
	NET_SDK_WRITEFLASHERROR,
	NET_SDK_UPGRADEFAIL,
	NET_SDK_CARDHAVEINIT,
	NET_SDK_PLAYERFAILED,
	NET_SDK_MAX_USERNUM,
	NET_SDK_GETLOCALIPANDMACFAIL,
	NET_SDK_NOENCODEING,
	NET_SDK_IPMISMATCH,
	NET_SDK_MACMISMATCH,
	NET_SDK_UPGRADELANGMISMATCH,
	NET_SDK_MAX_PLAYERPORT,
	NET_SDK_NOSPACEBACKUP,
	NET_SDK_NODEVICEBACKUP,
	NET_SDK_PICTURE_BITS_ERROR,
	NET_SDK_PICTURE_DIMENSION_ERROR,
	NET_SDK_PICTURE_SIZ_ERROR,
	NET_SDK_LOADPLAYERSDKFAILED,
	NET_SDK_LOADPLAYERSDKPROC_ERROR,
	NET_SDK_LOADDSSDKFAILED,
	NET_SDK_LOADDSSDKPROC_ERROR,
	NET_SDK_DSSDK_ERROR,
	NET_SDK_VOICEMONOPOLIZE,
	NET_SDK_JOINMULTICASTFAILED,
	NET_SDK_CREATEDIR_ERROR,
	NET_SDK_BINDSOCKET_ERROR,
	NET_SDK_SOCKETCLOSE_ERROR,
	NET_SDK_USERID_ISUSING,
	NET_SDK_PROGRAM_EXCEPTION,
	NET_SDK_WRITEFILE_FAILED,
	NET_SDK_FORMAT_READONLY,
	NET_SDK_WITHSAMEUSERNAME,
	NET_SDK_DEVICETYPE_ERROR,
	NET_SDK_LANGUAGE_ERROR,
	NET_SDK_PARAVERSION_ERROR,
	NET_SDK_FILE_SUCCESS,
	NET_SDK_FILE_NOFIND,
	NET_SDK_NOMOREFILE,
	NET_SDK_FILE_EXCEPTION,
	NET_SDK_TRY_LATER,
}NET_SDK_ERROR;

enum NET_DEVICE_STATUS
{
	NET_DEVICE_STATUS_CONNECTED,
	NET_DEVICE_STATUS_DISCONNECT,
};

enum NET_SDK_STREAM_TYPE
{
	NET_SDK_MAIN_STREAM,
	NET_SDK_SUB_STREAM,
};

enum NET_SDK_PLAYCTRL_TYPE
{
	NET_SDK_PLAYCTRL_PAUSE,
	NET_SDK_PLAYCTRL_FF,
	NET_SDK_PLAYCTRL_REW,
	NET_SDK_PLAYCTRL_RESUME,
	NET_SDK_PLAYCTRL_STOP,
	NET_SDK_PLAYCTRL_FRAME,
	NET_SDK_PLAYCTRL_NORMAL,
	NET_SDK_PLAYCTRL_STARTAUDIO,	//�ÿ������ͼ�����������������ֻ����SDK�ڲ�������ʾʱ�Ż�������
	NET_SDK_PLAYCTRL_STOPAUDIO,
	NET_SDK_PLAYCTRL_AUDIOVOLUME,
	NET_SDK_PLAYCTRL_SETPOS,
};

enum NET_SDK_RPB_SPEED
{
	NET_SDK_RPB_SPEED_1_32X = 1,
	NET_SDK_RPB_SPEED_1_16X,
	NET_SDK_RPB_SPEED_1_8X,		//1/8
	NET_SDK_RPB_SPEED_1_4X,		//1/4
	NET_SDK_RPB_SPEED_1_2X,		//1/2
	NET_SDK_RPB_SPEED_1X,		//1
	NET_SDK_RPB_SPEED_2X,
	NET_SDK_RPB_SPEED_4X,
	NET_SDK_RPB_SPEED_8X,
	NET_SDK_RPB_SPEED_16X,
	NET_SDK_RPB_SPEED_32X,
};

const static long MAX_NAMELEN			= 36;

//��¼�ṹ����
typedef struct _net_sdk_deviceinfo
{
	unsigned char	localVideoInputNum;		//������Ƶ����ͨ����Ŀ
	unsigned char	audioInputNum;			//��Ƶ����ͨ����Ŀ
	unsigned char	sensorInputNum;			//����������ͨ����Ŀ
	unsigned char	sensorOutputNum;		//�̵��������Ŀ
	unsigned long   displayResolutionMask;  //��������ѡ��ķֱ���

	unsigned char	videoOuputNum;			//��Ƶ�����Ŀ����֧�ֻط����ͨ����
	unsigned char	netVideoOutputNum;		//����ط����ͨ����Ŀ
	unsigned char	netVideoInputNum;		//�����źŽ���ͨ����Ŀ
	unsigned char	IVSNum;					//���ܷ���ͨ����Ŀ

	unsigned char	presetNumOneCH;			//ÿ��ͨ��Ԥ�õ���Ŀ
	unsigned char	cruiseNumOneCH;			//ÿ��ͨ��Ѳ������Ŀ
	unsigned char	presetNumOneCruise;		//ÿ��Ѳ���ߵ�Ԥ�õ���Ŀ
	unsigned char	trackNumOneCH;			//ÿ��ͨ���켣��Ŀ

	unsigned char	userNum;				//�û���Ŀ 
	unsigned char	netClientNum;			//���ͻ�����Ŀ
	unsigned char	netFirstStreamNum;		//�����������ͨ�������Ŀ����ͬʱ�����м����ͻ��˲鿴������
	unsigned char	deviceType;				//�豸����

	unsigned char	doblueStream;			//�Ƿ����ṩ˫����
	unsigned char	audioStream;			//�Ƿ����ṩ��Ƶ��
	unsigned char	talkAudio;				//�Ƿ��жԽ�����: 1��ʾ�жԽ�����;0��ʾû��
	unsigned char	bPasswordCheck;			//�����Ƿ�Ҫ��������

	unsigned char	defBrightness;			//ȱʡ����
	unsigned char	defContrast;			//ȱʡ�Աȶ�
	unsigned char	defSaturation;			//ȱʡ���Ͷ�
	unsigned char	defHue;					//ȱʡɫ��

	unsigned short	videoInputNum;			//��Ƶ����ͨ����Ŀ�����ؼ����磩
	unsigned short  deviceID;				//�豸ID��
	unsigned long   videoFormat;            //ϵͳ��ǰ��ʽ

	//������FUNC_REMOTE_UPGRADE��Ӧ�Ĺ��ܣ���ô��FUNC_REMOTE_UPGRADE������Ϊ1������Ϊ�㡣
	unsigned long	function[8];			//��������

	unsigned long	deviceIP;				//�豸�����ַ
	unsigned char	deviceMAC[6];			//�豸�����ַ
	unsigned short	devicePort;				//�豸�˿�

	unsigned long	buildDate;				//��������:year<<16 + month<<8 + mday
	unsigned long	buildTime;				//����ʱ��:hour<<16 + min<<8 + sec

	char			deviceName[36];			//�豸���

	char	firmwareVersion[36];			//�̼��汾
	char	kernelVersion[64];				//�ں˰汾
	char	hardwareVersion[36];			//Ӳ���汾
	char	MCUVersion[36];					//��Ƭ��汾
}NET_SDK_DEVICEINFO, *LPNET_SDK_DEVICEINFO;

//���֡ͷ����
typedef struct _net_sdk_frame_info
{
	unsigned long		deviceID;
	unsigned long       channel;
	unsigned long		frameType;	//�ο�DD_FRAME_TYPE
	unsigned long		length;
	unsigned long		keyFrame;	//0���ǹؼ�֡ 1���ؼ�֡
	unsigned long       width;
	unsigned long       height;
	unsigned long		frameIndex;
	unsigned long		frameAttrib;//�ο�DD_FRAME_ATTRIB
	unsigned long		streamID;
	LONGLONG			time;	   //��1970��1��1��0��0��0�뿪ʼ�ľ��ʱ�䣬��λ΢��
	LONGLONG			relativeTime;//���ʱ�䣬��λ΢��
}NET_SDK_FRAME_INFO;

//¼��ʱ����Ϣ����
typedef struct _net_sdk_rec_time
{
	DWORD			dwChannel;	//ͨ����
	DD_TIME			startTime;	//�ö�¼��ʼʱ��
	DD_TIME			stopTime;	//�ö�¼�����ʱ��
}NET_SDK_REC_TIME;

typedef struct _net_sdk_rec_file
{
	DWORD			dwChannel;
	DWORD			bFileLocked;
	DD_TIME			startTime;
	DD_TIME			stopTime;
	DWORD			dwRecType;
	DWORD			dwPartition;
	DWORD			dwFileIndex;
}NET_SDK_REC_FILE;

typedef struct _net_sdk_rec_event
{
	DWORD			dwChannel;
	DD_TIME			startTime;
	DD_TIME			stopTime;
	DWORD			dwRecType;	//DD_RECORD_TYPE
}NET_SDK_REC_EVENT;

//��־��Ϣ����
typedef struct _net_sdk_log
{
	DD_TIME			strLogTime;
	DWORD			dwMajorType;
	DWORD			dwMinorType;
	char			sNetUser[MAX_NAMELEN];
	DWORD			dwRemoteHostAddr;

}NET_SDK_LOG,*LPNET_SDK_LOG;

typedef struct _net_sdk_clientinfo
{
	LONG    lChannel;
	LONG    streamType;
	HWND    hPlayWnd;
}NET_SDK_CLIENTINFO, *LPNET_SDK_CLIENTINFO;

//�豸�ϴ���Ϣ����
enum NET_SDK_DEVICE_MSG_TYPE
{
	NET_SDK_ALARM,		//�豸������Ϣ
	NET_SDK_RECORD,		//�豸¼����Ϣ
	NET_SDK_IVM_RULE,	//������Ϊ������Ϣ(��ʱ����)
	NET_SDK_TRADEINFO,	//ATM������Ϣ(��ʱ����)
	NET_SDK_IPCCFG,		//�����DVR��IPC��Ϣ���(��ʱ����)
};

//�豸�ϴ���ϢΪ��������ʱ�ľ��屨������
enum NET_SDK_ALARM_TYPE
{
	NET_SDK_ALARM_TYPE_MOTION,		//�ƶ����
	NET_SDK_ALARM_TYPE_SENSOR,		//�ź�������
	NET_SDK_ALARM_TYPE_VLOSS,		//�źŶ�ʧ
	NET_SDK_ALARM_TYPE_SHELTER,		//�ڵ�����
	NET_SDK_ALARM_TYPE_DISK_FULL,	//Ӳ����
	NET_SDK_ALARM_TYPE_DISK_UNFORMATTED,//Ӳ��δ��ʽ��
	NET_SDK_ALARM_TYPE_DISK_WRITE_FAIL,	//��дӲ�̳���
	NET_SDK_ALARM_TYPE_EXCEPTION,
};

//�豸�ϴ���ϢΪ��������ʱ���ϴ���Ϣ�ṹ
typedef struct _net_sdk_alarminfo
{
	DWORD		dwAlarmType;
	DWORD		dwSensorIn;		//��������������˿ں�
	DWORD		dwChannel;		//�ڱ�����ͨ�����ʱ����ʾ������ͨ����
	DWORD		dwDisk;			//�ڴ��̱���ʱ����ʾ�����Ĵ��̺�
}NET_SDK_ALARMINFO;

typedef struct _net_sdk_record_status
{
	DWORD		dwRecordType;		//DD_RECORD_TYPE
	DWORD		dwChannel;
}NET_SDK_RECORD_STATUS;

typedef enum _net_sdk_disk_status
{	
	NET_SDK_DISK_NORMAL,				//�� 
	NET_SDK_DISK_NO_FORMAT,				//δ��ʽ��
}NET_SDK_DISK_STATUS;

typedef enum _net_sdkdisk_property
{
	NET_SDK_DISK_READ_WRITE = 0,			//�����д
	NET_SDK_DISK_ONLY_READ,					//ֻ�ܶ�������д
	NET_SDK_DISK_REDUNDANCY					//����
}NET_SDK_DISK_PROPERTY;

typedef struct _net_sdk_disk_info
{
	LONG		diskIndex;			//���̱��
	short		diskStatus;			//����״̬���ο�NET_SDK_DISK_STATUS
	short		diskProperty;		//����״̬���ο�NET_SDK_DISK_PROPERTY
	DWORD		diskTotalSpace;		//�����ܿռ䣬��λMB
	DWORD		diskFreeSpace;		//����ʣ��ռ䣬��λMB
}NET_SDK_DISK_INFO;

typedef struct
{
	WORD     wPicSize;
	WORD     wPicQuality;
}NET_SDK_JPEGPARA,*LPNET_SDK_JPEGPARA;

typedef enum _net_sdk_exception_type
{
	NETWORK_DISCONNECT = 0,
	NETWORK_RECONNECT,
}NET_SDK_EXCEPTION_TYPE;

enum NET_SDK_DEVICE_TYPE
{
	NET_SDK_DVR,
	NET_SDK_DVS,
	NET_SDK_IPCAMERA,
	NET_SDK_SUPERDVR,
	NET_SDK_DECODER,
};

typedef struct _net_sdk_device_discovery_info
{
	unsigned long		deviceType;		//NET_SDK_DEVICE_TYPE
	char				productType[16];
	char				strIP[16];
	char				strNetMask[16];
	char				strGateWay[16];
	unsigned char		byMac[8];
	unsigned short		netPort;
	unsigned short		httpPort;
	unsigned long		softVer;
	unsigned long		softBuildDate;
}NET_SDK_DEVICE_DISCOVERY_INFO;

//�ص�������
typedef void (CALLBACK *EXCEPTION_CALLBACK)(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);

typedef void (CALLBACK *DRAW_FUN_CALLBACK)(LONG lLiveHandle, HDC hDC, void *pUser);

typedef void (CALLBACK *LIVE_DATA_CALLBACK)(LONG lLiveHandle, NET_SDK_FRAME_INFO frameInfo, BYTE *pBuffer, void *pUser);

typedef BOOL (CALLBACK *NET_MESSAGE_CALLBACK)(LONG lCommand, LONG lUserID, char *pBuf, DWORD dwBufLen, void *pUser);

typedef void (CALLBACK *PLAY_DATA_CALLBACK)(LONG lPlayHandle, NET_SDK_FRAME_INFO frameInfo, BYTE *pBuffer, void *pUser);

typedef void (CALLBACK *TALK_DATA_CALLBACK)(LONG lVoiceComHandle, char *pRecvDataBuffer, DWORD dwBufSize, BYTE byAudioFlag, void* pUser);

//////////////////////////////////////////////////////////////////////////
//2012-3-15����SDK����DVR����ע��Ĺ���
typedef void (CALLBACK *ACCEPT_REGISTER_CALLBACK)(LONG lUserID, LONG lRegisterID, LPNET_SDK_DEVICEINFO pDeviceInfo, void *pUser);

//////////////////////////////////////////////////////////////////////////
//�ӿڶ���
/********************************SDK�ӿں�������*********************************/
//SDK��ʼ�����˳�
NET_SDK_API BOOL CALL_METHOD NET_SDK_Init();
NET_SDK_API BOOL CALL_METHOD NET_SDK_Cleanup();

//������ǰ���豸����
NET_SDK_API long CALL_METHOD NET_SDK_DiscoverDevice(NET_SDK_DEVICE_DISCOVERY_INFO *pDeviceInfo, long bufNum, long waitSeconds);

//SDK�����쳣�ص�
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetSDKMessageCallBack(UINT nMessage, HWND hWnd, EXCEPTION_CALLBACK fExceptionCallBack, void *pUser);

//DVR������״̬�ص�
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetDVRMessageCallBack(NET_MESSAGE_CALLBACK fMessageCallBack, void *pUser);

//������������
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetConnectTime(DWORD dwWaitTime = 5000, DWORD dwTryTimes = 3);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetReconnect(DWORD dwInterval = 30000, BOOL bEnableRecon = TRUE);

//�汾��Ϣ
NET_SDK_API DWORD CALL_METHOD NET_SDK_GetSDKVersion();
NET_SDK_API DWORD CALL_METHOD NET_SDK_GetSDKBuildVersion();

NET_SDK_API LONG CALL_METHOD NET_SDK_GetProductSubID(char *sDVRIP,WORD wDVRPort);

//�豸��¼�ǳ�
NET_SDK_API LONG CALL_METHOD NET_SDK_Login(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,LPNET_SDK_DEVICEINFO lpDeviceInfo);
NET_SDK_API BOOL CALL_METHOD NET_SDK_Logout(LONG lUserID);

//�����ѯ
NET_SDK_API DWORD CALL_METHOD NET_SDK_GetLastError();
NET_SDK_API char* CALL_METHOD NET_SDK_GetErrorMsg(LONG *pErrorNo = NULL);

//Ԥ����ؽӿ�
NET_SDK_API LONG CALL_METHOD NET_SDK_LivePlay(LONG lUserID, LPNET_SDK_CLIENTINFO lpClientInfo, LIVE_DATA_CALLBACK fLiveDataCallBack = NULL, void* pUser = NULL);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopLivePlay(LONG lLiveHandle);
NET_SDK_API BOOL CALL_METHOD NET_SDK_RegisterDrawFun(LONG lLiveHandle, DRAW_FUN_CALLBACK fDrawFun, void *pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetPlayerBufNumber(LONG lLiveHandle,DWORD dwBufNum);

NET_SDK_API BOOL CALL_METHOD NET_SDK_OpenSound(LONG lLiveHandle);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CloseSound();
NET_SDK_API BOOL CALL_METHOD NET_SDK_Volume(LONG lLiveHandle,WORD wVolume);

NET_SDK_API BOOL CALL_METHOD NET_SDK_SaveLiveData(LONG lLiveHandle,char *sFileName);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopSaveLiveData(LONG lLiveHandle);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetLiveDataCallBack(LONG lLiveHandle,LIVE_DATA_CALLBACK fLiveDataCallBack, void *pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CapturePicture(LONG lLiveHandle,char *sPicFileName);//bmp
NET_SDK_API BOOL CALL_METHOD NET_SDK_CapturePicture_Other(LONG lUserID, LONG lChannel,char *sPicFileName);//bmp

//��̬���I֡
NET_SDK_API BOOL CALL_METHOD NET_SDK_MakeKeyFrame(LONG lUserID, LONG lChannel);//������
NET_SDK_API BOOL CALL_METHOD NET_SDK_MakeKeyFrameSub(LONG lUserID, LONG lChannel);//������

//��̨������ؽӿ�
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZControl(LONG lLiveHandle, DWORD dwPTZCommand, DWORD dwSpeed);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZControl_Other(LONG lUserID, LONG lChannel, DWORD dwPTZCommand, DWORD dwSpeed);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZPreset(LONG lLiveHandle, DWORD dwPTZPresetCmd, DWORD dwPresetIndex);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZPreset_Other(LONG lUserID, LONG lChannel, DWORD dwPTZPresetCmd, DWORD dwPresetIndex);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZCruise(LONG lLiveHandle,DWORD dwPTZCruiseCmd,BYTE byCruiseRoute);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZCruise_Other(LONG lUserID,LONG lChannel,DWORD dwPTZCruiseCmd,BYTE byCruiseRoute);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZTrack(LONG lLiveHandle, DWORD dwPTZTrackCmd);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZTrack_Other(LONG lUserID, LONG lChannel, DWORD dwPTZTrackCmd);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZAutoScan(LONG lLiveHandle, DWORD dwPTZAutoScanCmd);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZAutoScan_Other(LONG lUserID, LONG lChannel, DWORD dwPTZAutoScanCmd);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZSetCruise(LONG lLiveHandle, BYTE byCruiseRoute, DD_CRUISE_POINT_INFO *pCruisePoint, WORD pointNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZSetCruise_Other(LONG lUserID, LONG lChannel, BYTE byCruiseRoute, DD_CRUISE_POINT_INFO *pCruisePoint, WORD pointNum);

//�ļ�������ط�
NET_SDK_API LONG CALL_METHOD NET_SDK_FindRecDate(LONG lUserID);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextRecDate(LONG lFindHandle, DD_DATE *lpRecDate);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindRecDateClose(LONG lFindHandle);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindFile(LONG lUserID,LONG lChannel, DD_TIME * lpStartTime, DD_TIME * lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextFile(LONG lFindHandle,NET_SDK_REC_FILE* lpFindData);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindClose(LONG lFindHandle);

NET_SDK_API LONG CALL_METHOD NET_SDK_FindEvent(LONG lUserID,LONG lChannel,DWORD dwRecType, DD_TIME * lpStartTime, DD_TIME * lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextEvent(LONG lFindHandle,NET_SDK_REC_EVENT *lpRecEvent);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindEventClose(LONG lFindHandle);

NET_SDK_API LONG CALL_METHOD NET_SDK_FindTime(LONG lUserID,LONG lChannel, DD_TIME * lpStartTime, DD_TIME * lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextTime(LONG lFindHandle, NET_SDK_REC_TIME *lpRecTime);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindTimeClose(LONG lFindHandle);

NET_SDK_API BOOL CALL_METHOD NET_SDK_LockFile(LONG lUserID, NET_SDK_REC_FILE *pFileToLock, LONG fileNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_UnlockFile(LONG lUserID, NET_SDK_REC_FILE *pFileToUnlock, LONG fileNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_DeleteRecFile(LONG lUserID, NET_SDK_REC_FILE *pFileToUnlock, LONG fileNum);

NET_SDK_API LONG CALL_METHOD NET_SDK_PlayBackByTime(LONG lUserID,LONG *pChannels, LONG channelNum, DD_TIME * lpStartTime, DD_TIME * lpStopTime, HWND *hWnds);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PlayBackControl(LONG lPlayHandle,DWORD dwControlCode,DWORD dwInValue,DWORD *lpOutValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopPlayBack(LONG lPlayHandle);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetPlayDataCallBack(LONG lPlayHandle,PLAY_DATA_CALLBACK fPlayDataCallBack, void *pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PlayBackSaveData(LONG lPlayHandle, LONG lChannel, char *sFileName);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopPlayBackSave(LONG lPlayHandle, LONG lChannel);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetPlayBackOsdTime(LONG lPlayHandle, DD_TIME * lpOsdTime);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PlayBackCaptureFile(LONG lPlayHandle, LONG lChannel, char *sFileName);

NET_SDK_API LONG CALL_METHOD NET_SDK_GetFileByTime(LONG lUserID,LONG lChannel, DD_TIME * lpStartTime, DD_TIME * lpStopTime, char *sSavedFileName);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopGetFile(LONG lFileHandle);
NET_SDK_API int CALL_METHOD NET_SDK_GetDownloadPos(LONG lFileHandle);

//��
NET_SDK_API LONG CALL_METHOD NET_SDK_Upgrade(LONG lUserID, char *sFileName);
NET_SDK_API int CALL_METHOD NET_SDK_GetUpgradeState(LONG lUpgradeHandle);
NET_SDK_API int CALL_METHOD NET_SDK_GetUpgradeProgress(LONG lUpgradeHandle);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CloseUpgradeHandle(LONG lUpgradeHandle);

//Զ�̹��?��ʽ��Ӳ��
NET_SDK_API LONG CALL_METHOD NET_SDK_FindDisk(LONG lUserID);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetNextDiskInfo(LONG lDiskHandle, NET_SDK_DISK_INFO *pDiskInfo);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindDiskClose(LONG lDiskHandle);
NET_SDK_API BOOL CALL_METHOD NET_SDK_ChangeDiskProperty(LONG lUserID, LONG lDiskNumber, short newProperty);
NET_SDK_API LONG CALL_METHOD NET_SDK_FormatDisk(LONG lUserID,LONG lDiskNumber);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetFormatProgress(LONG lFormatHandle, LONG *pCurrentFormatDisk,LONG *pCurrentDiskPos,LONG *pFormatStatic);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CloseFormatHandle(LONG lFormatHandle);

//����
NET_SDK_API LONG CALL_METHOD NET_SDK_SetupAlarmChan(LONG lUserID);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CloseAlarmChan(LONG lAlarmHandle);

//�����Խ�
NET_SDK_API LONG CALL_METHOD NET_SDK_StartVoiceCom(LONG lUserID, BOOL bNeedCBNoEncData, TALK_DATA_CALLBACK fVoiceDataCallBack, void* pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetAudioInfo(LONG lVoiceComHandle, void *pAudioInfo, LONG infoLen);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetVoiceComClientVolume(LONG lVoiceComHandle, WORD wVolume);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopVoiceCom(LONG lVoiceComHandle);

//����ת��
NET_SDK_API LONG CALL_METHOD NET_SDK_StartVoiceCom_MR(LONG lUserID, BOOL bNeedNoEncodeData, TALK_DATA_CALLBACK fVoiceDataCallBack, void* pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_VoiceComSendData(LONG lVoiceComHandle, char *pSendBuf, DWORD dwBufSize);

//////////////////////////////////////////////////////////////////////////
//͸�����ڹ���δ�ṩ

//��Ƶ����
NET_SDK_API LONG CALL_METHOD NET_SDK_InitAudioDecoder(void *pAudioInfo, LONG infoLen);
NET_SDK_API BOOL CALL_METHOD NET_SDK_DecodeAudioFrame(LONG lDecHandle, unsigned char* pInBuffer, LONG inLen, unsigned char* pOutBuffer, LONG *pOutLen);
NET_SDK_API void CALL_METHOD NET_SDK_ReleaseAudioDecoder(LONG lDecHandle);
//��Ƶ����
NET_SDK_API LONG CALL_METHOD NET_SDK_InitAudioEncoder(void *pAudioInfo, LONG infoLen);
NET_SDK_API BOOL CALL_METHOD NET_SDK_EncodeAudioFrame(LONG lEncodeHandle,unsigned char* pInBuffer, LONG inLen, unsigned char* pOutBuffer, LONG *pOutLen);
NET_SDK_API void CALL_METHOD NET_SDK_ReleaseAudioEncoder(LONG lEncodeHandle);

//Զ�̿����豸���ֶ�¼��
NET_SDK_API BOOL CALL_METHOD NET_SDK_StartDVRRecord(LONG lUserID,LONG lChannel,LONG lRecordType);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopDVRRecord(LONG lUserID,LONG lChannel);

//��־
NET_SDK_API LONG CALL_METHOD NET_SDK_FindDVRLog(LONG lUserID, DWORD dwType, DD_TIME * lpStartTime, DD_TIME * lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextLog(LONG lLogHandle, LPNET_SDK_LOG lpLogData);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindLogClose(LONG lLogHandle);

//JPEGץͼ���ڴ�
NET_SDK_API BOOL CALL_METHOD NET_SDK_CaptureJPEGPicture(LONG lUserID, LONG lChannel, LPNET_SDK_JPEGPARA lpJpegPara, char *sJpegPicBuffer, DWORD dwPicSize,  LPDWORD lpSizeReturned);

//end
NET_SDK_API BOOL CALL_METHOD NET_SDK_RefreshPlay(LONG lPlayHandle);
//�ָ�Ĭ��ֵ
NET_SDK_API BOOL CALL_METHOD NET_SDK_RestoreConfig(LONG lUserID);
//�������
NET_SDK_API BOOL CALL_METHOD NET_SDK_SaveConfig(LONG lUserID);
//����
NET_SDK_API BOOL CALL_METHOD NET_SDK_RebootDVR(LONG lUserID);
//�ر�DVR
NET_SDK_API BOOL CALL_METHOD NET_SDK_ShutDownDVR(LONG lUserID);

//��������
NET_SDK_API LONG CALL_METHOD NET_SDK_EnterDVRConfig(LONG lUserID);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDVRConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned, BOOL bDefautlConfig);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetDVRConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer,  DWORD dwInBufferSize);
NET_SDK_API BOOL CALL_METHOD NET_SDK_ExitDVRConfig(LONG lUserID);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetVideoEffect(LONG lUserID, LONG lChannel, DWORD *pBrightValue, DWORD *pContrastValue, DWORD *pSaturationValue, DWORD *pHueValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetVideoEffect(LONG lUserID, LONG lChannel, DWORD dwBrightValue, DWORD dwContrastValue, DWORD dwSaturationValue, DWORD dwHueValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SaveVideoEffect(LONG lUserID, LONG lChannel, DWORD dwBrightValue, DWORD dwContrastValue, DWORD dwSaturationValue, DWORD dwHueValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDefaultVideoEffect(LONG lUserID, DWORD *pBrightValue, DWORD *pContrastValue, DWORD *pSaturationValue, DWORD *pHueValue);

//�޸��豸ϵͳʱ��
NET_SDK_API BOOL CALL_METHOD NET_SDK_ChangTime(LONG lUserID, unsigned long time);

//�����ļ���������
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetConfigFile(LONG lUserID, char *sFileName);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetConfigFile(LONG lUserID, char *sFileName);

//������־�ļ�д��ӿ�
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetLogToFile(BOOL bLogEnable = FALSE, char * strLogDir = NULL, BOOL bAutoDel = TRUE);

//��ȡ�豸��Ϣ
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceInfo(LONG lUserID, LPNET_SDK_DEVICEINFO pdecviceInfo);
NET_SDK_API LONG CALL_METHOD NET_SDK_GetDeviceTypeName(LONG lUserID, char *pNameBuffer, long bufferLen);

//////////////////////////////////////////////////////////////////////////
//2012-3-15����SDK����DVR����ע��Ĺ���

//�豸����DVR����ע��ı���ƽ̨�˿ں�
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetRegisterPort(WORD wRegisterPort);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetRegisterCallback(ACCEPT_REGISTER_CALLBACK fRegisterCBFun, void *pUser);

#endif
