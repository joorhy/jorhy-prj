#include "..\include\BTKTransform.h"
#include "..\include\BTKError.h"
#include "..\include\BTKControl.h"
#include "..\include\DefaultConfig.h"
#include "..\include\BTKLog.h"

BTKTransform::BTKTransform(btk_transform_t &t,void *control)
{
	m_decoders		= t;
	m_control		= control;

	m_vDecoder		= NULL;
	m_vbuffer		= NULL;
	m_vbufferEX		= NULL;

	m_aDecoder		= NULL;
	m_abuffer		= NULL;
	m_abufferEX		= NULL;
	m_bDecDone		= false;
}

BTKTransform::~BTKTransform(void)
{
	BTKAudioDecode::ReleaseInstance(&m_aDecoder);
	BTKVideoDecode::ReleaseInstance(&m_vDecoder);

	BTKBuffer::ReleaseInstance(&m_abuffer);
	BTKBuffer::ReleaseInstance(&m_abufferEX);
	BTKBuffer::ReleaseInstance(&m_vbuffer);
	BTKBuffer::ReleaseInstance(&m_vbufferEX);
}


unsigned BTKTransform::AudioThread(void *parm)
{
	BTK_RESULT br = BTK_NO_ERROR;
	BTKTransform *pThis = reinterpret_cast<BTKTransform*>(parm);
	if(pThis)
	{
		BTKControl *ctl = reinterpret_cast<BTKControl*>(pThis->m_control);
		if(ctl)
		{
			

			if(ctl->m_WorkModel == BTK_PLAY_REALTIME)
			{
				pThis->m_abuffer = BTKBuffer::CreateInstance(BUFFER_FIFO,BUFFER_ADUIO_OUTPUT);		//参见m_decoders动态生成大小
				br = pThis->AudioLoopPush();
			}
			else if(ctl->m_WorkModel == BTK_PLAY_FILE);
			{
				pThis->m_abuffer	= BTKBuffer::CreateInstance(BUFFER_FIFO,BUFFER_ADUIO_OUTPUT);		//参见m_decoders动态生成大小
				pThis->m_abufferEX	= BTKBuffer::CreateInstance(BUFFER_FIFO,BUFFER_ADUIO_OUTPUT);		//参见m_decoders动态生成大小
				br = pThis->AudioLoopPull();
			}
		}
	}

	return br;
}

unsigned BTKTransform::VideoThread(void *parm)
{
	BTK_RESULT br = BTK_NO_ERROR;
	BTKTransform *pThis = reinterpret_cast<BTKTransform*>(parm);
	if(pThis)
	{

		BTKControl *ctl = reinterpret_cast<BTKControl*>(pThis->m_control);
		if(ctl)
		{
			if(ctl->m_WorkModel == BTK_PLAY_REALTIME)
			{
				pThis->m_vbuffer = BTKBuffer::CreateInstance(BUFFER_FIFO,BUFFER_VIDEO_OUTPUT);		//参见m_decoders动态生成大小
				br = pThis->VideoLoopPush();
			}
			else
			{
				pThis->m_vbuffer	= BTKBuffer::CreateInstance(BUFFER_LIST,BUFFER_VIDEO_OUTPUT);		//参见m_decoders动态生成大小
				pThis->m_vbufferEX	= BTKBuffer::CreateInstance(BUFFER_LIST,BUFFER_VIDEO_OUTPUT);
				br = pThis->VideoLoopPull();
			}
		}
	}


	return br;
}

BTK_RESULT BTKTransform::AudioLoopPush()
{
	BTK_RESULT br = BTK_NO_ERROR;
	m_aDecoder = BTKAudioDecode::CreateInstance(m_decoders.aType);
	if(!m_aDecoder)
		return BTK_ERROR_AUDIO_DECODE;

	BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
	bool bFirst = true;
	char *srcData = new char[MAX_AUDIO_FRAME_SIZE];
	char *dstData = new char[MAX_AUDIO_FRAME_SIZE];
	int srcLen = 0;
	int dstlen = 0;
	int state = BTK_NORMAL;
	++(*ctl->m_ThreadNumer);

	while(state != BTK_END && state != BTK_ERROR)
	{
		ctl->m_switch.Wait();
		
		btk_buffer_t head;
		btk_decode_t format;
		btk_audio_format_t aout;
		
		br = ctl->m_input->m_buffer->Read(srcData,(char*)&format,head);
		if(br == BTK_NO_ERROR)
		{
			if(format.type == DECODE_AUDIO)
			{	
				br = m_aDecoder->Decode(srcData,format.size,dstData,&dstlen);
				if(bFirst)
				{
					InitAudio();
					bFirst = false;
				}
				aout.size		= dstlen;
				aout.timestamp	= format.timestamp;
				head.datasize	= dstlen;
				head.extrasize	= sizeof(btk_audio_format_t);
				m_abuffer->Write(dstData,(char*)&aout,head);
				ctl->m_input->m_buffer->MoveNext();
			}
			else
				Sleep(1);
		}
		else
		{
			ctl->m_input->m_buffer->WaitData();
		}
		ctl->m_state->GetVariable(&state);
	}
	delete srcData;
	delete dstData;
	
	return br;
}

