#include "playCommon.h"

#define JUDGE_NULL_POINTER_NO_RET(pPointer) \
	if (NULL == pPointer) {\
	return;\
	}\

#ifdef DEBUG_LOG
#define ErrorLog(LogTip) (printf("%s\n", LogTip))
#else
#define ErrorLog(LogTip) 
#endif

void continueAfterClientCreation(CMyRtspClient * ActionRtspClient) 
{
	ErrorLog("continueAfterClientCreation");
	JUDGE_NULL_POINTER_NO_RET(ActionRtspClient);

	if (ActionRtspClient->sendOptionsRequest)
	{
		ActionRtspClient->getOptions(continueAfterOPTIONS);
	}
	else 
	{
		continueAfterOPTIONS(NULL, 0, NULL, ActionRtspClient);
	}
}

void continueAfterOPTIONS( RTSPClient* client, int resultCode, char* resultString, void * ActionRtspClient )
{
	ErrorLog("continueAfterOPTIONS");
	JUDGE_NULL_POINTER_NO_RET(ActionRtspClient);
	
	CMyRtspClient * pActionRtspClient = (CMyRtspClient *)ActionRtspClient;
	UsageEnvironment* pEnv = pActionRtspClient->env;

	if (pActionRtspClient->sendOptionsRequestOnly) 
	{
		if (resultCode != 0) 
		{
			*pEnv << "RTSP \"OPTIONS\" request failed: " << resultString << "\n";
		} 
		else 
		{
			*pEnv << "RTSP \"OPTIONS\" request returned: " << resultString << "\n";
		}
		shutdown(pActionRtspClient);
	}
	delete[] resultString;

	// Next, get a SDP description for the stream:
	pActionRtspClient->getSDPDescription(continueAfterDESCRIBE);
}

