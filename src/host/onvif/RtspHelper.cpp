#include "RtspHelper.h"
#include "x_errtype.h"

#include <string.h>
#include <stdlib.h>

const char *RTSP_DESCRIBE = 
	"DESCRIBE rtsp://%s:%d/Streaming/Channels/%d?transportmode=unicast RTSP/1.0\r\n"
	"CSeq: %d\r\n"
	"Accept: application/sdp\r\n"
	"User-Agent: ONVIF Filter (LIVE555 Streaming Media v2009.11.27)\r\n\r\n";

const char *RTSP_SETUP = 
	"SETUP rtsp://%s:%d/Streaming/Channels/%d/trackID=%d?transportmode=unicast RTSP/1.0\r\n"
	"CSeq: %d\r\n"
	"Transport: RTP/AVP/TCP;unicast;interleaved=0-1\r\n"
	"User-Agent: ONVIF Filter (LIVE555 Streaming Media v2009.11.27)\r\n\r\n";
	
const char *RTSP_PLAY = 
	"PLAY rtsp://%s:%d/Streaming/Channels/%d/?transportmode=unicast RTSP/1.0\r\n"
	"CSeq: %d\r\n"
	"Session: %u\r\n"
	"Range: npt=0.000-\r\n"
	"User-Agent: ONVIF Filter (LIVE555 Streaming Media v2009.11.27)\r\n\r\n";
	
const char *RTSP_TEARDOWN = 
	"TEARDOWN rtsp://%s:%d/Streaming/Channels/%d/?transportmode=unicast RTSP/1.0\r\n"
	"CSeq: %d\r\n"
	"Session: %u\r\n"
	"User-Agent: ONVIF Filter (LIVE555 Streaming Media v2009.11.27)\r\n\r\n";

CRtspHelper::CRtspHelper()
{
	m_nSeq = 0;
}

CRtspHelper::~CRtspHelper()
{
	
}
		
int CRtspHelper::OpenStream(J_OS::CTCPSocket *m_recvSocket, const char *pAddr, int nPort, int nChannel)
{
	char temp_buff[2048] = {0};
	//发送DESCRIBE
	sprintf(temp_buff, RTSP_DESCRIBE, pAddr, nPort, nChannel, m_nSeq++);
	m_recvSocket->Write_n(temp_buff, strlen(temp_buff));
	memset(temp_buff, 0, sizeof(temp_buff));
	m_recvSocket->Read(temp_buff, sizeof(temp_buff));
	if (IsSeccess(temp_buff))
	{
		ParserSDP(temp_buff);
		//发送SETUP
		memset(temp_buff, 0, sizeof(temp_buff));
		sprintf(temp_buff, RTSP_SETUP, pAddr, nPort, nChannel, m_nVideoTrackId, m_nSeq++);
		m_recvSocket->Write_n(temp_buff, strlen(temp_buff));
		memset(temp_buff, 0, sizeof(temp_buff));
		m_recvSocket->Read(temp_buff, sizeof(temp_buff));
		if (IsSeccess(temp_buff))
		{
			//发送PLAY
			memset(temp_buff, 0, sizeof(temp_buff));
			sprintf(temp_buff, RTSP_PLAY, pAddr, nPort, nChannel, m_nSeq++, this);
			m_recvSocket->Write_n(temp_buff, strlen(temp_buff));
			memset(temp_buff, 0, sizeof(temp_buff));
			m_recvSocket->Read(temp_buff, sizeof(temp_buff));
			
			return IsSeccess(temp_buff) ? J_OK : J_UNKNOW;
		}
	}
	
	return J_UNKNOW;
}

void CRtspHelper::CloseStream(J_OS::CTCPSocket *m_recvSocket, const char *pAddr, int nPort, int nChannel)
{
	char temp_buff[2048] = {0};
	//发送PLAY
	sprintf(temp_buff, RTSP_TEARDOWN, pAddr, nPort, nChannel, m_nSeq++, this);
	m_recvSocket->Write_n(temp_buff, strlen(temp_buff));
	memset(temp_buff, 0, sizeof(temp_buff));
	m_recvSocket->Read(temp_buff, sizeof(temp_buff));
}

bool CRtspHelper::IsSeccess(const char *pResp)
{
	return (strstr(pResp, "200 OK") != NULL);
}

int CRtspHelper::ParserSDP(const char *pSDP)
{
	const char *p = strstr(pSDP, "m=video");
	if (p != NULL)
	{
		const char *p2 = strstr(p, "trackID=");
		if (p2 != NULL)
		{
			m_nVideoTrackId = atoi(p2 + strlen("trackID="));
			return J_OK;
		}
	}
	return J_UNKNOW;
}