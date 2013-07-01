#include "RtspFilter.h"
#include "x_base64.h"
#include "x_string.h"
#include "x_socket.h"
#include "x_mux_factory.h"

const char *rtsp_end = "\r\n\r\n";

static unsigned const samplingFrequencyTable[16] = {
		96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050,
		16000, 12000, 11025, 8000, 7350, 0, 0, 0
};

#define VIDEO_TRACK_ID 	3
#define AUDIO_TRACK_ID	4

const char *ret_options =
	"RTSP/1.0 200 OK\r\n"
	"Server: Forcetv (Build/489.16; Platform/Win32; Release/Forcetv; state/beta; )\r\n"
	"Cseq: %d\r\n"
	"Public: DESCRIBE, SETUP, TEARDOWN, PLAY, PAUSE, OPTIONS\r\n\r\n";

const char *ret_describ =
	"RTSP/1.0 200 OK\r\n"
	"Server: Forcetv (Build/489.16; Platform/Win32; Release/Forcetv; state/beta; )\r\n"
	"Cseq: %d\r\n"
	"Cache-Control: must-revalidate\r\n"
	"Session: %X\r\n"
	"Content-length: %d\r\n"
	"Content-Type: application/sdp\r\n"
	"x-Accept-Retransmit: our-retransmit\r\n"
	"x-Accept-Dynamic-Rate: 1\r\n"
	"Content-Base: %s/\r\n\r\n";

const char *live_sdp =
	"v=0\r\n"
	"o=- 0 0 IN IP4 %s\r\n"
	"c=IN IP4 0.0.0.0\r\n"
	"a=control:*\r\n"
	"s=Force-live\r\n"
	"t=0 0\r\n"
	"a=range:npt=0-86400\r\n"
	"m=video 0 RTP/AVP 96\r\n"
	"a=control:trackID=3\r\n"
	"a=rtpmap:96 H264/90000\r\n"
	"a=fmtp:96 profile-level-id=%x%x%x; sprop-parameter-sets=%s,%s; packetization-mode=1\r\n"
	"m=audio 0 RTP/AVP 97\r\n"
	"b=AS:96\r\n"
	"a=rtpmap:97 MPEG4-GENERIC/16000\r\n"
	"a=fmtp:97 streamtype=5;profile-level-id=1;mode=AAC-hbr;sizelength=13;indexlength=3;indexdeltalength=3;config=%s\r\n"
	"a=control:trackID=4\r\n";

const char *ret_setup_tcp =
	"RTSP/1.0 200 OK\r\n"
	"Server: Forcetv (Build/489.16; Platform/Win32; Release/Forcetv; state/beta; )\r\n"
	"Cseq: %d\r\n"
	"Cache-Control: must-revalidate\r\n"
	"Session: %X\r\n"
	"Transport: RTP/AVP/TCP;unicast;interleaved=%s;ssrc=%s;mode=PLAY\r\n\r\n";

const char *ret_setup_udp =
	"RTSP/1.0 200 OK\r\n"
	"CSeq: %d\r\n"
	"Transport: RTP/AVP;unicast;destination=%s;source=%s;client_port=%d-%d;server_port=%d-%d\r\n"
	"Session: %X\r\n\r\n";

const char *ret_play =
	"RTSP/1.0 200 OK\r\n"
	"Server: Forcetv (Build/489.16; Platform/Win32; Release/Forcetv; state/beta; )\r\n"
	"Cseq: %d\r\n"
	"Session: %X\r\n"
	"Range: npt=0-86400\r\n"
	"RTP-Info: url=%strackID=3;seq=0;rtptime=0,url=%strackID=4\r\n\r\n";

const char *ret_pause =
		"RTSP/1.0 200 OK\r\n"
		"Server: Forcetv (Build/489.16; Platform/Win32; Release/Forcetv; state/beta; )\r\n"
		"Cseq: %d\r\n"
		"Session: %X\r\n\r\n";

