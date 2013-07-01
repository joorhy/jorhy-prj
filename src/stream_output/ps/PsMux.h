#ifndef __PS_MUX_H_
#define __PS_MUX_H_
#include "j_includes.h"
#include "x_time.h"
#include "x_module_manager_def.h"

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
	int MakePESHead(char *pHead, int nDataLen, j_uint64_t timeStamp, bool isAudio = false);
	int MakePSHead(char *pHead, j_uint64_t timeStamp, int nRate);
	int MakePSMHead(char *pHead, bool isAudio = false);
	j_uint32_t GetTickCount();

private:
	int m_nSeqNum;
};

#endif //~__PS_MUX_H_
