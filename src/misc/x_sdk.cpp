#include "x_sdk.h"

static const char *dev_type[] = 
{ "", "hik", "sony", "aipstar", "aironix", "samsung", "dahua", "onvif"};

#define JSON_CLEAN_ALL() \
    if (!is_error(json_respose_obj) && json_respose_obj != NULL)\
    {\
        json_object_put(json_respose_obj);\
        json_respose_obj = NULL;\
    }

JO_IMPLEMENT_SINGLETON(XSdk)

char *CXSdk::HttpCommunicate(char *body, char *uri)
{
	j_char_t *resrvdata = NULL;
	j_char_t *ret_data = NULL;
	m_httpHelper.SetUri(uri);
	m_httpHelper.SetType(x_http_type_post);
	m_httpHelper.SetBody(body,strlen(body));
	m_httpHelper.Prepare();
	if(m_httpHelper.Process() != J_OK)
	{
	    J_OS::LOGINFO("HttpCommunicate MC Error");
		return NULL;
	}
	j_int32_t ret_val = m_httpHelper.GetStatusCode();
	switch(ret_val)
	{
	case 200:	resrvdata = m_httpHelper.GetBody();
				if (resrvdata == NULL)
					return NULL;
				
				//J_OS::LOGINFO("%d", httpHelper.GetBodyLen());
				ret_data = new char[m_httpHelper.GetBodyLen() + 1];
				memset(ret_data, 0, m_httpHelper.GetBodyLen() + 1);
				strncpy(ret_data, resrvdata, m_httpHelper.GetBodyLen());
				break;
	default:
        J_OS::LOGINFO("HttpCommunicate MC Error, code = %d", ret_val);
        return NULL;
	}

	return ret_data;
}

int CXSdk::JsonGetInt(json_object *p_object, const char *p_key)
{
    if (p_object == NULL)
        return 0;

	json_object *pObject = NULL;
	pObject = json_object_object_get(p_object,(char *)p_key);
	if (pObject != NULL && !is_error(pObject))
		return json_object_get_int(pObject);

	J_OS::LOGINFO("json get_int error, key = %s", p_key);
	return -1;
}

char *CXSdk::JsonGetString(json_object *p_object, const char *p_key)
{
    if (p_object == NULL)
        return (char *)"";

	json_object *pObject = NULL;
	pObject = json_object_object_get(p_object,(char *)p_key);
	if (pObject && !is_error(pObject))
		return json_object_get_string(pObject);

	J_OS::LOGINFO("json get_string error, key = %s", p_key);
	return (char *)"";
}

json_object *CXSdk::JsonGetObj(json_object *p_object, const char *p_key)
{
    if (p_object == NULL)
        return NULL;

	json_object *pObject = NULL;
	pObject = json_object_object_get(p_object,(char *)p_key);
	if (pObject && !is_error(pObject))
		return pObject;

	J_OS::LOGINFO("json get_string error, key = %s", p_key);
	return NULL;
}

