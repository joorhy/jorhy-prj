#include "..\include\BTKAccess.h"
#include "BTKAccessRYSP.h"
#include "BTKAccessRTSP.h"

BTKAccess::BTKAccess(btk_cfg_t &cfg)
{
	m_cfg = cfg;
	m_bUsable = true;
}

BTKAccess::~BTKAccess(void)
{
}

BTKAccess *BTKAccess::CreateInstance(btk_cfg_t &cfg)
{
	BTKAccess *pInstance = NULL;
	switch(cfg.i_protocol)
	{
	case PROTOCOL_RYSP: 
		pInstance = new BTKAccessRYSP(cfg); 
		if(!pInstance->m_bUsable)
		{
			delete pInstance;
			pInstance = NULL;
		}
		break;
	case PROTOCOL_RTSP: 
		pInstance = new BTKAccessRTSP(cfg); 
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

void BTKAccess::ReleaseInstance(BTKAccess **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;
	switch((*pInstance)->m_accessID)
	{
	case PROTOCOL_RYSP: 
		delete (BTKAccessRYSP*)(*pInstance);
		*pInstance = NULL;
		break;
	case PROTOCOL_RTSP: 
		delete (BTKAccessRTSP*)(*pInstance);
		*pInstance = NULL;
		break;
	}
}