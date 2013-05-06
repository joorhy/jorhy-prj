#pragma once
#include "x_pl_base.h"
#include "x_pl_common.h"
#include "x_pl_data_struct.h"
#include "x_pl_buffer.h"

class J_PlDemux : public J_PlBase
{
public:
	static J_PlDemux *CreateInstance(j_pl_demux_t &t);
	static void ReleaseInstance(J_PlDemux **pInstance);

	virtual J_PL_RESULT DemuxBlock(char *data,J_PlBuffer *pIO) = 0;
	virtual J_PL_RESULT GetDecodeType(j_pl_transform_t &t) = 0;
	virtual J_PL_RESULT Control(int type,va_list args) = 0;

protected:
	J_PlDemux(void);
	~J_PlDemux(void);
	virtual J_PL_RESULT SetDecodeType(j_pl_transform_t &t) = 0;

protected:
	j_pl_demux_t m_demuxID;
	j_pl_transform_t m_codec;
};
