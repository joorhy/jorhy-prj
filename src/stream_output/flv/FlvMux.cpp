#include "FlvMux.h"

JO_IMPLEMENT_INTERFACE(Mux, "flv", CFlvMux::Maker)
#define RTMP_PACKET_LEN 128
//#define FLV_SAVE 1

const char H264_HEAD[5] = { 0x00, 0x00, 0x00, 0x01 };
#ifdef FLV_SAVE
static FILE *fp = NULL;
#endif

static bool b_start = false;

CFlvMux::CFlvMux()
{
	m_nPrevTagLen =0;
	m_nTimeStamp = 0;
	m_pBuffer = new char[1024 * 1024];

#ifdef FLV_SAVE
	if (fp == NULL)
		fp = fopen("F://test.flv", "wb+");
	const char flv_head[] = { 
		0x46, 0x4c, 0x56, 0x01, 0x01, 0x00, 0x00, 0x00, 0x09
	};
	fwrite(flv_head, 1, sizeof(flv_head), fp);
	/*char metaData[1024] = {0};
	m_nPrevTagLen = MakeMetaData(100000, 176, 144, 25, 364544, metaData + 15);
	m_nPrevTagLen += MakeFlvHead(0, 0x12, m_nPrevTagLen, 0, 0, metaData);
	fwrite(metaData, 1, m_nPrevTagLen, fp);*/
#endif
}

CFlvMux::~CFlvMux()
{
	delete m_pBuffer;
}

j_result_t CFlvMux::Init()
{
	return J_OK;
}

void CFlvMux::Deinit()
{

}

j_result_t CFlvMux::Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen, void *pExtdata)
{
	int nOffset = 0;
	char *p = (char *)pInputData;
	if (streamHeader.frameType == jo_video_i_frame)
	{
		int nLen = streamHeader.dataLen;
		char sps[64] = {0};
		int sps_len = 0;
		bool b_sps = false;
		char pps[16] = {0};
		int pps_len = 0;
		bool b_pps = false;
		while (nLen > 0)
		{
			if (memcmp(p, H264_HEAD, 4) == 0)
			{
				if ((p[4] & 0x1F) == 7)//sps
				{
					b_pps = false;
					p += 4;
					nLen -= 4;
					sps[sps_len] = *p;
					++sps_len;
					b_sps = true;
				}
				else if ((p[4] & 0x1F) == 8)//pps
				{
					b_sps = false;
					p += 4;
					nLen -= 4;
					pps[pps_len] = *p;
					++pps_len;
					b_pps = true;
				}
				else if ((p[4] & 0x1F) == 5)//i_frame
				{
					p += 4;
					nLen -= 4;
					break;
				}
			}
			else if (b_sps)
			{
				sps[sps_len] = *p;
				++sps_len;
			}
			else if (b_pps)
			{
				pps[pps_len] = *p;
				++pps_len;
			}
			++p;
			--nLen;
		}

		if (!b_start)
		{
#ifdef FLV_SAVE
			nOffset = MakeFlvHead(m_nPrevTagLen== 0 ? m_nPrevTagLen : m_nPrevTagLen - 4, 9, sps_len + pps_len + 16, m_nTimeStamp, 0, pOutputData);
#else
			nOffset = MakeAmfHead(9, sps_len + pps_len + 16, m_nTimeStamp, 1, pOutputData);
#endif
			nOffset += MakeAVCConfig(sps, sps_len, pps, pps_len, pOutputData + nOffset);
			m_nPrevTagLen = nOffset;

#ifdef FLV_SAVE
			nOffset += MakeFlvHead(m_nPrevTagLen - 4, 9, nLen + 9, m_nTimeStamp, 0, pOutputData + nOffset);
			nOffset += MakeFlvVideoData(p, nLen, pOutputData + nOffset);
#else
			int nChunks = ((nLen + 9) + RTMP_PACKET_LEN - 1) / RTMP_PACKET_LEN;
			nOffset += MakeAmfHead(9, nLen + 9 + (nChunks - 1), m_nTimeStamp, 1, pOutputData + nOffset);
			nOffset += MakeAmfVideoData(p, nLen, pOutputData + nOffset);
#endif
			m_nPrevTagLen = nOffset - m_nPrevTagLen;
			b_start = true;
		}
		/*else
		{
			nOffset = MakeFlvHead(m_nPrevTagLen== 0 ? m_nPrevTagLen : m_nPrevTagLen - 4, 9, sps_len + pps_len + 16, m_nTimeStamp, 0, pOutputData);
			//nOffset = MakeAmfHead(9, sps_len + pps_len + 16, m_nTimeStamp, 0, pOutputData);
			nOffset += MakeAVCConfig(sps, sps_len, pps, pps_len, pOutputData + nOffset);
			m_nPrevTagLen = nOffset;
			nOffset += MakeFlvHead(m_nPrevTagLen - 4, 9, nLen + 9, m_nTimeStamp, 0, pOutputData + nOffset);
			//nOffset += MakeAmfHead(9, nLen + 9, m_nTimeStamp, 0, pOutputData + nOffset);
			nOffset += MakeFlvVideoData(p, nLen, pOutputData + nOffset);
			m_nPrevTagLen = nOffset - m_nPrevTagLen;
		}*/
	}
	else if (streamHeader.frameType == jo_video_p_frame && b_start)
	{
		p = (char *)(pInputData + 4);
#ifdef FLV_SAVE
		nOffset = MakeFlvHead(m_nPrevTagLen - 4, 9, streamHeader.dataLen - 4 + 9, m_nTimeStamp, 0, pOutputData);
		nOffset += MakeFlvVideoData(p, streamHeader.dataLen - 4, pOutputData + nOffset, false);
#else
		int nChunks = ((streamHeader.dataLen - 4 + 9) + RTMP_PACKET_LEN - 1) / RTMP_PACKET_LEN;
		nOffset = MakeAmfHead(9, streamHeader.dataLen - 4 + 9 + (nChunks - 1), m_nTimeStamp, 1, pOutputData);
		nOffset += MakeAmfVideoData(p, streamHeader.dataLen - 4, pOutputData + nOffset, false);
#endif
		m_nPrevTagLen = nOffset;
	}
	if (nOffset > 0)
	{
#ifdef FLV_SAVE
		fwrite(pOutputData, 1, nOffset, fp);
#endif
		m_nTimeStamp += 40;
		printf("rtmp_send_data %d\n", nOffset);
	}

	nOutLen = nOffset;

	return J_OK;
}

