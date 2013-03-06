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
    virtual int Init(int nDataType = jo_video_normal);
    virtual int Deinit();
    virtual int InputData(const char *pData, int nLen);
    virtual int GetOnePacket(char *pData, J_StreamHeader &streamHeader);

private:
    void RectifyData();

private:
    J_OS::RWLocker_t m_rwLocker;
    char *m_pDataBuff;
    char *m_pOutBuff;
    int m_nOutSize;
    int m_nDataSize;
    int m_sdvrLen;
    int m_videoLen;
    int m_audioLen;
    int m_curFrameType;
    bool m_bIsComplate;
};
#endif //~__SAMSUNGPARSER_H_
