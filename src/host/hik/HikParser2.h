#ifndef __HIKPARSER2_H_
#define __HIKPARSER2_H_
#include "j_includes.h"
#include "x_time.h"
#include "faac.h"
#include "HikParserDef.h"

#define DATA_BUFFER_SIZE (1024 * 1024)
#define HIK_PACK_LENGHT(x) (((*(x + 3) & 0xFF) << 8) + (*(x + 2) & 0xFF))
#define HIK_PACK_LENGHT2(x) (((*(x + 2) & 0xFF) << 8) + (*(x + 3) & 0xFF) + 4)

class CHikParser2 : public J_MediaParser
{
public:
	CHikParser2();
	~CHikParser2();

public:
	///J_VideoParser
	virtual int Init(int nDataType = jo_video_normal);
	virtual int Deinit();
	virtual int InputData(const char *pData, int nLen);
	virtual int GetOnePacket(char *pData, J_StreamHeader &streamHeader);

private:
	int GetDataFlag();

private:
	J_OS::RWLocker_t m_rwLocker;

	HikStreamHead m_hikStreamHead;
	char *m_pOutBuff;
	bool m_bIsPrepared;
	bool m_bIsComplate;
	bool m_bPreComplate;
	j_uint32_t m_nDataLen;
	j_uint32_t m_nFrameLen;

	//音频解码
	unsigned int m_nSamples;
	short int *m_pAudioCache;
	faacEncHandle m_aacHandle;
	unsigned long m_nInputSamples;
	unsigned long m_nOutputBytes;
};

#endif //~__HIKPARSER2_H_