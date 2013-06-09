#include "x_pl_control.h"
#include "x_pl_default_config.h"
#include "x_pl_parser.h"
#include "x_pl_data_def.h"
#include "x_pl_log.h"
#include "x_pl_record.h"

J_PlControl::J_PlControl(void)
{
	int i_int;
	j_pl_mtime_t i_64;
	bool b_bool;

	i_int			= J_PL_NORMAL;
	m_state			= new J_PlVariable(J_PL_VAR_INT,&i_int);

	i_64			= 0;
	m_displayTime	= new J_PlVariable(J_PL_VAR_INT64,&i_64);

	i_int			= 0;
	m_ThreadNumer	= new J_PlVariable(J_PL_VAR_INT,&i_int);

	b_bool			= true;
	m_bForward		= new J_PlVariable(J_PL_VAR_BOOL,&b_bool);

	i_int			= J_PL_SPEED_NORMAL;
	m_speed			= new J_PlVariable(J_PL_VAR_INT,&i_int);
	
	b_bool			= false;
	m_bSleep		= new J_PlVariable(J_PL_VAR_BOOL,&b_bool);

	m_input = NULL;
	m_tansfm = NULL;
	m_render = NULL;

	m_pEndCBK		= NULL;
	m_pEndData		= NULL;

	ResetCBK();
}

J_PlControl::~J_PlControl(void)
{
	m_SafeClose.Wait();
	int state = J_PL_NORMAL;
	m_state->GetVariable(&state);
	if(state == J_PL_PALYING || state == J_PL_PAUSE)
	{
		Stop();
	}

	delete m_state;
	delete m_displayTime;
	delete m_ThreadNumer;
	delete m_bForward;
	delete m_speed;
	delete m_bSleep;
}

J_PL_RESULT J_PlControl::InitPlayByNetwork(const char *psz_mrl,j_pl_work_type model)
{
	if(!psz_mrl)
		return J_PL_ERROR_MRL;

	m_WorkModel = model;
	
	J_PL_RESULT br = J_PL_NO_ERROR;
	j_pl_cfg_t cfg;
	br = J_PlParser::ParseUrl((char*)psz_mrl,cfg);
	if(br != J_PL_NO_ERROR)
		return br;
	cfg.i_real	= m_WorkModel;

	m_input = new CXPlInput();
	br = m_input->Init(cfg,this);
	if(br != J_PL_NO_ERROR)
	{
		delete m_input;
		m_input = NULL;
		j_pl_error("Can not Open input : %s\n",psz_mrl);
		return br;
	}
	j_pl_info("Open input:%s success\n",psz_mrl);
	return J_PL_NO_ERROR;
}

J_PL_RESULT J_PlControl::InitPlayByPath(const char *psz_mrl,j_pl_work_type model)
{
	if(!psz_mrl)
		return J_PL_ERROR_MRL;

	m_WorkModel = model;

	return J_PL_NO_ERROR;
}


J_PL_RESULT J_PlControl::SetHwnd(HWND hwnd)
{
	if(m_input == NULL)
		return J_PL_ERROR_UNKNOW;
	if(m_render == NULL)
		m_render = new CXPlRender(this);			//实例

	return m_render->SetHwnd(hwnd);
}

J_PL_RESULT J_PlControl::Run()
{
	if(m_input == NULL || m_render == NULL)
		return J_PL_ERROR_UNKNOW;
	//m_switch.Single();

	return m_input->Run();
}

J_PL_RESULT J_PlControl::Stop()
{
	if(!IsPlaying())
		return J_PL_NO_ERROR;

	int state = J_PL_END;
	m_pDisplayCBK = NULL;
	m_switch.Single();
	m_state->SetVariable(&state);
	m_FrameSwitch.Single();

	//m_SafeClose.Wait();

	return J_PL_NO_ERROR;
}

J_PL_RESULT J_PlControl::Pause()
{
	int state = J_PL_NORMAL;
	m_state->GetVariable(&state);
	if(state == J_PL_PALYING)
	{
		state = J_PL_PAUSE;
		m_state->SetVariable(&state);
		m_switch.Unsingle();
	}
	else if(state == J_PL_PAUSE)
	{
		PlayNextFrame();
		state = J_PL_PALYING;
		m_state->SetVariable(&state);
		m_switch.Single();
	}

	return J_PL_NO_ERROR;
}

J_PL_BOOL J_PlControl::IsPlaying()
{
	int state = J_PL_NORMAL;
	if(m_state)
	{
		m_state->GetVariable(&state);
		if(state == J_PL_PALYING || state == J_PL_PAUSE)
			return J_PL_TRUE;
	}
	return J_PL_FALSE;
}

