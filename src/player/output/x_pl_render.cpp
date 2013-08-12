#include "x_pl_render.h"
#include "x_pl_error.h"
#include "x_pl_control.h"
#include "x_pl_video_output.h"
#include "x_pl_default_config.h"
#include "x_pl_log.h"
#include "x_pl_picture.h"

CXPlRender::CXPlRender(void *control)
{
	m_control	= control;
	m_hwnd		= NULL;
	m_vdata		= NULL;
	m_vOut			= NULL;
	m_aOut		= NULL;
}

CXPlRender::~CXPlRender(void)
{
	CXPlVideoOutput::ReleaseInstance(&m_vOut);
	CXPlAudioOutput::ReleaseInstance(&m_aOut);
	j_pl_info("CXPlRender::~CXPlRender(void) \n");
}

J_PL_RESULT CXPlRender::CreateVout(j_pl_video_out_t &vParm)
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	m_vOut = CXPlVideoOutput::CreateInstance(vParm);
	m_vOut->SetHwnd(m_hwnd);
	//j_pl_info("VoutLoopPush::VoutLoopPush3() %d\n", m_vOut);
	j_pl_info("Create Vout %d*%d \n",vParm.width,vParm.height);
	return br;
}

J_PL_RESULT CXPlRender::CreateAout(j_pl_audio_out_t &aParm)
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	return br;
}

J_PL_RESULT CXPlRender::RunVout()
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	m_vThreadParm.data = this;
	m_vThreadParm.priority = 0; 

	m_vThreadParm.entry= CXPlRender::VoutThread;
	br = m_vThread.Create(m_vThreadParm);
	if(br != J_PL_NO_ERROR)
		return br;

	return br;
}

J_PL_RESULT CXPlRender::RunAout()
{
	J_PL_RESULT br = J_PL_NO_ERROR;


	return br;
}

unsigned CXPlRender::AoutThread(void *parm)
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	CXPlRender *pThis = reinterpret_cast<CXPlRender*>(parm);
	if(pThis)
		br = pThis->AoutLoop();

	return br;
}

J_PL_RESULT CXPlRender::AoutLoop()
{
	J_PL_RESULT br = J_PL_NO_ERROR;

	J_PlControl *ctl = reinterpret_cast<J_PlControl*>(m_control);
	char *data = new char[1024*1024];
	int readlen = 0;
	int state = J_PL_NORMAL;
	j_pl_mtime_t syncTime = 0;
	++(*ctl->m_ThreadNumer);

	while(state != J_PL_END && state != J_PL_ERROR)
	{
		ctl->m_switch.Wait();
		j_pl_buffer_t head;
		j_pl_audio_format_t format;
		if(ctl->m_tansfm->m_abuffer->Read(data,(char*)&format,head) == J_PL_NO_ERROR)		//get display buffer
		{
			ctl->m_displayTime->GetVariable(&syncTime);
			if(syncTime == 0)
				continue;
			if(format.timestamp < syncTime - AOUT_MAX_PTS_DELAY)
			{
				continue;
			}
			else 
			{
				if(format.timestamp > syncTime + AOUT_MAX_PTS_DELAY)
				{
					J_PlThreadMisc::Sleep((format.timestamp - syncTime)/1000);
				}
				br = m_aOut->Display(data,format.size);
			}
			ctl->m_tansfm->m_abuffer->MoveNext();
		}
		else
		{
			Sleep(300);
		}

		ctl->m_state->GetVariable(&state);
	}
	delete data;
	return br;
}

unsigned CXPlRender::VoutThread(void *parm)
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	CXPlRender *pThis = reinterpret_cast<CXPlRender*>(parm);
	if(pThis)
	{
		J_PlControl *ctl = reinterpret_cast<J_PlControl*>(pThis->m_control);
		if(ctl->m_WorkModel == J_PL_PLAY_REALTIME)
		{
			br = pThis->VoutLoopPush();
		}
		else
		{
			br = pThis->VoutLoopPull();
		}
	}

	return br;
}

