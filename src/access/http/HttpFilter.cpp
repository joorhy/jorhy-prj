#include "HttpFilter.h"
#include "x_string.h"
#include "x_socket.h"
#include "x_mux_factory.h"

const int RATE = 1024;

const char *http_end = "\r\n\r\n";
const char *res_buff = "HTTP/1.1 200 OK\r\n"
						  "Content-Type: video/h264\r\n"
						  "Cache-Control: no-cache\r\n"
						  "Accept-Ranges: bytes\r\n"
						  "Content-Range: bytes 0-\r\n"
						  "Progma: no-cache\r\n\r\n";

JO_IMPLEMENT_INTERFACE(Filter, "http", CHttpFilter::Maker)

CHttpFilter::CHttpFilter()
{
	m_muxFilter = NULL;
	memset(m_strResid, 0, sizeof(m_strResid));
	memset(m_read_buff, 0, sizeof(m_read_buff));
	m_read_len = 0;
}

CHttpFilter::~CHttpFilter()
{
	if (m_muxFilter)
		SingletonTmpl<CMuxFactory>::Instance()->DelMux(this);
}

int CHttpFilter::Parser(J_AsioDataBase &asioData)
{
	memcpy(m_read_buff + m_read_len, asioData.ioRead.buf, asioData.ioRead.finishedLen);
	if (strstr(m_read_buff, http_end) == NULL)
	{
		m_read_len += asioData.ioRead.finishedLen;
		asioData.ioRead.bufLen = 1024;
		asioData.ioRead.whole = false;
		return J_NOT_COMPLATE;
	}
	CXString x_string(m_read_buff);

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

	if (strstr(m_read_buff, "vod") != NULL)
	{
		CXInteger64U u_start("start=", "&");
		x_string >> u_start;
		m_beginTime = u_start();

		CXInteger64U u_end("end=", "&");
		x_string >> u_end;
		m_endTime = u_end();

		if (strstr(m_read_buff, "scale=") != NULL)
		{
			CXInteger32 i_scale("scale=", "&");
			x_string >> i_scale;
			m_scale = i_scale();
		}
		m_mode = jo_push_mode;
	}

	if (strstr(m_read_buff, "stream=raw"))
	{
		m_muxFilter = SingletonTmpl<CMuxFactory>::Instance()->GetMux(this, "raw");
	}
	else if (strstr(m_read_buff, "stream=ps"))
	{
		m_muxFilter = SingletonTmpl<CMuxFactory>::Instance()->GetMux(this, "ps");
	}
	else
	{
		m_muxFilter = SingletonTmpl<CMuxFactory>::Instance()->GetMux(this, "ts");
	}
	memset (m_read_buff, 0, sizeof(m_read_buff));
	m_read_len = 0;

	return J_OK;
}

const char *CHttpFilter::GetResourceType()
{
	if (strstr(m_strResid, ".") != NULL)
		return "jorf";
		
	return "jofs";
}

int CHttpFilter::Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen)
{
	return m_muxFilter->Convert((const char *)pInputData, streamHeader, pOutputData, nOutLen, (void *)&RATE);
}

int CHttpFilter::Complete(J_AsioDataBase &asioData)
{
	asioData.ioWrite.buf = res_buff;
	asioData.ioWrite.bufLen = strlen(res_buff);
	asioData.ioWrite.whole = true;

	return J_OK;
}
