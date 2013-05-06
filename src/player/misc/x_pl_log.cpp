
#include "x_pl_log.h"
#include <ctime>
#include <stdarg.h>
#include <iostream>
#include <fstream>
#include <Windows.h>

J_PlLog *J_PlLog::m_pInstance = NULL;

J_PlLog::J_PlLog():m_pFile(NULL)
{
	memset (m_pFileName, 0, sizeof(m_pFileName));
	GetStrTime(m_pFileName);
	strcat(m_pFileName, ".log");
	m_pFile		= NULL;				
	m_hConsloe	= NULL;
	OpenFile();
#ifdef _DEBUG
	InitConsole();
#endif
}

J_PlLog::~J_PlLog()
{
	CloseFile();
#ifdef _DEBUG
	UnInitConsole();
#endif
}

J_PlLog *J_PlLog::Instance()
{
	if(NULL == m_pInstance)
	{
		m_pInstance = new J_PlLog();
	}
	return m_pInstance;
}

int J_PlLog::OpenFile()
{
	if(m_pFile == NULL)
	m_pFile = new std::ofstream(m_pFileName,std::ios::trunc | std::ios::out);
	
	return 1;
}

void J_PlLog::CloseFile()
{
	if(m_pFile)
	{
		((std::ofstream*)m_pFile)->close();
		m_pFile = NULL;
	}
}

int J_PlLog::WriteLog(int type,const char *format,...)  
{
	m_lock.Lock();
	va_list args;
	unsigned long lgsize;
	char nowtime[32] = {0};
	
	if(!m_pFile)
	{
		m_lock.Unlock();
		return 1;
	}
#ifdef _DEBUG
	if(!m_hConsloe)
	{
		m_lock.Unlock();
		return 1;
	}
#endif

	va_start(args, format);
	int len = vsnprintf (NULL, 0, format, args);
	char *str = new char[len+1];
	vsprintf (str, format, args);
	str[len] = '\0';
	GetStrTime(nowtime);
	switch(type)
	{
	case J_PL_LOG_INFO:	
#ifdef _DEBUG
		printf("[%s]Info:%s",nowtime,str);
#endif
		(*(std::ofstream*)m_pFile)<<"["<<nowtime<<"]"<<"Info:"<<str;
		((std::ofstream*)m_pFile)->flush();
		break;
	case J_PL_LOG_ERR:
#ifdef _DEBUG
		SetConsoleTextAttribute(m_hConsloe,FOREGROUND_INTENSITY|FOREGROUND_RED);
		printf("[%s]Error:%s",nowtime,str);
#endif
		(*(std::ofstream*)m_pFile)<<"["<<nowtime<<"]"<<"Error:"<<str;
		((std::ofstream*)m_pFile)->flush();
		break;
	case J_PL_LOG_WARN:	
#ifdef _DEBUG
		SetConsoleTextAttribute(m_hConsloe,FOREGROUND_INTENSITY|FOREGROUND_BLUE);
		printf("[%s]Warning:%s",nowtime,str);
#endif
		(*(std::ofstream*)m_pFile)<<"["<<nowtime<<"]"<<"Warning:"<<str;
		((std::ofstream*)m_pFile)->flush();
		break;
	case J_PL_LOG_DBG:
#ifdef _DEBUG
		SetConsoleTextAttribute(m_hConsloe,FOREGROUND_INTENSITY|FOREGROUND_GREEN);
		printf("[%s]Debug:%s",nowtime,str);
#endif
		(*(std::ofstream*)m_pFile)<<"["<<nowtime<<"]"<<"Debug:"<<str;
		((std::ofstream*)m_pFile)->flush();
		break;
	}
#ifdef _DEBUG
	SetConsoleTextAttribute(m_hConsloe,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
#endif
	delete str;
	m_lock.Unlock();
	return 1;
}

int J_PlLog::GetStrTime(char *OUT_time)
{
	if(!OUT_time)
		return FALSE;

	time_t curtime = time(NULL);
	tm *ascCurtime;
	ascCurtime = localtime(&curtime); 
	sprintf(OUT_time,"%04d%02d%02d%02d%02d%02d",
			ascCurtime->tm_year+1990,
			ascCurtime->tm_mon+1,
			ascCurtime->tm_mday,
			ascCurtime->tm_hour,
			ascCurtime->tm_min,
			ascCurtime->tm_sec);
	return TRUE;
}


void J_PlLog::InitConsole()
{
	AllocConsole();
	SetConsoleTitle("BTKPlayer-Debug");
	freopen("CONOUT$", "w", stderr);
	freopen("CONOUT$", "w", stdout);
	m_hConsloe = GetStdHandle(STD_OUTPUT_HANDLE);

}

void J_PlLog::UnInitConsole()
{
	FreeConsole();
	m_hConsloe = NULL;
}