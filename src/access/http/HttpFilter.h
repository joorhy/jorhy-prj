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
		virtual int Parser(J_AsioDataBase &asioData);
		const char *GetResourceType();
		virtual int Convert(const j_char_t *pInputData, J_StreamHeader &streamHeader, j_char_t *pOutputData, j_int32_t &nOutLen);
		virtual int Complete(J_AsioDataBase &asioData);

	private:
		J_MuxFilter *m_muxFilter;
		j_char_t m_read_buff[1024];
		j_int32_t m_read_len;
};

FILTER_BEGIN_MAKER(http)
	FILTER_ENTER_MAKER("http", CHttpFilter::Maker)
FILTER_END_MAKER()

#endif //~__HTTP_H_