J_PL_RESULT CXPlRender::VoutLoopPush()
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	J_PlControl *ctl = reinterpret_cast<J_PlControl*>(m_control);
	m_vdata			= new char[MAX_VIDEO_FRAME_SIZE];
	int state		= J_PL_NORMAL;
	++(*ctl->m_ThreadNumer);
	j_pl_mtime_t nowtime,lasttime,interval;
	interval = nowtime = lasttime = 0;
	bool bFrist = true;
	bool bSleep = false;
	J_PlCond vclock;

	while(true)
	{
		ctl->m_state->GetVariable(&state);
		ctl->m_switch.Wait();
		//j_pl_info("VoutLoopPush()\n");
		switch(state)
		{
		case J_PL_NORMAL: break;

		case J_PL_PALYING:
			m_vLock.Lock();
			br = ctl->m_tansfm->m_vbuffer->Read(m_vdata,(char*)&m_vformat,m_vhead);		//get display buffer
			if(br == J_PL_NO_ERROR)		
			{
				ctl->m_bSleep->GetVariable(&bSleep);
				if(!bSleep)
				{
					br = m_vOut->PrepareData(m_vdata,m_vformat.size);
					//vclock.WaitTime(0);
					br = m_vOut->Display();
					//lasttime = J_PlThreadMisc::MakeDate() + 25*1000;		//<=40 ms


					if(ctl->m_pDisplayCBK)
						ctl->m_pDisplayCBK(ctl->m_pDisplayData,m_vformat.timestamp);
				}
				ctl->m_displayTime->SetVariable(&m_vformat.timestamp);
		
				//br = ctl->m_tansfm->m_vbuffer->MoveNext();
			}
			else
			{
				ctl->m_tansfm->m_vbuffer->WaitData();
			}
			m_vLock.Unlock();
			break;

		case J_PL_PAUSE: 
			ctl->m_FrameSwitch.Wait();
			m_vLock.Lock();
			br = ctl->m_tansfm->m_vbuffer->Read(m_vdata,(char*)&m_vformat,m_vhead);		//get display buffer
			if(br == J_PL_NO_ERROR)		
			{
				ctl->m_bSleep->GetVariable(&bSleep);
				if(!bSleep)
				{
					br = m_vOut->PrepareData(m_vdata,m_vformat.size);
					br = m_vOut->Display();

					if(ctl->m_pDisplayCBK)
						ctl->m_pDisplayCBK(ctl->m_pDisplayData,m_vformat.timestamp);
				}
				br = ctl->m_tansfm->m_vbuffer->MoveNext();
			}
			else
			{
				ctl->m_tansfm->m_vbuffer->WaitData();
			}
			ctl->m_FrameSwitch.Unsingle();
			m_vLock.Unlock();
			break;

		case J_PL_END: 
			goto Vout_End;

		case J_PL_ERROR:
			goto Vout_End;
		}
	}
Vout_End:
	delete m_vdata;
	m_vdata = NULL;
	j_pl_info("Video Output Thread Exit : %d\tbr=%d\n",GetCurrentThreadId(),br);
	ctl->m_AllClose.Post();
	return br;
}

