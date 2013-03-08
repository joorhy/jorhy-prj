#include "x_time.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

j_string_t CTime::GetLocalTime()
{
	time_t curTime;
	curTime = time(0);
	tm *pCurTime = localtime(&curTime);

	struct timeval nowtimeval;
	gettimeofday(&nowtimeval,0);

	j_char_t pBuff[128] = {0};
	sprintf(pBuff, "%04d%02d%02d%02d%02d%02d%03ld",
			1900+pCurTime->tm_year,
			pCurTime->tm_mon+1,
			pCurTime->tm_mday,
			pCurTime->tm_hour,
			pCurTime->tm_min,
			pCurTime->tm_sec,
			nowtimeval.tv_usec / 1000);

	return j_string_t(pBuff);
}

j_uint64_t CTime::GetLocalTime(j_string_t &strTime)
{
	time_t curTime;
	curTime = time(0);
	tm *pCurTime = localtime(&curTime);

	struct timeval nowtimeval;
	gettimeofday(&nowtimeval,0);

	char pBuff[128] = {0};
	sprintf(pBuff, "%04d%02d%02d%02d%02d%02d%03ld",
			1900+pCurTime->tm_year,
			pCurTime->tm_mon+1,
			pCurTime->tm_mday,
			pCurTime->tm_hour,
			pCurTime->tm_min,
			pCurTime->tm_sec,
			nowtimeval.tv_usec / 1000);
	strTime = pBuff;

	return ((uint64_t)nowtimeval.tv_sec + (uint64_t)nowtimeval.tv_usec / 1000000);
}

j_uint64_t CTime::GetLocalTime(int) const
{
	struct timeval nowtimeval;
	gettimeofday(&nowtimeval, 0);

	return ((uint64_t)nowtimeval.tv_sec * 1000 + (uint64_t)nowtimeval.tv_usec / 1000);
}

j_string_t CTime::GetLocalTimeASC()
{
	time_t curTime;
	curTime = time(0);
	tm *pCurTime = localtime(&curTime);


	return j_string_t(asctime(pCurTime));
}

j_time_t CTime::ConvertToTime_t(const j_char_t *pLogTime)
{
	j_string_t str(pLogTime);
	struct tm logTime;
	logTime.tm_year = atoi(str.substr(0, 4).c_str()) - 1900;
	logTime.tm_mon = atoi(str.substr(4, 2).c_str()) - 1;
	logTime.tm_mday = atoi(str.substr(6, 2).c_str());
	logTime.tm_hour = atoi(str.substr(8, 2).c_str());
	logTime.tm_min = atoi(str.substr(10, 2).c_str());
	logTime.tm_sec = atoi(str.substr(12, 2).c_str());
	
	return mktime(&logTime);
}
