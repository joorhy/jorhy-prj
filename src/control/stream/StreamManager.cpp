#include "StreamManager.h"
#include "RealMediaObj.h"
#include "VodMediaObj.h"
#include "VoiceIcomObj.h"
#include "x_filter_factory.h"
#include "x_filereader_factory.h"

CStreamManager::CStreamManager()
{
#ifndef WIN32
	signal(SIGPIPE, SIG_IGN);
#endif
}

CStreamManager::~CStreamManager()
{

}

int CStreamManager::StartService(int nPort, const char *pType)
{
	m_serviceType = pType;
	//m_asio.Init();
	memset(&m_asioData, 0, sizeof(m_asioData));
	m_asioData.ioAccept.peerPort = nPort;
	m_asioData.ioUser = this;
	m_asio.Listen(&m_asioData);
	
	return J_OK;
}

int CStreamManager::StopService()
{
	//m_asio.Deinit();
	return J_OK;
}

j_result_t CStreamManager::OnAccept(const J_AsioDataBase *pAsioData, int nRet)
{
	j_socket_t nSocket;
	nSocket.sock = pAsioData->ioAccept.subHandle;
	m_asio.AddUser(nSocket, this);
	J_AsioDataBase *pDataBase = new J_AsioDataBase;
	memset(pDataBase, 0, sizeof(J_AsioDataBase));
	pDataBase->ioRead.buf = new j_char_t[1024];
	pDataBase->ioRead.finishedLen = 0;
	if (m_serviceType == "http")
	{
		pDataBase->ioRead.bufLen = 1024;
		pDataBase->ioRead.whole = false;
	}
	else if(m_serviceType == "josp")
	{
		pDataBase->ioRead.bufLen = sizeof(J_CtrlHead);
		pDataBase->ioRead.whole = true;
	}
	pDataBase->ioUser = this;
	pDataBase->ioCall = J_AsioDataBase::j_read_e;
	
	ClientInfo info;
	info.pAsioData = pDataBase;
	info.pObj = NULL;
	m_clientMap[nSocket.sock] = info;
	m_asio.Read(nSocket, pDataBase);
	
	return J_OK;
}

j_result_t CStreamManager::OnRead(const J_AsioDataBase *pAsioData, int nRet)
{
	ClientMap::iterator it = m_clientMap.find(pAsioData->ioHandle);
	if (it == m_clientMap.end())
	{
		J_OS::LOGINFO("CStreamManager::OnRead No Client");
		return J_NOT_FOUND;
	}

	return ParserRequest(pAsioData, it->second.pObj);
}

j_result_t CStreamManager::OnWrite(const J_AsioDataBase *pAsioData, int nRet)
{
	ClientMap::iterator it = m_clientMap.find(pAsioData->ioHandle);
	if (it == m_clientMap.end())
		return J_NOT_FOUND;

	int nResult = J_UNKNOW;
	J_MediaObj *pClient = dynamic_cast<J_MediaObj *>(it->second.pObj);
	if (pClient != NULL)
	{
		J_AsioDataBase *pDataBase = new J_AsioDataBase;
		memset(pDataBase, 0, sizeof(J_AsioDataBase));
		pDataBase->ioCall = J_AsioDataBase::j_write_e;
		pDataBase->ioHandle = pAsioData->ioHandle;
		pDataBase->ioUser = this;
		while (pDataBase->ioWrite.bufLen <= 0)
		{
			nResult = pClient->Process(*pDataBase);
			j_sleep(1);
		}
		if (nResult == J_OK)
		{
			m_asio.Write(pDataBase->ioHandle, pDataBase);
		}
		else
		{
			J_OS::LOGINFO("CStreamManager::OnWrite error %d", nResult);
		}
		delete pAsioData;
	}
	else
	{
		J_OS::LOGINFO("CStreamManager::OnWrite No Client");
	}
	return nResult;
}

