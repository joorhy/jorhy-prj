#pragma once
#include "x_pl_base.h"
#include "x_pl_record.h"
#include "stdio.h"

#define PAT_INTERVAL			30
#define PCR_INTERVAL			10
#define TS_DATA_LEN			188
#define TS_MAX_PAYLOAD_LEN	184
#define TS_NEED_CUT_LEN		183
#define TS_PAYLOAD_CUT_LEN	92

class CXPlRecordTs : public CXPlRecord
{
public:
	CXPlRecordTs(int nID);
	~CXPlRecordTs();

public:
	virtual J_PL_RESULT Start(char *filename);
	virtual J_PL_RESULT InputData(char *IN_buf,int In_len, int nType, long long timeStamp);
	virtual J_PL_RESULT Stop();

private:
	int MakePESHead(char *pHead, int nDataLen, UINT64 timeStamp, bool isAudio = false);
	int MakePAT(char *pHead);
	int MakePMT(char *pHead);
	int MakePCR(char *pHead, UINT64 timeStamp);
	int MakePacket(char *pHead, const char *pInputData, int nLen, bool bIsAudio = false, bool bIsStart = false);

private:
	FILE *m_pFile;
	bool n_bNeedIframe;

	int m_nPATCounter;
	int m_nPMTCounter;
	int m_nPCRCounter;
	int m_nVideoCounter;
	int m_nAudioCounter;
	int m_nFrameNum;
};