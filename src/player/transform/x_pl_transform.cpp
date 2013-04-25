#include "x_pl_transform.h"
#include "x_pl_error.h"
#include "x_pl_control.h"
#include "x_pl_default_config.h"
#include "x_pl_log.h"
#include "assert.h"

#define			SLEEP_MODE		20
#define			NORMAL_MODE	60

CXPlTransform::CXPlTransform(j_pl_transform_t &t,void *control)
{
	m_decoders		= t;
	m_control		= control;

	m_vDecoder		= NULL;
	m_vbuffer		= NULL;
	m_vbufferEX		= NULL;

	m_aDecoder		= NULL;
	m_abuffer		= NULL;
	m_abufferEX		= NULL;
	m_cpuInfo.Init();
}

CXPlTransform::~CXPlTransform(void)
{
	CXPlAudioDecode::ReleaseInstance(&m_aDecoder);
	J_PlVideoDecode::ReleaseInstance(&m_vDecoder);

	J_PlBuffer::ReleaseInstance(&m_abuffer);
	J_PlBuffer::ReleaseInstance(&m_abufferEX);
	J_PlBuffer::ReleaseInstance(&m_vbuffer);
	J_PlBuffer::ReleaseInstance(&m_vbufferEX);
	//sbtk_Info("CXPlTransform::~CXPlTransform : %d\n",this);
}

unsigned CXPlTransform::AudioThread(void *parm)
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	CXPlTransform *pThis = reinterpret_cast<CXPlTransform*>(parm);
	if(pThis)
	{
		J_PlControl *ctl = reinterpret_cast<J_PlControl*>(pThis->m_control);
		if(ctl)
		{
			if(ctl->m_WorkModel == J_PL_PLAY_REALTIME)
			{
				pThis->m_abuffer = J_PlBuffer::CreateInstance(BUFFER_FIFO,BUFFER_ADUIO_OUTPUT);		//参见m_decoders动态生成大小
				br = pThis->AudioLoopPush();
			}
			else if(ctl->m_WorkModel == J_PL_PLAY_FILE)
			{
				pThis->m_abuffer	= J_PlBuffer::CreateInstance(BUFFER_FIFO,BUFFER_ADUIO_OUTPUT);		//参见m_decoders动态生成大小
				pThis->m_abufferEX	= J_PlBuffer::CreateInstance(BUFFER_FIFO,BUFFER_ADUIO_OUTPUT);		//参见m_decoders动态生成大小
				br = pThis->AudioLoopPull();
			}
		}
	}

	return br;
}

unsigned CXPlTransform::VideoThread(void *parm)
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	CXPlTransform *pThis = reinterpret_cast<CXPlTransform*>(parm);
	if(pThis)
	{
		J_PlControl *ctl = reinterpret_cast<J_PlControl*>(pThis->m_control);
		if(ctl)
		{
			if(ctl->m_WorkModel == J_PL_PLAY_REALTIME)
			{
				pThis->m_vbuffer = J_PlBuffer::CreateInstance(BUFFER_FIFO,BUFFER_VIDEO_OUTPUT);		//参见m_decoders动态生成大小
				br = pThis->VideoLoopPush();
			}
			else
			{
				pThis->m_vbuffer	= J_PlBuffer::CreateInstance(BUFFER_LIST,BUFFER_VIDEO_OUTPUT);		//参见m_decoders动态生成大小
				pThis->m_vbufferEX	= J_PlBuffer::CreateInstance(BUFFER_LIST,BUFFER_VIDEO_OUTPUT);
				br = pThis->VideoLoopPull();
			}
		}
	}


	return br;
}