void continueAfterDESCRIBE( RTSPClient* client, int resultCode, char* resultString, void * ActionRtspClient )
{
	ErrorLog("continueAfterDESCRIBE");
	JUDGE_NULL_POINTER_NO_RET(ActionRtspClient);
	
	CMyRtspClient * pActionRtspClient = (CMyRtspClient *)ActionRtspClient;
	UsageEnvironment* pEnv = pActionRtspClient->env;

	if (resultCode != 0) 
	{
		*pEnv << "Failed to get a SDP description for the URL \"" << pActionRtspClient->strRtspUrl.c_str() 
			<< "\": " << resultString << "\n";
		delete[] resultString;
		shutdown(pActionRtspClient);
	}

	char* sdpDescription = resultString;
	*pEnv << "Opened URL \"" << pActionRtspClient->strRtspUrl.c_str() 
		<< "\", returning a SDP description:\n" << sdpDescription << "\n";

	// Create a media session object from this SDP description:
	pActionRtspClient->session = MediaSession::createNew(*pEnv, sdpDescription);
	delete[] sdpDescription;
	if (pActionRtspClient->session == NULL) 
	{
		*pEnv << "Failed to create a MediaSession object from the SDP description: " 
			<< pEnv->getResultMsg() << "\n";
		shutdown(pActionRtspClient);
	} 
	else if (!pActionRtspClient->session->hasSubsessions()) 
	{
		*pEnv << "This session has no media subsessions (i.e., no \"m=\" lines)\n";
		shutdown(pActionRtspClient);
	}

	// Then, setup the "RTPSource"s for the session:
	MediaSubsessionIterator iter(*pActionRtspClient->session);
	MediaSubsession *subsession;
	Boolean madeProgress = False;

	char const* singleMediumToTest = pActionRtspClient->singleMedium;
	while ((subsession = iter.next()) != NULL) 
	{
		// If we've asked to receive only a single medium, then check this now:
		if (singleMediumToTest != NULL) 
		{
			if (strcmp(subsession->mediumName(), singleMediumToTest) != 0) 
			{
				*pEnv << "Ignoring \"" << subsession->mediumName()
					<< "/" << subsession->codecName() << "\" subsession, because we've asked to receive a single " 
					<< pActionRtspClient->singleMedium << " session only\n";
				continue;
			} 
			else 
			{
				// Receive this subsession only
				singleMediumToTest = "xxxxx";
				// this hack ensures that we get only 1 subsession of this type
			}
		}

		if (pActionRtspClient->desiredPortNum != 0) 
		{
			subsession->setClientPortNum(pActionRtspClient->desiredPortNum);
			pActionRtspClient->desiredPortNum += 2;
		}

		if (pActionRtspClient->createReceivers) 
		{
			if (!subsession->initiate(pActionRtspClient->simpleRTPoffsetArg)) 
			{
				*pEnv << "Unable to create receiver for \"" << subsession->mediumName()
					<< "/" << subsession->codecName()
					<< "\" subsession: " << pEnv->getResultMsg() << "\n";
			} 
			else 
			{
				*pEnv << "Created receiver for \"" << subsession->mediumName()
					<< "/" << subsession->codecName()
					<< "\" subsession (client ports " << subsession->clientPortNum()
					<< "-" << subsession->clientPortNum()+1 << ")\n";
				madeProgress = True;

				if (subsession->rtpSource() != NULL) 
				{
					// Because we're saving the incoming data, rather than playing
					// it in real time, allow an especially large time threshold
					// (1 second) for reordering misordered incoming packets:
					unsigned const thresh = 1000000; // 1 second
					subsession->rtpSource()->setPacketReorderingThresholdTime(thresh);

					// Set the RTP source's OS socket buffer size as appropriate - either if we were explicitly asked (using -B),
					// or if the desired FileSink buffer size happens to be larger than the current OS socket buffer size.
					// (The latter case is a heuristic, on the assumption that if the user asked for a large FileSink buffer size,
					// then the input data rate may be large enough to justify increasing the OS socket buffer size also.)
					int socketNum = subsession->rtpSource()->RTPgs()->socketNum();
					unsigned curBufferSize = getReceiveBufferSize(*pEnv, socketNum);
					if (pActionRtspClient->socketInputBufferSize > 0 || pActionRtspClient->fileSinkBufferSize > curBufferSize) 
					{
						unsigned newBufferSize = 
							pActionRtspClient->socketInputBufferSize > 0 ? pActionRtspClient->socketInputBufferSize : pActionRtspClient->fileSinkBufferSize;
						newBufferSize = setReceiveBufferTo(*pEnv, socketNum, newBufferSize);
						if (pActionRtspClient->socketInputBufferSize > 0) 
						{
							// The user explicitly asked for the new socket buffer size; announce it:
							*pEnv << "Changed socket receive buffer size for the \""
								<< subsession->mediumName()
								<< "/" << subsession->codecName()
								<< "\" subsession from "
								<< curBufferSize << " to "
								<< newBufferSize << " bytes\n";
						}
					}
				}
			}
		} 
		else 
		{
			if (subsession->clientPortNum() == 0) 
			{
				*pEnv << "No client port was specified for the \""
					<< subsession->mediumName()
					<< "/" << subsession->codecName()
					<< "\" subsession.  (Try adding the \"-p <portNum>\" option.)\n";
			}
			else 
			{
				madeProgress = True;
			}
		}
	}
	if (!madeProgress)
		shutdown(pActionRtspClient);

	// Perform additional 'setup' on each subsession, before playing them:
	setupStreams(pActionRtspClient);
}

void continueAfterSETUP( RTSPClient* client, int resultCode, char* resultString, void * ActionRtspClient )
{
	ErrorLog("continueAfterSETUP");
	JUDGE_NULL_POINTER_NO_RET(ActionRtspClient);
	
	CMyRtspClient * pActionRtspClient = (CMyRtspClient *)ActionRtspClient;
	UsageEnvironment* pEnv = pActionRtspClient->env;

	if (resultCode == 0) 
	{
		*pEnv << "Setup \"" << pActionRtspClient->subsession->mediumName()
			<< "/" << pActionRtspClient->subsession->codecName()
			<< "\" subsession (client ports " << pActionRtspClient->subsession->clientPortNum()
			<< "-" << pActionRtspClient->subsession->clientPortNum()+1 << ")\n";
		pActionRtspClient->madeProgress = True;
	} 
	else 
	{
		*pEnv << "Failed to setup \"" << pActionRtspClient->subsession->mediumName()
			<< "/" << pActionRtspClient->subsession->codecName()
			<< "\" subsession: " << resultString << "\n";
	}
	delete[] resultString;

	// Set up the next subsession, if any:
	setupStreams(pActionRtspClient);
}

