#include "SamsungChannel.h"
#include "SamsungStream.h"

const char PT_SPEED[6] = {0x08, 0x10, 0x1B, 0x28, 0x34, 0x40};
const char ZF_SPEED[6] = {0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C};

CSamsungChannel::CSamsungChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode)
    : m_pAdapter(NULL)
    , m_nChannel(0)
    , m_bOpened(false)
{
    m_pAdapter = (CSamsungAdapter *) pOwner;
    m_nChannel = nChannel;
    m_nStreamType = nStream;
    m_nProtocol = nMode;

    m_recvSocket = NULL;
}

CSamsungChannel::~CSamsungChannel()
{

}

int CSamsungChannel::PtzControl(int nCmd, int nParam)
{
    SNP_ptz_req ptz_req = {0};
    memcpy(ptz_req.packet_header.start_code, "SDVR",  4);
    ptz_req.packet_header.ex_channel =  0x00;
    ptz_req.packet_header.pkt_version = 0x10;
    ptz_req.packet_header.pkt_size =  0x0C;
    ptz_req.packet_header.control =  0x11;
    ptz_req.packet_header.payload =  0x61;
    ptz_req.packet_header.seq = 0x00;
    ptz_req.packet_header.ctrlId = m_pAdapter->GetCtrlId();
    ptz_req.continue_header.ch =  0x0e;
    ptz_req.continue_header.cs = 0x00;
    ptz_req.ptz_cmd.channel = 0x01;
    ptz_req.ptz_cmd.rd = 0x00;

    if (nCmd == JO_PTZ_PRE_SET || nCmd == JO_PTZ_PRE_CLR || nCmd == JO_PTZ_GOTO_PRE)
    {
    	switch (nCmd)
    	{
    	case JO_PTZ_PRE_SET:
            ptz_req.ptz_cmd.part[0] = 0x3d;
    		break;
    	case JO_PTZ_GOTO_PRE:
            ptz_req.ptz_cmd.part[0] = 0x0f;
    		break;
        case JO_PTZ_PRE_CLR:
            ptz_req.ptz_cmd.part[0] = 0x65;
    		break;
    	}
    	ptz_req.ptz_cmd.part[1] = nParam;
    	ptz_req.ptz_cmd.part[2] = 0x00;
    	ptz_req.ptz_cmd.part[3] = 0x00;
    	ptz_req.ptz_cmd.part[4] = 0x00;
    }
    else
    {
    	if (nParam > 0)
    	{
    	    int nSpeed = nParam / 42;
    		switch (nCmd)
    		{
    		case JO_PTZ_UP:
                ptz_req.ptz_cmd.part[0] = 0x02;
                ptz_req.ptz_cmd.part[1] = 0x00;
                ptz_req.ptz_cmd.part[2] = 0x08;
                ptz_req.ptz_cmd.part[3] = 0x00;
                ptz_req.ptz_cmd.part[4] = PT_SPEED[nSpeed];
    			break;
    		case JO_PTZ_DOWN:
                ptz_req.ptz_cmd.part[0] = 0x02;
                ptz_req.ptz_cmd.part[1] = 0x00;
                ptz_req.ptz_cmd.part[2] = 0x10;
                ptz_req.ptz_cmd.part[3] = 0x00;
                ptz_req.ptz_cmd.part[4] = PT_SPEED[nSpeed];
    			break;
    		case JO_PTZ_LEFT:
                ptz_req.ptz_cmd.part[0] = 0x02;
                ptz_req.ptz_cmd.part[1] = 0x04;
                ptz_req.ptz_cmd.part[2] = 0x00;
                ptz_req.ptz_cmd.part[3] = PT_SPEED[nSpeed];
                ptz_req.ptz_cmd.part[4] = 0x00;
    			break;
    		case JO_PTZ_RIGHT:
                ptz_req.ptz_cmd.part[0] = 0x02;
                ptz_req.ptz_cmd.part[1] = 0x02;
                ptz_req.ptz_cmd.part[2] = 0x00;
                ptz_req.ptz_cmd.part[3] = PT_SPEED[nSpeed];
                ptz_req.ptz_cmd.part[4] = 0x00;
    			break;
    		case JO_PTZ_UP_LEFT:
                ptz_req.ptz_cmd.part[0] = 0x02;
                ptz_req.ptz_cmd.part[1] = 0x04;
                ptz_req.ptz_cmd.part[2] = 0x08;
                ptz_req.ptz_cmd.part[3] = PT_SPEED[nSpeed];
                ptz_req.ptz_cmd.part[4] = PT_SPEED[nSpeed];
                break;
    		case JO_PTZ_UP_RIGHT:
                ptz_req.ptz_cmd.part[0] = 0x02;
                ptz_req.ptz_cmd.part[1] = 0x02;
                ptz_req.ptz_cmd.part[2] = 0x08;
                ptz_req.ptz_cmd.part[3] = PT_SPEED[nSpeed];
                ptz_req.ptz_cmd.part[4] = PT_SPEED[nSpeed];
    			break;
    		case JO_PTZ_DOWN_LEFT:
                ptz_req.ptz_cmd.part[0] = 0x02;
                ptz_req.ptz_cmd.part[1] = 0x04;
                ptz_req.ptz_cmd.part[2] = 0x10;
                ptz_req.ptz_cmd.part[3] = PT_SPEED[nSpeed];
                ptz_req.ptz_cmd.part[4] = PT_SPEED[nSpeed];
    			break;
    		case JO_PTZ_DOWN_RIGHT:
                ptz_req.ptz_cmd.part[0] = 0x02;
                ptz_req.ptz_cmd.part[1] = 0x02;
                ptz_req.ptz_cmd.part[2] = 0x10;
                ptz_req.ptz_cmd.part[3] = PT_SPEED[nSpeed];
                ptz_req.ptz_cmd.part[4] = PT_SPEED[nSpeed];
    			break;
    		case JO_PTZ_ZOOM_IN:
                ptz_req.ptz_cmd.part[0] = 0x33;
                ptz_req.ptz_cmd.part[1] = 0x00;
                ptz_req.ptz_cmd.part[2] = ZF_SPEED[nSpeed];
                ptz_req.ptz_cmd.part[3] = 0x00;
                ptz_req.ptz_cmd.part[4] = 0x00;
    			break;
    		case JO_PTZ_ZOOM_OUT:
                ptz_req.ptz_cmd.part[0] = 0x34;
                ptz_req.ptz_cmd.part[1] = 0x00;
                ptz_req.ptz_cmd.part[2] = ZF_SPEED[nSpeed];;
                ptz_req.ptz_cmd.part[3] = 0x00;
                ptz_req.ptz_cmd.part[4] = 0x00;
    			break;
    		case JO_PTZ_FOCUS_NEAR:
                ptz_req.ptz_cmd.part[0] = 0x36;
                ptz_req.ptz_cmd.part[1] = 0x00;
                ptz_req.ptz_cmd.part[2] = ZF_SPEED[nSpeed];;
                ptz_req.ptz_cmd.part[3] = 0x00;
                ptz_req.ptz_cmd.part[4] = 0x00;
    			break;
    		case JO_PTZ_FOCUS_FAR:
                ptz_req.ptz_cmd.part[0] = 0x35;
                ptz_req.ptz_cmd.part[1] = 0x00;
                ptz_req.ptz_cmd.part[2] = ZF_SPEED[nSpeed];;
                ptz_req.ptz_cmd.part[3] = 0x00;
                ptz_req.ptz_cmd.part[4] = 0x00;
    			break;
    		case JO_PTZ_IRIS_OPEN:
    			break;
    		case JO_PTZ_IRIS_CLOSE:
    			break;
    		}
    	}
    	else
    	{
            ptz_req.ptz_cmd.part[0] = 0x01;
            ptz_req.ptz_cmd.part[1] = 0x00;
            ptz_req.ptz_cmd.part[2] = 0x00;
            ptz_req.ptz_cmd.part[3] = 0x00;
            ptz_req.ptz_cmd.part[4] = 0x00;
    	}
    }
    ptz_req.ptz_cmd.part2[0] = 0x00;
    ptz_req.ptz_cmd.part2[1] = 0x00;
    ptz_req.ptz_cmd.part2[2] = 0xFD;
    ptz_req.ptz_cmd.part2[3] = 0xFF;
    ptz_req.ptz_cmd.part2[4] = 0x3F;

    return m_pAdapter->SendCommand((const char *)&ptz_req, sizeof(SNP_ptz_req), sizeof(SNP_ptz_rep));
}

