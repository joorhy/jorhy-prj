#include "StreamManager.h"
#include "RealMediaObj.h"
#include "VodMediaObj.h"
#include "VoiceIcomObj.h"
#include "x_filter_factory.h"
#include "x_filereader_factory.h"

CStreamManager::CStreamManager()
{
	signal(SIGPIPE, SIG_IGN);
}

CStreamManager::~CStreamManager()
{

}

int CStreamManager::StartService(int nPort, const char *pType)
{
	m_serviceType = pType;
	CRdAsio::Instance()->Init();
	m_asioData.ioAccept.peerPort = nPort;
	m_asioData.ioUser = this;
	CRdAsio::Instance()->Listen(m_asioData);
	
	return J_OK;
}

int CStreamManager::StopService()
{
	CRdAsio::Instance()->Deinit();
	return J_OK;
}

void CStreamManager::OnAccept(const J_AsioDataBase &asioData, int nRet)
{
	j_socket_t nSocket;
	nSocket.sock = asioData.ioAccept.subHandle;
	CRdAsio::Instance()->AddUser(nSocket, this);
	J_AsioDataBase *pDataBase = new J_AsioDataBase;
	pDataBase->ioRead.buf = new j_char_t[1024];
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
	
	ClientInfo info;
	info.pAsioData = pDataBase;
	info.pObj = NULL;
	m_clientMap[nSocket.sock] = info;
	CRdAsio::Instance()->Read(nSocket, *pDataBase);
}

void CStreamManager::OnRead(const J_AsioDataBase &asioData, int nRet)
{
	ClientMap::iterator it = m_clientMap.find(asioData.ioHandle);
	if (it == m_clientMap.end())
	{
		J_OS::LOGINFO("CStreamManager::OnRead No Client");
		return;
	}

	if (ParserRequest(asioData, it->second.pObj) < 0)
		return;
}

void CStreamManager::OnWrite(const J_AsioDataBase &asioData, int nRet)
{
	ClientMap::iterator it = m_clientMap.find(asioData.ioHandle);
	if (it == m_clientMap.end())
		return;

	int nResult = J_OK;
	J_MediaObj *pClient = dynamic_cast<J_MediaObj *>(it->second.pObj);
	if (pClient != NULL)
	{
		nResult = pClient->Process((J_AsioDataBase &)asioData);
		if (nResult == J_OK)
		{
			CRdAsio::Instance()->Write(asioData.ioHandle, (J_AsioDataBase &)asioData);
		}
		else
		{
			J_OS::LOGINFO("CStreamManager::OnWrite error %d", nResult);
		}
	}
	else
	{
		J_OS::LOGINFO("CStreamManager::OnWrite No Client");
		return;
	}
}

void CStreamManager::OnBroken(const J_AsioDataBase &asioData, int nRet)
{
	ClientMap::iterator it = m_clientMap.find(asioData.ioHandle);
	if (it == m_clientMap.end())
		return;

	if (it->second.pObj != NULL)
	{
		it->second.pObj->Clearn();
		delete it->second.pObj;
		it->second.pObj = NULL;
	}

	m_clientMap.erase(it);
	CRdAsio::Instance()->DelUser(asioData.ioHandle);
}

int CStreamManager::ParserRequest(const J_AsioDataBase &asioData, J_MediaObj *pClient)
{
	ClientMap::iterator itClient = m_clientMap.find(asioData.ioHandle);
	if (itClient == m_clientMap.end())
		return J_UNKNOW;
		
	int nRet = J_OK;
	J_RequestFilter *protocolFilter = CFilterFactory::Instance()->GetFilter(asioData.ioHandle, m_serviceType.c_str());
	if (protocolFilter == NULL)
	{
		return J_PARAM_ERROR;
	}

	if ((nRet = protocolFilter->Parser((J_AsioDataBase &)asioData)) == J_OK)
	{
		nRet = ProcessCommand(asioData, protocolFilter, pClient);
	}
	else
	{
		ClientMap::iterator it = m_clientMap.find(asioData.ioHandle);
		if (it == m_clientMap.end())
			return nRet;
			
		/*if(nRet == J_WIAT_NEXT_CMD && m_serviceType == "josp")
		{
			nRet = ProcessCommand(asioData, protocolFilter, pClient);
		}*/
		CRdAsio::Instance()->Read(asioData.ioHandle, (J_AsioDataBase &)asioData);
	}

	return nRet;
}

int CStreamManager::ProcessCommand(const J_AsioDataBase &asioData, J_Obj *pObj, J_MediaObj *pClient)
{
	int nRet = J_OK;
	ClientMap::iterator itClient = m_clientMap.find(asioData.ioHandle);
	if (itClient == m_clientMap.end())
		return J_UNKNOW;
		
	J_CommandFilter *videoCommand = dynamic_cast<J_CommandFilter *>(pObj);
	if (videoCommand != NULL && pClient == NULL)
	{
		switch (videoCommand->GetCommandType())
		{
			case jo_start_real:
			{
				itClient->second.pObj = new CRealMediaObj(asioData.ioHandle, videoCommand->GetStreamType(), pObj);
				j_string_t resid = videoCommand->GetResid();
				ResidMap::iterator it = m_residMap.find(resid);
				if (it == m_residMap.end())
				{
					std::vector<j_socket_t> vecResid;
					m_residMap[resid] = vecResid;
					m_residMap[resid].push_back(asioData.ioHandle);
				}
				else
				{
					it->second.push_back(asioData.ioHandle);
				}
			}
				break;
			case jo_start_vod:
				itClient->second.pObj = new CVodMediaObj(asioData.ioHandle, pObj);
				break;
			case jo_start_voice:
				itClient->second.pObj = new CVoiceIcomObj(asioData.ioHandle, pObj);
				break;
			default:
				//assert(false);
				break;
		}
		pClient = itClient->second.pObj;
	}

	nRet = pClient->Process((J_AsioDataBase &)asioData);
	if (nRet < 0)
	{
		J_OS::LOGINFO("CStreamManager::ProcessCommand Process Error");
		return nRet;
	}

	J_AsioDataBase *pAsioData = new J_AsioDataBase;
	J_RequestFilter *protocolFilter = dynamic_cast<J_RequestFilter *>(pObj);
	if ((nRet = protocolFilter->Complete(*pAsioData)) < 0)
	{
		/*if (nRet == J_WIAT_NEXT_CMD)
		{
			pAsioData->ioUser = this;
			CRdAsio::Instance()->Write(asioData.ioHandle, (J_AsioDataBase&)*pAsioData);
			return J_OK;
		}*/
			
		J_OS::LOGERROR("CStreamManager::ProcessCommand Send Header error");
		return J_SOCKET_ERROR;
	}
	pAsioData->ioUser = this;
	CRdAsio::Instance()->Write(asioData.ioHandle, (J_AsioDataBase&)*pAsioData);
	
	pClient->Run();
	if (IS_CLOSE_CMD(videoCommand->GetCommandType()))
		return J_ON_CLOSE;

	return J_OK;
}

