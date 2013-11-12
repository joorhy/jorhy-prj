#include "JoPlayer.h"

#define RAW_DATA_BUFF_LEN (5 * 1024 * 1024)
#define VIDEO_DATA_BUFF_LEN (10 * 1024 * 1024)

JO_IMPLEMENT_INTERFACE(Player, "jo_player", CJoPlayer::Maker)

CJoPlayer::CJoPlayer()
{
	m_decoder = NULL;
	m_render = NULL;
	m_rawBuffer = NULL;
	m_vBuffer = NULL;
	m_vBuffer2 = NULL;
	m_bStart = false;
	m_bInitRender = false;
}

CJoPlayer::~CJoPlayer()
{
	Deinit();
}

j_result_t CJoPlayer::Play(j_wnd_t hWnd)
{
	m_hwnd = hWnd;
	if (m_decoder == NULL)
	{
		m_decoder = JoDecoderFactory->GetDecoder(hWnd, "h264");
		m_decoder->InidDecoder();
		m_decoder->AspectRatio(m_width, m_height);
	}
	if (m_render == NULL)
	{
		m_render = JoRenderFactory->GetRender(hWnd, "live");
		m_render->AspectRatio(m_width, m_height);
		//m_render->InitRender(hWnd);
	}

	Init();
	m_bStart = true;
	j_thread_parm decode_parm = {0};
	decode_parm.entry = CJoPlayer::DecodeThread;
	decode_parm.data = this;
	m_decThread.Create(decode_parm);

	j_thread_parm rend_parm = {0};
	rend_parm.entry = CJoPlayer::RendThread;
	rend_parm.data = this;
	m_rendThread.Create(rend_parm);

	return J_OK;
}

j_result_t CJoPlayer::Stop()
{
	m_bStart = false;
	//m_semDec.WaitTime(1000);
	//m_semRend.WaitTime(1000);
	m_semDec.Wait();
	m_semRend.Wait();
	Deinit();
	m_decThread.Release();
	m_rendThread.Release();

	return J_OK;
}

j_result_t CJoPlayer::Init()
{
	if (m_rawBuffer == NULL)
		m_rawBuffer = new CRingBuffer();
	if (m_vBuffer == NULL)
		m_vBuffer = new CRingBuffer();
	if (m_vBuffer2 == NULL)
		m_vBuffer2 = new CRingBuffer();

	return J_OK;
}

void CJoPlayer::Deinit()
{
	m_lockerDec._Lock();
	if (m_decoder != NULL)
	{
		m_decoder->DeinitDecoder();
		JoDecoderFactory->DelDecoder(m_hwnd);
		m_decoder = NULL;
	}
	if (m_rawBuffer != NULL)
	{
		delete m_rawBuffer;
		m_rawBuffer = NULL;
	}
	m_lockerDec._Unlock();

	m_lockerRend._Lock();
	if (m_render != NULL)
	{
		m_render->DeinitRender();
		JoRenderFactory->DelRender(m_hwnd);
		m_render = NULL;
	}
	if (m_vBuffer != NULL)
	{
		delete m_vBuffer;
		m_vBuffer = NULL;
	}
	if (m_vBuffer2 != NULL)
	{
		delete m_vBuffer2;
		m_vBuffer2 = NULL;
	}
	m_lockerRend._Unlock();
}

j_result_t CJoPlayer::InputData(j_char_t *pData, J_StreamHeader &streamHeader)
{
	if (m_bStart && m_rawBuffer != NULL)
	{
		m_rawBuffer->PushBuffer(pData, streamHeader);
	}

	return J_OK;
}

j_result_t CJoPlayer::AspectRatio(j_int32_t nWidth, j_int32_t nHeight)
{
	m_width = nWidth;
	m_height = nHeight;
	if (m_decoder != NULL)
		m_decoder->AspectRatio(nWidth, nHeight);
	if (m_render != NULL)
		m_render->AspectRatio(nWidth, nHeight);
	return J_OK;
}

void CJoPlayer::OnDecode()
{
	j_char_t *pInputDataBuff = new j_char_t[RAW_DATA_BUFF_LEN];
	j_char_t *pOutputDataBuff = new j_char_t[VIDEO_DATA_BUFF_LEN];
	j_int32_t nOutputLen = 0;
	J_StreamHeader streamHeader;
	J_VideoDecodeParam decParam;
	j_result_t nResult = J_OK;
	while (m_bStart)
	{
		m_lockerDec._Lock();
		memset(&streamHeader, 0, sizeof(streamHeader));
		nResult = m_rawBuffer->PopBuffer(pInputDataBuff, streamHeader);
		if (nResult == J_OK && streamHeader.dataLen > 0)
		{
			if (streamHeader.frameType == jo_video_i_frame ||
				streamHeader.frameType == jo_video_b_frame || streamHeader.frameType == jo_video_p_frame)
			{
				nResult = m_decoder->DecodeOneFrame(pInputDataBuff, streamHeader.dataLen, pOutputDataBuff, nOutputLen);
				if (nResult == J_OK && nOutputLen > 0)
				{
					streamHeader.dataLen = nOutputLen;
					if (!m_bInitRender)
					{
						m_decoder->GetDecodeParam(decParam);
						m_render->SetDisplayParam(decParam);
						m_bInitRender = (m_render->InitRender(m_hwnd) == J_OK);
					}
					m_vBuffer->PushBuffer(pOutputDataBuff, streamHeader);
				}
			}
		}
		else
		{
			m_lockerDec._Unlock();
			j_sleep(10);
			continue;
		}
		m_lockerDec._Unlock();
	}
	delete pInputDataBuff;
	delete pOutputDataBuff;
	m_semDec.Post();
}

void CJoPlayer::OnRend()
{
	j_char_t *pDataBuff = new j_char_t[VIDEO_DATA_BUFF_LEN];
	J_StreamHeader streamHeader;
	j_result_t nResult = J_OK;
	while (m_bStart)
	{
		m_lockerRend._Lock();
		memset(&streamHeader, 0, sizeof(streamHeader));
		nResult = m_vBuffer->PopBuffer(pDataBuff, streamHeader);
		if (nResult == J_OK && streamHeader.dataLen > 0)
		{
			nResult = m_render->DisplayFrame(pDataBuff, streamHeader.dataLen);
		}
		else
		{
			m_lockerRend._Unlock();
			j_sleep(10);
			continue;
		}
		m_lockerRend._Unlock();
	}
	delete pDataBuff;
	m_semRend.Post();
}