const char *ret_teardown =
	"RTSP/1.0 200 OK\r\n"
	"Server: Forcetv (Build/489.16; Platform/Win32; Release/Forcetv; state/beta; )\r\n"
	"Cseq: %d\r\n"
	"Session: %X\r\n"
	"Connection: Close\r\n\r\n";

const char *ret_setup_unsport =
	"RTSP/1.0 461 Unsupported Transport\r\n\r\n";
	
JO_IMPLEMENT_INTERFACE(Filter, "rtsp", CRtspFilter::Maker)

CRtspFilter::CRtspFilter()
{
	m_bPS_Ready = false;
	m_bConfig_Ready = false;
	memset(m_sps, 0, sizeof(m_sps));
	memset(m_pps, 0, sizeof(m_pps));
	memset(m_config, 0, sizeof(m_config));
	memset(m_profile_id, 0, sizeof(m_profile_id));
	memset(m_ssrc, 0, sizeof(m_ssrc));
	memset(m_client_ip, 0, sizeof(m_client_ip));

	m_muxFilter = NULL;
	m_mediaContext = NULL;
	m_protocolStatus = J_ProUnReady;
	m_video_ssrc = 10000UL;
	m_audio_ssrc = 20000UL;
	
	memset(m_read_buff, 0, sizeof(m_read_buff));
	m_read_len = 0;

	memset(m_strResid, 0, sizeof(m_strResid));
}

CRtspFilter::~CRtspFilter()
{
	if (m_muxFilter)
		SingletonTmpl<CMuxFactory>::Instance()->DelMux(this);
}

int CRtspFilter::Parser(J_AsioDataBase &asioData)
{
	memcpy(m_read_buff + m_read_len, asioData.ioRead.buf, asioData.ioRead.finishedLen);
	if (strstr(m_read_buff, rtsp_end) == NULL)
	{
		m_read_len += asioData.ioRead.finishedLen;
		asioData.ioRead.bufLen = 1024;
		asioData.ioRead.whole = false;
		return J_NOT_COMPLATE;
	}
	ParserUri(m_read_buff);
	
	char send_buff[2048] = {0};
	switch (ParserHeaders(m_read_buff))
	{
	case RTSP_OPTIONS:
		sprintf(send_buff, ret_options, m_nCseq);
		break;
	case RTSP_DESCRIBE:
		sprintf(send_buff, ret_describ, m_nCseq, this, strlen(m_sdp_temp), m_content_base);
		memcpy(send_buff + strlen(send_buff), m_sdp_temp, strlen(m_sdp_temp));
		break;
	case RTSP_SETUP:
		sprintf(send_buff, ret_setup_tcp, m_nCseq, this, m_interleaved, m_ssrc);
		memset(m_ssrc, 0, sizeof(m_ssrc));
		break;
	case RTSP_SETUP_UNSPORT:
		memcpy(send_buff, ret_setup_unsport, strlen(ret_setup_unsport));
		break;
	case RTSP_PAUSE:
		sprintf(send_buff, ret_pause, m_nCseq, this);
		break;
	case RTSP_TEARDOWN:
		sprintf(send_buff, ret_teardown, m_nCseq, this);
		break;
	case RTSP_PLAY:
		return J_OK;
	}
	//readSocket.Write_n(send_buff, strlen(send_buff));

	return J_NOT_COMPLATE;
}

const char *CRtspFilter::GetResourceType()
{
	return "jofs";
}

int CRtspFilter::Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen)
{
	nOutLen = 0;
	if (m_protocolStatus & J_ProPlaying)
	{
		if (streamHeader.frameType == jo_audio_frame)
		{
			m_muxFilter->Convert(pInputData, streamHeader, pOutputData, nOutLen);
		}
		else
		{
#if 1
			char nalu_header[4];
			nalu_header[0] = 0x00;
			nalu_header[1] = 0x00;
			nalu_header[2] = 0x00;
			nalu_header[3] = 0x01;

			char *p = (char *)pInputData;
			int nTotleLen = streamHeader.dataLen;

			while (nTotleLen > 0)
			{
				if (memcmp(p, nalu_header, 4) != 0)
				{
					++p;
					--nTotleLen;
					continue;
				}

				if ((p[4] & 0x1f) == 5)
				{
					streamHeader.dataLen = nTotleLen - 4;
					m_muxFilter->Convert(p + 4, streamHeader, pOutputData, nOutLen);
					nTotleLen = 0;
					return J_OK;
				}
				else if ((p[4] & 0x1f) == 1 /*|| (p[4] & 0x1f) == 2 || (p[4] & 0x1f) == 3 || (p[4] & 0x1f) == 4*/)
				{
					streamHeader.dataLen = nTotleLen - 4;
					m_muxFilter->Convert(p + 4, streamHeader, pOutputData, nOutLen);
					nTotleLen = 0;
					return J_OK;
				}

				p += 4;
				nTotleLen -= 4;
			}
#endif
		}
	}
	return J_OK;
}

