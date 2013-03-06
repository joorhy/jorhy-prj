#ifndef __SONYPARSER_H_
#define __SONYPARSER_H_
#include "j_includes.h"
#include "x_time.h"

#define DATA_BUFFER_SIZE (1024 * 1024)

class CSonyParser : public J_MediaParser
{
public:
	CSonyParser();
	~CSonyParser();

public:
	///J_VideoParser
	virtual int Init(int nDataType = jo_video_normal);
	virtual int Deinit();
	virtual int InputData(const char *pData, int nLen);
	virtual int GetOnePacket(char *pData, J_StreamHeader &streamHeader);

private:
	//J_OS::RWLocker_t m_rwLocker;
	char *m_pDataBuff;
	int m_nDataSize;
	int m_nSeqNum;
};
#endif //~__SONYPARSER_H_
