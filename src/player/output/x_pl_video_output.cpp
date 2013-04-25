#include "x_pl_video_output.h"
#include "x_pl_error.h"
#include "x_pl_vout_ddraw.h"

CXPlVideoOutput::CXPlVideoOutput(j_pl_video_out_t &t)
{
	m_parm = t;
}

CXPlVideoOutput::~CXPlVideoOutput(void)
{
}


CXPlVideoOutput *CXPlVideoOutput::CreateInstance(j_pl_video_out_t &t)
{
	CXPlVideoOutput *pInstance = NULL;
	switch(t.VoutDev)
	{
		case J_PL_DDRAW: pInstance = new CXPlVoutDDraw(t); 
			break;
	}

	return pInstance;

}

void CXPlVideoOutput::ReleaseInstance(CXPlVideoOutput **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;

	switch((*pInstance)->m_parm.VoutDev)
	{
	case J_PL_DDRAW: 
		delete (CXPlVoutDDraw*)(*pInstance);
		*pInstance = NULL;
		break;
	}

}

J_PL_RESULT CXPlVideoOutput::GetVoutParm(j_pl_video_out_t &OUT_t)
{
	OUT_t = m_parm;
	return J_PL_NO_ERROR;
}