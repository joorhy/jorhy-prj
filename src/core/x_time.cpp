#include "x_time.h"
#include "j_common.h"

JO_IMPLEMENT_SINGLETON(Time)

j_string_t CTime::GetLocalTime()
{
	time_t curTime;
	curTime = time(0);
	tm *pCurTime = localtime(&curTime);

	int nMilliseconds = 0;
#ifdef WIN32
	SYSTEMTIME st;  
	::GetLocalTime(&st);
	nMilliseconds = st.wMilliseconds;
#else
	struct timeval nowtimeval;
	gettimeofday(&nowtimeval,0);
	nMilliseconds = nowtimeval.tv_usec / 1000;
#endif

	j_char_t pBuff[128] = {0};
	sprintf(pBuff, "%04d%02d%02d%02d%02d%02d%03ld",
			1900+pCurTime->tm_year,
			pCurTime->tm_mon+1,
			pCurTime->tm_mday,
			pCurTime->tm_hour,
			pCurTime->tm_min,
			pCurTime->tm_sec,
			nMilliseconds);

	return j_string_t(pBuff);
}

j_uint64_t CTime::GetLocalTime(j_string_t &strTime)
{
	time_t curTime;
	curTime = time(0);
	tm *pCurTime = localtime(&curTime);

	j_int32_t nMilliseconds = 0;
	j_uint64_t nSecondsOfDay = 0;
#ifdef WIN32
	SYSTEMTIME st;  
	::GetLocalTime(&st);
	nMilliseconds = st.wMilliseconds;
	nSecondsOfDay = (st.wHour*3600 + st.wMinute*60 + st.wSecond);
#else
	struct timeval nowtimeval;
	gettimeofday(&nowtimeval,0);
	nMilliseconds = nowtimeval.tv_usec / 1000;
	nSecondsOfDay = ((uint64_t)nowtimeval.tv_sec + (uint64_t)nowtimeval.tv_usec / 1000000);
#endif

	char pBuff[128] = {0};
	sprintf(pBuff, "%04d%02d%02d%02d%02d%02d%03ld",
			1900+pCurTime->tm_year,
			pCurTime->tm_mon+1,
			pCurTime->tm_mday,
			pCurTime->tm_hour,
			pCurTime->tm_min,
			pCurTime->tm_sec,
			nMilliseconds);
	strTime = pBuff;

	return nSecondsOfDay;
}

j_uint64_t CTime::GetLocalTime(int) const
{
	j_uint64_t nMilliSecondsOfDay = 0;
#ifdef WIN32
	SYSTEMTIME st;  
	::GetLocalTime(&st);
	nMilliSecondsOfDay = time(0) * 1000 + st.wMilliseconds;
#else
	struct timeval nowtimeval;
	gettimeofday(&nowtimeval,0);
	nMilliSecondsOfDay = time(0);//((uint64_t)((time(0) * 1000) + (nowtimeval.tv_usec / 1000)));
	nMilliSecondsOfDay *= 1000;
	nMilliSecondsOfDay += (nowtimeval.tv_usec / 1000);
#endif

	return nMilliSecondsOfDay;
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

j_string_t CTime::GetDate()
{
	time_t curTime;
	curTime = time(0);
	tm *pCurTime = localtime(&curTime);
	pCurTime->tm_hour = 0;
	pCurTime->tm_min = 0;
	pCurTime->tm_sec = 0;
	char pBuff[128] = {0};
	sprintf(pBuff, "%d", mktime(pCurTime));

	return pBuff;
}

j_string_t CTime::GetDate(j_time_t nTime)
{
	time_t curTime;
	curTime = nTime;
	tm *pCurTime = localtime(&curTime);
	pCurTime->tm_hour = 0;
	pCurTime->tm_min = 0;
	pCurTime->tm_sec = 0;
	char pBuff[128] = {0};
	sprintf(pBuff, "%d", mktime(pCurTime));

	return pBuff;
}