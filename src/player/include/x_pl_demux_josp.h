#pragma once
#include "x_pl_demux.h"

class CXPlJospDemux : public J_PlDemux
{
public:
	CXPlJospDemux(void);
	~CXPlJospDemux(void);

	virtual J_PL_RESULT DemuxBlock(char *data,J_PlBuffer *pIO);
	virtual J_PL_RESULT GetDecodeType(j_pl_transform_t &t);
	virtual J_PL_RESULT Control(int type,va_list args);

private:
	virtual J_PL_RESULT SetDecodeType(j_pl_transform_t &t);

private:
	bool m_bFlush;			//for set time
	bool m_bNeedIframe;		//finde I frame;
};
