#include "SamsungParser.h"
#include "x_time.h"

#define PACKET_SIZE	1412

const char START_CODE[4] = { 'S', 'D', 'V', 'R' };
const char VIDEO_TAG[4] = { 0x00, 0x00, 0x01, 0xE0 };
const char AUDIO_TAG[4] = { 0x00, 0x00, 0x01, 0xC0 };
#define GET_SDVR_LENGTH(x) (((*((x) + 15) & 0xFF) << 24) + ((*((x) + 14) & 0xFF) << 16) + ((*((x) + 13) & 0xFF) << 8) + (*((x) + 12) & 0xFF))
#define GET_FRAME_TYPE(x) (*((x) + 20) & 0x0F)
#define GET_PES_LENGTH(x) (((*((x) + 5) & 0xFF) << 8) + (*((x) + 4) & 0xFF))
#define IS_MULTIPLE_END(x) (((*((x) + 8) & 0xFF) >> 4) & 0x01)
#define GET_PACKET_SIZE(x) (((*((x) + 7) & 0xFF) << 8) + (*((x) + 6) & 0xFF))
#define GET_SEQ_NUM(x) ((*((x) + 10) & 0x7F))
CSamsungParser::CSamsungParser()
{
    m_pDataBuff = NULL;
    m_nDataSize = 0;

    m_sdvrLen = 0;
    m_videoLen = 0;
    m_audioLen = 0;
    m_curFrameType = 0;

    m_nOutSize = 0;
    m_pOutBuff = NULL;
    m_bIsComplate = false;
}

CSamsungParser::~CSamsungParser()
{
    delete m_pOutBuff;
}

int CSamsungParser::Init(int nDataType)
{
    if (m_pDataBuff == NULL)
        m_pDataBuff = new char[1024 * 1024];

    if (m_pOutBuff == NULL)
        m_pOutBuff = new char[1024 * 1024];

    return J_OK;
}

int CSamsungParser::Deinit()
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

int CSamsungParser::InputData(const char *pData, int nLen)
{
    //WLock(m_rwLocker);
    memcpy(m_pDataBuff + m_nDataSize, pData, nLen);
    m_nDataSize += nLen;
    //RWUnlock(m_rwLocker);

    return J_OK;
}

int CSamsungParser::GetOnePacket(char *pData, J_StreamHeader &streamHeader)
{
    int nOffset = 0;
    int nMedieOffset = 0;
    int nFrameType = 0;
    int nLen = 0;
    m_bIsComplate = false;
    int nPacketLen = 0;
    bool bIsStart = false;
    while (m_nDataSize > 12)
    {
        nOffset = 12;
        nMedieOffset = 0;
        nPacketLen = 0;
        bIsStart = false;
        RectifyData();

        m_bIsComplate = IS_MULTIPLE_END(m_pDataBuff);
        nPacketLen = GET_PACKET_SIZE(m_pDataBuff);
        if (GET_SEQ_NUM(m_pDataBuff) == 0)
        {
            if (m_nDataSize < 52)
            {
                ///数据头信息不足
                return J_NOT_COMPLATE;
            }

            ///获取媒体信息
            m_sdvrLen = GET_SDVR_LENGTH(m_pDataBuff);
            nOffset += 40;
            int frameType = GET_FRAME_TYPE(m_pDataBuff);
            if (frameType > 3)
                m_curFrameType = J_AudioFrame;
            else if (frameType == 0)
                m_curFrameType = J_VideoIFrame;
            else
                m_curFrameType = J_VideoPFrame;

            bIsStart = true;
        }

        /*for (int i=0; i<16; i++)
        {
            printf("%02x ", m_pDataBuff[i] & 0xFF);
        }
        printf("\n");*/

        if (m_nDataSize >= nPacketLen)
        {
            nMedieOffset = nOffset;
            if (bIsStart)
            {
                ///去掉PES头
                if (m_curFrameType == J_AudioFrame)
                    nMedieOffset += 31;
                else
                    nMedieOffset += 32;
            }
            memcpy(m_pOutBuff + m_nOutSize, m_pDataBuff + nMedieOffset, nPacketLen - nMedieOffset);
            m_nOutSize += nPacketLen - nMedieOffset;

            m_nDataSize -= nPacketLen;
            memmove(m_pDataBuff, m_pDataBuff + nPacketLen, m_nDataSize);
            m_sdvrLen -= nPacketLen - nOffset;
        }
        else
        {
            return J_NOT_COMPLATE;
        }

        if (m_bIsComplate)
        {
            if (m_sdvrLen != 0)
            {
                J_OS::LOGINFO("fdsafjdsalkf");
            }
            if (m_curFrameType == J_AudioFrame)
            {
                ///暂时不处理音频数据
                streamHeader.timeStamp = 0;
                streamHeader.frameType = 0;
                streamHeader.dataLen = 0;
                //static FILE *fp = NULL;
                //if (fp == NULL)
                //    fp = fopen("yjj_samsung_31", "wb+");
                //fwrite(m_pOutBuff, 1, m_nOutSize, fp);
            }
            else
            {
                streamHeader.timeStamp = CTime::Instance()->GetLocalTime(0);
                streamHeader.frameType = m_curFrameType;
                streamHeader.dataLen = m_nOutSize;
                memcpy(pData, m_pOutBuff, m_nOutSize);
            }
            m_nOutSize = 0;

            return J_OK;
        }

        //memcpy(m_pOutBuff + m_nOutSize, m_pDataBuff + nOffset, PACKET_SIZE - nOffset);
        //m_nOutSize += PACKET_SIZE - nOffset;
    }

    return J_NOT_COMPLATE;
}

void CSamsungParser::RectifyData()
{
    int nOffset = 0;
    while (m_nDataSize > 4 && memcmp(m_pDataBuff + nOffset, START_CODE, 4) != 0)
    {
        ++nOffset;
    }

    if (nOffset > 0)
    {
        J_OS::LOGINFO("CSamsungParser::RectifyData() offset = %d", nOffset);
        m_nDataSize -= nOffset;
        memmove(m_pDataBuff, m_pDataBuff + nOffset, m_nDataSize);
    }
}
