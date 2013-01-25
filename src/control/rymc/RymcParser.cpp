#include "RymcParser.h"
#include "x_socket.h"
#include "x_string.h"

static const char *http_end = "\r\n\r\n";

CRymcParser::CRymcParser()
{

}

CRymcParser::~CRymcParser()
{

}

int CRymcParser::AddUser(int nSocket, const char *pAddr, short nPort)
{
	return J_OK;
}

int CRymcParser::ProcessRequest(int nSocket, char *&pResponse, int &nRespLen)
{
	J_OS::CTCPSocket ReadSocket(nSocket);
	char read_buff[2048] = {0};
	int read_ret = 0;
	int totle_recv = 0;
	char *p = NULL;
	do
	{
		read_ret = ReadSocket.Read(read_buff + totle_recv, sizeof(read_buff));
		if (read_ret < 0)
		{
			return J_SOCKET_ERROR;
		}
		if (strstr(read_buff, "HTTP") == NULL && strstr(read_buff, "POST") == NULL)
			return J_OK;

		totle_recv += read_ret;
	} while((p = strstr(read_buff, http_end)) == NULL);

	CXString x_string(read_buff);
	CXInteger32 i_command("Content-Length: ", "\r\n");
	x_string >> i_command;

	int body_recv = i_command() - (totle_recv - (p - read_buff) - 4);
	while (body_recv > 0)
	{
		read_ret = ReadSocket.Read(read_buff + totle_recv, sizeof(read_buff));
		if (read_ret < 0)
		{
			return J_SOCKET_ERROR;
		}
		totle_recv += read_ret;
		body_recv -= read_ret;
	}
	
	CHttpHelper httpHelper(read_buff);
	std::string strBody = httpHelper.GetBody();
	if(strBody.empty())
	{
		J_OS::LOGINFO("Empty");
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
	case 101://录像控制
	{
		r_recordcol recordcol;
		js = json_object_object_get(js, (char *)"parm");
		recordcol.act		= json_object_get_int(json_object_object_get(js, (char *)"act"));
		recordcol.resid 	= json_object_get_string(json_object_object_get(js, (char *)"resid"));
		recordcol.ms	= json_object_get_int(json_object_object_get(js, (char *)"ms"));

		nRet = RecordControl(recordcol.resid.c_str(), recordcol.act, recordcol.ms);

		break;
	}
	case 102://DVR历史查询
	{
		json_object_object_add(ret_obj, (char *)"cmd",json_object_new_int(102));

		break;
	}
	case 103://云台控制
	{
		r_cameracol ptc_cntl;
		js = json_object_object_get(js, (char *)"parm");
		ptc_cntl.resid 	= json_object_get_string(json_object_object_get(js, (char *)"resid"));
		ptc_cntl.action		= json_object_get_int(json_object_object_get(js, (char *)"action"));
		ptc_cntl.value	= json_object_get_int(json_object_object_get(js, (char *)"value"));

		nRet = PtzControl(ptc_cntl.resid.c_str(), ptc_cntl.action, ptc_cntl.value);
		break;
	}
	case 104://录像通知
	{
		json_object_object_add(ret_obj, (char *)"cmd", json_object_new_int(104));
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
	
	nRespLen = strlen(httpHelper.GetString());
	pResponse = new char[nRespLen + 1];
	pResponse[nRespLen] = '0';
	memcpy(pResponse, httpHelper.GetString(), nRespLen);

	return J_OK;
}

int CRymcParser::DelUser(int nSocket)
{
	return J_OK;
}

int CRymcParser::PtzControl(const char *pResid, int nCmd, int nParam)
{
	int nRet = J_OK;
	switch(nCmd)
	{
	case 1:
		nRet = m_deviceControl.PtzControl(pResid, JO_PTZ_UP, nParam);
		break;
	case 2:
		nRet = m_deviceControl.PtzControl(pResid, JO_PTZ_DOWN, nParam);
		break;
	case 3:
		nRet = m_deviceControl.PtzControl(pResid, JO_PTZ_LEFT, nParam);
		break;
	case 4:
		nRet = m_deviceControl.PtzControl(pResid, JO_PTZ_RIGHT, nParam);
		break;
	case 5:
		nRet = m_deviceControl.PtzControl(pResid, JO_PTZ_UP_LEFT, nParam);
		break;
	case 6:
		nRet = m_deviceControl.PtzControl(pResid, JO_PTZ_UP_RIGHT, nParam);
		break;
	case 7:
		nRet = m_deviceControl.PtzControl(pResid, JO_PTZ_DOWN_LEFT, nParam);
		break;
	case 8:
		nRet = m_deviceControl.PtzControl(pResid, JO_PTZ_DOWN_RIGHT, nParam);
		break;
	case 9:
		nRet = m_deviceControl.PtzControl(pResid, JO_PTZ_PRE_SET, nParam);
		break;
	case 10:
		nRet = m_deviceControl.PtzControl(pResid, JO_PTZ_PRE_CLR, nParam);
		break;
	case 11:
		nRet = m_deviceControl.PtzControl(pResid, JO_PTZ_GOTO_PRE, nParam);
		break;
	case 12:
		nRet = m_deviceControl.PtzControl(pResid, JO_PTZ_ZOOM_IN, nParam);
		break;
	case 13:
		nRet = m_deviceControl.PtzControl(pResid, JO_PTZ_ZOOM_OUT, nParam);
		break;
	default:
		nRet = J_UNKNOW;
		break;
	}

	return nRet;
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

