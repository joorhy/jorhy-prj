#ifndef __X_MSG_QUEUE_H_
#define __X_MSG_QUEUE_H_
#include "x_singleton.h"
#include "x_errtype.h"
#include "x_message.h"
#include "x_lock.h"
#include "x_thread.h"
#include "j_common.h"

typedef BaseMessage MessageType;
typedef struct MessageInfo
{
	unsigned int msgType;
	MessageType *pMessage;
	MessageInfo()
	{
		pMessage = NULL;
	}
}MessageInfo_t;
typedef void (*MessageFunc)(void *user, MessageType *pMessage);
typedef struct RegistInfo
{
	void *user;
	MessageFunc func;
	RegistInfo()
	{
		user = NULL;
		func = NULL;
	}
}RegistInfo_t;

class JO_API CXMessageQueue
{
public:
	CXMessageQueue();
	~CXMessageQueue();

public:
	///注册一个消息处理函数
	///@param nMsgType 消息类型
	///@param pFunction 消息处理函数
	///@return 参见x_error_type.h
	int RegistMessage(unsigned int nMsgType, MessageFunc pFunction, void *pUser);

	///取消一个消息处理函数
	///@param nMsgType 消息类型
	///@return 参见x_error_type.h
	int ReleaseMessage(unsigned int nMsgType);

	///投递消息,立刻返回
	///@param nMsgType 消息类型
	///@param pMessage 消息体
	///@return 参见x_error_type.h
	int PostMessage(unsigned int nMsgType, MessageType *pMessage);

private:
#ifdef WIN32
	static unsigned X_JO_API RouteMessage(void *pUser)
#else
	static void *RouteMessage(void *pUser)
#endif
	{
		(static_cast<CXMessageQueue *>(pUser))->OnRouteMessage();
		return 0;
	}
	void OnRouteMessage();

private:
	std::map<unsigned int, RegistInfo_t> m_msgMap;
	std::queue<MessageInfo_t> m_msgQue;

	int m_msgId;
	CJoThread m_msgThread;
	J_OS::CTLock m_locker;
};

#endif // ~__X_MSG_QUEUE_H_