int CRtspFilter::Complete(J_AsioDataBase &asioData)
{
	memset(m_send_buff, 0, sizeof(m_send_buff));
	sprintf(m_send_buff, ret_play, m_nCseq, this, m_content_base, m_content_base);
	asioData.ioWrite.buf = m_send_buff;
	asioData.ioWrite.bufLen = strlen(m_send_buff);
	asioData.ioWrite.whole = true;
	
	return J_OK;
}

/*int CRtspFilter::SetContext(const J_MediaContext *cxt)
{
	m_mediaContext = (J_MediaContext *)cxt;
	if (m_mediaContext)
	{
		if (!m_bPS_Ready)
		{
			J_ContextData *contextVideo = (J_ContextData *)m_mediaContext->data;
			assert(contextVideo->forcc == JO_MAKE_FORCC('H', '2', '6', '4'));
			m_bPS_Ready = GetPS((const char *)contextVideo->cxt.data, contextVideo->cxt.len);
		}

		if (!m_bConfig_Ready)
		{
			J_ContextData *contextAudio = (J_ContextData *)(m_mediaContext->data + sizeof(J_ContextData));
			assert(contextAudio->forcc == JO_MAKE_FORCC('A', 'A', 'C', '0'));
			m_bConfig_Ready = GetConfig((const char *)contextAudio->cxt.data, contextAudio->cxt.len);
		}
		m_protocolStatus |= J_ProParamOk;
	}

	return J_OK;
}*/

bool CRtspFilter::GetPS(const char *pData, int nLen)
{
#if 0
	m_profile_id[0] = 0x4D;
	m_profile_id[1] = 0x40;
	m_profile_id[2] = 0x1E;

	char sps[] = {0x00, 0x00, 0x00, 0x01, 0x67, 0x4D, 0x40, 0x1E,
					  0x8B, 0x95, 0x81, 0x60, 0x48, 0xA1, 0x00, 0x00,
					  0x07, 0x08, 0x00, 0x01, 0x5F, 0x90, 0x84, 0x01};
	char pps[] = {0x00, 0x00, 0x00, 0x01, 0x68, 0xDE, 0x38, 0x80};
	base64_in((unsigned char *)(sps + 4), m_sps, 20);
	base64_in((unsigned char *)(pps + 4), m_pps, 4);
	return true;
#else
	char nalu_header[4];
	nalu_header[0] = 0x00;
	nalu_header[1] = 0x00;
	nalu_header[2] = 0x00;
	nalu_header[3] = 0x01;

	char *p = (char *)pData;
	char *ps = NULL;
	int nTotleLen = nLen;

	while (nTotleLen > 0)
	{
		if (memcmp(p, nalu_header, 4) != 0)
		{
			++p;
			--nTotleLen;
			continue;
		}

		ps = p;
		if ((ps[4] & 0x1f) == 7)
		{
			memcpy(m_profile_id, ps + 5, 3);
			base64_in((unsigned char *)(ps + 4), m_sps, 22);
		}
		else if((ps[4] & 0x1f) == 8)
		{
			base64_in((unsigned char *)(ps + 4), m_pps, 4);
			return true;
		}

		p += 4;
		nTotleLen -= 4;
	}

	memset(m_sps, 0, sizeof(m_sps));
	memset(m_pps, 0, sizeof(m_pps));

	return false;
#endif
}

