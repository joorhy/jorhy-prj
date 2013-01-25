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
}

CDahuaParser::~CDahuaParser()
{

}

int CDahuaParser::Init(int nDataType)
{
	m_parser = DHSP_Init(0, 0);
		
	return J_OK;
}

int CDahuaParser::Deinit()
{
	DHSP_Free(m_parser);
	
	return J_OK;
}

int CDahuaParser::InputData(const char *pData, int nLen)
{
	/*static FILE *fp = NULL;
	if (fp == NULL)
        fp = fopen("dahua.hik", "wb+");
    fwrite(pData, 1, nLen, fp);
	fflush(fp);*/
	DHSP_InputData(m_parser, (unsigned char *)pData, nLen);
	
	return J_OK;
}

int CDahuaParser::GetOnePacket(char *pData, J_StreamHeader &streamHeader)
{
	if ((m_frame = DHSP_GetNextFrame(m_parser)) != NULL)
	{
		if (m_frame->nFrameLength == 0)
			return J_NOT_COMPLATE;
			
		streamHeader.timeStamp = CTime::Instance()->GetLocalTime(0);
		streamHeader.dataLen = 0;
		if (m_frame->nType == DH_FRAME_TYPE_VIDEO)
		{
			streamHeader.dataLen = m_frame->nFrameLength;
			if (m_frame->nSubType == DH_FRAME_TYPE_VIDEO_I_FRAME)
			{
				streamHeader.frameType = J_VideoIFrame;
			}
			else
			{
				streamHeader.frameType = J_VideoPFrame;
			}
			memcpy(pData, m_frame->pContent, m_frame->nFrameLength);
		}
		return J_OK;
	}

	return J_NOT_COMPLATE;
}