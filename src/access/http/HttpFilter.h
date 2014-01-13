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
		virtual j_result_t Parser(J_AsioDataBase &asioData);
		const j_char_t *GetResourceType();
		virtual j_result_t Convert(const j_char_t *pInputData, J_StreamHeader &streamHeader, j_char_t *pOutputData, j_int32_t &nOutLen);
		virtual j_result_t Complete(J_AsioDataBase &asioData);

	private:
		J_MuxFilter *m_muxFilter;
		j_char_t m_read_buff[1024];
		j_int32_t m_read_len;
};

#endif //~__HTTP_H_
