#ifndef __JOSMUX_H_
#define __JOSMUX_H_
#include "j_includes.h"
#include "x_module_manager_def.h"

class CJosMux : public J_MuxFilter
{
public:
	CJosMux();
	~CJosMux();

	static int Maker(J_Obj *&pObj)
	{
		pObj = new CJosMux();
		return J_OK;
	}

public:
	virtual int Init();
	virtual void Deinit();
	virtual int Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen, void *pExtdata = 0);

private:
	int m_nFrameSeq;
};

#endif //~__JOSMUX_H_