j_result_t CXSdk::Login(j_int32_t nId, j_char_t *pUrl, ResourceMap &resInfo)
{
	json_object *json_request_obj = json_object_new_object();
	json_object_object_add(json_request_obj, (char *)"cmd", json_object_new_int(jo_json_login));
	json_object *json_param_obj = json_object_new_object();
	json_object_object_add(json_param_obj, (char *)"id", json_object_new_int(nId));
	json_object_object_add(json_request_obj, (char *)"parm", json_param_obj);

	char *json_return_buf = HttpCommunicate(json_object_to_json_string(json_request_obj), pUrl);
	json_object_put(json_request_obj);
	if(json_return_buf == NULL)
	{
		J_OS::LOGINFO("CXSdk::Login error");
		return J_UNKNOW;
	}

	json_object *json_respose_obj = json_object_new_object();
	json_respose_obj = json_tokener_parse(json_return_buf);
	if(is_error(json_respose_obj))
	{
		J_OS::LOGINFO("StreamServerResgister json_tokener_parse error");
		J_OS::LOGINFO("json_data = %s", json_return_buf);
		JSON_CLEAN_ALL();
		return J_UNKNOW;
	}
	j_result_t nResult = JsonGetInt(json_respose_obj, "rst");
	if (nResult != J_OK)
	{
        J_OS::LOGINFO("json_data = %s", json_return_buf);
		JSON_CLEAN_ALL();
		return J_UNKNOW;
	}

	json_object *json_resp_param_obj = JsonGetObj(json_respose_obj, (char *)"parm");
	if(!json_resp_param_obj)
	{
	    JSON_CLEAN_ALL();
		J_OS::LOGINFO("StreamServerResgister json_object_object_get error");
		return J_UNKNOW;
	}

	json_object *json_resource_obj = JsonGetObj(json_resp_param_obj, (char *)"res");
	if(!json_resource_obj)
	{
	    JSON_CLEAN_ALL();
		J_OS::LOGINFO("StreamServerResgister json_object_object_get error");
		return J_UNKNOW;
	}

	json_object *json_dev_obj = json_object_new_object();
	json_object *json_res_obj = json_object_new_object();
	json_object *json_channel_obj   = json_object_new_object();
	for(int i=0; i<json_object_array_length(json_resource_obj); i++)
	{
		json_dev_obj = json_object_array_get_idx(json_resource_obj, i);
        if (json_dev_obj == NULL)
            continue;

		J_DeviceInfo devInfo = {0};
		devInfo.devStatus = jo_dev_broken;
		devInfo.devId = JsonGetInt(json_dev_obj, "id");
		int devType = JsonGetInt(json_dev_obj, "type");
		sprintf(devInfo.devType, "%s", dev_type[devType]);
		sprintf(devInfo.devIp, "%s", JsonGetString(json_dev_obj, "ip"));
		devInfo.devPort = JsonGetInt(json_dev_obj, "port");
		sprintf(devInfo.userName, "%s", JsonGetString(json_dev_obj, "user"));
		sprintf(devInfo.passWd, "%s", JsonGetString(json_dev_obj, "pass"));
		json_res_obj = json_object_object_get(json_dev_obj, (char *)"cha");
        if (json_res_obj == NULL)
		    continue;

		for(int j=0; j<json_object_array_length(json_res_obj); j++)
		{
			json_channel_obj = json_object_array_get_idx(json_res_obj, j);
            if (json_channel_obj == NULL)
                continue;

			J_ResourceInfo resourceInfo;
			resourceInfo.devInfo = devInfo;
			resourceInfo.chNum = JsonGetInt(json_channel_obj, "cha");
			sprintf(resourceInfo.resid, "%s", JsonGetString(json_channel_obj, "resid"));
			resourceInfo.streamType	= JsonGetInt(json_channel_obj, "ms");
			resInfo[resourceInfo.resid] = resourceInfo;
		}
	}
	JSON_CLEAN_ALL();

	return J_OK;
}

j_result_t CXSdk::GetResourceInfo(j_char_t *pResid, j_char_t *pUrl, J_ResourceInfo &resInfo)
{
	memset(&resInfo.devInfo, 0, sizeof(J_DeviceInfo));
	if (strstr(pResid, ".") != NULL)
	{
		//平台相关处理
		memset(resInfo.resid, 0, sizeof(resInfo.resid));
		resInfo.chNum = 0;
		resInfo.streamType = 0;
	}
	else
	{
		//生成发送数据
		json_object *json_request_obj = json_object_new_object();
		json_object_object_add(json_request_obj, (char *)"cmd", json_object_new_int(jo_json_get_resinfo));
		json_object *json_param_obj = json_object_new_object();
		json_object_object_add(json_param_obj, (char *)"id", json_object_new_string(pResid));
		json_object_object_add(json_request_obj, (char *)"parm", json_param_obj);

		//发送并接受数据
		char *json_return_buf  = HttpCommunicate(json_object_to_json_string(json_request_obj), pUrl);
		json_object_put(json_request_obj);
		if(json_return_buf == NULL)
		{
			J_OS::LOGINFO(" CXSdk::GetResourceInfo HttpCommunicate Faild");
			return J_UNKNOW;
		}

		//解析数据
		json_object *json_respose_obj = json_object_new_object();
		json_respose_obj = json_tokener_parse(json_return_buf);
		if(is_error(json_respose_obj))
		{
			J_OS::LOGINFO("CXSdk::GetResourceInfo json_tokener_parse error");
			J_OS::LOGINFO("json_data = %s", json_return_buf);
			JSON_CLEAN_ALL();
			return J_UNKNOW;
		}
		j_result_t nResult = JsonGetInt(json_respose_obj, "rst");
		if (nResult != 0)
		{
			J_OS::LOGINFO("json_data = %s", json_return_buf);
			JSON_CLEAN_ALL();
			return J_UNKNOW;
		}

		json_object *json_resp_param_obj = JsonGetObj(json_respose_obj, (char *)"parm");
		if(!json_resp_param_obj)
		{
			JSON_CLEAN_ALL();
			J_OS::LOGINFO("CXSdk::GetResourceInfo json_object_object_get error");
			return J_UNKNOW;
		}
		sprintf(resInfo.resid, "%s", pResid);
		resInfo.streamType = 0;
		resInfo.devInfo.devId = JsonGetInt(json_resp_param_obj, "id");
		sprintf(resInfo.devInfo.devType, "%s",  JsonGetString(json_resp_param_obj, "type"));
		sprintf(resInfo.devInfo.devIp, "%s", JsonGetString(json_resp_param_obj, "ip"));
		resInfo.devInfo.devPort = JsonGetInt(json_resp_param_obj, "port");
		sprintf(resInfo.devInfo.userName, "%s", JsonGetString(json_resp_param_obj, "user"));
		sprintf(resInfo.devInfo.passWd, "%s", JsonGetString(json_resp_param_obj, "pass"));
		resInfo.chNum = JsonGetInt(json_resp_param_obj, "cha");
		sprintf(resInfo.resid, "%s", JsonGetString(json_resp_param_obj, "resid"));
		resInfo.streamType = JsonGetInt(json_resp_param_obj, "ms");
		JSON_CLEAN_ALL();
	}

	return J_OK;
}

