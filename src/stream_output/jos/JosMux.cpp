#include "JosMux.h"
extern "C"
{
#include "x_inet.h"
}

JO_IMPLEMENT_INTERFACE(Mux, "jos", CJosMux::Maker)

CJosMux::CJosMux()
{
	J_OS::LOGINFO("CJosMux::CJosMux()");
}

CJosMux::~CJosMux()
{
	J_OS::LOGINFO("CJosMux::~CJosMux()");
}

int CJosMux::Init()
{
	m_nFrameSeq = 0;
	return J_OK;
}

void CJosMux::Deinit()
{

}

int CJosMux::Convert(const char *pInputData, J_StreamHeader &streamHeader, char *pOutputData, int &nOutLen, void *pExtdata)
{
	nOutLen = 0;
	J_DataHead *pDataHead = (J_DataHead *)pOutputData;
	memcpy(pDataHead->start_code, "JOAV", 4);
	pDataHead->data_len = htonl(streamHeader.dataLen);
	pDataHead->frame_type = htonl(streamHeader.frameType);
	pDataHead->time_stamp = htonll(streamHeader.timeStamp);
	pDataHead->frame_seq = htonl(m_nFrameSeq++);
	pDataHead->b_last_frame = 0;
	
	memcpy(pOutputData + sizeof(J_DataHead), pInputData, streamHeader.dataLen);
	nOutLen = streamHeader.dataLen + sizeof(J_DataHead);
	printf("%d   %d\n", sizeof(J_DataHead), streamHeader.dataLen);
	
	//J_OS::LOGINFO("data_len = %d", streamHeader.dataLen);

	return J_OK;
}