j_result_t CStreamManager::OnBroken(const J_AsioDataBase *pAsioData, int nRet)
{
	J_OS::LOGINFO("OnBroken");
	ClientMap::iterator it = m_clientMap.find(pAsioData->ioHandle);
	if (it == m_clientMap.end())
		return J_UNKNOW;

	if (it->second.pObj != NULL)
	{
		it->second.pObj->Clearn();
		delete it->second.pObj;
		it->second.pObj = NULL;
	}

	m_clientMap.erase(it);
	m_asio.DelUser(pAsioData->ioHandle);
	return J_OK;
}

int CStreamManager::ParserRequest(const J_AsioDataBase *pAsioData, J_MediaObj *pClient)
{
	ClientMap::iterator itClient = m_clientMap.find(pAsioData->ioHandle);
	if (itClient == m_clientMap.end())
		return J_UNKNOW;
		
	int nRet = J_OK;
	J_RequestFilter *protocolFilter = JoFilterFactory->GetFilter(pAsioData->ioHandle, m_serviceType.c_str());
	if (protocolFilter == NULL)
	{
		return J_PARAM_ERROR;
	}

	if ((nRet = protocolFilter->Parser((J_AsioDataBase &)*pAsioData)) == J_OK)
	{
		nRet = ProcessCommand(pAsioData, protocolFilter, pClient);
	}
	else
	{
		ClientMap::iterator it = m_clientMap.find(pAsioData->ioHandle);
		if (it == m_clientMap.end())
			return nRet;
			
		((J_AsioDataBase *)pAsioData)->ioRead.finishedLen = 0;
		m_asio.Read(pAsioData->ioHandle, (J_AsioDataBase *)pAsioData);
		nRet = J_OK;
	}

	return nRet;
}

int CStreamManager::ProcessCommand(const J_AsioDataBase *pAsioData, J_Obj *pObj, J_MediaObj *pClient)
{
	int nRet = J_OK;
	ClientMap::iterator itClient = m_clientMap.find(pAsioData->ioHandle);
	if (itClient == m_clientMap.end())
		return J_UNKNOW;
		
	J_CommandFilter *videoCommand = dynamic_cast<J_CommandFilter *>(pObj);
	if (videoCommand != NULL && pClient == NULL)
	{
		switch (videoCommand->GetCommandType())
		{
			case jo_start_real:
			{
				itClient->second.pObj = new CRealMediaObj(pAsioData->ioHandle, videoCommand->GetStreamType(), pObj);
				j_string_t resid = videoCommand->GetResid();
				ResidMap::iterator it = m_residMap.find(resid);
				if (it == m_residMap.end())
				{
					std::vector<j_socket_t> vecResid;
					m_residMap[resid] = vecResid;
					m_residMap[resid].push_back(pAsioData->ioHandle);
				}
				else
				{
					it->second.push_back(pAsioData->ioHandle);
				}
			}
				break;
			case jo_start_vod:
				itClient->second.pObj = new CVodMediaObj(pAsioData->ioHandle, pObj);
				break;
			case jo_start_voice:
				itClient->second.pObj = new CVoiceIcomObj(pAsioData->ioHandle, pObj);
				break;
			default:
				//assert(false);
				break;
		}
		pClient = itClient->second.pObj;
	}

	nRet = pClient->Process((J_AsioDataBase &)*pAsioData);
	if (nRet < 0)
	{
		J_OS::LOGINFO("CStreamManager::ProcessCommand Process Error");
		return nRet;
	}

	J_AsioDataBase *pDataBase = new J_AsioDataBase;
	memset(pDataBase, 0, sizeof(J_AsioDataBase));
	J_RequestFilter *protocolFilter = dynamic_cast<J_RequestFilter *>(pObj);
	if ((nRet = protocolFilter->Complete(*pDataBase)) < 0)
	{
		delete pDataBase;
			
		J_OS::LOGERROR("CStreamManager::ProcessCommand Send Header error");
		return J_SOCKET_ERROR;
	}
	pDataBase->ioUser = this;
	pDataBase->ioHandle = pAsioData->ioHandle;
	pDataBase->ioCall = J_AsioDataBase::j_write_e;
	m_asio.Write(pDataBase->ioHandle, pDataBase);
	
	pClient->Run();
	if (IS_CLOSE_CMD(videoCommand->GetCommandType()))
		return J_ON_CLOSE;

	return J_OK;
}

