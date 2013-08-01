#include "OnvifChannel.h"
#include "OnvifStream.h"
#include "x_base64.h"

#define RATE_CHANGE(nRate) (/*1.0f*/static_cast<float>(nRate/256.0f))

COnvifChannel::COnvifChannel(const char *pResid, J_Obj *pOwner, int nChannel, int nStream, int nMode)
: m_pAdapter(NULL)
, m_nChannel(0)
, m_bOpened(false)
{
	m_pAdapter = dynamic_cast<COnvifAdapter *>(pOwner);
	m_nChannel = nChannel;
	m_nStreamType = nStream;
	m_nProtocol = nMode;

	m_recvSocket = NULL;
}

COnvifChannel::~COnvifChannel()
{

}

int COnvifChannel::PtzControl(int nCmd, int nParam)
{
	printf("COnvifChannel::PtzControl start\n");
	char ptzCommand[1024] = {0};
	if (nCmd == jo_ptz_pre_set || nCmd == jo_ptz_pre_clr || nCmd == jo_ptz_goto_pre)
	{
		char command[128] = {0};
		char authorization[32] = {0};
		char uname_pw[64] = {0};
		sprintf(uname_pw, "%s:%s", m_pAdapter->GetUser(), m_pAdapter->GetPassword());
		base64_in((unsigned char *)uname_pw, authorization, strlen(uname_pw));

		switch (nCmd)
		{
		case jo_ptz_pre_set:
			break;
		case jo_ptz_goto_pre:
			break;
		}
		//J_OS::LOGINFO(ptzCommand);
	}
	else
	{
		if (nParam > 0)
		{
			switch (nCmd)
			{
			case jo_ptz_up:
				m_pAdapter->m_OnvifPtz.PTZUp(RATE_CHANGE(nParam));
				break;
			case jo_ptz_down:
				m_pAdapter->m_OnvifPtz.PTZDown(RATE_CHANGE(nParam));
				break;
			case jo_ptz_left:
				m_pAdapter->m_OnvifPtz.PTZLeft(RATE_CHANGE(nParam));
				break;
			case jo_ptz_right:
				m_pAdapter->m_OnvifPtz.PTZRight(RATE_CHANGE(nParam));
				break;
			case jo_ptz_up_left:
				break;
			case jo_ptz_up_right:
				break;
			case jo_ptz_down_left:
				break;
			case jo_ptz_down_right:
				break;
			case jo_ptz_zoom_in:
				m_pAdapter->m_OnvifPtz.PTZZoomIn(RATE_CHANGE(nParam));
				break;
			case jo_ptz_room_out:
				m_pAdapter->m_OnvifPtz.PTZZoomOut(RATE_CHANGE(nParam));
				break;
			case jo_ptz_focus_near:
				break;
			case jo_ptz_focus_far:
				break;
			case jo_ptz_iris_open:
				break;
			case jo_ptz_iris_close:
				break;
			}
		}
		else
		{
			switch (nCmd)
			{
			case jo_ptz_up:
			case jo_ptz_down:
			case jo_ptz_left:
			case jo_ptz_right:
			case jo_ptz_up_left:
			case jo_ptz_up_right:
			case jo_ptz_down_left:
			case jo_ptz_down_right:
				break;
			case jo_ptz_zoom_in:
			case jo_ptz_room_out:
				break;
			default:
				break;
			}
			m_pAdapter->m_OnvifPtz.PTZStop();
		}
	}
	printf("COnvifChannel::PtzControl end\n");

	return J_OK;
}

int COnvifChannel::OpenStream(J_Obj *&pObj, CRingBuffer *pRingBuffer)
{
	if (m_pAdapter->GetStatus() != jo_dev_ready)
	{
		m_bOpened = false;
		return J_DEV_BROKEN;
	}

	if (m_bOpened && pObj != NULL)
	{
		(dynamic_cast<COnvifStream *> (pObj))->AddRingBuffer(pRingBuffer);

		return J_OK;
	}

	m_bOpened = true;
	pObj = new COnvifStream(m_recvSocket, m_resid);
	(dynamic_cast<COnvifStream *> (pObj))->AddRingBuffer(pRingBuffer);
	(dynamic_cast<COnvifStream *> (pObj))->Startup();

	return J_OK;
}

int COnvifChannel::CloseStream(J_Obj *pObj, CRingBuffer *pRingBuffer)
{
	if (!m_bOpened)
		return J_OK;

	COnvifStream *pSonyStream = dynamic_cast<COnvifStream *>(pObj);
	if (pSonyStream == NULL)
		return J_OK;

	if (pSonyStream->RingBufferCount() == 1)
	{
		//StopView();
		m_bOpened = false;
		(dynamic_cast<COnvifStream *> (pObj))->Shutdown();
		pSonyStream->DelRingBuffer(pRingBuffer);
		delete pObj;

		return J_NO_REF;
	}

	if (pSonyStream->RingBufferCount() > 0)
		pSonyStream->DelRingBuffer(pRingBuffer);

	return J_OK;
}

