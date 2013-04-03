#pragma once
#include "btkbase.h"
#include "BTKCommon.h"

#define DECLARE_AOUT(id) m_aoutID = id

class BTKAudioOutput : public BTKBase
{
public:
	static BTKAudioOutput* CreateInstance(int nCode);		//详见codec_id_e
	static void ReleaseInstance(BTKAudioOutput **pInstance);

public:
	BTKAudioOutput(void);
	~BTKAudioOutput(void);
	
	virtual BTK_RESULT Display(char *IN_buf,int IN_len) = 0;

protected:
	int m_aoutID;			//标志这个类的解码类型
};
