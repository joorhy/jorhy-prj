#include "RymcParser.h"
#include "x_socket.h"
#include "x_string.h"

static const char *http_end = "\r\n\r\n";

CRymcParser::CRymcParser()
{
	memset(m_read_buff, 0, sizeof(m_read_buff));
	m_state = RYMC_HEAD;
}

CRymcParser::~CRymcParser()
{

}

int CRymcParser::AddUser(j_socket_t nSocket, const char *pAddr, short nPort)
{
	printf("%s\n", pAddr);
	return J_OK;
}

int CRymcParser::ProcessRequest(J_AsioDataBase *pAsioData_in, J_AsioDataBase *pAsioData_out)
{
	memcpy(m_read_buff + m_read_len, pAsioData_in->ioRead.buf, pAsioData_in->ioRead.finishedLen);
	m_read_len += pAsioData_in->ioRead.finishedLen;
	printf("%s\n", pAsioData_in->ioRead.buf);
	memset(pAsioData_in->ioRead.buf, 0, 2048);
	if (m_state == RYMC_HEAD)
	{
		if (strstr(m_read_buff, http_end) == NULL)
		{
			pAsioData_in->ioRead.bufLen = 1;
			pAsioData_in->ioRead.whole = true;
			return J_NOT_COMPLATE;
		}
		m_state = RYMC_BODY;
	}

	CXString x_string(m_read_buff);
	CXInteger32 i_command("Content-Length: ", "\r\n");
	x_string >> i_command;

	if (m_state == RYMC_BODY)
	{
		j_char_t *p = strstr(m_read_buff, http_end);
		int body_recv = i_command();
		if (body_recv > 0)
		{
			pAsioData_in->ioRead.bufLen = body_recv;
			pAsioData_in->ioRead.whole = true;
			m_state = RYMC_FINISH;
			return J_NOT_COMPLATE;
		}
	}
	
	CHttpHelper httpHelper(m_read_buff);
	std::string strBody = httpHelper.GetBody();
	if(strBody.empty())
	{
		J_OS::LOGINFO("CRymcParser::ProcessRequest Empty");
		return J_JSON_UNKOWN;
	}

	json_object *js = json_tokener_parse((char *)strBody.c_str());
	if(is_error(js))
	{
		return J_JSON_UNKOWN;
	}

	int nRet = J_OK;
	int cmd = json_object_get_int(json_object_object_get(js, (char *)"cmd"));
	json_object *ret_obj = json_object_new_object();
	switch(cmd)
	{
	case RCD_CONTROL://录像控制
	{
		r_recordcol recordcol;
		js = json_object_object_get(js, (char *)"parm");
		recordcol.act		= json_object_get_int(json_object_object_get(js, (char *)"act"));
		recordcol.resid 	= json_object_get_string(json_object_object_get(js, (char *)"resid"));
		recordcol.ms	= json_object_get_int(json_object_object_get(js, (char *)"ms"));

		J_OS::LOGINFO("CRymcParser::ProcessRequest RecordControl resid = %s", recordcol.resid.c_str());
		nRet = RecordControl(recordcol.resid.c_str(), recordcol.act, recordcol.ms);

		break;
	}
	case RCD_SEARCH_DVR://DVR历史查询
	{
		json_object_object_add(ret_obj, (char *)"cmd",json_object_new_int(102));

		break;
	}
	case PTZ_CONTROL://云台控制
	{
		r_cameracol ptc_cntl;
		js = json_object_object_get(js, (char *)"parm");
		ptc_cntl.resid 	= json_object_get_string(json_object_object_get(js, (char *)"resid"));
		ptc_cntl.action		= json_object_get_int(json_object_object_get(js, (char *)"action"));
		ptc_cntl.value	= json_object_get_int(json_object_object_get(js, (char *)"value"));
		
		nRet = PtzControl(ptc_cntl.resid.c_str(), ptc_cntl.action, ptc_cntl.value);
		break;
	}
	case RCD_MOVE://录像迁移
	{
		json_object_object_add(ret_obj, (char *)"cmd", json_object_new_int(104));
		break;
	}
	case RCD_SEARCH_NVR:
	{
		r_rcd_search rcd_search;
		js = json_object_object_get(js, (char *)"parm");
		rcd_search.resid = json_object_get_string(json_object_object_get(js, (char *)"resid"));
		rcd_search.begin_time = json_object_get_int(json_object_object_get(js, (char *)"start"));
		rcd_search.end_time	= json_object_get_int(json_object_object_get(js, (char *)"end"));
		
		nRet = RecordSearch(rcd_search.resid.c_str(), rcd_search.begin_time, rcd_search.end_time);
		break;
	}
	default:
		break;
	}

	if (nRet < 0)
		nRet = 1;

	json_object_object_add(ret_obj, (char *)"rst", json_object_new_int(nRet));
	httpHelper.SetStatue(200);
	httpHelper.SetBody(json_object_to_json_string(ret_obj));
	
	j_int32_t nRespLen = strlen(httpHelper.GetString());
	j_char_t *pResponse = new char[nRespLen + 1];
	pResponse[nRespLen] = '\0';
	memcpy(pResponse, httpHelper.GetString(), nRespLen);
	
	pAsioData_out->ioWrite.buf = pResponse;
    pAsioData_out->ioWrite.bufLen = nRespLen;
	pAsioData_out->ioWrite.whole = true;
	
	memset(m_read_buff, 0, sizeof(m_read_buff));
	m_state = RYMC_HEAD;
	m_read_len = 0;

	return J_OK;
}

int CRymcParser::DelUser(j_socket_t nSocket)
{
	return J_OK;
}

int CRymcParser::PtzControl(const char *pResid, int nCmd, int nParam)
{
	return m_deviceControl.PtzControl(pResid, nCmd, nParam);
}

int CRymcParser::RecordControl(const char *pResid, int nCmd, int nStreamType)
{
	int nRet = J_OK;
	switch(nCmd)
	{
	case 1:
        nRet = m_deviceControl.StartRecord(pResid);
		break;
	case 2:
		nRet = m_deviceControl.StopRecord(pResid);
		break;
	}

	return nRet;
}

int CRymcParser::RecordSearch(const char *pResid, time_t beginTime, time_t endTime)
{
	return J_OK;
}

