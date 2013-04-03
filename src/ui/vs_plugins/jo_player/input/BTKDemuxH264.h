#pragma once
#include "..\include\btkdemux.h"

class BTKDemuxH264 : public BTKDemux
{
public:
	BTKDemuxH264(void);
	~BTKDemuxH264(void);

	virtual BTK_RESULT DemuxBlock(char *data,BTKBuffer *pIO);
	virtual BTK_RESULT GetDecodeType(btk_transform_t &t);
	virtual BTK_RESULT Control(int type,va_list args);

private:
	virtual BTK_RESULT SetDecodeType(btk_transform_t &t);

};