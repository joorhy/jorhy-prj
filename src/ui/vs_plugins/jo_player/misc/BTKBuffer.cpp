#include "..\include\BTKBuffer.h"
#include "BTKBufferFIFO.h"
#include "BTKBufferLIFO.h"
#include "BTKBufferLIST.h"

BTKBuffer *BTKBuffer::CreateInstance(buffer_type_e t,int size_buffer)
{
	BTKBuffer *pInstance = NULL;
	switch(t)
	{
	case BUFFER_FIFO: pInstance = new BTKBufferFIFO(size_buffer); break;
	case BUFFER_LIFO: pInstance = new BTKBufferLIFO(size_buffer);break;
	case BUFFER_LIST: pInstance = new BTKBufferLIST(size_buffer);break;
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

	case BUFFER_LIFO:
		delete (BTKBufferLIFO*)(*pInstance);
		*pInstance = NULL;
		break;

	case BUFFER_LIST:
		delete (BTKBufferLIST*)(*pInstance);
		*pInstance = NULL;
		break;
	}
}

BTKBuffer::BTKBuffer(int size)
{
	
}