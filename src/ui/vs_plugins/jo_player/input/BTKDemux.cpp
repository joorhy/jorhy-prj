#include "..\include\BTKDemux.h"
#include "BTKDemuxRYSP.h"

BTKDemux::BTKDemux(void)
{
}

BTKDemux::~BTKDemux(void)
{
}

BTKDemux *BTKDemux::CreateInstance(btk_demux_t &t)
{
	BTKDemux *pInstance = NULL;
	switch(t.media_type)
	{
	case DEMUX_RYSP: 
		pInstance = new BTKDemuxRYSP();
		pInstance->m_demuxID = t;
		break; 
	}

	return pInstance;
}

void BTKDemux::ReleaseInstance(BTKDemux **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;
	switch((*pInstance)->m_demuxID.media_type)
	{
	case DEMUX_RYSP: 
		delete (BTKDemuxRYSP*)(*pInstance); 
		*pInstance = NULL;
		break;
	}
}