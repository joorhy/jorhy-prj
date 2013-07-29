#include "MyRtspClient.h"

CMyRtspClient::CMyRtspClient(void)
: ourRTSPClient(NULL)
{
}

CMyRtspClient::~CMyRtspClient(void)
{

}


Medium* CMyRtspClient::CreateClient(UsageEnvironment& env, void * ActionRtspClient, char const* url, int verbosityLevel) 
{
	ourRTSPClient = RTSPClient::createNew(env, url, verbosityLevel);
	ourRTSPClient->InitActionRtspClient(ActionRtspClient);
	return ourRTSPClient;
}

void CMyRtspClient::assignClient(Medium* client)
{
	ourRTSPClient = (RTSPClient*)client;
}

void CMyRtspClient::getOptions(RTSPClient::responseHandler* afterFunc) 
{ 
	ourRTSPClient->sendOptionsCommand(afterFunc, ourAuthenticator);
}

void CMyRtspClient::getSDPDescription(RTSPClient::responseHandler* afterFunc)
{
	ourRTSPClient->sendDescribeCommand(afterFunc, ourAuthenticator);
}

void CMyRtspClient::setupSubsession(MediaSubsession* subsession, Boolean streamUsingTCP, RTSPClient::responseHandler* afterFunc)
{
	Boolean forceMulticastOnUnspecified = False;
	ourRTSPClient->sendSetupCommand(*subsession, afterFunc, False, streamUsingTCP, forceMulticastOnUnspecified, ourAuthenticator);
}

void CMyRtspClient::startPlayingSession(MediaSession* session, double start, double end, float scale, RTSPClient::responseHandler* afterFunc) 
{
	ourRTSPClient->sendPlayCommand(*session, afterFunc, start, end, scale, ourAuthenticator);
}

void CMyRtspClient::startPlayingSession(MediaSession* session, char const* absStartTime, char const* absEndTime, float scale, RTSPClient::responseHandler* afterFunc)
{
	ourRTSPClient->sendPlayCommand(*session, afterFunc, absStartTime, absEndTime, scale, ourAuthenticator);
}

void CMyRtspClient::tearDownSession(MediaSession* session, RTSPClient::responseHandler* afterFunc)
{
	ourRTSPClient->sendTeardownCommand(*session, afterFunc, ourAuthenticator);
}
