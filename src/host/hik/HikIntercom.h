#ifndef __HIK_INTERCOM_H_
#define __HIK_INTERCOM_H_
#include "x_socket.h"
#include "x_timer.h"
#include "HikType.h"
#include "HikAdapter.h"

class CHikIntercom : public J_ResidTmpl<J_BaseAdapter>
{
public:
	CHikIntercom(const char *pResid, void *pOwner, int nChannel);
	~CHikIntercom();

public:
	///J_StreamChannel
	virtual int OpenStream(void *&pObj, CRingBuffer *pRingBuffer);
	virtual int CloseStream(void *pObj, CRingBuffer *pRingBuffer);
	virtual bool HasMultiStream() { return false; }

private:
	int GetCompressType();
	int StartVoice();
	int StopVoice();

private:
	CHikAdapter *m_pAdapter;
	J_OS::CTCPSocket *m_recvSocket;

	pthread_t sendThread;
	static void *WorkThread(void *param)
	{
		(static_cast<CHikIntercom *>(param))->OnWork();
		return (void *)0;
	}
	void OnWork();
};

#endif //~__HIK_INTERCOM_H_
