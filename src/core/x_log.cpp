#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>

#include "x_log.h"
#include "x_time.h"


namespace J_OS
{

CLog* CLog::m_pInstance = NULL;

CLog::CLog()
: m_pFile(NULL)
{
	/*CTime curTime;
	char fileName[128] = {0};
	sprintf(fileName, "%s.log", curTime.GetLocalTime().c_str());

	m_pFile = (void *)fopen(fileName, "wb+");*/
	CreateFile();
}

CLog::~CLog()
{
	if (m_pFile)
	{
		fclose((FILE *)m_pFile);
		m_pFile = NULL;
	}
}

CLog* CLog::Instance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CLog();
	}

	return m_pInstance;
}

int CLog::WriteLogInfo(const char *format, ...)
{
	m_locker._Lock();

	static char dataBuff[1024] = {0};
	int nArgLen = 0;

	va_list arg_ptr;
	va_start(arg_ptr, format);
	nArgLen = vsprintf(dataBuff, format, arg_ptr);
	va_end(arg_ptr);

	std::string strLocalTime = CTime::Instance()->GetLocalTime();
	fwrite(strLocalTime.c_str(), 1, strLocalTime.length(), (FILE *)m_pFile);
	fwrite(" : ", 1, 3, (FILE *)m_pFile);
	fwrite(dataBuff, 1, nArgLen, (FILE *)m_pFile);
	fwrite("\r\n", 1, 2, (FILE *)m_pFile);

	fflush((FILE *)m_pFile);

	printf("%s : %s\n", strLocalTime.c_str(), dataBuff);
	m_locker._Unlock();

	return J_OK;
}

int CLog::WriteLogError(const char *format, ...)
{
	m_locker._Lock();
	char errBuff[256] = {0};
	sprintf(errBuff, "(%s, errno = %d)", strerror(errno), errno);

	static char dataBuff[1024] = {0};
	int nArgLen = 0;

	va_list arg_ptr;
	va_start(arg_ptr, format);
	nArgLen = vsprintf(dataBuff, format, arg_ptr);
	va_end(arg_ptr);

	std::string strLocalTime = CTime::Instance()->GetLocalTime();
	fwrite(strLocalTime.c_str(), 1, strLocalTime.length(), (FILE *)m_pFile);
	fwrite(" : ", 1, 3, (FILE *)m_pFile);
	fwrite(dataBuff, 1, nArgLen, (FILE *)m_pFile);
	fwrite(errBuff, 1, strlen(errBuff), (FILE *)m_pFile);
	fwrite("\r\n", 1, 2, (FILE *)m_pFile);

	fflush((FILE *)m_pFile);

	printf("%s : %s%s\n", strLocalTime.c_str(), dataBuff, errBuff);
	m_locker._Unlock();

	return J_OK;
}

int CLog::CreateFile()
{
	char vodDir[512] = {0};
	sprintf(vodDir, "%s/log", get_current_dir_name());

	char fileName[256] = {0};
	sprintf(fileName, "%s/%s.log", vodDir, CTime::Instance()->GetLocalTime().c_str());

	if (access(vodDir, F_OK) != 0)
	{
		if (mkdir(vodDir, S_IRWXU | S_IRWXG | S_IRWXO) < 0)
		{
			J_OS::LOGERROR("CLog::CreateFile mkdir error");
			return J_FILE_ERROR;
		}
	}
	m_pFile = fopen(fileName, "wb+");

	return J_OK;
}

}
