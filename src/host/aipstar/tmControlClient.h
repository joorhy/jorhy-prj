#ifndef __TMCONTROLCLIENT_H__
#define __TMCONTROLCLIENT_H__

#ifdef _LIB
	#define TMCC_API
	#define TMCC_CALL
#else
	#ifdef WIN32
		#define TMCC_API	extern "C" __declspec(dllexport) 
		#define TMCC_CALL	__cdecl
	#else
		#define TMCC_API	extern "C"	
		#define TMCC_CALL	
	#endif //WIN32
#endif //_LIB

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tmServerInfo_t	tmServerInfo_t;
typedef struct tmServerInfoEx_t	tmServerInfoEx_t;
typedef struct tmServerCfg_t	tmServerCfg_t;
typedef struct tmDecoderInfo_t	tmDecoderInfo_t;

#define USER_CONTEXT_SIZE		128

typedef struct tmConnectInfo_t
{
	unsigned int	dwSize;
	char			pIp[32];
	int				iPort;
	char			szUser[32];
	char			szPass[32];
	int				iUserLevel;
	unsigned char	pUserContext[USER_CONTEXT_SIZE];
}tmConnectInfo_t;

typedef struct tmCommandInfo_t
{
	unsigned int		dwSize;				
	unsigned int		dwMajorCommand;		
	unsigned int		dwMinorCommand;		
	unsigned short		iChannel;		
	unsigned short		iStream;			
	void*				pCommandBuffer;		
	int					iCommandBufferLen;	
	int					iCommandDataLen;	
	unsigned int		dwResult;			
}tmCommandInfo_t;

typedef struct tmProgressInfo_t
{
	HANDLE			hTmcc;					
	unsigned int	dwModalID;				
	unsigned int	dwModalSize;			
	unsigned int	dwModalPos;				
}tmProgressInfo_t;

typedef struct tmUpgradeConfig_t
{
	unsigned int		dwSize;					
	int					iListenPort;			
	int					iServerListCount;		
	tmServerInfoEx_t*	pServerInfoList;		
	
	int					iFileType;				
	char				szFileName[MAX_PATH];	

	BOOL				bAutoReboot;			
}tmUpgradeConfig_t;

typedef struct tmUpgradeInfo_t
{
	unsigned int		dwSize;					
	tmServerInfoEx_t*	pServerInfo;			
	unsigned int		dwResultCode;			
	int					iUpgradeProgress;		
}tmUpgradeInfo_t;

typedef struct tmAvRenderConfig_t
{
	unsigned int	dwSize;

	BOOL			bVideo;				
	int				iWidth;				
	int				iHeight;			
	int				iFrameRate;			

	BOOL			bAudio;				
	unsigned char	byBitsPerSample;	
	unsigned char	byChannels;			
	int				iSamplesPerSec;		
}tmAvRenderConfig_t;

typedef struct tmVoiceHead_t
{
	unsigned int	dwSize;	
	unsigned char	byCompressFormat;	
	unsigned char	byTemp;				
	unsigned char	byBitsPerSample;	
	unsigned char	byChannels;		
	int				iSamplesPerSec;	
	int				iAudioBitRate;		
}tmVoiceHead_t;

typedef struct tmVoiceData_t
{
	unsigned int	dwSize;				
	unsigned char	byDataType;			
	unsigned char	byTemp[3];			
	void*			pData;			
	int				iDataSize;			
	unsigned int	dwTimeStamp;		
}tmVoiceData_t;

typedef struct tmStreamHeadInfo_t
{
	unsigned int	dwSize;

	BOOL			bVideo;				
	unsigned int	dwVideoTag;			
	unsigned int	dwVideoId;			
	int				iWidth;				
	int				iHeight;			
	int				iDisplayScale;		
	int				iFrameRate;			
	int				iVideoBitRate;	
	BOOL			bInterlacer;	

	BOOL			bAudio;				
	unsigned int	dwAudioTag;			
	unsigned int	dwAudioId;				
	int				iBitsPerSample;		
	int				iChannels;			
	int				iSamplesPerSec;		
	int				iAudioBitRate;		
	unsigned int	dwSampleSize;		
	
}tmStreamHeadInfo_t;

typedef struct tmDeviceLoginInfo_t
{
	unsigned int	dwSize;
	unsigned int	dwDeviceIp;
	unsigned int	dwFactoryId;
	char			sDeviceId[64];
	char			sDeviceSn[48];
}tmDeviceLoginInfo_t;

