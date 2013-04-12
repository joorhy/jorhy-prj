#include "..\include\BTKBuffer.h"
#include "BTKBufferFIFO.h"

BTKBuffer *BTKBuffer::CreateInstance(buffer_type_e t,int size_buffer)
{
	BTKBuffer *pInstance = NULL;
	switch(t)
	{
	case BUFFER_FIFO: pInstance = new BTKBufferFIFO(size_buffer); break;
	}
	return pInstance;
}

BTKBuffer::~BTKBuffer(void)
{
}

void BTKBuffer::ReleaseInstance(BTKBuffer **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;
	switch((*pInstance)->m_bufferID)
	{
	case BUFFER_FIFO: 
		delete (BTKBufferFIFO*)(*pInstance);
		*pInstance = NULL;
		break;
	}
}

BTKBuffer::BTKBuffer(int size)
{
	
}