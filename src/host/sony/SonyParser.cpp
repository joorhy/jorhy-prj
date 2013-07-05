#include "SonyParser.h"

const char H264_HEAD[5] = { 0x00, 0x00, 0x00, 0x01};
const int H264_HEAD_LEN = 4;
#define IS_H264_DATA(x) ((*(x+4) & 0x0F) == 7 || (*(x+4) & 0x0F) == 1)
#define IS_H264_OTHER(x) ((*(x+4) & 0x0F) == 8 || (*(x+4) & 0x0F) == 5 || (*(x+4) & 0x0F) == 6)
#define IS_H264_KEY(x)	((*(x+4) & 0x0F) == 7)
#define RATE 2048
#define PACKET_SIZE	8000

CSonyParser::CSonyParser()
{
	m_pDataBuff = NULL;
	m_nDataSize = 0;
	m_nSeqNum = rand();
	m_frameNum = 0;
}

CSonyParser::~CSonyParser()
{

}

int CSonyParser::Init(int nDataType)
{
	if (m_pDataBuff == NULL)
		m_pDataBuff = new char[1024 * 1024];

	return J_OK;
}

int CSonyParser::Deinit()
{
	if (m_pDataBuff != NULL)
	{
		delete m_pDataBuff;
		m_pDataBuff = NULL;
	}

	return J_OK;
}

int CSonyParser::InputData(const char *pData, int nLen)
{
	//WLock(m_rwLocker);
	memcpy(m_pDataBuff + m_nDataSize, pData, nLen);
	m_nDataSize += nLen;
	//RWUnlock(m_rwLocker);

	return J_OK;
}

int CSonyParser::GetOnePacket(char *pData, J_StreamHeader &streamHeader)
{
	//WLock(m_rwLocker);
	int nOffset = 0;
	while (memcmp(m_pDataBuff + nOffset, H264_HEAD, H264_HEAD_LEN) != 0 && nOffset < m_nDataSize)
	{
		++nOffset;
	}

	if (nOffset > 0)
	{
	    J_OS::LOGINFO("CSonyParser::GetOnePacket Data Error");
	    m_nDataSize -= nOffset;
		memmove(m_pDataBuff, m_pDataBuff + nOffset, m_nDataSize);
		nOffset = 0;
	}

	nOffset = 4;
	while ( nOffset < m_nDataSize)
	{
		if (memcmp(m_pDataBuff + nOffset, H264_HEAD, H264_HEAD_LEN) == 0)
		{
			if(IS_H264_OTHER(m_pDataBuff + nOffset))
			{
				++nOffset;
				continue;
			}
			else
			{
				break;
			}
		}
		++nOffset;
	}

	if (nOffset == m_nDataSize)
	{
		return J_NOT_COMPLATE;//不足一包数据
	}

    streamHeader.timeStamp = JoTime->GetLocalTime(0);
	if (IS_H264_DATA(m_pDataBuff))
	{
		memcpy(pData, m_pDataBuff, nOffset);
		if (IS_H264_KEY(m_pDataBuff))
            streamHeader.frameType = jo_video_i_frame;
        else
            streamHeader.frameType = jo_video_p_frame;
        streamHeader.dataLen = nOffset;
		streamHeader.frameNum = m_frameNum++;
		m_frameNum %= 0xFFFFFFFF;
	}
	memmove(m_pDataBuff, m_pDataBuff + nOffset, m_nDataSize - nOffset);
	m_nDataSize -= nOffset;
	//RWUnlock(m_rwLocker);

	return J_OK;
}
