#include "x_http.h"
#include "x_socket.h"

#define X_HTTP_BODY_LEN	(1024*7)
#define X_HTTP_MESSAGE_LEN	(1024*8)

const char *x_http_type_str[] = 
{"GET", "", "", "POST", "", "", "", "", "", "", "", "", "", "", ""};
const char *x_http_end_tag = "\r\n\r\n";

CXHttp::CXHttp()
{
	m_pBody = new char[X_HTTP_BODY_LEN];
	m_pMessage = new char[X_HTTP_MESSAGE_LEN];
	m_pResponse = new char[X_HTTP_MESSAGE_LEN];
}

CXHttp::~CXHttp()
{
	delete m_pBody;
	delete m_pMessage;
	delete m_pResponse;
}

j_result_t CXHttp::SetUri(j_char_t *pUri)
{
	memset(m_pAddr, 0, sizeof(m_pAddr));
	m_nPort = 80;
	memset(m_pUri, 0, sizeof(m_pUri));
	char *p = strstr(pUri, "http://");
	if (p != NULL)
	{
		char *p2 = strstr(p, ":");
		char *p3 = NULL;
		if (p2 != NULL)
		{
			memcpy(m_pAddr, p, p2 - p);
			p3 = strstr(p2 + 1, "/");
			m_nPort = atoi(p2 + 1);
		}
		else
		{
			p3 = strstr(p, "/");
		}
		strcpy(m_pUri, p3);
	}

	return J_OK;
}

j_result_t CXHttp::SetType(j_int32_t nType)
{
	m_nType = nType;

	return J_OK;
}

j_result_t CXHttp::SetBody(j_char_t *pBody, j_int32_t nLen)
{
	memset(m_pBody, 0, X_HTTP_BODY_LEN);
	m_nBodyLen = nLen;
	assert(nLen < X_HTTP_BODY_LEN);
	if (nLen < X_HTTP_BODY_LEN)
		memcpy(m_pBody, pBody, nLen);

	return J_OK;
}

j_result_t CXHttp::Prepare()
{
	memset(m_pMessage, 0, X_HTTP_MESSAGE_LEN);
	switch (m_nType)
	{
	case x_http_type_get:
		sprintf(m_pMessage, "%s %s HTTP/1.1\r\nUser-Agent: JoAgent/3.0\r\nHost: %s:%d\r\n\r\n", 
			x_http_type_str[m_nType], m_pUri, m_pAddr, m_nPort);
		m_nMessageLen = strlen(m_pMessage);
		break;
	case x_http_type_post:
		sprintf(m_pMessage, "%s %s HTTP/1.1\r\nUser-Agent: JoAgent/3.0\r\nHost: %s:%d\r\nContent-Type: text/xml\r\nContent-Length: %d\r\n\r\n",
			x_http_type_str[m_nType], m_pUri, m_pAddr, m_nPort, m_nBodyLen);
		m_nMessageLen = strlen(m_pMessage) + m_nBodyLen;
		memcpy(m_pMessage+strlen(m_pMessage), m_pBody, m_nBodyLen);
		break;
	default:
		assert(false);
		break;
	}
	
	return J_OK;
}

j_result_t CXHttp::Process()
{
	J_OS::CTCPSocket sock;
	if (sock.Connect(m_pAddr, m_nPort) != J_OK)
		return J_SOCKET_ERROR;
	if (sock.Write_n(m_pMessage, m_nMessageLen) < 0)
		return J_SOCKET_ERROR;

	int nRet = 0;
	m_nRespHeadLen = 0;
	while (1)
	{
		if ((nRet = sock.Read_n(m_pResponse, 1)) < 0)
			return J_SOCKET_ERROR;

		++m_nRespHeadLen;
		if (memcmp(m_pResponse + (m_nRespHeadLen - 4), x_http_end_tag, strlen(x_http_end_tag)) == 0)
			break;
	}
	char *p = strstr(m_pResponse, "Content-Length: ");
	if (p == NULL)
		p = strstr(m_pResponse, "CONTENT-LENGTH: ");

	if (p != NULL)
	{
		m_pRespBodyLen = atoi(p);
		if (sock.Read_n(m_pResponse + m_nRespHeadLen, m_pRespBodyLen) < 0)
			return J_SOCKET_ERROR;
	}

	return J_OK;
}

j_int32_t CXHttp::GetStatusCode()
{
	j_int32_t nStatusCode = 404;
	char *p = strstr(m_pResponse, " ");
	if (p != NULL)
		nStatusCode = atoi(p + 1);

	return (nStatusCode > 0 ? nStatusCode : 404);
}

j_char_t *CXHttp::GetBody()
{
	return (m_pRespBodyLen > 0 ? m_pResponse + m_nRespHeadLen : NULL);
}