int CSamsungChannel::OpenStream(void *&pObj, CRingBuffer *pRingBuffer)
{
    if (m_pAdapter->GetStatus() != J_DevReady)
    {
        m_bOpened = false;
        return J_DEV_BROKEN;
    }

    if (m_bOpened && pObj != NULL)
    {
        (static_cast<CSamsungStream *> (pObj))->AddRingBuffer(pRingBuffer);
        return J_OK;
    }

    int nRet = StartView();
    if (nRet != J_OK)
    {
        return J_STREAM_ERROR;
    }

    m_bOpened = true;
    pObj = new CSamsungStream(m_recvSocket, m_resid);
    (static_cast<CSamsungStream *> (pObj))->AddRingBuffer(pRingBuffer);
    (static_cast<CSamsungStream *> (pObj))->Startup();

    return J_OK;
}

int CSamsungChannel::CloseStream(void *pObj, CRingBuffer *pRingBuffer)
{
    if (!m_bOpened)
        return J_OK;

    CSamsungStream *pSamsungStream = static_cast<CSamsungStream *>(pObj);
    if (pSamsungStream == NULL)
        return J_OK;

    if (pSamsungStream->RingBufferCount() == 1)
    {
        StopView();
        m_bOpened = false;
        (static_cast<CSamsungStream *> (pObj))->Shutdown();
        pSamsungStream->DelRingBuffer(pRingBuffer);
        delete (CSamsungStream *) pObj;

        return J_NO_REF;
    }

    if (pSamsungStream->RingBufferCount() > 0)
        pSamsungStream->DelRingBuffer(pRingBuffer);

    return J_OK;
}

