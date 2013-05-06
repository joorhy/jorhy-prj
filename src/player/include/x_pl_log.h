#pragma once
#include "x_pl_base.h"
#include "x_pl_data_def.h"
#include "x_pl_thread.h"

#define j_pl_info(...)	\
		J_PlLog::Instance()->WriteLog(J_PL_LOG_INFO,__VA_ARGS__)
#define j_pl_dbg(...)	\
		J_PlLog::Instance()->WriteLog(J_PL_LOG_DBG,__VA_ARGS__)
#define j_pl_warn(...)	\
		J_PlLog::Instance()->WriteLog(J_PL_LOG_WARN,__VA_ARGS__)
#define j_pl_error(...)	\
		J_PlLog::Instance()->WriteLog(J_PL_LOG_ERR,__VA_ARGS__)

class J_PlLog : public J_PlBase
{
public:
	JO_PL_API static J_PlLog *Instance();
	JO_PL_API int WriteLog(int type,const char *format,...);
	int GetStrTime(char *OUT_time);
public:
	~J_PlLog();

protected:
	J_PlLog();

private:
	int OpenFile();
	void CloseFile();
	void InitConsole();
	void UnInitConsole();

private:
	static J_PlLog *m_pInstance;
	J_PlMutexLock m_lock;
	void *m_pFile;				//std::ofstream
	char m_pFileName[256];
	void *m_hConsloe;
};
