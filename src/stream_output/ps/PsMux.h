#ifndef __PS_MUX_H_
#define __PS_MUX_H_
#include "j_includes.h"
#include "x_time.h"
#include "ModuleManagerDef.h"

class CPsMux : public J_MuxFilter
{
public:
	CPsMux();
	~CPsMux();

	static int Maker(J_Obj *&pObj)
	{
		pObj = new CPsMux();
		return J_OK;
	}

public:
	virtual int Init();
	virtual void Deinit();
	virtual int Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen, void *pExtdata = 0);

private:
	int MakePESHead(char *pHead, int nDataLen, uint64_t timeStamp, bool isAudio = false);
	int MakePSHead(char *pHead, uint64_t timeStamp, int nRate);
	int MakePSMHead(char *pHead, bool isAudio = false);
	uint32_t GetTickCount();

private:
	int m_nSeqNum;
};

MUX_BEGIN_MAKER(ps)
	MUX_ENTER_MAKER("ps", CPsMux::Maker)
MUX_END_MAKER()

#endif //~__PS_MUX_H_
