#include "..\include\BTKAudioDecode.h"

BTKAudioDecode::BTKAudioDecode(void)
{
}

BTKAudioDecode::~BTKAudioDecode(void)
{
}

BTKAudioDecode *BTKAudioDecode::CreateInstance(int nCode)	//Ïê¼ûcodec_id_e
{
	BTKAudioDecode *pInstance = NULL;
	switch(nCode)
	{
	case CODE_AAC: 
		//pInstance = new BTKDecodeH264();
		break;
	}

	return pInstance;
}

void BTKAudioDecode::ReleaseInstance(BTKAudioDecode **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;
	switch((*pInstance)->m_codeID)
	{
	case CODE_AAC:
		//delete (BTKAudioDecode*)(*pInstance);
		*pInstance = NULL;
		return;
	}
}