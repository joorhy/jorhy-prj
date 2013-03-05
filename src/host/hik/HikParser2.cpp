#include "HikParser2.h"
#include "G722_1_1C_Float.h"

const char PACK_HEAD[5] = { 0x00, 0x00, 0x01, 0xBA };
const char PSM_HEAD[5] = { 0x00, 0x00, 0x01, 0xBC };
const char VIDEO_HEAD[5] = { 0x00, 0x00, 0x01, 0xE0 };
const char AUDIO_HEAD[5] = { 0x00, 0x00, 0x01, 0xC0 };
const char H264_SPS_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x67};
const char H264_I_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x65 };
const char H264_P_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x61 };
const char H264_SEI_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x06 };
const char H264_AUD_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x09 };

#define VIDEO_HEAD_LENGTH(x) ((*(x + 8) & 0xFF) + 9)
#define VIDEO_DATA_LENGTH(x) (((*(x + 4) & 0xFF) << 8) + (*(x + 5) & 0xFF) \
									- (VIDEO_HEAD_LENGTH(x) - 6))
#define AUDIO_HEAD_LENGTH(x) VIDEO_HEAD_LENGTH(x)
#define AUDIO_DATA_LENGTH(x) VIDEO_DATA_LENGTH(x)

const int HEAD_LEN = 4;
#define IS_H264_DATA(x) ((*(x+4) & 0x0F) == 7 || (*(x+4) & 0x0F) == 1)
#define IS_H264_OTHER(x) ((*(x+4) & 0x0F) == 8 || (*(x+4) & 0x0F) == 5 || (*(x+4) & 0x0F) == 6)
#define IS_H264_KEY(x)	((*(x+4) & 0x0F) == 7)

#define HIK_PACK_LEN 4

CHikParser2::CHikParser2()
{
	m_nDataSize = 0;
	m_pOutBuff = NULL;

	m_bIsComplate = false;
	m_nDataLen = 0;

	m_pAudioCache = NULL;
	m_nSamples = 0;

	m_aacHandle = NULL;
	m_nInputSamples = 0;
	m_nOutputBytes = 0;
}

CHikParser2::~CHikParser2()
{

}

int CHikParser2::Init(int nDataType)
{
	if (m_pOutBuff == NULL)
		m_pOutBuff = new char[1024 * 1024 * 2];

	if (m_pAudioCache == NULL)
		m_pAudioCache = new short int[1024 * 10];

	//初始化G.722.1解码库
	mlt_based_coder_init();

	//初始化AAC编码库
	m_aacHandle = faacEncOpen(16000, 1, &m_nInputSamples, &m_nOutputBytes);
	faacEncConfigurationPtr pAacConfig = faacEncGetCurrentConfiguration(m_aacHandle);
	pAacConfig->aacObjectType = MAIN;
	pAacConfig->mpegVersion = MPEG4;
	pAacConfig->useTns = 0;
	pAacConfig->allowMidside = 1;
	pAacConfig->outputFormat = 1;
	pAacConfig->bitRate = 16 * 1024;
	pAacConfig->bandWidth = 0;
	pAacConfig->inputFormat = FAAC_INPUT_16BIT;
	faacEncSetConfiguration(m_aacHandle, pAacConfig);
	//delete pAacConfig;

	return J_OK;
}

int CHikParser2::Deinit()
{
	if (m_pOutBuff != NULL)
	{
		delete m_pOutBuff;
		m_pOutBuff = NULL;
	}

	WLock(m_rwLocker);
	if (m_aacHandle != NULL)
	{
		//faacEncClose(m_aacHandle);
		m_aacHandle = NULL;
	}

	if (m_pAudioCache != NULL)
	{
		delete m_pAudioCache;
		m_pAudioCache = NULL;
	}

	RWUnlock(m_rwLocker);

	return J_OK;
}

int CHikParser2::InputData(const char *pData, int nLen)
{
	if (memcmp(pData, VIDEO_HEAD, 4) == 0)
	{		
		int i_head_length = VIDEO_HEAD_LENGTH(pData);
		int i_data_length = VIDEO_DATA_LENGTH(pData);
		const char *p_data_264 = pData + i_head_length;
		if (m_bPreComplate && (memcmp(p_data_264, H264_I_HEAD, 4) == 0))
		{
			m_bIsComplate = true;
			m_nFrameLen = m_nDataLen;
			m_bPreComplate = false;
		}
	
		if ((memcmp(p_data_264, H264_I_HEAD, 5) == 0) 
			|| (memcmp(p_data_264, H264_P_HEAD, 5) == 0))
		{
			m_bPreComplate = true;
		}
		
		if (!((memcmp(p_data_264, H264_SEI_HEAD, 5) == 0) || (memcmp(p_data_264, H264_AUD_HEAD, 5) == 0)))
		{
			/*static FILE *fp = NULL;
			if (fp == NULL)
				fp = fopen("/home/jorhy/share/hik3.h264", "wb+");
			fwrite(p_data_264, 1, i_data_length, fp);*/
			
			memcpy(m_pOutBuff + m_nDataLen, p_data_264, i_data_length);
			m_nDataLen += i_data_length;
		}
	}

	return J_OK;
}

int CHikParser2::GetOnePacket(char *pData, J_StreamHeader &streamHeader)
{
	if (m_bIsComplate)
	{
		//获得时间戳
		streamHeader.timeStamp = CTime::Instance()->GetLocalTime(0);
		streamHeader.frameType = (memcmp(m_pOutBuff, H264_SPS_HEAD, 5) == 0) ? J_VideoIFrame : J_VideoPFrame;
		streamHeader.dataLen = m_nFrameLen;
		m_nDataLen -= m_nFrameLen;
		memcpy(pData, m_pOutBuff, m_nFrameLen);
		memmove(m_pOutBuff, m_pOutBuff + m_nFrameLen, m_nDataLen);
		
		m_bIsComplate = false;
	}
	else
	{
		return J_NOT_COMPLATE;
	}

	return J_OK;
}