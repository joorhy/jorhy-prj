#include "x_pl_demux.h"
#include "x_pl_demux_josp.h"

J_PlDemux::J_PlDemux(void)
{
}

J_PlDemux::~J_PlDemux(void)
{
}

J_PlDemux *J_PlDemux::CreateInstance(j_pl_demux_t &t)
{
	J_PlDemux *pInstance = NULL;
	switch(t.media_type)
	{
	case DEMUX_RYSP: 
		pInstance = new CXPlJospDemux();
		pInstance->m_demuxID = t;
		break; 
	}

	return pInstance;
}

void J_PlDemux::ReleaseInstance(J_PlDemux **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;
	switch((*pInstance)->m_demuxID.media_type)
	{
	case DEMUX_RYSP: 
		delete (CXPlJospDemux*)(*pInstance); 
		*pInstance = NULL;
		break;
	}
}