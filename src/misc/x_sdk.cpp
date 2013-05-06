#include "x_sdk.h"

#define clean_all() \
    if (json_buf != NULL)\
    {\
        delete json_buf;\
        json_buf = NULL;\
    }\
    if (!is_error(json_helper) && json_helper != NULL)\
    {\
        json_object_put(json_helper);\
        json_helper = NULL;\
    }\

char *HttpCommunicate(char *body,char *uri)
{
	char *resrvdata = NULL;
	char *ret_data = NULL;
	ghttp_request *conntoserv = ghttp_request_new();
	ghttp_set_uri(conntoserv,uri);
	ghttp_set_type(conntoserv, ghttp_type_post); 		//在set body前必须这样
	ghttp_set_body(conntoserv,body,strlen(body));
	ghttp_prepare(conntoserv);
	if(ghttp_process(conntoserv) == ghttp_error)
	{
	    J_OS::LOGINFO("HttpCommunicate MC Error, ghttp_process = %d", ghttp_error);
	    ghttp_close(conntoserv);
	    ghttp_request_destroy(conntoserv);
		return NULL;
	}
	int ret_val = ghttp_status_code(conntoserv);
	switch(ret_val)
	{
	case 200:	resrvdata = ghttp_get_body(conntoserv);
				ret_data = new char[strlen(resrvdata) + 1];
				memset(ret_data, 0, strlen(resrvdata) + 1);
				strncpy(ret_data, resrvdata, ghttp_get_body_len(conntoserv));
				break;
	default:
        J_OS::LOGINFO("HttpCommunicate MC Error, code = %d", ret_val);
        ghttp_request_destroy(conntoserv);
        return NULL;
	}

	ghttp_close(conntoserv);
	ghttp_request_destroy(conntoserv);

	return ret_data;
}

static int get_int(json_object *p_object, const char *p_key)
{
    if (p_object == NULL)
        return 0;

	json_object *pObject = NULL;
	pObject = json_object_object_get(p_object,(char *)p_key);
	if (pObject && !is_error(pObject))
		return json_object_get_int(pObject);

	J_OS::LOGINFO("json get_int error, key = %s", p_key);
	return -1;
}

static char *get_string(json_object *p_object, const char *p_key)
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

static json_object *get_object(json_object *p_object, const char *p_key)
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

r_register *StreamServerResgister(int ssid,char *uri)
{
	char *json_buf = NULL;
	r_register *r_data = NULL;
	json_object *json_helper = NULL;

	/*生成发送数据*/
	json_object *jsojt = json_object_new_object();
	json_object_object_add(jsojt,(char *)"cmd",json_object_new_int(1));
	json_object *helpjs = json_object_new_object();
	json_object_object_add(helpjs,(char *)"id",json_object_new_int(ssid));
	json_object_object_add(jsojt,(char *)"parm",helpjs);
	/*发送并接受数据*/
	json_buf = HttpCommunicate(json_object_to_json_string(jsojt), uri);
	json_object_put(jsojt);
	if(json_buf == NULL)
	{
	    //assert(false);
		return NULL;
	}
	/*解析数据*/
	//json_helper = json_object_new_object();
	json_helper = json_tokener_parse(json_buf);
	//J_OS::LOGINFO(json_buf);
	if(is_error(json_helper))
	{
		J_OS::LOGINFO("StreamServerResgister json_tokener_parse error");
		J_OS::LOGINFO("json_data = %s", json_buf);
		clean_all();
		return NULL;
	}
	r_data = new r_register;
	//r_data->cmd = get_int(json_helper, "cmd");
	r_data->rst = get_int(json_helper, "rst");
	if (r_data->rst != 0)
	{
        J_OS::LOGINFO("json_data = %s", json_buf);
		clean_all();
		return NULL;
	}

	json_helper = get_object(json_helper, (char *)"parm");
	if(!json_helper)
	{
	    clean_all();
		J_OS::LOGINFO("StreamServerResgister json_object_object_get error");
		return NULL;
	}
	r_data->parm.store		= get_string(json_helper, "strore");
	r_data->parm.segment_h 	= get_int(json_helper, "segment_h");
	r_data->parm.segment_a 	= get_int(json_helper, "segment_a");

	json_helper = get_object(json_helper, (char *)"res");
	if(!json_helper)
	{
	    clean_all();
		J_OS::LOGINFO("StreamServerResgister json_object_object_get error");
		return NULL;
	}

	json_object *otemp = json_object_new_object();
	json_object *otemp2 = json_object_new_object();
	json_object *cha   = json_object_new_object();
	for(int i=0;i<json_object_array_length(json_helper);i++)
	{
		otemp = json_object_array_get_idx(json_helper,i);
        if (otemp == NULL)
            continue;

		_res rtemp;
		rtemp.id	= get_int(otemp, "id");
		rtemp.type 	= get_int(otemp, "type");
		rtemp.ip	= get_string(otemp, "ip");
		rtemp.port 	= get_int(otemp, "port");
		rtemp.user 	= get_string(otemp, "user");
		rtemp.pass 	= get_string(otemp, "pass");
		otemp2 = json_object_object_get(otemp,(char *)"cha");
        if (otemp2 == NULL)
		    continue;

		for(int j=0;j<json_object_array_length(otemp2);j++)
		{
			cha = json_object_array_get_idx(otemp2,j);
            if (cha == NULL)
                continue;
			_cha ctemp;
			ctemp.cha	= get_int(cha, "cha");
			ctemp.resid	= get_string(cha, "resid");
			ctemp.ms	= get_int(cha, "ms");
			rtemp.chanum.push_back(ctemp);
		}
		r_data->parm.resnum.push_back(rtemp);
	}
	json_object_put(otemp);
	json_object_put(otemp2);
	json_object_put(cha);
	clean_all();

	return r_data;
}

