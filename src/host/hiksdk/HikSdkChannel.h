#ifndef __HIKSDKCHANNEL_H_
#define __HIKSDKCHANNEL_H_
#include "x_socket.h"
#include "x_timer.h"
#include "HikSdkType.h"
#include "HikSdkAdapter.h"

class CHikSdkChannelBase : public J_ChannelStream
                      , public J_PtzControl
					  , public J_RemoteVod
{};

class CHikSdkChannel : public J_ResidTmpl<J_BaseAdapter, CHikSdkChannelBase>
{
public:
	CHikSdkChannel(const char *pResid, J_Obj *pOwner, int nChannel, int nStream, int nMode);
	~CHikSdkChannel();

public:
	///J_StreamChannel
	virtual j_result_t OpenStream(J_Obj *&pObj, CRingBuffer *pRingBuffer);
	virtual j_result_t CloseStream(J_Obj *pObj, CRingBuffer *pRingBuffer);
	virtual j_boolean_t HasMultiStream() { return true; }
	///J_PtzControl
	virtual j_result_t PtzControl(int nCmd, int nParam);
	///J_RemoteVod
	virtual j_result_t EmunFileByTime(time_t beginTime, time_t endTime, j_vec_file_info_t &vecFileInfo);
	virtual j_result_t OpenVodStream(J_Obj *&pObj);
	virtual j_result_t CloseVodStream(J_Obj *pObj);

private:
	CHikSdkAdapter *m_pAdapter;
	j_int32_t m_nChannel;
	j_int32_t m_nStreamType;
	j_int32_t m_nProtocol;
	j_boolean_t m_bOpened;
	LONG m_hStream;
	J_Obj *m_pStream;
};
#endif //~__HIKSDKCHANNEL_H_