void continueAfterPLAY( RTSPClient* client, int resultCode, char* resultString, void * ActionRtspClient )
{
	ErrorLog("continueAfterPLAY");
	JUDGE_NULL_POINTER_NO_RET(ActionRtspClient);
	
	CMyRtspClient * pActionRtspClient = (CMyRtspClient *)ActionRtspClient;
	UsageEnvironment* pEnv = pActionRtspClient->env;

	if (resultCode != 0) 
	{
		*pEnv << "Failed to start playing session: " << resultString << "\n";
		delete[] resultString;
		shutdown(pActionRtspClient);
	} 
	else 
	{
		*pEnv << "Started playing session\n";
	}
	delete[] resultString;

	// Figure out how long to delay (if at all) before shutting down, or
	// repeating the playing
	Boolean timerIsBeingUsed = False;
	double secondsToDelay = pActionRtspClient->duration;
	if (pActionRtspClient->duration > 0)
	{
		// First, adjust "duration" based on any change to the play range (that was specified in the "PLAY" response):
		double rangeAdjustment = (pActionRtspClient->session->playEndTime() - pActionRtspClient->session->playStartTime()) 
			- (pActionRtspClient->endTime - pActionRtspClient->initialSeekTime);
		if (pActionRtspClient->duration + rangeAdjustment > 0.0) 
			pActionRtspClient->duration += rangeAdjustment;

		timerIsBeingUsed = True;
		double absScale = pActionRtspClient->scale > 0 ? pActionRtspClient->scale : -pActionRtspClient->scale; // ASSERT: scale != 0
		secondsToDelay = pActionRtspClient->duration/absScale + pActionRtspClient->durationSlop;

		int64_t uSecsToDelay = (int64_t)(secondsToDelay*1000000.0);
		pActionRtspClient->sessionTimerTask = pEnv->taskScheduler().scheduleDelayedTask(uSecsToDelay, 
			(TaskFunc*)sessionTimerHandler, (void*)pActionRtspClient);
	}

	char const* actionString = pActionRtspClient->createReceivers ? "Receiving streamed data":"Data is being streamed";
	if (timerIsBeingUsed) 
	{
		*pEnv << actionString
			<< " (for up to " << secondsToDelay
			<< " seconds)...\n";
	} 
	else 
	{
		*pEnv << actionString << "...\n";
	}
}

void continueAfterTEARDOWN( RTSPClient* client, int resultCode, char* resultString, void * ActionRtspClient )
{
	ErrorLog("continueAfterTEARDOWN");
	JUDGE_NULL_POINTER_NO_RET(ActionRtspClient);

	CMyRtspClient * pActionRtspClient = (CMyRtspClient *)ActionRtspClient;
	delete[] resultString;

	// Now that we've stopped any more incoming data from arriving, close our output files:
	closeMediaSinks(pActionRtspClient);
	Medium::close(pActionRtspClient->session);

	// Finally, shut down our client:
	delete pActionRtspClient->ourAuthenticator;
	Medium::close(pActionRtspClient->ourClient);

	// Adios...
	exit(pActionRtspClient->shutdownExitCode);
}

void subsessionAfterPlaying(void* ActionRtspClient) 
{
	ErrorLog("subsessionAfterPlaying");
	JUDGE_NULL_POINTER_NO_RET(ActionRtspClient);

	CMyRtspClient * pActionRtspClient = (CMyRtspClient *)ActionRtspClient;

	// Begin by closing this media subsession's stream:
	MediaSubsession* subsession = pActionRtspClient->subsession;
	Medium::close(subsession->sink);
	subsession->sink = NULL;

	// Next, check whether *all* subsessions' streams have now been closed:
	MediaSession& session = subsession->parentSession();
	MediaSubsessionIterator iter(session);
	while ((subsession = iter.next()) != NULL) 
	{
		if (subsession->sink != NULL) 
			return; // this subsession is still active
	}

	// All subsessions' streams have now been closed
	sessionAfterPlaying(ActionRtspClient);
}

void subsessionByeHandler(void* ActionRtspClient)
{
	ErrorLog("subsessionByeHandler");
	JUDGE_NULL_POINTER_NO_RET(ActionRtspClient);
	
	CMyRtspClient * pActionRtspClient =(CMyRtspClient *)ActionRtspClient;
	UsageEnvironment* pEnv = pActionRtspClient->env;

	timeval timeNow;
	gettimeofday(&timeNow, NULL);
	unsigned secsDiff = timeNow.tv_sec - pActionRtspClient->startTime.tv_sec;

	MediaSubsession* subsession = (MediaSubsession*)pActionRtspClient->subsession;
	*pEnv << "Received RTCP \"BYE\" on \"" << subsession->mediumName()
		<< "/" << subsession->codecName()
		<< "\" subsession (after " << secsDiff
		<< " seconds)\n";

	// Act now as if the subsession had closed:
	subsessionAfterPlaying(ActionRtspClient);
}