BTK_RESULT BTKTransform::VideoLoopPush()
{
	BTK_RESULT br = BTK_NO_ERROR;
	m_vDecoder = BTKVideoDecode::CreateInstance(m_decoders.vType);
	if(!m_vDecoder)
		return BTK_ERROR_VIDEO_DECODE;

	BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
	bool bFirst = true;
	DWORD dwDecTime = 0;
	bool bNeedIframe = false;
	char *srcData = new char[MAX_VIDEO_FRAME_SIZE];
	char *dstData = new char[MAX_VIDEO_FRAME_SIZE];
	int dstlen = 0;
	int state = BTK_NORMAL;
	++(*ctl->m_ThreadNumer);

	while(true)
	{
		ctl->m_state->GetVariable(&state);
		
		btk_buffer_t head;
		btk_decode_t format;
		btk_video_format_t vout;

		switch(state)
		{
		case BTK_NORMAL: break;

		case BTK_PALYING:
		case BTK_PAUSE:
			ctl->m_switch.Wait();
			br = ctl->m_input->m_buffer->Read(srcData,(char*)&format,head);
			if(br == BTK_NO_ERROR)
			{
				if(format.type != DECODE_AUDIO)
				{	
					if(ConsiderVDecoder(format,dwDecTime,bNeedIframe))
					{
						dwDecTime = GetTickCount();
						br = m_vDecoder->Decode(srcData,format.size,dstData,&dstlen);
						dwDecTime = GetTickCount() - dwDecTime;
						if(br == BTK_NO_ERROR)
						{
							if(bFirst)
							{
								InitVideo();
								bFirst = false;
							}
							vout.size		= dstlen;
							vout.timestamp	= format.timestamp;
							vout.fps		= format.fps;
							head.datasize	= dstlen;
							head.extrasize	= sizeof(btk_audio_format_t);
							br = m_vbuffer->Write(dstData,(char*)&vout,head);
							if(br == BTK_ERROR_FULL_BUFFER)
							{
								m_vbuffer->Flush();
								m_vbuffer->Write(dstData,(char*)&vout,head);
							}
						}
					}

					ctl->m_input->m_buffer->MoveNext();
				}
				else
					Sleep(1);
			}
			else
			{
				ctl->m_input->m_buffer->WaitData();
			}
			break;

		case BTK_END: 
			goto VDec_End;
			break;

		case BTK_ERROR: 
			goto VDec_End;
			break;

		}

	}

VDec_End:
	delete []srcData;
	delete []dstData;
	btk_Info("Video Decode Thread Exit : %d\tbr=%d\n",GetCurrentThreadId(),br);
	ctl->m_AllClose.Post();
	return br;
}

BTK_RESULT BTKTransform::InitAudio()
{
	BTK_RESULT br = BTK_NO_ERROR;
	btk_audio_out_t parm;
	br = m_aDecoder->GetOutputType(parm);

	BTKControl *control = reinterpret_cast<BTKControl*>(m_control);
	if(!control)
		return BTK_ERROR_CONTROL;
	if(!control->m_render)
		return BTK_ERROR_NO_RENDER;
	br = control->m_render->CreateAout(parm);
	if(br != BTK_NO_ERROR)
		return br;
	br = control->m_render->RunAout();
	if(br != BTK_NO_ERROR)
		return br;

	return br;
}

BTK_RESULT BTKTransform::InitVideo()
{
	BTK_RESULT br = BTK_NO_ERROR;
	btk_video_out_t parm;
	br = m_vDecoder->GetOutputType(parm);

	BTKControl *control = reinterpret_cast<BTKControl*>(m_control);
	if(!control)
		return BTK_ERROR_CONTROL;
	if(!control->m_render)
		return BTK_ERROR_NO_RENDER;
	br = control->m_render->CreateVout(parm);
	if(br != BTK_NO_ERROR)
		return br;
	br = control->m_render->RunVout();
	if(br != BTK_NO_ERROR)
		return br;

	return br;
}

BTK_RESULT BTKTransform::Run()
{
	BTK_RESULT br = BTK_NO_ERROR;

	btk_thread_t parm;
	parm.data = this;
	parm.priority = 0;//THREAD_PRIORITY_HIGHEST; 

	parm.entry= BTKTransform::AudioThread;
	br = m_aThread.Create(parm);
	if(br != BTK_NO_ERROR)
		return br;

	parm.entry= BTKTransform::VideoThread;
	br = m_vThread.Create(parm);
	if(br != BTK_NO_ERROR)
		return br;

	return BTK_NO_ERROR;
}

