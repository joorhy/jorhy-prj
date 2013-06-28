#include "x_msg_queue.h"
#include "x_log.h"

CXMessageQueue::CXMessageQueue()
{
	j_thread_parm threadParm = {0};
	threadParm.entry = CXMessageQueue::RouteMessage;
	threadParm.data = this;
	m_msgThread.Create(threadParm);

	J_OS::LOGINFO("CXMessageQueue::CXMessageQueue created");
}

CXMessageQueue::~CXMessageQueue()
{
	m_msgThread.Release();

	J_OS::LOGINFO("CXMessageQueue::~CXMessageQueue detroyed");
}

int CXMessageQueue::RegistMessage(unsigned int nMsgType, MessageFunc pFunction, void *pUser)
{
	std::map<unsigned int, RegistInfo_t>::iterator it = m_msgMap.find(nMsgType);
	if (it == m_msgMap.end())
	{
		RegistInfo_t info;
		info.user = pUser;
		info.func = pFunction;
		m_msgMap[nMsgType] = info;

		return J_OK;
	}

	return J_EXIST;
}

int CXMessageQueue::ReleaseMessage(unsigned int nMsgType)
{
	std::map<unsigned int, RegistInfo_t>::iterator it = m_msgMap.find(nMsgType);
	if (it == m_msgMap.end())
		return J_NOT_EXIST;

	m_msgMap.erase(it);

	return J_OK;
}

int CXMessageQueue::PostMessage(unsigned int nMsgType, MessageType *pMessage)
{
	MessageInfo_t msgInfo;
	msgInfo.msgType = nMsgType;
	msgInfo.pMessage = pMessage;
	m_msgQue.push(msgInfo);

	return J_OK;
}

void CXMessageQueue::OnRouteMessage()
{
	while (true)
	{
		if(m_msgQue.empty())
		{
#ifdef WIN32
			Sleep(1);
#else
			usleep(10);
#endif
			continue;
		}

		MessageInfo_t info = m_msgQue.front();
		m_msgQue.pop();

		std::map<unsigned int, RegistInfo_t>::iterator it = m_msgMap.find(info.msgType);
		if (it == m_msgMap.end())
		{
			J_OS::LOGINFO("CMessageQueue::OnRouteMessage message not registed msgType = %d", info.msgType);
			continue;
		}

		if (it->second.user == NULL || it->second.func == NULL)
		{
			J_OS::LOGINFO("CMessageQueue::OnRouteMessage message RegisterInfo error");
			continue;
		}

		it->second.func(it->second.user, info.pMessage);
	}
}