void sessionAfterPlaying(void* ActionRtspClient) 
{
	ErrorLog("sessionAfterPlaying");
	JUDGE_NULL_POINTER_NO_RET(ActionRtspClient);

	CMyRtspClient * pActionRstpClient = (CMyRtspClient *)ActionRtspClient;
	UsageEnvironment* pEnv = pActionRstpClient->env;

	if (!pActionRstpClient->playContinuously)
	{
		shutdown(pActionRstpClient, 0);
	} 
	else 
	{
		// We've been asked to play the stream(s) over again.
		// First, reset state from the current session:
		if (pEnv != NULL)
		{
			pEnv->taskScheduler().unscheduleDelayedTask(pActionRstpClient->sessionTimerTask);
			pEnv->taskScheduler().unscheduleDelayedTask(pActionRstpClient->arrivalCheckTimerTask);
			pEnv->taskScheduler().unscheduleDelayedTask(pActionRstpClient->interPacketGapCheckTimerTask);
			pEnv->taskScheduler().unscheduleDelayedTask(pActionRstpClient->qosMeasurementTimerTask);
		}
		pActionRstpClient->totNumPacketsReceived = ~0;

		pActionRstpClient->startPlayingSession(pActionRstpClient->session, 
			pActionRstpClient->initialSeekTime, pActionRstpClient->endTime, pActionRstpClient->scale, continueAfterPLAY);
	}
}

void sessionTimerHandler(void* ActionRtspClient) 
{
	ErrorLog("sessionTimerHandler");
	JUDGE_NULL_POINTER_NO_RET(ActionRtspClient);

	CMyRtspClient * pActionRtspClient = (CMyRtspClient *)ActionRtspClient;
	pActionRtspClient->sessionTimerTask = NULL;

	sessionAfterPlaying(pActionRtspClient);
}



void closeMediaSinks(CMyRtspClient * ActionRtspClient) 
{
	ErrorLog("closeMediaSinks");
	JUDGE_NULL_POINTER_NO_RET(ActionRtspClient);

	if (ActionRtspClient->session == NULL) 
		return;
	MediaSubsessionIterator iter(*ActionRtspClient->session);
	MediaSubsession* subsession;
	while ((subsession = iter.next()) != NULL)
	{
		Medium::close(subsession->sink);
		subsession->sink = NULL;
	}
}


void shutdown(CMyRtspClient * pActionRtspClient, int exitCode) 
{
	ErrorLog("shutdown");
	JUDGE_NULL_POINTER_NO_RET(pActionRtspClient);

	// in case we're called after receiving a RTCP "BYE" while in the middle of a "TEARDOWN".
	if (pActionRtspClient->areAlreadyShuttingDown) 
		return;
	pActionRtspClient->areAlreadyShuttingDown = True;

	UsageEnvironment* pEnv = pActionRtspClient->env;

	pActionRtspClient->shutdownExitCode = exitCode;
	if (pEnv != NULL) 
	{
		pEnv->taskScheduler().unscheduleDelayedTask(pActionRtspClient->sessionTimerTask);
		pEnv->taskScheduler().unscheduleDelayedTask(pActionRtspClient->arrivalCheckTimerTask);
		pEnv->taskScheduler().unscheduleDelayedTask(pActionRtspClient->interPacketGapCheckTimerTask);
		pEnv->taskScheduler().unscheduleDelayedTask(pActionRtspClient->qosMeasurementTimerTask);
	}

	// Teardown, then shutdown, any outstanding RTP/RTCP subsessions
	if (pActionRtspClient->session != NULL) 
	{
		pActionRtspClient->tearDownSession(pActionRtspClient->session, continueAfterTEARDOWN);
	}
	else 
	{
		continueAfterTEARDOWN(NULL, 0, NULL, pActionRtspClient);
	}
}


