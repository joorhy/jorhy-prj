#pragma once
#include "btkbase.h"
#include "BTKCommon.h"
#include "BTKThread.h"

class BTKVariable : public BTKBase
{
public:
	BTKVariable(int type);				//var_type_e
	BTKVariable(int type,void *OUT_ptr);
	~BTKVariable(void);
	BTK_RESULT GetVariable(void *OUT_ptr);
	BTK_RESULT SetVariable(void *IN_ptr);		
	void ZeroVariable();

	BTKVariable &operator++();			//ǰ׺
	BTKVariable &operator--();			//ǰ׺

private:
	int				m_varID;				//variable ID
	void			*m_data;
	int				m_dataLen;				
	BTKMutexLock	m_lock;
};
