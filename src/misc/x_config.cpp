#include "x_config.h"
#include "json.h"

using namespace std;

int CXConfig::m_mcPort = 6004;
char CXConfig::m_mcAddr[16];
int CXConfig::m_ssId = 0;
char CXConfig::m_httpUrl[64];
char CXConfig::m_configType[32];
std::vector<J_ServerInfo> CXConfig::m_serverVec;

CXConfig::CXConfig()
{
	memset(CXConfig::m_mcAddr, 0, sizeof(CXConfig::m_mcAddr));
	memset(CXConfig::m_httpUrl, 0, sizeof(CXConfig::m_httpUrl));
	memset(CXConfig::m_configType, 0, sizeof(CXConfig::m_configType));
}

CXConfig::~CXConfig()
{

}

int CXConfig::Init()
{
	fstream fin;
	fin.open("x_conf.json", ifstream::in);

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
	
	std::string cms_addr = json_object_get_string(json_object_object_get(
							json_object_object_get(helper,(char *)"CMSConf"), (char *)"ip"));
	memcpy(CXConfig::m_mcAddr, cms_addr.c_str(), cms_addr.length());
	
	m_mcPort = json_object_get_int(json_object_object_get(json_object_object_get(helper,(char *)"CMSConf"), (char *)"port"));
	sprintf(CXConfig::m_httpUrl, "http://%s:%d/controller/request", CXConfig::m_mcAddr, m_mcPort);
	
	std::string cms_type = json_object_get_string(json_object_object_get(
							json_object_object_get(helper,(char *)"CMSConf"), (char *)"type"));
	memcpy(CXConfig::m_configType, cms_type.c_str(), cms_type.length());
	
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