j_int32_t CFlvMux::MakeFlvHead(int nPrevTagLen, int nTagType, int nDataLen, int timeStamp, int nStreamId, char *pBuffer)
{
	char *p = pBuffer;
	p[0] = (nPrevTagLen >> 24) & 0xFF;; 
	p[1] = (nPrevTagLen >> 16) & 0xFF; 
	p[2] = (nPrevTagLen >> 8) & 0xFF; 
	p[3] = nPrevTagLen & 0xFF;
	p += 4;
	p[0] = nTagType; 
	p[1] = (nDataLen >> 16) & 0xFF; 
	p[2] = (nDataLen >> 8) & 0xFF; 
	p[3] = nDataLen & 0xFF;
	p[4] = (timeStamp >> 16) & 0xFF; 
	p[5] = (timeStamp >> 8) & 0xFF; 
	p[6] = timeStamp & 0xFF;
	p += 7;
	p[0] = (nStreamId >> 24) & 0xFF;; 
	p[1] = (nStreamId >> 16) & 0xFF; 
	p[2] = (nStreamId >> 8) & 0xFF; 
	p[3] = nStreamId & 0xFF;

	return 15;
}

j_int32_t CFlvMux::MakeAmfHead(int nTagType, int nDataLen, int timeStamp, int nStreamId, char *pBuffer)
{
	char *p = pBuffer;
	p[0] = 0x05; 
	p[1] = (timeStamp >> 16) & 0xFF; 
	p[2] = (timeStamp >> 8) & 0xFF; 
	p[3] = timeStamp & 0xFF;
	p[4] = (nDataLen >> 16) & 0xFF; 
	p[5] = (nDataLen >> 8) & 0xFF; 
	p[6] = nDataLen & 0xFF;
	p += 7;
	p[0] = nTagType;
	p += 1;
	p[0] = (nStreamId >> 24) & 0xFF;; 
	p[1] = (nStreamId >> 16) & 0xFF; 
	p[2] = (nStreamId >> 8) & 0xFF; 
	p[3] = nStreamId & 0xFF;
	
	return 12;
}

