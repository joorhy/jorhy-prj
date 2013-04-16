#include "BTKAccessRYSP.h"
#include "..\include\DataDef.h"
#include "..\include\BTKError.h"
#include "..\include\DefaultConfig.h"
#include <assert.h>
#include <string>
#include <WinSock.h>

#define FAILED_BTK(br) \
	if(br != BTK_NO_ERROR){return br;}

BTKAccessRYSP::BTKAccessRYSP(btk_cfg_t &cfg)
:BTKAccess(cfg)
{
	m_netWork		= new BTKSockt();
	m_bNeedtime		= true;
	m_nNeedRequst	= true;
	m_bEnd			= true;
	m_bForward		= true;
	memset(&m_RequstData,0,sizeof(m_RequstData));
	memset(&m_demuxParm,0,sizeof(m_demuxParm));
	//if(m_netWork->NonblockConnect(cfg.psz_ip,cfg.i_port,1) != BTK_NO_ERROR)
	if(m_netWork->BlockConnect(cfg.psz_ip,cfg.i_port) != BTK_NO_ERROR)
		m_bUsable = false;
}

BTKAccessRYSP::~BTKAccessRYSP(void)
{
	if(m_netWork)
	{
		delete m_netWork;
		m_netWork = NULL;
	}
}

BTK_RESULT BTKAccessRYSP::GetDemuxType(btk_demux_t &t)
{
	BTK_RESULT br;
	br = RequestServer(m_cfg.i_real);
	//assert(br == BTK_NO_ERROR);
	FAILED_BTK(br);

	br = ReadHeader(t);
	//assert(br == BTK_NO_ERROR);

	return br;
}

BTK_RESULT BTKAccessRYSP::ReadBlock(char *OUT_buf,int &OUT_len)
{
	if(m_cfg.i_real == BTK_PLAY_REALTIME)
		return ReadBlockReal(OUT_buf,OUT_len);
	else if(m_cfg.i_real == BTK_PLAY_FILE)
		return ReadBlockFile(OUT_buf,OUT_len);

	return BTK_NO_ERROR;
}

BTK_RESULT BTKAccessRYSP::RequestServer(btk_work_type type)
{
	BTK_RESULT br;
	if(!m_netWork)
		return BTK_ERROR_NO_NETWORK;

	struct RequestData
	{
		RYSP_CtrlHead head;
		RYSP_OpenData data;
	} req_data;

	memset(&req_data.head,0,sizeof(RYSP_CtrlHead));
	strcpy((char*)req_data.head.start_code,"JOSP");
	req_data.head.version	= 2;
	req_data.head.cmd		= (type == BTK_PLAY_REALTIME ? RYSP_OPEN_STREAM : RYSP_OPEN_FILE);
	req_data.head.ex_length	= htons(sizeof(RYSP_OpenData));

	strncpy_s(req_data.data.res_id,m_cfg.psz_resource,sizeof(req_data.data.res_id));
	req_data.data.stream_type= 0;		//主码流

	br = m_netWork->NWrite((const char*)&req_data,sizeof(RequestData));
	FAILED_BTK(br);

	return br;
}

BTK_RESULT BTKAccessRYSP::ReadHeader(btk_demux_t &t)
{
	BTK_RESULT br;
	RYSP_CtrlHead head;
	RYSP_OpenRetData data;
	
	if(!m_netWork)
		return BTK_NO_ERROR;
	br = m_netWork->NRead((char*)&head,sizeof(head));
	FAILED_BTK(br);

	unsigned char cmd = (m_cfg.i_real == BTK_PLAY_REALTIME ? RYSP_OPEN_STREAM_RET : RYSP_OPEN_FILE_RET);
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
		return BTK_ERROR_ACCESS_ERROR;
	

	return BTK_NO_ERROR;
}

BTK_RESULT BTKAccessRYSP::Control(int type,va_list args)
{
	btk_mtime_t i_64;
	int i_32;
	switch (type)
	{
	case ACCESS_SET_TIME:
		i_64 = (btk_mtime_t)va_arg(args,btk_mtime_t);
		m_nNeedRequst = true;
		m_llRequesttime = i_64;
		break;

	case ACCESS_SET_BACKRUN:

		break;

	case ACCESS_SET_SPEED:
		i_32 = (int)va_arg(args,int);
		switch(i_32)
		{
		case BTK_SPEED_SLOWEST:
		case BTK_SPEED_SLOWER:
		case BTK_SPEED_SLOW:
		case BTK_SPEED_NORMAL:
		case BTK_SPEED_FAST:
		case BTK_SPEED_FASTER:
			m_RequstData.time_interval = (1000 * m_demuxParm.iframe_interval / m_demuxParm.fps);
			break;
		case BTK_SPEED_FASTEST:
			m_RequstData.time_interval = 2 * (1000 * m_demuxParm.iframe_interval / m_demuxParm.fps);
			break;
		}
		break;

	default:
		return BTK_ERROR_ACCESS_CONTROL;
	}

	return BTK_NO_ERROR;
}

