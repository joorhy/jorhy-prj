#include "BTKDemuxH264.h"
#include "..\include\DataDef.h"
#include "..\include\DataStruct.h"
#include "..\include\BTKError.h"
#include "..\include\BTKLog.h"

BTKDemuxH264::BTKDemuxH264(void)
{
	m_demuxID.media_type = DEMUX_H264;
	SetDecodeType(m_codec);
}

BTKDemuxH264::~BTKDemuxH264(void)
{
}

BTK_RESULT BTKDemuxH264::DemuxBlock(char *data,BTKBuffer *pIO)
{
	BTK_RESULT br = BTK_NO_ERROR;
	btk_decode_t decHead;
	btk_buffer_t bufHead;

	decHead.fps = 25;
	decHead.timestamp = 0;
	decHead.type = DECODE_I_FRAME;
	decHead.size = *(int*)(data);

	bufHead.datasize = decHead.size;
	bufHead.extrasize = sizeof(btk_decode_t);
	br = pIO->Write(data + sizeof(int),(char*)&decHead,bufHead);
	
	return br;
}

BTK_RESULT BTKDemuxH264::GetDecodeType(btk_transform_t &t)
{
	t = m_codec;
	return BTK_NO_ERROR;
}

BTK_RESULT BTKDemuxH264::SetDecodeType(btk_transform_t &t)
{
	t.aType	= CODE_UNKNOW;
	t.vType	= CODE_H264;
	return BTK_NO_ERROR;
}

BTK_RESULT BTKDemuxH264::Control(int type,va_list args)
{
	switch (type)
	{
	case ACCESS_SET_TIME:
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