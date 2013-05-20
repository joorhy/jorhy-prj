#ifndef __X_HTTP_H_
#define __X_HTTP_H_
#include "j_common.h"

enum X_HTTP_TYPE
{
	x_http_type_get = 0,
	x_http_type_options,
	x_http_type_head,
	x_http_type_post,
	x_http_type_put,
	x_http_type_delete,
	x_http_type_trace,
	x_http_type_connect,
	x_http_type_propfind,
	x_http_type_proppatch,
	x_http_type_mkcol,
	x_http_type_copy,
	x_http_type_move,
	x_http_type_lock,
	x_http_type_unlock
};

class CXHttp
{
public:
	CXHttp();
	~CXHttp();

public:
	j_result_t SetUri(j_char_t *pUri);
	j_result_t SetType(j_int32_t nType);
	j_result_t SetBody(j_char_t *pBody, j_int32_t nLen);
	j_result_t Prepare();
	j_result_t Process();
	j_int32_t GetStatusCode();
	j_char_t *GetBody();

private:
	j_int32_t m_nType;
	j_char_t m_pAddr[16];
	j_int32_t m_nPort;
	j_char_t m_pUri[1024];
	j_char_t *m_pBody;
	j_int32_t m_nBodyLen;
	j_char_t *m_pMessage;
	j_int32_t m_nMessageLen;
	j_char_t *m_pResponse;
	j_int32_t m_nRespHeadLen;
	j_int32_t m_pRespBodyLen;
};

#endif //~__X_HTTP_H_