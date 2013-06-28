#ifndef __PARSERFACTORY_H_
#define __PARSERFACTORY_H_
#include "j_includes.h"
#include "x_singleton.h"
#include "x_lock.h"

typedef int (*J_MakeParserFun)(J_Obj *&);

class JO_API CParserFactory : public SingletonTmpl<CParserFactory>
{
	typedef std::map<std::string, J_MakeParserFun> ParserRegistMap;
	typedef std::map<int, J_CommandParser *> ParserMap;
public:
	CParserFactory(int) {}
	~CParserFactory() {}

protected:
    CParserFactory() {}

public:
	///注册Filter类
	///@param[in] 	parserType parser
	///@param[in] 	J_MakeParserFun Parser的构造函数
	///@return 		参考x_error_type.h
	int RegisterParser(const char *parserType, J_MakeParserFun pFun);

	J_CommandParser *GetParser(int nSocket, const char *pType);
	void DelParser(int nSocket);

private:
	ParserRegistMap m_parserRegistMap;
	ParserMap m_parserMap;
	J_OS::TLocker_t m_lock;
};

#endif //~__PARSERFACTORY_H_
