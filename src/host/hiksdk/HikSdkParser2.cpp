#include "HikSdkParser2.h"
#include "G722_1_1C_Float.h"

const char PACK_HEAD[5] = { 0x00, 0x00, 0x01, 0xBA };
const char PSM_HEAD[5] = { 0x00, 0x00, 0x01, 0xBC };
const char VIDEO_HEAD[5] = { 0x00, 0x00, 0x01, 0xE0 };
const char AUDIO_HEAD[5] = { 0x00, 0x00, 0x01, 0xC0 };
const char H264_SPS_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x67};
const char H264_PPS_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x68};
const char H264_I_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x65 };
const char H264_P_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x61 };
const char H264_P_HEAD2[6] = { 0x00, 0x00, 0x00, 0x01, 0x41 };
const char H264_P_HEAD3[6] = { 0x00, 0x00, 0x00, 0x01, 0x21 };
const char H264_SEI_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x06 };
const char H264_AUD_HEAD[6] = { 0x00, 0x00, 0x00, 0x01, 0x09 };


#define PACK_HEAD_LENGTH(x) ((*(x + 13) & 0x07) + 14)
#define PSM_HEAD_LENGTH(x) ((*(x + 4) & 0xFF) + (*(x + 5) & 0xFF) + 6)
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

CHikSdkParser2::CHikSdkParser2()
{
	m_pDataBuff = NULL;
	m_pOutBuff = NULL;

	m_bIsComplate = false;
	m_nDataLen = 0;
	m_nDataSize = 0;

	m_frameNum = 0;
}

CHikSdkParser2::~CHikSdkParser2()
{

}

int CHikSdkParser2::Init(int nDataType)
{
	if (m_pDataBuff == NULL)
		m_pDataBuff = new char[1024 * 1024 * 2];
	if (m_pOutBuff == NULL)
		m_pOutBuff = new char[1024 * 1024 * 2];

	return J_OK;
}

int CHikSdkParser2::Deinit()
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

	return J_OK;
}

int CHikSdkParser2::InputData(const char *pData, int nLen)
{
	if (m_pDataBuff)
	{
		memcpy(m_pDataBuff + m_nDataSize, pData, nLen);
		m_nDataSize += nLen;
		//J_OS::LOGINFO("m_nDataSize = %d nLen = %d", m_nDataSize, nLen);
	}

	return J_OK;
}

int CHikSdkParser2::GetOnePacket(char *pData, J_StreamHeader &streamHeader)
{
	while (!m_bIsComplate && m_nDataSize > 0)
	{
		int nMoveLen = 0;
		if (memcmp(m_pDataBuff, PACK_HEAD, 4) == 0)
		{
			nMoveLen = PACK_HEAD_LENGTH(m_pDataBuff);
			if (nMoveLen > m_nDataSize)
				return J_NOT_COMPLATE;
			m_nDataSize -= nMoveLen;
			memmove(m_pDataBuff, m_pDataBuff + nMoveLen, m_nDataSize);
		}
		else if (memcmp(m_pDataBuff, PSM_HEAD, 4) == 0)
		{
			nMoveLen = PSM_HEAD_LENGTH(m_pDataBuff);
			if (nMoveLen > m_nDataSize)
				return J_NOT_COMPLATE;
			m_nDataSize -= nMoveLen;
			memmove(m_pDataBuff, m_pDataBuff + nMoveLen, m_nDataSize);
		}
		else if (memcmp(m_pDataBuff, VIDEO_HEAD, 4) == 0)
		{
			nMoveLen = VIDEO_HEAD_LENGTH(m_pDataBuff);
			if (nMoveLen > m_nDataSize)
				return J_NOT_COMPLATE;
			int i_data_length = VIDEO_DATA_LENGTH(m_pDataBuff);
			const char *p_data_264 = m_pDataBuff + nMoveLen;
			if ((memcmp(p_data_264, H264_SPS_HEAD, 5) == 0) 
				|| (memcmp(p_data_264, H264_PPS_HEAD, 5) == 0))
			{
				memcpy(m_pOutBuff + m_nDataLen, p_data_264, i_data_length);
				m_nDataLen += i_data_length;
				
				nMoveLen += i_data_length;
			}
			else if ((memcmp(p_data_264, H264_I_HEAD, 5) == 0) 
				|| (memcmp(p_data_264, H264_P_HEAD, 5) == 0)
				|| (memcmp(p_data_264, H264_P_HEAD2, 5) == 0)
				|| (memcmp(p_data_264, H264_P_HEAD3, 5) == 0))
			{
				if (nMoveLen + i_data_length <= m_nDataSize)
				{
					memcpy(m_pOutBuff + m_nDataLen, p_data_264, i_data_length);
					m_nDataLen += i_data_length;
					m_bIsComplate = true;
					nMoveLen += i_data_length;
				}
				else
				{
					return J_NOT_COMPLATE;
				}
			}
			else
			{
				nMoveLen += i_data_length;
				if (nMoveLen > m_nDataSize)
					return J_NOT_COMPLATE;
			}
			if (nMoveLen > m_nDataSize)
					return J_NOT_COMPLATE;
			m_nDataSize -= nMoveLen;
			memmove(m_pDataBuff, m_pDataBuff + nMoveLen, m_nDataSize);
		}
		else if (memcmp(m_pDataBuff, AUDIO_HEAD, 4) == 0)
		{
			nMoveLen = AUDIO_HEAD_LENGTH(m_pDataBuff);
			if (nMoveLen > m_nDataSize)
				return J_NOT_COMPLATE;
			nMoveLen += AUDIO_DATA_LENGTH(m_pDataBuff);
			if (nMoveLen > m_nDataSize)
				return J_NOT_COMPLATE;
			m_nDataSize -= nMoveLen;
			memmove(m_pDataBuff, m_pDataBuff + nMoveLen, m_nDataSize);
		}
	}
	
	if (m_bIsComplate)
	{
		//获得时间戳;
		streamHeader.timeStamp = JoTime->GetLocalTime(0);
		streamHeader.frameType = (memcmp(m_pOutBuff, H264_SPS_HEAD, 5) == 0) ? jo_video_i_frame : jo_video_p_frame;
		streamHeader.dataLen = m_nDataLen;
		memcpy(pData, m_pOutBuff, m_nDataLen);
		streamHeader.frameNum = m_frameNum++;
		m_frameNum %= 0xFFFFFFFF;
		m_nDataLen = 0;
		m_bIsComplate = false;
		return J_OK;
	}
	

	return J_NOT_COMPLATE;
}