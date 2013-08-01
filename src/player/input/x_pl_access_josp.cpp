#include "x_pl_access_josp.h"
#include "x_pl_data_def.h"
#include "x_pl_error.h"
#include "x_pl_default_config.h"
#include "x_pl_log.h"
#include <assert.h>
#include <string>
#include <WinSock.h>

#define J_PL_FAILED(br) \
	if(br != J_PL_NO_ERROR){return br;}

CXPlJospAccess::CXPlJospAccess(j_pl_cfg_t &cfg)
:J_PlAccess(cfg)
{
	m_netWork		= new J_PlSocket();
	m_bNeedtime		= true;
	m_nNeedRequst	= true;
	m_bEnd			= true;
	m_bForward		= true;
	memset(&m_RequstData,0,sizeof(m_RequstData));
	memset(&m_demuxParm,0,sizeof(m_demuxParm));
	if(m_netWork->NonblockConnect(cfg.psz_ip,cfg.i_port,1) != J_PL_NO_ERROR)
	//if(m_netWork->BlockConnect(cfg.psz_ip,cfg.i_port) != J_PL_NO_ERROR)
		m_bUsable = false;
}

CXPlJospAccess::~CXPlJospAccess(void)
{
	if(m_netWork)
	{
		delete m_netWork;
		m_netWork = NULL;
	}
}

J_PL_RESULT CXPlJospAccess::GetDemuxType(j_pl_demux_t &t)
{
	J_PL_RESULT br = J_PL_ERROR_CONNECT;
	if (m_bUsable)
	{
		br = RequestServer(m_cfg.i_real);
		//assert(br == J_PL_NO_ERROR);
		J_PL_FAILED(br);

		br = ReadHeader(t);
		//assert(br == J_PL_NO_ERROR);
	}

	return br;
}

