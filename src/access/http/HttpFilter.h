#ifndef __HTTP_H_
#define __HTTP_H_
#include "j_includes.h"
#include "x_module_manager_def.h"

class CHttpFilter : public J_RequestFilter
				  , public J_VodCommandFilter
{
	public:
		CHttpFilter();
		~CHttpFilter();

		static int Maker(J_Obj *&pObj)
		{
			pObj = new CHttpFilter();
			return J_OK;
		}

	public:
		///J_ProtocolFilter
		virtual int Parser(int nSocket);
		const char *GetResourceType();
		virtual int Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen);
		virtual int Complete(int nSocket);

	private:
		J_MuxFilter *m_muxFilter;
};

FILTER_BEGIN_MAKER(http)
	FILTER_ENTER_MAKER("http", CHttpFilter::Maker)
FILTER_END_MAKER()

#endif //~__HTTP_H_
