#include "OnvifParser.h"

COnvifParser::COnvifParser()
{
	m_pDataBuff = NULL;
	m_pOutBuff = NULL;
	m_nDataSize = 0;
	m_nOffset = 0;
	m_bStartSlice = true;
	m_bIsComplate = false;
}

COnvifParser::~COnvifParser()
{

}

int COnvifParser::Init(int nDataType)
{
	if (m_pDataBuff == NULL)
		m_pDataBuff = new char[1024 * 1024];
	
	if (m_pOutBuff == NULL)
		m_pOutBuff = new char[1024 * 1024];

	return J_OK;
}

int COnvifParser::Deinit()
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

int COnvifParser::InputData(const char *pData, int nLen)
{
	memcpy(m_pDataBuff + m_nDataSize, pData, nLen);
	m_nDataSize += nLen;

	return J_OK;
}

int COnvifParser::GetOnePacket(char *pData, J_StreamHeader &streamHeader)
{
	if (m_nDataSize < 4)
		return J_NOT_COMPLATE;
		
	int nLength = 0;
	char *pEsData = NULL;
	m_bIsComplate = false;
	//获得时间戳
	streamHeader.timeStamp = CTime::Instance()->GetLocalTime(0);
	streamHeader.frameType = J_VideoPFrame;
	while (!m_bIsComplate)
	{
		assert((m_pDataBuff[0] & 0xFF) == 0x24);
		nLength = ((m_pDataBuff[2] & 0xFF) << 8) + (m_pDataBuff[3] & 0xFF); 
		if (m_nDataSize < (nLength + 4))
			return J_NOT_COMPLATE;
			
		if ((m_pDataBuff[1] & 0xFF) == 0x00)
		{
			if (m_pDataBuff[5] & 0x80)
				m_bIsComplate = true;
				
			if (m_bStartSlice)
			{
				m_pOutBuff[m_nOffset] = 0x00;
				m_pOutBuff[m_nOffset + 1] = 0x00;
				m_pOutBuff[m_nOffset + 2] = 0x00;
				m_pOutBuff[m_nOffset + 3] = 0x01;
				m_nOffset += 4;
			}
			pEsData = m_pDataBuff + 16;
			int nal_unit_type = pEsData[0] & 0x1f;
			if (nal_unit_type == 28) //FU_A
			{
				if (pEsData[1] & 0x80)
				{
					int forbidden_bit = pEsData[0] & 0x80;
					int nal_reference_idc = (pEsData[0] & 0x60);
					nal_unit_type = pEsData[1] & 0x1f;
					m_pOutBuff[m_nOffset] = forbidden_bit + nal_reference_idc + nal_unit_type;
					m_nOffset += 1;
				}
				memcpy(m_pOutBuff + m_nOffset, pEsData + 2, nLength - 12 - 2);
				m_nOffset += nLength - 12 - 2;
				m_bStartSlice = false;
			}
			else
			{
				if (nal_unit_type == 7)
					streamHeader.frameType = J_VideoIFrame;
					
				memcpy(m_pOutBuff + m_nOffset, pEsData, nLength - 12);
				m_nOffset += nLength - 12;
				m_bStartSlice = true;
			}
		}
		m_nDataSize -= nLength + 4;
		memmove(m_pDataBuff, m_pDataBuff + nLength + 4, m_nDataSize);
	}
	static FILE *fp = NULL;
	if (fp == NULL)
		fp = fopen("test.h264", "wb+");
	fwrite(m_pOutBuff, 1, m_nOffset, fp);
	streamHeader.dataLen = m_nOffset;
	memcpy(pData, m_pOutBuff, m_nOffset);
	m_nOffset = 0;
	m_bStartSlice = true;
	
	return J_OK;
}
