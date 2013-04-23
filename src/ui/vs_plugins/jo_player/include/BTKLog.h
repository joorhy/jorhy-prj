#pragma once
#include "BTKBase.h"
#include "DataDef.h"
#include "BTKThread.h"

#define btk_Info(...)	\
		BTKLog::Instance()->WriteLog(BTK_LOG_INFO,__VA_ARGS__)
#define btk_Dbg(...)	\
		BTKLog::Instance()->WriteLog(BTK_LOG_DBG,__VA_ARGS__)
#define btk_Warn(...)	\
		BTKLog::Instance()->WriteLog(BTK_LOG_WARN,__VA_ARGS__)
#define btk_Error(...)	\
		BTKLog::Instance()->WriteLog(BTK_LOG_ERR,__VA_ARGS__)

class BTKLog : public BTKBase
{
public:
	DLL_IMPORT static BTKLog *Instance();
	DLL_IMPORT int WriteLog(int type,const char *format,...);
	int GetStrTime(char *OUT_time);
public:
	~BTKLog();

protected:
	BTKLog();

private:
	int OpenFile();
	void CloseFile();
	void InitConsole();
	void UnInitConsole();

private:
	static BTKLog *m_pInstance;
	BTKMutexLock m_lock;
	void *m_pFile;				//std::ofstream
	char m_pFileName[256];
	void *m_hConsloe;
};
