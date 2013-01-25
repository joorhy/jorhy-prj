#include "x_time.h"
#include <sys/time.h>
#include <stdio.h>
#include <time.h>

std::string CTime::GetLocalTime()
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

	return std::string(pBuff);
}

uint64_t CTime::GetLocalTime(std::string &strTime)
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

uint64_t CTime::GetLocalTime(int) const
{
	struct timeval nowtimeval;
	gettimeofday(&nowtimeval, 0);

	return ((uint64_t)nowtimeval.tv_sec * 1000 + (uint64_t)nowtimeval.tv_usec / 1000);
}

std::string CTime::GetLocalTimeASC()
{
	time_t curTime;
	curTime = time(0);
	tm *pCurTime = localtime(&curTime);


	return std::string(asctime(pCurTime));
}
