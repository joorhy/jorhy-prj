#include "x_iconv.h"
#include "x_errtype.h"

#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>

#define WS_VERSION_V7		7
#define WS_VERSION_V8		8

const unsigned char MarkTable[][4] =
{
		{0xF7, 0x83, 0x97, 0x98},
		{0xF6, 0xDF, 0x9B, 0x3A},
		{0xE0, 0xC7, 0xA3, 0x11},
		{0xCF, 0xA4, 0xFA, 0x25},
		{0x7C, 0x73, 0x1B, 0x5B},
		{0x7C, 0x71, 0x6B, 0xE2},
		{0x27, 0x7B, 0xA4, 0x73},
		{0xAA, 0x3E, 0xB3, 0x7C},
		{0x82, 0xDB, 0x61, 0x69},
		{0x16, 0xDF, 0xDA, 0xF3}
};

CXIconv::CXIconv()
{
	m_nVersion = WS_VERSION_V7;
}

CXIconv::~CXIconv()
{

}

int CXIconv::Wsf2str(const char *pContent, int nLen, string_t &strMessage)
{
	if (pContent[0] == 0x00)
	{
		///v76版本处理
		m_nVersion = WS_VERSION_V7;
		strMessage.assign(pContent + 1, nLen - 2);
	}
	else if (pContent[0] & 0x80)
	{
		///新版本处理
		m_nVersion = WS_VERSION_V8;
		int nPayloadLen = 0;
		int nPayloadOffset = 0;
		bool bMarking = false;
		char byteMark[4] = {0};

		GetDataLength(pContent, nPayloadLen, nPayloadOffset);
		GetMarking(pContent, nPayloadOffset + 2, bMarking, byteMark);

		strMessage = GetStr(pContent + 2 + nPayloadOffset +(bMarking ? 4 : 0)
				, bMarking, byteMark, nPayloadLen);
	}

	return J_OK;
}

int CXIconv::Str2wsf(const string_t &strMessage, char *pContent, int &nLen, bool isMarking)
{
	long long nStrLen = strMessage.length();
	if (m_nVersion == WS_VERSION_V7)
	{
		pContent[0] = 0x00;
		memcpy(pContent + 1, strMessage.c_str(), nStrLen);
		pContent[nStrLen + 1] = 0xFF;
		nLen = nStrLen + 2;
	}
	else
	{
		pContent[0] = 0x81;//文本模式
		pContent[1] = 0x00;
		if (isMarking)
			pContent[1] = (0x01 << 7);

		int nOffset = 2;
		if (nStrLen > 65535)
		{
			nOffset += 8;
			pContent[1] += 127;

			pContent[2] = (nStrLen >> 56) & 0xFF;
			pContent[3] = (nStrLen >> 48) & 0xFF;
			pContent[4] = (nStrLen >> 40) & 0xFF;
			pContent[5] = (nStrLen >> 32) & 0xFF;
			pContent[6] = (nStrLen >> 24) & 0xFF;
			pContent[7] = (nStrLen >> 16) & 0xFF;
			pContent[8] = (nStrLen >> 8) & 0xFF;
			pContent[9] = nStrLen & 0xFF;
		}
		else if (nStrLen >= 126)
		{
			nOffset += 2;
			pContent[1] += 126;
			pContent[2] = (nStrLen >> 8) & 0xFF;
			pContent[3] = nStrLen & 0xFF;
		}
		else
		{
			pContent[1] += nStrLen;
		}

		char *pMarking = pContent + nOffset;
		srand(time(NULL));
		int nMarkIndex = rand() % 10;
		if (isMarking)
		{
			pMarking[0] = MarkTable[nMarkIndex][0];
			pMarking[1] = MarkTable[nMarkIndex][1];
			pMarking[2] = MarkTable[nMarkIndex][2];
			pMarking[3] = MarkTable[nMarkIndex][3];

			nOffset += 4;
		}

		char *pPayload = pContent + nOffset;
		for (int i = 0; i < nStrLen; i++)
		{
			if (isMarking)
			{
				pPayload[i] = strMessage.at(i) ^ MarkTable[nMarkIndex][i % 4];
			}
			else
			{
				pPayload[i] = strMessage.at(i);
			}
		}
		nLen = nStrLen + nOffset;
	}

	return J_OK;
}

int CXIconv::GetMarking(const char *pContent, int nOffset, bool &isMarking, char byMark[4])
{
	isMarking = false;
	if (pContent[1] & 0x80)
	{
		isMarking = true;

		byMark[0] = pContent[nOffset];
		byMark[1] = pContent[nOffset + 1];
		byMark[2] = pContent[nOffset + 2];
		byMark[3] = pContent[nOffset + 3];
	}

	return J_OK;
}

int CXIconv::GetDataLength(const char *pContent, int &nLength, int &nOffset)
{
	int payloadLen = 0;
	payloadLen = pContent[1] & 0x7F;
	if (payloadLen == 126)
	{
		nLength = ((pContent[2] & 0xFF) << 8) + (pContent[3] & 0xFF);
		nOffset = 2;
	}
	else if (payloadLen == 127)
	{
		nLength = ((pContent[2] & 0xFF) << 56) + ((pContent[3] & 0xFF) << 48)
				+ ((pContent[4] & 0xFF) << 40) + ((pContent[5] & 0xFF) << 32) + ((pContent[6] & 0xFF) << 24)
				+ ((pContent[7] & 0xFF) << 16) + ((pContent[8] & 0xFF) << 8) + (pContent[9] & 0xFF);
		nOffset = 8;
	}
	else
	{
		nLength = payloadLen;
		nOffset = 0;
	}

	return J_OK;
}

string_t CXIconv::GetStr(const char *pContent, bool isMarking, char byMark[4], int nPayloadLen)
{
	char *pPayLoadData = new char[nPayloadLen + 1];
	memset(pPayLoadData, 0, nPayloadLen + 1);
	for (int i = 0; i < nPayloadLen; i++)
	{
		if (isMarking)
		{
			pPayLoadData[i] = pContent[i] ^ byMark[i % 4];
		}
		else
		{
			pPayLoadData[i] = pContent[i];
		}
	}

	string_t strPayload(pPayLoadData);
	delete pPayLoadData;

	return strPayload;
}
