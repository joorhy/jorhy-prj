#include "HttpFilter.h"
#include "x_string.h"
#include "x_socket.h"
#include "MuxFactory.h"

const int RATE = 1024;

const char *http_end = "\r\n\r\n";
const char *res_buff = "HTTP/1.1 200 OK\r\n"
						  "Content-Type: video/h264\r\n"
						  "Cache-Control: no-cache\r\n"
						  "Accept-Ranges: bytes\r\n"
						  "Content-Range: bytes 0-\r\n"
						  "Progma: no-cache\r\n\r\n";

CHttpFilter::CHttpFilter()
{
	m_muxFilter = NULL;
	memset(m_strResid, 0, sizeof(m_strResid));
}

CHttpFilter::~CHttpFilter()
{
	if (m_muxFilter)
		CMuxFactory::Instance()->DelMux(this);
}

int CHttpFilter::Parser(int nSocket)
{
	J_OS::CTCPSocket readSocket(nSocket);
	char read_buff[1024] = {0};
	int read_ret = 0;
	int totle_recv = 0;
	do
	{
		read_ret = readSocket.Read(read_buff + totle_recv, sizeof(read_buff));
		if (read_ret < 0)
		{
			return J_SOCKET_ERROR;
		}
		if (strstr(read_buff, "HTTP") == NULL)
			return J_UNKNOW;

		totle_recv += read_ret;
	} while(strstr(read_buff, http_end) == NULL);
	CXString x_string(read_buff);

	CXInteger32 i_command("cmd=", "&");
	x_string >> i_command;
	m_nCommandType = i_command();

	CXChar_n c_resid("resid=", "&");
	x_string >> c_resid;
	memcpy(m_strResid, c_resid(), strlen(c_resid()));

	m_nStreamType = 0;
	CXInteger32 i_type("type=", "&");
	x_string >> i_type;
	m_nStreamType = i_type();

	if (strstr(read_buff, "vod") != NULL)
	{
		CXInteger64U u_start("start=", "&");
		x_string >> u_start;
		m_beginTime = u_start();

		CXInteger64U u_end("end=", "&");
		x_string >> u_end;
		m_endTime = u_end();

		if (strstr(read_buff, "scale=") != NULL)
		{
			CXInteger32 i_scale("scale=", "&");
			x_string >> i_scale;
			m_scale = i_scale();
		}
	}

	if (strstr(read_buff, "stream=raw"))
	{
		m_muxFilter = CMuxFactory::Instance()->GetMux(this, "raw");
	}
	else if (strstr(read_buff, "stream=ps"))
	{
		m_muxFilter = CMuxFactory::Instance()->GetMux(this, "ps");
	}
	else
	{
		m_muxFilter = CMuxFactory::Instance()->GetMux(this, "ts");
	}

	return J_OK;
}

const char *CHttpFilter::GetResourceType()
{
		return "jofs";
}

int CHttpFilter::Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen)
{
	return m_muxFilter->Convert((const char *)pInputData, streamHeader, pOutputData, nOutLen, (void *)&RATE);
}

int CHttpFilter::Complete(int nSocket)
{
	J_OS::CTCPSocket writeSocket(nSocket);
	if (writeSocket.Write_n((char *)res_buff, strlen(res_buff)) < 0)
	{
		J_OS::LOGERROR("CHttpFilter::Complete Send Header error");
		return J_SOCKET_ERROR;
	}

	return J_OK;
}
