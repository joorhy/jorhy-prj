#include "Live555ErrorToFile.h"

CLive555ErrorToFile::CLive555ErrorToFile(TaskScheduler& taskScheduler, string strErrorFile)
	: BasicUsageEnvironment(taskScheduler)
	, m_ErrFile(NULL)
{
#ifdef ERROR_TO_FILE_FLAG
	if (strErrorFile.size() > 0)
	{
		m_ErrFile = fopen(strErrorFile.c_str(), "w");
	}
#endif	
}

CLive555ErrorToFile::~CLive555ErrorToFile(void)
{
#ifdef ERROR_TO_FILE_FLAG
	if (NULL != m_ErrFile)
	{
		fclose(m_ErrFile);
		m_ErrFile = NULL;
	}
#endif
}

UsageEnvironment& CLive555ErrorToFile::operator<<(char const* str) 
{
#ifdef ERROR_TO_FILE_FLAG
	if (str == NULL) 
		str = "(NULL)"; // sanity check
	if (NULL != m_ErrFile)
		fprintf(m_ErrFile, "%s", str);
#endif	
	return *this;
}

UsageEnvironment& CLive555ErrorToFile::operator<<(int i) 
{
#ifdef ERROR_TO_FILE_FLAG
	if (NULL != m_ErrFile)
		fprintf(m_ErrFile, "%d", i);
#endif	
	return *this;
}

UsageEnvironment& CLive555ErrorToFile::operator<<(unsigned u) 
{
#ifdef ERROR_TO_FILE_FLAG
	if (NULL != m_ErrFile)
		fprintf(m_ErrFile, "%u", u);
#endif	
	return *this;
}

UsageEnvironment& CLive555ErrorToFile::operator<<(double d) 
{
#ifdef ERROR_TO_FILE_FLAG
	if (NULL != m_ErrFile)
		fprintf(m_ErrFile, "%f", d);
#endif	
	return *this;
}

UsageEnvironment& CLive555ErrorToFile::operator<<(void* p) 
{
#ifdef ERROR_TO_FILE_FLAG
	if (NULL != m_ErrFile)
		fprintf(m_ErrFile, "%p", p);
#endif	
	return *this;
}

CLive555ErrorToFile* CLive555ErrorToFile::CreateNew( TaskScheduler& taskScheduler, 
															  string strErrorFile)
{
	return new CLive555ErrorToFile(taskScheduler, strErrorFile);
}
