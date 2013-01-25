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

/* ��������������������Լ������������ */
typedef struct tmCommandInfo_t
{
	unsigned int		dwSize;				//�ýṹ�Ĵ�С��������дΪsizeof(tmCommandInfo_t)	
	unsigned int		dwMajorCommand;		//����Ϣ�������������
	unsigned int		dwMinorCommand;		//����Ϣ�������������	
	unsigned short		iChannel;			//ͨ���ţ���ͨ����Ҫ���dwMajorCommand���ж��Ƿ���Ч
	unsigned short		iStream;			//��ͨ���ţ���ͨ����Ҫ���dwMajorCommand���ж��Ƿ���Ч
	void*				pCommandBuffer;		//��Ϣ��ݻ���
	int					iCommandBufferLen;	//��Ϣ��ݻ����С
	int					iCommandDataLen;	//��Ϣ���ʵ�ʴ�С
	unsigned int		dwResult;			//��Ϣ���Ʒ��ؽ��
}tmCommandInfo_t;

/*������ϵͳ������Ϣ*/
typedef struct tmProgressInfo_t
{
	HANDLE			hTmcc;					//�ӿڿ��ƾ��
	unsigned int	dwModalID;				//ģ��ID��
	unsigned int	dwModalSize;			//ģ����ݴ�С
	unsigned int	dwModalPos;				//��ݴ��䵱ǰλ��
}tmProgressInfo_t;

//�������Զ������ýṹ
typedef struct tmUpgradeConfig_t
{
	unsigned int		dwSize;					//���ṹ��С
	
	int					iListenPort;			//����������˿ڣ��豸���������Ӵ˶˿�

	int					iServerListCount;		//�������б���Ϊ0ʱ�����������л�����	
	tmServerInfoEx_t*	pServerInfoList;		//��Ҫ����豸�б?�ɷ�������Ϣ����б�
	
	int					iFileType;				//��İ�����0-���ļ�,1-IE���,2-�ں����
	char				szFileName[MAX_PATH];	//����ļ����IE��Ŀ¼

	BOOL				bAutoReboot;			//����ɺ��Զ�����
}tmUpgradeConfig_t;

//�������Զ�����Ϣ�ṹ
typedef struct tmUpgradeInfo_t
{
	unsigned int		dwSize;					//���ṹ��С
	tmServerInfoEx_t*	pServerInfo;			//�豸��Ϣ
	unsigned int		dwResultCode;			//ģ�������,��ο�������Զ���������붨��˵��	
	int					iUpgradeProgress;		//����0-100
}tmUpgradeInfo_t;

//������ݽṹ����
typedef struct tmAvRenderConfig_t
{
	unsigned int	dwSize;

	//��Ƶ
	BOOL			bVideo;				//�Ƿ����Ƶ
	int				iWidth;				//��Ƶ��
	int				iHeight;			//��Ƶ��
	int				iFrameRate;			//֡��*1000

	//��Ƶ
	BOOL			bAudio;				//�Ƿ����Ƶ
	unsigned char	byBitsPerSample;	//��Ƶ����λ��
	unsigned char	byChannels;			//��Ƶ�������
	int				iSamplesPerSec;		//��Ƶ������
}tmAvRenderConfig_t;

//�����Խ����ͷ
typedef struct tmVoiceHead_t
{
	unsigned int	dwSize;	
	unsigned char	byCompressFormat;	//��Ƶ�����ʽ0-MP2,1-AAC,2-S16LE,3-MULAW/G.711,4-ALAW/G.711,5-G.722,6-G.723,7-G.726,8-G.729
	unsigned char	byTemp;				//����
	unsigned char	byBitsPerSample;	//��Ƶ����λ��
	unsigned char	byChannels;			//��Ƶ�������
	int				iSamplesPerSec;		//��Ƶ������
	int				iAudioBitRate;		//��Ƶ������С
}tmVoiceHead_t;

//������ݽṹ����
typedef struct tmVoiceData_t
{
	unsigned int	dwSize;				//���ṹ��С
	unsigned char	byDataType;			//��Ƶ�������0��ͷ��1����ݰ�
	unsigned char	byTemp[3];			//����
	void*			pData;				//��Ƶ��ݻ��壬û�а�ͷ��һ���������
	int				iDataSize;			//��Ƶ��ݻ����С
	unsigned int	dwTimeStamp;		//��Ƶ��ʱ���С������
}tmVoiceData_t;

//�����ͷ��Ϣ
typedef struct tmStreamHeadInfo_t
{
	unsigned int	dwSize;

	//��Ƶ
	BOOL			bVideo;				//�Ƿ����Ƶ
	unsigned int	dwVideoTag;			//������Tag
	unsigned int	dwVideoId;			//��ID
	int				iWidth;				//��Ƶ��
	int				iHeight;			//��Ƶ��
	int				iDisplayScale;		//��ʾ����*1000
	int				iFrameRate;			//֡��*1000
	int				iVideoBitRate;		//���������������С
	BOOL			bInterlacer;		//��Ƶ��Interlacer

	//��Ƶ
	BOOL			bAudio;				//�Ƿ�ɼ���Ƶ
	unsigned int	dwAudioTag;			//��Ƶ������Tag
	unsigned int	dwAudioId;			//��Ƶ��ID	
	int				iBitsPerSample;		//��Ƶ����λ��
	int				iChannels;			//��Ƶ�������
	int				iSamplesPerSec;		//��Ƶ������
	int				iAudioBitRate;		//����Ƶ����������С
	unsigned int	dwSampleSize;		//һ����Ƶ������֡
	
}tmStreamHeadInfo_t;

//�豸������¼��Ϣ�ṹ����
typedef struct tmDeviceLoginInfo_t
{
	unsigned int	dwSize;
	unsigned int	dwDeviceIp;
	unsigned int	dwFactoryId;
	char			sDeviceId[64];
	char			sDeviceSn[48];
}tmDeviceLoginInfo_t;
//�豸��������ϴ���Ϣ�ṹ����
typedef struct tmDeviceStreamInfo_t
{
	unsigned int	dwSize;				//���ṹ��С
	unsigned int	dwDeviceIp;			//�豸��ַ
	unsigned int	dwFactoryId;		//�豸�ĳ��̺�
	char			sDeviceId[64];		//�豸��¼ID��
	char			sDeviceSn[48];		//�豸Ψһ���к�
	unsigned char	byChannel;			//�ϴ���ͨ��
	unsigned char	byStream;			//�ϴ�������
}tmDeviceStreamInfo_t;
//�豸���������Խ���Ϣ�ṹ����
typedef struct tmDeviceTalkInfo_t
{
	unsigned int	dwSize;
	unsigned int	dwDeviceIp;
	unsigned int	dwFactoryId;
	char			sDeviceId[64];
	char			sDeviceSn[48];
}tmDeviceTalkInfo_t;


//������Զ����������˵������
#define AUTO_UPGRADE_CODE_REQUEST			0x01//�豸������
#define AUTO_UPGRADE_CODE_START				0x02//�豸��ʼ��
#define AUTO_UPGRADE_CODE_SUCCESS			0x03//�豸�ɹ���
#define AUTO_UPGRADE_CODE_STATE				0x04//�豸����
#define AUTO_UPGRADE_CODE_NETWORKERROR		0x05//�豸�ͷ��������粻ͨ
#define AUTO_UPGRADE_CODE_CANTCONNECT		0x06//�豸��������ʱ�������
#define AUTO_UPGRADE_CODE_WRITEERROR		0x07//�豸��Firmareʱ�������

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


