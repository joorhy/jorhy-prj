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
	virtual int Init(int nDataType);
	virtual int Deinit();
	virtual int InputData(const char *pData, int nLen);
	virtual int GetOnePacket(char *pData, J_StreamHeader &streamHeader);

private:

private:
};

#endif //~__AIPSTARPARSER_H_
