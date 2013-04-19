
#include "..\..\include\BTKLog.h"
#include <ctime>
#include <stdarg.h>
#include <iostream>
#include <fstream>
#include <Windows.h>

BTKLog *BTKLog::m_pInstance = NULL;

BTKLog::BTKLog():m_pFile(NULL)
{
	m_pFileName = "BTKPlayer-LoggFile.txt";
	m_pFile		= NULL;				
	m_hConsloe	= NULL;
	OpenFile();
#ifdef _DEBUG
	InitConsole();
#endif
}

BTKLog::~BTKLog()
{
	CloseFile();
#ifdef _DEBUG
	UnInitConsole();
#endif
}

BTKLog *BTKLog::Instance()
{
	if(NULL == m_pInstance)
	{
		m_pInstance = new BTKLog();
	}
	return m_pInstance;
}

int BTKLog::OpenFile()
{
	if(m_pFile == NULL)
	m_pFile = new std::ofstream(m_pFileName,std::ios::trunc | std::ios::out);
	
	return 1;
}

void BTKLog::CloseFile()
{
	if(m_pFile)
	{
		((std::ofstream*)m_pFile)->close();
		m_pFile = NULL;
	}
}

int BTKLog::WriteLog(int type,const char *format,...)  
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
	case BTK_LOG_INFO:	
#ifdef _DEBUG
		printf("[%s]Info:%s",nowtime,str);
#endif
		(*(std::ofstream*)m_pFile)<<"["<<nowtime<<"]"<<"Info:"<<str;
		((std::ofstream*)m_pFile)->flush();
		break;
	case BTK_LOG_ERR:
#ifdef _DEBUG
		SetConsoleTextAttribute(m_hConsloe,FOREGROUND_INTENSITY|FOREGROUND_RED);
		printf("[%s]Error:%s",nowtime,str);
#endif
		(*(std::ofstream*)m_pFile)<<"["<<nowtime<<"]"<<"Error:"<<str;
		((std::ofstream*)m_pFile)->flush();
		break;
	case BTK_LOG_WARN:	
#ifdef _DEBUG
		SetConsoleTextAttribute(m_hConsloe,FOREGROUND_INTENSITY|FOREGROUND_BLUE);
		printf("[%s]Warning:%s",nowtime,str);
#endif
		(*(std::ofstream*)m_pFile)<<"["<<nowtime<<"]"<<"Warning:"<<str;
		((std::ofstream*)m_pFile)->flush();
		break;
	case BTK_LOG_DBG:
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

int BTKLog::GetStrTime(char *OUT_time)
{
	if(!OUT_time)
		return FALSE;

	time_t curtime = time(NULL);
	tm *ascCurtime;
	ascCurtime = localtime(&curtime); 
	sprintf(OUT_time,"%d-%d-%d %d:%d:%d",
			ascCurtime->tm_year+1990,
			ascCurtime->tm_mon+1,
			ascCurtime->tm_mday,
			ascCurtime->tm_hour,
			ascCurtime->tm_min,
			ascCurtime->tm_sec
			);
	return TRUE;
}


void BTKLog::InitConsole()
{
	AllocConsole();
	SetConsoleTitle("BTKPlayer-Debug");
	freopen("CONOUT$", "w", stderr);
	freopen("CONOUT$", "w", stdout);
	m_hConsloe = GetStdHandle(STD_OUTPUT_HANDLE);

}

void BTKLog::UnInitConsole()
{
	FreeConsole();
	m_hConsloe = NULL;
}