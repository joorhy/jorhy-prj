#include "..\include\BTKControl.h"
#include "..\include\DefaultConfig.h"
#include "..\include\BTKParser.h"
#include "..\include\DataDef.h"
#include "..\include\BTKLog.h"
#include "..\include\BTKRecord.h"

BTKControl::BTKControl(void)
{
	int i_int;
	btk_mtime_t i_64;
	bool b_bool;

	i_int			= BTK_NORMAL;
	m_state			= new BTKVariable(BTK_VAR_INT,&i_int);

	i_64			= 0;
	m_displayTime	= new BTKVariable(BTK_VAR_INT64,&i_64);

	i_int			= 0;
	m_ThreadNumer	= new BTKVariable(BTK_VAR_INT,&i_int);

	b_bool			= true;
	m_bForward		= new BTKVariable(BTK_VAR_BOOL,&b_bool);

	i_int			= BTK_SPEED_NORMAL;
	m_speed			= new BTKVariable(BTK_VAR_INT,&i_int);
	
	b_bool			= false;
	m_bSleep		= new BTKVariable(BTK_VAR_BOOL,&b_bool);

	m_input = NULL;
	m_tansfm = NULL;
	m_render = NULL;

	m_pEndCBK		= NULL;
	m_pEndData		= NULL;

	ResetCBK();
}

