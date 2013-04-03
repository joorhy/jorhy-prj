#pragma once
#include <fstream>

namespace e_log
{
#define WRTLOG CLog::Instance()->WriteLog

class CLog
{
public:
	static CLog *Instance();
	int WriteLog(const char *info);
	char *GetStrTime()const;
public:
	~CLog();

protected:
	CLog();

private:
	int CreateFile();

private:
	static CLog *m_pInstance;
	std::ofstream *m_pFile;
	char *m_pFileName;
	char *m_pStrtime;
};

}