bool CRtspFilter::GetConfig(const char *pData, int nLen)
{
#if 0
	char header[] = { 0xFF, 0xF1, 0x60, 0x40, 0x1E, 0x1F, 0xFC };
	char *fixedHeader = header;
#else
	char *fixedHeader = (char *)pData;
#endif
	if (!(((fixedHeader[0] & 0xFF) == 0xFF) && ((fixedHeader[1] & 0xF0) == 0xF0)))
		return false;

	j_uint8_t profile = (fixedHeader[2] & 0xC0) >> 6;
	if (profile == 3)
	{
		J_OS::LOGINFO("Bad profile: 3 in first frame of ADTS");
		return false;
	}

	j_uint8_t sampling_frequency_index = (fixedHeader[2] & 0x3C) >> 2;
	if (samplingFrequencyTable[sampling_frequency_index] == 0)
	{
		J_OS::LOGINFO("Bad sampling_frequency_index: in first frame of ADTS");
		return false;
	}

	j_uint8_t channel_configuration = ((fixedHeader[2] & 0x01) << 2) | ((fixedHeader[3] & 0xC0) >> 6);

	j_uint8_t audioSpecificConfig[2] = {0};
	j_uint8_t audioObjectType = profile + 1;
	audioSpecificConfig[0] = (audioObjectType << 3) | (sampling_frequency_index >> 1);
	audioSpecificConfig[1] = (sampling_frequency_index << 7) | (channel_configuration << 3);
	sprintf(m_config, "%02X%02X", audioSpecificConfig[0] & 0xFF, audioSpecificConfig[1] & 0xFF);

	return true;
}

int CRtspFilter::ParserUri(const char *request)
{
	CXString x_string(request);

	CXInteger32 i_command("cmd=", "&");
	x_string >> i_command;
	m_nCommandType = i_command();

	CXChar_n c_resid("resid=", "&");
	x_string >> c_resid;
	memcpy(m_strResid, c_resid(), strlen(c_resid()));

	m_nStreamType = 0;
	CXInteger32 i_type("type=", "&");
	x_string >> i_type;
	m_nStreamType = i_type();

	if (strstr(request, "vod") != NULL)
	{
		CXInteger64U u_start("start=", "&");
		x_string >> u_start;
		m_beginTime = u_start();

		if (m_nRtspMethord == RTSP_PAUSE)
		{
			CXFloat2 u_npt("Range: npt=", "-");
			x_string >> u_npt;
			m_beginTime = (j_uint64_t)(u_npt() * 1000);
		}

		CXInteger64U u_end("end=", "&");
		x_string >> u_end;
		m_endTime = u_end();

		if (strstr(request, "scale=") != NULL)
		{
			CXInteger32 i_scale("scale=", "&");
			x_string >> i_scale;
			m_scale = i_scale();
			m_nCommandType = jo_setscale_vod;
		}
	}

	if (strstr(request, "stream=rtp-tcp"))
	{
		m_muxFilter = SingletonTmpl<CMuxFactory>::Instance()->GetMux(this, "rtp");
	}
	else if (strstr(request, "stream=rtp-udp"))
	{
		m_muxFilter = SingletonTmpl<CMuxFactory>::Instance()->GetMux(this, "rtp");
	}
	else
	{
		m_muxFilter = SingletonTmpl<CMuxFactory>::Instance()->GetMux(this, "rtp");
	}

	return J_OK;
}

