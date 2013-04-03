#include "..\include\BTKVideoDecode.h"
#include"BTKDecodeH264.h"

BTKVideoDecode::BTKVideoDecode(void)
{
}

BTKVideoDecode::~BTKVideoDecode(void)
{
}

BTKVideoDecode *BTKVideoDecode::CreateInstance(int nCode)
{
	BTKVideoDecode *pInstance = NULL;
	switch(nCode)
	{
	case CODE_H264: 
		pInstance = new BTKDecodeH264();
		break;
	}

	return pInstance;
}

void BTKVideoDecode::ReleaseInstance(BTKVideoDecode **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;
	switch((*pInstance)->m_codeID)
	{
	case CODE_H264:
		delete (BTKDecodeH264*)(*pInstance);
		*pInstance = NULL;
		return;
	}
}