typedef struct tmDeviceStreamInfo_t
{
	unsigned int	dwSize;				
	unsigned int	dwDeviceIp;			
	unsigned int	dwFactoryId;		
	char			sDeviceId[64];		
	char			sDeviceSn[48];		
	unsigned char	byChannel;			
	unsigned char	byStream;			
}tmDeviceStreamInfo_t;

typedef struct tmDeviceTalkInfo_t
{
	unsigned int	dwSize;
	unsigned int	dwDeviceIp;
	unsigned int	dwFactoryId;
	char			sDeviceId[64];
	char			sDeviceSn[48];
}tmDeviceTalkInfo_t;


#define AUTO_UPGRADE_CODE_REQUEST			0x01
#define AUTO_UPGRADE_CODE_START				0x02
#define AUTO_UPGRADE_CODE_SUCCESS			0x03
#define AUTO_UPGRADE_CODE_STATE				0x04
#define AUTO_UPGRADE_CODE_NETWORKERROR		0x05
#define AUTO_UPGRADE_CODE_CANTCONNECT		0x06
#define AUTO_UPGRADE_CODE_WRITEERROR		0x07

#define TMCC_INITTYPE_CONTROL				0x00
#define TMCC_INITTYPE_ENUM					0x01
#define TMCC_INITTYPE_UPGRADE				0x02
#define TMCC_INITTYPE_TALK					0x03
#define TMCC_INITTYPE_STREAM				0x04
#define TMCC_INITTYPE_REALSTREAM			0x05
#define TMCC_INITTYPE_LISTEN				0x06
#define TMCC_INITTYPE_VIDEORENDER			0x07
#define TMCC_INITTYPE_VOICERENDER			0x08
#define TMCC_INITTYPE_LISTENDEVICE			0x09


typedef void (CALLBACK* TMCC_LOG_CALLBACK)( HANDLE hTmCC, unsigned int code, const char* info, void* context );
typedef BOOL (CALLBACK* TMCC_CONNECT_CALLBACK)( HANDLE hTmCC, BOOL bConnect, unsigned int dwResult, void *context );
typedef int  (CALLBACK* TMCC_DATAREAD_CALLBACK)( HANDLE hTmcc, tmCommandInfo_t* pCmd, void *context );
typedef BOOL (CALLBACK* TMCC_ENUMSERVER_CALLBACK)( tmServerInfo_t* pEnum, void *context );
typedef BOOL (CALLBACK* TMCC_SERVERINFO_CALLBACK)( tmCommandInfo_t* pCmd, void *context );
typedef BOOL (CALLBACK* TMCC_PROGRESS_CALLBACK)( tmProgressInfo_t* pInfo, void *context );
typedef int  (CALLBACK* TMCC_SERIALDATA_CALLBACK)( HANDLE hTmCC, char *pRecvDataBuffer, int iBufSize, void* context );
typedef int  (CALLBACK* TMCC_ENUMCONNECT_CALLBACK)( HANDLE hTmCC, int iChannel, tmConnectCfg_t* pInfo, int iInfoSize,  void* context );
typedef int  (CALLBACK* TMCC_UPGRADE_CALLBACK)( HANDLE hTmCC, tmUpgradeInfo_t* pInfo, void* context );
typedef int  (CALLBACK* TMCC_STREAMREAD_CALLBACK)( HANDLE hTmCC, tmRealStreamInfo_t* pStreamInfo, void *context );
typedef void (CALLBACK* TMCC_DDRAW_CALLBACK)( HANDLE hTmCC, HDC hDC, RECT* lpRect, int iRegionNum, void* context );
typedef int	 (CALLBACK* TMCC_AVFRAME_CALLBACK)( HANDLE hTmCC, tmAvImageInfo_t* pImage, void* context );
typedef BOOL (CALLBACK* TMCC_DOWNLOADPROGRESS_CALLBACK)( HANDLE hTmCC, tmPlayStateCfg_t* pDownloadState, void *context );
typedef int  (CALLBACK* TMCC_VOICEDATA_CALLBACK)( HANDLE hTmCC, tmVoiceData_t* pVoiceData, void *context );
typedef int  (CALLBACK* TMCC_DEVICELOGIN_CALLBACK)( HANDLE hTmCC, HANDLE hNewTmCC, tmDeviceLoginInfo_t* pDeviceLogin, void *context );
typedef int  (CALLBACK* TMCC_DEVICESTREAM_CALLBACK)( HANDLE hTmCC, HANDLE hNewTmCC, tmDeviceStreamInfo_t* pDeviceStream, void *context );
typedef int  (CALLBACK* TMCC_DEVICETALK_CALLBACK)( HANDLE hTmCC, HANDLE hNewTmCC, tmDeviceTalkInfo_t* pDeviceTalk, void *context );


