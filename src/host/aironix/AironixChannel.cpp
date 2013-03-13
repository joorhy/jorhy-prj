#include "AironixChannel.h"
#include "AironixStream.h"
#include "DVR_NET_SDK.h"
#include "PTZ.h"

CAironixChannel::CAironixChannel(const j_char_t *pResid, j_void_t *pOwner, j_int32_t nChannel, j_int32_t nStream, j_int32_t nMode)
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

j_result_t CAironixChannel::OpenStream(j_void_t *&pObj, CRingBuffer *pRingBuffer)
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

j_result_t CAironixChannel::CloseStream(j_void_t *pObj, CRingBuffer *pRingBuffer)
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

j_result_t CAironixChannel::PtzControl(j_int32_t nCmd, j_int32_t nParam)
{
	j_int32_t ptzCmd = 0;
	BOOL bRet = TRUE;
	if (nCmd == jo_ptz_pre_set || nCmd == jo_ptz_pre_clr || nCmd == jo_ptz_goto_pre)
	{
		switch (nCmd)
		{
		case jo_ptz_pre_set:
            ptzCmd = PTZ_CMD_PRESET_SET;
			break;
		case jo_ptz_pre_clr:
            ptzCmd = PTZ_CMD_PRESET_DEL;
			break;
		case jo_ptz_goto_pre:
            ptzCmd = PTZ_CMD_PRESET_GO;
			break;
		}
		bRet = NET_SDK_PTZPreset(m_hStream, ptzCmd, nParam);
	}
	else
	{
		switch (nCmd)
		{
		case jo_ptz_up:
            ptzCmd = PTZ_CMD_UP;
			break;
		case jo_ptz_down:
            ptzCmd = PTZ_CMD_DOWN;
			break;
		case jo_ptz_left:
            ptzCmd = PTZ_CMD_LEFT;
			break;
		case jo_ptz_right:
            ptzCmd = PTZ_CMD_RIGHT;
			break;
		case jo_ptz_up_left:
            ptzCmd = PTZ_CMD_LEFT_UP;
			break;
		case jo_ptz_up_right:
            ptzCmd = PTZ_CMD_RIGHT_UP;
			break;
		case jo_ptz_down_left:
            ptzCmd = PTZ_CMD_LEFT_DOWN;
			break;
		case jo_ptz_down_right:
            ptzCmd = PTZ_CMD_RIGHT_DOWN;
			break;
		case jo_ptz_zoom_in:
            ptzCmd = PTZ_CMD_ZOOM_IN;
			break;
		case jo_ptz_room_out:
            ptzCmd = PTZ_CMD_ZOOM_OUT;
			break;
		case jo_ptz_focus_near:
            ptzCmd = PTZ_CMD_NEAR;
			break;
		case jo_ptz_focus_far:
            ptzCmd = PTZ_CMD_FAR;
			break;
		case jo_ptz_iris_open:
            ptzCmd = PTZ_CMD_IRIS_OPEN;
			break;
		case jo_ptz_iris_close:
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

j_result_t CAironixChannel::StartView(j_void_t *pObj)
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

j_result_t CAironixChannel::StopView()
{
    //NET_SDK_SetLiveDataCallBack(m_hStream, NULL, NULL);
    BOOL bRet = NET_SDK_StopLivePlay(m_hStream);
    if (!bRet)
        J_OS::LOGINFO("CAironixChannel::StopView errno=%d", NET_SDK_GetLastError());

	return J_OK;
}
