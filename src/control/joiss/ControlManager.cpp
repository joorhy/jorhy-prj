#include "ControlManager.h"
#include "json.h"
#include "x_time.h"
#include "x_sdk_def.h"
#include "x_adapter_manager.h"
#include "x_parser_factory.h"

#include <uuid.h>

CControlManager::CControlManager()
{
	m_pCommandParser = NULL;
}

CControlManager::~CControlManager()
{
	if (m_pCommandParser != NULL)
		CParserFactory::Instance()->DelParser(m_nPort);
}

int CControlManager::StartService(int nPort, const char *pCommandType)
{
	m_nPort = nPort;
	m_pCommandParser = CParserFactory::Instance()->GetParser(nPort, pCommandType);
	if (m_pCommandParser == NULL)
		return J_UNKNOW;
		
	return Start(nPort);
}

int CControlManager::StopService()
{
	if (m_pCommandParser != NULL)
	{
		delete m_pCommandParser;
		m_pCommandParser = NULL;
	}
	return Stop();
}

///CXService
int CControlManager::OnAccept(int nSocket, const char *pAddr, short nPort)
{
	m_pCommandParser->AddUser(nSocket, pAddr, nPort);
	return J_OK;
}

int CControlManager::OnRead(int nSocket)
{
	int write_len = 0;
	char *write_buff = NULL;
	m_pCommandParser->ProcessRequest(nSocket, write_buff, write_len);
	if (write_len > 0)
	{
		J_OS::CTCPSocket writeSocket(nSocket);
        writeSocket.Write_n(write_buff, write_len);
		delete write_buff;
	}

	return J_OK;
}

int CControlManager::OnWrite(int nSocket)
{
	usleep(1000);
	return J_OK;
}

int CControlManager::OnBroken(int nSocket)
{
    m_pCommandParser->DelUser(nSocket);
	return J_OK;
}
