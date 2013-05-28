#include "x_pl_demux_josp.h"
#include "x_pl_data_def.h"
#include "x_pl_data_struct.h"
#include "x_pl_error.h"
#include "x_pl_josp_data_struct.h"
#include "x_pl_misc.h"
#include "x_pl_log.h"
#include <WinSock.h>
#include <string>

CXPlJospDemux::CXPlJospDemux(void)
{
	m_demuxID.media_type = DEMUX_RYSP;
	SetDecodeType(m_codec);
	m_bFlush = false;
	m_bNeedIframe = true;
}

CXPlJospDemux::~CXPlJospDemux(void)
{
}

J_PL_RESULT CXPlJospDemux::DemuxBlock(char *data,J_PlBuffer *pIO)
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	JOSP_DataHead *head;
	j_pl_decode_t decHead;
	j_pl_buffer_t bufHead;

	head = (JOSP_DataHead*)data;
	
	if(m_bNeedIframe)
	{
		unsigned short frametype = ntohl(head->frame_type);
		if(frametype != 3)
			return br;
		else
			m_bNeedIframe = false;
	}

	if(m_demuxID.i_real == J_PL_PLAY_REALTIME)
	{
	
		decHead.fps			= m_demuxID.fps;
		decHead.size		= ntohl(head->data_len);
		decHead.timestamp	= j_pl_ntohll(head->time_stamp);
		unsigned int frametype = ntohl(head->frame_type);

		switch(frametype)
		{
		case 3:
			decHead.type = DECODE_I_FRAME;
			break;

		case 4:
			decHead.type = DECODE_B_FRAME;
			break;

		case 5:
			decHead.type = DECODE_P_FRAME;
			break;

		case 6:
			return J_PL_NO_ERROR;			//暂时不处理音频
			break;
		}

		bufHead.datasize	= decHead.size;
		bufHead.extrasize	= sizeof(j_pl_decode_t);
		bufHead.datatype = 0;
		br = pIO->Write(data+sizeof(JOSP_DataHead),(char*)&decHead,bufHead);
		if(br == J_PL_ERROR_FULL_BUFFER)
		{
			pIO->Flush();			//decode 处理不过来
			m_bNeedIframe = true;
		}
	}
	else
	{
		decHead.fps			= m_demuxID.fps;
		decHead.size		= ntohl(head->data_len);
		decHead.timestamp	= j_pl_ntohll(head->time_stamp);
		unsigned int frametype = ntohl(head->frame_type);

		switch(frametype)
		{
		case 3:
			decHead.type = DECODE_I_FRAME;
			break;

		case 4:
			decHead.type = DECODE_B_FRAME;
			break;

		case 5:
			decHead.type = DECODE_P_FRAME;
			break;

		case 6:
			return J_PL_NO_ERROR;			//暂时不处理音频
			break;
		}

		bufHead.datasize	= decHead.size;
		bufHead.extrasize	= sizeof(j_pl_decode_t);
		bufHead.datatype = 0;
		br = pIO->Write(data+sizeof(JOSP_DataHead),(char*)&decHead,bufHead);
		if(br == J_PL_ERROR_FULL_BUFFER)
		{
			pIO->Flush();			//decode 处理不过来
			m_bNeedIframe = true;
		}
	}
	return br;
}

J_PL_RESULT CXPlJospDemux::GetDecodeType(j_pl_transform_t &t)
{
	t = m_codec;
	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlJospDemux::SetDecodeType(j_pl_transform_t &t)
{
	t.aType	= CODE_UNKNOW;
	t.vType	= CODE_H264;
	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlJospDemux::Control(int type,va_list args)
{
	switch (type)
	{
	case ACCESS_SET_TIME:
		m_bFlush = true;
		break;

	case ACCESS_SET_BACKRUN:
		break;

	case ACCESS_SET_SPEED:
		break;

	default:
		return J_PL_ERROR_DEMUX_CONTROL;
	}

	return J_PL_NO_ERROR;
}