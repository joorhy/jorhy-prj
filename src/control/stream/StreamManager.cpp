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
	//注册消息回调函数
	CXMessageQueue::Instance()->RegistMessage(MSG_MEDIA, CStreamManager::OnMessage, this);
	m_serviceType = pType;
	
	return Start(nPort);
}

int CStreamManager::StopService()
{
	//取消消息回调函数
	CXMessageQueue::Instance()->ReleaseMessage(MSG_MEDIA);

	return Stop();
}

int CStreamManager::OnAccept(int nSocket, const char *pAddr, short nPort)
{
	m_clientMap[nSocket] = NULL;

	return J_OK;
}

int CStreamManager::OnRead(int nSocket)
{
	std::map<int, J_MediaObj *>::iterator it = m_clientMap.find(nSocket);
	if (it == m_clientMap.end())
	{
		J_OS::LOGINFO("CStreamManager::OnRead No Client");
		return J_NOT_EXIST;
	}

	if (ParserRequest(nSocket, it->second) < 0)
	{
		return J_UNKNOW;
	}

	return J_OK;
}

int CStreamManager::OnWrite(int nSocket)
{
	std::map<int, J_MediaObj *>::iterator it = m_clientMap.find(nSocket);
	if (it == m_clientMap.end())
	{
		return J_NOT_EXIST;
	}

	int nRet = J_OK;
	J_MediaObj *pClient = dynamic_cast<J_MediaObj *>(it->second);
	if (pClient != NULL)
	{
		nRet = pClient->Process(jo_io_write);
		if (nRet < 0)
			J_OS::LOGERROR("CStreamManager::OnWrite Error");
	}
	else
	{
		usleep(1);
		//J_OS::LOGINFO("CStreamManager::OnWrite No Client");
		//return J_NOT_EXIST;
		return J_OK;
	}

	return nRet;
}

int CStreamManager::OnBroken(int nSocket)
{
	std::map<int, J_MediaObj *>::iterator it = m_clientMap.find(nSocket);
	if (it == m_clientMap.end())
	{
		return J_NOT_EXIST;
	}

	if (it->second != NULL)
	{
		it->second->Clearn();
		delete it->second;
		it->second = NULL;
	}

	m_clientMap.erase(it);

	return J_OK;
}

int CStreamManager::GetSocketByResid(const char *pResid)
{
	ResidMap::iterator it = m_residMap.find(pResid);
	if (it != m_residMap.end())
	{
		if (!it->second.empty())
		{
			int nSocket = it->second.back();
			it->second.pop_back();

			if (it->second.empty())
				m_residMap.erase(it);

			return nSocket;
		}
		return 0;
	}

	return 0;
}

int CStreamManager::ParserRequest(int nSocket, J_MediaObj *pClient)
{
	int nRet = J_OK;
	J_RequestFilter *protocolFilter = CFilterFactory::Instance()->GetFilter(nSocket, m_serviceType.c_str());
	if (protocolFilter == NULL)
	{
		return J_PARAM_ERROR;
	}

	if (protocolFilter->Parser(nSocket) == J_OK)
	{
		nRet = ProcessCommand(nSocket, protocolFilter, pClient);
	}

	return nRet;
}

int CStreamManager::ProcessCommand(int nSocket, J_Obj *pObj, J_MediaObj *pClient)
{
	int nRet = J_OK;
	J_CommandFilter *videoCommand = dynamic_cast<J_CommandFilter *>(pObj);
	if (videoCommand != NULL && pClient == NULL)
	{
		switch (videoCommand->GetCommandType())
		{
			case jo_start_real:
			{
				m_clientMap[nSocket] = new CRealMediaObj(nSocket, videoCommand->GetStreamType(), pObj);
				std::string resid = videoCommand->GetResid();
				ResidMap::iterator it = m_residMap.find(resid);
				if (it == m_residMap.end())
				{
					std::vector<int> vecResid;
					m_residMap[resid] = vecResid;
					m_residMap[resid].push_back(nSocket);
				}
				else
				{
					it->second.push_back(nSocket);
				}
			}
				break;
			case jo_start_vod:
				m_clientMap[nSocket] = new CVodMediaObj(nSocket, pObj);
				break;
			case jo_start_voice:
				m_clientMap[nSocket] = new CVoiceIcomObj(nSocket, pObj);
				break;
			default:
				assert(false);
				break;
		}
		pClient = m_clientMap[nSocket];
	}

	nRet = pClient->Process(jo_io_read);
	if (nRet < 0)
	{
		J_OS::LOGINFO("CStreamManager::ProcessCommand Process Error");
		return nRet;
	}

	J_RequestFilter *protocolFilter = dynamic_cast<J_RequestFilter *>(pObj);
	if (protocolFilter->Complete(nSocket) < 0)
	{
		J_OS::LOGERROR("CStreamManager::ProcessCommand Send Header error");
		return J_SOCKET_ERROR;
	}

	pClient->Run();
	if (IS_CLOSE_CMD(videoCommand->GetCommandType()))
		return J_ON_CLOSE;

	return J_OK;
}

void CStreamManager::ProcMessage(BaseMessage *pMessage)
{
	MessageImpl<std::string> *pMsgImpl = dynamic_cast<MessageImpl<std::string> *>(pMessage);
	if (pMsgImpl != NULL)
	{
		int nSocket = 0;
		CMediaConvert mediaConvert;
		while ((nSocket = GetSocketByResid(
				pMsgImpl->OnMessage(mediaConvert).c_str())) > 0)
		{
			RECLock(m_locker);
			Broken(nSocket, m_evListen);
			VecSocket::iterator it = m_vecSocket.begin();
			for (; it != m_vecSocket.end(); it++)
			{
				if ((*it).fd == nSocket)
				{
					m_vecSocket.erase(it);
					break;
				}
			}
			RECUnlock(m_locker);
		}
	}
	delete pMessage;
}

