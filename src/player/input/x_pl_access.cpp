#include "x_pl_access.h"
#include "x_pl_access_josp.h"

J_PlAccess::J_PlAccess(j_pl_cfg_t &cfg)
{
	m_cfg = cfg;
	m_bUsable = true;
}

J_PlAccess::~J_PlAccess(void)
{
}

J_PlAccess *J_PlAccess::CreateInstance(j_pl_cfg_t &cfg)
{
	J_PlAccess *pInstance = NULL;
	switch(cfg.i_protocol)
	{
	case PROTOCOL_RYSP: 
		pInstance = new CXPlJospAccess(cfg); 
		if(!pInstance->m_bUsable)
		{
			delete pInstance;
			pInstance = NULL;
		}
		break;
	}
	if(pInstance)
	{
		pInstance->SetAccessType(pInstance->m_accessID);
	}
	return pInstance;
}

void J_PlAccess::ReleaseInstance(J_PlAccess **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;
	switch((*pInstance)->m_accessID)
	{
	case PROTOCOL_RYSP: 
		delete (CXPlJospAccess*)(*pInstance);
		*pInstance = NULL;
		break;
	}
}