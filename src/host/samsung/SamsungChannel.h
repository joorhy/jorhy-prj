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
    CSamsungChannel(const j_char_t *pResid, J_Obj *pOwner, j_int32_t nChannel, j_int32_t nStream, j_int32_t nMode);
    ~CSamsungChannel();

public:

    ///J_PtzControl
    virtual j_result_t PtzControl(j_int32_t nCmd, j_int32_t nParam);
    ///J_StreamChannel
    virtual j_result_t OpenStream(J_Obj *&pObj, CRingBuffer *pRingBuffer);
    virtual j_result_t CloseStream(J_Obj *pObj, CRingBuffer *pRingBuffer);
    virtual j_boolean_t HasMultiStream() { return false; }

private:
    j_result_t StartView();
    j_result_t StopView();
    j_result_t SelectStream();

private:
    CSamsungAdapter *m_pAdapter;
    j_int32_t m_nChannel;
    j_int32_t m_nStreamType;
    j_int32_t m_nProtocol;

    J_OS::CTCPSocket *m_recvSocket;
    j_boolean_t m_bOpened;
};

#endif //~__SAMSUNGCHANNEL_H_