BTK_RESULT BTKTransform::SwitchBuffer()
{
	BTKBuffer *tmp = NULL;
	bool front = true;
	while(true)
	{
		if(m_bDecDone)
		{
			tmp			= m_vbuffer;
			m_vbuffer	= m_vbufferEX;
			m_vbufferEX	= tmp;
			
			BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
			if(ctl)
			{
				ctl->m_bForward->GetVariable(&front);
				if(front)
					m_vbuffer->SetReadPoint(false);			//begin point
				else
					m_vbuffer->SetReadPoint(true);			//end point
			}
			m_bDecDone = false;
			break;
		}
	}
	
	return BTK_NO_ERROR;
}

BTK_RESULT BTKTransform::VideoLoopPull()
{
	BTK_RESULT br = BTK_NO_ERROR;
	m_vDecoder = BTKVideoDecode::CreateInstance(m_decoders.vType);
	if(!m_vDecoder)
		return BTK_ERROR_VIDEO_DECODE;

	BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
	bool bFirst		= true;
	char *srcData	= new char[MAX_VIDEO_FRAME_SIZE];
	char *dstData	= new char[MAX_VIDEO_FRAME_SIZE];
	int dstlen		= 0;
	int framenum	= 0;
	int state		= BTK_NORMAL;
	++(*ctl->m_ThreadNumer);

	while(true)
	{
		btk_buffer_t head;
		btk_decode_t format;
		btk_video_format_t vout;

		m_pullSwitch.Wait();
		ctl->m_input->m_pullSwitch.Single();

		ctl->m_state->GetVariable(&state);
		switch(state)
		{
		case BTK_NORMAL: break;

		case BTK_PALYING:
		case BTK_PAUSE:
			while(framenum < m_decoders.iframe_interval)
			{
				ctl->m_input->m_buffer->WaitData();
				br = ctl->m_input->m_buffer->Read(srcData,(char*)&format,head);
				if(br == BTK_NO_ERROR)
				{
					if(format.type != DECODE_AUDIO)
					{	
						br = m_vDecoder->Decode(srcData,format.size,dstData,&dstlen);
						if(br == BTK_NO_ERROR)
						{
							if(bFirst)
							{
								InitVideo();
								bFirst = false;
							}
							vout.size		= dstlen;
							vout.timestamp	= format.timestamp;
							vout.fps		= format.fps;
							head.datasize	= dstlen;
							head.extrasize	= sizeof(btk_audio_format_t);
							br = m_vbufferEX->Write(dstData,(char*)&vout,head);
						}
						ctl->m_input->m_buffer->MoveNext();
						framenum++;
					}
					else
						Sleep(1);
				}
				else if(br == BTK_ERROR_EMPTY_BUFFER)
				{
					break;
				}
			}
			m_bDecDone = true;
			break;

		case BTK_END: 
			goto VDec_End2;
			break;

		case BTK_ERROR: 
			goto VDec_End2;
			break;

		}
		m_pullSwitch.Unsingle();
	}

VDec_End2:
	delete []srcData;
	delete []dstData;
	btk_Info("Pull Video Decode Thread Exit : %d\tbr=%d\n",GetCurrentThreadId(),br);
	ctl->m_AllClose.Post();
	return br;
}

BTK_RESULT BTKTransform::AudioLoopPull()
{
	return BTK_NO_ERROR;
}

BTK_RESULT BTKTransform::SetDirection(bool bFront)
{
	if(bFront)
	{
		m_vbuffer->SetReadType(true);
	}
	else
	{
		m_vbuffer->SetReadType(false);
	}
	m_vbufferEX->Flush();

	return BTK_NO_ERROR;
}

BTK_BOOL BTKTransform::ConsiderVDecoder(btk_decode_t format,DWORD LastDecTime,bool &bNeedIframe)
{
	BTKControl *ctl = reinterpret_cast<BTKControl*>(m_control);
	bool bSleep = false;
	BTK_BOOL bRet = BTK_TRUE;
	if(ctl)
	{
		ctl->m_bSleep->GetVariable(&bSleep);
		if(format.type == DECODE_I_FRAME)			//自要是I帧都不丢
		{
			bRet = BTK_TRUE;
			bNeedIframe = false;
		}
		else								//睡眠状态切换都要重新找到I帧开始解码
		{
			if(bSleep)						//睡眠的情况
			{
				bRet = BTK_FALSE;
				bNeedIframe = true;
			}	
			else							//不是睡眠的情况
			{
				if(LastDecTime > 1000 /*/ format.fps*/)
				{
					bRet = BTK_FALSE;
					bNeedIframe = true;
				}

				if(bNeedIframe)			//如果需要I帧
					bRet = BTK_FALSE;
			}
		}
	}
	return bRet;
}