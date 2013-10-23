#ifndef __HIKSDKCHANNEL_H_
#define __HIKSDKCHANNEL_H_
#include "x_socket.h"
#include "x_timer.h"
#include "HikSdkType.h"
#include "HikSdkAdapter.h"

class CHikSdkChannelBase : public J_ChannelStream
                      , public J_PtzControl
{};

class CHikSdkChannel : public J_ResidTmpl<J_BaseAdapter, CHikSdkChannelBase>
{
public:
	CHikSdkChannel(const char *pResid, J_Obj *pOwner, int nChannel, int nStream, int nMode);
	~CHikSdkChannel();

public:
	///J_StreamChannel
	virtual int OpenStream(J_Obj *&pObj, CRingBuffer *pRingBuffer);
	virtual int CloseStream(J_Obj *pObj, CRingBuffer *pRingBuffer);
	virtual bool HasMultiStream() { return true; }
	///J_PtzControl
	virtual int PtzControl(int nCmd, int nParam);

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
