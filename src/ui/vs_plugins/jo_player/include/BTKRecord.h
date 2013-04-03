#pragma once
#include "BTKBase.h"
#include "BTKBuffer.h"

class BTKRecord : public BTKBase
{
public:
	BTKRecord();
	~BTKRecord();

	BTK_RESULT Start(char *filename);
	BTK_RESULT Stop();

private:
	BTK_RESULT Init(char *filename);


private:
	
};