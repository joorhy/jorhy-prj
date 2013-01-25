#include "x_http_helper.h"

const char *resp = "HTTP/1.1 %d OK\r\n"
						 "Content-Type: application/x-json;charset=ISO-8859-1\r\n"
						 "Content-Length: %d\r\n\r\n";

CHttpHelper::CHttpHelper(const char *pRequest)
: m_nStatue(200)
{
	if (strlen(pRequest) > sizeof(m_strReqMessage))
	{
		J_OS::LOGINFO("CHttpHelper::CHttpHelper Message too long");
		throw("Constructor Error");
	}
	memset(m_strReqMessage, 0, sizeof(m_strReqMessage));
	strcpy(m_strReqMessage, pRequest);
}

CHttpHelper::~CHttpHelper()
{

}

std::string CHttpHelper::GetBody()
{
	char *p = strstr(m_strReqMessage, "\r\n\r\n");
	if (p != NULL)
	{
		char *p2 = p + strlen("\r\n\r\n");
		return p2;
	}

	return "";
}

int CHttpHelper::SetBody(char *pBody)
{
	m_strBody = pBody;
	return J_OK;
}

int CHttpHelper::SetStatue(int nStatue)
{
	m_nStatue = nStatue;
	return J_OK;
}

int CHttpHelper::ToString()
{
	char resp_buff[512] = {0};
	sprintf(resp_buff, resp, m_nStatue, m_strBody.length());
	m_strRespMessage.append(resp_buff);
	m_strRespMessage += m_strBody;

	return J_OK;
}

char *CHttpHelper::GetString()
{
	ToString();
	return (char *)m_strRespMessage.c_str();
}

int CHttpHelper::GetLength()
{
	ToString();
	return m_strRespMessage.length();
}
