#pragma once

#include <stdio.h>

#define WITH_DOM

#include "liveMedia.hh"
#include "Live555ErrorToFile.h"
#include "GroupsockHelper.hh"
#include "H264Frame.h"

#define RTSP_URL "rtsp://admin:12345@192.168.1.17:554/Streaming/Channels/1?transportmode=unicast"
#define USER_NAME "admin"
#define PASS_WORD "12345"
#define VERBOSITY_LEVEL 1

class CRes
{
public:
	CRes(void);
	virtual ~CRes(void);

public:
	string strRtspUrl;
	string strUserName;
	string strPassWd;

public:
	TaskScheduler* scheduler;
	UsageEnvironment* env;
	Medium* ourClient;
	Authenticator* ourAuthenticator;
	MediaSession* session;
	MediaSubsession *subsession;
	TaskToken sessionTimerTask;
	TaskToken arrivalCheckTimerTask;
	TaskToken interPacketGapCheckTimerTask;
	TaskToken qosMeasurementTimerTask;
	char const* singleMedium;
	double duration;
	double durationSlop; // extra seconds to play at the end
	double initialSeekTime;
	char* initialAbsoluteSeekTime;
	float scale;		// 计时减少单位
	double endTime;
	unsigned totNumPacketsReceived; // used if checking inter-packet gaps
	int simpleRTPoffsetArg;
	unsigned short desiredPortNum;
	unsigned fileSinkBufferSize;
	unsigned socketInputBufferSize;
	Boolean madeProgress;
	Boolean areAlreadyShuttingDown;
	Boolean createReceivers;
	Boolean playContinuously;
	Boolean sendOptionsRequest;
	Boolean sendOptionsRequestOnly;

	Boolean streamUsingTCP;
	int shutdownExitCode;
	struct timeval startTime;

	CH264Frame* m_H264Frame;
	MediaSubsessionIterator* setupIter;

private:
};
