#pragma once
#include "x_pl_access.h"
#include "x_pl_socket.h"
#include "x_pl_josp_data_struct.h"

class CXPlJospAccess : public J_PlAccess
{
public:
	CXPlJospAccess(j_pl_cfg_t &cfg);
	~CXPlJospAccess(void);

	virtual J_PL_RESULT GetDemuxType(j_pl_demux_t &t);		
	virtual J_PL_RESULT ReadBlock(char *OUT_buf,int &OUT_len);
	virtual J_PL_RESULT Control(int type,va_list args);
	virtual J_PL_RESULT RequestData(int interval);
	virtual int GuessBufferSize();

private:
	J_PL_RESULT RequestServer(j_pl_work_type type);
	J_PL_RESULT ReadHeader(j_pl_demux_t &t);

	//realtime only
	J_PL_RESULT ReadBlockReal(char *OUT_buf,int &OUT_len);		

	//vod only
	J_PL_RESULT ReadBlockFile(char *OUT_buf,int &OUT_len);			

	virtual void SetAccessType(int &ID);

private:
	J_PlSocket *m_netWork;

	//vod only
	JOSP_RequestData m_RequstData;
	j_pl_mtime_t m_llRequesttime;				//¼ÇÂ¼Ê±¼ä

	bool m_bNeedtime;
	bool m_bFirst;
	bool m_nNeedRequst;
	bool m_bEnd;
	bool m_bForward;

};
