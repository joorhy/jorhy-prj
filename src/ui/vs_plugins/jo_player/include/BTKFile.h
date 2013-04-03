#pragma once
#include "BTKBase.h"
#include <fstream>

class BTKFile : public BTKBase
{
public:
	BTKFile(char *file_name);
	~BTKFile();

public:
	int Write(const char *buf,int len);

private:
	std::ofstream *m_pFile;
};