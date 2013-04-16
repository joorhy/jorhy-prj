#include "..\include\BTKRender.h"
#include "..\include\BTKError.h"
#include "..\include\BTKControl.h"
#include "..\include\BTKVideoOutput.h"
#include "..\include\DefaultConfig.h"
#include "..\include\BTKLog.h"
#include "..\include\BTKPicture.h"

BTKRender::BTKRender(void *control)
{
	m_control	= control;
	m_hwnd		= NULL;
	m_vdata		= NULL;
	m_vOut		= NULL;
	m_aOut		= NULL;
}

BTKRender::~BTKRender(void)
{
	BTKVideoOutput::ReleaseInstance(&m_vOut);
	BTKAudioOutput::ReleaseInstance(&m_aOut);
}



BTK_RESULT BTKRender::CreateVout(btk_video_out_t &vParm)
{
	BTK_RESULT br = BTK_NO_ERROR;
	m_vOut = BTKVideoOutput::CreateInstance(vParm);
	m_vOut->SetHwnd(m_hwnd);
	btk_Info("Create Vout %d*%d \n",vParm.width,vParm.height);
	return br;
}

BTK_RESULT BTKRender::CreateAout(btk_audio_out_t &aParm)
{
	BTK_RESULT br = BTK_NO_ERROR;


	return br;
}

BTK_RESULT BTKRender::RunVout()
{
	BTK_RESULT br = BTK_NO_ERROR;
	btk_thread_t parm;
	parm.data = this;
	parm.priority = 0; 

	parm.entry= BTKRender::VoutThread;
	br = m_vThread.Create(parm);
	if(br != BTK_NO_ERROR)
		return br;

	return br;
}

BTK_RESULT BTKRender::RunAout()
{
	BTK_RESULT br = BTK_NO_ERROR;


	return br;
}

unsigned BTKRender::AoutThread(void *parm)
{
	BTK_RESULT br = BTK_NO_ERROR;
	BTKRender *pThis = reinterpret_cast<BTKRender*>(parm);
	if(pThis)
		br = pThis->AoutLoop();

	return br;
}

