#include "x_pl_variable.h"
#include "x_pl_error.h"
#include "x_pl_data_def.h"

#define DEFAULT_TYPE_LEN sizeof(long long) 
J_PlVariable::J_PlVariable(int type)
{
	m_varID = type;
	m_data = new char[DEFAULT_TYPE_LEN];


}

J_PlVariable::J_PlVariable(int type,void *IN_ptr)
{
	m_varID = type;
	m_data = new char[DEFAULT_TYPE_LEN];

	SetVariable(IN_ptr);
}

J_PlVariable::~J_PlVariable(void)
{
	m_lock.Lock();
	delete m_data;
	m_lock.Unlock();
}

J_PL_RESULT J_PlVariable::GetVariable(void *OUT_ptr)
{
	m_lock.Lock();
	if(!m_data)
	{
		m_lock.Unlock();
		return J_PL_ERROR_VARIABLE;
	}

	switch(m_varID)
	{
	case J_PL_VAR_BOOL:
	case J_PL_VAR_INT:
	case J_PL_VAR_STRING:
	case J_PL_VAR_INT64:
		memcpy(OUT_ptr,m_data,m_dataLen);	
		break;

	default:
		m_lock.Unlock();
		return J_PL_ERROR_VARIABLE;
	}

	m_lock.Unlock();
	return J_PL_NO_ERROR;
}

J_PL_RESULT J_PlVariable::SetVariable(void *IN_ptr)
{
	m_lock.Lock();
	if(!m_data)
	{
		m_lock.Unlock();
		return J_PL_ERROR_VARIABLE;
	}

	switch(m_varID)
	{
	case J_PL_VAR_BOOL:
		m_dataLen = sizeof(bool);
		memcpy(m_data,IN_ptr,m_dataLen);	
		break;

	case J_PL_VAR_INT:	
		m_dataLen = sizeof(int);
		memcpy(m_data,IN_ptr,m_dataLen);	
		break;

	case J_PL_VAR_STRING:
		{
			int m_dataLen = strlen((const char *)IN_ptr);
			if(m_dataLen >= DEFAULT_TYPE_LEN)
			{
				delete m_data;
				m_data = NULL;
				m_data = new char[m_dataLen+1];
			}
			memcpy(m_data,IN_ptr,m_dataLen);
			*((char*)m_data + m_dataLen) = '\0';
			break;
		}
	case J_PL_VAR_INT64:	
		m_dataLen = sizeof(long long);
		memcpy(m_data,IN_ptr,m_dataLen);	
		break;

	default:
		m_lock.Unlock();
		return J_PL_ERROR_VARIABLE;
	}

	m_lock.Unlock();
	return J_PL_NO_ERROR;
}

J_PlVariable &J_PlVariable::operator ++()
{
	m_lock.Lock();
	if(m_varID == J_PL_VAR_INT)
	{
		int tmp = *(int*)(m_data);
		tmp++;
		memcpy(m_data,&tmp,m_dataLen);
	}
	else if(m_varID == J_PL_VAR_INT64)
	{
		long long tmp = *(long long*)(m_data);
		tmp++;
		memcpy(m_data,&tmp,m_dataLen);
	}

	m_lock.Unlock();
	return *this;
}


J_PlVariable &J_PlVariable::operator--()
{
	m_lock.Lock();

	if(m_varID == J_PL_VAR_INT)
	{
		int tmp = *(int*)(m_data);
		tmp--;
		memcpy(m_data,&tmp,m_dataLen);
	}
	else if(m_varID == J_PL_VAR_INT64)
	{
		long long tmp = *(long long*)(m_data);
		tmp--;
		memcpy(m_data,&tmp,m_dataLen);
	}

	m_lock.Unlock();
	return *this;
}


void J_PlVariable::ZeroVariable()
{
	m_lock.Lock();
	memset(m_data,0,m_dataLen);
	m_lock.Unlock();
}