TMCC_API unsigned int TMCC_CALL TMCC_GetVersion( unsigned int* pBulid );
TMCC_API void TMCC_CALL TMCC_RegisterLogCallBack( TMCC_LOG_CALLBACK pCallBack, void* context );
TMCC_API void TMCC_CALL TMCC_RegisterServerInfoCallBack( TMCC_SERVERINFO_CALLBACK pCallBack, void* context );
TMCC_API int TMCC_CALL TMCC_GetLastError();
TMCC_API HANDLE	TMCC_CALL TMCC_Init( unsigned int dwFlags );
TMCC_API int TMCC_CALL TMCC_Done( HANDLE hTmCC );
TMCC_API void TMCC_CALL TMCC_RegisterConnectCallBack( HANDLE hTmCC, TMCC_CONNECT_CALLBACK pCallBack, void* context );
TMCC_API void TMCC_CALL TMCC_RegisterDataReadCallBack( HANDLE hTmCC, TMCC_DATAREAD_CALLBACK pCallBack, void* context );
TMCC_API void TMCC_CALL TMCC_RegisterProgressCallBack( HANDLE hTmCC, TMCC_PROGRESS_CALLBACK pCallBack, void* context );
TMCC_API int TMCC_CALL TMCC_SetTimeOut( HANDLE hTmCC, int dwTime );
TMCC_API int TMCC_CALL TMCC_GetTimeOut( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_SetAutoReConnect( HANDLE hTmCC, BOOL bAutoConnect );
TMCC_API BOOL TMCC_CALL TMCC_GetAutoReConnect( HANDLE hTmCC );
TMCC_API BOOL TMCC_CALL TMCC_IsConnect( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_Connect( HANDLE hTmCC, tmConnectInfo_t* pConnectInfo, BOOL bSync );
TMCC_API int TMCC_CALL TMCC_DisConnect( HANDLE hTmC );
TMCC_API int TMCC_CALL TMCC_SetConfig( HANDLE hTmCC, tmCommandInfo_t* pCommandInfo );
TMCC_API int TMCC_CALL TMCC_GetConfig( HANDLE hTmCC, tmCommandInfo_t* pCommandInfo );
TMCC_API int TMCC_CALL TMCC_SaveConfig( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_RestoreConfig( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_Reboot( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_ShutDown( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_UpgradeSystem( HANDLE hTmCC, const char *lpszFileName );
TMCC_API int TMCC_CALL TMCC_BackupSystem( HANDLE hTmCC, const char *lpszFileName, int iModal = 0x3E );
TMCC_API int TMCC_CALL TMCC_EnumServer( TMCC_ENUMSERVER_CALLBACK pCallBack, void* context, BOOL bRegisterCallBack = false );
TMCC_API int TMCC_CALL TMCC_RefreshEnumServer();
TMCC_API int TMCC_CALL TMCC_ConfigServer( tmServerCfg_t* pConfig, unsigned int dwFlags = 0 );
TMCC_API int TMCC_CALL TMCC_PtzGetDecoderList( HANDLE hTmCC, tmDecoderInfo_t pInfo[], int* info_num );
TMCC_API int TMCC_CALL TMCC_PtzOpen( HANDLE hTmCC, int iChannel, BOOL bLock = false );
TMCC_API int TMCC_CALL TMCC_PtzClose( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_PtzLock( HANDLE hTmCC, int iChannel );
TMCC_API int TMCC_CALL TMCC_PtzUnLock( HANDLE hTmCC, int iChannel );
TMCC_API int TMCC_CALL TMCC_PtzControl( HANDLE hTmCC, unsigned int dwPTZCommand, unsigned int dwPTZControl, unsigned int dwSpeed );
TMCC_API int TMCC_CALL TMCC_PtzTrans( HANDLE hTmCC, unsigned char *pPTZCodeBuf, int iBufSize );
TMCC_API int TMCC_CALL TMCC_PtzPreset( HANDLE hTmCC, unsigned int dwPTZPresetCmd, unsigned int dwPresetIndex, unsigned int dwSpeed );
TMCC_API int TMCC_CALL TMCC_PtzIntegrate( HANDLE hTmCC, tmPtzParameter_t* pParam, int iParamSize );
TMCC_API void TMCC_CALL TMCC_RegisterSerialDataReadCallBack( HANDLE hTmCC, TMCC_SERIALDATA_CALLBACK pCallBack, void* context );
TMCC_API int TMCC_CALL TMCC_SerialOpen( HANDLE hTmCC, int iSerialPort );
TMCC_API int TMCC_CALL TMCC_SerialSend( HANDLE hTmCC, int iChannel, char *pSendBuf, int iBufSize );
TMCC_API int TMCC_CALL TMCC_SerialClose( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_StartVoiceCom( HANDLE hTmCC, tmConnectInfo_t* pConnectInfo );
TMCC_API int TMCC_CALL TMCC_SetVoiceComClientVolume( HANDLE hTmCC, int iVolume );
TMCC_API int TMCC_CALL TMCC_SetVoiceComClientVolumeZoom( HANDLE hTmCC, float fpmPerNum );
TMCC_API int TMCC_CALL TMCC_SetVoiceComClientMicZoom( HANDLE hTmCC, float fpmPerNum );
TMCC_API int TMCC_CALL TMCC_StopVoiceCom( HANDLE hTmCC );
TMCC_API void TMCC_CALL TMCC_RegisterVoiceDataCallBack( HANDLE hTmCC, TMCC_VOICEDATA_CALLBACK pCallBack, void* context );
TMCC_API int TMCC_CALL TMCC_PutInVoiceData( HANDLE hTmCC, tmVoiceData_t* pVoiceData );
TMCC_API int TMCC_CALL TMCC_OpenVoice( HANDLE hTmCC, tmVoiceHead_t* pVoiceInHead, tmVoiceHead_t* pVoiceOutHead );
TMCC_API int TMCC_CALL TMCC_CloseVoice( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_GetServerWorkState( HANDLE hTmCC, tmWorkState_t* lpWorkState );
TMCC_API int TMCC_CALL TMCC_ConfigServerEx( HANDLE hTmCC, tmServerExCfg_t* pConfig, unsigned int dwFlags );
TMCC_API int TMCC_CALL TMCC_SetPlayWaveFile( HANDLE hTmCC, char *pFileName, unsigned char bCirclePlay );
TMCC_API int TMCC_CALL TMCC_SaveDefaultConfig( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_SetConnectInfo( HANDLE hTmCC, int iChannel, tmConnectCfg_t* pConfig, int size );
TMCC_API int TMCC_CALL TMCC_GetConnectInfo( HANDLE hTmCC, int iChannel, tmConnectCfg_t* pConfig, int size );
TMCC_API int TMCC_CALL TMCC_ClearConnectInfo( HANDLE hTmCC, int iChannel, int iIndex );
TMCC_API int TMCC_CALL TMCC_EnumConnectInfo( HANDLE hTmCC, int iChannel, TMCC_ENUMCONNECT_CALLBACK pCallBack, void* context );
TMCC_API int TMCC_CALL TMCC_SetWindowInfo( HANDLE hTmCC, int iChannel, tmWindowsCfg_t* pConfig, int size );
TMCC_API int TMCC_CALL TMCC_GetWindowInfo( HANDLE hTmCC, int iChannel, tmWindowsCfg_t* pConfig, int size );
TMCC_API int TMCC_CALL TMCC_SetDisplayInfo( HANDLE hTmCC, tmDisplayCfg_t* pConfig, int size );
TMCC_API int TMCC_CALL TMCC_GetDisplayInfo( HANDLE hTmCC, tmDisplayCfg_t* pConfig, int size );
TMCC_API int TMCC_CALL TMCC_SetLockInfo( HANDLE hTmCC, int iChannel, tmLockCfg_t* pConfig, int size );
TMCC_API int TMCC_CALL TMCC_GetLockInfo( HANDLE hTmCC, int iChannel, tmLockCfg_t* pConfig, int size );
TMCC_API int TMCC_CALL TMCC_StartConnect( HANDLE hTmCC, int iChannel );
TMCC_API int TMCC_CALL TMCC_StopConnect( HANDLE hTmCC, int iChannel );
TMCC_API int TMCC_CALL TMCC_SetSerialNumber( HANDLE hTmCC, const char* szSerialNumber );
TMCC_API int TMCC_CALL TMCC_SetOtherParam( HANDLE hTmCC, unsigned int dwFlags, void* buf, int* iLen );
TMCC_API int TMCC_CALL TMCC_UpgradeWebPage( HANDLE hTmCC, const char *lpszPathName );
TMCC_API int TMCC_CALL TMCC_UpgradeKernel( HANDLE hTmCC, const char *lpszName );
TMCC_API int TMCC_CALL TMCC_UpgradeTmccModule( HANDLE hTmCC, const char *lpszName );
TMCC_API int TMCC_CALL TMCC_ConfigUpgradeServer( HANDLE hTmCC, tmUpgradeConfig_t* pConfig );
TMCC_API void TMCC_CALL TMCC_RegisterUpgradeCallBack( HANDLE hTmCC, TMCC_UPGRADE_CALLBACK pCallBack, void* context );
TMCC_API int TMCC_CALL TMCC_StartUpgrade( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_StopUpgrade( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_SendUpgradeMessage( HANDLE hTmCC );
TMCC_API void TMCC_CALL TMCC_RegisterEnumServerCallBack( HANDLE hEnum, TMCC_ENUMSERVER_CALLBACK pCallBack, void* context );
TMCC_API int TMCC_CALL TMCC_StartEnum( HANDLE hEnum );
TMCC_API int TMCC_CALL TMCC_StopEnum( HANDLE hEnum );
TMCC_API int TMCC_CALL TMCC_RefreshEnum( HANDLE hEnum );
TMCC_API int TMCC_CALL TMCC_ConfigServerByMulti( HANDLE hEnum, tmMultiServerCfg_t* pConfig );
TMCC_API void TMCC_CALL TMCC_RegisterStreamCallBack( HANDLE hClient, TMCC_STREAMREAD_CALLBACK pCallBack, void* context );
TMCC_API void TMCC_CALL TMCC_RegisterConnectMessage( HANDLE hClient, HWND hWnd, unsigned int msgID );
TMCC_API int TMCC_CALL TMCC_ConnectStream( HANDLE hClient, tmPlayRealStreamCfg_t* pPlayInfo, HWND hPlayWnd );
TMCC_API int TMCC_CALL TMCC_MakeKeyFrame( HANDLE hClient );
TMCC_API int TMCC_CALL TMCC_SetStreamBufferTime( HANDLE hClient, unsigned int dwTime );
TMCC_API int TMCC_CALL TMCC_RefreshStreamBuffer( HANDLE hClient );
TMCC_API int TMCC_CALL TMCC_SwicthRealStream( HANDLE hClient, int iStreamId );
TMCC_API int TMCC_CALL TMCC_OpenStream( HANDLE hStream, unsigned char* pHeadBuf, int iHeadSize, HWND hPlayWnd, int iPushBufferSize );
TMCC_API int TMCC_CALL TMCC_ResetStream( HANDLE hStream, unsigned char* pHeadBuf, int iHeadSize );
TMCC_API int TMCC_CALL TMCC_CloseStream( HANDLE hStream );
TMCC_API int TMCC_CALL TMCC_GetFileHead( const char* lpszFileName, unsigned char* pHeadBuf, int iBufSize );
TMCC_API int TMCC_CALL TMCC_PutInStream( HANDLE hStream, unsigned char* pStreamBuf, int iStreamSize, BOOL bLost );
TMCC_API HANDLE TMCC_CALL TMCC_FindFirstFile( HANDLE hTmCC, tmFindConditionCfg_t* pFindCondition, tmFindFileCfg_t* lpFindFileData );
TMCC_API int TMCC_CALL TMCC_FindNextFile( HANDLE hTmFile, tmFindFileCfg_t* lpFindFileData );
TMCC_API int TMCC_CALL TMCC_FindCloseFile( HANDLE hTmFile );
TMCC_API int TMCC_CALL TMCC_DownloadFile( HANDLE hTmCC, tmPlayConditionCfg_t* pPlayInfo, const char* lpSaveFileName, BOOL* bCancel, TMCC_DOWNLOADPROGRESS_CALLBACK pCallBack, void* context );
TMCC_API int TMCC_CALL TMCC_DownloadFileA( HANDLE hTmCC, tmDownloadFileCfg_t* pDownloadInfo, int iDownloadNum, BOOL* bCancel, TMCC_DOWNLOADPROGRESS_CALLBACK pCallBack, void* context );
TMCC_API HANDLE TMCC_CALL TMCC_OpenFile( HANDLE hTmCC, tmPlayConditionCfg_t* pPlayInfo, HWND hPlayWnd );
TMCC_API int TMCC_CALL TMCC_CloseFile( HANDLE hTmFile );
TMCC_API int TMCC_CALL TMCC_ReadFile( HANDLE hTmFile, BYTE* buf, int iReadSize );
TMCC_API int TMCC_CALL TMCC_ControlFile( HANDLE hTmFile, tmPlayControlCfg_t* pPlayControl );
TMCC_API int TMCC_CALL TMCC_GetFilePlayState( HANDLE hTmFile, tmPlayStateCfg_t* pState );
TMCC_API void TMCC_CALL TMCC_RegisterFileCallBack( HANDLE hTmFile, tmFileAccessInterface_t* pCallBack, void* context );
TMCC_API void TMCC_CALL TMCC_RegisterAVFrameCallBack( HANDLE hTmCC, TMCC_AVFRAME_CALLBACK pCallBack, void* context );
TMCC_API void TMCC_CALL TMCC_RegisterDrawCallBack( HANDLE hTmCC, TMCC_DDRAW_CALLBACK pCallBack, void* context );
TMCC_API int TMCC_CALL TMCC_SetVolume( HANDLE hTmCC, int iVolume );
TMCC_API int TMCC_CALL TMCC_SetMute( HANDLE hTmCC, BOOL bMute );
TMCC_API int TMCC_CALL TMCC_SetDisplayShow( HANDLE hTmCC, BOOL bShow );
TMCC_API int TMCC_CALL TMCC_SetImageOutFmt( HANDLE hTmCC, unsigned int iOutFmt );
TMCC_API int TMCC_CALL TMCC_GetDisplayRegion( HANDLE hTmCC, int iRegionNum, RECT* pSrcRect, HWND* hDestWnd, BOOL* bEnable );
TMCC_API int TMCC_CALL TMCC_SetDisplayRegion( HANDLE hTmCC, int iRegionNum, RECT* pSrcRect, HWND hDestWnd, BOOL bEnable );
TMCC_API int TMCC_CALL TMCC_RefreshDisplay( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_ClearDisplay( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_GetImageSize( HANDLE hTmCC, int* iWidth, int* iHeight );
TMCC_API int TMCC_CALL TMCC_GetDisplayScale( HANDLE hTmCC, int* iScale );
TMCC_API int TMCC_CALL TMCC_CapturePictureToFile( HANDLE hTmCC, const char* pFileName, const char* pFmt );
TMCC_API int TMCC_CALL TMCC_CapturePictureToBuffer( HANDLE hTmCC, const char* pFmt, void* lpBuffer, int* iBufferSize );
TMCC_API int TMCC_CALL TMCC_OpenAvRender( HANDLE hTmCC, tmAvRenderConfig_t* pCfg, HWND hPlayWnd );
TMCC_API int TMCC_CALL TMCC_CloseAvRender( HANDLE hTmCC );
TMCC_API int TMCC_CALL TMCC_PutinAvFrame( HANDLE hTmCC, tmAvImageInfo_t* pImage );
TMCC_API int TMCC_CALL TMCC_StartListen( HANDLE hTmCC, int iPort );
TMCC_API int TMCC_CALL TMCC_StopListen( HANDLE hTmCC );
TMCC_API void TMCC_CALL TMCC_RegisterDeviceLoginCallBack( HANDLE hTmCC, TMCC_DEVICELOGIN_CALLBACK pCallBack, void* context );
TMCC_API void TMCC_CALL TMCC_RegisterDeviceStreamCallBack( HANDLE hTmCC, TMCC_DEVICESTREAM_CALLBACK pCallBack, void* context );
TMCC_API void TMCC_CALL TMCC_RegisterDeviceTalkCallBack( HANDLE hTmCC, TMCC_DEVICETALK_CALLBACK pCallBack, void* context );
TMCC_API int TMCC_CALL TMCC_StartListenDevice( HANDLE hTmCC, int iPort );
TMCC_API int TMCC_CALL TMCC_StopListenDevice( HANDLE hTmCC );

#ifdef __cplusplus
}
#endif

#endif //__TMCONTROLCLIENT_H__
