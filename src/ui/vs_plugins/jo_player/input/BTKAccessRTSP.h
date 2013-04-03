#pragma once

#include "..\include\btkaccess.h"
#include "RYSPDataStruct.h"

#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include "GroupsockHelper.hh"

class BTKAccessRTSP;

class RTSPClientBTK : public RTSPClient
{
public:
	RTSPClientBTK( UsageEnvironment& env, char const* rtspURL, int verbosityLevel,
					char const* applicationName, portNumBits tunnelOverHTTPPortNum,
					BTKAccessRTSP *p_access)
					:RTSPClient( env, rtspURL, verbosityLevel, applicationName,
								tunnelOverHTTPPortNum )
	{
		m_accessrtsp = p_access;
	}
	BTKAccessRTSP *m_accessrtsp;
};

class BTKAccessRTSP : public BTKAccess
{
public:
	BTKAccessRTSP(btk_cfg_t &cfg);
	~BTKAccessRTSP(void);

	virtual BTK_RESULT GetDemuxType(btk_demux_t &t);		
	virtual BTK_RESULT ReadBlock(char *OUT_buf,int &OUT_len);
	virtual BTK_RESULT Control(int type,va_list args);
	virtual int GuessBufferSize();

protected:
	virtual void SetAccessType(int &ID);

private:
	BTK_RESULT Connect();				//connects to the RTSP server to setup the session DESCRIBE
	BTK_RESULT SessionsSetup();			//prepares the subsessions and does the SETUP
	BTK_RESULT Play();					//starts the actual playback of the stream

	static void AfterOPTIONS(RTSPClient* client,int resultCode,char* resultString);
	static void AfterDESCRIBE(RTSPClient* client,int result_code,char* result_string);
	static void AfterSETUP(RTSPClient* client,int result_code,char* result_string);
	static void AfterPLAY(RTSPClient* client,int result_code,char* result_string);
	static void AfterTEARDOWN(RTSPClient* client,int result_code,char* result_string);
	static bool WaitResponse(BTKAccessRTSP *p_access,int i_timeout = 0);
	static void TaskInterruptRTSP(void *pUser);
	static void StreamClose(void *pUser);
	static void StreamRead( void *pUser, unsigned int i_size,
							unsigned int i_truncated_bytes, struct timeval pts,
							unsigned int duration );

private:
	TaskScheduler		*m_scheduler;
	UsageEnvironment	*m_env;
	RTSPClientBTK		*m_client;
	MediaSession		*m_session;
	MediaSubsession		*m_sub;

	char				m_event;				//rtsp事件信号
	char				m_data;					//rtsp数据信号
	int					m_live555Ret;			//返回码
	bool				m_error;				//是否错误
	bool				m_b_get_param;			//是否支持GET_PARAMETER
	char				*m_sdp;
	
	double				m_starttime;			//开始时间
	double				m_totaltime;			//总计时间
	int					m_timeout;				//超时
	unsigned int		m_size;
	unsigned char		*m_extmem;				//额外扩展mem
	unsigned char		*m_buf;					//不需要释放
	bool				m_bHaveReadFirstFrame;	//是否是第一帧

};
