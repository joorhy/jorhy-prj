#include "..\include\BTKAudioOutput.h"
#include "..\include\DataDef.h"

BTKAudioOutput::BTKAudioOutput(void)
{
}

BTKAudioOutput::~BTKAudioOutput(void)
{
}

BTKAudioOutput *BTKAudioOutput::CreateInstance(int nCode)	//Ïê¼ûcodec_id_e
{
	BTKAudioOutput *pInstance = NULL;
	switch(nCode)
	{
	case CODE_AAC: 
		//pInstance = new BTKDecodeH264();
		break;
	}

	return pInstance;
}

void BTKAudioOutput::ReleaseInstance(BTKAudioOutput **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;
	switch((*pInstance)->m_aoutID)
	{
	case BTK_DSOUND:
		//delete (BTKAudioDecode*)(*pInstance);
		*pInstance = NULL;
		return;
	}
}