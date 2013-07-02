#include "DahuaParser.h"

#define DH_PACK_LEN		32
#define DH_VIDEO_I		1
#define DH_VIDEO_P		2
#define DH_AUDIO		3

const char DH_VIDEO_I_HEAD[8] = { 0x44, 0x48, 0x41, 0x56, 0xFD, 0x00, 0x00, 0x00};
const char DH_VIDEO_P_HEAD[8] = { 0x44, 0x48, 0x41, 0x56, 0xFC, 0x00, 0x00, 0x00};
const char DH_AUDIO_HEAD[8] = { 0x44, 0x48, 0x41, 0x56, 0xF0, 0x00, 0x00, 0x00};
#define DH_PACK_LENGTH(x) (((*(x + 15) & 0xFF) << 24) + ((*(x + 14) & 0xFF) << 16) + \
							((*(x + 13) & 0xFF) << 8) + (*(x + 12) & 0xFF) )

CDahuaParser::CDahuaParser()
{
	m_parser = NULL;
	m_frameNum = 0;
}

CDahuaParser::~CDahuaParser()
{

}

int CDahuaParser::Init(int nDataType)
{
	ANA_CreateStream(2 * 1024 * 1024, &m_parser);
		
	return J_OK;
}

int CDahuaParser::Deinit()
{
	ANA_Destroy(m_parser);
	
	return J_OK;
}

int CDahuaParser::InputData(const char *pData, int nLen)
{
	/*static FILE *fp = NULL;
	if (fp == NULL)
        fp = fopen("dahua.hik", "wb+");
    fwrite(pData, 1, nLen, fp);
	fflush(fp);*/
	ANA_InputData(m_parser, (unsigned char *)pData, nLen);
	
	return J_OK;
}

int CDahuaParser::GetOnePacket(char *pData, J_StreamHeader &streamHeader)
{
	if (ANA_GetNextFrame(m_parser, &m_frame) == 0)
	{
		if (m_frame.nBodyLength == 0)
			return J_NOT_COMPLATE;
			
		streamHeader.timeStamp = GetTimeLayer()->GetLocalTime(0);
		streamHeader.dataLen = 0;
		if (m_frame.nType == FRAME_TYPE_VIDEO)
		{
			if (m_frame.nSubType == TYPE_VIDEO_I_FRAME)
			{
				streamHeader.frameType = jo_video_i_frame;
			}
			else
			{
				streamHeader.frameType = jo_video_p_frame;

			}
			streamHeader.frameNum = m_frameNum++;
			m_frameNum %= 0xFFFFFFFF;
			streamHeader.dataLen = m_frame.nBodyLength;
			memcpy(pData, m_frame.pFrameBody, m_frame.nBodyLength);
		}
		else 
		{
			//printf("dahua data type = %d\n", m_frame.nType);
		}
		return J_OK;
	}

	return J_NOT_COMPLATE;
}