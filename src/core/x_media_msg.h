#ifndef __X_MEDIA_MSG_H_
#define __X_MEDIA_MSG_H_
#include "x_message.h"
#include "x_convert.h"

class CMediaMessage : public MessageImpl<std::string>
{
public:
	REGIST_MESSAGE()

	CMediaMessage();
	~CMediaMessage();

public:
	void SetResid(const char *pResid) { m_resid = pResid; }
	std::string GetResid() { return m_resid; }

private:
	std::string m_resid;
};

class CMediaConvert : public BaseConvert,
							 public J_Convert<CMediaMessage, std::string>
{
public:
	std::string Convert(CMediaMessage&);
};

#endif //~__X_MEDIA_MSG_H_
