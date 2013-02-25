#include "HikParser2.h"
#include "G722_1_1C_Float.h"

const char HIK_HEAD[5] = { 0x49, 0x4D, 0x4B, 0x48 };
const char PACK_HEAD[5] = { 0x00, 0x00, 0x01, 0xBA };
const char PSM_HEAD[5] = { 0x00, 0x00, 0x01, 0xBC };
const char PRIVATE_STREAM_HEAD[5] = { 0x00, 0x00, 0x01, 0xBD };
const char VIDEO_HEAD[5] = { 0x00, 0x00, 0x01, 0xE0 };
const char AUDIO_HEAD[5] = { 0x00, 0x00, 0x01, 0xC0 };
const char H264_SPS_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x67};
const char H264_I_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x65 };
const char H264_P_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x61 };

#define PACK_HEAD_LENGTH(x) ((*(x + 13) & 0x07) + 14)
#define PSM_HEAD_LENGTH(x) (((*(x + 4) & 0xFF) << 8) + (*(x + 5) & 0xFF) + 6)
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
	m_pDataBuff = NULL;
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
	if (m_pDataBuff == NULL)
		m_pDataBuff = new char[1024 * 1024];

	if (m_pOutBuff == NULL)
		m_pOutBuff = new char[1024 * 1024];

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
	if (m_pDataBuff != NULL)
	{
		delete m_pDataBuff;
		m_pDataBuff = NULL;
	}

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
	if (m_pDataBuff)
	{
		/*static FILE *fp = NULL;
		if (fp == NULL)
			fp = fopen("test.hik", "wb+");
		fwrite(pData, 1, nLen, fp);*/
		
		memcpy(m_pDataBuff + m_nDataSize, pData, nLen);
		m_nDataSize += nLen;
	}

	return J_OK;
}

