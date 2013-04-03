#include "BTKDemuxRYSP.h"
#include "..\include\DataDef.h"
#include "..\include\DataStruct.h"
#include "..\include\BTKError.h"
#include "RYSPDataStruct.h"
#include <WinSock.h>
#include <string>
#include "..\include\BTKMisc.h"
#include "..\include\BTKLog.h"

BTKDemuxRYSP::BTKDemuxRYSP(void)
{
	m_demuxID.media_type = DEMUX_RYSP;
	SetDecodeType(m_codec);
	m_bFlush = false;
	m_bNeedIframe = true;
}

BTKDemuxRYSP::~BTKDemuxRYSP(void)
{
}

BTK_RESULT BTKDemuxRYSP::DemuxBlock(char *data,BTKBuffer *pIO)
{
	BTK_RESULT br = BTK_NO_ERROR;
	RYSP_DataHead *head;
	btk_decode_t decHead;
	btk_buffer_t bufHead;

	head = (RYSP_DataHead*)data;
	
	if(m_bNeedIframe)
	{
		unsigned short frametype = ntohl(head->frame_type);
		if(frametype != 3)
			return br;
		else
			m_bNeedIframe = false;
	}

	if(m_demuxID.i_real == BTK_PLAY_REALTIME)
	{
	
		decHead.fps			= m_demuxID.fps;
		decHead.size		= ntohl(head->data_len);
		decHead.timestamp	= BTK_ntohll(head->time_stamp);
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
			return BTK_NO_ERROR;			//暂时不处理音频
			break;
		}

		bufHead.datasize	= decHead.size;
		bufHead.extrasize	= sizeof(btk_decode_t);
		br = pIO->Write(data+sizeof(RYSP_DataHead),(char*)&decHead,bufHead);
		if(br == BTK_ERROR_FULL_BUFFER)
		{
			pIO->Flush();			//decode 处理不过来
			m_bNeedIframe = true;
		}
	}
	else
	{
		int num = *(int*)data;
		char *pos = data + sizeof(num);
		for(int i=0;i<num;i++)
		{
			if(m_bFlush)
			{
				pIO->Flush();
				break;
			}
			head = (RYSP_DataHead*)pos;

			decHead.fps			= m_demuxID.fps;
			decHead.size		= ntohl(head->data_len);
			decHead.timestamp	= BTK_ntohll(head->time_stamp);
			unsigned short frametype = ntohl(head->frame_type);
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
				return BTK_NO_ERROR;			//暂时不处理音频
				break;
			}

			bufHead.datasize	= decHead.size;
			bufHead.extrasize	= sizeof(btk_decode_t);
			br = pIO->Write(pos+sizeof(RYSP_DataHead),(char*)&decHead,bufHead);
			if(br != BTK_NO_ERROR)
				return br;

			pos += (sizeof(RYSP_DataHead) + decHead.size);
		}
		m_bFlush = false;
	}
	return br;
}

BTK_RESULT BTKDemuxRYSP::GetDecodeType(btk_transform_t &t)
{
	t = m_codec;
	return BTK_NO_ERROR;
}

BTK_RESULT BTKDemuxRYSP::SetDecodeType(btk_transform_t &t)
{
	t.aType	= CODE_UNKNOW;
	t.vType	= CODE_H264;
	return BTK_NO_ERROR;
}

BTK_RESULT BTKDemuxRYSP::Control(int type,va_list args)
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
		return BTK_ERROR_DEMUX_CONTROL;
	}

	return BTK_NO_ERROR;
}