j_result_t CXSdk::GetStreamServerInfo(j_char_t *pResid, j_char_t *pUrl, J_StreamServerInfo &ssInfo)
{
	//生成发送数据
	json_object *json_request_obj = json_object_new_object();
	json_object_object_add(json_request_obj, (char *)"cmd", json_object_new_int(jo_json_get_ss_info));
	json_object *json_param_obj = json_object_new_object();
	json_object_object_add(json_param_obj ,(char *)"resid", json_object_new_string(pResid));
	json_object_object_add(json_request_obj, (char *)"parm", json_param_obj);

	//发送并接受数据
	char *json_return_buf = HttpCommunicate(json_object_to_json_string(json_request_obj), pUrl);
	json_object_put(json_request_obj);
	if(json_return_buf == NULL)
	{
		J_OS::LOGINFO(" CXSdk::GetStreamServerInfo HttpCommunicate Faild");
		return J_UNKNOW;
	}

	//解析数据
	json_object *json_respose_obj = json_object_new_object();
	json_respose_obj = json_tokener_parse(json_return_buf);
	if(is_error(json_respose_obj))
	{
		J_OS::LOGINFO("GetSSConfigByResid json_tokener_parse error");
		J_OS::LOGINFO("json_data = %s", json_return_buf);
		JSON_CLEAN_ALL();
		return J_UNKNOW;
	}
	j_result_t nResult = JsonGetInt(json_respose_obj, "rst");
	if (nResult != 0)
	{
		J_OS::LOGINFO("json_data = %s", json_return_buf);
		JSON_CLEAN_ALL();
		return J_UNKNOW;
	}

	json_object *json_resp_param_obj = JsonGetObj(json_respose_obj, (char *)"parm");
	if(!json_resp_param_obj)
	{
		JSON_CLEAN_ALL();
		J_OS::LOGINFO("GetStreamServerInfo json_object_object_get error");
		return J_UNKNOW;
	}
	memset(&ssInfo, 0, sizeof(J_StreamServerInfo));
	sprintf(ssInfo.devIp, "%s", JsonGetString(json_resp_param_obj, "ss"));
	ssInfo.devPort = JsonGetInt(json_resp_param_obj, "port");
	JSON_CLEAN_ALL();

	return J_OK;
}

j_result_t CXSdk::KeepAlive(j_int32_t nStreamServerId, j_char_t *pUrl)
{
	//生成发送数据
	json_object *json_request_obj = json_object_new_object();
	json_object_object_add(json_request_obj, (char *)"cmd", json_object_new_int(jo_json_keepalive));
	json_object *json_param_obj = json_object_new_object();
	json_object_object_add(json_param_obj ,(char *)"id", json_object_new_int(nStreamServerId));
	json_object_object_add(json_request_obj, (char *)"parm", json_param_obj);

	//发送并接受数据
	char *json_return_buf = HttpCommunicate(json_object_to_json_string(json_request_obj), pUrl);
	json_object_put(json_request_obj);
	if(json_return_buf == NULL)
	{
		J_OS::LOGINFO(" CXSdk::KeepAlive HttpCommunicate Faild");
	    return J_UNKNOW;
    }

	//解析数据
	json_object *json_respose_obj = json_object_new_object();
	json_respose_obj = json_tokener_parse(json_return_buf);
	if(is_error(json_respose_obj))
	{
		J_OS::LOGINFO("CXSdk::KeepAlive json_tokener_parse error");
		J_OS::LOGINFO("json_data = %s", json_return_buf);
        JSON_CLEAN_ALL();
		return J_UNKNOW;
	}
	j_result_t nResult = JsonGetInt(json_respose_obj, "rst");
	if (nResult != 0)
	{
		JSON_CLEAN_ALL();
		return J_UNKNOW;
	}
    JSON_CLEAN_ALL();

	return J_OK;
}

