#ifndef __SONYCHANNEL_H_
#define __SONYCHANNEL_H_
#include "x_socket.h"
#include "SonyAdapter.h"

class CSonyChannel : public J_ResidTmpl<J_BaseAdapter>
						 , public J_PtzControl
{
public:
	CSonyChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode);
	~CSonyChannel();

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
	CSonyAdapter *m_pAdapter;
	int m_nChannel;
	int m_nStreamType;
	int m_nProtocol;

	J_OS::CTCPSocket *m_recvSocket;
	bool m_bOpened;
};

#endif //~__SONYCHANNEL_H_S
