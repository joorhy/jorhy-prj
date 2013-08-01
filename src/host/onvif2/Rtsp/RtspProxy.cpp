#include "RtspProxy.h"

extern void sessionAfterPlaying(void* ActionRtspClient) ;

CRtspProxy::CRtspProxy(void)
: bStop(0)
{
}

CRtspProxy::~CRtspProxy(void)
{
}

bool CRtspProxy::Init( pRtspFrameCallBack pCallBack, void * pCallBackData, double dTime /*= 0.0f*/ )
{
	// Begin by setting up our usage environment:
	g_MyRtsp.scheduler = BasicTaskScheduler::createNew();
	g_MyRtsp.env = CLive555ErrorToFile::CreateNew(*g_MyRtsp.scheduler, "Live555_Error.log");

	g_MyRtsp.m_H264Frame = CH264Frame::CreateNew(*g_MyRtsp.env, g_MyRtsp.fileSinkBufferSize);
	g_MyRtsp.m_H264Frame->m_pFunCallBack = pCallBack;
	g_MyRtsp.m_H264Frame->pFunCallBackData = pCallBackData;

	gettimeofday(&g_MyRtsp.startTime, NULL);

	g_MyRtsp.ourAuthenticator = new Authenticator(g_MyRtsp.strUserName.c_str(), g_MyRtsp.strPassWd.c_str());
	g_MyRtsp.duration = dTime;		//时间
	g_MyRtsp.durationSlop = 0.0f;

	g_MyRtsp.ourClient = g_MyRtsp.CreateClient(*g_MyRtsp.env, &g_MyRtsp, g_MyRtsp.strRtspUrl.c_str(), VERBOSITY_LEVEL);
	if (g_MyRtsp.ourClient == NULL)
	{
		*g_MyRtsp.env << "Failed to create RTSP client: " << g_MyRtsp.env->getResultMsg() << "\n";
		shutdown(&g_MyRtsp);
		return false;
	}
	return true;
}

void CRtspProxy::Begin(void)
{
	bStop = 0;
	continueAfterClientCreation(&g_MyRtsp);

	// All subsequent activity takes place within the event loop, and does not return
	g_MyRtsp.env->taskScheduler().doEventLoop(&bStop);
}

void CRtspProxy::Stop(void)
{
	bStop = 1;
	
	// 等待结束（应当加上同步）
	#ifdef WIN32
	Sleep(1000);
	#else
	sleep(1);
	#endif
	sessionAfterPlaying((void *)&g_MyRtsp);

}
