#ifndef __LIVEPARSER_H_
#define __LIVEPARSER_H_
#include "j_includes.h"
#include "x_time.h"

extern "C"
{
#include "x264.h"
};

class CLiveParser : public J_MediaParser
{
public:
	CLiveParser();
	~CLiveParser();

public:
	///J_VideoParser
	virtual int Init(int nDataType);
	virtual int Deinit();
	virtual int InputData(const char *pData, int nLen);
	virtual int GetOnePacket(char *pData, J_StreamHeader &streamHeader);

private:
	int encode(x264_t* pX264Handle, x264_picture_t* pPicIn, x264_picture_t* pPicOut);

private:
	x264_t *m_pX264Handle;
	x264_param_t *m_pX264Param;

	int m_iNal;
	x264_nal_t *m_pNals;

	x264_picture_t *m_pPicIn;
	x264_picture_t *m_pPicOut;

	J_OS::RWLocker_t m_rwLocker;
	char *m_pDataBuff;
	int m_nDataSize;
	int m_dateType;
};

#endif //~__LIVEPARSER_H_
