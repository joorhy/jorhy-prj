#include "x_pl_input.h"
#include "x_pl_error.h"
#include "x_pl_control.h"
#include "x_pl_default_config.h"
#include "x_pl_log.h"

CXPlInput::CXPlInput(void)
{
	m_access	= NULL;
	m_control	= NULL;
	m_demux		= NULL;
	m_buffer	= NULL;
	j_pl_info("CXPlInput::CXPlInput()\n");
}

CXPlInput::~CXPlInput(void)
{
	J_PlAccess::ReleaseInstance(&m_access);
	J_PlDemux::ReleaseInstance(&m_demux);
	J_PlBuffer::ReleaseInstance(&m_buffer);
}

J_PL_RESULT CXPlInput::Init(j_pl_cfg_t &cfg,void *control)
{
	m_control = control;
	m_access = J_PlAccess::CreateInstance(cfg);
	if(m_access == NULL)
		return J_PL_ERROR_ACCESS_CREATE;

	J_PL_RESULT br = InitDemux();
	if(br != J_PL_NO_ERROR)
		return br;

	return J_PL_NO_ERROR;
}

unsigned CXPlInput::Thread(void *pdata)
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	CXPlInput *pThis = reinterpret_cast<CXPlInput*>(pdata);
	if(pThis)
	{
		J_PlControl *ctl = reinterpret_cast<J_PlControl*>(pThis->m_control);
		if(ctl)
		{
			//br = pThis->InitDemux();
			//if(br != J_PL_NO_ERROR)
			//{
			//	int state = J_PL_ERROR;
			//	ctl->m_state->SetVariable(&state);
			//	return br;
			//}

			br = pThis->InitDecoder();			//额外产生两个线程
			if(br != J_PL_NO_ERROR)
			{
				int state = J_PL_ERROR;
				ctl->m_state->SetVariable(&state);
				return br;
			}
			
			ctl->m_switch.Single();
			if(ctl->m_WorkModel == J_PL_PLAY_REALTIME)
				br = pThis->ThreadLoopPush();
			else
				br = pThis->ThreadLoopPull();

			br = ctl->CallBackStop();
		}
	}
	
	return br;
}

J_PL_RESULT CXPlInput::Run()
{
	J_PL_RESULT br;
	m_threadParm.data = this;
	m_threadParm.entry= CXPlInput::Thread;
	m_threadParm.priority = 0; 
	br = m_thread.Create(m_threadParm);

	return br;
}

J_PL_RESULT CXPlInput::ThreadLoopPush()
{
	J_PL_RESULT br = J_PL_NO_ERROR;

	J_PlControl *ctl = reinterpret_cast<J_PlControl*>(m_control);
	char *accessdata = new char[m_access->GuessBufferSize()];
	int readlen = 0;
	int state = J_PL_PALYING;
	++(*ctl->m_ThreadNumer);
	ctl->m_state->SetVariable(&state);

	while(true)
	{
		ctl->m_state->GetVariable(&state);
		//j_pl_info("ThreadLoopPush()\n");
		switch(state)
		{
		case J_PL_NORMAL: break;
		case J_PL_PALYING:
		case J_PL_PAUSE:
			//ctl->m_switch.Wait();
			br = m_access->ReadBlock(accessdata,readlen);
			if(br == J_PL_ERROR_ACCESS_END)
			{
				state = J_PL_ERROR;
				ctl->m_state->SetVariable(&state);
				break;
			}
			else if(br == J_PL_ERROR_ACCESS_ERROR)
			{
				state = J_PL_ERROR;
				ctl->m_state->SetVariable(&state);
				break;
			}
			br = m_demux->DemuxBlock(accessdata,m_buffer);			//demux
			//if(br != J_PL_NO_ERROR)
			//	Sleep(30);
			break;
		case J_PL_END: 
			goto Input_End;
			break;
		case J_PL_ERROR:
			if(ctl->m_pEndCBK)					//回调
				ctl->m_pEndCBK(ctl->m_pEndData);
			goto Input_End;
			break;
		}
	}
Input_End:
	delete accessdata;
	j_pl_info("Input Thread Exit : %d\tbr=%d\n",GetCurrentThreadId(),br);
	ctl->m_AllClose.Post();
	return br;
}

