#pragma once
#include "btkbase.h"
#include "BTKCommon.h"
#include "DataStruct.h"
#include "BTKBuffer.h"

class BTKDemux : public BTKBase
{
public:
	static BTKDemux *CreateInstance(btk_demux_t &t);
	static void ReleaseInstance(BTKDemux **pInstance);

	virtual BTK_RESULT DemuxBlock(char *data,BTKBuffer *pIO) = 0;
	virtual BTK_RESULT GetDecodeType(btk_transform_t &t) = 0;
	virtual BTK_RESULT Control(int type,va_list args) = 0;

protected:
	BTKDemux(void);
	~BTKDemux(void);
	virtual BTK_RESULT SetDecodeType(btk_transform_t &t) = 0;

protected:
	btk_demux_t m_demuxID;
	btk_transform_t m_codec;
};
