#include "x_mux_factory.h"

JO_IMPLEMENT_SINGLETON(MuxFactory)

int CMuxFactory::RegisterMux(const char *muxType, J_MakeMuxFun pFun)
{
	MuxRegistMap::iterator it = m_muxRegistMap.find(muxType);
	if (it == m_muxRegistMap.end())
	{
		m_muxRegistMap[muxType] = pFun;
		J_OS::LOGINFO("CMuxFactory::RegisterMux %s Regist Sucess!!!", muxType);

		return J_OK;
	}

	return J_EXIST;
}

J_MuxFilter *CMuxFactory::GetMux(J_Obj *pOwner, const char *pMuxType)
{
	TLock(m_lock);
	J_Obj *pMux = NULL;
	MuxMap::iterator it = m_muxMap.find(pOwner);
	if (it == m_muxMap.end())
	{
		MuxRegistMap::iterator itMux = m_muxRegistMap.find(pMuxType);
		if (itMux == m_muxRegistMap.end())
		{
			J_OS::LOGINFO("CMuxFactory::GetMux Mux not registed, filterType = %s", pMuxType);
		}
		else
		{
			itMux->second(pMux);
		}

		if (pMux != NULL)
			m_muxMap[pOwner] = dynamic_cast<J_MuxFilter *>(pMux);
	}
	else
		pMux = it->second;

	TUnlock(m_lock);
	//J_OS::LOGINFO("pMux = %x", pMux);

	return dynamic_cast<J_MuxFilter *>(pMux);
}

void CMuxFactory::DelMux(J_Obj *pOwner)
{
	TLock(m_lock);
	MuxMap::iterator it = m_muxMap.find(pOwner);
	if (it != m_muxMap.end())
	{
		delete it->second;
		m_muxMap.erase(it);
	}
	TUnlock(m_lock);
}
