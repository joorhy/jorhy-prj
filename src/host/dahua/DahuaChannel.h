#ifndef __DAHUACHANNEL_H_
#define __DAHUACHANNEL_H_
#include "x_socket.h"
#include "DahuaAdapter.h"

class CDahuaChannelBase : public J_ChannelStream
                          , public J_PtzControl
{};

class CDahuaChannel : public J_ResidTmpl<J_BaseAdapter, CDahuaChannelBase>
{
public:
	CDahuaChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode);
	~CDahuaChannel();

	J_OS::TLocker_t  m_sockLocker;
public:
	///J_StreamChannel
	virtual int OpenStream(void *&pObj, CRingBuffer *pRingBuffer);
	virtual int CloseStream(void *pObj, CRingBuffer *pRingBuffer);
	virtual bool HasMultiStream() { return true; }
	///J_PtzControl
	virtual int PtzControl(int nCmd, int nParam);

private:
	int StartView();
	int StopView();

	int SendOption();
	int SendDescribe();
	int SendSetup(int nTrack, int nPort);
	int SendPlay();
	int SendTeardown();

private:
	CDahuaAdapter *m_pAdapter;
	int m_nChannel;
	int m_nStreamType;
	int m_nProtocol;

	char *m_pDataBuff;
	bool m_bOpened;
	long m_lRealHandle;
};

#endif //~__DAHUACHANNEL_H_
