#ifndef __HIKCHANNEL_H_
#define __HIKCHANNEL_H_

#include "x_socket.h"
#include "x_timer.h"
#include "Hikv3Type.h"
#include "Hikv3Adapter.h"

class CHikv3ChannelBase : public J_ChannelStream
                      , public J_PtzControl
                      , public J_RemoteVod
                      , public J_StreamParser
{};

class CHikv3Channel : public J_ResidTmpl<J_BaseAdapter, CHikv3ChannelBase>
{
public:
	CHikv3Channel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode);
	~CHikv3Channel();

	J_OS::TLocker_t  m_sockLocker;
public:
	///J_StreamChannel
	virtual int OpenStream(J_Obj *&pObj, CRingBuffer *pRingBuffer);
	virtual int CloseStream(J_Obj *pObj, CRingBuffer *pRingBuffer);
	virtual bool HasMultiStream() { return true; }
	///J_PtzControl
	virtual int PtzControl(int nCmd, int nParam);
	///J_StreamParser
	virtual int OpenParser(J_Obj *&pObj);
	virtual int CloseParser(J_Obj *pObj);
	///J_RemoteVod
	virtual int EmunFileByTime(time_t beginTime, time_t endTime, std::vector<J_FileInfo> &fileList);
	virtual int OpenVodStream(J_Obj *&pObj);
	virtual int CloseVodStream(J_Obj *pObj);

private:
	int StartView();
	int StopView();

	static void OnTimer(void *user)
	{
		(static_cast<CHikv3Channel *>((void *)user))->ExchangeData();
	}
	void ExchangeData();
	int MakeIFrame(int nChannel);
	void Convert2HikTime(time_t utcTime, HikTime &hikTime);
	int SendCommand(int nCmd, const char *pSendData, int nDataLen);

private:
	CHikv3Adapter *m_pAdapter;
	int m_nChannel;
	int m_nStreamType;
	int m_nProtocol;

	J_OS::CTCPSocket *m_recvSocket;
	char *m_pDataBuff;
	bool m_bOpened;
	J_OS::CTimer m_timer;
};
#endif //~__HIKCHANNEL_H_
