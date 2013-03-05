#ifndef __FILTERFACTORY_H_
#define __FILTERFACTORY_H_
#include "j_includes.h"
#include "x_singleton.h"
#include "x_lock.h"

typedef int (*J_MakeFilterFun)(J_Obj *&);

class CFilterFactory : public SingletonTmpl<CFilterFactory>
{
	typedef std::map<std::string, J_MakeFilterFun> FilterRegistMap;
	typedef std::map<int, J_RequestFilter *> FilterMap;
public:
	CFilterFactory(int) {}
	~CFilterFactory() {}

protected:
    CFilterFactory() {}

public:
	///注册Filter类
	///@param[in] 	adapterType filter
	///@param[in] 	J_MakeFilterFun Filter的构造函数
	///@return 		参考x_error_type.h
	int RegisterFilter(const char *filterType, J_MakeFilterFun pFun);

	J_RequestFilter *GetFilter(int nSocket, const char *pType);
	void DelFilter(int nSocket);

private:
	FilterRegistMap m_filterRegistMap;
	FilterMap m_filterMap;
	J_OS::TLocker_t m_lock;
};

#endif //~__FILTERFACTORY_H_