/* �����ص������� */
//��ʽ�ص�����ֻ���ڿ���ģʽ�²���Ч
typedef void (CALLBACK* TMCC_LOG_CALLBACK)( HANDLE hTmCC, unsigned int code, const char* info, void* context );
//������Ϣ�ص�����ͨ������Եõ��첽��ʽ�ͶϿ�����״̬
typedef BOOL (CALLBACK* TMCC_CONNECT_CALLBACK)( HANDLE hTmCC, BOOL bConnect, unsigned int dwResult, void *context );
//��Ϣ��ȡ�ص�����ͨ������Եõ���������Ϣ��ͬʱ�첽��ʽ�ķ�������ݻ��Ҳ��ͨ��ûص�
typedef int  (CALLBACK* TMCC_DATAREAD_CALLBACK)( HANDLE hTmcc, tmCommandInfo_t* pCmd, void *context );
//�������оٻص�������
typedef BOOL (CALLBACK* TMCC_ENUMSERVER_CALLBACK)( tmServerInfo_t* pEnum, void *context );
//���������ӻص�����ͨ������Եõ���������½�����߷����������ӵı�����Ϣ
typedef BOOL (CALLBACK* TMCC_SERVERINFO_CALLBACK)( tmCommandInfo_t* pCmd, void *context );
//������ģ�����Ȼص�����
typedef BOOL (CALLBACK* TMCC_PROGRESS_CALLBACK)( tmProgressInfo_t* pInfo, void *context );
//ͨ��ͨ����ݻص�����
typedef int  (CALLBACK* TMCC_SERIALDATA_CALLBACK)( HANDLE hTmCC, char *pRecvDataBuffer, int iBufSize, void* context );
//add by stone 20070930
//������Ϣö�ٻص�����
typedef int  (CALLBACK* TMCC_ENUMCONNECT_CALLBACK)( HANDLE hTmCC, int iChannel, tmConnectCfg_t* pInfo, int iInfoSize,  void* context );
//�������Զ�����Ϣ����ص�
typedef int  (CALLBACK* TMCC_UPGRADE_CALLBACK)( HANDLE hTmCC, tmUpgradeInfo_t* pInfo, void* context );
//������ص�
typedef int  (CALLBACK* TMCC_STREAMREAD_CALLBACK)( HANDLE hTmCC, tmRealStreamInfo_t* pStreamInfo, void *context );
//��Ƶ��ʾ�ص�
typedef void (CALLBACK* TMCC_DDRAW_CALLBACK)( HANDLE hTmCC, HDC hDC, RECT* lpRect, int iRegionNum, void* context );
//����֡����ص�
typedef int	 (CALLBACK* TMCC_AVFRAME_CALLBACK)( HANDLE hTmCC, tmAvImageInfo_t* pImage, void* context );
//�ļ����ؽ�Ȼص�
typedef BOOL (CALLBACK* TMCC_DOWNLOADPROGRESS_CALLBACK)( HANDLE hTmCC, tmPlayStateCfg_t* pDownloadState, void *context );
//�Խ���Ƶ�������ص�
typedef int  (CALLBACK* TMCC_VOICEDATA_CALLBACK)( HANDLE hTmCC, tmVoiceData_t* pVoiceData, void *context );
//�豸������¼�ص���ע��hNewTmCCΪ����ɵľ��
typedef int  (CALLBACK* TMCC_DEVICELOGIN_CALLBACK)( HANDLE hTmCC, HANDLE hNewTmCC, tmDeviceLoginInfo_t* pDeviceLogin, void *context );
//�豸����������ӻص���ע��hNewTmCCΪ����ɵľ��
typedef int  (CALLBACK* TMCC_DEVICESTREAM_CALLBACK)( HANDLE hTmCC, HANDLE hNewTmCC, tmDeviceStreamInfo_t* pDeviceStream, void *context );
//�豸�����������ӻص���ע��hNewTmCCΪ����ɵľ��
typedef int  (CALLBACK* TMCC_DEVICETALK_CALLBACK)( HANDLE hTmCC, HANDLE hNewTmCC, tmDeviceTalkInfo_t* pDeviceTalk, void *context );


/*
 *��  ��: TMCC_GetVersion 
 *˵  ��: ��ñ��ͻ��˿�汾��Ϣ
 *��  ��: pBulidΪ��ű������
 *����ֵ: ���ذ汾�ţ���ʽ��<����ֵΪ10000����汾V1.0.0.00>
 */
TMCC_API unsigned int TMCC_CALL TMCC_GetVersion( unsigned int* pBulid );

/*
 *��  ��: TMCC_RegisterLogCallBack 
 *˵  ��: ע�������Ϣ�ص�����ֻ���ڿ���ģʽ�²���Ч
 *��  ��: pCallBackΪ�ص�����ָ�룬contextΪ�������Զ������
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterLogCallBack( TMCC_LOG_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_RegisterServerInfoCallBack 
 *˵  ��: ע���������Ϣ��Ϣ�ص�����ͨ��˻ص����Եõ��������Թ������ĵ������Լ�������Ϣ
 *��  ��: pCallBackΪ�ص�����ָ�룬contextΪ�������Զ������
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterServerInfoCallBack( TMCC_SERVERINFO_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_GetLastError 
 *˵  ��: ��õ�ǰ�Ĵ�����
 *��  ��: ��
 *����ֵ: ���ش�����
 */
TMCC_API int TMCC_CALL TMCC_GetLastError();

/////////////////////////////////////////////////////////////////////
///////////////////////////�豸�����ÿ��ƽӿ�//////////////////////
/////////////////////////////////////////////////////////////////////
/*
 *��  ��: TMCC_Init 
 *˵  ��: ��ʼ�������һ�����������ƾ���������нӿں��������˾����ʷ�����
 *��  ��: dwFlags������������Ϊ0
 *����ֵ: �ɹ����ؿ��ƾ��ʧ�ܷ���NULL
 */
TMCC_API HANDLE	TMCC_CALL TMCC_Init( unsigned int dwFlags );

