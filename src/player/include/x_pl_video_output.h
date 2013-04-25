#pragma once
#include "x_pl_base.h"
#include "x_pl_common.h"
#include "x_pl_data_struct.h"
#include <windows.h>

class CXPlVideoOutput : public J_PlBase
{
public:
	static CXPlVideoOutput *CreateInstance(j_pl_video_out_t &t);
	static void ReleaseInstance(CXPlVideoOutput **pInstance);
	J_PL_RESULT GetVoutParm(j_pl_video_out_t &OUT_t);

	virtual J_PL_RESULT Display() = 0;
	virtual J_PL_RESULT PrepareData(char *IN_buf,int IN_len) = 0;
	virtual J_PL_RESULT SetHwnd(HWND hwnd) = 0;
	virtual J_PL_RESULT GetHwnd(HWND &hwnd) = 0;

protected:
	CXPlVideoOutput(j_pl_video_out_t &t);
	~CXPlVideoOutput(void);


	int m_voutID;			//标志这个类的解码类型
	j_pl_video_out_t m_parm;

};
