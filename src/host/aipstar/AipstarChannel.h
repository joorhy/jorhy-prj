#ifndef __AIPSTARCHANNEL_H_
#define __AIPSTARCHANNEL_H_
#include "x_socket.h"
#include "AipstarAdapter.h"

class CAipstarChannelBase : public J_ChannelStream
                          , public J_PtzControl
{};

class CAipstarChannel : public J_ResidTmpl<J_BaseAdapter, CAipstarChannelBase>
{
public:
	CAipstarChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode);
	~CAipstarChannel();

	J_OS::TLocker_t  m_sockLocker;
public:
	///J_StreamChannel
	virtual j_result_t OpenStream(void *&pObj, CRingBuffer *pRingBuffer);
	virtual j_result_t CloseStream(void *pObj, CRingBuffer *pRingBuffer);
	virtual j_boolean_t HasMultiStream() { return true; }
	///J_PtzControl
	virtual j_result_t PtzControl(int nCmd, int nParam);
	
public:
	int Broken();

private:
	j_result_t StartView();
	j_result_t StopView();

	j_result_t SendOption();
	j_result_t SendDescribe();
	j_result_t SendSetup(j_int32_t nTrack, j_int32_t nPort);
	j_result_t SendPlay();
	j_result_t SendTeardown();

private:
	CAipstarAdapter *m_pAdapter;
	j_int32_t m_nChannel;
	j_int32_t m_nStreamType;
	j_int32_t m_nProtocol;

	j_char_t *m_pDataBuff;
	j_boolean_t m_bOpened;
	HANDLE m_hStream;
	void *m_pStream;
};

#endif //~__AIPSTARCHANNEL_H_
