#ifndef __MUXFACTORY_H_
#define __MUXFACTORY_H_
#include "j_includes.h"
#include "x_singleton.h"
#include "x_lock.h"

typedef int (*J_MakeMuxFun)(J_Obj *&);

class JO_API CMuxFactory
{
	typedef std::map<std::string, J_MakeMuxFun> MuxRegistMap;
	typedef std::map<void *, J_MuxFilter *> MuxMap;
public:
	CMuxFactory() {}
	~CMuxFactory() {}

public:
	///注册Filter类
	///@param[in] 	muxType mux
	///@param[in] 	J_MakeMuxFun Mux的构造函数
	///@return 		参考x_error_type.h
	int RegisterMux(const char *muxType, J_MakeMuxFun pFun);

	J_MuxFilter *GetMux(void *pOwner, const char *pMuxType);
	void DelMux(void *pOwner);

private:
	MuxRegistMap m_muxRegistMap;
	MuxMap m_muxMap;
	J_OS::TLocker_t m_lock;
};

JO_DECLARE_SINGLETON(MuxFactory)

#endif //~__MUXFACTORY_H_
