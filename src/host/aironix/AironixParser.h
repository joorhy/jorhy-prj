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
	virtual j_result_t Init(j_int32_t nDataType);
	virtual j_result_t Deinit();
	virtual j_result_t InputData(const j_char_t *pData, j_int32_t nLen);
	virtual j_result_t GetOnePacket(j_char_t *pData, J_StreamHeader &streamHeader);

private:

private:
};

#endif //~__AIRONIXPARSER_H_
