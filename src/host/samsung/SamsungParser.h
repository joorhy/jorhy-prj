#ifndef __SAMSUNGPARSER_H_
#define __SAMSUNGPARSER_H_
#include "j_includes.h"

#define DATA_BUFFER_SIZE (1024 * 1024)

class CSamsungParser : public J_MediaParser
{
public:
    CSamsungParser();
    ~CSamsungParser();

public:
    ///J_VideoParser
    virtual j_result_t Init(int nDataType = jo_video_normal);
    virtual j_result_t Deinit();
    virtual j_result_t InputData(const char *pData, int nLen);
    virtual j_result_t GetOnePacket(char *pData, J_StreamHeader &streamHeader);

private:
    j_void_t RectifyData();

private:
    J_OS::RWLocker_t m_rwLocker;
    j_char_t *m_pDataBuff;
    j_char_t *m_pOutBuff;
    j_int32_t m_nOutSize;
    j_int32_t m_nDataSize;
    j_int32_t m_sdvrLen;
    j_int32_t m_videoLen;
    j_int32_t m_audioLen;
    j_int32_t m_curFrameType;
    j_boolean_t m_bIsComplate;
	j_uint32_t m_frameNum;
};
#endif //~__SAMSUNGPARSER_H_
