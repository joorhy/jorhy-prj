#ifndef __X_HTTP_HELPER_H_
#define __X_HTTP_HELPER_H_
#include "j_includes.h"

class JO_API CHttpHelper
{
public:
	CHttpHelper(const char *pRequest);
	~CHttpHelper();

public:
	std::string GetBody();

	int SetBody(char *pBody);
	int SetStatue(int nStatue = 200);

	char *GetString();
	int GetLength();
private:
	int ToString();

private:
	char m_strReqMessage[1024];
	int m_nStatue;
	std::string m_strBody;
	std::string m_strRespMessage;
};
#endif //~__X_HTTP_HELPER_H_
