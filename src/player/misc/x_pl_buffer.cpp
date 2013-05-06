#include "x_pl_buffer.h"
#include "x_pl_buffer_fifo.h"

J_PlBuffer *J_PlBuffer::CreateInstance(buffer_type_e t,int size_buffer)
{
	J_PlBuffer *pInstance = NULL;
	switch(t)
	{
	case BUFFER_FIFO: pInstance = new CXPlBufferFIFO(size_buffer); 
		break;
	}
	return pInstance;
}

J_PlBuffer::~J_PlBuffer(void)
{
}

void J_PlBuffer::ReleaseInstance(J_PlBuffer **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;
	switch((*pInstance)->m_bufferID)
	{
	case BUFFER_FIFO: 
		delete (CXPlBufferFIFO*)(*pInstance);
		*pInstance = NULL;
		break;
	}
}

J_PlBuffer::J_PlBuffer(int size)
{
	
}