r_devconfig *GetDevConfigByResid(char *resid,char *uri)
{
	r_devconfig *r_data = NULL;
	if (strstr(resid, ".") != NULL)
	{
		//平台相关处理
		r_data = new r_devconfig;
		r_data->parm.id 	= 0;
		r_data->parm.cha	= 0;
		r_data->rst 		= 0;
	}
	else
	{
		//站端相关处理
		char *json_buf = NULL;
		json_object *json_helper = NULL;

		/*生成发送数据*/
		json_object *jsojt = json_object_new_object();
		json_object_object_add(jsojt,(char *)"cmd",json_object_new_int(2));
		json_object *helpjs = json_object_new_object();
		json_object_object_add(helpjs,(char *)"id",json_object_new_string(resid));
		json_object_object_add(jsojt,(char *)"parm",helpjs);

		/*发送并接受数据*/
		json_buf = HttpCommunicate(json_object_to_json_string(jsojt), uri);
		json_object_put(jsojt);
		if(json_buf == NULL)
		{
			assert(false);
			return NULL;
		}

		/*解析数据*/
		//json_helper = json_object_new_object();
		json_helper = json_tokener_parse(json_buf);
		if(is_error(json_helper))
		{
			J_OS::LOGINFO("GetDevConfigByResid json_tokener_parse error");
			J_OS::LOGINFO("json_data = %s", json_buf);
			clean_all();
			return NULL;
		}
		r_data = new r_devconfig;
		r_data->rst = get_int(json_helper, "rst");
		if (r_data->rst != 0)
		{
			J_OS::LOGINFO("json_data = %s", json_buf);
			clean_all();
			return NULL;
		}

		json_helper = get_object(json_helper,(char *)"parm");
		if(!json_helper)
		{
			clean_all();
			delete r_data;
			J_OS::LOGINFO("GetDevConfigByResid json_object_object_get error");
			return NULL;
		}
		r_data->parm.id		= get_int(json_helper, "id");
		r_data->parm.type	= get_string(json_helper, "type");
		r_data->parm.ip		= get_string(json_helper, "ip");
		r_data->parm.port	= get_int(json_helper, "port");
		r_data->parm.user	= get_string(json_helper, "user");
		r_data->parm.pass	= get_string(json_helper, "pass");
		r_data->parm.cha	= get_int(json_helper, "cha");
		r_data->parm.resid	= get_string(json_helper, "resid");
		r_data->parm.ms		= get_int(json_helper, "ms");
		r_data->parm.store	= get_int(json_helper, "store");
		clean_all();
	}

	return r_data;
}