int CRtspFilter::ParserHeaders(const char *request)
{
	char *p = (char *)request;
	char *p2 = (char *)strstr(p, " ");
	if (p2 == NULL)
	{
		return J_PARAM_ERROR;
	}

	char methord[20] = {0};
	memcpy(methord, p, p2 - p);

	m_nCseq = 0;
	p = ++p2;
	p2 = (char *)strstr(p, "CSeq:");
	if (p2 == NULL)
	{
		return J_PARAM_ERROR;
	}

	p = p2 + strlen("CSeq:");
	p2 = (char *)strstr(p, "\r\n");
	if (p2 == NULL)
		return J_PARAM_ERROR;

	char cseq[10] = {0};
	memcpy(cseq, p, p2 - p);
	m_nCseq = atoi(cseq);

	if (memcmp(methord, "OPTIONS", strlen("OPTIONS")) == 0)
	{
		return RTSP_OPTIONS;
	}
	else if (memcmp(methord, "DESCRIBE", strlen("DESCRIBR")) == 0)
	{
		p = (char *)request;
		p2 = (char *)strstr(p, " ");
		if (p2 == NULL)
			return J_PARAM_ERROR;

		p = ++p2;
		p2 = (char *)strstr(p, " ");
		if (p2 == NULL)
			return J_PARAM_ERROR;

		memset(m_content_base, 0, sizeof(m_content_base));
		memcpy(m_content_base, p, p2 - p);
		p = m_content_base;
		p2 = (char *)strstr(p, "//");
		if (p2 == NULL)
			return J_PARAM_ERROR;

		p = p2 + strlen("//");
		p2 = (char *)strstr(p, ":");
		if (p2 == NULL)
			return J_PARAM_ERROR;

		char str_ip[16] = {0};
		memcpy(str_ip, p, p2 - p);
		sprintf(m_sdp_temp, live_sdp, "127.0.0.1", m_profile_id[0] & 0xFF, m_profile_id[1] & 0xFF
				, m_profile_id[2] & 0xFF, m_sps, m_pps, m_config);
				
		return RTSP_DESCRIBE;
	}
	else if (memcmp(methord, "SETUP", strlen("SETUP")) == 0)
	{
		if (strstr(p, "TCP") == NULL)
		{
			m_nRtspMethord = RTSP_SETUP_UNSPORT;
			return J_OK;
		}

		p = (char *)request;
		p2 = (char *)strstr(p, "trackID=");
		if (p2 == NULL)
			return J_PARAM_ERROR;

		p = p2 + strlen("trackID=");
		p2 = (char *)strstr(p, " ");
		if (p2 == NULL)
			return J_PARAM_ERROR;

		char track_id[4] = {0};
		memcpy(track_id, p, p2 - p);
		int nTrackId = atoi(track_id);
		if (nTrackId == VIDEO_TRACK_ID)
			sprintf(m_ssrc, "%X", m_video_ssrc);
		else
			sprintf(m_ssrc, "%X", m_audio_ssrc);

		p2 = (char *)strstr(p, "interleaved=");
		if (p2 == NULL)
			return J_PARAM_ERROR;

		p = p2 + strlen("interleaved=");
		p2 = strstr(p, "\r\n");
		if (p2 == NULL)
			return J_PARAM_ERROR;

		memset(m_interleaved, 0, sizeof(m_interleaved));
		memcpy(m_interleaved, p, p2 - p);
		
		return RTSP_SETUP;
	}
	else if (memcmp(methord, "PLAY", strlen("PLAY")) == 0)
	{
		m_nRtspMethord = RTSP_PLAY;
		p = (char *)request;
		p2 = (char *)strstr(p, " ");
		if (p2 == NULL)
			return J_PARAM_ERROR;

		p = ++p2;
		p2 = (char *)strstr(p, " ");
		if (p2 == NULL)
			return J_PARAM_ERROR;

		memset(m_content_base, 0, sizeof(m_content_base));
		memcpy(m_content_base, p, p2 - p);

		m_protocolStatus |= J_ProConnOk;
		m_protocolStatus &= ~J_ProPaused;
		
		return jo_start_vod;
	}
	else if (memcmp(methord, "PAUSE", strlen("PAUSE")) == 0)
	{
		m_nRtspMethord = RTSP_PAUSE;
		m_protocolStatus |= J_ProDataUnReady;
		m_protocolStatus |= J_ProPaused;
		
		return jo_pause_vod;
	}
	else if (memcmp(methord, "TEARDOWN", strlen("TEARDOWN")) == 0)
	{
		if (!(m_protocolStatus & J_ProPlaying))
			return J_UNKNOW;

		return RTSP_TEARDOWN;
	}

	return J_OK;
}