j_result_t CXSdk::ParserRecordCtrl(const char *pJsonStr, J_ControlObj &ctrlObj)
{
	json_object *json_request_obj = json_tokener_parse((char *)pJsonStr);
	if(is_error(json_request_obj))
	{
		return J_JSON_UNKOWN;
	}
	ctrlObj.nCommand = JsonGetInt(json_request_obj, (char *)"cmd");
	json_object *json_param_obj = json_object_new_object();
	switch (ctrlObj.nCommand)
	{
		case jo_json_ctrl_record://录像控制
			json_param_obj = JsonGetObj(json_request_obj, (char *)"parm");
			ctrlObj.recordCtrl.action	= JsonGetInt(json_param_obj, (char *)"act");
			sprintf(ctrlObj.recordCtrl.resid, "%s", JsonGetString(json_param_obj, (char *)"resid"));
			ctrlObj.recordCtrl.stream_type	= JsonGetInt(json_param_obj, (char *)"ms");
			break;
		case jo_json_ptz_ctrl://云台控制
			json_param_obj = JsonGetObj(json_request_obj, (char *)"parm");
			sprintf(ctrlObj.ptzCtrl.resid, "%s", JsonGetString(json_param_obj, (char *)"resid"));
			ctrlObj.ptzCtrl.action	= JsonGetInt(json_param_obj, (char *)"action");
			ctrlObj.ptzCtrl.parm	= JsonGetInt(json_param_obj, (char *)"value");
			break;
		case jo_json_search_nvr_files://录像查询
			json_param_obj = JsonGetObj(json_request_obj, (char *)"parm");
			sprintf(ctrlObj.fileSearchCtrl.resid, "%s", JsonGetString(json_param_obj, (char *)"resid"));
			ctrlObj.fileSearchCtrl.begin_time = JsonGetInt(json_param_obj, (char *)"stime");
			ctrlObj.fileSearchCtrl.end_time	= JsonGetInt(json_param_obj, (char *)"etime");
			break;
		case jo_json_get_record_info://获得录像资源
			json_param_obj = JsonGetObj(json_request_obj, (char *)"parm");
			sprintf(ctrlObj.resid, "%s", JsonGetString(json_param_obj, (char *)"resid"));
			break;
		case jo_json_del_record:
			json_param_obj = JsonGetObj(json_request_obj, (char *)"parm");
			sprintf(ctrlObj.delRecordCtrl.resid, "%s", JsonGetString(json_param_obj, (char *)"resid"));
			ctrlObj.delRecordCtrl.nType = JsonGetInt(json_param_obj, (char *)"all");
			ctrlObj.delRecordCtrl.begin_time = JsonGetInt(json_param_obj, (char *)"stime");
			ctrlObj.delRecordCtrl.end_time = JsonGetInt(json_param_obj, (char *)"etime");
			break;
		case jo_json_add_resid://添加资源
			memset(&ctrlObj.resInfo.devInfo, 0, sizeof(J_DeviceInfo));
			json_param_obj = JsonGetObj(json_request_obj, (char *)"parm");
			sprintf(ctrlObj.resInfo.resid, "%s", JsonGetString(json_param_obj, (char *)"resid"));
			ctrlObj.resInfo.chNum = JsonGetInt(json_param_obj, (char *)"cha");
			ctrlObj.resInfo.streamType = JsonGetInt(json_param_obj, (char *)"ms");
			ctrlObj.resInfo.devInfo.devId = JsonGetInt(json_param_obj, (char *)"id");
			sprintf(ctrlObj.resInfo.devInfo.devIp, "%s",  JsonGetString(json_param_obj, (char *)"ip"));
			ctrlObj.resInfo.devInfo.devPort = JsonGetInt(json_param_obj, (char *)"port");
			int devType = JsonGetInt(json_param_obj, (char *)"type");
			sprintf(ctrlObj.resInfo.devInfo.devType, "%s", dev_type[devType]);
			sprintf(ctrlObj.resInfo.devInfo.userName, "%s", JsonGetString(json_param_obj, (char *)"user"));
			sprintf(ctrlObj.resInfo.devInfo.passWd, "%s", JsonGetString(json_param_obj, (char *)"pass"));
			break;
	}
	json_object_put(json_request_obj);

	return J_OK;
}