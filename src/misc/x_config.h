#ifndef __X_CONFIG_H_
#define __X_CONFIG_H_
#include "j_includes.h"

#include <vector>

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
	static int Init();
	static int GetStreamServerId() { return m_ssId; }
	static char *GetMCServerAddr() { return m_mcAddr; }
	static int GetMCServerPort() { return m_mcPort; }
	static char *GetUrl() { return m_httpUrl; }
	static char *GetConfigType() { return m_configType; }
	static std::vector<J_ServerInfo> &GetServerInfo() { return m_serverVec; }

private:
	static char m_mcAddr[16];
	static int m_mcPort;
	static int m_ssId;
	static char m_httpUrl[64];
	static char m_configType[32];
	
	static std::vector<J_ServerInfo> m_serverVec;
};

#endif //~__X_CONFIG_H_
