#include "SonyChannel.h"
#include "SonyStream.h"
#include "x_base64.h"

const char *viewRequest =
		"GET /image%d HTTP/1.1\r\n"
		"Host: %s\r\n"
		"Connection: Close\r\n\r\n";

const char *ptzfCommand =
		"GET /command/ptzf.cgi?Move=%s,%s HTTP/1.1\r\n"
		"Host: %s\r\n"
		"Connection: Close\r\n"
		"Pragma: no-cache\r\n"
		"Cache-Control: no-store, no-cache\r\n"
		"Expires: Mon, 01 Jan 1990 01:01:01 GMT\r\n\r\n";

const char *presetCommand =
		"POST /command/presetposition.cgi HTTP/1.1\r\n"
		"Accept: */*\r\n"
		"Accept-Language: zh-cn\r\n"
		"Referer: http://%s/zh_hans/l4/position/preset.html\r\n"
		"Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n"
		"Accept-Encoding: gzip, deflate\r\n"
		"User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729)\r\n"
		"Host: %s\r\n"
		"Content-Length: %d\r\n"
		"Connection: Keep-Alive\r\n"
		"Cache-Control: no-cache\r\n"
		"Authorization: Basic %s\r\n\r\n%s";

const char *presetSet = "PresetSet=%d,%d,on&PresetThumbnailClear=1";
const char *presetCall = "PresetCall=%d,24";

CSonyChannel::CSonyChannel(const char *pResid, void *pOwner, int nChannel, int nStream, int nMode)
: m_pAdapter(NULL)
, m_nChannel(0)
, m_bOpened(false)
{
	m_pAdapter = (CSonyAdapter *) pOwner;
	m_nChannel = nChannel;
	m_nStreamType = nStream;
	m_nProtocol = nMode;

	m_recvSocket = NULL;
}

CSonyChannel::~CSonyChannel()
{

}

int CSonyChannel::PtzControl(int nCmd, int nParam)
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
			{
				sprintf(command, presetSet, nParam);
				sprintf(ptzCommand, presetCommand, m_pAdapter->GetRemoteIp(), m_pAdapter->GetRemoteIp()
						, strlen(command),authorization, command);
			}
			break;
		case jo_ptz_goto_pre:
				sprintf(command, presetCall, nParam, nParam);
				sprintf(ptzCommand, presetCommand, m_pAdapter->GetRemoteIp(), m_pAdapter->GetRemoteIp()
						, strlen(command),authorization, command);
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
				sprintf(ptzCommand, ptzfCommand, "up", "0", m_pAdapter->GetRemoteIp());
				break;
			case jo_ptz_down:
				sprintf(ptzCommand, ptzfCommand, "down", "0", m_pAdapter->GetRemoteIp());
				break;
			case jo_ptz_left:
				sprintf(ptzCommand, ptzfCommand, "left", "0", m_pAdapter->GetRemoteIp());
				break;
			case jo_ptz_right:
				sprintf(ptzCommand, ptzfCommand, "right", "0", m_pAdapter->GetRemoteIp());
				break;
			case jo_ptz_up_left:
				sprintf(ptzCommand, ptzfCommand, "up-left", "0", m_pAdapter->GetRemoteIp());
				break;
			case jo_ptz_up_right:
				sprintf(ptzCommand, ptzfCommand, "up-right", "0", m_pAdapter->GetRemoteIp());
				break;
			case jo_ptz_down_left:
				sprintf(ptzCommand, ptzfCommand, "down-left", "0", m_pAdapter->GetRemoteIp());
				break;
			case jo_ptz_down_right:
				sprintf(ptzCommand, ptzfCommand, "down-right", "0", m_pAdapter->GetRemoteIp());
				break;
			case jo_ptz_zoom_in:
				sprintf(ptzCommand, ptzfCommand, "tele", "0", m_pAdapter->GetRemoteIp());
				break;
			case jo_ptz_room_out:
				sprintf(ptzCommand, ptzfCommand, "wide", "0", m_pAdapter->GetRemoteIp());
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
				sprintf(ptzCommand, ptzfCommand, "stop", "motor", m_pAdapter->GetRemoteIp());
				break;
			case jo_ptz_zoom_in:
			case jo_ptz_room_out:
				sprintf(ptzCommand, ptzfCommand, "stop", "zoom", m_pAdapter->GetRemoteIp());
				break;
			default:
				break;
			}
		}
	}

	return SendCommand(ptzCommand);
}

int CSonyChannel::OpenStream(void *&pObj, CRingBuffer *pRingBuffer)
{
	if (m_pAdapter->GetStatus() != jo_dev_ready)
	{
		m_bOpened = false;
		return J_DEV_BROKEN;
	}

	if (m_bOpened && pObj != NULL)
	{
		(static_cast<CSonyStream *> (pObj))->AddRingBuffer(pRingBuffer);

		return J_OK;
	}

	int nRet = StartView();
	if (nRet != J_OK)
	{
	    m_pAdapter->Broken();
		return J_STREAM_ERROR;
	}

	m_bOpened = true;
	pObj = new CSonyStream(m_recvSocket, m_resid);
	(static_cast<CSonyStream *> (pObj))->AddRingBuffer(pRingBuffer);
	(static_cast<CSonyStream *> (pObj))->Startup();

	return J_OK;
}

int CSonyChannel::CloseStream(void *pObj, CRingBuffer *pRingBuffer)
{
	if (!m_bOpened)
		return J_OK;

	CSonyStream *pSonyStream = static_cast<CSonyStream *>(pObj);
	if (pSonyStream == NULL)
		return J_OK;

	if (pSonyStream->RingBufferCount() == 1)
	{
		StopView();
		m_bOpened = false;
		(static_cast<CSonyStream *> (pObj))->Shutdown();
		pSonyStream->DelRingBuffer(pRingBuffer);
		delete (CSonyStream *) pObj;

		return J_NO_REF;
	}

	if (pSonyStream->RingBufferCount() > 0)
		pSonyStream->DelRingBuffer(pRingBuffer);

	return J_OK;
}


int CSonyChannel::StartView()
{
	if (m_recvSocket != NULL)
	{
		delete m_recvSocket;
		m_recvSocket = NULL;
	}
	m_recvSocket = new J_OS::CTCPSocket();
	m_recvSocket->Connect(m_pAdapter->GetRemoteIp(),
			m_pAdapter->GetRemotePort());

	char reqBuff[1024] = {0};
	sprintf(reqBuff, viewRequest, m_nStreamType + 1, m_pAdapter->GetRemoteIp());
	if (m_recvSocket->Write((char*)reqBuff, strlen(reqBuff)) < 0)
	{
		if (errno == EPIPE)
		{
			delete m_recvSocket;
			m_recvSocket = NULL;
		}
		return J_INVALID_DEV;
	}

	if (m_recvSocket->Read((char*)reqBuff, sizeof(reqBuff)) < 0)
		return J_INVALID_DEV;

	return J_OK;
}

int CSonyChannel::StopView()
{
	if (m_recvSocket != NULL)
	{
		delete m_recvSocket;
		m_recvSocket = NULL;
	}

	return J_OK;
}

int CSonyChannel::SendCommand(const char *pCommand)
{
	J_OS::CTCPSocket cmdSocket(m_pAdapter->GetRemoteIp(),
			m_pAdapter->GetRemotePort());
	if (cmdSocket.GetHandle() == -1)
		return J_INVALID_DEV;

	if (cmdSocket.Write((char*)pCommand, strlen(pCommand)) < 0)
		return J_INVALID_DEV;

	return J_OK;
}
