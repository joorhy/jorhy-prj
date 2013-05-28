#pragma once
#include "x_pl_base.h"
#include "x_pl_data_struct.h"
#include "x_pl_common.h"
#include <stdarg.h>

class J_PlAccess : public J_PlBase
{
public:
	static J_PlAccess *CreateInstance(j_pl_cfg_t &cfg);
	static void ReleaseInstance(J_PlAccess **pInstance); 

protected:
	J_PlAccess(j_pl_cfg_t &cfg);
	~J_PlAccess(void);

public:
	virtual J_PL_RESULT GetDemuxType(j_pl_demux_t &t) = 0;				//read some data,
	virtual J_PL_RESULT ReadBlock(char *OUT_buf,int &OUT_len) = 0;
	virtual J_PL_RESULT Control(int type,va_list args) = 0;
	virtual J_PL_RESULT RequestData(int interval) = 0;
	virtual int GuessBufferSize()= 0;

protected:
	virtual void SetAccessType(int &ID) = 0;

protected:
	int m_accessID;				//标志accessID的 protocol_type_e
	j_pl_cfg_t m_cfg;
	bool m_bUsable;				//是否是可用access 默认true
	j_pl_demux_t m_demuxParm;	
};
