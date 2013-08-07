#include "ControlManager.h"
#include "json.h"
#include "x_time.h"
#include "x_sdk_def.h"
#include "x_adapter_manager.h"
#include "x_parser_factory.h"

CControlManager::CControlManager()
{
	m_pCommandParser = NULL;
#ifndef WIN32
	signal(SIGPIPE, SIG_IGN);
#endif
}

CControlManager::~CControlManager()
{
	if (m_pCommandParser != NULL)
		JoParserFactory->DelParser(m_nPort);
}

j_result_t CControlManager::StartService(j_int32_t nPort, const j_char_t *pCommandType)
{
	m_nPort = nPort;
	m_serviceType = pCommandType;
	//m_asio.Init();
	m_asioData.ioAccept.peerPort = nPort;
	m_asioData.ioUser = this;
	m_asio.Listen(&m_asioData);
	
	m_pCommandParser = JoParserFactory->GetParser(nPort, pCommandType);
	if (m_pCommandParser == NULL)
		return J_UNKNOW;
		
	return J_OK;
}

j_result_t CControlManager::StopService()
{
	if (m_pCommandParser != NULL)
	{
		delete m_pCommandParser;
		m_pCommandParser = NULL;
	}
	//m_asio.Deinit();
	
	return J_OK;
}

///AsioUser
j_result_t CControlManager::OnAccept(const J_AsioDataBase *pAsioData, int nRet)
{
	j_socket_t nSocket;
	nSocket.sock = pAsioData->ioAccept.subHandle;
	//struct in_addr addr_in = {0};
	//addr_in.s_addr = pAsioData->ioAccept.peerIP;
	//m_pCommandParser->AddUser(nSocket, inet_ntoa(addr_in), pAsioData->ioAccept.peerPort);

	m_asio.AddUser(nSocket, this);
	J_AsioDataBase *pDataBase = new J_AsioDataBase;
	memset(pDataBase, 0, sizeof(J_AsioDataBase));
	pDataBase->ioRead.buf = new j_char_t[2048];
	if (m_serviceType == "mcsp")
	{
		pDataBase->ioRead.bufLen = -1;
		pDataBase->ioRead.whole = true;
		memcpy(pDataBase->ioRead.until_buf, "\r\n\r\n", 4);
	}
	else if(m_serviceType == "josp")
	{
		pDataBase->ioRead.bufLen = sizeof(J_CtrlHead);
		pDataBase->ioRead.whole = true;
	}
	pDataBase->ioUser = this;
	pDataBase->ioCall = J_AsioDataBase::j_read_e;
	pDataBase->ioHandle = nSocket.sock;
	m_asio.Read(nSocket, pDataBase);
	
	return J_OK;
}

j_result_t CControlManager::OnRead(const J_AsioDataBase *pAsioData, int nRet)
{
	J_AsioDataBase *pDataBase = new J_AsioDataBase;
	memset(pDataBase, 0, sizeof(J_AsioDataBase));
	pDataBase->ioCall = J_AsioDataBase::j_write_e;
	pDataBase->ioHandle = pAsioData->ioHandle;
	pDataBase->ioUser = this;
	j_result_t nResult = m_pCommandParser->ProcessRequest((J_AsioDataBase *)pAsioData, pDataBase);
	if (nResult == J_OK)
	{
		j_socket_t nSocket;
		nSocket.sock = pDataBase->ioHandle;
		m_asio.Write(pDataBase->ioHandle, pDataBase);
		if (pAsioData->ioRead.buf != NULL)
			delete pAsioData->ioRead.buf;
		delete pAsioData;
		
		J_AsioDataBase *pDataBase2 = new J_AsioDataBase;
		memset(pDataBase2, 0, sizeof(J_AsioDataBase));
		pDataBase2->ioRead.buf = new j_char_t[2048];
		if (m_serviceType == "mcsp")
		{
			pDataBase2->ioRead.bufLen = -1;
			pDataBase2->ioRead.whole = true;
			memcpy(pDataBase2->ioRead.until_buf, "\r\n\r\n", 4);
		}
		else if(m_serviceType == "josp")
		{
			pDataBase2->ioRead.bufLen = sizeof(J_CtrlHead);
			pDataBase2->ioRead.whole = true;
		}
		pDataBase2->ioUser = this;
		pDataBase2->ioCall = J_AsioDataBase::j_read_e;
		pDataBase2->ioHandle = nSocket.sock;
		m_asio.Read(nSocket, pDataBase2);
	}
	else
	{
		delete pDataBase;
		((J_AsioDataBase *)pAsioData)->ioRead.finishedLen = 0;
		m_asio.Read(pAsioData->ioHandle, (J_AsioDataBase *)pAsioData);
	}
	return J_OK;
}

j_result_t CControlManager::OnWrite(const J_AsioDataBase *pAsioData, int nRet)
{
	//printf("CControlManager::OnWrite %s\n", pAsioData->ioWrite.buf);
	if (pAsioData->ioWrite.buf != NULL)
		delete pAsioData->ioWrite.buf;

	delete pAsioData;
	return J_OK;
}

j_result_t CControlManager::OnBroken(const J_AsioDataBase *pAsioData, int nRet)
{
	J_OS::LOGINFO("CControlManager::OnBroken %d\n", pAsioData->ioHandle);
    m_pCommandParser->DelUser(pAsioData->ioHandle);
	m_asio.DelUser(pAsioData->ioHandle);
	return J_OK;
}
