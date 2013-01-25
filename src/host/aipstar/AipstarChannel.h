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
	CAipstarAdapter *m_pAdapter;
	int m_nChannel;
	int m_nStreamType;
	int m_nProtocol;

	char *m_pDataBuff;
	bool m_bOpened;
	HANDLE m_hStream;
};

#endif //~__AIPSTARCHANNEL_H_
