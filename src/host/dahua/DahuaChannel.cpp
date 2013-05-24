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
	if (m_pAdapter->GetStatus() != jo_dev_ready)
	{
		m_pAdapter->Broken();
		m_pAdapter->Relogin();
		m_bOpened = false;
		return J_DEV_BROKEN;
	}
	
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
	if (nCmd == jo_ptz_pre_set || nCmd == jo_ptz_pre_clr || nCmd == jo_ptz_goto_pre)
	{
		switch (nCmd)
		{
		case jo_ptz_pre_set:
			ptzCmd = DH_PTZ_POINT_SET_CONTROL;
			break;
		case jo_ptz_pre_clr:
			ptzCmd = DH_PTZ_POINT_DEL_CONTROL;
			break;
		case jo_ptz_goto_pre:
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
		case jo_ptz_up:
            ptzCmd = DH_PTZ_UP_CONTROL;
			param2 = nSpeed;
			break;
		case jo_ptz_down:
            ptzCmd = DH_PTZ_DOWN_CONTROL;
			param2 = nSpeed;
			break;
		case jo_ptz_left:
            ptzCmd = DH_PTZ_LEFT_CONTROL;
			param2 = nSpeed;
			break;
		case jo_ptz_right:
            ptzCmd = DH_PTZ_RIGHT_CONTROL;
			param2 = nSpeed;
			break;
		case jo_ptz_up_left:
            ptzCmd = DH_EXTPTZ_LEFTTOP;
			param1 = nSpeed2;
			param2 = nSpeed2;
			break;
		case jo_ptz_up_right:
            ptzCmd = DH_EXTPTZ_RIGHTTOP;
			param1 = nSpeed2;
			param2 = nSpeed2;
			break;
		case jo_ptz_down_left:
            ptzCmd = DH_EXTPTZ_LEFTDOWN;
			param1 = nSpeed2;
			param2 = nSpeed2;
			break;
		case jo_ptz_down_right:
            ptzCmd = DH_EXTPTZ_RIGHTDOWN;
			param1 = nSpeed2;
			param2 = nSpeed2;
			break;
		case jo_ptz_zoom_in:
            ptzCmd = DH_PTZ_ZOOM_ADD_CONTROL;
			param2 = nSpeed;
			break;
		case jo_ptz_room_out:
            ptzCmd = DH_PTZ_ZOOM_DEC_CONTROL;
			param2 = nSpeed;
			break;
		case jo_ptz_focus_near:
            ptzCmd = DH_PTZ_FOCUS_ADD_CONTROL;
			param2 = nSpeed;
			break;
		case jo_ptz_focus_far:
            ptzCmd = DH_PTZ_FOCUS_DEC_CONTROL;
			param2 = nSpeed;
			break;
		case jo_ptz_iris_open:
            ptzCmd = DH_PTZ_APERTURE_ADD_CONTROL;
			param2 = nSpeed;
			break;
		case jo_ptz_iris_close:
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
	if (m_nStreamType == 0)
		m_lRealHandle = CLIENT_RealPlayEx(m_pAdapter->GetDevID(), m_nChannel - 1, NULL, DH_RType_Realplay_0);
	else
		m_lRealHandle = CLIENT_RealPlayEx(m_pAdapter->GetDevID(), m_nChannel - 1, NULL, DH_RType_Realplay_1);
		
    if (m_lRealHandle == 0)
	{
		//_EC();
	    J_OS::LOGINFO("CDahuaChannel::StartView Error %u", CLIENT_GetLastError());
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