/*
 *��  ��: TMCC_Done 
 *˵  ��: �ͷŷ��������ƾ�������Դ
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_Done( HANDLE hTmCC );

/*
 *��  ��: TMCC_RegisterConnectCallBack 
 *˵  ��: ע��������Ϣ���ػص������첽���ӳɹ�ͨ��ûص�����أ��������Ͽ�����Ҳͨ��ûص�
 *��  ��: hTmCCΪ���������ƾ��pCallBackΪ�ص�����ָ�룬contextΪ�Զ������
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterConnectCallBack( HANDLE hTmCC, TMCC_CONNECT_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_RegisterDataReadCallBack 
 *˵  ��: ע���������Ϣ��ȡ�ص������첽��ʽͨ�����÷�������Ϣ�������籨����ϢҲͨ����õ�
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��pCallBackΪ�ص�����ָ�룬contextΪ�Զ������
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterDataReadCallBack( HANDLE hTmCC, TMCC_DATAREAD_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_RegisterProgressCallBack 
 *˵  ��: ע�������Ϣ�ص�����ֻ���ڿ�����ģʽ�²���Ч
 *��  ��: pCallBackΪ�ص�����ָ�룬contextΪ�������Զ������
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterProgressCallBack( HANDLE hTmCC, TMCC_PROGRESS_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_SetTimeOut 
 *˵  ��: �����������ͨѶ�����ĳ�ʱʱ�䣬����Ҫ��TMCC_Connect����ǰ���ò���Ч
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��dwTimeʱ��ֵ��λΪ����ϵͳĬ��Ϊ2000����
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetTimeOut( HANDLE hTmCC, int dwTime );

/*
 *��  ��: TMCC_GetTimeOut 
 *˵  ��: ����������ͨѶ�����ĳ�ʱʱ�䣬�κ�ʱ���ܵ���
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��
 *����ֵ: �ɹ�����ʱ��ֵ�����󷵻�0
 */
TMCC_API int TMCC_CALL TMCC_GetTimeOut( HANDLE hTmCC );

/*
 *��  ��: TMCC_SetAutoReConnect 
 *˵  ��: ���÷��������Ƿ��Զ��������ӣ�ע�����Ҫע�����ӻص������һ��ݻص������ֵ�ж��Ƿ�����
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��bAutoConnectΪ�Զ����ӱ�־��ϵͳĬ��ΪFALSE
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetAutoReConnect( HANDLE hTmCC, BOOL bAutoConnect );

/*
 *��  ��: TMCC_GetAutoReConnect 
 *˵  ��: ��÷��������Ƿ��Զ��������ӱ�־���κ�ʱ���ܵ���
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��
 *����ֵ: �ɹ������Զ����ӱ�־�����󷵻�FALSE
 */
TMCC_API BOOL TMCC_CALL TMCC_GetAutoReConnect( HANDLE hTmCC );

/*
 *��  ��: TMCC_IsConnect 
 *˵  ��: ��õ�ǰ�Ƿ������ӷ��������κ�ʱ���ܵ���
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��
 *����ֵ: �ɹ������������־�����󷵻�FALSE
 */
TMCC_API BOOL TMCC_CALL TMCC_IsConnect( HANDLE hTmCC );