void setupStreams(CMyRtspClient * ActionRtspClient) 
{
	ErrorLog("setupStreams");
	JUDGE_NULL_POINTER_NO_RET(ActionRtspClient);
	UsageEnvironment* pEnv = ActionRtspClient->env;

	if (ActionRtspClient->setupIter == NULL) 
		ActionRtspClient->setupIter = new MediaSubsessionIterator(*ActionRtspClient->session);

	while ((ActionRtspClient->subsession = ActionRtspClient->setupIter->next()) != NULL) 
	{
		// We have another subsession left to set up:
		if (ActionRtspClient->subsession->clientPortNum() == 0) 
			continue; // port # was not set

		ActionRtspClient->setupSubsession(ActionRtspClient->subsession, ActionRtspClient->streamUsingTCP, continueAfterSETUP);
		return;
	}

	// We're done setting up subsessions.
	if (NULL != ActionRtspClient->setupIter)
	{
		delete ActionRtspClient->setupIter;
		ActionRtspClient->setupIter = NULL;
	}	
	
	if (!ActionRtspClient->madeProgress) 
		shutdown(ActionRtspClient);

	// Create output files:
	if (ActionRtspClient->createReceivers) 
	{
		// Create and start "FileSink"s for each subsession:
		ActionRtspClient->madeProgress = False;
		MediaSubsessionIterator iter(*ActionRtspClient->session);
		while ((ActionRtspClient->subsession = iter.next()) != NULL) 
		{
			if (ActionRtspClient->subsession->readSource() == NULL) 
				continue; // was not initiated

			// For H.264 video stream, we use a special sink that adds 'start codes', and (at the start) the SPS and PPS NAL units:


			ActionRtspClient->subsession->sink = ActionRtspClient->m_H264Frame;
			if (ActionRtspClient->subsession->sink == NULL) 
			{
				*pEnv << "Failed to create FileSink for \"" 
					<< "\": " << ActionRtspClient->env->getResultMsg() << "\n";
			} 
			else 
			{
				ActionRtspClient->subsession->sink->startPlaying(*(ActionRtspClient->subsession->readSource()),
					subsessionAfterPlaying,
					ActionRtspClient->subsession);

				// Also set a handler to be called if a RTCP "BYE" arrives
				// for this subsession:
				if (ActionRtspClient->subsession->rtcpInstance() != NULL) 
				{
					ActionRtspClient->subsession->rtcpInstance()->setByeHandler(subsessionByeHandler, ActionRtspClient);
				}

				ActionRtspClient->madeProgress = True;
			}
		}
		if (!ActionRtspClient->madeProgress) 
			shutdown(ActionRtspClient);
	}

	// Finally, start playing each subsession, to start the data flow:
	if (ActionRtspClient->duration == 0) 
	{
		if (ActionRtspClient->scale > 0) 
			ActionRtspClient->duration = ActionRtspClient->session->playEndTime() - ActionRtspClient->initialSeekTime; // use SDP end time
		else if (ActionRtspClient->scale < 0) 
			ActionRtspClient->duration = ActionRtspClient->initialSeekTime;
	}
	if (ActionRtspClient->duration < 0) 
		ActionRtspClient->duration = 0.0;

	ActionRtspClient->endTime = ActionRtspClient->initialSeekTime;
	if (ActionRtspClient->scale > 0) 
	{
		if (ActionRtspClient->duration <= 0) 
			ActionRtspClient->endTime = -1.0f;
		else 
			ActionRtspClient->endTime = ActionRtspClient->initialSeekTime + ActionRtspClient->duration;
	} 
	else 
	{
		ActionRtspClient->endTime = ActionRtspClient->initialSeekTime - ActionRtspClient->duration;
		if (ActionRtspClient->endTime < 0) 
			ActionRtspClient->endTime = 0.0f;
	}

	char const* absStartTime = ActionRtspClient->initialAbsoluteSeekTime != 
		NULL ? ActionRtspClient->initialAbsoluteSeekTime : ActionRtspClient->session->absStartTime();
	if (absStartTime != NULL) 
	{
		// Either we or the server have specified that seeking should be done by 'absolute' time:
		ActionRtspClient->startPlayingSession(ActionRtspClient->session, absStartTime, ActionRtspClient->session->absEndTime(), 
			ActionRtspClient->scale, continueAfterPLAY);
	} 
	else 
	{
		// Normal case: Seek by relative time (NPT):
		ActionRtspClient->startPlayingSession(ActionRtspClient->session, ActionRtspClient->initialSeekTime, 
			ActionRtspClient->endTime, ActionRtspClient->scale, continueAfterPLAY);
	}
}
