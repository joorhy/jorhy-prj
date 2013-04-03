#include "..\..\include\BTKFile.h"
#include <iostream>

BTKFile::BTKFile(char *file_name)
:m_pFile(NULL)
{
	if(m_pFile == NULL)
		m_pFile = new std::ofstream(file_name,std::ios::trunc | std::ios::out);
}

BTKFile::~BTKFile()
{
	if(m_pFile)
	{
		m_pFile->close();
		m_pFile = NULL;
	}
}

int BTKFile::Write(const char *buf,int len)
{
	m_pFile->write(buf,len);
	return len;
}
