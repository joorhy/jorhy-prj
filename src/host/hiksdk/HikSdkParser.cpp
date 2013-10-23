#include "HikSdkParser.h"
#include "G722_1_1C_Float.h"

const char HIK_HEAD[5] = { 0x49, 0x4D, 0x4B, 0x48 };
const char PACK_HEAD[5] = { 0x00, 0x00, 0x01, 0xBA };
const char PSM_HEAD[5] = { 0x00, 0x00, 0x01, 0xBC };
const char VIDEO_HEAD[5] = { 0x00, 0x00, 0x01, 0xE0 };
const char AUDIO_HEAD[5] = { 0x00, 0x00, 0x01, 0xC0 };
const char H264_SPS_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x67};
const char H264_I_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x65 };
const char H264_P_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x41 };
const char H264_B_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x41 };

#define PACK_HEAD_LENGTH(x) ((*(x + 13) & 0x07) + 14)
#define PSM_HEAD_LENGTH(x) ((*(x + 4) & 0xFF) + (*(x + 5) & 0xFF) + 4)
#define VIDEO_HEAD_LENGTH(x) ((*(x + 8) & 0xFF) + 9)
#define VIDEO_DATA_LENGTH(x) ((*(x + 4) & 0xFF) + (*(x + 4) & 0xFF) \
									- (VIDEO_HEAD_LENGTH(x) - 6))
#define AUDIO_HEAD_LENGTH(x) VIDEO_HEAD_LENGTH(x)
#define AUDIO_DATA_LENGTH(x) VIDEO_DATA_LENGTH(x)

const unsigned short SKIP_FLAG = 0xF090;
const unsigned short H264_FLAG_I = 0x60A0;
const unsigned short H264_FLAG_P = 0xE0A0;
const unsigned short H264_FLAG_B = 0x6080;
const unsigned short H264_FLAG_PB = 0xE080;
const unsigned short G722_1_FLAG = 0xE280;

const unsigned short PACKET_I_HEAD = 0x857C;
const unsigned short PACKET_I_MID = 0x057C;
const unsigned short PACKET_I_END = 0x457C;
const unsigned short PACKET_P_HEAD = 0x815C;
const unsigned short PACKET_P_MID = 0x015C;
const unsigned short PACKET_P_END = 0x415C;
const unsigned short PACKET_B_HEAD = 0x813C;
const unsigned short PACKET_B_MID = 0x013C;
const unsigned short PACKET_B_END = 0x413C;

const int HIK_PACK_LEN = 16;
const int G722_PACK_LEN = 80;

const int HEAD_LEN = 4;
#define IS_H264_DATA(x) ((*(x+4) & 0x0F) == 7 || (*(x+4) & 0x0F) == 1)
#define IS_H264_OTHER(x) ((*(x+4) & 0x0F) == 8 || (*(x+4) & 0x0F) == 5 || (*(x+4) & 0x0F) == 6)
#define IS_H264_KEY(x)	((*(x+4) & 0x0F) == 7)

CHikSdkParser::CHikSdkParser()
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
	m_frameNum = 0;
}

CHikSdkParser::~CHikSdkParser()
{

}

int CHikSdkParser::Init(int nDataType)
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

int CHikSdkParser::Deinit()
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

int CHikSdkParser::InputData(const char *pData, int nLen)
{
	//WLock(m_rwLocker);
	//static FILE *fp = NULL;
	//if (fp == NULL)
    //    fp = fopen("test.hik", "wb+");
    //fwrite(pData, 1, nLen, fp);
	if (m_pDataBuff)
	{
		memcpy(m_pDataBuff + m_nDataSize, pData, nLen);
		m_nDataSize += nLen;
	}
	//RWUnlock(m_rwLocker);

	return J_OK;
}

