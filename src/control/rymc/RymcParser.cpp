#include "RymcParser.h"
#include "x_socket.h"
#include "x_string.h"
#include "x_vod_manager.h"
#include "x_sdk.h"
#include "x_resource_manager.h"

static const char *http_end = "\r\n\r\n";

JO_IMPLEMENT_INTERFACE(Parser, "mcsp", CRymcParser::Maker)

CRymcParser::CRymcParser()
{
	memset(m_read_buff, 0, sizeof(m_read_buff));
	m_state = RYMC_HEAD;
	m_read_len = 0;
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
	//printf(pAsioData_in->ioRead.buf);
	memcpy(m_read_buff + m_read_len, pAsioData_in->ioRead.buf, pAsioData_in->ioRead.finishedLen);
	m_read_len += pAsioData_in->ioRead.finishedLen;
	//printf("%s\n", pAsioData_in->ioRead.buf);
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
	j_string_t strBody = httpHelper.GetBody();
	if(strBody.empty())
	{
		J_OS::LOGINFO("CRymcParser::ProcessRequest Empty");
		return J_JSON_UNKOWN;
	}

	j_result_t nResult = J_OK;
	json_object *json_resp_param_obj = NULL;
	J_ControlObj controlObj = {0};
	JoXSdk->ParserRecordCtrl(strBody.c_str(), controlObj);
	switch(controlObj.nCommand)
	{
	case jo_json_ctrl_record://录像控制
	{
		J_OS::LOGINFO("CRymcParser::ProcessRequest RecordControl resid = %s", controlObj.recordCtrl.resid);
		nResult = RecordControl(controlObj.recordCtrl.resid, controlObj.recordCtrl.action, controlObj.recordCtrl.stream_type);
		break;
	}
	case jo_json_ptz_ctrl://云台控制
	{
		nResult = PtzControl(controlObj.ptzCtrl.resid, controlObj.ptzCtrl.action, controlObj.ptzCtrl.parm);
		break;
	}
	case jo_json_search_nvr_files:
	{
		nResult = RecordSearch(controlObj.fileSearchCtrl.resid, controlObj.fileSearchCtrl.begin_time, controlObj.fileSearchCtrl.end_time, &json_resp_param_obj);
		break;
	}
	case jo_json_get_record_info:
	{
		nResult = GetRecordInfo(controlObj.resid, &json_resp_param_obj);
		break;
	}
	case jo_json_del_record:
	{
		nResult = DelRecord(controlObj.delRecordCtrl);
		break;
	}
	case jo_json_get_record_resid:
	{
		nResult = GetRecordResid(&json_resp_param_obj);
		if (nResult < 0)
		{
			json_resp_param_obj = json_object_new_object();
			json_object *json_resid_array_obj = json_object_new_array();
			json_object_object_add(json_resp_param_obj, (char *)"res", json_resid_array_obj);
		}
		break;
	}
	case jo_json_add_resid:
	{
		nResult = JoResourceManager->AddResource(controlObj.resInfo);
		break;
	}
	default:
		nResult = -1;
		break;
	}

	if (nResult < 0)
		nResult = 100;

	json_object *json_response_obj = json_object_new_object();
	json_object_object_add(json_response_obj, (char *)"rst", json_object_new_int(nResult));
	if (json_resp_param_obj != NULL)
		json_object_object_add(json_response_obj, (char *)"parm", json_resp_param_obj);
	httpHelper.SetStatue(200);
	httpHelper.SetBody(json_object_to_json_string(json_response_obj));
	
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
	case jo_act_start_record:
        nRet = m_deviceControl.StartRecord(pResid);
		break;
	case jo_act_stop_record:
		nRet = m_deviceControl.StopRecord(pResid);
		break;
	}

	return nRet;
}

int CRymcParser::RecordSearch(const char *pResid, j_time_t beginTime, j_time_t endTime, json_object **json_param_obj)
{
	j_vec_file_info_t vecFileInfo;
	JoVodManager->SearchVodFiles(pResid, beginTime, endTime, vecFileInfo);
	*json_param_obj = json_object_new_object();
	json_object *json_file_array_obj = json_object_new_array();
	json_object *json_file_obj = json_object_new_object();
	j_int32_t nStartTime = -1;
	j_int32_t nEndTime = -1;
	j_vec_file_info_t::iterator it = vecFileInfo.begin();
	for (; it!=vecFileInfo.end(); ++it)
	{
		if (nStartTime < 0)
		{
			nStartTime = it->tStartTime;
			nEndTime = it->tStoptime;
			json_object_object_add(json_file_obj, (char *)"stime", json_object_new_int(nStartTime));
		}
		else if (it->tStartTime - nEndTime > 20)
		{
			json_object_object_add(json_file_obj, (char *)"etime", json_object_new_int(nEndTime));
			json_object_array_add(json_file_array_obj, json_file_obj);
			nStartTime = it->tStartTime;
			nEndTime = it->tStoptime;
			json_file_obj = json_object_new_object();
			json_object_object_add(json_file_obj, (char *)"stime", json_object_new_int(nStartTime));
		}
		else
		{
			nEndTime = it->tStoptime;
		}
	}
	json_object_object_add(json_file_obj, (char *)"etime", json_object_new_int(nEndTime));
	json_object_array_add(json_file_array_obj, json_file_obj);
	json_object_object_add(*json_param_obj, (char *)"files", json_file_array_obj);

	return J_OK;
}

int CRymcParser::GetRecordInfo(const char *pResid, json_object **json_param_obj)
{
	j_time_t begin_time;
	j_time_t end_time;
	j_int64_t nSize;
	JoVodManager->GetRecordInfo(pResid, begin_time, end_time, nSize);

	nSize /= 1024;//以KB为单位
	*json_param_obj = json_object_new_object();
	json_object_object_add(*json_param_obj, (char *)"stime", json_object_new_int(begin_time));
	json_object_object_add(*json_param_obj, (char *)"etime", json_object_new_int(end_time));
	json_object_object_add(*json_param_obj, (char *)"size", json_object_new_int(nSize));

	return J_OK;
}

int CRymcParser::GetRecordResid(json_object **json_param_obj)
{
	j_vec_resid_t vecResid;
	JoVodManager->GetRecordResid(vecResid);

	*json_param_obj = json_object_new_object();
	json_object *json_resid_array_obj = json_object_new_array();
	j_vec_resid_t::iterator it = vecResid.begin();
	for (; it!=vecResid.end(); ++it)
	{
		json_object_array_add(json_resid_array_obj, json_object_new_string((char *)it->c_str()));
	}
	json_object_object_add(*json_param_obj, (char *)"res", json_resid_array_obj);

	return J_OK;
}

int CRymcParser::DelRecord(J_DelRecordCtrl &delRecordCtrl)
{
	JoVodManager->DelFiles(delRecordCtrl);
	return J_OK;
}