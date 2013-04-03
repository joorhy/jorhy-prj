#include "BTKAccessRTSP.h"
#include "..\include\BTKError.h"
#include "..\include\BTKLog.h"
#include "..\include\BTKString.h"

#define FailPTR(p) if(!p){return BTK_ERROR_LIVE555;}

BTKAccessRTSP::BTKAccessRTSP(btk_cfg_t &cfg)
:BTKAccess(cfg)
{
	m_scheduler	= NULL;
	m_env		= NULL;
	m_client	= NULL;
	m_session	= NULL;
	m_sub		= NULL;
	m_event		= 0;
	m_data		= 0;
	m_live555Ret= 0;
	m_error		= true;
	m_b_get_param = false;
	m_sdp		= NULL;
	m_extmem	= NULL;
	m_buf		= NULL;
	m_bHaveReadFirstFrame = false;
}

BTKAccessRTSP::~BTKAccessRTSP(void)
{
	m_client->sendTeardownCommand(*m_session,AfterTEARDOWN);
	WaitResponse(this);

	if(m_session)
		Medium::close(m_session);
	if(m_client)
		RTSPClient::close(m_client);
	if(m_env)
		m_env->reclaim();	
	if(m_scheduler)
		delete m_scheduler;
	if(m_sdp)
		delete m_sdp;
	if(m_extmem)
		delete m_extmem;
}

BTK_RESULT BTKAccessRTSP::GetDemuxType(btk_demux_t &t)
{
	BTK_RESULT br = BTK_NO_ERROR;

	m_scheduler	= BasicTaskScheduler::createNew();
	FailPTR(m_scheduler);

	m_env		= BasicUsageEnvironment::createNew(*m_scheduler);
	FailPTR(m_env);

	br = Connect();
	if(br != BTK_NO_ERROR)
		return br;

	br = SessionsSetup();
	if(br != BTK_NO_ERROR)
		return br;

	br = Play();
	if(br != BTK_NO_ERROR)
		return br;

	t = m_demuxParm;

	return br;
}

BTK_RESULT BTKAccessRTSP::ReadBlock(char *OUT_buf,int &OUT_len)
{
	BTK_RESULT br = BTK_NO_ERROR;
	
	if(m_extmem == NULL)
	{
		m_extmem = new unsigned char[GuessBufferSize()];
	}

	m_data = 0;
	m_buf = (unsigned char *)OUT_buf;			//attach Ö¸Õë
	m_sub->rtpSource()->getNextFrame(m_extmem,GuessBufferSize(),StreamRead,this,StreamClose,this);
	m_scheduler->doEventLoop(&m_data);

	OUT_len = m_size;
	m_buf = NULL;				//detach Ö¸Õë				

	return br;
}

BTK_RESULT BTKAccessRTSP::Control(int type,va_list args)
{
	BTK_RESULT br = BTK_NO_ERROR;
	return br;
}

int BTKAccessRTSP::GuessBufferSize()
{
	return 1024*1024*10;
}

void BTKAccessRTSP::SetAccessType(int &ID)
{
	ID = PROTOCOL_RTSP;
}


BTK_RESULT BTKAccessRTSP::Connect()
{
	BTK_RESULT br = BTK_NO_ERROR;
	char *url = new char[sizeof(m_cfg)];
	char progname[256] = {0};

	sprintf(url,"rtsp://%s:%d/%s",m_cfg.psz_ip,m_cfg.i_port,m_cfg.psz_resource);
	GetModuleFileName(NULL,progname,sizeof(progname));

	m_client	= new RTSPClientBTK(*m_env, url,1,progname,0,this);
	delete url;
	FailPTR(m_client);
	
	m_client->sendOptionsCommand(AfterOPTIONS,NULL);
	
	
	if(!WaitResponse(this))
	{
		br = BTK_ERROR_LIVE555;
	}
	

	return br;
}

