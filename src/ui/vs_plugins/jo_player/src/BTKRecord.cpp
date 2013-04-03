#include "..\include\BTKRecord.h"
#include "..\include\BTKLog.h"
#include "..\include\BTKError.h"
#include "..\include\BTKThread.h"
#include "AVIStruct.h"
#include <stdio.h>

BTKRecord::BTKRecord()
{
}

BTKRecord::~BTKRecord()
{
	Stop();
}

BTK_RESULT BTKRecord::Start(char *filename)
{
	BTK_RESULT br;
	
	/*br = Init(filename);
	if(br != BTK_NO_ERROR)
		return br;*/

	//btk_thread_t parm;
	//parm.data = this;
	//parm.priority = 0; 

	//parm.entry= BTKRecord::Thread;
	//br = m_vThread.Create(parm);
	//if(br != BTK_NO_ERROR)
	//	return br;

	return br;
}

BTK_RESULT BTKRecord::Stop()
{
	return BTK_NO_ERROR;
}