j_int32_t CFlvMux::MakeAmfVideoData(char *pData, int nDataLen, char *pBuffer, bool bIFrame, int nChunkSize)
{
	char *p = m_pBuffer; 
	if (bIFrame) p[0] = 0x17;
	else p[0] = 0x27;
	p[1] = 0x01; p[2] = 0x00; p[3] = 0x00; p[4] = 0x00;
	p += 5;
	p[0] = (nDataLen >> 24) & 0xFF;; 
	p[1] = (nDataLen >> 16) & 0xFF; 
	p[2] = (nDataLen >> 8) & 0xFF; 
	p[3] = nDataLen & 0xFF;
	p += 4;
	memcpy(p, pData, nDataLen);

	char *p2 = pBuffer;
	int nTotleLen = nDataLen + 9;
	int nOffset = 0;
	int nSendLen = 0;
	if (nTotleLen <= RTMP_PACKET_LEN)
	{
		memcpy(p2, m_pBuffer, nTotleLen);
		nOffset = nTotleLen;
		nTotleLen = 0;
	}
	else
	{
		memcpy(p2, m_pBuffer, RTMP_PACKET_LEN);
		nOffset = RTMP_PACKET_LEN;
		nTotleLen -= RTMP_PACKET_LEN;
		nSendLen = RTMP_PACKET_LEN;
	}
	while (nTotleLen > 0)
	{
		*(p2 + nOffset) = 0xC5;
		++nOffset;
		if (nTotleLen < RTMP_PACKET_LEN)
		{
			memcpy(p2 + nOffset, m_pBuffer + nSendLen, nTotleLen);
			nOffset += nTotleLen;
			nSendLen += nTotleLen;
			nTotleLen = 0;
		}
		else
		{
			memcpy(p2 + nOffset, m_pBuffer + nSendLen, RTMP_PACKET_LEN);
			nOffset += RTMP_PACKET_LEN;
			nSendLen += RTMP_PACKET_LEN;
			nTotleLen -= RTMP_PACKET_LEN;
		}
	}

	return nOffset;
}

j_int32_t CFlvMux::MakeAVCConfig(char *sps, int sps_len, char *pps, int pps_len, char *pBuffer)
{
	char *p = pBuffer;
	p[0] = 0x17;
	p[1] = 0x00; p[2] = 0x00; p[3] = 0x00; p[4] = 0x00;
	p += 5;
	///AVC Configure
	p[0] = 0x01;			//°æ±¾ºÅ
	p[1] = sps[1];	 p[2] = sps[2]; p[3] = sps[3];
	p[4] = 0xFF; p[5] = 0xE1;
	p += 6;
	p[0] = (sps_len >> 8) & 0xFF; 
	p[1] = sps_len & 0xFF;
	p += 2;
	memcpy(p, sps, sps_len);
	p += sps_len;
	p[0] = 0x01;
	p[1] = (pps_len >> 8) & 0xFF; 
	p[2] = pps_len & 0xFF;
	p += 3;
	memcpy(p, pps, pps_len);

	return sps_len + pps_len + 16;
}

j_int32_t CFlvMux::MakeFlvVideoData(char *pData, int nDataLen, char *pBuffer, bool bIFrame)
{
	char *p = pBuffer;
	if (bIFrame) p[0] = 0x17;
	else p[0] = 0x27;
	p[1] = 0x01; p[2] = 0x00; p[3] = 0x00; p[4] = 0x00;
	p += 5;
	p[0] = (nDataLen >> 24) & 0xFF;; 
	p[1] = (nDataLen >> 16) & 0xFF; 
	p[2] = (nDataLen >> 8) & 0xFF; 
	p[3] = nDataLen & 0xFF;
	p += 4;
	memcpy(p, pData, nDataLen);

	return nDataLen + 9;
}

