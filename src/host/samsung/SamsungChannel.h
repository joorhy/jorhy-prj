#ifndef __SAMSUNGCHANNEL_H_
#define __SAMSUNGCHANNEL_H_
#include "x_socket.h"
#include "SamsungAdapter.h"

class CSamsungChannelBase : public J_ChannelStream
    , public J_PtzControl
{};

class CSamsungChannel :  public J_ResidTmpl<J_BaseAdapter, CSamsungChannelBase>
{
public:
    CSamsungChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode);
    ~CSamsungChannel();

public:

    ///J_PtzControl
    virtual int PtzControl(int nCmd, int nParam);
    ///J_StreamChannel
    virtual int OpenStream(void *&pObj, CRingBuffer *pRingBuffer);
    virtual int CloseStream(void *pObj, CRingBuffer *pRingBuffer);
    virtual bool HasMultiStream() { return false; }

private:
    int StartView();
    int StopView();
    int SelectStream();

private:
    CSamsungAdapter *m_pAdapter;
    int m_nChannel;
    int m_nStreamType;
    int m_nProtocol;

    J_OS::CTCPSocket *m_recvSocket;
    bool m_bOpened;
};

#endif //~__SAMSUNGCHANNEL_H_
