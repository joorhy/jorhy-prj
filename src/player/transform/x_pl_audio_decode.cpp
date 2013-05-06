#include "x_pl_audio_decode.h"

CXPlAudioDecode::CXPlAudioDecode(void)
{
}

CXPlAudioDecode::~CXPlAudioDecode(void)
{
}

CXPlAudioDecode *CXPlAudioDecode::CreateInstance(int nCode)	//Ïê¼ûcodec_id_e
{
	CXPlAudioDecode *pInstance = NULL;
	switch(nCode)
	{
	case CODE_AAC: 
		//pInstance = new CXPlDecodeH264();
		break;
	}

	return pInstance;
}

void CXPlAudioDecode::ReleaseInstance(CXPlAudioDecode **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;
	switch((*pInstance)->m_codeID)
	{
	case CODE_AAC:
		//delete (CXPlAudioDecode*)(*pInstance);
		*pInstance = NULL;
		return;
	}
}