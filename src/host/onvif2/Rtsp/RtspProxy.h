#ifndef _RtspProxy_head__
#define _RtspProxy_head__

#pragma once

#include "MyRtspClient.h"
#include "playCommon.h"

class CRtspProxy
{
public:
	CRtspProxy(void);
	virtual ~CRtspProxy(void);

	bool Init(pRtspFrameCallBack pCallBack, void * pCallBackData, double dTime = 0.0f);

	void Begin(void);

	void Stop(void);

private:
	CMyRtspClient g_MyRtsp;
	char bStop;
};

#endif // _RtspProxy_head__