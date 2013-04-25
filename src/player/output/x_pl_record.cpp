#include "x_pl_record.h"
#include "x_pl_log.h"
#include "x_pl_error.h"
#include "x_pl_thread.h"
#include "x_pl_avi_struct.h"
#include <stdio.h>

CXPlRecord::CXPlRecord()
{
}

CXPlRecord::~CXPlRecord()
{
	Stop();
}

J_PL_RESULT CXPlRecord::Start(char *filename)
{
	J_PL_RESULT br;
	
	/*br = Init(filename);
	if(br != J_PL_NO_ERROR)
		return br;*/

	//j_pl_thread_t parm;
	//parm.data = this;
	//parm.priority = 0; 

	//parm.entry= CXPlRecord::Thread;
	//br = m_vThread.Create(parm);
	//if(br != J_PL_NO_ERROR)
	//	return br;

	return br;
}

J_PL_RESULT CXPlRecord::Stop()
{
	return J_PL_NO_ERROR;
}
