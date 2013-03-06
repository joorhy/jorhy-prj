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
		virtual int Parser(int nSocket);
		const char *GetResourceType();
		virtual int Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen);
		virtual int Complete(int nSocket);
		
	private:
		int MakeHeader(char *pBuffer, uint8_t byCmd, uint16_t exLength, uint8_t byRet = 0x00);
		
	private:
		J_MuxFilter *m_muxFilter;
		int m_nRetLen;
		char *m_pRetBuff;
};

FILTER_BEGIN_MAKER(http)
	FILTER_ENTER_MAKER("josp", CJospFilter::Maker)
FILTER_END_MAKER()

#endif //~__JOSP_H_