j_int32_t CFlvMux::MakeMetaData(double nDuration, double nWidth, double nHeight, double nFrameRate, double nFileSeize, char *pBuffer)
{
	char *p = (char *)pBuffer;
	p[0] = 0x02; p[1] = 0x00; p[2] = 0x0A;
	p += 3;
	memcpy(p, "onMetaData", strlen("onMetaData"));
	p += 10;
	p[0] = 0x08; p[1] = 0x00; p[2] = 0x00; p[3] = 0x00; p[4] = 0x06;
	p += 5;
	p[0] = 0x00;
	p[1] = 0x08;
	p += 2;
	memcpy(p, "duration", strlen("duration"));
	p += 8;
	p[0] = 0x00;
	char *pDuration = (char *)&nDuration;
	p[1] = pDuration[7] & 0xFF; 
	p[2] = pDuration[6] & 0xFF; 
	p[3] = pDuration[5] & 0xFF; 
	p[4] = pDuration[4] & 0xFF; 
	p[5] = pDuration[3] & 0xFF; 
	p[6] = pDuration[2] & 0xFF; 
	p[7] = pDuration[1] & 0xFF; 
	p[8] = pDuration[0] & 0xFF;
	p += 9;
	p[0] = 0x00;
	p[1] = 0x05;
	p += 2;
	memcpy(p, "width", strlen("width"));
	p += 5;
	p[0] = 0x00;
	char *pWidth = (char *)&nWidth;
	p[1] = pWidth[7] & 0xFF; 
	p[2] = pWidth[6] & 0xFF; 
	p[3] = pWidth[5] & 0xFF; 
	p[4] = pWidth[4] & 0xFF; 
	p[5] = pWidth[3] & 0xFF; 
	p[6] = pWidth[2] & 0xFF; 
	p[7] = pWidth[1] & 0xFF; 
	p[8] = pWidth[0] & 0xFF;
	p += 9;
	p[0] = 0x00;
	p[1] = 0x06;
	p += 2;
	memcpy(p, "height", strlen("height"));
	p += 6;
	p[0] = 0x00;
	char *pHeight = (char *)&nHeight;
	p[1] = pHeight[7] & 0xFF; 
	p[2] = pHeight[6] & 0xFF; 
	p[3] = pHeight[5] & 0xFF; 
	p[4] = pHeight[4] & 0xFF; 
	p[5] = pHeight[3] & 0xFF; 
	p[6] = pHeight[2] & 0xFF; 
	p[7] = pHeight[1] & 0xFF; 
	p[8] = pHeight[0] & 0xFF;
	p += 9;
	p[0] = 0x00;
	p[1] = 0x0D;
	p += 2;
	memcpy(p, "videodatarate", strlen("videodatarate"));
	p += 13;
	p[0] = 0x00; 
	p[1] = 0x00; p[2] = 0x00; p[3] = 0x00; p[4] = 0x00; 
	p[5] = 0x00; p[6] = 0x00; p[7] = 0x00; p[8] = 0x00;
	p += 9;
	p[0] = 0x00;
	p[1] = 0x09;
	p += 2;
	memcpy(p, "framerate", strlen("framerate"));
	p += 9;
	p[0] = 0x00;
	char *pFrameRate = (char *)&nFrameRate;
	p[1] = pFrameRate[7] & 0xFF; 
	p[2] = pFrameRate[6] & 0xFF; 
	p[3] = pFrameRate[5] & 0xFF; 
	p[4] = pFrameRate[4] & 0xFF; 
	p[5] = pFrameRate[3] & 0xFF; 
	p[6] = pFrameRate[2] & 0xFF; 
	p[7] = pFrameRate[1] & 0xFF; 
	p[8] = pFrameRate[0] & 0xFF;
	p += 9;
	p[0] = 0x00;
	p[1] = 0x0C;
	p += 2;
	memcpy(p, "videocodecid", strlen("videocodecid"));
	p += 12;
	p[0] = 0x00;
	p[1] = 0x40; p[2] = 0x1C; p[3] = 0x00; p[4] = 0x00; 
	p[5] = 0x00; p[6] = 0x00; p[7] = 0x00; p[8] = 0x00;
	p += 9;
	p[0] = 0x00;
	p[1] = 0x0C;
	p += 2;
	memcpy(p, "canSeekToEnd", strlen("canSeekToEnd"));
	p += 12;
	p[0] = 0x01; p[1] = 0x00;
	p += 2;
	p[0] = 0x00; p[1] = 0x00; p[2] = 0x09;
	p += 3;

	return p - pBuffer;
}