J_PL_RESULT CXPlInput::InitDemux()
{
	J_PL_RESULT br;
	if(!m_access)
		return J_PL_ERROR_ACCESS_CREATE;

	j_pl_demux_t demux_parm;
	br = m_access->GetDemuxType(demux_parm);					//输出一个产生demux的参数
	if(br != J_PL_NO_ERROR)
	{
		j_pl_error("No Demux Type\n");
		return br;
	}
	
	J_PlControl *ctl = reinterpret_cast<J_PlControl*>(m_control);
	int size = 0;
	if(ctl->m_WorkModel == J_PL_PLAY_REALTIME)
		size = BUFFER_INPUT;
	else
		size = demux_parm.height * demux_parm.width * demux_parm.iframe_interval;

	m_buffer = J_PlBuffer::CreateInstance(BUFFER_FIFO,size);		//智能判断buffer大小
	if (!m_buffer)
		return J_PL_ERROR_UNKNOW;

	m_demux = J_PlDemux::CreateInstance(demux_parm);
	
	if(!m_demux)
	{
		j_pl_error("No Such Demux\n");
		return J_PL_ERROR_DEMUX_CREATE;
	}

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlInput::InitDecoder()
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	J_PlControl *control = reinterpret_cast<J_PlControl*>(m_control);
	if(!control)
		return J_PL_ERROR_CONTROL;
	if(!m_demux)
		return J_PL_ERROR_DEMUX_CREATE;

	j_pl_transform_t parm;
	br = m_demux->GetDecodeType(parm);
	if(br != J_PL_NO_ERROR)
	{
		j_pl_error("CXPlInput::InitDecoder Error Demux!\n");
		return br;
	}
	control->m_tansfm = new CXPlTransform(parm,m_control);
	control->m_tansfm->Run();			//开始decode线程
	return br;
}

J_PL_RESULT CXPlInput::RequestData()
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	br = m_access->RequestData(24 * 60 * 60 * 1000);
	if (br != J_PL_NO_ERROR)
		return br;

	//m_pullSwitch.Single();
	return br;
}

J_PL_RESULT CXPlInput::ControlAccess(int type,va_list args)
{
	if(!m_access)
		return J_PL_ERROR_ACCESS_ERROR;

	return m_access->Control(type,args);
}

J_PL_RESULT CXPlInput::ThreadLoopPull()
{
	J_PL_RESULT br = J_PL_NO_ERROR;

	J_PlControl *ctl = reinterpret_cast<J_PlControl*>(m_control);
	char *accessdata = new char[m_access->GuessBufferSize()];
	int readlen = 0;
	int state = J_PL_PALYING;
	if (RequestData() == J_PL_NO_ERROR)
	{
		++(*ctl->m_ThreadNumer);
		ctl->m_state->SetVariable(&state);
	}
	else
	{
		state = J_PL_ERROR;
		ctl->m_state->SetVariable(&state);
	}

	while(true)
	{
		m_pullSwitch.WaitTime(2000);
		//j_pl_info("m_pullSwitch.Wait()\n");
		ctl->m_state->GetVariable(&state);
		switch(state)
		{
		case J_PL_NORMAL: break;

		case J_PL_PALYING:
		case J_PL_PAUSE:
			br = m_access->ReadBlock(accessdata,readlen);
			if(br == J_PL_ERROR_ACCESS_END)
			{
				state = J_PL_ERROR;
				ctl->m_state->SetVariable(&state);
				break;
			}
			else if(br == J_PL_ERROR_ACCESS_ERROR)
			{
				state = J_PL_END;
				ctl->m_state->SetVariable(&state);
				break;
			}

			br = m_demux->DemuxBlock(accessdata,m_buffer);			//demux
			break;

		case J_PL_END: 
			goto Input_End2;
			break;

		case J_PL_ERROR: 
			goto Input_End2;
			break;

		}
		m_pullSwitch.Unsingle();
	}
Input_End2:
	delete accessdata;
	j_pl_info("Pull Input Thread Exit : %d\tbr=%d\n",GetCurrentThreadId(),br);
	ctl->m_AllClose.Post();
	return br;
}