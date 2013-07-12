#ifndef __ONVIFCHANNEL_H_
#define __ONVIFCHANNEL_H_
#include "x_socket.h"
#include "OnvifAdapter.h"
#include "RtspHelper.h"

class COnvifChannel : public J_ResidTmpl<J_BaseAdapter>
					, public J_PtzControl
{
public:
	COnvifChannel(const char *pResid, J_Obj *pOwner, int nChannel, int nStream, int nMode);
	~COnvifChannel();

public:

	///J_PtzControl
	virtual int PtzControl(int nCmd, int nParam);
	///J_StreamChannel
	virtual int OpenStream(J_Obj *&pObj, CRingBuffer *pRingBuffer);
	virtual int CloseStream(J_Obj *pObj, CRingBuffer *pRingBuffer);
	virtual bool HasMultiStream() { return true; }

private:
	int StartView();
	int StopView();
	int SendCommand(const char *pCommand);

private:
	COnvifAdapter *m_pAdapter;
	int m_nChannel;
	int m_nStreamType;
	int m_nProtocol;

	J_OS::CTCPSocket *m_recvSocket;
	bool m_bOpened;
	CRtspHelper m_rtspHelper;
};

#endif //~__ONVIFCHANNEL_H_
