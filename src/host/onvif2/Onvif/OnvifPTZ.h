/**
*  Copyright (c) 2013, 成都荣耀科技有限公司(http://www.ronyao.com/)
*  All rights reserved.
*
*  @file        OnvifPTZ.h
*  @author      雷银春(yo7@foxmail.com)
*  @date        2013/07/09 17:24
*  @version     ver 1.0.0.2
*
*  @brief       Onvif云台控制
*  @note        无
*
*    v1.0.0.1    2013/07/09 17:24    第一次完成代码。
*    v1.0.0.2    2013/07/19 14:36    函数实现移至cpp中；
                                     修订Ptz停止失效的bug（未申请资源）；
                                     功能测试通过。
*    v1.0.0.3    2013/07/27 13:23    修订Ptz放大缩小Bug（未申请资源）；
*/

#ifndef __OnvifPTZ_head__
#define __OnvifPTZ_head__

#include "OnvifCore.h"


/** 镜头水平移动速度 */
#define ONVIF_SPEEND 1.0f

/** 镜头上下移动距离 */
#define ONVIF_UPDOWN 1.0f

/** 放大缩小单位距离 */
#define ONVIF_ZOOM 1.0f

/** 非作用置零 */
#define ONVIF_ZERO 0.0f

/** 每次PTZ作用时间 */
#define PTZ_TIME 1


/**
*  @author      雷银春(yo7@foxmail.com)
*  @date        2013/07/09 18:07
*  @class       COnvifPTZ
*  @brief       Onvif设备云台控制
*  @note        无
*/
class COnvifPTZ : 
	public COnvifCore
{
public:
    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 18:07
    *  @brief       构造函数
    *  @return      无
    *  @see         ~COnvifPTZ()
    */
	COnvifPTZ(void);

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 18:09
    *  @brief       析构函数
    *  @note        释放资源
    *  @return      无
    *  @see         COnvifPTZ()
    */
	~COnvifPTZ(void);

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 18:09
    *  @brief       初始化PTZ环境
    *  @return      无
    *  @warning     在onvif云台控制之前必须调用此函数初始化环境
    */
	void InitPTZ(void);

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 16:16
    *  @brief       左移
    *  @param[in]   LeftUnitRange 左移单元距离
    *  @return      成功返回true，否则为false
    */
	bool PTZLeft(float LeftUnitRange = ONVIF_SPEEND);

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 16:16
    *  @brief       右移
    *  @param[in]   RightUnitRange 右移单元距离
    *  @return      成功返回true，否则为false
    */
	bool PTZRight(float RightUnitRange = ONVIF_SPEEND);

	/**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 16:16
    *  @brief       上移
    *  @param[in]   UpUnitRange 上移单元距离
    *  @return      成功返回true，否则为false
    */
	bool PTZUp(float UpUnitRange = ONVIF_UPDOWN);

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 16:16
    *  @brief       下移
    *  @param[in]   DownUnitRange 下移单元距离
    *  @return      成功返回true，否则为false
    */
	bool PTZDown(float DownUnitRange = ONVIF_UPDOWN);

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 16:16
    *  @brief       放大
    *  @param[in]   InUnitRange 放大单元距离
    *  @return      成功返回true，否则为false
    */
	bool PTZZoomIn(float InUnitRange = ONVIF_ZOOM);

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 16:16
    *  @brief       缩小
    *  @param[in]   OutUnitRange 缩小单元距离
    *  @return      成功返回true，否则为false
    */
	bool PTZZoomOut(float OutUnitRange = ONVIF_ZOOM);

    /**
    *  @author      雷银春(yo7@foxmail.com)
    *  @date        2013/07/09 16:16
    *  @brief       停止
    *  @param[in]   
    *  @return      成功返回true，否则为false
    */
	bool PTZStop(void);

private:
	/** 连续移动请求对象 */
	_tptz__ContinuousMove *tptz__ContinuousMove;

	/** 连续移动响应对象*/
	_tptz__ContinuousMoveResponse *tptz__ContinuousMoveResponse;

	/** 停止移动请求对象 */
	_tptz__Stop *tptz__Stop;

	/** 停止移动响应对象 */
	_tptz__StopResponse *tptz__StopResponse;
};

#endif // __OnvifPTZ_head__