#include "x_pl_audio_output.h"
#include "x_pl_data_def.h"

CXPlAudioOutput::CXPlAudioOutput(void)
{
}

CXPlAudioOutput::~CXPlAudioOutput(void)
{
}

CXPlAudioOutput *CXPlAudioOutput::CreateInstance(int nCode)	//Ïê¼ûcodec_id_e
{
	CXPlAudioOutput *pInstance = NULL;
	switch(nCode)
	{
	case CODE_AAC: 
		//pInstance = new CXPlDecodeH264();
		break;
	}

	return pInstance;
}

void CXPlAudioOutput::ReleaseInstance(CXPlAudioOutput **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;
	switch((*pInstance)->m_aoutID)
	{
	case J_PL_DSOUND:
		//delete (CXPlAudioDecode*)(*pInstance);
		*pInstance = NULL;
		return;
	}
}