#include "OnvifChannel.h"
#include "OnvifStream.h"
#include "x_base64.h"

COnvifChannel::COnvifChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode)
: m_pAdapter(NULL)
, m_nChannel(0)
, m_bOpened(false)
{
	m_pAdapter = (COnvifAdapter *) pOwner;
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
				break;
			case jo_ptz_down:
				break;
			case jo_ptz_left:
				break;
			case jo_ptz_right:
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
				break;
			case jo_ptz_room_out:
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
		}
	}

	return SendCommand(ptzCommand);
}

int COnvifChannel::OpenStream(void *&pObj, CRingBuffer *pRingBuffer)
{
	if (m_pAdapter->GetStatus() != jo_dev_ready)
	{
		m_bOpened = false;
		return J_DEV_BROKEN;
	}

	if (m_bOpened && pObj != NULL)
	{
		(static_cast<COnvifStream *> (pObj))->AddRingBuffer(pRingBuffer);

		return J_OK;
	}

	int nRet = StartView();
	if (nRet != J_OK)
	{
	    //m_pAdapter->Broken();
		return J_STREAM_ERROR;
	}

	m_bOpened = true;
	pObj = new COnvifStream(m_recvSocket, m_resid);
	(static_cast<COnvifStream *> (pObj))->AddRingBuffer(pRingBuffer);
	(static_cast<COnvifStream *> (pObj))->Startup();

	return J_OK;
}

int COnvifChannel::CloseStream(void *pObj, CRingBuffer *pRingBuffer)
{
	if (!m_bOpened)
		return J_OK;

	COnvifStream *pSonyStream = static_cast<COnvifStream *>(pObj);
	if (pSonyStream == NULL)
		return J_OK;

	if (pSonyStream->RingBufferCount() == 1)
	{
		StopView();
		m_bOpened = false;
		(static_cast<COnvifStream *> (pObj))->Shutdown();
		pSonyStream->DelRingBuffer(pRingBuffer);
		delete (COnvifStream *) pObj;

		return J_NO_REF;
	}

	if (pSonyStream->RingBufferCount() > 0)
		pSonyStream->DelRingBuffer(pRingBuffer);

	return J_OK;
}


int COnvifChannel::StartView()
{
	if (m_recvSocket != NULL)
	{
		delete m_recvSocket;
		m_recvSocket = NULL;
	}
	m_recvSocket = new J_OS::CTCPSocket();
	m_recvSocket->Connect(m_pAdapter->GetRemoteIp(),
			m_pAdapter->GetRemotePort());

	if (m_rtspHelper.OpenStream(m_recvSocket, m_pAdapter->GetRemoteIp(), m_pAdapter->GetRemotePort(), m_nChannel) != J_OK)
	{
		delete m_recvSocket;
		m_recvSocket = NULL;
		
		return J_INVALID_DEV;
	}

	return J_OK;
}

int COnvifChannel::StopView()
{
	m_rtspHelper.CloseStream(m_recvSocket, m_pAdapter->GetRemoteIp(), m_pAdapter->GetRemotePort(), m_nChannel);
	if (m_recvSocket != NULL)
	{
		delete m_recvSocket;
		m_recvSocket = NULL;
	}

	return J_OK;
}

int COnvifChannel::SendCommand(const char *pCommand)
{
	J_OS::CTCPSocket cmdSocket(m_pAdapter->GetRemoteIp(),
			m_pAdapter->GetRemotePort());
	if (cmdSocket.GetHandle() == -1)
		return J_INVALID_DEV;

	if (cmdSocket.Write((char*)pCommand, strlen(pCommand)) < 0)
		return J_INVALID_DEV;

	return J_OK;
}
