#ifndef __X_MSG_QUEUE_H_
#define __X_MSG_QUEUE_H_
#include "x_singleton.h"
#include "x_errtype.h"
#include "x_message.h"
#include "x_lock.h"

#include <map>
#include <queue>
#include <pthread.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>

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

class CXMessageQueue : public SingletonTmpl<CXMessageQueue>
{
public:
	CXMessageQueue(int);
	~CXMessageQueue();

protected:
    CXMessageQueue() {}

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
	static void *RouteMessage(void *pUser)
	{
		(static_cast<CXMessageQueue *>(pUser))->OnRouteMessage();
		return (void *)0;
	}
	void OnRouteMessage();

private:
	std::map<unsigned int, RegistInfo_t> m_msgMap;
	std::queue<MessageInfo_t> m_msgQue;

	int m_msgId;
	pthread_t m_msgThread;
	J_OS::CTLock m_locker;
};

#endif // ~__X_MSG_QUEUE_H_
