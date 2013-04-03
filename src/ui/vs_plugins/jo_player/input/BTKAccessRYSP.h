#pragma once
#include "..\include\btkaccess.h"
#include "..\include\BTKSockt.h"
#include "RYSPDataStruct.h"

class BTKAccessRYSP : public BTKAccess
{
public:
	BTKAccessRYSP(btk_cfg_t &cfg);
	~BTKAccessRYSP(void);

	virtual BTK_RESULT GetDemuxType(btk_demux_t &t);		
	virtual BTK_RESULT ReadBlock(char *OUT_buf,int &OUT_len);
	virtual BTK_RESULT Control(int type,va_list args);
	virtual int GuessBufferSize();

private:
	BTK_RESULT RequestServer(btk_work_type type);
	BTK_RESULT ReadHeader(btk_demux_t &t);

	//realtime only
	BTK_RESULT ReadBlockReal(char *OUT_buf,int &OUT_len);		

	//vod only
	BTK_RESULT ReadBlockFile(char *OUT_buf,int &OUT_len);			
	BTK_RESULT FindTime(btk_mtime_t &time);
	bool NeedRequest();
	BTK_RESULT RequestData();

	virtual void SetAccessType(int &ID);

private:
	BTKSockt *m_netWork;

	//vod only
	RYSP_RequestData m_RequstData;
	btk_mtime_t m_llRequesttime;				//¼ÇÂ¼Ê±¼ä

	bool m_bNeedtime;
	bool m_bFirst;
	bool m_nNeedRequst;
	bool m_bEnd;
	bool m_bForward;

};
