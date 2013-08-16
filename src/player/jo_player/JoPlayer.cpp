#include "JoPlayer.h"

#define RAW_DATA_BUFF_LEN (2 * 1024 * 1024)
#define VIDEO_DATA_BUFF_LEN (5 * 1024 * 1024)

JO_IMPLEMENT_INTERFACE(Player, "jo_player", CJoPlayer::Maker)

CJoPlayer::CJoPlayer()
{
	m_decoder = NULL;
	m_render = NULL;
	m_rawBuffer = NULL;
	m_vBuffer = NULL;
	m_vBuffer2 = NULL;
	m_bStart = false;
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
	}
	if (m_render == NULL)
	{
		m_render = JoRenderFactory->GetRender(hWnd, "live");
		m_render->InitRender(hWnd);
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
	m_decThread.Release();
	m_rendThread.Release();
	Deinit();

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
	if (m_decoder != NULL)
	{
		m_decoder->DeinitDecoder();
		JoDecoderFactory->DelDecoder(m_hwnd);
		m_decoder = NULL;
	}
	if (m_render != NULL)
	{
		m_render->DeinitRender();
		JoRenderFactory->DelRender(m_hwnd);
		m_render = NULL;
	}
	if (m_rawBuffer != NULL)
	{
		delete m_rawBuffer;
		m_rawBuffer = NULL;
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
}

j_result_t CJoPlayer::InputData(j_char_t *pData, J_StreamHeader &streamHeader)
{
	if (m_rawBuffer != NULL)
	{
		m_rawBuffer->PushBuffer(pData, streamHeader);
	}

	return J_OK;
}

void CJoPlayer::OnDecode()
{
	j_char_t *pInputDataBuff = new j_char_t[RAW_DATA_BUFF_LEN];
	j_char_t *pOutputDataBuff = new j_char_t[VIDEO_DATA_BUFF_LEN];
	j_int32_t nOutputLen = 0;
	J_StreamHeader streamHeader;
	j_result_t nResult = J_OK;
	while (m_bStart)
	{
		memset(&streamHeader, 0, sizeof(streamHeader));
		nResult = m_rawBuffer->PopBuffer(pInputDataBuff, streamHeader);
		if (nResult == J_OK && streamHeader.dataLen > 0)
		{
			static FILE *fp2 = NULL;
			if (fp2 == NULL)
				fp2 = fopen("test2.h264", "wb+");
			fwrite(pInputDataBuff, 1, streamHeader.dataLen, fp2);

			if (streamHeader.frameType == jo_video_i_frame ||
				streamHeader.frameType == jo_video_b_frame || streamHeader.frameType == jo_video_p_frame)
			{
				nResult = m_decoder->DecodeOneFrame(pInputDataBuff, streamHeader.dataLen, pOutputDataBuff, nOutputLen);
				if (nResult == J_OK && nOutputLen > 0)
				{
					streamHeader.dataLen = nOutputLen;
					m_vBuffer->PushBuffer(pOutputDataBuff, streamHeader);
				}
			}
		}
		else
		{
			continue;
		}
	}
	delete pInputDataBuff;
	delete pOutputDataBuff;
}

void CJoPlayer::OnRend()
{
	j_char_t *pDataBuff = new j_char_t[VIDEO_DATA_BUFF_LEN];
	J_StreamHeader streamHeader;
	j_result_t nResult = J_OK;
	while (m_bStart)
	{
		memset(&streamHeader, 0, sizeof(streamHeader));
		nResult = m_vBuffer->PopBuffer(pDataBuff, streamHeader);
		if (nResult == J_OK && streamHeader.dataLen > 0)
		{
			nResult = m_render->DisplayFrame(pDataBuff, streamHeader.dataLen);
		}
		else
		{
			continue;
		}
	}
	delete pDataBuff;
}