J_PL_RESULT CXPlTransform::AudioLoopPush()
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	m_aDecoder = CXPlAudioDecode::CreateInstance(m_decoders.aType);
	if(!m_aDecoder)
		return J_PL_ERROR_AUDIO_DECODE;

	J_PlControl *ctl = reinterpret_cast<J_PlControl*>(m_control);
	bool bFirst = true;
	char *srcData = new char[MAX_AUDIO_FRAME_SIZE];
	char *dstData = new char[MAX_AUDIO_FRAME_SIZE];
	int srcLen = 0;
	int dstlen = 0;
	int state = J_PL_NORMAL;
	++(*ctl->m_ThreadNumer);

	while(state != J_PL_END && state != J_PL_ERROR)
	{
		ctl->m_switch.Wait();
		
		j_pl_buffer_t head;
		j_pl_decode_t format;
		j_pl_audio_format_t aout;
		
		br = ctl->m_input->m_buffer->Read(srcData,(char*)&format,head);
		if(br == J_PL_NO_ERROR)
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
				head.extrasize	= sizeof(j_pl_audio_format_t);
				head.datatype	= 2;
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

J_PL_RESULT CXPlTransform::VideoLoopPush()
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	m_vDecoder = J_PlVideoDecode::CreateInstance(m_decoders.vType);
	if(!m_vDecoder)
		return J_PL_ERROR_VIDEO_DECODE;

	J_PlControl *ctl = reinterpret_cast<J_PlControl*>(m_control);
	bool bFirst = true;
	bool bNeedDec = true;
	bool bNeedIframe = false;
	bool bIsIFrame = false;
	char *srcData = new char[MAX_VIDEO_FRAME_SIZE];
	char *dstData = new char[MAX_VIDEO_FRAME_SIZE];
	int dstlen = 0;
	int state = J_PL_NORMAL;
	++(*ctl->m_ThreadNumer);

	while(true)
	{
		ctl->m_state->GetVariable(&state);
		
		j_pl_buffer_t head;
		j_pl_decode_t format;
		j_pl_video_format_t vout;

		switch(state)
		{
		case J_PL_NORMAL: break;

		case J_PL_PALYING:
		case J_PL_PAUSE:
			//ctl->m_switch.Wait();
			if(ctl->m_input->m_buffer && 
				(br = ctl->m_input->m_buffer->Read(srcData,(char*)&format,head)) == J_PL_NO_ERROR)
			{
				if(format.type != DECODE_AUDIO)
				{	
					if(ConsiderVDecoder(format, bNeedDec, bNeedIframe, bIsIFrame))
					{
						if (bIsIFrame)
							m_vDecoder->FlushBuffer();

						br = m_vDecoder->Decode(srcData,format.size,dstData,&dstlen);
						if(br == J_PL_NO_ERROR)
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
							head.extrasize	= sizeof(j_pl_audio_format_t);
							head.datatype	= 1;
							br = m_vbuffer->Write(dstData,(char*)&vout,head);
							if(br == J_PL_ERROR_FULL_BUFFER)
							{
								m_vbuffer->Flush();
								m_vbuffer->Write(dstData,(char*)&vout,head);
							}
						}
						else
						{
							state = J_PL_ERROR;
							ctl->m_state->SetVariable(&state);
							break;
						}
					}
					//ctl->m_input->m_buffer->MoveNext();
				}
				//else
				//	Sleep(1);
			}
			else
			{
				if (ctl->m_input->m_buffer)
					ctl->m_input->m_buffer->WaitData();
			}
			break;

		case J_PL_END: 
			goto VDec_End;
			break;

		case J_PL_ERROR: 
			goto VDec_End;
			break;
		}
	}

VDec_End:
	delete srcData;
	delete dstData;
	j_pl_info("Video Decode Thread Exit : %d\tbr=%d\n",GetCurrentThreadId(),br);
	ctl->m_AllClose.Post();
	return br;
}

J_PL_RESULT CXPlTransform::InitAudio()
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	j_pl_audio_out_t parm;
	br = m_aDecoder->GetOutputType(parm);

	J_PlControl *control = reinterpret_cast<J_PlControl*>(m_control);
	if(!control)
		return J_PL_ERROR_CONTROL;
	if(!control->m_render)
		return J_PL_ERROR_NO_RENDER;
	br = control->m_render->CreateAout(parm);
	if(br != J_PL_NO_ERROR)
		return br;
	br = control->m_render->RunAout();
	if(br != J_PL_NO_ERROR)
		return br;

	return br;
}

J_PL_RESULT CXPlTransform::InitVideo()
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	j_pl_video_out_t parm;
	br = m_vDecoder->GetOutputType(parm);

	J_PlControl *control = reinterpret_cast<J_PlControl*>(m_control);
	if(!control)
		return J_PL_ERROR_CONTROL;
	if(!control->m_render)
		return J_PL_ERROR_NO_RENDER;
	br = control->m_render->CreateVout(parm);
	if(br != J_PL_NO_ERROR)
		return br;
	br = control->m_render->RunVout();
	if(br != J_PL_NO_ERROR)
		return br;

	return br;
}

