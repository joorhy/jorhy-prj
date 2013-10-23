#include "HikSdkAdapter.h"
#include "HikSdkChannel.h"
#include "HikSdkStream.h"
#include "HikSdkParser.h"

CHikSdkChannel::CHikSdkChannel(const char *pResid, J_Obj *pOwner, int nChannel,
		int nStream, int nMode) 
{
	m_bOpened = false;

	m_pAdapter = dynamic_cast<CHikSdkAdapter *> (pOwner);
	m_nChannel = nChannel;
	m_nStreamType = nStream;
	m_nProtocol = nMode;
	m_hStream = -1;

	m_resid = pResid;
	
	J_OS::LOGINFO("CHikSdkChannel::CHikSdkChannel()");
}

CHikSdkChannel::~CHikSdkChannel()
{
	J_OS::LOGINFO("CHikSdkChannel::~CHikSdkChannel()");
}

///J_VideoChannel
int CHikSdkChannel::PtzControl(int nCmd, int nParam)
{
	int ptzCmd = 0;
	int nSpeed = 0;
	if (nCmd == jo_ptz_pre_set || nCmd == jo_ptz_pre_clr || nCmd == jo_ptz_goto_pre)
	{
		switch (nCmd)
		{
		case jo_ptz_pre_set:
		ptzCmd = HIK_PTZ_PRESET_SET;
			break;
		case jo_ptz_pre_clr:
		ptzCmd = HIK_PTZ_PRESET_CLR;
			break;
		case jo_ptz_goto_pre:
		ptzCmd = HIK_PTZ_PRESET_MOV;
			break;
		}
		NET_DVR_PTZPreset_Other(m_pAdapter->GetUserId(), m_nChannel, ptzCmd, nParam);
	}
	else
	{
		switch (nCmd)
		{
		case jo_ptz_up:
			ptzCmd = HIK_PTZ_MOVE_UP;
			break;
		case jo_ptz_down:
			ptzCmd = HIK_PTZ_MOVE_DOWN;
			break;
		case jo_ptz_left:
			ptzCmd = HIK_PTZ_MOVE_LEFT;
			break;
		case jo_ptz_right:
			ptzCmd = HIK_PTZ_MOVE_RIGHT;
			break;
		case jo_ptz_up_left:
			ptzCmd = HIK_PTZ_MOVE_UP_LEFT;
			break;
		case jo_ptz_up_right:
			ptzCmd = HIK_PTZ_MOVE_UP_RIGHT;
			break;
		case jo_ptz_down_left:
			ptzCmd = HIK_PTZ_MOVE_DOWN_LEFT;
			break;
		case jo_ptz_down_right:
			ptzCmd = HIK_PTZ_MOVE_DOWN_RIGHT;
			break;
		case jo_ptz_zoom_in:
			ptzCmd = HIK_PTZ_ZOOM_IN;
			break;
		case jo_ptz_room_out:
			ptzCmd = HIK_PTZ_ZOOM_OUT;
			break;
		case jo_ptz_focus_near:
			ptzCmd = HIK_PTZ_FOCUS_NEAR;
			break;
		case jo_ptz_focus_far:
			ptzCmd = HIK_PTZ_FOCUS_FAR;
			break;
		case jo_ptz_iris_open:
			ptzCmd = HIK_PTZ_IRIS_OPEN;
			break;
		case jo_ptz_iris_close:
			ptzCmd = HIK_PTZ_IRIS_CLOSE;
			break;
		}
		if (nParam == 0)
		{
			!NET_DVR_PTZControlWithSpeed_Other(m_pAdapter->GetUserId(), m_nChannel, ptzCmd, 1, 0);
		}
		else
		{
			nSpeed = nParam / 37 + 1;
			//if (!NET_DVR_PTZControlWithSpeed(m_hStream, ptzCmd, 0, nSpeed))
			if (!NET_DVR_PTZControlWithSpeed_Other(m_pAdapter->GetUserId(), m_nChannel, ptzCmd, 0, nSpeed))
			{
				J_OS::LOGINFO("NET_DVR_PTZControlWithSpeed Error %d", NET_DVR_GetLastError());
			}
		}
	}
	

	return J_OK;
}

int CHikSdkChannel::OpenStream(J_Obj *&pObj, CRingBuffer *pRingBuffer)
{
	if (m_pAdapter->GetStatus() != jo_dev_ready)
	{
		m_pAdapter->Broken();
		m_bOpened = false;
		return J_DEV_BROKEN;
	}

	if (m_bOpened && pObj != NULL)
	{
		//NET_DVR_MakeKeyFrame(m_pAdapter->GetUserId(), m_nChannel);
		(dynamic_cast<CHikSdkStream *> (pObj))->AddRingBuffer(pRingBuffer);
		return J_OK;
	}

	pObj = new CHikSdkStream(m_resid);
	
	NET_DVR_PREVIEWINFO prevInfo = {0};
	prevInfo.lChannel = m_nChannel;
	prevInfo.dwStreamType = m_nStreamType;
	prevInfo.dwLinkMode = 0;//TCP
	prevInfo.hPlayWnd = NULL;
	prevInfo.bBlocked = 1;//no block
	prevInfo.bPassbackRecord = 0;
	prevInfo.byPreviewMode = 0;
	prevInfo.byProtoType = 0;
	m_hStream = NET_DVR_RealPlay_V40(m_pAdapter->GetUserId(), &prevInfo, CHikSdkStream::RealDataCallback, pObj);
	if (m_hStream == -1)
	{
		m_pAdapter->Broken();
		//m_pAdapter->Relogin();
		delete pObj;
		J_OS::LOGINFO("CHikSdkChannel::OpenStream StartView error, ret = %d", NET_DVR_GetLastError());
		return J_STREAM_ERROR;
	}

	m_bOpened = true;
	m_pStream = pObj;
	(dynamic_cast<CHikSdkStream *> (pObj))->AddRingBuffer(pRingBuffer);
	(dynamic_cast<CHikSdkStream *> (pObj))->Startup();

	return J_OK;
}

int CHikSdkChannel::CloseStream(J_Obj *pObj, CRingBuffer *pRingBuffer)
{
	if (!m_bOpened)
		return J_OK;

	CHikSdkStream *pHikStream = dynamic_cast<CHikSdkStream *>(pObj);
	if (pHikStream == NULL)
		return J_OK;

	if (pHikStream->RingBufferCount() == 1)
	{
		NET_DVR_StopRealPlay(m_hStream);
		m_hStream = -1;

		m_bOpened = false;
		(dynamic_cast<CHikSdkStream *> (pObj))->Shutdown();
		//J_OS::LOGINFO("StopView Begin");
		pHikStream->DelRingBuffer(pRingBuffer);
		//J_OS::LOGINFO("StopView End");
		delete pObj;

		return J_NO_REF;
	}

	if (pHikStream->RingBufferCount() > 0)
		pHikStream->DelRingBuffer(pRingBuffer);

	return J_OK;
}