/*
 *��  ��: TMCC_Connect 
 *˵  ��: ���ӷ�����������¼�������������øú���ɹ������Ҫ����TMCC_DisConnect������һ�ε��ã�
		  ������һ�첽��ʽ�����ӳɹ���ͨ�����ӻص�����ӳ����ûע�����ӻص������첽���ӻ�ʧ��
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��pConnectInfoΪ�û�������Ϣ��bSyncΪ���ӷ�ʽ<�첽��ͬ��>
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_Connect( HANDLE hTmCC, tmConnectInfo_t* pConnectInfo, BOOL bSync );

/*
 *��  ��: TMCC_DisConnect 
 *˵  ��: �Ͽ���������������
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_DisConnect( HANDLE hTmC );

/*
 *��  ��: TMCC_SetConfig
 *˵  ��: �������������ã��ú����������õĲ����ڷ�������������ᶪʧ����ǵ���TMCC_SaveConfig��ȷ����
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��
 		  pCommandInfo������Ϣ�ṹָ�룬���а�������Ҫ����������
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetConfig( HANDLE hTmCC, tmCommandInfo_t* pCommandInfo );

/*
 *��  ��: TMCC_GetConfig
 *˵  ��: ��ȡ����������
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��
 		  pCommandInfo������Ϣ�ṹָ�룬���а�������Ҫ����������
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_GetConfig( HANDLE hTmCC, tmCommandInfo_t* pCommandInfo );

/*
 *��  ��: TMCC_SaveConfig
 *˵  ��: ������������ò����������Flash�Ĳ�д����һ�����ޣ����鲻Ҫ��������
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SaveConfig( HANDLE hTmCC );

/*
 *��  ��: TMCC_RestoreConfig
 *˵  ��: �ָ����������ò���ΪϵͳĬ��ֵ
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_RestoreConfig( HANDLE hTmCC );

/*
 *��  ��: TMCC_Reboot
 *˵  ��: ����������������������ͻ��˻��Զ������������ڼ��������þ���Ч
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_Reboot( HANDLE hTmCC );

/*
 *��  ��: TMCC_ShutDown
 *˵  ��: �رշ��������رպ���������������Զ��Ͽ�
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_ShutDown( HANDLE hTmCC );

/*
 *��  ��: TMCC_UpgradeSystem
 *˵  ��: �������ϵͳ����ϵͳҲҪ����Flash�����Խ��鲻Ҫ������ϵͳ��
 		  �ú���Ϊ������ã������ڼ��������в�����Ч
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��lpszFileNameΪϵͳ����ȫ·����
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_UpgradeSystem( HANDLE hTmCC, const char *lpszFileName );

/*
 *��  ��: TMCC_BackupSystem
 *˵  ��: ���������ϵͳΪ�����ļ����ú���Ϊ������ã������ڼ��������в�����Ч
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��lpszFileNameΪϵͳ����ȫ·����
 *		  iModalΪҪ���ݵ�ģ���־���ֱ���λ��ʾ�������Ϊ��ʼ :
		  0λ��ʾ��������ģ�飬1λ��ʾ�����������ģ��, 2λ��ʾ���ݲ���ģ�飬3λ��ʾ����PTZģ�飬
		  4λ��ʾ����WEBģ�飬5λ��ʾ������չģ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_BackupSystem( HANDLE hTmCC, const char *lpszFileName, int iModal = 0x3E );

/*
 *��  ��: TMCC_EnumServer
 *˵  ��: �о������еķ��������оٳ������豸������Ϊ�ο���������Щ�����оٵ�
 *��  ��: pCallBackΪ�ص�����ָ�룻contextΪ���������õ�������ָ��
 *		  �ں���pCallBack�з���TRUE��ʾ�����о٣�FALSEΪֹͣ�о�
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_EnumServer( TMCC_ENUMSERVER_CALLBACK pCallBack, void* context, BOOL bRegisterCallBack = false );

/*
 *��  ��: TMCC_RefreshEnumServer
 *˵  ��: ˢ������������б�
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_RefreshEnumServer();

/*
 *��  ��: TMCC_ConfigServer
 *˵  ��: ���÷������ĵ�ַ��Ϣ
 *��  ��: dwFlagsΪ�������ͣ���ͨ��ʲô��ʽ���ã�Ŀǰ��֧������
 *		  pConfigΪ�µķ�������Ϣ
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_ConfigServer( tmServerCfg_t* pConfig, unsigned int dwFlags = 0 );

//��̨����
/*
 *��  ��: TMCC_PtzGetDecoderList
 *˵  ��: ��÷��������ý�����Э���б�
 *��  ��: pInfoΪҪ��Э����б?info_numΪ����Ϊ�б����������Ϊ��ǰЭ�����
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_PtzGetDecoderList( HANDLE hTmCC, tmDecoderInfo_t pInfo[], int* info_num );

/*
 *��  ��: TMCC_PtzOpen
 *˵  ��: ����̨���ƣ�Ҫ���Ʒ�������̨�������ȴ򿪶�Ӧ̨��
 *��  ��: iChannelΪ��̨��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_PtzOpen( HANDLE hTmCC, int iChannel, BOOL bLock = false );

/*
 *��  ��: TMCC_PtzClose
 *˵  ��: �ر���̨����
 *��  ��: hTmCCΪ���ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_PtzClose( HANDLE hTmCC );

/*
 *��  ��: TMCC_PtzLock
 *˵  ��: ����̨���ƣ������ȴ򿪶�Ӧ̨��
 *��  ��: hTmCCΪ���ƾ��, iChannelΪ��̨��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_PtzLock( HANDLE hTmCC, int iChannel );

/*
 *��  ��: TMCC_PtzUnLock
 *˵  ��: ������̨����
 *��  ��: hTmCCΪ���ƾ��, iChannelΪ��̨��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_PtzUnLock( HANDLE hTmCC, int iChannel );

/*
 *��  ��: TMCC_PtzControl
 *˵  ��: ��̨���������Щ����þ���ѡ��Э��ת������������ô˹��ܱ���ѡ����ȷ����Э��
 *��  ��: hTmCCΪ���ƾ��dwPTZCommandΪ��̨�������dwPTZControlΪ���Ʒ���0-�ر�1-��ʼ��dwSpeedΪ�˶��ٶ�
 *		  ���NVS������ȷ�Ķ�ӦЭ�飬������	TMCC_PtzTrans�����ϲ��������	
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_PtzControl( HANDLE hTmCC, unsigned int dwPTZCommand, unsigned int dwPTZControl, unsigned int dwSpeed );

/*
 *��  ��: TMCC_PtzTrans
 *˵  ��: Ϊ��̨����ֱ��������������ý���Э��ת��
 *��  ��: hTmCCΪ���ƾ��pPTZCodeBufΪ�������ݻ��壬iBufSizeΪ��ݴ�С�����ֵ����С��128
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_PtzTrans( HANDLE hTmCC, unsigned char *pPTZCodeBuf, int iBufSize );

/*
 *��  ��: TMCC_PtzPreset
 *˵  ��: ��̨Ԥ�õ����
 *��  ��: hTmCCΪ���ƾ��dwPTZPresetCmdΪ��̨��������ţ�dwPresetIndexΪԤ�õ�ţ�dwSpeedΪ�ٶ�
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_PtzPreset( HANDLE hTmCC, unsigned int dwPTZPresetCmd, unsigned int dwPresetIndex, unsigned int dwSpeed );

/*
 *��  ��: TMCC_PtzIntegrate
 *˵  ��: Ϊ��̨�ۺϿ��ƣ���Ҫ��ֱ̨�Ӻ�һ���֧��
 *��  ��: hTmCCΪ���ƾ��pParamΪ���Ƶľ������ṹָ�룬iParamSizeΪ�ṹ��С��С�����ֵ����С��128
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_PtzIntegrate( HANDLE hTmCC, tmPtzParameter_t* pParam, int iParamSize );

//͸��ͨ������
/*
 *��  ��: TMCC_RegisterSerialDataReadCallBack
 *˵  ��: ע�������������ݻ�ûص�����
 *��  ��: hTmCCΪ���ƾ��, , pCallBackΪ��ȡͨ���Ļش���ݣ�contextΪ�û��Զ������
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterSerialDataReadCallBack( HANDLE hTmCC, TMCC_SERIALDATA_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_SerialOpen
 *˵  ��: ������������͸��ͨ������
 *��  ��: hTmCCΪ���ƾ��, iSerialPort==0ʱ��232,==1��485
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SerialOpen( HANDLE hTmCC, int iSerialPort );

/*
 *��  ��: TMCC_SerialSend
 *˵  ��: �����������ͨ����ݣ���Щ��ݷ���������������ֱ���ͳ�
 *��  ��: hTmCCΪ���ƾ��iChannelΪ���͵�ͨ���Ž�485��Ч
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SerialSend( HANDLE hTmCC, int iChannel, char *pSendBuf, int iBufSize );

/*
 *��  ��: TMCC_SerialClose
 *˵  ��: �ر����������ͨ������
 *��  ��: hTmCCΪ���ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SerialClose( HANDLE hTmCC );

///////////////////////////////////////////////////////////////////////
///////////////////////////////�����Խ�////////////////////////////////
///////////////////////////////////////////////////////////////////////
/*
 *��  ��: TMCC_StartVoiceCom
 *˵  ��: ���������Խ�
 *��  ��: hTmCCΪ���ƾ��pConnectInfoΪ�����������ΪNULL
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_StartVoiceCom( HANDLE hTmCC, tmConnectInfo_t* pConnectInfo );

/*
 *��  ��: TMCC_SetVoiceComClientVolume
 *˵  ��: ���ÿͻ�����������Ӳ��������С
 *��  ��: hTmCCΪ���ƾ��iVolumeΪ����ֵ-10000~0,-10000��С,0���
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetVoiceComClientVolume( HANDLE hTmCC, int iVolume );

/*
 *��  ��: TMCC_SetVoiceComClientVolumeZoom
 *˵  ��: ���ÿͻ���������������Ŵ�ֵ
 *��  ��: hTmCCΪ���ƾ��fpmPerNumΪ�����Ŵ�ֵ0 < fpmPerNum < 10.0
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetVoiceComClientVolumeZoom( HANDLE hTmCC, float fpmPerNum );

/*
 *��  ��: TMCC_SetVoiceComClientMicZoom
 *˵  ��: ���ÿͻ��������ɼ�������˷�������С
 *��  ��: hTmCCΪ���ƾ��fpmPerNumΪ�����Ŵ�ֵ0 < fpmPerNum < 10.0
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetVoiceComClientMicZoom( HANDLE hTmCC, float fpmPerNum );

/*
 *��  ��: TMCC_StopVoiceCom
 *˵  ��: �ر���������������ӽ�
 *��  ��: hTmCCΪ���ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_StopVoiceCom( HANDLE hTmCC );

/*
 *��  ��: TMCC_RegisterVoiceDataCallBack 
 *˵  ��: ע�������Խ���ݻ�ûص���ͨ��˻ص����Եõ����������������
 *��  ��: pCallBackΪ�ص�����ָ�룬contextΪ�������Զ������
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterVoiceDataCallBack( HANDLE hTmCC, TMCC_VOICEDATA_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_PutInVoiceData
 *˵  ��: ���������Խ����
 *��  ��: hTmCCΪ���ƾ��pVoiceDataΪ��Ƶ��ݽṹ
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_PutInVoiceData( HANDLE hTmCC, tmVoiceData_t* pVoiceData );

/*
 *��  ��: TMCC_OpenVoice
 *˵  ��: �������Խ���ݽ������������
 *��  ��: hTmCCΪ���ƾ��pVoiceHeadΪ��Ƶ���ͷ�ṹ
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_OpenVoice( HANDLE hTmCC, tmVoiceHead_t* pVoiceInHead, tmVoiceHead_t* pVoiceOutHead );

/*
 *��  ��: TMCC_CloseVoice
 *˵  ��: �ر������Խ���ݽ������������
 *��  ��: hTmCCΪ���ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_CloseVoice( HANDLE hTmCC );


//������״̬
/*
 *��  ��: TMCC_GetServerWorkState
 *˵  ��: �õ���������ǰ����״̬
 *��  ��: hTmCCΪ���ƾ��lpWorkStatewΪ��ŷ�����״̬��Ϣ�Ľṹָ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_GetServerWorkState( HANDLE hTmCC, tmWorkState_t* lpWorkState );

/*
 *��  ��: TMCC_ConfigServerEx
 *˵  ��: ���÷������ĵ�ַ��Ϣ��1.0.0.09���
 *��  ��: dwFlagsΪ�������ͣ���ͨ��ʲô��ʽ���ã�Ŀǰ��֧������
 *		  pConfigΪ�µķ�������Ϣ
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_ConfigServerEx( HANDLE hTmCC, tmServerExCfg_t* pConfig, unsigned int dwFlags );

//////////////////////////////////////////////////////////////////////////
//2007/07/16 franxkia �¼�

//���ò��ŵ�wave�ļ�
/*
 *��  ��: TMCC_SetPlayWaveFile
 *˵  ��: PC����WAVE�ļ�,ͨ�������Խ�ͨ�����͵�DVS,DVS���
 *��  ��: hTmCCΪ���ƾ��pFileNameΪ�ļ���ȫ·��,bPlayNumΪҪ���ŵĴ���
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetPlayWaveFile( HANDLE hTmCC, char *pFileName, unsigned char bCirclePlay );

/*
 *��  ��: TMCC_SaveDefaultConfig
 *˵  ��: ���������Ĭ�����ò����������Flash�Ĳ�д����һ�����ޣ����鲻Ҫ��������
 *��  ��: hTmCCΪTMCC_Init���صķ��������ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SaveDefaultConfig( HANDLE hTmCC );

//////////////////////////////////////////////////////////////////////////////
///////////��Ƶ������ֱ�Ӳ�������ӿڶ��� add by stone 20070930///////////////
//////////////////////////////////////////////////////////////////////////////
/*
 *��  ��: TMCC_SetConnectInfo
 *˵  ��: ���÷�������������Ϣ��1.0.0.20��ӣ������ѭ����������룬����Ƿ�ѭ���Ǿʹ���
 *��  ��: pConfigΪ������Ϣ, iChannelΪͨ����(�򴰿ں�)��sizeΪpConfig�Ļ����С
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetConnectInfo( HANDLE hTmCC, int iChannel, tmConnectCfg_t* pConfig, int size );

/*
 *��  ��: TMCC_GetConnectInfo
 *˵  ��: �õ���ǰ��������Ϣ��1.0.0.20���
 *��  ��: pConfigΪ������Ϣ, iChannelΪͨ����(�򴰿ں�)��sizeΪpConfig�Ļ����С
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_GetConnectInfo( HANDLE hTmCC, int iChannel, tmConnectCfg_t* pConfig, int size );

/*
 *��  ��: TMCC_ClearConnectInfo
 *˵  ��: ���ǰ��������Ϣ�������ѭ�����������ָ��ѭ����ţ�1.0.0.20���
 *��  ��: iChannelΪͨ����(�򴰿ں�)��iIndexΪΪѭ�������Ϊ-1��Ϊ�������
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_ClearConnectInfo( HANDLE hTmCC, int iChannel, int iIndex );

/*
 *��  ��: TMCC_GetEnumConnectInfo
 *˵  ��: ö�ٷ�������������Ϣ��ͨ��ص�������ص��п��Է�ӳͨ���ţ��Ƿ���ѭ�����ӵ���Ϣ��1.0.0.20���
 *��  ��: iChannelΪͨ����(�򴰿ں�)��pCallBackΪ�ص�����ָ�룬contextΪ�û������ָ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_EnumConnectInfo( HANDLE hTmCC, int iChannel, TMCC_ENUMCONNECT_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_SetWindowInfo
 *˵  ��: ������ʾ�Ĵ�����Ϣ��1.0.0.20���
 *��  ��: iChannelΪͨ����(�򴰿ں�)��pConfigΪ������Ϣָ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetWindowInfo( HANDLE hTmCC, int iChannel, tmWindowsCfg_t* pConfig, int size );

/*
 *��  ��: TMCC_GetWindowInfo
 *˵  ��: ��ȡ��ʾ�Ĵ�����Ϣ��1.0.0.20���
 *��  ��: iChannelΪͨ����(�򴰿ں�)��pConfigΪ������Ϣָ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_GetWindowInfo( HANDLE hTmCC, int iChannel, tmWindowsCfg_t* pConfig, int size );

/*
 *��  ��: TMCC_SetDisplayInfo
 *˵  ��: ���ý���������ʾ��Ϣ���絥���Ŵ��,1.0.0.20���
 *��  ��: pConfigΪ��ʾ��Ϣָ�룬sizeΪ��ݻ����С
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetDisplayInfo( HANDLE hTmCC, tmDisplayCfg_t* pConfig, int size );

/*
 *��  ��: TMCC_GetDisplayInfo
 *˵  ��: ��ȡ����������ʾ��Ϣ���絥���Ŵ��,1.0.0.20���
 *��  ��: pConfigΪ��ʾ��Ϣָ�룬sizeΪ��ݻ����С
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_GetDisplayInfo( HANDLE hTmCC, tmDisplayCfg_t* pConfig, int size );

/*
 *��  ��: TMCC_SetLockInfo
 *˵  ��: ����ͨ����������Ϣ���絥�Ƿ�ѭ���л���, ע��ѭ�е�ʱ����������������Ϣʱ����,1.0.0.20���
 *��  ��: iChannelΪͨ����,pConfigΪ��ʾ��Ϣָ�룬sizeΪ��ݻ����С
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetLockInfo( HANDLE hTmCC, int iChannel, tmLockCfg_t* pConfig, int size );

/*
 *��  ��: TMCC_GetLockInfo
 *˵  ��: ��ȡͨ����������Ϣ���絥�Ƿ�ѭ���л���, ע��ѭ�е�ʱ����������������Ϣʱ����,1.0.0.20���
 *��  ��: iChannelΪͨ����,pConfigΪ��ʾ��Ϣָ�룬sizeΪ��ݻ����С
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_GetLockInfo( HANDLE hTmCC, int iChannel, tmLockCfg_t* pConfig, int size );

/*
 *��  ��: TMCC_StartConnect
 *˵  ��: ʹ������������,1.0.0.20���
 *��  ��: iChannelΪͨ����
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_StartConnect( HANDLE hTmCC, int iChannel );

/*
 *��  ��: TMCC_StopConnect
 *˵  ��: ʹ�������ر�����,1.0.0.20���
 *��  ��: iChannelΪͨ����
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_StopConnect( HANDLE hTmCC, int iChannel );

/*
 *��  ��: TMCC_SetSerialNumber
 *˵  ��: �������ӵ�Ψһ������Ϣ
 *��  ��: hTmCC���ƾ��, szSerialNumberΪ���к�
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetSerialNumber( HANDLE hTmCC, const char* szSerialNumber );

/*
 *��  ��: TMCC_SetOtherParam
 *˵  ��: ����һЩ��չ��Ϣ���ѷ���
 *��  ��: hTmCCΪ���ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetOtherParam( HANDLE hTmCC, unsigned int dwFlags, void* buf, int* iLen );

/*
 *��  ��: TMCC_UpgradeWebPage
 *˵  ��: ��������е���ҳ����ҳ�����û�������ƣ��ռ��С����5M��
 *��  ��: hTmCCΪ���ƾ��, lpszPathName�����ҳ��Ŀ¼
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_UpgradeWebPage( HANDLE hTmCC, const char *lpszPathName );

/*
 *��  ��: TMCC_UpgradeKernel
 *˵  ��: ���������Firmware
 *��  ��: hTmCCΪ���ƾ��, lpszNameΪFirmware���
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_UpgradeKernel( HANDLE hTmCC, const char *lpszName );

/*
 *��  ��: TMCC_UpgradeTmccModule
 *˵  ��: ���������Tmcc��չģ��
 *��  ��: hTmCCΪ���ƾ��, lpszNameΪ��չģ��Ŀ¼���
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_UpgradeTmccModule( HANDLE hTmCC, const char *lpszName );

//////////////////////////////////////////////////////////////
///////////////////�豸�Զ���ģ��///////////////////////////
//////////////////////////////////////////////////////////////
/*
 *��  ��: TMCC_ConfigUpgradeServer
 *˵  ��: �����Զ��������
 *��  ��: hTmCCΪ����������ƾ��
 *����ֵ: �ɹ���������������ƾ��ʧ�ܷ���NULL
 */
