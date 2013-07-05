#include "x_decoder_factory.h"
#include "x_string.h"

JO_IMPLEMENT_SINGLETON(DecoderFactory)

int CDecoderFactory::RegisterDecoder(const char *decType, J_MakeDecoderFun pFun)
{
	DecoderRegistMap::iterator it = m_decRegistMap.find(decType);
	if (it == m_decRegistMap.end())
	{
		m_decRegistMap[decType] = pFun;
		J_OS::LOGINFO("CDecoderFactory::RegisterDecoder %s Regist Sucess!!!", decType);

		return J_OK;
	}

	return J_EXIST;
}

J_Decoder *CDecoderFactory::GetDecoder(j_wnd_t hWindow, const char *pType)
{
	TLock(m_lock);
	J_Obj *protocolDecoder = NULL;
	DecoderMap::iterator it = m_decMap.find(hWindow);
	if (it == m_decMap.end())
	{
		DecoderRegistMap::iterator itDecoder = m_decRegistMap.find(pType);
		if (itDecoder == m_decRegistMap.end())
		{
			J_OS::LOGINFO("CDecoderFactory::GetDecoder Decoder not registed, decType = %s", pType);
		}
		else
		{
			itDecoder->second(protocolDecoder);
		}

		if (protocolDecoder != NULL)
			m_decMap[hWindow] = dynamic_cast<J_Decoder *>(protocolDecoder);
	}
	else
		protocolDecoder = it->second;

	TUnlock(m_lock);

	return dynamic_cast<J_Decoder *>(protocolDecoder);
}

void CDecoderFactory::DelDecoder(j_wnd_t hWindow)
{
	TLock(m_lock);
	DecoderMap::iterator it = m_decMap.find(hWindow);
	if (it != m_decMap.end())
	{
		delete it->second;
		m_decMap.erase(it);
	}
	TUnlock(m_lock);
}
