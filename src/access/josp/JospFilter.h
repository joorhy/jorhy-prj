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
		virtual int Parser(J_AsioDataBase &asioData);
		const char *GetResourceType();
		virtual int Convert(const j_char_t *pInputData, J_StreamHeader &streamHeader, j_char_t *pOutputData, j_int32_t &nOutLen);
		virtual int Complete(J_AsioDataBase &asioData);
		
	private:
		enum
		{
			J_JOSP_HEAD = 1,
			J_JOSP_DATA
		};
		J_MuxFilter *m_muxFilter;
		j_int32_t m_nRetLen;
		j_char_t *m_pRetBuff;
		j_int32_t m_state;
};

FILTER_BEGIN_MAKER(http)
	FILTER_ENTER_MAKER("josp", CJospFilter::Maker)
FILTER_END_MAKER()

#endif //~__JOSP_H_
