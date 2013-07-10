#include "x_render_factory.h"
#include "x_string.h"

JO_IMPLEMENT_SINGLETON(RenderFactory)

int CRenderFactory::RegisterRender(const char *rendType, J_MakeRenderFun pFun)
{
	RenderRegistMap::iterator it = m_rendRegistMap.find(rendType);
	if (it == m_rendRegistMap.end())
	{
		m_rendRegistMap[rendType] = pFun;
		J_OS::LOGINFO("CRenderFactory::RegisterRender %s Regist Sucess!!!", rendType);

		return J_OK;
	}

	return J_EXIST;
}

J_Render *CRenderFactory::GetRender(j_wnd_t hWindow, const char *pType)
{
	TLock(m_lock);
	J_Obj *protocolRender = NULL;
	RenderMap::iterator it = m_rendMap.find(hWindow);
	if (it == m_rendMap.end())
	{
		RenderRegistMap::iterator itRender = m_rendRegistMap.find(pType);
		if (itRender == m_rendRegistMap.end())
		{
			J_OS::LOGINFO("CRenderFactory::GetRender Render not registed, rendType = %s", pType);
		}
		else
		{
			itRender->second(protocolRender);
		}

		if (protocolRender != NULL)
			m_rendMap[hWindow] = dynamic_cast<J_Render *>(protocolRender);
	}
	else
		protocolRender = it->second;

	TUnlock(m_lock);

	return dynamic_cast<J_Render *>(protocolRender);
}

void CRenderFactory::DelRender(j_wnd_t hWindow)
{
	TLock(m_lock);
	RenderMap::iterator it = m_rendMap.find(hWindow);
	if (it != m_rendMap.end())
	{
		delete it->second;
		m_rendMap.erase(it);
	}
	TUnlock(m_lock);
}