BTK_RESULT BTKAccessRYSP::ReadBlockReal(char *OUT_buf,int &OUT_len)
{
	BTK_RESULT br;
	RYSP_DataHead head = {0};

	if(!m_netWork)
		return BTK_NO_ERROR;

	br = m_netWork->NRead((char*)&head,sizeof(head));
	if(br == BTK_ERROR_RECEIVE)
		return BTK_ERROR_ACCESS_END;
	if(br == BTK_ERROR_RECEIVE_TIMEOUT)
		return BTK_ERROR_ACCESS_ERROR;

	if(_strnicmp((char*)head.start_code,"JOAV",4) == 0)
	{
		int datalen = ntohl(head.data_len);
		memcpy(OUT_buf,(char*)&head,sizeof(head));

		br = m_netWork->NRead(OUT_buf+sizeof(head),datalen);
		if(br == BTK_ERROR_RECEIVE)
			return BTK_ERROR_ACCESS_END;
		if(br == BTK_ERROR_RECEIVE_TIMEOUT)
			return BTK_ERROR_ACCESS_ERROR;

		OUT_len = sizeof(head) + datalen;

		return BTK_NO_ERROR;
	}
	
	return BTK_ERROR_ACCESS_END;
}

BTK_RESULT BTKAccessRYSP::ReadBlockFile(char *OUT_buf,int &OUT_len)
{
	BTK_RESULT br;
	RYSP_DataHead head;
	int framenum = 0;
	int datalen = 0;
	char *tmpBuf = OUT_buf + sizeof(framenum);

	if(!m_netWork)
		return BTK_NO_ERROR;

	if(NeedRequest())
	{
		br = RequestData();
		FAILED_BTK(br);
	}
	while(!m_bEnd)
	{
		if(m_nNeedRequst)	//for set time；
		{
			framenum = 0;
			break;
		}

		br = m_netWork->NRead((char*)&head,sizeof(head));
		FAILED_BTK(br);

		if(_strnicmp((char*)head.start_code,"JOAV",4) == 0)
		{
			if(ntohl(head.b_last_frame))
			{
				m_bEnd = true;
			}

			datalen = ntohl(head.data_len);
			memcpy(OUT_buf,(char*)&head,sizeof(head));

			br = m_netWork->NRead(tmpBuf+sizeof(head),datalen);
			FAILED_BTK(br);

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

	return BTK_NO_ERROR;
}

BTK_RESULT BTKAccessRYSP::FindTime(btk_mtime_t &time)
{
	char *pos = strstr(m_cfg.psz_resource,"start=");
	if(!pos)
		return BTK_ERROR_PTR;
	pos += strlen("start=");
	time = _atoi64(pos);
	return BTK_NO_ERROR;
}

bool BTKAccessRYSP::NeedRequest()
{
	bool ret;
	if(m_nNeedRequst)
	{
		if(m_bFirst)
		{
			if(FindTime(m_RequstData.time_stamp) != BTK_NO_ERROR)
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

BTK_RESULT BTKAccessRYSP::RequestData()
{
	BTK_RESULT br;
	RYSP_DataHead head;
	RYSP_RequestRetData headRet;
	char *tmpbuf = NULL;

	if(!m_netWork)
		return BTK_NO_ERROR;

	while(!m_bEnd)
	{
		if(tmpbuf == NULL)
		{
			tmpbuf = new char[1024*50];
		}
		br = m_netWork->NRead((char*)&head,sizeof(head));
		FAILED_BTK(br);

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
	FAILED_BTK(br);
	br = m_netWork->NRead((char*)&headRet,sizeof(headRet));
	FAILED_BTK(br);
	if(ntohl(headRet.ret) != 0)
		return BTK_ERROR_UNKNOW;

	m_bEnd = false;

	return BTK_NO_ERROR;
}

int BTKAccessRYSP::GuessBufferSize()
{
	if(m_cfg.i_real == BTK_PLAY_REALTIME)
		return MAX_VIDEO_FRAME_SIZE;
	
	return 2 * (m_demuxParm.height * m_demuxParm.width * m_demuxParm.iframe_interval );
}

void BTKAccessRYSP::SetAccessType(int &ID)
{
	ID = PROTOCOL_RYSP;
}