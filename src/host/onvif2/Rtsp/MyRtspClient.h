#pragma once

#include "Res.h"

class CMyRtspClient
	: public CRes
{
public:
	CMyRtspClient(void);
	virtual ~CMyRtspClient(void);

	Medium* CreateClient(UsageEnvironment& env, 
		void * ActionRtspClient, 
		char const* URL, 
		int verbosityLevel);

	void assignClient(Medium* client);

	void getOptions(RTSPClient::responseHandler* afterFunc);

	void getSDPDescription(RTSPClient::responseHandler* afterFunc);

	void setupSubsession(MediaSubsession* subsession, 
		Boolean streamUsingTCP, 
		RTSPClient::responseHandler* afterFunc);

	void startPlayingSession(MediaSession* session, 
		double start, 
		double end, 
		float scale, 
		RTSPClient::responseHandler* afterFunc);

	void startPlayingSession(MediaSession* session, 
		char const* absStartTime, 
		char const* absEndTime, 
		float scale, 
		RTSPClient::responseHandler* afterFunc);

	void tearDownSession(MediaSession* session, 
		RTSPClient::responseHandler* afterFunc);
	
private:
	RTSPClient* ourRTSPClient;
};