BTK_RESULT BTKAccessRTSP::SessionsSetup()
{
	BTK_RESULT br = BTK_NO_ERROR;
	MediaSubsessionIterator *iter   = NULL;
	MediaSubsession         *sub    = NULL;

	unsigned int   i_buffer = 0;
	unsigned const thresh = 200000; /* RTP reorder threshold .2 second (default .1) */


	m_session = MediaSession::createNew(*m_env,m_sdp);
	if(!m_session)
	{
		btk_Error("Could not create the RTSP Session: %s",m_env->getResultMsg());
		br = BTK_ERROR_LIVE555;
		return br;
	}

	iter = new MediaSubsessionIterator(*m_session);
	while((sub = iter->next()) != NULL)
	{
		if( !strcmp( sub->mediumName(), "audio" ) )
			i_buffer = 500000;
		else if( !strcmp( sub->mediumName(), "video" ) )
			i_buffer = 1000000;
		else if( !strcmp( sub->mediumName(), "text" ) )
			;
		else continue;

		if(!sub->initiate())
		{
			btk_Warn("RTP subsession '%s/%s' failed (%s)",
					sub->mediumName(), sub->codecName(),
					m_env->getResultMsg() );
		}
		else
		{
			if(sub->rtpSource() != NULL )
			{
				int fd = sub->rtpSource()->RTPgs()->socketNum();
				/* Increase the buffer size */
				if( i_buffer > 0 )
					increaseReceiveBufferTo(*m_env,fd,i_buffer );

				/* Increase the RTP reorder timebuffer just a bit */
				sub->rtpSource()->setPacketReorderingThresholdTime(thresh);
			}

			btk_Info("RTP subsession '%s/%s'", sub->mediumName(),sub->codecName());
			m_client->sendSetupCommand(*sub,AfterSETUP);
			if(!WaitResponse(this))
			{
				br = BTK_ERROR_LIVE555;
			}

			/* Check if we will receive data from this subsession for
			* this track */
			if(sub->readSource() == NULL ) 
				continue;

			m_sub = sub;
			if(!strcmp( sub->mediumName(), "audio" ))
			{
				/*AC3 L20 PCMA PCMU .etc*/
			}
			else if(!strcmp( sub->mediumName(), "video" ))
			{
				/*MPV H263 H261 .ect*/
				if(!strcmp( sub->codecName(), "H264"))
				{
					m_demuxParm.media_type = DEMUX_H264;
					m_demuxParm.height = 960;//sub->videoHeight();
					m_demuxParm.width = 1280;//sub->videoWidth();
					m_demuxParm.fps	= 25;//sub->videoFPS();
					m_demuxParm.iframe_interval = 5;
				}
			}
			else if( !strcmp( sub->mediumName(), "text" ))
			{
				
			}

			if( sub->rtcpInstance() != NULL )
			{
				sub->rtcpInstance()->setByeHandler( StreamClose,this);
			}
			m_starttime = m_session->playStartTime();
			m_totaltime	= m_session->playEndTime();

			btk_Info("Setup Start: %f Stop: %f",m_starttime,m_totaltime);
		}
	}
	return br;
}


BTK_RESULT BTKAccessRTSP::Play()
{
	m_client->sendPlayCommand(*m_session,AfterPLAY,m_starttime);

	if(!WaitResponse(this))
	{
		btk_Error("RTSP PLAY failed %s", m_env->getResultMsg());
		return BTK_ERROR_LIVE555;
	}
	m_timeout = m_client->sessionTimeoutParameter();

	m_starttime = m_session->playStartTime();
	if(m_session->playEndTime() > 0)
		m_totaltime	= m_session->playEndTime();

	btk_Info("Setup Start: %f Stop: %f",m_starttime,m_totaltime);

	return BTK_NO_ERROR;

}
/*********************************static call***************************************/
void BTKAccessRTSP::AfterOPTIONS(RTSPClient* client,int resultCode,char* resultString)
{
	RTSPClientBTK *client_btk = reinterpret_cast<RTSPClientBTK *>(client);
	BTKAccessRTSP *pThis = client_btk->m_accessrtsp;

	pThis->m_live555Ret = resultCode;
	if(resultCode != 0)
	{
		pThis->m_error = true;
		pThis->m_event = 1;
	}
	else
	{
		pThis->m_b_get_param = (resultString != NULL && strstr( resultString, "GET_PARAMETER" ) != NULL);
		client_btk->sendDescribeCommand(AfterDESCRIBE );
	}
	delete[] resultString;
}

