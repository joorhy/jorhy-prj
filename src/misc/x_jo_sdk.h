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
	int MakeReqHeader(j_char_t *pBuff, j_char_t *pUserID, j_uint8_t byCmd, j_uint8_t byFlag, j_uint16_t sqNum, j_uint16_t exLength, j_uint8_t byRet = 0x00);
	int MakeRespHeader(j_char_t *pBuffer, j_uint8_t byCmd, j_uint16_t exLength, j_uint8_t byRet = 0x00);
};

#endif //~__X_JO_SDK_H_