BTK_RESULT BTKRender::AoutLoop()
{
	BTK_RESULT br = BTK_NO_ERROR;

	BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
	char *data = new char[1024*1024];
	int readlen = 0;
	int state = BTK_NORMAL;
	btk_mtime_t syncTime = 0;
	++(*ctl->m_ThreadNumer);

	while(state != BTK_END && state != BTK_ERROR)
	{
		ctl->m_switch.Wait();
		btk_buffer_t head;
		btk_audio_format_t format;
		if(ctl->m_tansfm->m_abuffer->Read(data,(char*)&format,head) == BTK_NO_ERROR)		//get display buffer
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
					BTKThreadMisc::Sleep((format.timestamp - syncTime)/1000);
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

unsigned BTKRender::VoutThread(void *parm)
{
	BTK_RESULT br = BTK_NO_ERROR;
	BTKRender *pThis = reinterpret_cast<BTKRender*>(parm);
	if(pThis)
	{
		BTKControl *ctl = reinterpret_cast<BTKControl*>(pThis->m_control);
		if(ctl->m_WorkModel == BTK_PLAY_REALTIME)
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

BTK_RESULT BTKRender::VoutLoopPush()
{
	BTK_RESULT br = BTK_NO_ERROR;
	BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
	m_vdata			= new char[MAX_VIDEO_FRAME_SIZE];
	int state		= BTK_NORMAL;
	++(*ctl->m_ThreadNumer);
	btk_mtime_t nowtime,lasttime,interval;
	interval = nowtime = lasttime = 0;
	bool bFrist = true;
	bool bSleep = false;
	BTKCond vclock;

	while(true)
	{
		ctl->m_state->GetVariable(&state);
		ctl->m_switch.Wait();
		switch(state)
		{
		case BTK_NORMAL: break;

		case BTK_PALYING:
			m_vLock.Lock();
			br = ctl->m_tansfm->m_vbuffer->Read(m_vdata,(char*)&m_vformat,m_vhead);		//get display buffer
			if(br == BTK_NO_ERROR)		
			{
				ctl->m_bSleep->GetVariable(&bSleep);
				if(!bSleep)
				{
					br = m_vOut->PrepareData(m_vdata,m_vformat.size);
					vclock.WaitTime(lasttime);
					br = m_vOut->Display();
					lasttime = BTKThreadMisc::MakeDate() + 25*1000;		//<=40 ms


					if(ctl->m_pDisplayCBK)
						ctl->m_pDisplayCBK(ctl->m_pDisplayData,m_vformat.timestamp);
				}
				ctl->m_displayTime->SetVariable(&m_vformat.timestamp);
		
				br = ctl->m_tansfm->m_vbuffer->MoveNext();
			}
			else
			{
				ctl->m_tansfm->m_vbuffer->WaitData();
			}
			m_vLock.Unlock();
			break;

		case BTK_PAUSE: 
			ctl->m_FrameSwitch.Wait();
			m_vLock.Lock();
			br = ctl->m_tansfm->m_vbuffer->Read(m_vdata,(char*)&m_vformat,m_vhead);		//get display buffer
			if(br == BTK_NO_ERROR)		
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

		case BTK_END: 
			goto Vout_End;

		case BTK_ERROR:
			goto Vout_End;

		}

	}
Vout_End:
	delete m_vdata;
	m_vdata = NULL;
	btk_Info("Video Output Thread Exit : %d\tbr=%d\n",GetCurrentThreadId(),br);
	ctl->m_AllClose.Post();
	return br;
}

BTK_RESULT BTKRender::SetHwnd(HWND hwnd)
{
	m_hwnd = hwnd;
	return BTK_NO_ERROR;
}

BTK_RESULT BTKRender::TakeSnapshot(char *path_name)
{
	m_vLock.Lock();
	
	BTK_RESULT br;
	btk_video_format_t	format;
	char				*data = NULL;
	btk_video_out_t		voutfmt;
	
	memcpy(&format,&m_vformat,sizeof(format));
	if(!m_vdata || format.size == 0 || !m_vOut)
	{
		m_vLock.Unlock();
		return BTK_ERROR_NO_PICTURE;
	}

	data = new char[format.size];
	memcpy(data,m_vdata,format.size);
	m_vOut->GetVoutParm(voutfmt);
	m_vLock.Unlock();

	br = BTKPicture::SavePicture(format,data,voutfmt,path_name);

	delete data;
	data = NULL;
	return BTK_NO_ERROR;
}


BTK_RESULT BTKRender::VoutLoopPull()
{
	BTK_RESULT br;
	BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
	m_vdata			= new char[MAX_VIDEO_FRAME_SIZE];
	int state		= BTK_NORMAL;
	++(*ctl->m_ThreadNumer);

	ctl->m_tansfm->m_pullSwitch.Single();			//唤醒decode线程
	bool bFirst		= true;
	btk_mtime_t lasttime	= 0;
	btk_mtime_t interval_time = 0;
	while(true)
	{
		ctl->m_switch.Wait();
		ctl->m_state->GetVariable(&state);

		switch(state)
		{
		case BTK_NORMAL: break;

		case BTK_PALYING:
			m_vLock.Lock();
			
			br = GetNextFrame(m_vdata,m_vformat,m_vhead);
			if(bFirst)
			{
				bFirst = false;
				interval_time = ((double)1000 / (double)m_vformat.fps) + 0.5;
			}

			br = DisplayNextFrame(lasttime,lasttime + interval_time);
			lasttime += interval_time;

			m_vLock.Unlock();
			break;

		case BTK_PAUSE: 
			ctl->m_FrameSwitch.Wait();			//单帧
			m_vLock.Lock();

			br = GetNextFrame(m_vdata,m_vformat,m_vhead);

			ctl->m_FrameSwitch.Unsingle();
			m_vLock.Unlock();
			break;

		case BTK_END: 
			goto Vout_End2;

		case BTK_ERROR:
			goto Vout_End2;

		}

	}
Vout_End2:
	delete m_vdata;
	m_vdata = NULL;
	btk_Info("Pull Video Output Thread Exit : %d\tbr=%d\n",GetCurrentThreadId(),br);
	ctl->m_AllClose.Post();
	return br;
}

BTK_RESULT BTKRender::GetNextFrame(char *data,btk_video_format_t &t,btk_buffer_t &head)
{
	BTK_RESULT br;
	BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
	btk_mtime_t lasttime = 0;
	bool bFront = true;
	if(ctl)
	{
		br = ctl->m_displayTime->GetVariable(&lasttime);
		br = ctl->m_bForward->GetVariable(&bFront);
		while(true)
		{
			br = ctl->m_tansfm->m_vbuffer->Read(data,(char*)&t,head);
			if(br == BTK_ERROR_EMPTY_BUFFER)
			{
				ctl->m_tansfm->SwitchBuffer();					//交换vout buffer background 和 vout buffer

				ctl->m_tansfm->m_pullSwitch.Single();			//唤醒decode线程

				br = ctl->m_tansfm->m_vbuffer->Read(data,(char*)&t,head);
				if(br == BTK_ERROR_EMPTY_BUFFER)
					return br;
			}
			br = ctl->m_tansfm->m_vbuffer->MoveNext();

			if(bFront)
			{
				if(lasttime <= t.timestamp)
				{
					break;
				}
			}
			else
			{
				if(lasttime >= t.timestamp)
				{
					break;
				}
			}
		}

	}

	return BTK_NO_ERROR;
}

BTK_RESULT BTKRender::DisplayNextFrame(btk_mtime_t last_time,btk_mtime_t now_time)
{
	BTK_RESULT br;
	BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
	if(ctl)
	{
		int speedkey = BTK_SPEED_NORMAL;
		ctl->m_speed->GetVariable(&speedkey);
		btk_mtime_t intervaltime = (now_time - last_time) * btk_speed_values[speedkey].value + 0.5;
		Sleep(intervaltime);
		// 显示图片
		br = m_vOut->PrepareData(m_vdata,m_vformat.size);
		br = m_vOut->Display();

		if(ctl->m_pDisplayCBK)
			ctl->m_pDisplayCBK(ctl->m_pDisplayData,m_vformat.timestamp);

		ctl->m_displayTime->SetVariable(&m_vformat.timestamp);

	}
	return br;
}

BTK_RESULT BTKRender::SetTime(btk_mtime_t time)
{
	BTK_RESULT br = BTK_NO_ERROR;
	BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
	if(ctl)
	{
		br = ctl->m_tansfm->m_vbuffer->Flush();
		br = ctl->m_tansfm->m_vbufferEX->Flush();
		br = ctl->m_input->ControlAccess(ACCESS_SET_TIME,(va_list)&time);
		br = ctl->m_displayTime->SetVariable(&time);
	}

	return br;
}

BTK_RESULT BTKRender::GetHwnd(HWND &hwnd)
{
	if(m_hwnd)
		hwnd = m_hwnd;
	else
		hwnd = NULL;

	return BTK_NO_ERROR;
}