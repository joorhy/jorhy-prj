#ifndef __HikSdkRemoteReader_H_
#define __HikSdkRemoteReader_H_
#include "j_includes.h"
#include "HikSdkAdapter.h"
#include "HikSdkParser2.h"
class CHikRemoteReader : public J_FileReader
{
public:
	CHikRemoteReader(J_Obj *pOwner, j_int32_t nChanne);
	~CHikRemoteReader();

public:
	virtual j_result_t GetContext(J_MediaContext *&mediaContext);
	virtual j_result_t GetPacket(j_char_t *pBuffer, J_StreamHeader &streamHeader);
	virtual j_result_t Pause();
	virtual j_result_t SetScale(float nScale = 1);
	virtual j_result_t SetTime(j_uint64_t s_time, j_uint64_t e_time);
	virtual j_result_t SetPosition(j_int32_t nPos);
	virtual j_result_t GetMediaData(j_uint64_t beginTime, j_int32_t nIval);

private:
	static void VodDataCallback(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
	{
		((CHikRemoteReader *)pUser)->OnRecvData(lRealHandle, dwDataType, pBuffer, dwBufSize);
	}
	void OnRecvData(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize);

private:
	CHikSdkAdapter *m_pAdapter;
	j_int32_t m_nChannel;
	LONG m_hStream;
	CHikSdkParser2 m_parser;
	char *m_pDataBuff;
	CRingBuffer m_ringBuffer;
};
#endif//~__HikSdkRemoteReader_H_