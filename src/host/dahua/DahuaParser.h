#ifndef __DAHUAPARSER_H_
#define __DAHUAPARSER_H_
#include "j_includes.h"
#include "x_time.h"
#include "dhstreamparse.h"

class CDahuaParser : public J_MediaParser
{
public:
	CDahuaParser();
	~CDahuaParser();

public:
	///J_VideoParser
	virtual int Init(int nDataType = jo_video_normal);
	virtual int Deinit();
	virtual int InputData(const char *pData, int nLen);
	virtual int GetOnePacket(char *pData, J_StreamHeader &streamHeader);

private:
	PARSERHANDLE m_parser;
	DH_FRAME_INFO *m_frame;
	j_uint32_t m_frameNum;
};

#endif //~__DAHUAPARSER_H_
