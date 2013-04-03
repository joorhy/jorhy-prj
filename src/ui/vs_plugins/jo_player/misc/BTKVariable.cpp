#include "..\include\BTKVariable.h"
#include "..\include\BTKError.h"
#include "..\include\DataDef.h"

#define DEFAULT_TYPE_LEN sizeof(long long) 
BTKVariable::BTKVariable(int type)
{
	m_varID = type;
	m_data = new char[DEFAULT_TYPE_LEN];


}

BTKVariable::BTKVariable(int type,void *IN_ptr)
{
	m_varID = type;
	m_data = new char[DEFAULT_TYPE_LEN];

	SetVariable(IN_ptr);
}

BTKVariable::~BTKVariable(void)
{
	m_lock.Lock();
	delete m_data;
	m_lock.Unlock();
}

BTK_RESULT BTKVariable::GetVariable(void *OUT_ptr)
{
	m_lock.Lock();
	if(!m_data)
	{
		m_lock.Unlock();
		return BTK_ERROR_VARIABLE;
	}

	switch(m_varID)
	{
	case BTK_VAR_BOOL:
	case BTK_VAR_INT:
	case BTK_VAR_STRING:
	case BTK_VAR_INT64:
		memcpy(OUT_ptr,m_data,m_dataLen);	
		break;

	default:
		m_lock.Unlock();
		return BTK_ERROR_VARIABLE;
	}

	m_lock.Unlock();
	return BTK_NO_ERROR;
}

BTK_RESULT BTKVariable::SetVariable(void *IN_ptr)
{
	m_lock.Lock();
	if(!m_data)
	{
		m_lock.Unlock();
		return BTK_ERROR_VARIABLE;
	}

	switch(m_varID)
	{
	case BTK_VAR_BOOL:
		m_dataLen = sizeof(bool);
		memcpy(m_data,IN_ptr,m_dataLen);	
		break;

	case BTK_VAR_INT:	
		m_dataLen = sizeof(int);
		memcpy(m_data,IN_ptr,m_dataLen);	
		break;

	case BTK_VAR_STRING:
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
	case BTK_VAR_INT64:	
		m_dataLen = sizeof(long long);
		memcpy(m_data,IN_ptr,m_dataLen);	
		break;

	default:
		m_lock.Unlock();
		return BTK_ERROR_VARIABLE;
	}

	m_lock.Unlock();
	return BTK_NO_ERROR;
}

BTKVariable &BTKVariable::operator ++()
{
	m_lock.Lock();
	if(m_varID == BTK_VAR_INT)
	{
		int tmp = *(int*)(m_data);
		tmp++;
		memcpy(m_data,&tmp,m_dataLen);
	}
	else if(m_varID == BTK_VAR_INT64)
	{
		long long tmp = *(long long*)(m_data);
		tmp++;
		memcpy(m_data,&tmp,m_dataLen);
	}

	m_lock.Unlock();
	return *this;
}


BTKVariable &BTKVariable::operator--()
{
	m_lock.Lock();

	if(m_varID == BTK_VAR_INT)
	{
		int tmp = *(int*)(m_data);
		tmp--;
		memcpy(m_data,&tmp,m_dataLen);
	}
	else if(m_varID == BTK_VAR_INT64)
	{
		long long tmp = *(long long*)(m_data);
		tmp--;
		memcpy(m_data,&tmp,m_dataLen);
	}

	m_lock.Unlock();
	return *this;
}


void BTKVariable::ZeroVariable()
{
	m_lock.Lock();
	memset(m_data,0,m_dataLen);
	m_lock.Unlock();
}