J_PL_RESULT CXPlJospAccess::ReadBlock(char *OUT_buf,int &OUT_len)
{
	if(m_cfg.i_real == J_PL_PLAY_REALTIME)
		return ReadBlockReal(OUT_buf,OUT_len);
	else if(m_cfg.i_real == J_PL_PLAY_FILE)
		return ReadBlockFile(OUT_buf,OUT_len);

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlJospAccess::RequestServer(j_pl_work_type type)
{
	J_PL_RESULT br;
	if(!m_netWork)
		return J_PL_ERROR_NO_NETWORK;

	struct RequestData
	{
		JOSP_CtrlHead head;
		union
		{
			JOSP_OpenData real_data;
			JOSP_OpenVod vod_data;
		} data;
	} req_data;

	memset(&req_data.head,0,sizeof(JOSP_CtrlHead));
	strcpy((char*)req_data.head.start_code,"JOSP");
	req_data.head.version	= 2;

	if (type == J_PL_PLAY_REALTIME)
	{
		req_data.head.cmd = JOSP_OPEN_STREAM;
		req_data.head.ex_length	= htons(sizeof(JOSP_OpenData));
		strncpy_s(req_data.data.real_data.res_id,m_cfg.psz_resource,sizeof(req_data.data.real_data.res_id));
		req_data.data.real_data.stream_type= 0;		//主码流
	}
	else
	{
		req_data.head.cmd = JOSP_OPEN_FILE;
		req_data.head.ex_length	= htons(sizeof(JOSP_OpenVod));
		strncpy_s(req_data.data.vod_data.res_id,m_cfg.psz_resource,sizeof(req_data.data.vod_data.res_id));
		req_data.data.vod_data.begin_time = htonl(m_cfg.begin_time);
		req_data.data.vod_data.end_time = htonl(m_cfg.end_time);
	}

	br = m_netWork->NWrite((const char*)&req_data,sizeof(JOSP_CtrlHead) + ntohs(req_data.head.ex_length));
	J_PL_FAILED(br);

	return br;
}

J_PL_RESULT CXPlJospAccess::RequestData(int interval)
{
	J_PL_RESULT br;
	if(!m_netWork)
		return J_PL_ERROR_NO_NETWORK;

	struct RequestData
	{
		JOSP_CtrlHead head;
		JOSP_RequestData data;
	} req_data;

	memset(&req_data.head,0,sizeof(JOSP_CtrlHead));
	strcpy((char*)req_data.head.start_code,"JOSP");
	req_data.head.version	= 2;

	req_data.head.cmd = JOSP_REQ_DATA;
	req_data.head.ex_length	= htons(sizeof(JOSP_RequestData));
	strncpy_s(req_data.data.res_id,m_cfg.psz_resource,sizeof(req_data.data.res_id));
	req_data.data.time_stamp = htonl(m_cfg.begin_time);		
	req_data.data.time_interval = htonl(interval);

	br = m_netWork->NWrite((const char*)&req_data,sizeof(JOSP_CtrlHead) + ntohs(req_data.head.ex_length));
	J_PL_FAILED(br);

	return br;
}

J_PL_RESULT CXPlJospAccess::ReadHeader(j_pl_demux_t &t)
{
	J_PL_RESULT br;
	JOSP_CtrlHead head;

	union 
	{
		JOSP_OpenRetData real_data;
		JOSP_OpenVodRet vod_data;
	} data;
	
	if(!m_netWork)
		return J_PL_NO_ERROR;
	br = m_netWork->NRead((char*)&head,sizeof(head));
	J_PL_FAILED(br);

	unsigned char cmd = (m_cfg.i_real == J_PL_PLAY_REALTIME ? JOSP_OPEN_STREAM_RET : JOSP_OPEN_FILE_RET);
	if(head.cmd == cmd)
	{
		br = m_netWork->NRead((char*)&data,ntohs(head.ex_length));

		m_demuxParm.i_real	= m_cfg.i_real;
		if (m_cfg.i_real == J_PL_PLAY_REALTIME)
		{
			m_demuxParm.fps	= data.real_data.fps;
			if(_strnicmp((const char*)data.real_data.media_code,"JOMS",sizeof(data.real_data.media_code)) == 0)
				m_demuxParm.media_type	= DEMUX_RYSP;
			else
				m_demuxParm.media_type	= DEMUX_TS;

			//后面动态添加
			m_demuxParm.width		= data.real_data.width;
			m_demuxParm.height		= data.real_data.height;
			m_demuxParm.iframe_interval = data.real_data.iframe_interval;
		}
		else
		{
			m_demuxParm.fps	= data.vod_data.fps;
			if(_strnicmp((const char*)data.vod_data.media_code,"JOMS",sizeof(data.vod_data.media_code)) == 0)
				m_demuxParm.media_type	= DEMUX_RYSP;
			else
				m_demuxParm.media_type	= DEMUX_TS;

			//后面动态添加
			m_demuxParm.width		= data.vod_data.width;
			m_demuxParm.height		= data.vod_data.height;
			m_demuxParm.iframe_interval = data.vod_data.iframe_interval;
		}
		m_RequstData.time_interval = (1000 * m_demuxParm.iframe_interval / m_demuxParm.fps);

		t = m_demuxParm;
	}
	else
		return J_PL_ERROR_ACCESS_ERROR;
	

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlJospAccess::Control(int type,va_list args)
{
	j_pl_mtime_t i_64;
	int i_32;
	switch (type)
	{
	case ACCESS_SET_TIME:
		i_64 = (j_pl_mtime_t)va_arg(args,j_pl_mtime_t);
		m_nNeedRequst = true;
		m_llRequesttime = i_64;
		break;

	case ACCESS_SET_BACKRUN:

		break;

	case ACCESS_SET_SPEED:
		i_32 = (int)va_arg(args,int);
		switch(i_32)
		{
		case J_PL_SPEED_SLOWEST:
		case J_PL_SPEED_SLOWER:
		case J_PL_SPEED_SLOW:
		case J_PL_SPEED_NORMAL:
		case J_PL_SPEED_FAST:
		case J_PL_SPEED_FASTER:
			m_RequstData.time_interval = (1000 * m_demuxParm.iframe_interval / m_demuxParm.fps);
			break;
		case J_PL_SPEED_FASTEST:
			m_RequstData.time_interval = 2 * (1000 * m_demuxParm.iframe_interval / m_demuxParm.fps);
			break;
		}
		break;

	default:
		return J_PL_ERROR_ACCESS_CONTROL;
	}

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlJospAccess::ReadBlockReal(char *OUT_buf,int &OUT_len)
{
	J_PL_RESULT br;
	JOSP_DataHead head = {0};

	if(!m_netWork)
		return J_PL_NO_ERROR;

	br = m_netWork->NRead((char*)&head,sizeof(head));
	if(br == J_PL_ERROR_RECEIVE)
		return J_PL_ERROR_ACCESS_END;
	if(br == J_PL_ERROR_RECEIVE_TIMEOUT)
		return J_PL_ERROR_ACCESS_ERROR;

	//j_pl_info("%d \n", ntohl(head.data_len));
	if(_strnicmp((char*)head.start_code,"JOAV",4) == 0)
	{
		int datalen = ntohl(head.data_len);
		memcpy(OUT_buf,(char*)&head,sizeof(head));

		br = m_netWork->NRead(OUT_buf+sizeof(head),datalen);
		if(br == J_PL_ERROR_RECEIVE)
			return J_PL_ERROR_ACCESS_END;
		if(br == J_PL_ERROR_RECEIVE_TIMEOUT)
			return J_PL_ERROR_ACCESS_ERROR;

		OUT_len = sizeof(head) + datalen;

		return J_PL_NO_ERROR;
	}
	
	return J_PL_ERROR_ACCESS_END;
}

J_PL_RESULT CXPlJospAccess::ReadBlockFile(char *OUT_buf,int &OUT_len)
{
	J_PL_RESULT br;
	JOSP_DataHead head = {0};

	if(!m_netWork)
		return J_PL_NO_ERROR;

	br = m_netWork->NRead((char*)&head,sizeof(JOSP_DataHead));
	if(br == J_PL_ERROR_RECEIVE)
		return J_PL_ERROR_ACCESS_END;
	if(br == J_PL_ERROR_RECEIVE_TIMEOUT)
		return J_PL_ERROR_ACCESS_ERROR;

	//j_pl_info("%d %d\n", ntohl(head.data_len), sizeof(JOSP_DataHead));
	if(_strnicmp((char*)head.start_code,"JOAV",4) == 0)
	{
		int datalen = ntohl(head.data_len);
		memcpy(OUT_buf,(char*)&head,sizeof(head));

		br = m_netWork->NRead(OUT_buf+sizeof(head),datalen);
		if(br == J_PL_ERROR_RECEIVE)
			return J_PL_ERROR_ACCESS_END;
		if(br == J_PL_ERROR_RECEIVE_TIMEOUT)
			return J_PL_ERROR_ACCESS_ERROR;

		OUT_len = sizeof(head) + datalen;

		return J_PL_NO_ERROR;
	}

	return J_PL_ERROR_ACCESS_END;
}

int CXPlJospAccess::GuessBufferSize()
{
	if(m_cfg.i_real == J_PL_PLAY_REALTIME)
		return MAX_VIDEO_FRAME_SIZE;
	
	return 2 * (m_demuxParm.height * m_demuxParm.width * m_demuxParm.iframe_interval );
}

void CXPlJospAccess::SetAccessType(int &ID)
{
	ID = PROTOCOL_RYSP;
}