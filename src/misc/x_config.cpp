#include "x_config.h"
#include "json.h"

using namespace std;

int CXConfig::m_mcPort = 6004;
std::string CXConfig::m_mcAddr;
int CXConfig::m_ssId = 0;
std::string CXConfig::m_httpUrl;
std::string CXConfig::m_configType;
std::string CXConfig::m_vodPath;
std::vector<J_ServerInfo> CXConfig::m_serverVec;

CXConfig::CXConfig()
{

}

CXConfig::~CXConfig()
{

}

int CXConfig::Init()
{
	fstream fin;
#ifdef _DEBUG
	fin.open("Debug\\x_conf.json", ifstream::in);
#else
	fin.open("x_conf.json", ifstream::in);
#endif

	ostringstream sout_temp;
	sout_temp << fin.rdbuf();
	string strConf(sout_temp.str());

	json_object *helper = json_object_new_object();
	helper = json_tokener_parse((char *)strConf.c_str());
	if(is_error(helper))
	{
		return -1;
	}
	m_ssId = json_object_get_int(json_object_object_get(json_object_object_get(helper,(char *)"CMSConf"), (char *)"id"));
	
	CXConfig::m_mcAddr = json_object_get_string(json_object_object_get(
							json_object_object_get(helper,(char *)"CMSConf"), (char *)"ip"));
	
	m_mcPort = json_object_get_int(json_object_object_get(json_object_object_get(helper,(char *)"CMSConf"), (char *)"port"));
	char http_url[128] = {0};
	sprintf(http_url, "http://%s:%d/controller/request", CXConfig::m_mcAddr.c_str(), m_mcPort);
	CXConfig::m_httpUrl = http_url;
	
	CXConfig::m_configType = json_object_get_string(json_object_object_get(
							json_object_object_get(helper,(char *)"CMSConf"), (char *)"type"));

	CXConfig::m_vodPath = json_object_get_string(json_object_object_get(
		json_object_object_get(helper,(char *)"CMSConf"), (char *)"vod_path"));
	
	json_object *server = json_object_object_get(helper,(char *)"Server");
	int server_num = json_object_array_length(server);
	for (int i=0; i<server_num; i++)
	{
		json_object *node = json_object_array_get_idx(server, i);
		
		J_ServerInfo info = {0};
		strcpy(info.stream_type, json_object_get_string(json_object_object_get(node, (char *)"stream_type")));
		info.stream_port = json_object_get_int(json_object_object_get(node, (char *)"stream_port"));
		strcpy(info.control_type, json_object_get_string(json_object_object_get(node, (char *)"control_type")));
		info.control_port = json_object_get_int(json_object_object_get(node, (char *)"control_port"));
		
		m_serverVec.push_back(info);
	}

	return 0;
}
