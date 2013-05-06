#pragma once
#include "x_pl_base.h"
#include "x_pl_common.h"
#include "x_pl_data_struct.h"

class CXPlAudioDecode : public J_PlBase
{
public:
	static CXPlAudioDecode* CreateInstance(int nCode);		//详见codec_id_e
	static void ReleaseInstance(CXPlAudioDecode **pInstance);

public:
	CXPlAudioDecode(void);
	~CXPlAudioDecode(void);

	virtual J_PL_RESULT Decode(char *IN_buf,int In_len,char *OUT_buf,int *OUT_len) = 0;
	virtual J_PL_RESULT GetOutputType(j_pl_audio_out_t &t) = 0;

protected:
	int m_codeID;			//标志这个类的解码类型
};