J_PL_RESULT CXPlRender::SetHwnd(HWND hwnd)
{
	m_hwnd = hwnd;
	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlRender::TakeSnapshot(char *path_name)
{
	m_vLock.Lock();
	
	J_PL_RESULT br;
	j_pl_video_format_t	format;
	char				*data = NULL;
	j_pl_video_out_t		voutfmt;
	
	memcpy(&format,&m_vformat,sizeof(format));
	if(!m_vdata || format.size == 0 || !m_vOut)
	{
		m_vLock.Unlock();
		return J_PL_ERROR_NO_PICTURE;
	}

	data = new char[format.size];
	memcpy(data,m_vdata,format.size);
	m_vOut->GetVoutParm(voutfmt);
	m_vLock.Unlock();

	br = CXPlPicture::SavePicture(format,data,voutfmt,path_name);

	delete data;
	data = NULL;
	return J_PL_NO_ERROR;
}


J_PL_RESULT CXPlRender::VoutLoopPull()
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	J_PlControl *ctl = reinterpret_cast<J_PlControl*>(m_control);
	m_vdata		= new char[MAX_VIDEO_FRAME_SIZE];
	int state		= J_PL_NORMAL;
	++(*ctl->m_ThreadNumer);

	bool bDisplay		= true;
	j_pl_mtime_t lasttime	= 0;
	DWORD nowTime = 0;
	j_pl_mtime_t last_display_time = 0;
	while(true)
	{
		nowTime = GetTickCount();
		//ctl->m_switch.Wait();
		ctl->m_state->GetVariable(&state);
		switch(state)
		{
		case J_PL_NORMAL: break;
		case J_PL_PALYING:
			//m_vLock.Lock();
			if (bDisplay)
			{
				br = GetNextFrame(m_vdata,m_vformat,m_vhead);
				if (br == J_PL_NO_ERROR)
				{
					//m_vLock.Unlock();
					//continue;
					bDisplay = false;
				}
			}
			if (!bDisplay && last_display_time == 0 || nowTime - lasttime >= m_vformat.timestamp - last_display_time)
			{
				br = DisplayNextFrame();
				//if (br != J_PL_NO_ERROR)
				lasttime = 2 * nowTime - GetTickCount() - 5;

				bDisplay = true;
				last_display_time = m_vformat.timestamp;
			}
			//m_vLock.Unlock();
			break;
		case J_PL_PAUSE: 
			//j_pl_info("J_PL_PAUSE\n");
			ctl->m_FrameSwitch.Wait();			//单帧
			m_vLock.Lock();
			br = GetNextFrame(m_vdata,m_vformat,m_vhead);
			ctl->m_FrameSwitch.Unsingle();
			m_vLock.Unlock();
			break;
		case J_PL_END: 
			goto Vout_End2;
		case J_PL_ERROR:
			goto Vout_End2;
		}
	}
Vout_End2:
	//j_pl_info("ctl->m_tansfm->m_pullSwitch.Single()\n");
	ctl->m_tansfm->m_pullSwitch.Single();			//唤醒decode线程
	delete m_vdata;
	m_vdata = NULL;
	j_pl_info("Pull Video Output Thread Exit : %d\tbr=%d\n",GetCurrentThreadId(),br);
	ctl->m_AllClose.Post();
	return br;
}

J_PL_RESULT CXPlRender::GetNextFrame(char *data,j_pl_video_format_t &t,j_pl_buffer_t &head)
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	J_PlControl *ctl = reinterpret_cast<J_PlControl*>(m_control);
	bool bFront = true;
	if(ctl)
	{
		br = ctl->m_bForward->GetVariable(&bFront);
		br = ctl->m_tansfm->m_vbuffer->Read(data,(char*)&t,head);
		if(br == J_PL_ERROR_EMPTY_BUFFER)
		{
			ctl->m_tansfm->SwitchBuffer();					//交换vout buffer background 和 vout buffer
			ctl->m_tansfm->m_pullSwitch.Single();			//唤醒decode线程
			br = ctl->m_tansfm->m_vbuffer->Read(data,(char*)&t,head);
			if(br == J_PL_ERROR_EMPTY_BUFFER)
				return br;
		}
	}

	return br;
}

J_PL_RESULT CXPlRender::DisplayNextFrame()
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	J_PlControl *ctl = reinterpret_cast<J_PlControl*>(m_control);
	if(ctl)
	{
		int speedkey = J_PL_SPEED_NORMAL;
		ctl->m_speed->GetVariable(&speedkey);
		// 显示图片
		br = m_vOut->PrepareData(m_vdata,m_vformat.size);
		br = m_vOut->Display();
		if(ctl->m_pDisplayCBK)
		{
			ctl->m_pDisplayCBK(ctl->m_pDisplayData,m_vformat.timestamp);
		}
		
		ctl->m_displayTime->SetVariable(&m_vformat.timestamp);
	}
	return br;
}

J_PL_RESULT CXPlRender::SetTime(j_pl_mtime_t time)
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	J_PlControl *ctl = reinterpret_cast<J_PlControl*>(m_control);
	if(ctl)
	{
		br = ctl->m_tansfm->m_vbuffer->Flush();
		//br = ctl->m_tansfm->m_vbufferEX->Flush();
		br = ctl->m_input->ControlAccess(ACCESS_SET_TIME,(va_list)&time);
		br = ctl->m_displayTime->SetVariable(&time);
	}

	return br;
}

J_PL_RESULT CXPlRender::GetHwnd(HWND &hwnd)
{
	if(m_hwnd)
		hwnd = m_hwnd;
	else
		hwnd = NULL;

	return J_PL_NO_ERROR;
}