r_ssconfig *GetSSConfigByResid(char *resid,char *uri)
{
	r_ssconfig *r_data = NULL;
	char *json_buf = NULL;
	json_object *json_helper = NULL;

	/*生成发送数据*/
	json_object *jsojt = json_object_new_object();
	json_object_object_add(jsojt,(char *)"cmd",json_object_new_int(7));
	json_object *helpjs = json_object_new_object();
	json_object_object_add(helpjs,(char *)"resid",json_object_new_string(resid));
	json_object_object_add(jsojt,(char *)"parm",helpjs);

	/*发送并接受数据*/
	json_buf = HttpCommunicate(json_object_to_json_string(jsojt), uri);
	json_object_put(jsojt);
	if(json_buf == NULL)
	{
		assert(false);
		return NULL;
	}

	/*解析数据*/
	json_helper = json_tokener_parse(json_buf);
	if(is_error(json_helper))
	{
		J_OS::LOGINFO("GetSSConfigByResid json_tokener_parse error");
		J_OS::LOGINFO("json_data = %s", json_buf);
		clean_all();
		return NULL;
	}
	r_data = new r_ssconfig;
	r_data->rst = get_int(json_helper, "rst");
	if (r_data->rst != 0)
	{
		J_OS::LOGINFO("json_data = %s", json_buf);
		clean_all();
		return NULL;
	}

	json_helper = get_object(json_helper,(char *)"parm");
	if(!json_helper)
	{
		clean_all();
		delete r_data;
		J_OS::LOGINFO("GetDevConfigByResid json_object_object_get error");
		return NULL;
	}
	r_data->parm.ip		= get_string(json_helper, "ss");
	r_data->parm.port	= get_int(json_helper, "port");
	clean_all();

	return r_data;
}

int GetRealTimePermission(char *resid,char *uid,char *uri)
{
	char *json_buf = NULL;
	int r_data = -1;
	json_object *json_helper = NULL;

	/*生成发送数据*/
	json_object *jsojt = json_object_new_object();
	json_object_object_add(jsojt,(char *)"cmd",json_object_new_int(3));
	json_object *helpjs = json_object_new_object();
	json_object_object_add(helpjs,(char *)"resid",json_object_new_string(resid));
	json_object_object_add(helpjs,(char *)"uid",json_object_new_string(uid));
	json_object_object_add(jsojt,(char *)"parm",helpjs);

	/*发送并接受数据*/
	json_buf = HttpCommunicate(json_object_to_json_string(jsojt), uri);
	json_object_put(jsojt);
	if(json_buf == NULL)
	{
	    assert(false);
	    return r_data;
    }

	/*解析数据*/
	//json_helper = json_object_new_object();
	json_helper = json_tokener_parse(json_buf);
	if(is_error(json_helper))
	{
		J_OS::LOGINFO("GetRealTimePermission json_tokener_parse error");
		J_OS::LOGINFO("json_data = %s", json_buf);
		clean_all();
		return 0;
	}
	r_data = get_int(json_helper, "rst");
	clean_all();

	return r_data;
}

r_historyfile *GetHistoryFile(char *resid,char *uid,time_t stime,time_t etime,char *uri)
{
	char *json_buf = NULL;
	r_historyfile *r_data = NULL;
	json_object *json_helper = NULL;

	/*生成发送数据*/
	json_object *jsojt = json_object_new_object();
	json_object_object_add(jsojt,(char *)"cmd",json_object_new_int(4));
	json_object *helpjs = json_object_new_object();
	json_object_object_add(helpjs,(char *)"resid",json_object_new_string(resid));
	json_object_object_add(helpjs,(char *)"uid",json_object_new_string(uid));
	json_object_object_add(helpjs,(char *)"stime",json_object_new_double(stime));
	json_object_object_add(helpjs,(char *)"etime",json_object_new_double(etime));
	json_object_object_add(jsojt,(char *)"parm",helpjs);

	/*发送并接受数据*/
	json_buf = HttpCommunicate(json_object_to_json_string(jsojt), uri);
	json_object_put(jsojt);
	if(json_buf == NULL)
	{
	    assert(false);
	    return NULL;
    }

	/*解析数据*/
	//json_helper = json_object_new_object();
	json_helper = json_tokener_parse(json_buf);
	if(is_error(json_helper))
	{
		J_OS::LOGINFO("GetHistoryFile json_tokener_parse error");
		J_OS::LOGINFO("json_data = %s", json_buf);
		clean_all();
		return NULL;
	}

    r_data = new r_historyfile;
	r_data->rst = get_int(json_helper,  "rst");
    if (r_data->rst != 0)
	{
        J_OS::LOGINFO("json_data = %s", json_buf);
        delete r_data;
		clean_all();
		return NULL;
	}
	json_helper = get_object(json_helper, (char *)"parm");
	if(!json_helper)
	{
	    delete r_data;
        clean_all();
		J_OS::LOGINFO("GetHistoryFile json_object_object_get parm error");
		return NULL;
	}
	r_data->parm.dvr = get_int(json_helper,  "dvr");

	json_helper	= get_object(json_helper, (char *)"files");
	if(!json_helper)
	{
        clean_all();
	    delete r_data;
		J_OS::LOGINFO("GetHistoryFile json_object_object_get files error");
		return NULL;
	}

	int arrlen = json_object_array_length(json_helper);
	string tmp;
	for(int i=0; i<arrlen; i++)
	{
		tmp = json_object_get_string(json_object_array_get_idx(json_helper, i));
		r_data->parm.files.push_back(tmp);
	}
	clean_all();

	return r_data;
}