bool BTKAccessRTSP::WaitResponse( BTKAccessRTSP *p_access,int i_timeout)
{
	TaskToken task;
	p_access->m_event = 0;
	if(i_timeout > 0)
	{
		 /* Create a task that will be called if we wait more than timeout ms */
		task = p_access->m_scheduler->scheduleDelayedTask(i_timeout*1000,TaskInterruptRTSP,p_access);
	}
	p_access->m_event = 0;
	p_access->m_error = true;
	p_access->m_live555Ret = 0;

	p_access->m_scheduler->doEventLoop(&p_access->m_event);

	if(i_timeout > 0)
	{
		 /* remove the task */
		p_access->m_scheduler->unscheduleDelayedTask(task);
	}
	return !p_access->m_error;
}

void BTKAccessRTSP::AfterDESCRIBE(RTSPClient* client,int resultCode,char* resultString)
{
	RTSPClientBTK *client_btk = reinterpret_cast<RTSPClientBTK *>(client);
	BTKAccessRTSP *pThis = client_btk->m_accessrtsp;

	if(resultCode != 0)
	{
		pThis->m_error = true;
	}
	else
	{
		pThis->m_error = false;
		pThis->m_sdp = BTKString::StrDup(resultString);
		btk_Info(resultString);
	}

	delete[] resultString;
	pThis->m_event = 1;
}

void BTKAccessRTSP::AfterSETUP(RTSPClient* client,int resultCode,char* resultString)
{
	RTSPClientBTK *client_btk = reinterpret_cast<RTSPClientBTK *>(client);
	BTKAccessRTSP *pThis = client_btk->m_accessrtsp;
	
	delete[] resultString;
	pThis->m_live555Ret = resultCode;
	pThis->m_error = (resultCode != 0);
	pThis->m_event = 1;
}

void BTKAccessRTSP::AfterPLAY(RTSPClient* client,int resultCode,char* resultString)
{
	RTSPClientBTK *client_btk = reinterpret_cast<RTSPClientBTK *>(client);
	BTKAccessRTSP *pThis = client_btk->m_accessrtsp;

	delete[] resultString;
	pThis->m_live555Ret = resultCode;
	pThis->m_error = (resultCode != 0);
	pThis->m_event = 1;
}

void BTKAccessRTSP::AfterTEARDOWN(RTSPClient* client,int resultCode,char* resultString)
{
	RTSPClientBTK *client_btk = reinterpret_cast<RTSPClientBTK *>(client);
	BTKAccessRTSP *pThis = client_btk->m_accessrtsp;

	pThis->m_event = 1;
}

void BTKAccessRTSP::TaskInterruptRTSP(void *pUser)
{
	BTKAccessRTSP *pThis = (BTKAccessRTSP*)pUser;
	
	pThis->m_event = 0xff;
}

void BTKAccessRTSP::StreamClose(void *pUser)
{
	BTKAccessRTSP *pThis = (BTKAccessRTSP*)pUser;

	btk_Info("RTSP Stream Close\n");

	pThis->m_event = 0xff;
	pThis->m_data = 0xff;
	pThis->m_error = true;
}

void BTKAccessRTSP::StreamRead( void *pUser, unsigned int i_size,
								unsigned int i_truncated_bytes, struct timeval pts,
								unsigned int duration )
{
	unsigned char const start_code[4] = {0x00, 0x00, 0x00, 0x01};

	BTKAccessRTSP *pThis = (BTKAccessRTSP*)pUser;
	int size = 0;
	unsigned char *buf = pThis->m_buf + sizeof(size);
	if(!pThis->m_bHaveReadFirstFrame)
	{
		unsigned numSPropRecords;
		SPropRecord* sPropRecords = parseSPropParameterSets(pThis->m_sdp, numSPropRecords);
		for (unsigned i = 0; i < numSPropRecords; ++i) 
		{
			memcpy(buf + size,start_code,4);
			size += 4;
			memcpy(buf + size,sPropRecords[i].sPropBytes, sPropRecords[i].sPropLength);
			size += sPropRecords[i].sPropLength;
		}
		delete[] sPropRecords;
		pThis->m_bHaveReadFirstFrame = True; // for next time
	}
	memcpy(buf + size,start_code,4);
	size += 4;
	memcpy(buf +size,pThis->m_extmem,i_size);
	size += i_size;
	memcpy(pThis->m_buf,&size,sizeof(size));

	pThis->m_size = size;
	pThis->m_data = 1;
}