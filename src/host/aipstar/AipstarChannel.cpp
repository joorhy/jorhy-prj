#include "AipstarChannel.h"
#include "AipstarStream.h"

CAipstarChannel::CAipstarChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode)
{
	m_bOpened = false;
	m_nChannel = nChannel;

	m_pAdapter = (CAipstarAdapter *) pOwner;
	m_nChannel = nChannel;
	m_nStreamType = nStream;
	m_nProtocol = nMode;

	m_resid = pResid;
	TMCC_PtzOpen(m_pAdapter->GetClientHandle(), m_nChannel - 1);
	m_hStream = TMCC_Init(TMCC_INITTYPE_REALSTREAM);
}

CAipstarChannel::~CAipstarChannel()
{
	int nRet = TMCC_PtzClose(m_pAdapter->GetClientHandle());
	assert(nRet == TMCC_ERR_SUCCESS);

	TMCC_Done(m_hStream);
}

int CAipstarChannel::OpenStream(void *&pObj, CRingBuffer *pRingBuffer)
{
	if (m_bOpened && pObj != NULL)
	{
	    TMCC_MakeKeyFrame(m_hStream);
		(static_cast<CAipstarStream *> (pObj))->AddRingBuffer(pRingBuffer);
		return J_OK;
	}

	pObj = new CAipstarStream(m_resid, m_nChannel);
	TMCC_RegisterStreamCallBack(m_hStream, CAipstarStream::OnStreamCallBack, pObj);
	int nRet = StartView();
	if (nRet != J_OK)
	{
		m_pAdapter->Broken();
		//m_pAdapter->Relogin();
		delete pObj;
		J_OS::LOGINFO("CAipstarChannel::OpenStream StartView error, ret = %d", nRet);
		return J_STREAM_ERROR;
	}

	m_bOpened = true;
	(static_cast<CAipstarStream *> (pObj))->AddRingBuffer(pRingBuffer);
	(static_cast<CAipstarStream *> (pObj))->Startup();

	return J_OK;
}

int CAipstarChannel::CloseStream(void *pObj, CRingBuffer *pRingBuffer)
{
	if (!m_bOpened)
		return J_OK;

	CAipstarStream *pStream = static_cast<CAipstarStream *>(pObj);
	if (pStream == NULL)
		return J_OK;

	if (pStream->RingBufferCount() == 1)
	{
		StopView();

		m_bOpened = false;
		(static_cast<CAipstarStream *> (pObj))->Shutdown();
		pStream->DelRingBuffer(pRingBuffer);
		delete (CAipstarStream *) pObj;

		return J_NO_REF;
	}

	if (pStream->RingBufferCount() > 0)
		pStream->DelRingBuffer(pRingBuffer);

	return J_OK;
}