int GetWarningMsg(char *resid,int type,char *uri)
{
	char *json_buf = NULL;
	int r_data = -1;
	json_object *json_helper = NULL;

	/*生成发送数据*/
	json_object *jsojt = json_object_new_object();
	json_object_object_add(jsojt,(char *)"cmd",json_object_new_int(5));
	json_object *helpjs = json_object_new_object();
	json_object_object_add(helpjs,(char *)"resid",json_object_new_string(resid));
	json_object_object_add(helpjs,(char *)"type",json_object_new_int(type));
	json_object_object_add(jsojt,(char *)"parm",helpjs);

	/*发送并接受数据*/
	json_buf = HttpCommunicate(json_object_to_json_string(jsojt), uri);
	json_object_put(jsojt);
	if(json_buf == NULL)
	{
	    assert(false);
	    return r_data;
    }

	/*解析数据*/
	//json_helper = json_object_new_object();
	json_helper = json_tokener_parse(json_buf);
	if(is_error(json_helper))
	{
		J_OS::LOGINFO("GetWarningMsg json_tokener_parse error");
		J_OS::LOGINFO("json_data = %s", json_buf);
        clean_all();
		return 0;
	}
	r_data = get_int(json_helper, "rst");
    clean_all();

	return r_data;
}

int GetRecordNotice(s_record &record,char *uri)
{
	char *json_buf = NULL;
	int r_data = -1;
	json_object *json_helper = NULL;

	/*生成发送数据*/
	json_object *jsojt = json_object_new_object();
	json_object *helpjs = json_object_new_object();
	json_object *jsonarr = json_object_new_array();
	json_object_object_add(jsojt,(char *)"cmd",json_object_new_int(6));
	json_object_object_add(helpjs,(char *)"resid",json_object_new_string((char *)record.resid.c_str()));
	json_object_object_add(helpjs,(char *)"files",jsonarr);
	//J_OS::LOGINFO("NUM = %d", record.filenum.size());
	for(vector<s_fileinfo>::iterator iter = record.filenum.begin();
			iter != record.filenum.end();
			iter++)
	{
		json_object *jotemp = json_object_new_object();
		json_object_object_add(jotemp,(char *)"file",json_object_new_string((char *)iter->file.c_str()));
		json_object_object_add(jotemp,(char *)"stime",json_object_new_double(iter->stime));
		json_object_object_add(jotemp,(char *)"etime",json_object_new_double(iter->etime));
		json_object_array_add(jsonarr,jotemp);
	}
	json_object_object_add(jsojt,(char *)"parm", helpjs);


	/*发送并接受数据*/
	json_buf = HttpCommunicate(json_object_to_json_string(jsojt), uri);
    json_object_put(jsojt);
	if(json_buf == NULL)
	{
	    //assert(false);
	    return -1;
    }

	/*解析数据*/
	//json_helper = json_object_new_object();
	json_helper = json_tokener_parse(json_buf);
	if(is_error(json_helper))
	{
		J_OS::LOGINFO("GetRecordNotice json_tokener_parse error");
		J_OS::LOGINFO("json_data = %s", json_buf);
		clean_all();
		return -1;
	}
	r_data = get_int(json_helper, "rst");
    clean_all();

	return r_data;
}








