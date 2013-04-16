
#include "stdafx.h"
#include "runner_log.h"
#include <ctime>
#include <iostream>

namespace e_log
{
CLog *CLog::m_pInstance = NULL;

CLog::CLog():m_pFile(NULL)
{
	m_pStrtime = new char[512];
	m_pFileName = "..\\plugins\\RunningLog.txt";
	CreateFile();
}

CLog::~CLog()
{
	if(m_pFile)
	{
		m_pFile->close();
		m_pFile = NULL;
	}
	delete m_pStrtime;
}

CLog *CLog::Instance()
{
	if(NULL == m_pInstance)
	{
		m_pInstance = new CLog();
	}
	return m_pInstance;
}

int CLog::CreateFile()
{
	if(m_pFile == NULL)
	m_pFile = new std::ofstream(m_pFileName,std::ios::trunc | std::ios::out);
	
	return 1;
}

int CLog::WriteLog(const char *info)  
{
	*m_pFile<<GetStrTime()<<": "<<info<<std::endl;
	return 1;
}

char *CLog::GetStrTime()const
{
	memset(m_pStrtime,0,512);
	time_t curtime = time(NULL);
	tm *ascCurtime;
	ascCurtime = localtime(&curtime); 
	sprintf(m_pStrtime,"%d-%d-%d %d:%d:%d",
			ascCurtime->tm_year+1990,
			ascCurtime->tm_mon+1,
			ascCurtime->tm_mday,
			ascCurtime->tm_hour,
			ascCurtime->tm_min,
			ascCurtime->tm_sec
			);
	return m_pStrtime;
}

}

