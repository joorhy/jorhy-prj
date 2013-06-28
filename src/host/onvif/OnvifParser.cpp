#include "OnvifParser.h"

const char H264_HEAD[] = {0x00, 0x00, 0x00, 0x01};

COnvifParser::COnvifParser()
{
	m_pOutBuff = NULL;
	m_nDataSize = 0;
	m_nOffset = 0;
	m_bStartSlice = true;
	m_bIsComplate = false;
	m_frameNum = 0;
}

COnvifParser::~COnvifParser()
{

}

int COnvifParser::Init(int nDataType)
{
	if (m_pOutBuff == NULL)
		m_pOutBuff = new char[1024 * 1024 * 10];

	return J_OK;
}

int COnvifParser::Deinit()
{
	if (m_pOutBuff != NULL)
	{
		delete m_pOutBuff;
		m_pOutBuff = NULL;
	}

	return J_OK;
}

int COnvifParser::InputData(const char *pData, int nLen)
{
	const char *pEsData = pData + 16;
	bool is_padding = false;
	int nLength = ((pData[2] & 0xFF) << 8) + (pData[3] & 0xFF);
	if ((pData[1] & 0xFF) == 0x00)
	{
		if (pData[5] & 0x80)
			m_bIsComplate = true;
		if (pData[4] & 0x20)
			is_padding = true;
			
		int nal_unit_type = pEsData[0] & 0x1f;
		if (nal_unit_type == 28)
		{
			if (pEsData[1] & 0x80)
			{
				memcpy(m_pOutBuff + m_nOffset, H264_HEAD, 4);
				m_nOffset += 4;
				int forbidden_bit = pEsData[0] & 0x80;
				int nal_reference_idc = (pEsData[0] & 0x60);
				nal_unit_type = pEsData[1] & 0x1f;
				m_pOutBuff[m_nOffset] = forbidden_bit + nal_reference_idc + nal_unit_type;
				m_nOffset += 1;
			}
			memcpy(m_pOutBuff + m_nOffset, pEsData + 2, nLength - 12 - 2);
			m_nOffset += nLength - 12 - 2;
		}
		else
		{
			//printf("nal_unit_type = %d\n", nal_unit_type);
			memcpy(m_pOutBuff + m_nOffset, H264_HEAD, 4);
			m_nOffset += 4;
			if (!(nal_unit_type == 7 || nal_unit_type == 8))
			{
				m_bIsComplate = true;
			}
				
			memcpy(m_pOutBuff + m_nOffset, pEsData, nLength - 12);
			m_nOffset += nLength - 12;
		}
		if (is_padding)
		{
			m_nOffset -= (*(m_pOutBuff + m_nOffset - 1) & 0xFF);
		}
	}

	return J_OK;
}

int COnvifParser::GetOnePacket(char *pData, J_StreamHeader &streamHeader)
{
	memset(&streamHeader, 0, sizeof(J_StreamHeader));
	if (m_bIsComplate)
	{
		streamHeader.frameType = jo_video_p_frame;
		if (m_pOutBuff[4] == 0x67)
			streamHeader.frameType = jo_video_i_frame;
		streamHeader.dataLen = m_nOffset;
		streamHeader.timeStamp = SingletonTmpl<CTime>::Instance()->GetLocalTime(0);
		streamHeader.frameNum = m_frameNum++;
		m_frameNum %= 0xFFFFFFFF;
		memcpy(pData, m_pOutBuff, m_nOffset);
		m_nOffset = 0;
		m_bIsComplate = false;
		return J_OK;
	}
	
	return J_NOT_COMPLATE;
}