int CSamsungChannel::StartView()
{
    //J_OS::LOGINFO("type = %d", m_nStreamType);
    //m_pAdapter->Login();
    if (m_recvSocket != NULL)
    {
        delete m_recvSocket;
        m_recvSocket = NULL;
    }

    m_recvSocket = new J_OS::CTCPSocket();
    m_recvSocket->Connect(m_pAdapter->GetRemoteIp(),
                          m_pAdapter->GetRemotePort() + 1);

    SNP_Packet_info viewRequest = {0};
    memcpy(viewRequest.start_code, "SDVR",  4);
    viewRequest.ex_channel = 0x00;
    viewRequest.pkt_version = 0x10;
    viewRequest.pkt_size = 0x0C;
    viewRequest.control = 0x30;
    viewRequest.payload = 0x11;
    viewRequest.seq = 0x80;
    viewRequest.ctrlId =  m_pAdapter->GetCtrlId();

    if (m_recvSocket->Write((char*)&viewRequest, sizeof(SNP_Packet_info)) < 0)
    {
        if (errno == EPIPE)
        {
            delete m_recvSocket;
            m_recvSocket = NULL;
        }
        return J_INVALID_DEV;
    }

    /*if (m_nStreamType == 1)
    {
        char buff[1024];
        m_recvSocket->Read(buff, 0);
        SelectStream();
    }*/

    return J_OK;
}

int CSamsungChannel::StopView()
{
    m_pAdapter->Logout();
    if (m_recvSocket != NULL)
    {
        delete m_recvSocket;
        m_recvSocket = NULL;
    }

    return J_OK;
}

int CSamsungChannel::SelectStream()
{
    SNP_enc_type_req enc_type_req = {0};
    memcpy(enc_type_req.packet_header.start_code, "SDVR",  4);
    enc_type_req.packet_header.ex_channel = 0x00;
    enc_type_req.packet_header.pkt_version = 0x10;
    enc_type_req.packet_header.pkt_size = 0x0C;
    enc_type_req.packet_header.control = 0x11;
    enc_type_req.packet_header.payload = 0x51;
    enc_type_req.packet_header.seq = 0x00;
    enc_type_req.packet_header.ctrlId = m_pAdapter->GetCtrlId();
    enc_type_req.continue_header.ch =  0x0a;
    enc_type_req.continue_header.cs = 0x00;
    enc_type_req.enc_type.channel = 0x01;
    enc_type_req.enc_type.video = 0x01;
    enc_type_req.enc_type.type = 0xff;
    enc_type_req.enc_type.res = 0x02;
    enc_type_req.enc_type.frame = 0xff;
    enc_type_req.enc_type.bit = 0xff;
    enc_type_req.enc_type.atc = 0x00;
    enc_type_req.enc_type.data = 0x00;

    return m_pAdapter->SendCommand((const char *)&enc_type_req, sizeof(SNP_enc_type_req), 16);
}