J_PL_RESULT J_PlControl::SetDisplayCBK(j_pl_entry_display_t pCBK,void *pUser)
{
	if(!pCBK)
		return J_PL_ERROR_PTR;

	m_pDisplayCBK	= pCBK;
	m_pDisplayData	= pUser;

	return J_PL_NO_ERROR;
}

void J_PlControl::ResetCBK()
{
	m_pDisplayCBK	= NULL;
	m_pDisplayData	= NULL;
}

J_PL_RESULT J_PlControl::PlayNextFrame()
{
	int state = J_PL_NORMAL;
	m_state->GetVariable(&state);
	if(state != J_PL_PAUSE)
	{
		state = J_PL_PAUSE;
		m_state->SetVariable(&state);
	}
	else if(state == J_PL_PAUSE)
		m_switch.Single();

	m_FrameSwitch.Single();
	return J_PL_NO_ERROR;
}

J_PL_RESULT J_PlControl::Snapshot(char *path_name)
{
	J_PL_RESULT br;
	if(m_render)
		br = m_render->TakeSnapshot(path_name);
	if(br != J_PL_NO_ERROR)
		return br;

	j_pl_warn("TakeSnapshot location=%s\n",path_name);

	return J_PL_NO_ERROR;
}

J_PL_RESULT J_PlControl::ToggelRecord(char *path_name)
{
	J_PL_RESULT br;
	CXPlRecord record;
	br = record.Start(path_name);
	if(br != J_PL_NO_ERROR)
		return br;

	return J_PL_NO_ERROR;
}

J_PL_RESULT J_PlControl::SetPlayDirection(bool bFront)
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	if(m_WorkModel == J_PL_PLAY_FILE)
	{
		bool Forward = true;
		br = m_bForward->GetVariable(&Forward);
		if(br)
		{
			if(Forward != bFront)
			{
				br = m_tansfm->SetDirection(bFront); //和当前播放模式不一样才设置
				br = m_input->ControlAccess(ACCESS_SET_BACKRUN,(va_list)&bFront);
			}
		}
	}

	return br;
}

J_PL_RESULT J_PlControl::SetSpeed(j_pl_speed e)
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	switch(e)
	{
	case J_PL_SPEED_SLOWEST:
	case J_PL_SPEED_SLOWER:
	case J_PL_SPEED_SLOW:
	case J_PL_SPEED_NORMAL:
	case J_PL_SPEED_FAST:
	case J_PL_SPEED_FASTER:
	case J_PL_SPEED_FASTEST:
		br = m_speed->SetVariable(&e);	
		br = m_input->ControlAccess(ACCESS_SET_SPEED,(va_list)&e);
		break;
	}

	return br;
}

J_PL_RESULT J_PlControl::SetTime(j_pl_mtime_t time)
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	if(m_WorkModel == J_PL_PLAY_FILE)
	{
		br = m_render->SetTime(time);
	}

	return br;
}

J_PL_RESULT J_PlControl::ToggelBackRun(bool bEnable)
{
	return J_PL_NO_ERROR;
}

J_PL_RESULT J_PlControl::SetVolume(int volume)
{
	return J_PL_NO_ERROR;
}

J_PL_RESULT J_PlControl::GetVolume(int &volume)
{
	return J_PL_NO_ERROR;
}

J_PL_RESULT J_PlControl::GetState(int &state)
{
	if(m_state)
	{
		m_state->GetVariable(&state);
	}
	return J_PL_NO_ERROR;
}

J_PL_RESULT J_PlControl::CallBackStop()
{
	int num = 0;
	m_ThreadNumer->GetVariable(&num);

	for (int i=0; i<num; ++i)
	{
		m_AllClose.Wait();
	}

	if(m_input != NULL)
	{
		delete m_input;
		m_input = NULL;
	}
	if(m_tansfm != NULL)
	{
		delete m_tansfm;
		m_tansfm = NULL;
	}
	if(m_render != NULL)
	{
		delete m_render;
		m_render = NULL;
	}

	m_ThreadNumer->ZeroVariable();
	m_state->ZeroVariable();
	m_displayTime->ZeroVariable();

	ResetCBK();

	m_SafeClose.Post();

	return J_PL_NO_ERROR;
}

void J_PlControl::SleepPlayer(bool bEnable)
{
	if(m_bSleep)
	{
		m_bSleep->SetVariable(&bEnable);
	}
}

J_PL_RESULT J_PlControl::GetHwnd(HWND &hwnd)
{
	if(m_render)
		return m_render->GetHwnd(hwnd);
}

J_PL_RESULT J_PlControl::SetEndCBK(j_pl_entry_end_t pCBK,void *pUser)
{
	if(!pCBK)
		return J_PL_ERROR_PTR;

	m_pEndCBK	= pCBK;
	m_pEndData	= pUser;

	return J_PL_NO_ERROR;
}