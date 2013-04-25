#pragma once
#include "x_pl_base.h"
#include <fstream>

class J_PlFile : public J_PlBase
{
public:
	J_PlFile(char *file_name);
	~J_PlFile();

public:
	int Write(const char *buf,int len);

private:
	std::ofstream *m_pFile;
};