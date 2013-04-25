#include "x_pl_file.h"
#include <iostream>

J_PlFile::J_PlFile(char *file_name)
:m_pFile(NULL)
{
	if(m_pFile == NULL)
		m_pFile = new std::ofstream(file_name,std::ios::trunc | std::ios::out);
}

J_PlFile::~J_PlFile()
{
	if(m_pFile)
	{
		m_pFile->close();
		m_pFile = NULL;
	}
}

int J_PlFile::Write(const char *buf,int len)
{
	m_pFile->write(buf,len);
	return len;
}
