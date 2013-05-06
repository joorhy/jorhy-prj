#include "x_pl_video_decode.h"
#include "x_pl_decode_h264.h"

J_PlVideoDecode::J_PlVideoDecode(void)
{
}

J_PlVideoDecode::~J_PlVideoDecode(void)
{
}

J_PlVideoDecode *J_PlVideoDecode::CreateInstance(int nCode)
{
	J_PlVideoDecode *pInstance = NULL;
	switch(nCode)
	{
	case CODE_H264: 
		pInstance = new CXPlDecodeH264();
		break;
	}

	return pInstance;
}

void J_PlVideoDecode::ReleaseInstance(J_PlVideoDecode **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;
	switch((*pInstance)->m_codeID)
	{
	case CODE_H264:
		delete (CXPlDecodeH264*)(*pInstance);
		*pInstance = NULL;
		return;
	}
}
