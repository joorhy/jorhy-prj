#include "..\include\BTKInput.h"
#include "..\include\BTKError.h"
#include "..\include\BTKControl.h"
#include "..\include\DefaultConfig.h"
#include "..\include\BTKLog.h"

BTKInput::BTKInput(void)
{
	m_access	= NULL;
	m_control	= NULL;
	m_demux		= NULL;
	m_buffer	= NULL;
}

BTKInput::~BTKInput(void)
{
	BTKAccess::ReleaseInstance(&m_access);
	BTKDemux::ReleaseInstance(&m_demux);
	BTKBuffer::ReleaseInstance(&m_buffer);
}

BTK_RESULT BTKInput::Init(btk_cfg_t &cfg,void *control)
{
	m_control = control;
	m_access = BTKAccess::CreateInstance(cfg);
	if(m_access == NULL)
		return BTK_ERROR_ACCESS_CREATE;

	BTK_RESULT br = InitDemux();
	if(br != BTK_NO_ERROR)
		return br;

	return BTK_NO_ERROR;
}

unsigned BTKInput::Thread(void *pdata)
{
	BTK_RESULT br = BTK_NO_ERROR;
	BTKInput *pThis = reinterpret_cast<BTKInput*>(pdata);
	if(pThis)
	{
		BTKControl *ctl = reinterpret_cast<BTKControl*>(pThis->m_control);
		if(ctl)
		{
			//br = pThis->InitDemux();
			//if(br != BTK_NO_ERROR)
			//{
			//	int state = BTK_ERROR;
			//	ctl->m_state->SetVariable(&state);
			//	return br;
			//}

			br = pThis->InitDecoder();			//额外产生两个线程
			if(br != BTK_NO_ERROR)
			{
				int state = BTK_ERROR;
				ctl->m_state->SetVariable(&state);
				return br;
			}
			
			ctl->m_switch.Single();
			if(ctl->m_WorkModel == BTK_PLAY_REALTIME)
				br = pThis->ThreadLoopPush();
			else
				br = pThis->ThreadLoopPull();

			br = ctl->CallBackStop();
		}
	}
	
	return br;
}

BTK_RESULT BTKInput::Run()
{
	BTK_RESULT br;
	m_threadParm.data = this;
	m_threadParm.entry= BTKInput::Thread;
	m_threadParm.priority = 0; 
	br = m_thread.Create(m_threadParm);

	return br;
}

BTK_RESULT BTKInput::ThreadLoopPush()
{
	BTK_RESULT br = BTK_NO_ERROR;

	BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
	char *accessdata = new char[m_access->GuessBufferSize()];
	int readlen = 0;
	int state = BTK_PALYING;
	++(*ctl->m_ThreadNumer);
	ctl->m_state->SetVariable(&state);

	while(true)
	{
		ctl->m_state->GetVariable(&state);

		switch(state)
		{
		case BTK_NORMAL: break;
		case BTK_PALYING:
		case BTK_PAUSE:
			ctl->m_switch.Wait();
			br = m_access->ReadBlock(accessdata,readlen);
			if(br == BTK_ERROR_ACCESS_END)
			{
				state = BTK_ERROR;
				ctl->m_state->SetVariable(&state);
				break;
			}
			else if(br == BTK_ERROR_ACCESS_ERROR)
			{
				state = BTK_ERROR;
				ctl->m_state->SetVariable(&state);
				break;
			}
			br = m_demux->DemuxBlock(accessdata,m_buffer);			//demux
			if(br != BTK_NO_ERROR)
				Sleep(30);
			break;
		case BTK_END: 
			goto Input_End;
			break;
		case BTK_ERROR:
			if(ctl->m_pEndCBK)					//回调
				ctl->m_pEndCBK(ctl->m_pEndData);
			goto Input_End;
			break;
		}
	}
Input_End:
	delete accessdata;
	btk_Info("Input Thread Exit : %d\tbr=%d\n",GetCurrentThreadId(),br);
	ctl->m_AllClose.Post();
	return br;
}

BTK_RESULT BTKInput::InitDemux()
{
	BTK_RESULT br;
	if(!m_access)
		return BTK_ERROR_ACCESS_CREATE;

	btk_demux_t demux_parm;
	br = m_access->GetDemuxType(demux_parm);					//输出一个产生demux的参数
	if(br != BTK_NO_ERROR)
	{
		btk_Error("No Demux Type\n");
		return br;
	}
	
	BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
	int size = 0;
	if(ctl->m_WorkModel == BTK_PLAY_REALTIME)
		size = BUFFER_INPUT;
	else
		size = demux_parm.height * demux_parm.width * demux_parm.iframe_interval;

	m_buffer = BTKBuffer::CreateInstance(BUFFER_FIFO,size);		//智能判断buffer大小
	if (!m_buffer)
		return BTK_ERROR_UNKNOW;

	m_demux = BTKDemux::CreateInstance(demux_parm);
	
	if(!m_demux)
	{
		btk_Error("No Such Demux\n");
		return BTK_ERROR_DEMUX_CREATE;
	}

	return BTK_NO_ERROR;
}

BTK_RESULT BTKInput::InitDecoder()
{
	BTK_RESULT br = BTK_NO_ERROR;
	BTKControl *control = reinterpret_cast<BTKControl*>(m_control);
	if(!control)
		return BTK_ERROR_CONTROL;
	if(!m_demux)
		return BTK_ERROR_DEMUX_CREATE;

	btk_transform_t parm;
	br = m_demux->GetDecodeType(parm);
	if(br != BTK_NO_ERROR)
	{
		btk_Error("Error Demux!\n");
		return br;
	}
	control->m_tansfm = new BTKTransform(parm,m_control);
	control->m_tansfm->Run();			//开始decode线程
	return br;
}

BTK_RESULT BTKInput::ControlAccess(int type,va_list args)
{
	if(!m_access)
		return BTK_ERROR_ACCESS_ERROR;

	return m_access->Control(type,args);
}

BTK_RESULT BTKInput::ThreadLoopPull()
{
	BTK_RESULT br = BTK_NO_ERROR;

	BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
	char *accessdata = new char[m_access->GuessBufferSize()];
	int readlen = 0;
	int state = BTK_NORMAL;
	++(*ctl->m_ThreadNumer);

	while(true)
	{
		m_pullSwitch.Wait();
		ctl->m_state->GetVariable(&state);

		switch(state)
		{
		case BTK_NORMAL: break;

		case BTK_PALYING:
		case BTK_PAUSE:
			br = m_access->ReadBlock(accessdata,readlen);
			if(br == BTK_ERROR_ACCESS_END)
			{
				state = BTK_ERROR;
				ctl->m_state->SetVariable(&state);
				break;
			}
			else if(br == BTK_ERROR_ACCESS_ERROR)
			{
				state = BTK_END;
				ctl->m_state->SetVariable(&state);
				break;
			}

			br = m_demux->DemuxBlock(accessdata,m_buffer);			//demux
			if(br != BTK_NO_ERROR)
				Sleep(30);
			break;

		case BTK_END: 
			goto Input_End2;
			break;

		case BTK_ERROR: 
			goto Input_End2;
			break;

		}
		m_pullSwitch.Unsingle();
	}
Input_End2:
	delete accessdata;
	btk_Info("Pull Input Thread Exit : %d\tbr=%d\n",GetCurrentThreadId(),br);
	ctl->m_AllClose.Post();
	return br;
}