int CHikSdkParser::GetOnePacket(char *pData, J_StreamHeader &streamHeader)
{
	//WLock(m_rwLocker);
	/*static bool bFirst = true;
	if (bFirst)
	{
	    streamHeader.frameType = J_MediaHead;
	    streamHeader.timeStamp = m_time.GetLocalTime(0);
	    streamHeader.dataLen = 40;

        memcpy(pData, m_pDataBuff + 4, 40);
        m_nDataSize -= 44;
        memmove(m_pDataBuff, m_pDataBuff + 44, m_nDataSize);
        bFirst = false;
        return J_OK;
	}*/

	if (m_pDataBuff == NULL)
	{
		//RWUnlock(m_rwLocker);
		return J_NOT_COMPLATE;
	}

	int nFrameType = jo_media_unknow;
	int i_data_flag = 0;
	int nLen = 0;

	int nAACLen = 0;
	unsigned char aacOutBuff[2048] = {0};

	//获得时间戳
	streamHeader.timeStamp = JoTime->GetLocalTime(0);
	m_bIsComplate = false;
	while (!m_bIsComplate)
	{
		if ((i_data_flag = GetDataFlag()) > 0)
		{
			int i_pack_length = 0;
			if ((m_pDataBuff[0] & 0xFF) == 0x03)
			{
				i_pack_length = HIK_PACK_LENGHT(m_pDataBuff);
			}
			else if ((m_pDataBuff[0] & 0xFF) == 0x24)
			{
				i_pack_length = HIK_PACK_LENGHT2(m_pDataBuff);
			}
			else
				printf("error pack type\n");

			if (m_nDataSize < i_pack_length)
			{
				nLen = 0;
				//RWUnlock(m_rwLocker);
				return J_NOT_COMPLATE;
			}

            /*switch (i_data_flag)
			{
			    case H264_TYPE:
                    streamHeader.frameType = J_VideoIFrame;
                    break;
                default:
                    streamHeader.frameType = J_AudioFrame;
                    break;
			}
			streamHeader.dataLen = i_pack_length;
			//printf("i_pack_length = %d\n", i_pack_length);
			memcpy(pData, m_pDataBuff, i_pack_length);
			m_bIsComplate = true;
			m_nDataSize -= i_pack_length;
			memmove(m_pDataBuff, m_pDataBuff + i_pack_length, m_nDataSize);*/

			switch (i_data_flag)
			{
			case SKIP_TYPE:
				m_nDataSize -= i_pack_length;
				memmove(m_pDataBuff, m_pDataBuff + i_pack_length, m_nDataSize);
				break;
			case H264_TYPE:
				{
					char *p_data_264 = m_pDataBuff + HIK_PACK_LEN;
					if (*(unsigned short *)(p_data_264) == PACKET_I_HEAD ||
							*(unsigned short *)(p_data_264) == PACKET_P_HEAD ||
							*(unsigned short *)(p_data_264) == PACKET_B_HEAD)
					{
						//printf("%02X %02X\n", *(unsigned char *)(p_data_264), *(unsigned char *)(p_data_264 + 1));
						if (*(unsigned short *)(p_data_264) == PACKET_I_HEAD)
						{
							memcpy(m_pOutBuff + m_nDataLen, H264_I_HEAD, 5);
						}
						else if (*(unsigned short *)(p_data_264) == PACKET_P_HEAD)
						{
							memcpy(m_pOutBuff + m_nDataLen, H264_P_HEAD, 5);
						}
						else if (*(unsigned short *)(p_data_264) == PACKET_B_HEAD)
						{
							memcpy(m_pOutBuff + m_nDataLen, H264_B_HEAD, 5);
						}
						else
							printf("H264_X_HEAD \n");

						m_nDataLen += 5;
						memcpy(m_pOutBuff + m_nDataLen, p_data_264 + 2, (i_pack_length - HIK_PACK_LEN - 2));
						m_nDataLen += (i_pack_length - HIK_PACK_LEN - 2);
					}
					else if (*(unsigned short *)(p_data_264) == PACKET_I_MID ||
							*(unsigned short *)(p_data_264) == PACKET_I_END ||
							*(unsigned short *)(p_data_264) == PACKET_P_MID ||
							*(unsigned short *)(p_data_264) == PACKET_P_END ||
							*(unsigned short *)(p_data_264) == PACKET_B_MID ||
							*(unsigned short *)(p_data_264) == PACKET_B_END)
					{
						//printf("%02X %02X\n", *(unsigned char *)(p_data_264), *(unsigned char *)(p_data_264 + 1));
						if (*(unsigned short *)(p_data_264) == PACKET_I_END ||
								*(unsigned short *)(p_data_264) == PACKET_P_END ||
								*(unsigned short *)(p_data_264) == PACKET_B_END)
						{
							m_bIsComplate = true;
							nFrameType = jo_video_p_frame;
						}

						memcpy(m_pOutBuff + m_nDataLen, p_data_264 + 2, (i_pack_length - HIK_PACK_LEN - 2));
						m_nDataLen += (i_pack_length - HIK_PACK_LEN - 2);
					}
					else
					{
						if (!(*(unsigned char *)(p_data_264) == 0x67 || *(unsigned char *)(p_data_264) == 0x68))
						{
							m_bIsComplate = true;
						}

						nFrameType = jo_video_p_frame;
						memcpy(m_pOutBuff + m_nDataLen, H264_I_HEAD, 4);
						m_nDataLen += 4;
						memcpy(m_pOutBuff + m_nDataLen, p_data_264, i_pack_length - HIK_PACK_LEN);
						m_nDataLen += i_pack_length - HIK_PACK_LEN;
					}
					m_nDataSize -= i_pack_length;
					memmove(m_pDataBuff, m_pDataBuff + i_pack_length, m_nDataSize);
				}
				break;
			case G722_1_TYPE:
				{
					if (i_pack_length - HIK_PACK_LEN > MAX_BITS_PER_FRAME / 16 * 2)
					{
						printf("error audio data\n");
						//RWUnlock(m_rwLocker);
						return J_NOT_COMPLATE;
					}

					if (i_pack_length - HIK_PACK_LEN > 80)
						J_OS::LOGINFO("i_pack_length - HIK_PACK_LEN == %d", i_pack_length - HIK_PACK_LEN);

					short int out_words[MAX_BITS_PER_FRAME / 16];
					memcpy(out_words, m_pDataBuff + HIK_PACK_LEN, i_pack_length - HIK_PACK_LEN);
					G722_1_1C_Float_decoder(m_pAudioCache + m_nSamples, out_words, 16000, 7000);
					m_nSamples += 320;
					G722_1_1C_Float_decoder(m_pAudioCache + m_nSamples, out_words + 20, 16000, 7000);
					m_nSamples += 320;

					m_nDataSize -= i_pack_length;
					memmove(m_pDataBuff, m_pDataBuff + i_pack_length, m_nDataSize);

					if (m_nSamples >= m_nInputSamples)
					{
						if ((void *)faacEncEncode == NULL)
							break;

						if ((nAACLen = faacEncEncode(m_aacHandle, (int32_t *)m_pAudioCache, m_nInputSamples, aacOutBuff + nAACLen, m_nOutputBytes)) > 0)
						{
							m_bIsComplate = true;
							nFrameType = jo_audio_frame;

							m_nSamples -= m_nInputSamples;
							memmove(m_pAudioCache, m_pAudioCache + m_nInputSamples, m_nInputSamples * 2);
						}
					}
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
		if (nFrameType == jo_video_p_frame)
		{
			if (memcmp(m_pOutBuff, H264_SPS_HEAD, 5) == 0)
				nFrameType = jo_video_i_frame;

			memcpy(pData, m_pOutBuff, m_nDataLen);
			nLen = m_nDataLen;
			m_nDataLen = 0;
			streamHeader.frameNum = m_frameNum++;
			m_frameNum %= 0xFFFFFFFF;
		}
		else if (nFrameType == jo_audio_frame)
		{
			memcpy(pData, aacOutBuff, nAACLen);
			nLen = nAACLen;
		}

		m_bIsComplate = false;
		if (nLen > 0)
		{
			streamHeader.frameType = nFrameType;
			streamHeader.dataLen = nLen;
			//获得时间戳
			//streamHeader.timeStamp = m_time.GetLocalTime(0);
		}
		else
		{
			//RWUnlock(m_rwLocker);
			return J_NOT_COMPLATE;
		}
	}
	else
	{
		//RWUnlock(m_rwLocker);
		return J_NOT_COMPLATE;
	}
	//RWUnlock(m_rwLocker);


	return J_OK;
}

int CHikSdkParser::GetDataFlag()
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
			b_loop = false;

		if (*(unsigned short *)(p_data + 4) == SKIP_FLAG)
		{
			i_data_flag = SKIP_TYPE;
			b_loop = false;
		}
		else if (*(unsigned short *)(p_data + 4) == H264_FLAG_I
				|| *(unsigned short *)(p_data + 4) == H264_FLAG_P
				|| *(unsigned short *)(p_data + 4) == H264_FLAG_B
				|| *(unsigned short *)(p_data + 4) == H264_FLAG_PB)
		{
			i_data_flag = H264_TYPE;
			b_loop = false;
		}
		else if (*(unsigned short *)(p_data + 4) == G722_1_FLAG)
		{
			i_data_flag = G722_1_TYPE;
			b_loop = false;
		}
		else
		{
			++i_offset;
			printf("data flag = %X %X\n", p_data[4] & 0xFF, p_data[5] & 0xFF);
		}
	}

	if (i_offset > 0)
	{
		memmove(m_pDataBuff, m_pDataBuff + i_offset, m_nDataSize - i_offset);
	}

	return i_data_flag;
}
