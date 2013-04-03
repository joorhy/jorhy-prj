#pragma once
#include "btkbase.h"
#include "BTKCommon.h"
#include <windows.h>
#include "DataStruct.h"

class BTKVideoOutput : public BTKBase
{
public:
	static BTKVideoOutput *CreateInstance(btk_video_out_t &t);
	static void ReleaseInstance(BTKVideoOutput **pInstance);
	BTK_RESULT GetVoutParm(btk_video_out_t &OUT_t);

	virtual BTK_RESULT Display() = 0;
	virtual BTK_RESULT PrepareData(char *IN_buf,int IN_len) = 0;
	virtual BTK_RESULT SetHwnd(HWND hwnd) = 0;
	virtual BTK_RESULT GetHwnd(HWND &hwnd) = 0;

protected:
	BTKVideoOutput(btk_video_out_t &t);
	~BTKVideoOutput(void);


	int m_voutID;			//标志这个类的解码类型
	btk_video_out_t m_parm;

};
