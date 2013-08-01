/**
*  Copyright (c) 2013, 成都荣耀科技有限公司(http://www.ronyao.com/)
*  All rights reserved.
*
*  @file        Res.cpp
*  @author      雷银春(yo7@foxmail.com)
*  @date        2013/07/26 14:18
*  @version     ver 1.0.0.1
*
*  @brief       资源实现文件
*  @note        无
*
*    v1.0.0.1    2013/07/26 14:18    第一次完成基础代码
*    v1.0.0.2    2013/07/26 14:23    修订泄露Bug
*/

#include "Res.h"




/**
*  @author      雷银春(yo7@foxmail.com)
*  @date        2013/07/26 14:19
*  @class       CRes
*  @brief       资源类
*  @note        无
*/
CRes::CRes(void)
: strRtspUrl(RTSP_URL)
, strUserName(USER_NAME)
, strPassWd(PASS_WORD)
, scheduler(NULL)
, env(NULL)
, ourClient(NULL)
, ourAuthenticator(NULL)
, session(NULL)
, sessionTimerTask(NULL)
, arrivalCheckTimerTask(NULL)
, interPacketGapCheckTimerTask(NULL)
, qosMeasurementTimerTask(NULL)
, singleMedium(NULL)
, subsession(NULL)
, madeProgress(False)
, areAlreadyShuttingDown(False)
, sendOptionsRequest(True)
, sendOptionsRequestOnly(False)
, playContinuously(False)
, streamUsingTCP(True)
, duration(0)
, durationSlop(-1.0)
, initialSeekTime(0.0f)
, initialAbsoluteSeekTime(NULL)
, scale(1.0f)
, endTime(0.0f)
, totNumPacketsReceived(~0)
, simpleRTPoffsetArg(-1)
, desiredPortNum(0)
, fileSinkBufferSize(500000)
, socketInputBufferSize(0)
, m_H264Frame(NULL)
, setupIter(NULL)
,createReceivers(true)
{
}



CRes::~CRes(void)
{
// 	if (NULL != m_H264Frame)
// 	{
// 		Medium::close(m_H264Frame);
// 		m_H264Frame = NULL;
// 	}
// 	if (NULL != ourClient)
// 	{
// 		Medium::close(ourClient);
// 		ourClient = NULL;
// 	}

	if (NULL != ourAuthenticator)
	{
		delete ourAuthenticator;
		ourAuthenticator = NULL;
	}

	if (NULL != env)
	{
		env->reclaim();
		env = NULL;
	}

	if (NULL != scheduler)
	{
		delete scheduler;
		scheduler = NULL;
	}

}