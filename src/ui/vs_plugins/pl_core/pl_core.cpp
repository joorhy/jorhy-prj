#include "StdAfx.h"
#include "pl_core.h"
#include "pl_err.h"

LONG g_poModuleRefCnt = 0; ///< 模块引用计数
static JoMakerEntry* s_firstMaker = NULL;

INT JO_LINK_MODULE_MAKERS(JoMakerEntry* makers)
{
	ASSERT(makers != NULL);
	JoMakerEntry* pEntry = makers;
	while(*(pEntry->clsid) != JO_INVALID_GUID)
		++pEntry;
	pEntry->fMaker = reinterpret_cast<JoFMaker>(s_firstMaker);
	s_firstMaker = makers;
	return PL_OK;
}

extern "C"
{

	__declspec(dllexport) JoMakerEntry* JoModuleMakerList()
	{
		return s_firstMaker;
	}

	__declspec(dllexport) LONG JoModuleRefCnt()
	{
		return g_poModuleRefCnt;
	}

} // extern "C"