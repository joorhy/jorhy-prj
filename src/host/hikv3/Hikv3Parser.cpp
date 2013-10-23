#include "Hikv3Parser.h"

CHikv3Parser::CHikv3Parser()
{
	m_hNewHandle = NULL;
	m_nDataSize = 0;

	J_OS::LOGINFO("CHikv3Parser::CHikv3Parser created");
}

CHikv3Parser::~CHikv3Parser()
{
	if (m_hNewHandle != NULL)
		Deinit();

	J_OS::LOGINFO("CHikv3Parser::CHikv3Parser distroyed");
}

int CHikv3Parser::Init(int nDataType)
{
	//if (pHeader == NULL)
	//	return J_PARAM_ERROR;

	//m_hNewHandle = HIKANA_CreateStreamEx(DATA_BUFFER_SIZE, (unsigned char *)pHeader);

	return J_OK;
}

int CHikv3Parser::Deinit()
{
	if (m_hNewHandle != NULL)
	{
		m_hNewHandle = NULL;
	}

	return J_OK;
}

int CHikv3Parser::InputData(const char *pData, int nLen)
{
	WLock(m_rwLocker);
	HIKANA_InputData(m_hNewHandle, (unsigned char *)pData, nLen);
	//m_nDataSize += nLen;
	RWUnlock(m_rwLocker);

	return J_MEMORY_ERROR;
}

int CHikv3Parser::GetOnePacket(char *pData, J_StreamHeader &streamHeader)
{
	/*RLock(m_rwLocker);
	bool bKeyFrame = false;
	PACKET_INFO_EX stPacket;
	nLen = 0;
	nFrameType = UNKOWN_T;

	if (HIKANA_GetOnePacketEx(m_hNewHandle, &stPacket) == 0)
	{
		if (stPacket.nPacketType == FILE_HEAD)
		{
			nFrameType = HEADER_T;
		}
		else if (stPacket.nPacketType == VIDEO_I_FRAME)
		{
			bKeyFrame = true;
			nFrameType = VIDEO_T;
		}
		else if (stPacket.nPacketType == VIDEO_P_FRAME
				|| stPacket.nPacketType == VIDEO_B_FRAME)
		{
			nFrameType = VIDEO_T;
		}
		else if (stPacket.nPacketType == AUDIO_PACKET)
		{
			nFrameType = AUDIO_T;
		}

		if (stPacket.dwPacketSize > 0)
		{
			memcpy(pData, stPacket.pPacketBuffer, stPacket.dwPacketSize);
			nLen = stPacket.dwPacketSize;
		}
	}
	RWUnlock(m_rwLocker);

	return bKeyFrame;*/
	return 0;
}