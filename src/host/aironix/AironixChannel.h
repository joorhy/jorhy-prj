#ifndef __AIRONIXCHANNEL_H_
#define __AIRONIXCHANNEL_H_
#include "x_socket.h"
#include "AironixAdapter.h"

class CAironixChannelBase : public J_ChannelStream
								  , public J_PtzControl
{};

class CAironixChannel : public J_ResidTmpl<J_BaseAdapter, CAironixChannelBase>
{
public:
	CAironixChannel(const j_char_t *pResid, j_void_t *pOwner, j_int32_t nChannel, j_int32_t nStream, j_int32_t nMode);
	~CAironixChannel();

	J_OS::TLocker_t  m_sockLocker;
public:
	///J_StreamChannel
	virtual j_result_t OpenStream(j_void_t *&pObj, CRingBuffer *pRingBuffer);
	virtual j_result_t CloseStream(j_void_t *pObj, CRingBuffer *pRingBuffer);
	virtual j_boolean_t HasMultiStream() { return true; }
	///J_PtzControl
	virtual j_result_t PtzControl(j_int32_t nCmd, j_int32_t nParam);

private:
	j_result_t StartView(j_void_t *pObj);
	j_result_t StopView();

	j_result_t SendOption();
	j_result_t SendDescribe();
	j_result_t SendSetup(j_int32_t nTrack, j_int32_t nPort);
	j_result_t SendPlay();
	j_result_t SendTeardown();

private:
	CAironixAdapter *m_pAdapter;
	j_int32_t m_nChannel;
	j_int32_t m_nStreamType;
	j_int32_t m_nProtocol;

	j_char_t *m_pDataBuff;
	j_boolean_t m_bOpened;
	j_int32_t m_hStream;
};

#endif //~__AIRONIXCHANNEL_H_
