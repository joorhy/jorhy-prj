
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
	InitConsole();
}

BTKLog::~BTKLog()
{
	CloseFile();
	UnInitConsole();
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
	va_list args;
	unsigned long lgsize;
	char nowtime[32] = {0};
	
	if(!m_pFile || !m_hConsloe)
		return 1;

	va_start(args, format);
	int len = vsnprintf (NULL, 0, format, args);
	char *str = new char[len+1];
	vsprintf (str, format, args);
	str[len] = '\0';
	GetStrTime(nowtime);
	switch(type)
	{
	case BTK_LOG_INFO:	
		printf("[%s]Info:%s",nowtime,str);
		(*(std::ofstream*)m_pFile)<<"["<<nowtime<<"]"<<"Info:"<<str;
		((std::ofstream*)m_pFile)->flush();
		break;
	case BTK_LOG_ERR:
		SetConsoleTextAttribute(m_hConsloe,FOREGROUND_INTENSITY|FOREGROUND_RED);
		printf("[%s]Error:%s",nowtime,str);
		(*(std::ofstream*)m_pFile)<<"["<<nowtime<<"]"<<"Error:"<<str;
		((std::ofstream*)m_pFile)->flush();
		break;
	case BTK_LOG_WARN:	
		SetConsoleTextAttribute(m_hConsloe,FOREGROUND_INTENSITY|FOREGROUND_BLUE);
		printf("[%s]Warning:%s",nowtime,str);
		(*(std::ofstream*)m_pFile)<<"["<<nowtime<<"]"<<"Warning:"<<str;
		((std::ofstream*)m_pFile)->flush();
		break;
	case BTK_LOG_DBG:
		SetConsoleTextAttribute(m_hConsloe,FOREGROUND_INTENSITY|FOREGROUND_GREEN);
		printf("[%s]Debug:%s",nowtime,str);
		(*(std::ofstream*)m_pFile)<<"["<<nowtime<<"]"<<"Debug:"<<str;
		((std::ofstream*)m_pFile)->flush();
		break;
	}
	SetConsoleTextAttribute(m_hConsloe,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
	delete str;
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
	//BOOL bRet;
	//SECURITY_ATTRIBUTES sa;
	//ZeroMemory( &sa,sizeof(sa));

	//sa.nLength = sizeof(sa);
	//sa.bInheritHandle = 1;
	//sa.lpSecurityDescriptor = 0;

	//bRet = CreatePipe(&m_hRead,&m_hWrite,&sa, 0);
	//if(!bRet)
	//	return FALSE;

	//STARTUPINFO si;
	//ZeroMemory( &si, sizeof(si) );
	//si.cb			= sizeof(si) ;
	//si.dwFlags		= STARTF_USESHOWWINDOW;
	//si.wShowWindow	= SW_SHOW;
	//si.hStdInput	= m_hRead;//让等会建立的进程的标准输入来自管道的read端;

	//PROCESS_INFORMATION pi;
	//ZeroMemory( &pi, sizeof(pi) );

	//bRet = CreateProcess(NULL,"BTKPlayer-Debug.exe",NULL,NULL,
	//					TRUE,0,NULL,NULL,&si,&pi
	//					);
	//if(!bRet)
	//	return FALSE;
	//WaitForSingleObject( pi.hProcess,INFINITE);
	//m_hProcess	= pi.hProcess;
	//m_hThread	= pi.hThread;

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