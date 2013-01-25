#ifndef __X_MESSAGE_H_
#define __X_MESSAGE_H_
#include "x_msg_def.h"
#include "x_convert.h"

class BaseMessage
{
public:
	virtual ~BaseMessage() {}
	void SetMsgType(unsigned int nMsgType) { m_nMsgType = nMsgType; }
	unsigned int GetMsgType() { return m_nMsgType; }

private:
	unsigned int m_nMsgType;
};

template <typename R = void>
class MessageImpl : public BaseMessage
{
public:
	typedef R ReturnType;
	virtual ReturnType OnMessage(BaseConvert& convert) = 0;

protected:
	template <class T>
	static ReturnType ConvertImpl(T& message, BaseConvert& convert)
	{
		if (J_Convert<T, ReturnType> *p = dynamic_cast<J_Convert<T, ReturnType> *>(&convert))
		{
			return p->Convert(message);
		}
		return ReturnType();
	}
};

#define REGIST_MESSAGE() \
	virtual ReturnType OnMessage(BaseConvert& convert) \
	{ return ConvertImpl(*this, convert); }

#endif //~__X_MESSAGE_H_
