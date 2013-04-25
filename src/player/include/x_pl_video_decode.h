#pragma once
#include "x_pl_base.h"
#include "x_pl_common.h"
#include "x_pl_data_struct.h"

class J_PlVideoDecode : public J_PlBase
{
public:
	static J_PlVideoDecode* CreateInstance(int nCode);		//详见codec_id_e
	static void ReleaseInstance(J_PlVideoDecode **pInstance);

public:
	J_PlVideoDecode(void);
	~J_PlVideoDecode(void);
	
	//子类需要重写
	virtual J_PL_RESULT InitDecode() = 0;
	virtual J_PL_RESULT Decode(char *IN_buf,int In_len,char *OUT_buf,int *OUT_len) = 0;
	virtual J_PL_RESULT FlushBuffer() = 0;
	virtual J_PL_RESULT GetOutputType(j_pl_video_out_t &t) = 0;

protected:
	virtual J_PL_RESULT SetOutputType(j_pl_video_out_t &t) = 0;			//decode（）会自动调用

protected:
	int m_codeID;			//标志这个类的解码类型
	j_pl_video_out_t m_voutT;
};
