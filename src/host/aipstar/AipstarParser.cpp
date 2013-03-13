#include "AipstarParser.h"

CAipstarParser::CAipstarParser()
{

}

CAipstarParser::~CAipstarParser()
{

}

j_result_t CAipstarParser::Init(j_int32_t nDataType)
{
	return J_OK;
}

j_result_t CAipstarParser::Deinit()
{
	return J_OK;
}

j_result_t CAipstarParser::InputData(const j_char_t *pData, j_int32_t nLen)
{
	return J_OK;
}

int CAipstarParser::GetOnePacket(j_char_t *pData, J_StreamHeader &streamHeader)
{
	return J_OK;
}
