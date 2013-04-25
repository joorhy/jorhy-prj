#pragma once
#include "x_pl_base.h"
#include "x_pl_common.h"

#define DECLARE_AOUT(id) m_aoutID = id

class CXPlAudioOutput : public J_PlBase
{
public:
	static CXPlAudioOutput* CreateInstance(int nCode);		//详见codec_id_e
	static void ReleaseInstance(CXPlAudioOutput **pInstance);

public:
	CXPlAudioOutput(void);
	~CXPlAudioOutput(void);
	
	virtual J_PL_RESULT Display(char *IN_buf,int IN_len) = 0;

protected:
	int m_aoutID;			//标志这个类的解码类型
};
