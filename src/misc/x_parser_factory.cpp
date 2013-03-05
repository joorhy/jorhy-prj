#include "x_parser_factory.h"
#include "x_string.h"

int CParserFactory::RegisterParser(const char *parserType, J_MakeParserFun pFun)
{
	ParserRegistMap::iterator it = m_parserRegistMap.find(parserType);
	if (it == m_parserRegistMap.end())
	{
		m_parserRegistMap[parserType] = pFun;
		J_OS::LOGINFO("CParserFactory::CParserFactory %s Regist Sucess!!!", parserType);

		return J_OK;
	}

	return J_EXIST;
}

J_CommandParser *CParserFactory::GetParser(int nSocket, const char *pType)
{
	TLock(m_lock);
	J_Obj *commandParser = NULL;
	ParserMap::iterator it = m_parserMap.find(nSocket);
	if (it == m_parserMap.end())
	{
		ParserRegistMap::iterator itParser = m_parserRegistMap.find(pType);
		if (itParser == m_parserRegistMap.end())
		{
			J_OS::LOGINFO("CParserFactory::GetParser Parser not registed, parserType = %s", pType);
		}
		else
		{
			itParser->second(commandParser);
		}

		if (commandParser != NULL)
			m_parserMap[nSocket] = dynamic_cast<J_CommandParser *>(commandParser);
	}
	else
		commandParser = it->second;

	TUnlock(m_lock);

	return dynamic_cast<J_CommandParser *>(commandParser);
}

void CParserFactory::DelParser(int nSocket)
{
	TLock(m_lock);
	ParserMap::iterator it = m_parserMap.find(nSocket);
	if (it != m_parserMap.end())
	{
		delete it->second;
		m_parserMap.erase(it);
	}
	TUnlock(m_lock);
}
