#ifndef __AIPSTARPARSER_H_
#define __AIPSTARPARSER_H_
#include "j_includes.h"
#include "x_time.h"

class CAipstarParser : public J_MediaParser
{
public:
	CAipstarParser();
	~CAipstarParser();

public:
	///J_VideoParser
	virtual j_result_t Init(int nDataType);
	virtual j_result_t Deinit();
	virtual j_result_t InputData(const char *pData, int nLen);
	virtual j_result_t GetOnePacket(char *pData, J_StreamHeader &streamHeader);

private:

private:
};

#endif //~__AIPSTARPARSER_H_
