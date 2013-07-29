#pragma once

#include "MyRtspClient.h"


// Forward function definitions:
void continueAfterClientCreation(CMyRtspClient * ActionRtspClient);
void continueAfterOPTIONS(RTSPClient* client, int resultCode, char* resultString, void * ActionRtspClient);
void continueAfterDESCRIBE(RTSPClient* client, int resultCode, char* resultString, void * ActionRtspClient);
void continueAfterSETUP(RTSPClient* client, int resultCode, char* resultString, void * ActionRtspClient);
void continueAfterPLAY(RTSPClient* client, int resultCode, char* resultString, void * ActionRtspClient);
void continueAfterTEARDOWN(RTSPClient* client, int resultCode, char* resultString, void * ActionRtspClient);

void shutdown(CMyRtspClient * ActionRtspClient, int exitCode = 1);
void setupStreams(CMyRtspClient * ActionRtspClient);
void closeMediaSinks(CMyRtspClient * ActionRtspClient);
void sessionTimerHandler(void* ActionRtspClient);
void subsessionByeHandler(void* ActionRtspClient);
void sessionAfterPlaying(void* ActionRtspClient);
void subsessionAfterPlaying(void* ActionRtspClient);