BTKControl::~BTKControl(void)
{
	int state = BTK_NORMAL;
	m_state->GetVariable(&state);
	if(state == BTK_PALYING || state == BTK_PAUSE)
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

BTK_RESULT BTKControl::InitPlayByNetwork(const char *psz_mrl,btk_work_type model)
{
	if(!psz_mrl)
		return BTK_ERROR_MRL;

	m_WorkModel = model;
	
	BTK_RESULT br = BTK_NO_ERROR;
	btk_cfg_t cfg;
	br = BTKParser::ParseUrl((char*)psz_mrl,cfg);
	if(br != BTK_NO_ERROR)
		return br;
	cfg.i_real	= m_WorkModel;

	m_input = new BTKInput();
	br = m_input->Init(cfg,this);
	if(br != BTK_NO_ERROR)
	{
		delete m_input;
		m_input = NULL;
		btk_Error("Can not Open input : %s\n",psz_mrl);
		return br;
	}
	btk_Info("Open input:%s success\n",psz_mrl);
	return BTK_NO_ERROR;
}

BTK_RESULT BTKControl::InitPlayByPath(const char *psz_mrl,btk_work_type model)
{
	if(!psz_mrl)
		return BTK_ERROR_MRL;

	m_WorkModel = model;

	return BTK_NO_ERROR;
}


BTK_RESULT BTKControl::SetHwnd(HWND hwnd)
{
	if(m_input == NULL)
		return BTK_ERROR_UNKNOW;
	if(m_render == NULL)
		m_render = new BTKRender(this);			//实例

	return m_render->SetHwnd(hwnd);
}

BTK_RESULT BTKControl::Run()
{
	if(m_input == NULL || m_render == NULL)
		return BTK_ERROR_UNKNOW;
	//m_switch.Single();

	return m_input->Run();
}

BTK_RESULT BTKControl::Stop()
{
	if(!IsPlaying())
		return BTK_NO_ERROR;

	int state = BTK_END;
	m_switch.Single();
	m_state->SetVariable(&state);
	m_FrameSwitch.Single();

	m_SafeClose.Wait();

	return BTK_NO_ERROR;
}

BTK_RESULT BTKControl::Pause()
{
	int state = BTK_NORMAL;
	m_state->GetVariable(&state);
	if(state == BTK_PALYING)
	{
		state = BTK_PAUSE;
		m_state->SetVariable(&state);
		m_switch.Unsingle();
	}
	else if(state == BTK_PAUSE)
	{
		PlayNextFrame();
		state = BTK_PALYING;
		m_state->SetVariable(&state);
		m_switch.Single();
	}

	return BTK_NO_ERROR;
}

BTK_BOOL BTKControl::IsPlaying()
{
	int state = BTK_NORMAL;
	if(m_state)
	{
		m_state->GetVariable(&state);
		if(state == BTK_PALYING || state == BTK_PAUSE)
			return BTK_TRUE;
	}
	return BTK_FALSE;
}

BTK_RESULT BTKControl::SetDisplayCBK(btk_entry_display_t pCBK,void *pUser)
{
	if(!pCBK)
		return BTK_ERROR_PTR;

	m_pDisplayCBK	= pCBK;
	m_pDisplayData	= pUser;

	return BTK_NO_ERROR;
}

void BTKControl::ResetCBK()
{
	m_pDisplayCBK	= NULL;
	m_pDisplayData	= NULL;
}

BTK_RESULT BTKControl::PlayNextFrame()
{
	int state = BTK_NORMAL;
	m_state->GetVariable(&state);
	if(state != BTK_PAUSE)
	{
		state = BTK_PAUSE;
		m_state->SetVariable(&state);
	}
	else if(state == BTK_PAUSE)
		m_switch.Single();

	m_FrameSwitch.Single();
	return BTK_NO_ERROR;
}

BTK_RESULT BTKControl::Snapshot(char *path_name)
{
	BTK_RESULT br;
	if(m_render)
		br = m_render->TakeSnapshot(path_name);
	if(br != BTK_NO_ERROR)
		return br;

	btk_Warn("TakeSnapshot location=%s\n",path_name);

	return BTK_NO_ERROR;
}

BTK_RESULT BTKControl::ToggelRecord(char *path_name)
{
	BTK_RESULT br;
	BTKRecord record;
	br = record.Start(path_name);
	if(br != BTK_NO_ERROR)
		return br;

	return BTK_NO_ERROR;
}

BTK_RESULT BTKControl::SetPlayDirection(bool bFront)
{
	BTK_RESULT br = BTK_NO_ERROR;
	if(m_WorkModel == BTK_PLAY_FILE)
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

BTK_RESULT BTKControl::SetSpeed(btk_speed_e e)
{
	BTK_RESULT br = BTK_NO_ERROR;
	switch(e)
	{
	case BTK_SPEED_SLOWEST:
	case BTK_SPEED_SLOWER:
	case BTK_SPEED_SLOW:
	case BTK_SPEED_NORMAL:
	case BTK_SPEED_FAST:
	case BTK_SPEED_FASTER:
	case BTK_SPEED_FASTEST:
		br = m_speed->SetVariable(&e);	
		br = m_input->ControlAccess(ACCESS_SET_SPEED,(va_list)&e);
		break;
	}

	return br;
}

BTK_RESULT BTKControl::SetTime(btk_mtime_t time)
{
	BTK_RESULT br = BTK_NO_ERROR;
	if(m_WorkModel == BTK_PLAY_FILE)
	{
		br = m_render->SetTime(time);
	}

	return br;
}

BTK_RESULT BTKControl::ToggelBackRun(bool bEnable)
{
	return BTK_NO_ERROR;
}

BTK_RESULT BTKControl::SetVolume(int volume)
{
	return BTK_NO_ERROR;
}

BTK_RESULT BTKControl::GetVolume(int &volume)
{
	return BTK_NO_ERROR;
}

BTK_RESULT BTKControl::GetState(int &state)
{
	if(m_state)
	{
		m_state->GetVariable(&state);
	}
	return BTK_NO_ERROR;
}

BTK_RESULT BTKControl::CallBackStop()
{
	int num = 0;
	m_ThreadNumer->GetVariable(&num);

	for(int i=0;i<num;i++)
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

	return BTK_NO_ERROR;
}

void BTKControl::SleepPlayer(bool bEnable)
{
	if(m_bSleep)
	{
		m_bSleep->SetVariable(&bEnable);
	}
}

BTK_RESULT BTKControl::GetHwnd(HWND &hwnd)
{
	if(m_render)
		return m_render->GetHwnd(hwnd);
}

BTK_RESULT BTKControl::SetEndCBK(btk_entry_end_t pCBK,void *pUser)
{
	if(!pCBK)
		return BTK_ERROR_PTR;

	m_pEndCBK	= pCBK;
	m_pEndData	= pUser;

	return BTK_NO_ERROR;
}