int CAipstarChannel::PtzControl(int nCmd, int nParam)
{
	int ptzCmd = 0;
	int nRet = TMCC_ERR_SUCCESS;
	HANDLE devHandle = TMCC_Init(TMCC_INITTYPE_CONTROL);
	
	tmConnectInfo_t conInfo = {0};
	conInfo.dwSize = sizeof(tmConnectInfo_t);
	strcpy(conInfo.pIp, m_pAdapter->GetRemoteIp());
	conInfo.iPort = m_pAdapter->GetRemotePort();
	strcpy(conInfo.szUser, m_pAdapter->GetRemoteUser());
	strcpy(conInfo.szPass, m_pAdapter->GetRemotePw());

	nRet = TMCC_Connect(devHandle, &conInfo, true);
	if (nRet != TMCC_ERR_SUCCESS)
    {
        J_OS::LOGINFO("CAipstarChannel::PtzControl Connect Error %d", nRet);
		return J_UNKNOW;
    }
	if (nCmd == JO_PTZ_PRE_SET || nCmd == JO_PTZ_PRE_CLR || nCmd == JO_PTZ_GOTO_PRE)
	{
		switch (nCmd)
		{
		case JO_PTZ_PRE_SET:
		ptzCmd = PTZ_SET_PRESET;
			break;
		case JO_PTZ_PRE_CLR:
		ptzCmd = PTZ_CLE_PRESET;
			break;
		case JO_PTZ_GOTO_PRE:
		ptzCmd = PTZ_GOTO_PRESET;
			break;
		}
		nRet = TMCC_PtzPreset(devHandle, ptzCmd, nParam, 5);
	}
	else
	{
		switch (nCmd)
		{
		case JO_PTZ_UP:
            ptzCmd = PTZ_UP;
			break;
		case JO_PTZ_DOWN:
            ptzCmd = PTZ_DOWN;
			break;
		case JO_PTZ_LEFT:
            ptzCmd = PTZ_LEFT;
			break;
		case JO_PTZ_RIGHT:
            ptzCmd = PTZ_RIGHT;
			break;
		case JO_PTZ_UP_LEFT:
            ptzCmd = PTZ_LEFTUP;
			break;
		case JO_PTZ_UP_RIGHT:
            ptzCmd = PTZ_RIGHTUP;
			break;
		case JO_PTZ_DOWN_LEFT:
            ptzCmd = PTZ_LEFTDOWN;
			break;
		case JO_PTZ_DOWN_RIGHT:
            ptzCmd = PTZ_RIGHTDOWN;
			break;
		case JO_PTZ_ZOOM_IN:
            ptzCmd = PTZ_ZOOM_IN;
			break;
		case JO_PTZ_ZOOM_OUT:
            ptzCmd = PTZ_ZOOM_OUT;
			break;
		case JO_PTZ_FOCUS_NEAR:
            ptzCmd = PTZ_FOCUS_NEAR;
			break;
		case JO_PTZ_FOCUS_FAR:
            ptzCmd = PTZ_FOCUS_FAR;
			break;
		case JO_PTZ_IRIS_OPEN:
            ptzCmd = PTZ_IRIS_ENLARGE;
			break;
		case JO_PTZ_IRIS_CLOSE:
            ptzCmd = PTZ_IRIS_SHRINK;
			break;
		}
		if (nParam == 0)
		{
			nRet = TMCC_PtzControl(devHandle, ptzCmd, 0, nParam);
		}
		else
		{
			nRet = TMCC_PtzControl(devHandle, ptzCmd, 1, nParam);
		}
	}

	if (nRet != TMCC_ERR_SUCCESS)
	{
	    J_OS::LOGINFO("CAipstarChannel::PtzControl Error %d", nRet);
	    //m_pAdapter->Relogin();
	}
	TMCC_DisConnect(devHandle);

	return (nRet == TMCC_ERR_SUCCESS ? J_OK : J_UNKNOW);
}

int CAipstarChannel::StartView()
{
	tmPlayRealStreamCfg_t realInfo = {0};
	realInfo.dwSize = sizeof(tmRealStreamInfo_t);
	strcpy(realInfo.szAddress, m_pAdapter->GetRemoteIp());
	realInfo.iPort = m_pAdapter->GetRemotePort();
	strcpy(realInfo.szUser, m_pAdapter->GetRemoteUser());
	strcpy(realInfo.szPass, m_pAdapter->GetRemotePw());
	realInfo.byChannel = m_nChannel - 1;
	realInfo.byStream = m_nStreamType;
	realInfo.byReConnectNum = 1;
	realInfo.iReConnectTime = 10;

	int nRet = TMCC_ConnectStream(m_hStream, &realInfo, NULL);
    if (nRet != TMCC_ERR_SUCCESS)
	{
	    J_OS::LOGINFO("CAipstarChannel::StartView Error %d", nRet);
	    return J_DEV_BROKEN;
	}
	TMCC_MakeKeyFrame(m_hStream);

	return J_OK;
}

int CAipstarChannel::StopView()
{
	int nRet = TMCC_CloseStream(m_hStream);
    if (nRet != TMCC_ERR_SUCCESS)
	{
	    J_OS::LOGINFO("CAipstarChannel::StopView Error %d", nRet);
	}

	return J_OK;
}