J_PL_RESULT CXPlTransform::Run()
{
	J_PL_RESULT br = J_PL_NO_ERROR;

	
	m_aThreadParm.data = this;
	m_aThreadParm.priority = 0;//THREAD_PRIORITY_HIGHEST; 
	m_aThreadParm.entry= CXPlTransform::AudioThread;
	br = m_aThread.Create(m_aThreadParm);
	if(br != J_PL_NO_ERROR)
		return br;

	m_vThreadParm.data = this;
	m_vThreadParm.priority = 0;//THREAD_PRIORITY_HIGHEST; 
	m_vThreadParm.entry= CXPlTransform::VideoThread;
	br = m_vThread.Create(m_vThreadParm);
	if(br != J_PL_NO_ERROR)
		return br;

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlTransform::SwitchBuffer()
{
	J_PlBuffer *tmp = NULL;
	bool front = true;

	m_sem.WaitTime(100);
	tmp			= m_vbuffer;
	m_vbuffer	= m_vbufferEX;
	m_vbufferEX	= tmp;

	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlTransform::VideoLoopPull()
{
	J_PL_RESULT br = J_PL_NO_ERROR;
	m_vDecoder = J_PlVideoDecode::CreateInstance(m_decoders.vType);
	if(!m_vDecoder)
		return J_PL_ERROR_VIDEO_DECODE;

	J_PlControl *ctl = reinterpret_cast<J_PlControl*>(m_control);
	bool bFirst		= true;
	char *srcData	= new char[MAX_VIDEO_FRAME_SIZE];
	char *dstData	= new char[MAX_VIDEO_FRAME_SIZE];
	int dstlen		= 0;
	int framenum	= 0;
	int state		= J_PL_NORMAL;
	++(*ctl->m_ThreadNumer);

	while(true)
	{
		j_pl_buffer_t head;
		j_pl_decode_t format;
		j_pl_video_format_t vout;

		m_pullSwitch.Wait();
		ctl->m_input->m_pullSwitch.Single();

		ctl->m_state->GetVariable(&state);
		switch(state)
		{
		case J_PL_NORMAL: break;

		case J_PL_PALYING:
		case J_PL_PAUSE:
			while(framenum < m_decoders.iframe_interval)
			{
				ctl->m_input->m_buffer->WaitData();
				br = ctl->m_input->m_buffer->Read(srcData,(char*)&format,head);
				if(br == J_PL_NO_ERROR)
				{
					if(format.type != DECODE_AUDIO)
					{	
						br = m_vDecoder->Decode(srcData,format.size,dstData,&dstlen);
						if(br == J_PL_NO_ERROR)
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
							head.extrasize	= sizeof(j_pl_audio_format_t);
							head.datatype	= 1;
							br = m_vbufferEX->Write(dstData,(char*)&vout,head);
						}
						ctl->m_input->m_buffer->MoveNext();
						framenum++;
					}
					else
						Sleep(1);
				}
				else if(br == J_PL_ERROR_EMPTY_BUFFER)
				{
					break;
				}
			}
			m_sem.Post();
			break;

		case J_PL_END: 
			goto VDec_End2;
			break;

		case J_PL_ERROR: 
			goto VDec_End2;
			break;

		}
		m_pullSwitch.Unsingle();
	}

VDec_End2:
	delete srcData;
	delete dstData;
	j_pl_info("Pull Video Decode Thread Exit : %d\tbr=%d\n",GetCurrentThreadId(),br);
	ctl->m_AllClose.Post();
	return br;
}

J_PL_RESULT CXPlTransform::AudioLoopPull()
{
	return J_PL_NO_ERROR;
}

J_PL_RESULT CXPlTransform::SetDirection(bool bFront)
{
	m_vbufferEX->Flush();
	return J_PL_NO_ERROR;
}

J_PL_BOOL CXPlTransform::ConsiderVDecoder(j_pl_decode_t format, bool &bNeedDec, bool &bNeedIframe, bool &bIsIFrame)
{
	J_PlControl *ctl = reinterpret_cast<J_PlControl*>(m_control);
	bool bSleep = false;
	J_PL_BOOL bRet = J_PL_TRUE;
	if(ctl)
	{
		ctl->m_bSleep->GetVariable(&bSleep);
		if(bSleep)						//睡眠的情况
		{
			bRet = J_PL_FALSE;
			bNeedIframe = true;
			bNeedDec = false;
			return bRet;
		}
		if(format.type == DECODE_I_FRAME)			//只要是I帧都不丢
		{
			bRet = J_PL_TRUE;
			bNeedIframe = false;
			bNeedDec = true;
			bIsIFrame = true;
		}
		else								//睡眠状态切换都要重新找到I帧开始解码
		{
			bIsIFrame = false;
			//不是睡眠的情况
			if(!bNeedDec)
			{
				bRet = J_PL_FALSE;
				bNeedIframe = true;
			}
			else
			{
				UINT nInfo = 0;
				if (m_cpuInfo.GetInfo(nInfo) && nInfo > NORMAL_MODE)
				{
					bNeedDec = false;
					bRet = J_PL_FALSE;
					bNeedIframe = true;
				}
			}

			if(bNeedIframe)			//如果需要I帧
				bRet = J_PL_FALSE;
		}
	}
	return bRet;
}