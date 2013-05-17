#ifndef __JOSP_H_
#define __JOSP_H_
#include "j_includes.h"
#include "x_module_manager_def.h"
#include "j_type.h"

class CJospFilter : public J_RequestFilter
				  , public J_VodCommandFilter
{
	public:
		CJospFilter();
		~CJospFilter();

		static int Maker(J_Obj *&pObj)
		{
			pObj = new CJospFilter();
			return J_OK;
		}

	public:
		///J_ProtocolFilter
		virtual int Parser(j_socket_t nSocket);
		const char *GetResourceType();
		virtual int Convert(const j_char_t *pInputData, J_StreamHeader &streamHeader, j_char_t *pOutputData, j_int32_t &nOutLen);
		virtual int Complete(j_socket_t nSocket);
		
	private:
		J_MuxFilter *m_muxFilter;
		int m_nRetLen;
		char *m_pRetBuff;
};

FILTER_BEGIN_MAKER(http)
	FILTER_ENTER_MAKER("josp", CJospFilter::Maker)
FILTER_END_MAKER()

#endif //~__JOSP_H_
