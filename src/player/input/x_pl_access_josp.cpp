#include "x_pl_access_josp.h"
#include "x_pl_data_def.h"
#include "x_pl_error.h"
#include "x_pl_default_config.h"
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
		JOSP_OpenData data;
	} req_data;

	memset(&req_data.head,0,sizeof(JOSP_CtrlHead));
	strcpy((char*)req_data.head.start_code,"JOSP");
	req_data.head.version	= 2;
	req_data.head.cmd		= (type == J_PL_PLAY_REALTIME ? JOSP_OPEN_STREAM : JOSP_OPEN_FILE);
	req_data.head.ex_length	= htons(sizeof(JOSP_OpenData));

	strncpy_s(req_data.data.res_id,m_cfg.psz_resource,sizeof(req_data.data.res_id));
	req_data.data.stream_type= 0;		//主码流

	br = m_netWork->NWrite((const char*)&req_data,sizeof(RequestData));
	J_PL_FAILED(br);

	return br;
}

J_PL_RESULT CXPlJospAccess::ReadHeader(j_pl_demux_t &t)
{
	J_PL_RESULT br;
	JOSP_CtrlHead head;
	JOSP_OpenRetData data;
	
	if(!m_netWork)
		return J_PL_NO_ERROR;
	br = m_netWork->NRead((char*)&head,sizeof(head));
	J_PL_FAILED(br);

	unsigned char cmd = (m_cfg.i_real == J_PL_PLAY_REALTIME ? JOSP_OPEN_STREAM_RET : JOSP_OPEN_FILE_RET);
	if(head.cmd == cmd)
	{
		br = m_netWork->NRead((char*)&data,sizeof(data));
		m_demuxParm.fps	= data.fps;
		if(_strnicmp((const char*)data.media_code,"JOMS",sizeof(data.media_code)) == 0)
			m_demuxParm.media_type	= DEMUX_RYSP;
		else
			m_demuxParm.media_type	= DEMUX_TS;
		m_demuxParm.i_real	= m_cfg.i_real;

		//后面动态添加
		m_demuxParm.width		= data.width;
		m_demuxParm.height		= data.height;
		m_demuxParm.iframe_interval = data.iframe_interval;
		
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
	JOSP_DataHead head;
	int framenum = 0;
	int datalen = 0;
	char *tmpBuf = OUT_buf + sizeof(framenum);

	if(!m_netWork)
		return J_PL_NO_ERROR;

	if(NeedRequest())
	{
		br = RequestData();
		J_PL_FAILED(br);
	}
	while(!m_bEnd)
	{
		if(m_nNeedRequst)	//for set time；
		{
			framenum = 0;
			break;
		}

		br = m_netWork->NRead((char*)&head,sizeof(head));
		J_PL_FAILED(br);

		if(_strnicmp((char*)head.start_code,"JOAV",4) == 0)
		{
			if(ntohl(head.b_last_frame))
			{
				m_bEnd = true;
			}

			datalen = ntohl(head.data_len);
			memcpy(OUT_buf,(char*)&head,sizeof(head));

			br = m_netWork->NRead(tmpBuf+sizeof(head),datalen);
			J_PL_FAILED(br);

			OUT_len += (sizeof(head) + datalen);
			tmpBuf +=(sizeof(head) + datalen);
			framenum++;
		}
		if(ntohl(head.b_last_frame))
		{
			m_bEnd = true;
		}
	}
	memcpy(OUT_buf,&framenum,sizeof(framenum));			//告诉demux有多少帧
	m_nNeedRequst = true;

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlJospAccess::FindTime(j_pl_mtime_t &time)
{
	char *pos = strstr(m_cfg.psz_resource,"start=");
	if(!pos)
		return J_PL_ERROR_PTR;
	pos += strlen("start=");
	time = _atoi64(pos);
	return J_PL_NO_ERROR;
}

bool CXPlJospAccess::NeedRequest()
{
	bool ret;
	if(m_nNeedRequst)
	{
		if(m_bFirst)
		{
			if(FindTime(m_RequstData.time_stamp) != J_PL_NO_ERROR)
				return false;
			m_llRequesttime = m_RequstData.time_stamp;
			m_bFirst = false;
		}
		else
		{
			if(m_bForward)
			{
				m_llRequesttime += m_RequstData.time_interval;
			}
			else
			{
				m_llRequesttime -= m_RequstData.time_interval;
			}
		}
		m_RequstData.time_stamp = m_llRequesttime;
		ret = true;
		m_nNeedRequst = false;
	}
	else
	{
		ret = false;
		m_nNeedRequst = false;
	}

	return ret;
}

J_PL_RESULT CXPlJospAccess::RequestData()
{
	J_PL_RESULT br;
	JOSP_DataHead head;
	JOSP_RequestRetData headRet;
	char *tmpbuf = NULL;

	if(!m_netWork)
		return J_PL_NO_ERROR;

	while(!m_bEnd)
	{
		if(tmpbuf == NULL)
		{
			tmpbuf = new char[1024*50];
		}
		br = m_netWork->NRead((char*)&head,sizeof(head));
		J_PL_FAILED(br);

		if(_strnicmp((char*)head.start_code,"JOAV",4) == 0)
		{
			br = m_netWork->NRead(tmpbuf,sizeof(tmpbuf));
		}
		if(ntohl(head.b_last_frame))
		{
			m_bEnd = true;
		}

	}
	if(tmpbuf)
		delete tmpbuf;

	br = m_netWork->NWrite((const char*)&m_RequstData,sizeof(m_RequstData));
	J_PL_FAILED(br);
	br = m_netWork->NRead((char*)&headRet,sizeof(headRet));
	J_PL_FAILED(br);
	if(ntohl(headRet.ret) != 0)
		return J_PL_ERROR_UNKNOW;

	m_bEnd = false;

	return J_PL_NO_ERROR;
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