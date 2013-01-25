#include "AironixChannel.h"
#include "AironixStream.h"
#include "DVR_NET_SDK.h"
#include "PTZ.h"

CAironixChannel::CAironixChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode)
{
	m_bOpened = false;
	m_nChannel = nChannel;

	m_pAdapter = (CAironixAdapter *) pOwner;
	m_nChannel = nChannel;
	m_nStreamType = nStream;
	m_nProtocol = nMode;

	m_resid = pResid;
	//TMCC_PtzOpen(m_pAdapter->GetClientHandle(), m_nChannel - 1);
	//m_hStream = TMCC_Init(TMCC_INITTYPE_REALSTREAM);
}

CAironixChannel::~CAironixChannel()
{
	//int nRet = TMCC_PtzClose(m_pAdapter->GetClientHandle());
	//assert(nRet == TMCC_ERR_SUCCESS);

	//TMCC_Done(m_hStream);
}

int CAironixChannel::OpenStream(void *&pObj, CRingBuffer *pRingBuffer)
{
	if (m_bOpened && pObj != NULL)
	{
        if (m_nStreamType == 0)
        {
             NET_SDK_MakeKeyFrame(m_pAdapter->GetUserId(), m_nChannel - 1);
        }
        else
        {
            NET_SDK_MakeKeyFrameSub(m_pAdapter->GetSubUserId(), m_nChannel - 1);
        }

		(static_cast<CAironixStream *> (pObj))->AddRingBuffer(pRingBuffer);
		return J_OK;
	}

	pObj = new CAironixStream(m_resid, m_nChannel);
	int nRet = StartView(pObj);
	if (nRet != J_OK)
	{
		m_pAdapter->Broken();
		//m_pAdapter->Relogin();
		delete pObj;
		J_OS::LOGINFO("CAironixChannel::OpenStream StartView error, ret = %d", nRet);
		return J_STREAM_ERROR;
	}

	m_bOpened = true;
	(static_cast<CAironixStream *> (pObj))->AddRingBuffer(pRingBuffer);
	(static_cast<CAironixStream *> (pObj))->Startup();

	return J_OK;
}

int CAironixChannel::CloseStream(void *pObj, CRingBuffer *pRingBuffer)
{
	if (!m_bOpened)
		return J_OK;

	CAironixStream *pStream = static_cast<CAironixStream *>(pObj);
	if (pStream == NULL)
		return J_OK;

	if (pStream->RingBufferCount() == 1)
	{
		StopView();

		m_bOpened = false;
		(static_cast<CAironixStream *> (pObj))->Shutdown();
		pStream->DelRingBuffer(pRingBuffer);
		delete (CAironixStream *) pObj;

		return J_NO_REF;
	}

	if (pStream->RingBufferCount() > 0)
		pStream->DelRingBuffer(pRingBuffer);

	return J_OK;
}

int CAironixChannel::PtzControl(int nCmd, int nParam)
{
	int ptzCmd = 0;
	BOOL bRet = TRUE;
	if (nCmd == JO_PTZ_PRE_SET || nCmd == JO_PTZ_PRE_CLR || nCmd == JO_PTZ_GOTO_PRE)
	{
		switch (nCmd)
		{
		case JO_PTZ_PRE_SET:
            ptzCmd = PTZ_CMD_PRESET_SET;
			break;
		case JO_PTZ_PRE_CLR:
            ptzCmd = PTZ_CMD_PRESET_DEL;
			break;
		case JO_PTZ_GOTO_PRE:
            ptzCmd = PTZ_CMD_PRESET_GO;
			break;
		}
		bRet = NET_SDK_PTZPreset(m_hStream, ptzCmd, nParam);
	}
	else
	{
		switch (nCmd)
		{
		case JO_PTZ_UP:
            ptzCmd = PTZ_CMD_UP;
			break;
		case JO_PTZ_DOWN:
            ptzCmd = PTZ_CMD_DOWN;
			break;
		case JO_PTZ_LEFT:
            ptzCmd = PTZ_CMD_LEFT;
			break;
		case JO_PTZ_RIGHT:
            ptzCmd = PTZ_CMD_RIGHT;
			break;
		case JO_PTZ_UP_LEFT:
            ptzCmd = PTZ_CMD_LEFT_UP;
			break;
		case JO_PTZ_UP_RIGHT:
            ptzCmd = PTZ_CMD_RIGHT_UP;
			break;
		case JO_PTZ_DOWN_LEFT:
            ptzCmd = PTZ_CMD_LEFT_DOWN;
			break;
		case JO_PTZ_DOWN_RIGHT:
            ptzCmd = PTZ_CMD_RIGHT_DOWN;
			break;
		case JO_PTZ_ZOOM_IN:
            ptzCmd = PTZ_CMD_ZOOM_IN;
			break;
		case JO_PTZ_ZOOM_OUT:
            ptzCmd = PTZ_CMD_ZOOM_OUT;
			break;
		case JO_PTZ_FOCUS_NEAR:
            ptzCmd = PTZ_CMD_NEAR;
			break;
		case JO_PTZ_FOCUS_FAR:
            ptzCmd = PTZ_CMD_FAR;
			break;
		case JO_PTZ_IRIS_OPEN:
            ptzCmd = PTZ_CMD_IRIS_OPEN;
			break;
		case JO_PTZ_IRIS_CLOSE:
            ptzCmd = PTZ_CMD_IRIS_CLOSE;
			break;
		}
		if (nParam == 0)
		{
            ptzCmd = PTZ_CMD_STOP;
		}
        bRet = NET_SDK_PTZControl(m_hStream, ptzCmd, (nParam + 36) / 37);

	}
	//assert(nRet);

	return (bRet ? J_OK : J_UNKNOW);
}

int CAironixChannel::StartView(void *pObj)
{
    NET_SDK_CLIENTINFO clientInfo;
	clientInfo.lChannel = m_nChannel - 1;
	clientInfo.hPlayWnd = NULL;

    if (m_nStreamType == 0)
    {
        clientInfo.streamType = NET_SDK_MAIN_STREAM;
        m_hStream = NET_SDK_LivePlay(m_pAdapter->GetUserId(), &clientInfo, CAironixStream::OnStreamCallBack, pObj);
        assert(m_hStream != -1);
        //J_OS::LOGINFO("stream_handle = %d", m_hStream);
        //NET_SDK_SetLiveDataCallBack(m_hStream, CAironixStream::OnStreamCallBack, pObj);
        NET_SDK_MakeKeyFrame(m_pAdapter->GetUserId(), m_nChannel - 1);
    }
    else
    {
        clientInfo.streamType = NET_SDK_SUB_STREAM;
        m_hStream = NET_SDK_LivePlay(m_pAdapter->GetSubUserId(), &clientInfo, CAironixStream::OnStreamCallBack, pObj);
        assert(m_hStream != -1);
        //J_OS::LOGINFO("sub stream_handle = %d", m_hStream);
        //NET_SDK_SetLiveDataCallBack(m_hStream, CAironixStream::OnStreamCallBack, pObj);
        NET_SDK_MakeKeyFrameSub(m_pAdapter->GetSubUserId(), m_nChannel - 1);
    }

	return J_OK;
}

int CAironixChannel::StopView()
{
    //NET_SDK_SetLiveDataCallBack(m_hStream, NULL, NULL);
    BOOL bRet = NET_SDK_StopLivePlay(m_hStream);
    if (!bRet)
        J_OS::LOGINFO("CAironixChannel::StopView errno=%d", NET_SDK_GetLastError());

	return J_OK;
}
