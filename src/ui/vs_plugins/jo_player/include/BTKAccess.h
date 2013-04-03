#pragma once
#include "btkbase.h"
#include "DataStruct.h"
#include "BTKCommon.h"
#include <stdarg.h>

class BTKAccess : public BTKBase
{
public:
	static BTKAccess *CreateInstance(btk_cfg_t &cfg);
	static void ReleaseInstance(BTKAccess **pInstance); 

protected:
	BTKAccess(btk_cfg_t &cfg);
	~BTKAccess(void);

public:
	virtual BTK_RESULT GetDemuxType(btk_demux_t &t) = 0;				//read some data,
	virtual BTK_RESULT ReadBlock(char *OUT_buf,int &OUT_len) = 0;
	virtual BTK_RESULT Control(int type,va_list args) = 0;
	virtual int GuessBufferSize()= 0;

protected:
	virtual void SetAccessType(int &ID) = 0;

protected:
	int m_accessID;				//标志accessID的 protocol_type_e
	btk_cfg_t m_cfg;
	bool m_bUsable;				//是否是可用access 默认true
	btk_demux_t m_demuxParm;	
};
