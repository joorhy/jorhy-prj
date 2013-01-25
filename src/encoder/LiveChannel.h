#ifndef __LIVECHANNEL_H_
#define __LIVECHANNEL_H_
#include "LiveAdapter.h"

class CLiveChannelBase : public J_ChannelStream
{};

class CLiveChannel : public J_ResidTmpl<J_BaseAdapter, CLiveChannelBase>
{
public:
	CLiveChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode);
	~CLiveChannel();

	J_OS::TLocker_t  m_sockLocker;
public:
	///J_StreamChannel
	virtual int OpenStream(void *&pObj, CRingBuffer *pRingBuffer);
	virtual int CloseStream(void *pObj, CRingBuffer *pRingBuffer);
	virtual bool HasMultiStream() { return false; }

private:
	bool m_bOpened;
	int m_nChannel;
};

#endif //~__LIVECHANNEL_H_
