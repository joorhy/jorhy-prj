#include "DahuaChannel.h"
#include "DahuaStream.h"
#include <math.h>

CDahuaChannel::CDahuaChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode)
{
	m_bOpened = false;
	m_nChannel = nChannel;

	m_pAdapter = (CDahuaAdapter *) pOwner;
	m_nChannel = nChannel;
	m_nStreamType = nStream;
	m_nProtocol = nMode;
	m_lRealHandle = 0;

	m_resid = pResid;
}

CDahuaChannel::~CDahuaChannel()
{

}

int CDahuaChannel::OpenStream(void *&pObj, CRingBuffer *pRingBuffer)
{
	if (m_bOpened && pObj != NULL)
	{
		(static_cast<CDahuaStream *> (pObj))->AddRingBuffer(pRingBuffer);
		return J_OK;
	}

	pObj = new CDahuaStream(m_resid, m_nChannel);
	int nRet = StartView();
	if (nRet != J_OK)
	{
		m_pAdapter->Broken();
		delete pObj;
		J_OS::LOGINFO("CDahuaChannel::OpenStream StartView error, ret = %d", nRet);
		return J_STREAM_ERROR;
	}
	CLIENT_SetRealDataCallBack(m_lRealHandle, CDahuaStream::OnStreamCallBack, (DWORD)pObj);

	m_bOpened = true;
	(static_cast<CDahuaStream *> (pObj))->AddRingBuffer(pRingBuffer);
	(static_cast<CDahuaStream *> (pObj))->Startup();

	return J_OK;
}

int CDahuaChannel::CloseStream(void *pObj, CRingBuffer *pRingBuffer)
{
	if (!m_bOpened)
		return J_OK;

	CDahuaStream *pStream = static_cast<CDahuaStream *>(pObj);
	if (pStream == NULL)
		return J_OK;

	if (pStream->RingBufferCount() == 1)
	{
		StopView();

		m_bOpened = false;
		(static_cast<CDahuaStream *> (pObj))->Shutdown();
		pStream->DelRingBuffer(pRingBuffer);
		delete (CDahuaStream *) pObj;

		return J_NO_REF;
	}

	if (pStream->RingBufferCount() > 0)
		pStream->DelRingBuffer(pRingBuffer);

	return J_OK;
}

int CDahuaChannel::PtzControl(int nCmd, int nParam)
{
	DWORD ptzCmd = 0;
	unsigned char param1;
	unsigned char param2;
	unsigned char param3;
	BOOL bRet = false;
	if (nCmd == JO_PTZ_PRE_SET || nCmd == JO_PTZ_PRE_CLR || nCmd == JO_PTZ_GOTO_PRE)
	{
		switch (nCmd)
		{
		case JO_PTZ_PRE_SET:
			ptzCmd = DH_PTZ_POINT_SET_CONTROL;
			break;
		case JO_PTZ_PRE_CLR:
			ptzCmd = DH_PTZ_POINT_DEL_CONTROL;
			break;
		case JO_PTZ_GOTO_PRE:
			ptzCmd = DH_PTZ_POINT_MOVE_CONTROL;
			break;
		}
		param2 = nParam;
		bRet = CLIENT_DHPTZControl(m_pAdapter->GetDevID(), m_nChannel - 1, ptzCmd, param1, param2, param3, false);
	}
	else
	{
		int nSpeed = nParam / 32 + 1;
		int nSpeed2 = sqrt(nSpeed * nSpeed / 2);
		switch (nCmd)
		{
		case JO_PTZ_UP:
            ptzCmd = DH_PTZ_UP_CONTROL;
			param2 = nSpeed;
			break;
		case JO_PTZ_DOWN:
            ptzCmd = DH_PTZ_DOWN_CONTROL;
			param2 = nSpeed;
			break;
		case JO_PTZ_LEFT:
            ptzCmd = DH_PTZ_LEFT_CONTROL;
			param2 = nSpeed;
			break;
		case JO_PTZ_RIGHT:
            ptzCmd = DH_PTZ_RIGHT_CONTROL;
			param2 = nSpeed;
			break;
		case JO_PTZ_UP_LEFT:
            ptzCmd = DH_EXTPTZ_LEFTTOP;
			param1 = nSpeed2;
			param2 = nSpeed2;
			break;
		case JO_PTZ_UP_RIGHT:
            ptzCmd = DH_EXTPTZ_RIGHTTOP;
			param1 = nSpeed2;
			param2 = nSpeed2;
			break;
		case JO_PTZ_DOWN_LEFT:
            ptzCmd = DH_EXTPTZ_LEFTDOWN;
			param1 = nSpeed2;
			param2 = nSpeed2;
			break;
		case JO_PTZ_DOWN_RIGHT:
            ptzCmd = DH_EXTPTZ_RIGHTDOWN;
			param1 = nSpeed2;
			param2 = nSpeed2;
			break;
		case JO_PTZ_ZOOM_IN:
            ptzCmd = DH_PTZ_ZOOM_ADD_CONTROL;
			param2 = nSpeed;
			break;
		case JO_PTZ_ZOOM_OUT:
            ptzCmd = DH_PTZ_ZOOM_DEC_CONTROL;
			param2 = nSpeed;
			break;
		case JO_PTZ_FOCUS_NEAR:
            ptzCmd = DH_PTZ_FOCUS_ADD_CONTROL;
			param2 = nSpeed;
			break;
		case JO_PTZ_FOCUS_FAR:
            ptzCmd = DH_PTZ_FOCUS_DEC_CONTROL;
			param2 = nSpeed;
			break;
		case JO_PTZ_IRIS_OPEN:
            ptzCmd = DH_PTZ_APERTURE_ADD_CONTROL;
			param2 = nSpeed;
			break;
		case JO_PTZ_IRIS_CLOSE:
            ptzCmd = DH_PTZ_APERTURE_DEC_CONTROL;
			param2 = nSpeed;
			break;
		}
		if (nParam == 0)
			bRet = CLIENT_DHPTZControl(m_pAdapter->GetDevID(), m_nChannel - 1, ptzCmd, param1, param2, param3, true);
		else 
			bRet = CLIENT_DHPTZControl(m_pAdapter->GetDevID(), m_nChannel - 1, ptzCmd, param1, param2, param3, false);
	}

	if (!bRet)
	{
	    J_OS::LOGINFO("CDahuaChannel::PtzControl Error");
	}

	return (bRet ? J_OK : J_UNKNOW);
}

int CDahuaChannel::StartView()
{
	m_lRealHandle = CLIENT_RealPlay(m_pAdapter->GetDevID(), m_nChannel - 1, NULL);
    if (m_lRealHandle == 0)
	{
	    J_OS::LOGINFO("CDahuaChannel::StartView Error %d", m_lRealHandle);
	    return J_DEV_BROKEN;
	}

	return J_OK;
}

int CDahuaChannel::StopView()
{
    if (!CLIENT_StopRealPlay(m_lRealHandle))
	{
	    J_OS::LOGINFO("CDahuaChannel::StopView Error");
	}

	return J_OK;
}