TMCC_API int TMCC_CALL TMCC_ConfigUpgradeServer( HANDLE hTmCC, tmUpgradeConfig_t* pConfig );

/*
 *��  ��: TMCC_RegisterUpgradeCallBack
 *˵  ��: ע�����������Ϣ����ص�����
 *��  ��: hTmCCΪ����������ƾ��
 *����ֵ: �ɹ���������������ƾ��ʧ�ܷ���NULL
 */
TMCC_API void TMCC_CALL TMCC_RegisterUpgradeCallBack( HANDLE hTmCC, TMCC_UPGRADE_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_StartUpgrade
 *˵  ��: ���������������ʼ��
 *��  ��: hTmCCΪ����������ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_StartUpgrade( HANDLE hTmCC );

/*
 *��  ��: TMCC_StopUpgrade
 *˵  ��: ֹͣ�������
 *��  ��: hTmCCΪ����������ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_StopUpgrade( HANDLE hTmCC );

/*
 *��  ��: TMCC_SendUpgradeMessage
 *˵  ��: �������Ϸ�������Ϣ
 *��  ��: hTmCCΪ����������ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SendUpgradeMessage( HANDLE hTmCC );

//////////////////////////////////////////////////////////////
///////////////////�豸�Զ�����������/////////////////////////
//////////////////////////////////////////////////////////////
/*
 *��  ��: TMCC_RegisterEnumServerCallBack 
 *˵  ��: ע��ö�ٷ�������Ϣ�ص�����
 *��  ��: pCallBackΪ�ص�����ָ�룬contextΪ�������Զ������
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterEnumServerCallBack( HANDLE hEnum, TMCC_ENUMSERVER_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_StartEnum
 *˵  ��: ��������
 *��  ��: hEnumΪ��ö�ٿ��ƾ����TMCC_CreateEnumServer��ʼ�����ؾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_StartEnum( HANDLE hEnum );

/*
 *��  ��: TMCC_StopListen
 *˵  ��: �ر�ö�ټ��� 
 *��  ��: hEnumΪ��ö�ٿ��ƾ����TMCC_CreateEnumServer��ʼ�����ؾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_StopEnum( HANDLE hEnum );

/*
 *��  ��: TMCC_EnumServer
 *˵  ��: �о������еķ�����
 *��  ��: hEnumΪ��ö�ٿ��ƾ����TMCC_CreateEnumServer��ʼ�����ؾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_RefreshEnum( HANDLE hEnum );

/*
 *��  ��: TMCC_ConfigServerBuEnum
 *˵  ��: UDP��ʽ���÷�����
 *��  ��: hEnumΪ��ö�ٿ��ƾ����TMCC_CreateEnumServer��ʼ�����ؾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_ConfigServerByMulti( HANDLE hEnum, tmMultiServerCfg_t* pConfig );


////////////////////////////////////////////////////////
///////////////////ʵʱ��ݲ���/////////////////////////
////////////////////////////////////////////////////////
/*
 *��  ��: TMCC_RegisterRealStreamCallBack
 *˵  ��: ע��ʵʱ�������ص�
 *��  ��: hClientΪ�ļ����������,pCallBackΪ�ص�����ָ��,contextΪ�û�ָ��ʽ
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API void TMCC_CALL TMCC_RegisterStreamCallBack( HANDLE hClient, TMCC_STREAMREAD_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_RegisterConnectMessage
 *˵  ��: ע������״̬�����Ϣ
 *��  ��: hClientΪ���������,hWnd�û�������Ϣ����,msgID��ϢID
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterConnectMessage( HANDLE hClient, HWND hWnd, unsigned int msgID );

/*
 *��  ��: TMCC_ConnectStream
 *˵  ��: ��ָ�������򿪷�����ʵʱ��
 *��  ��: hClientΪ���ž��,pPlayInfoΪ���ļ�������
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_ConnectStream( HANDLE hClient, tmPlayRealStreamCfg_t* pPlayInfo, HWND hPlayWnd );

/*
 *��  ��: TMCC_MakeKeyFrame
 *˵  ��: ǿ����һ֡Ϊ�ؼ�֡���������������Ƶ����ôͨ����Ϣ�������е���Ϣ
 *��  ��: hClientΪ���ž��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_MakeKeyFrame( HANDLE hClient );

/*
 *��  ��: TMCC_SetRealStreamBufferTime
 *˵  ��: ���û���ʱ���С
 *��  ��: hClientΪ���ž��,dwTimeΪ����ʱ��(��λ����)
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetStreamBufferTime( HANDLE hClient, unsigned int dwTime );

/*
 *��  ��: TMCC_RefreshRealStreamBuffer
 *˵  ��: ˢ�µ�ǰ��ݻ���
 *��  ��: hClientΪ���ž��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_RefreshStreamBuffer( HANDLE hClient );

/*
 *��  ��: TMCC_SwicthRealStream
 *˵  ��: �л���������ӵ�����
 *��  ��: hClientΪ���ž��,iStreamIdΪ������
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SwicthRealStream( HANDLE hClient, int iStreamId );


////////////////////////////////////////////////////////
/////////////////////���������/////////////////////////
////////////////////////////////////////////////////////
/*
 *��  ��: TMCC_OpenStream
 *˵  ��: ��ָ�������򿪷������ļ�
 *��  ��: hTmFileΪ�ļ����������,pHeadBufΪ���ļ�ͷ����tmStreamHeadInfo_tͷ,hPlayWndΪ��ʾ��Ƶ�Ĵ���
 *		  iPushBufferSizeΪ�����С����ݱ����ʽ������һ��1024*1024
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_OpenStream( HANDLE hStream, unsigned char* pHeadBuf, int iHeadSize, HWND hPlayWnd, int iPushBufferSize );

/*
 *��  ��: TMCC_ResetStream
 *˵  ��: ��ָ��������λ�����
 *��  ��: hStream��������ƾ��,pHeadBufΪ�����ͷ���壬iHeadSizeͷ�����С
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_ResetStream( HANDLE hStream, unsigned char* pHeadBuf, int iHeadSize );

/*
 *��  ��: TMCC_CloseStream
 *˵  ��: �ر����������
 *��  ��: hStreamΪ�ļ����������,pPlayInfoΪ���ļ�������,hPlayWndΪ��ʾ��Ƶ�Ĵ���
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_CloseStream( HANDLE hStream );

/*
 * ��  ��: TMCC_GetFileHead
 * ˵  ��: ��ȡ�ļ���ͷ������ֱ������OpenStream
 * ��  ��: pHeadBufΪ�����ͷ��Ż���,iBufSize���峤��
 * ����ֵ: �ɹ������ļ�ͷ���ȣ�ʧ�ܷ���<=0
 */
TMCC_API int TMCC_CALL TMCC_GetFileHead( const char* lpszFileName, unsigned char* pHeadBuf, int iBufSize );

/*
 *��  ��: TMCC_PutInStream
 *˵  ��: �������������
 *��  ��: hStreamΪ��������ž����,pStreamBufΪ���������,iStreamSizeΪ�������С
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_PutInStream( HANDLE hStream, unsigned char* pStreamBuf, int iStreamSize, BOOL bLost );


////////////////////////////////////////////////////////
///////////////////Զ���ļ�����/////////////////////////
////////////////////////////////////////////////////////
/*
 *��  ��: TMCC_FindFirst
 *˵  ��: ��ʼ������ʽ�����������ļ�
 *��  ��: hTmFileΪ�ļ����������pFindConditionΪ����������lpFindFileDataΪ����ļ���Ϣ
 *����ֵ: �ɹ������ļ��������ʧ�ܷ���NULL
 */
TMCC_API HANDLE TMCC_CALL TMCC_FindFirstFile( HANDLE hTmCC, tmFindConditionCfg_t* pFindCondition, tmFindFileCfg_t* lpFindFileData );

/*
 *��  ��: TMCC_FindNextFile
 *˵  ��: ������һ���ļ�
 *��  ��: hTmFileΪ�ļ����������lpFindFileDataΪ����ļ���Ϣ
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_FindNextFile( HANDLE hTmFile, tmFindFileCfg_t* lpFindFileData );

/*
 *��  ��: TMCC_FindCloseFile
 *˵  ��: �ر�����
 *��  ��: hTmFileΪ�ļ����������
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_FindCloseFile( HANDLE hTmFile );

/*
 *��  ��: TMCC_DownloadFile
 *˵  ��: ���ط������ļ�
 *��  ��: hTmFileΪ�ļ����������, pPlayInfoΪ��������,lpSaveFileNameΪ����ı����ļ�,bCancel������ָֹͣ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_DownloadFile( HANDLE hTmCC, tmPlayConditionCfg_t* pPlayInfo, const char* lpSaveFileName, BOOL* bCancel, TMCC_DOWNLOADPROGRESS_CALLBACK pCallBack, void* context );
TMCC_API int TMCC_CALL TMCC_DownloadFileA( HANDLE hTmCC, tmDownloadFileCfg_t* pDownloadInfo, int iDownloadNum, BOOL* bCancel, TMCC_DOWNLOADPROGRESS_CALLBACK pCallBack, void* context );


////////////////////////////////////////////////////////
//////////////////////�ļ�����//////////////////////////
////////////////////////////////////////////////////////
/*
 *��  ��: TMCC_OpenFile
 *˵  ��: ��ָ�������򿪷������ļ�
 *��  ��: hTmCCΪ�ļ����������,pPlayInfoΪ���ļ�������,hPlayWndΪ��ʾ��Ƶ�Ĵ���;
 *		  ��hTmCC==NULL��Ϊ���ű����ļ�
 *����ֵ: �ɹ����ز��ſ��ƾ��,ʧ�ܷ���NULL
 */
TMCC_API HANDLE TMCC_CALL TMCC_OpenFile( HANDLE hTmCC, tmPlayConditionCfg_t* pPlayInfo, HWND hPlayWnd );

/*
 *��  ��: TMCC_CloseFile
 *˵  ��: �رմ򿪵ķ������ļ�
 *��  ��: hTmFileΪ�ļ����������
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_CloseFile( HANDLE hTmFile );

/*
 *��  ��: TMCC_ReadFile
 *˵  ��: ��ȡ�ļ���ݣ����������ȡ�����ȡ����һ֡
 *��  ��: hTmFileΪ�ļ����������,buf��ݻ��壬iReadSizeΪ��ȡ��С
 *����ֵ: �ɹ����ض�ȡ�Ĵ�С��ʧ�ܷ���С��0
 */
TMCC_API int TMCC_CALL TMCC_ReadFile( HANDLE hTmFile, BYTE* buf, int iReadSize );

/*
 *��  ��: TMCC_ControlFile
 *˵  ��: �����ļ�����
 *��  ��: hTmFileΪ�ļ����������,pPlayControlΪ�ļ����Ʋ�����Ϣ
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_ControlFile( HANDLE hTmFile, tmPlayControlCfg_t* pPlayControl );

/*
 *��  ��: TMCC_GetFilePlayState
 *˵  ��: ��ȡ�򿪵��ļ�λ��
 *��  ��: hTmFileΪ�ļ����������,tmTimeInfo_tΪ����ļ�λ��ָ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_GetFilePlayState( HANDLE hTmFile, tmPlayStateCfg_t* pState );

/*
 *��  ��: TMCC_RegisterFileCallBack 
 *˵  ��: ע���ļ����ʻص�����
 *��  ��: pCallBackΪ�ص�����ָ�룬contextΪ�������Զ������
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterFileCallBack( HANDLE hTmFile, tmFileAccessInterface_t* pCallBack, void* context );

//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////��Ƶ���ƽӿڶ���//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*
 *��  ��: TMCC_RegisterAVFrameCallBack
 *˵  ��: ע�������Ƶ����ص�
 *��  ��: hTmCCΪ���������,pCallBack�û��ص�����ָ��,contextΪ�û��Զ���ָ��
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterAVFrameCallBack( HANDLE hTmCC, TMCC_AVFRAME_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_RegisterDrawCallBack
 *˵  ��: ע�������Ƶ�Ի�����ص�
 *��  ��: hTmCCΪ���������,pCallBack�û��ص�����ָ��,contextΪ�û��Զ���ָ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API void TMCC_CALL TMCC_RegisterDrawCallBack( HANDLE hTmCC, TMCC_DDRAW_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_SetVolume
 *˵  ��: ������Ƶ��������
 *��  ��: hTmCCΪ���ƾ��iVolumeΪ����(-10000~0,-10000��С,0���)
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetVolume( HANDLE hTmCC, int iVolume );

/*
 *��  ��: TMCC_SetMute
 *˵  ��: ���ò����������أ�ֻ�Ǳ��ؽ���������
 *��  ��: hTmCCΪ���ƾ��bMuteΪ����(FALSE��������TRUE����)
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetMute( HANDLE hTmCC, BOOL bMute );

/*
 *��  ��: TMCC_SetDisplayShow
 *˵  ��: ���ý�����Ƶ�Ƿ���ʾ��Ĭ�ϴ�
 *��  ��: hTmCCΪ���ƾ��bShowΪ����(FALSE����ʾ��TRUE��ʾ)
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetDisplayShow( HANDLE hTmCC, BOOL bShow );

/*
 *��  ��: TMCC_SetImageOutFmt
 *˵  ��: ���ý�����Ƶ�����ʽ(Ĭ����YUV420)
 *��  ��: hTmCCΪ���ƾ��iOutFmtΪ�����ʽ
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetImageOutFmt( HANDLE hTmCC, unsigned int iOutFmt );

/*
 *��  ��: TMCC_GetDisplayRegion
 *˵  ��: ��ȡ��ʾ��Ƶ����ʾλ��
 *��  ��: hTmCCΪ���ƾ��iRegionNumΪ��ʾ��,pSrcRectΪ��ʾλ�������ԭʼͼ��,hDestWnd��ʾ����,bEnableΪ�Ƿ���ʾ
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_GetDisplayRegion( HANDLE hTmCC, int iRegionNum, RECT* pSrcRect, HWND* hDestWnd, BOOL* bEnable );

/*
 *��  ��: TMCC_SetDisplayRegion
 *˵  ��: ��ȡ��ʾ��Ƶ����ʾλ��
 *��  ��: hTmCCΪ���ƾ��iRegionNumΪ��ʾ��,pSrcRectΪ��ʾλ�������ԭʼͼ��,hDestWnd��ʾ����,bEnableΪ�Ƿ���ʾ
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_SetDisplayRegion( HANDLE hTmCC, int iRegionNum, RECT* pSrcRect, HWND hDestWnd, BOOL bEnable );

/*
 *��  ��: TMCC_RefreshDisplay
 *˵  ��: ˢ�µ�ǰ��ʾ
 *��  ��: hTmCCΪ���ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_RefreshDisplay( HANDLE hTmCC );

/*
 *��  ��: TMCC_ClearDisplay
 *˵  ��: ��յ�ǰ��ʾ
 *��  ��: hTmCCΪ���ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_ClearDisplay( HANDLE hTmCC );

/*
 *��  ��: TMCC_GetImageSize
 *˵  ��: ��ȡ��Ƶ��С
 *��  ��: hTmCCΪ���ƾ��iWidth/iHeightΪ��Ŵ�С��ָ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_GetImageSize( HANDLE hTmCC, int* iWidth, int* iHeight );

/*
 *��  ��: TMCC_GetDisplayScale
 *˵  ��: ��ȡ��Ƶԭʼ��ʾ����
 *��  ��: hTmCCΪ���ƾ��iScaleΪ�����ʾ�����ָ�룬ע��˱���Ϊ��/��*1000
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_GetDisplayScale( HANDLE hTmCC, int* iScale );

/*
 *��  ��: TMCC_CapturePictureToFile
 *˵  ��: ��ǰ��ʾ��Ƶץͼ��ָ���ļ�
 *��  ��: hTmCCΪ���ƾ��,pFileNameΪ��ŵ��ļ�,pFmtΪ��ʽ
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_CapturePictureToFile( HANDLE hTmCC, const char* pFileName, const char* pFmt );

/*
 *��  ��: TMCC_CapturePictureToBuffer
 *˵  ��: ��ǰ��ʾ��Ƶץͼ��ָ������
 *��  ��: hTmCCΪ���ƾ��,lpBufferΪ���ͼƬ����,iBufferSizeΪ�����С(����Ϊ�����С�����ʵ����ݴ�С),pFmtΪ��ʽ
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_CapturePictureToBuffer( HANDLE hTmCC, const char* pFmt, void* lpBuffer, int* iBufferSize );

/*
 *��  ��: TMCC_OpenAvRender
 *˵  ��: ��ָ������������ƵRender
 *��  ��: pCfgΪ������
 *����ֵ: �ɹ�����RENDER���ƾ��,ʧ�ܷ���NULL
 */
TMCC_API int TMCC_CALL TMCC_OpenAvRender( HANDLE hTmCC, tmAvRenderConfig_t* pCfg, HWND hPlayWnd );

/*
 *��  ��: TMCC_CloseAvRender
 *˵  ��: �رմ򿪵�Render
 *��  ��: hTmFileΪ�ļ����������
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_CloseAvRender( HANDLE hTmCC );

/*
 *��  ��: TMCC_PutinAvFrame
 *˵  ��: ��������Ƶ������ʾ
 *��  ��: hTmCCΪ���ƾ��,pImage����Ƶ֡
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_PutinAvFrame( HANDLE hTmCC, tmAvImageInfo_t* pImage );

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////�豸״̬�ͱ�������/////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*
 *��  ��: TMCC_StartListen
 *˵  ��: ����״̬�ͱ��������Լ�����ͼƬ�ϴ�
 *��  ��: hTmCCΪ���ƾ��,iPortΪ����˿�
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_StartListen( HANDLE hTmCC, int iPort );

/*
 *��  ��: TMCC_StopListen
 *˵  ��: �ر�״̬�ͱ��������Լ�����ͼƬ�ϴ�
 *��  ��: hTmCCΪ���ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_StopListen( HANDLE hTmCC );


//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////�����豸�����ϴ�///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*
 *��  ��: TMCC_RegisterDeviceLoginCallBack
 *˵  ��: ע���豸������¼����ص�
 *��  ��: hTmCCΪ���������,pCallBack�û��ص�����ָ��,contextΪ�û��Զ���ָ��
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterDeviceLoginCallBack( HANDLE hTmCC, TMCC_DEVICELOGIN_CALLBACK pCallBack, void* context );
/*
 *��  ��: TMCC_RegisterDeviceStreamCallBack
 *˵  ��: ע���豸����ϴ�����ص�
 *��  ��: hTmCCΪ���������,pCallBack�û��ص�����ָ��,contextΪ�û��Զ���ָ��
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterDeviceStreamCallBack( HANDLE hTmCC, TMCC_DEVICESTREAM_CALLBACK pCallBack, void* context );
/*
 *��  ��: TMCC_RegisterDeviceTalkCallBack
 *˵  ��: ע���豸���������Խ�����ص�
 *��  ��: hTmCCΪ���������,pCallBack�û��ص�����ָ��,contextΪ�û��Զ���ָ��
 *����ֵ: ��
 */
TMCC_API void TMCC_CALL TMCC_RegisterDeviceTalkCallBack( HANDLE hTmCC, TMCC_DEVICETALK_CALLBACK pCallBack, void* context );

/*
 *��  ��: TMCC_StartListenDevice
 *˵  ��: �����豸�ϴ�����
 *��  ��: hTmCCΪ���ƾ��,iPortΪ����˿�
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_StartListenDevice( HANDLE hTmCC, int iPort );

/*
 *��  ��: TMCC_StopListenDevice
 *˵  ��: �ر��豸�ϴ�����
 *��  ��: hTmCCΪ���ƾ��
 *����ֵ: �ɹ�����TMCC_ERR_SUCCESS��ʧ�ܷ�������ֵ
 */
TMCC_API int TMCC_CALL TMCC_StopListenDevice( HANDLE hTmCC );

#ifdef __cplusplus
}
#endif

#endif //__TMCONTROLCLIENT_H__
