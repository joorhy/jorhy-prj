#pragma once
#include "x_pl_base.h"
#include "x_pl_common.h"
#include "x_pl_thread.h"

class J_PlVariable : public J_PlBase
{
public:
	J_PlVariable(int type);				//var_type_e
	J_PlVariable(int type,void *OUT_ptr);
	~J_PlVariable(void);
	J_PL_RESULT GetVariable(void *OUT_ptr);
	J_PL_RESULT SetVariable(void *IN_ptr);		
	void ZeroVariable();

	J_PlVariable &operator++();			//ǰ׺
	J_PlVariable &operator--();			//ǰ׺

private:
	int				m_varID;				//variable ID
	void			*m_data;
	int				m_dataLen;				
	J_PlMutexLock	m_lock;
};
