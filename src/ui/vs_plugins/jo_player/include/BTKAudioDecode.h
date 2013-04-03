#pragma once
#include "btkbase.h"
#include "BTKCommon.h"
#include "DataStruct.h"

class BTKAudioDecode : public BTKBase
{
public:
	static BTKAudioDecode* CreateInstance(int nCode);		//详见codec_id_e
	static void ReleaseInstance(BTKAudioDecode **pInstance);

public:
	BTKAudioDecode(void);
	~BTKAudioDecode(void);

	virtual BTK_RESULT Decode(char *IN_buf,int In_len,char *OUT_buf,int *OUT_len) = 0;
	virtual BTK_RESULT GetOutputType(btk_audio_out_t &t) = 0;

protected:
	int m_codeID;			//标志这个类的解码类型
};
