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
	CAironixChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode);
	~CAironixChannel();

	J_OS::TLocker_t  m_sockLocker;
public:
	///J_StreamChannel
	virtual int OpenStream(void *&pObj, CRingBuffer *pRingBuffer);
	virtual int CloseStream(void *pObj, CRingBuffer *pRingBuffer);
	virtual bool HasMultiStream() { return true; }
	///J_PtzControl
	virtual int PtzControl(int nCmd, int nParam);

private:
	int StartView(void *pObj);
	int StopView();

	int SendOption();
	int SendDescribe();
	int SendSetup(int nTrack, int nPort);
	int SendPlay();
	int SendTeardown();

private:
	CAironixAdapter *m_pAdapter;
	int m_nChannel;
	int m_nStreamType;
	int m_nProtocol;

	char *m_pDataBuff;
	bool m_bOpened;
	long m_hStream;
};

#endif //~__AIRONIXCHANNEL_H_
