#include "PsMux.h"
#include "x_crc32.h"

CPsMux::CPsMux()
{
	m_nSeqNum = rand();
}

CPsMux::~CPsMux()
{

}

int CPsMux::Init()
{
	return 0;
}

void CPsMux::Deinit()
{

}

int CPsMux::Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen, void *pExtdata)
{
	int nLen = 0;

	int nTotleLen = streamHeader.dataLen;		//总数据长度
	int nPackedLen = 0;							//打包数据长度
	int nPackOffset = 0;						//已经打包的数据的偏移
	bool isAudio = (streamHeader.frameType == jo_audio_frame);

	int nRate = *(int *)pExtdata;
	///构造PS头
	int nPSHeadLen = MakePSHead(pOutputData, streamHeader.timeStamp, nRate);
	nPackOffset += nPSHeadLen;
	nLen += nPSHeadLen;

	///构造PSM头
	int nPSMHeadLen = MakePSMHead(pOutputData + nPSHeadLen, isAudio);
	nPackOffset += nPSMHeadLen;
	nLen += nPSMHeadLen;

	///打包PES数据
	nPackedLen = nTotleLen;
	int nPESHeadLen = 0;
	nPESHeadLen = MakePESHead(pOutputData + nPackOffset, nPackedLen, streamHeader.timeStamp, isAudio);

	nPackOffset += nPESHeadLen;
	nLen += nPESHeadLen;

	memcpy(pOutputData + nPackOffset, pInputData, nPackedLen);
	nPackOffset += nPackedLen;
	nLen += nPackedLen;

	nOutLen = nLen;

	return J_OK;
}

int CPsMux::MakePESHead(char *pHead, int nDataLen, uint64_t timeStamp, bool isAudio)
{
		memset(pHead, 0, 20);
		int nLen = nDataLen + 14;
		uint64_t uPts = timeStamp * 90;//CTime::Instance()->GetLocalTime(0) * 90;
		///封装PES头
		pHead[0] = 0x00; pHead[1] = 0x00; pHead[2] = 0x01; pHead[3] = 0xE0;//Packetized Elementary Stream Header
		if (isAudio)
		{
			pHead[3] = 0xC0;
			//uPts -= 90;
		}

		pHead[4] = (nLen >> 8) & 0xFF;
		pHead[5] = nLen & 0xFF;

		pHead[6] = 0x8C; pHead[7] = 0x80;

		pHead[8] = 0x0B;
		pHead[9] = (0x01 << 5) | (((uPts >> 30) & 0x07) << 1) | 0x01;
		pHead[10] =  ((uPts >> 22) & 0xFF);
		pHead[11] =  (((uPts >> 15) & 0x7F) << 1) | 0x01;
		pHead[12] = ((uPts >> 7) & 0xFF);;
		pHead[13] = ((uPts & 0x7F) << 1) | 0x01;;
		pHead[14] = 0xFF; pHead[15] = 0xFF; pHead[16] = 0xFF;
		pHead[17] = 0xFF; pHead[18] = 0xFF; pHead[19] = 0xF8;

		return 20;
}

int CPsMux::MakePSHead(char *pHead, uint64_t timeStamp, int nRate)
{
	memset(pHead, 0, 20);
	///封装PS头
	pHead[0] = 0x00; pHead[1] = 0x00; pHead[2] = 0x01; pHead[3] = 0xBA;//Packed  Header

	uint64_t uScr = timeStamp * 90;//CTime::Instance()->GetLocalTime(0) * 90;
	pHead[4] = (0x01 << 6) | (((uScr >> 30) & 0x07) << 3) | (0x01 << 2)  | ((uScr >> 28) & 0x03);
	pHead[5] = ((uScr >> 20) & 0xFF);
	pHead[6] = (((uScr >> 15) & 0x1f) << 3) | (0x01 << 2) | ((uScr >> 13) & 0x03);
	pHead[7] = ((uScr >> 5) & 0xFF);
	pHead[8] = ((uScr & 0x1f) << 3) | (0x01 << 2);
	pHead[9] = 0x01;

	uint32_t muxRate = (nRate * 1024 + (50 -1)) / 50;
	pHead[10] = (muxRate >> 14) & 0xFF;
	pHead[11] = (muxRate >> 6) & 0xFF;
	pHead[12] = ((muxRate & 0x3F) << 2) | 0x03;

	pHead[13] = 0xFE; pHead[14] = 0xFF; pHead[15] = 0xFF;

	pHead[16] = (m_nSeqNum >> 24) & 0xFF;
	pHead[17] = (m_nSeqNum >> 16) & 0xFF;
	pHead[18] = (m_nSeqNum >> 8) & 0xFF;
	pHead[19] = m_nSeqNum & 0xFF;

	return 20;
}

int CPsMux::MakePSMHead(char *pHead, bool isAudio)
{
	memset(pHead, 0, 20);
	///封装PSM
	pHead[0] = 0x00; pHead[1] = 0x00; pHead[2] = 0x01; pHead[3] = 0xBC;//Program Stream map
	pHead[4] = 0x00; pHead[5] = 0x12; pHead[6] = 0xE6; pHead[7] = 0xFF;
	pHead[8] = 0x00; pHead[9] = 0x00;
	pHead[10] = 0x00; pHead[11] = 0x08;
	pHead[12] = 0x1B; pHead[13] = 0xE0; pHead[14] = 0x00; pHead[15] = 0x00;
	pHead[16] = 0x0F; pHead[17] = 0xC0; pHead[18] = 0x00; pHead[19] = 0x00;


	unsigned long i_crc = get_crc32(pHead, 20);
	pHead[20] = (i_crc >> 24) & 0xff;		//CRC_32
	pHead[21] = (i_crc >> 16) & 0xff;
	pHead[22] = (i_crc >> 8) & 0xff;
	pHead[33] = i_crc & 0xff;

	return 24;
}
