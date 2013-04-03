#pragma once
#include "..\include\btkdemux.h"

class BTKDemuxRYSP : public BTKDemux
{
public:
	BTKDemuxRYSP(void);
	~BTKDemuxRYSP(void);

	virtual BTK_RESULT DemuxBlock(char *data,BTKBuffer *pIO);
	virtual BTK_RESULT GetDecodeType(btk_transform_t &t);
	virtual BTK_RESULT Control(int type,va_list args);

private:
	virtual BTK_RESULT SetDecodeType(btk_transform_t &t);

private:
	bool m_bFlush;			//for set time
	bool m_bNeedIframe;		//finde I frame;
};
