/**
*  Copyright (c) 2013, 成都荣耀科技有限公司(http://www.ronyao.com/)
*  All rights reserved.
*
*  @file        OnvifCore.h
*  @author      雷银春(yo7@foxmail.com)
*  @date        2013/07/09 14:51
*  @version     ver 1.0.0.2
*
*  @brief       连接并管理Onvif设备
*  @note        无
*
*   v1.0.0.1    2013/07/09 14:51    第一次完成代码编写
*   v1.0.0.2    2013/07/19 14:38    函数实现移至cpp中，功能测试通过。
*/
#ifndef __OnvifCore_head__
#define __OnvifCore_head__

#include "Includes.h"

/** 设备连接超时时间 */
#define TOKEN_TIMESTAMP 5

/** Media配置文件 */
typedef struct _tagMediaProfile
{
	string Profile;		/**< 配置文件名称 */
	string RtrpUrl;		/**< RTSP地址 */
}MediaProfile;

typedef vector<MediaProfile> MediaProfileVec;
typedef MediaProfileVec::iterator MediaProfileVecItor;

/** PTZ状态 */
typedef enum _tagPTZStatus
{
	NoSupport = 0,	/**< 不支持PTZ */
	Support = 1,	/**< 支持PTZ */
	Used = 2,		/**< 使用过PTZ */
	FreeUsed = 3	/**< 释放了PTZ */
}PTZStatus;

/** Onvif设备用户名 */
#define DEV_USERNAME "admin"

/** Onvif设备密码 */
#define DEV_PASSWORD "12345"

/**
*  @author      雷银春(yo7@foxmail.com)
*  @date        2013/07/09 14:57
*  @class       COnvifCore
*  @brief       用于连接、管理等Onvif设备
*  @note        无
*/
class COnvifCore
{
public:
    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 15:28
    *  @brief       构造函数
    *  @note        申请资源
    *  @see         ~COnvifCore()
    */
	COnvifCore(void);

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 15:29
    *  @brief       析构函数
    *  @note        释放资源
    *  @see         COnvifCore()
    */
	virtual ~COnvifCore(void);

public:
    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 15:32
    *  @brief       初始化Onvif连接信息
    *  @note        无
    *  @param[in]   szTargetIp Onvife设备IP地址
    *  @return      成功返回true，否则为false 
    */
	bool InitCore(const char * szTargetIp);

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 16:03
    *  @brief       获取设备的Media信息
    *  @return      成功返回true，否则为false
    */
	bool GetMediaProfile(void);

	string & GetRtspUrl(string & strRtspUrl)
	{
		if (m_MediaProfileVec.size() < 1)
		{
			strRtspUrl = "";
		}
		else
		{
			strRtspUrl = m_MediaProfileVec[0].RtrpUrl;
		}
		return strRtspUrl;
	}

protected:
	bool Authentication(soap *TargetSoap, 
			const char *szUserName = DEV_USERNAME, 
			const char *szPassWord = DEV_PASSWORD,
			const char *szId = NULL);
    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 15:34
    *  @brief       Onvif设备认证
    *  @param[in]   TargetSoap 连接Onvif设备对象
	*  @param[in]   szUserName Onvif设备用户名
	*  @param[in]   szPassWord Onvif设备密码
	*  @param[in]   szId 设备Id
    *  @return      成功返回true，否则为false 
    */

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 15:51
    *  @brief       设备认证超时时间
    *  @param[in]   TargetSoap 连接Onvif设备对象
	*  @param[in]   lifetime 超时时间
    *  @return      成功返回true，否则为false 
    */
	bool TokenTimestmap(soap *TargetSoap, 
		time_t lifetime = TOKEN_TIMESTAMP);

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 15:55
    *  @brief       获取设备信息（Media和PTZ）
    *  @return      成功返回true，否则为false 
    */
	bool GetDeviceInfo(void);

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 15:56
    *  @brief       释放每次通信的资源
    */
	void FreeSoap(void);

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 15:57
    *  @brief       打印错误信息
	*  @param[in]   ErrorSoap 错误信息对象
    */
	void PrintErr(soap* ErrorSoap);

public:
    /** 连接Onvif设备对象 */
	soap *MySoap;

	/** 访问RTSP的配置文件名称 */
	string strProfileToken;

    /** 是否支持PTZ */
	PTZStatus m_SupportPTZ;

    /** 目标设备的Onvif地址 */
	string strHostName;

    /** Media配置文件列表 */
	MediaProfileVec m_MediaProfileVec;

    /** 设备对象 */
	DeviceBinding proxyDevice;

    /** 设备Media对象 */
	MediaBinding proxyMedia;

    /** 设备PTZ对象 */
	PTZBinding proxyPTZ;

};

#endif // __OnvifCore_head__