#ifndef __HIKPARSER_H_
#define __HIKPARSER_H_
#include "j_includes.h"
#include "x_time.h"
#include "Hikv3ParserDef.h"

#define DATA_BUFFER_SIZE (1024 * 1024)

class CHikv3Parser : public J_MediaParser
{
public:
	CHikv3Parser();
	~CHikv3Parser();

public:
	///J_MediaParser
	virtual int Init(int nDataType = jo_video_normal);
	virtual int Deinit();
	virtual int InputData(const char *pData, int nLen);
	virtual int GetOnePacket(char *pData, J_StreamHeader &streamHeader);

private:
	J_OS::RWLocker_t m_rwLocker;
	void *m_hNewHandle;
	int m_nDataSize;
};

#endif //~__HIKPARSER_H_
