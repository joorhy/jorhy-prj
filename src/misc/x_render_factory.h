#ifndef __X_RENDER_FACTORY_H_
#define __X_RENDER_FACTORY_H_
#include "j_includes.h"
#include "x_singleton.h"
#include "x_lock.h"

typedef int (*J_MakeRenderFun)(J_Obj *&);

class JO_API CRenderFactory
{
	typedef std::map<j_string_t, J_MakeRenderFun> RenderRegistMap;
	typedef std::map<j_wnd_t, J_Render*> RenderMap;
public:
	CRenderFactory() {}
	~CRenderFactory() {}

public:
	///注册Render类
	///@param[in] 	rendType Render
	///@param[in] 	J_MakeRenderFun Render的构造函数
	///@return 		参考x_error_type.h
	int RegisterRender(const char *rendType, J_MakeRenderFun pFun);

	J_Render *GetRender(j_wnd_t hWindow, const char *pType);
	void DelRender(j_wnd_t hWindow);

private:
	RenderRegistMap m_rendRegistMap;
	RenderMap m_rendMap;
	J_OS::TLocker_t m_lock;
};
JO_DECLARE_SINGLETON(RenderFactory)
#endif //~__X_RENDER_FACTORY_H_