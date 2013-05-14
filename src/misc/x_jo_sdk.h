#ifndef __X_JO_SDK_H_
#define __X_JO_SDK_H_
#include "j_includes.h"
#include "x_singleton.h"

class CXJoSdk : public SingletonTmpl<CXJoSdk>
{
public:
	CXJoSdk(int) {}
	~CXJoSdk() {}
	
protected:
	CXJoSdk() {}
	
public:
	int MakeReqHeader(char *pBuff, char *pUserID, unsigned char byCmd, unsigned char byFlag, unsigned short sqNum, unsigned short exLength, unsigned char byRet = 0x00);
	int MakeRespHeader(char *pBuffer, uint8_t byCmd, uint16_t exLength, uint8_t byRet = 0x00);
};

#endif //~__X_JO_SDK_H_