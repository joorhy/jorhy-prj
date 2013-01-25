#ifndef __AIRONIXPARSER_H_
#define __AIRONIXPARSER_H_
#include "j_includes.h"
#include "x_time.h"

class CAironixParser : public J_MediaParser
{
public:
	CAironixParser();
	~CAironixParser();

public:
	///J_VideoParser
	virtual int Init(int nDataType);
	virtual int Deinit();
	virtual int InputData(const char *pData, int nLen);
	virtual int GetOnePacket(char *pData, J_StreamHeader &streamHeader);

private:

private:
};

#endif //~__AIRONIXPARSER_H_
