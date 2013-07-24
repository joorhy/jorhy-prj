#ifndef __X_CONFIG_H_
#define __X_CONFIG_H_
#include "j_includes.h"

#include <vector>
#include <string>

#ifdef WIN32
#ifdef   JO_CONF_EXPORTS 
#define   JO_CONF_API           __declspec(dllexport) 
#else 
#define   JO_CONF_API           __declspec(dllimport) 
#endif 
#else
#define JO_CONF_API  
#endif

struct J_ServerInfo
{
	char stream_type[16];
	int stream_port;
	char control_type[16];
	int control_port;
};

class CXConfig
{
public:
	CXConfig();
	~CXConfig();

public:
	static JO_CONF_API  int Init();
	static JO_CONF_API int GetStreamServerId() { return m_ssId; }
	static JO_CONF_API const char *GetMCServerAddr() { return m_mcAddr.c_str(); }
	static JO_CONF_API int GetMCServerPort() { return m_mcPort; }
	static JO_CONF_API const char *GetUrl() { return m_httpUrl.c_str(); }
	static JO_CONF_API const char *GetConfigType() { return m_configType.c_str(); }
	static JO_CONF_API const char *GetVodPath() { return m_vodPath.c_str(); }
	static JO_CONF_API std::vector<J_ServerInfo> &GetServerInfo() { return m_serverVec; }

private:
	static std::string m_mcAddr;
	static int m_mcPort;
	static int m_ssId;
	static std::string m_httpUrl;
	static std::string m_configType;
	static std::string m_vodPath;
	
	static std::vector<J_ServerInfo> m_serverVec;
};

#endif //~__X_CONFIG_H_
