#ifndef __JOCHANNEL_H_
#define __JOCHANNEL_H_
#include "x_socket.h"
#include "JoAdapter.h"
//#include "RtspHelper.h"

class CJoChannel : public J_ResidTmpl<J_BaseAdapter>
					, public J_PtzControl
{
public:
	CJoChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode);
	~CJoChannel();

public:

	///J_PtzControl
	virtual int PtzControl(int nCmd, int nParam);
	///J_StreamChannel
	virtual int OpenStream(void *&pObj, CRingBuffer *pRingBuffer);
	virtual int CloseStream(void *pObj, CRingBuffer *pRingBuffer);
	virtual bool HasMultiStream() { return true; }

private:
	int StartView();
	int StopView();
	int SendCommand(const char *pCommand);

private:
	CJoAdapter *m_pAdapter;
	int m_nChannel;
	int m_nStreamType;
	int m_nProtocol;

	J_OS::CTCPSocket *m_recvSocket;
	bool m_bOpened;
	//CRtspHelper m_rtspHelper;
};

#endif //~__JOCHANNEL_H_
