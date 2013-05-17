#ifndef __X_ICONV_H_
#define __X_ICONV_H_
#include <iconv.h>
#include <string>

typedef std::string string_t;
class CXIconv
{
public:
	CXIconv();
	~CXIconv();

public:
	int SetVersion(int nVersion) { m_nVersion = nVersion; return 0; }
	int Wsf2str(const char *pContent, int nLen, string_t &strMessage);
	int Str2wsf(const string_t &strMessage, char *pContent, int &nLen, bool isMarking = true);

private:
	int GetMarking(const char *pContent, int nOffset, bool &isMarking, char byMark[4]);
	int GetDataLength(const char *pContent, int &nLength, int &nOffset);
	string_t GetStr(const char *pContent, bool isMarking, char byMark[4], int nPayloadLen);

private:
	int m_nVersion;
};

#endif //~__X_ICONV_H_