int CHikParser2::GetOnePacket(char *pData, J_StreamHeader &streamHeader)
{
	if (m_pDataBuff == NULL)
	{
		return J_NOT_COMPLATE;
	}

	int nFrameType = J_MediaUnknow;
	int i_data_flag = 0;
	int nLen = 0;

	int nAACLen = 0;
	unsigned char aacOutBuff[2048] = {0};

	m_bIsPrepared = false;
	m_bIsComplate = false;
	while (!m_bIsComplate)
	{
		if ((i_data_flag = GetDataFlag()) > 0)
		{
			int i_pack_length = 0;
			switch (i_data_flag)
			{
				case PACKHEAD_TYPE:
					i_pack_length = PACK_HEAD_LENGTH(m_pDataBuff);
					break;
				case PSM_TYPE:
					i_pack_length = PSM_HEAD_LENGTH(m_pDataBuff);
					break;
				case H264_TYPE: case G722_1_TYPE:
					i_pack_length = VIDEO_HEAD_LENGTH(m_pDataBuff) + VIDEO_DATA_LENGTH(m_pDataBuff);
					break;
				default:
					printf("type error\n");
					break;
			}

			if (m_nDataSize < i_pack_length)
			{
				nLen = 0;
				return J_NOT_COMPLATE;
			}

			switch (i_data_flag)
			{
			case PACKHEAD_TYPE: case PSM_TYPE: case G722_1_TYPE:
				m_nDataSize -= i_pack_length;
				memmove(m_pDataBuff, m_pDataBuff + i_pack_length, m_nDataSize);
				break;
			case H264_TYPE:
				{
					//fprintf(stderr, "len1 = %d\n", i_pack_length);
					char *p_data_264 = m_pDataBuff + VIDEO_HEAD_LENGTH(m_pDataBuff);
					if (memcmp(p_data_264, H264_I_HEAD, 5) == 0)
					{
						m_bIsComplate = true;
						nFrameType = J_VideoIFrame;
					}
					else if (memcmp(p_data_264, H264_P_HEAD, 5) == 0)
					{
						m_bIsComplate = true;
						nFrameType = J_VideoPFrame;
					}
					/*if (m_bIsPrepared && memcmp(p_data_264, H264_I_HEAD, 4) == 0)*/
					else
					{
						if (memcmp(p_data_264, H264_I_HEAD, 4) != 0)
						{
							//for (int i = 0; i < i_pack_length; i++)
							//	fprintf(stderr, "%02X ", m_pDataBuff[i] & 0xFF);
							//fprintf(stderr, "len = %d\n", i_pack_length);
							//memcpy(m_pOutBuff + m_nDataLen, H264_I_HEAD, 5);
							//m_nDataLen += 5;
							//m_bIsComplate = true;
							//nFrameType = J_VideoPFrame;
						}
					}
					memcpy(m_pOutBuff + m_nDataLen, p_data_264, VIDEO_DATA_LENGTH(m_pDataBuff));
					m_nDataLen += VIDEO_DATA_LENGTH(m_pDataBuff);
					m_nDataSize -= i_pack_length;
					memmove(m_pDataBuff, m_pDataBuff + i_pack_length, m_nDataSize);
				}
				break;
			}
		}
		else
		{
			return J_NOT_COMPLATE;
		}
	}

	if (m_bIsComplate)
	{
		//获得时间戳
		streamHeader.timeStamp = CTime::Instance()->GetLocalTime(0);
		if (nFrameType == J_VideoIFrame || nFrameType == J_VideoPFrame)
		{
			memcpy(pData, m_pOutBuff, m_nDataLen);
			//if (memcmp(pData, H264_I_HEAD, 4) != 0)
			//	fprintf(stderr, "h264 %02x %02x %02x %02x\n", pData[0], pData[1], pData[2], pData[3]);
			nLen = m_nDataLen;
			m_nDataLen = 0;
		}
		else if (nFrameType == J_AudioFrame)
		{
			memcpy(pData, aacOutBuff, nAACLen);
			nLen = nAACLen;
		}

		m_bIsComplate = false;
		if (nLen > 0)
		{
			streamHeader.frameType = nFrameType;
			streamHeader.dataLen = nLen;
			return J_OK;
		}
		else
		{
			return J_NOT_COMPLATE;
		}
	}
	else
	{
		return J_NOT_COMPLATE;
	}

	return J_OK;
}

int CHikParser2::GetDataFlag()
{
	if (m_nDataSize < HIK_PACK_LEN)
		return 0;

	int i_data_flag = 0;

	bool b_loop = true;
	int i_offset = 0;
	while (b_loop && m_pDataBuff)
	{
		char *p_data = m_pDataBuff + i_offset;
		if ((i_offset + HIK_PACK_LEN) > m_nDataSize)
			break;

		if (memcmp(p_data, PACK_HEAD, 4) == 0)
		{
			i_data_flag = PACKHEAD_TYPE;
			b_loop = false;
		}
		else if (memcmp(p_data, PSM_HEAD, 4) == 0)
		{
			i_data_flag = PSM_TYPE;
			b_loop = false;
		}
		else if (memcmp(p_data, PRIVATE_STREAM_HEAD, 4) == 0)
		{
			i_data_flag = PSM_TYPE;
			b_loop = false;
		}
		else if (memcmp(p_data, VIDEO_HEAD, 4) == 0)
		{
			i_data_flag = H264_TYPE;
			b_loop = false;
		}
		else if (memcmp(p_data, AUDIO_HEAD, 4) == 0)
		{
			i_data_flag = G722_1_TYPE;
			b_loop = false;
		}
		else
		{
			++i_offset;
			printf("data flag = %X %X %X %X\n", p_data[0] & 0xFF, p_data[1] & 0xFF,
				p_data[2] & 0xFF, p_data[3] & 0xFF);
		}
	}

	if (i_offset > 0)
	{
		memmove(m_pDataBuff, m_pDataBuff + i_offset, m_nDataSize - i_offset);
	}

	return i_data_flag;
}
