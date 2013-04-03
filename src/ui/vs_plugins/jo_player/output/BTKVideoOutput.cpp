#include "..\include\BTKVideoOutput.h"
#include "..\include\BTKError.h"
#include "BTKVoutDDraw.h"

BTKVideoOutput::BTKVideoOutput(btk_video_out_t &t)
{
	m_parm = t;
}

BTKVideoOutput::~BTKVideoOutput(void)
{
}


BTKVideoOutput *BTKVideoOutput::CreateInstance(btk_video_out_t &t)
{
	BTKVideoOutput *pInstance = NULL;
		switch(t.VoutDev)
	{
	case BTK_DDRAW: pInstance = new BTKVoutDDraw(t); break;
	}

	return pInstance;

}

void BTKVideoOutput::ReleaseInstance(BTKVideoOutput **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;

	switch((*pInstance)->m_parm.VoutDev)
	{
	case BTK_DDRAW: 
		delete (BTKVoutDDraw*)(*pInstance);
		*pInstance = NULL;
		break;
	}

}

BTK_RESULT BTKVideoOutput::GetVoutParm(btk_video_out_t &OUT_t)
{
	OUT_t = m_parm;
	return BTK_NO_ERROR;
}