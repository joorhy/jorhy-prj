#include "HikAdapter.h"
#include "HikChannel.h"
#include "HikStream.h"
#include "HikParser.h"
#include "HikVodStream.h"
#include "x_msg_queue.h"
#include "x_media_msg.h"

#define DATA_BUFF_SIZE	1024

CHikChannel::CHikChannel(const char *pResid, void *pOwner, int nChannel,
		int nStream, int nMode) :
	m_pAdapter(NULL), m_nChannel(0), m_pDataBuff(NULL), m_bOpened(false)
{
	m_pAdapter = (CHikAdapter *) pOwner;
	m_nChannel = nChannel;
	m_nStreamType = nStream;
	m_nProtocol = nMode;

	m_recvSocket = NULL;
	m_pDataBuff = new char[DATA_BUFF_SIZE];
	memset(m_pDataBuff, 0, DATA_BUFF_SIZE);

	m_resid = pResid;

	J_OS::LOGINFO("CHikChannel::CHikChannel()");
	//signal(SIGPIPE, SIG_IGN);

	//m_timer = J_OS::ADD_TIMER2(3, CHikChannel::OnTimer, (unsigned long)this, false);
}

CHikChannel::~CHikChannel()
{
	if (m_pDataBuff != NULL)
		delete m_pDataBuff;

	if (m_recvSocket != NULL)
		delete m_recvSocket;

	m_timer.Destroy();
	J_OS::LOGINFO("CHikChannel::~CHikChannel()");
}

///J_VideoChannel
int CHikChannel::PtzControl(int nCmd, int nParam)
{
	int mainCmd = 0;
	int ptzCmd = 0;
	HikPtzData ptzData;
	ptzData.channelNum = htonl(m_nChannel);
	if (nCmd == jo_ptz_pre_set || nCmd == jo_ptz_pre_clr || nCmd == jo_ptz_goto_pre)
	{
		ptzData.param = htonl(nParam);
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
		mainCmd = HIK_CMD_PTZ_CTRL;
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
			ptzData.param = htonl(0);
			ptzCmd = ~ptzCmd;
		}
		else
		{
			ptzData.param = htonl(nParam / 37 + 1);
		}
		mainCmd = HIK_CMD_PTZ_CTRL_WITH_SPEED;
	}
	ptzData.cmd = htonl(ptzCmd);

	return SendCommand(mainCmd, (const char *) &ptzData, sizeof(HikPtzData));
}

int CHikChannel::EmunFileByTime(time_t beginTime, time_t endTime,
		std::vector<J_FileInfo> &fileList)
{
	HikCommHead commHead;
	memset(&commHead, 0, sizeof(HikCommHead));
	commHead.len = htonl(sizeof(HikCommHead) + sizeof(HikFindFile));
	commHead.protoType = 90;/*(THIS_SDK_VERSION < NETSDK_VERSION_V30) ? 90 : 99*/;
	commHead.command = htonl(HIK_CMD_FIND_FILE_V3);
	commHead.userId = htonl(m_pAdapter->GetUserId());
	m_pAdapter->GetLocalNetInfo(commHead.clientIP, commHead.clientMAC);
	commHead.checkSum = htonl(
			m_pAdapter->CheckSum((unsigned char*) &commHead,
					sizeof(HikCommHead)));

	J_OS::CTCPSocket sendSocket(m_pAdapter->GetRemoteIp(),
			m_pAdapter->GetRemotePort());
	if (sendSocket.Write((char*) &commHead, sizeof(commHead)) < 0)
	{
		J_OS::LOGINFO("CHikChannel::EmunFileByTime FindFile error");
		return J_SOCKET_ERROR;
	}

	HikFindFile findFile;
	memset(&findFile, 0, sizeof(HikFindFile));
	findFile.channelNum = htonl(m_nChannel);
	findFile.fileType = htonl(0xff);
	findFile.lockState = htonl(0xff);
	findFile.needCardNum = htonl(0);
	Convert2HikTime(beginTime, findFile.beginTime);
	Convert2HikTime(endTime, findFile.endTime);

	if (sendSocket.Write((char*) &findFile, sizeof(HikFindFile)) < 0)
	{
		J_OS::LOGINFO("CHikChannel::EmunFileByTime FindFile error");
		return J_SOCKET_ERROR;
	}

	HikRetHead retHead;
	if (sendSocket.Read((char*) &retHead, sizeof(HikRetHead)) < 0)
	{
		J_OS::LOGINFO("CHikChannel::EmunFileByTime FindFile error");
		return J_SOCKET_ERROR;
	}

	retHead.retVal = ntohl(retHead.retVal);
	if (retHead.retVal != HIK_RET_OK)
	{
		m_pAdapter->Broken();
		return J_DEV_BROKEN;
	}

	int nFindState = NEEDWAIT;
	int fileNum = 0;
	HikFindFileRet findFileRet;
	while (true)
	{
		if (nFindState == NEEDWAIT)
		{
			if (sendSocket.Read((char*) &findFileRet, sizeof(HikFindFileRet))
					< 0)
			{
				J_OS::LOGINFO("CHikChannel::EmunFileByTime FindFile error");
				return J_SOCKET_ERROR;
			}

			nFindState = ntohl(findFileRet.state);
			if (nFindState == NEEDWAIT)
				j_sleep(1000);
		}
		else if (nFindState == RECVFILEINFO)
		{
			if (sendSocket.Read((char*) &fileNum, sizeof(int)) < 0)
			{
				J_OS::LOGINFO("CHikChannel::EmunFileByTime FindFile error");
				return J_SOCKET_ERROR;
			}
			fileNum = ntohl(fileNum);
			J_FileInfo fileInfo;
			for (int i = 0; i < fileNum; i++)
			{
				memset(&fileInfo, 0, sizeof(J_FileInfo));
				if (sendSocket.Read((char*) &fileInfo, sizeof(HikFileInfo)) < 0)
				{
					J_OS::LOGINFO("CHikChannel::EmunFileByTime FindFile error");
					return J_SOCKET_ERROR;
				}
				fileInfo.tStartTime = ntohl(fileInfo.tStartTime);
				fileInfo.tStoptime = ntohl(fileInfo.tStoptime);
				//fileInfo.ulFileSize = ntohl(fileInfo.ulFileSize);

				fileList.push_back(fileInfo);
			}
			nFindState = NEEDWAIT;
		}
		else
		{
			J_OS::LOGINFO(
					"CHikChannel::EmunFileByTime state = %d FindFile over, fileNum = %d",
					nFindState, fileNum);
			break;
		}
	}

	return J_OK;
}

int CHikChannel::OpenStream(void *&pObj, CRingBuffer *pRingBuffer)
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
		MakeIFrame(m_nChannel);
		(static_cast<CHikStream *> (pObj))->AddRingBuffer(pRingBuffer);
		return J_OK;
	}

	int nRet = StartView();
	if (nRet != J_OK)
	{
		m_pAdapter->Broken();
		m_pAdapter->Relogin();
		J_OS::LOGINFO("CHikChannel::OpenStream StartView error, ret = %d", nRet);
		return J_STREAM_ERROR;
	}

	m_bOpened = true;
	pObj = new CHikStream(m_recvSocket, m_resid);
	(static_cast<CHikStream *> (pObj))->AddRingBuffer(pRingBuffer);
	(static_cast<CHikStream *> (pObj))->Startup();

	return J_OK;
}

int CHikChannel::CloseStream(void *pObj, CRingBuffer *pRingBuffer)
{
	if (!m_bOpened)
		return J_OK;

	CHikStream *pHikStream = static_cast<CHikStream *>(pObj);
	if (pHikStream == NULL)
		return J_OK;

	if (pHikStream->RingBufferCount() == 1)
	{
		StopView();

		m_bOpened = false;
		(static_cast<CHikStream *> (pObj))->Shutdown();
		//J_OS::LOGINFO("StopView Begin");
		pHikStream->DelRingBuffer(pRingBuffer);
		//J_OS::LOGINFO("StopView End");
		delete (CHikStream *) pObj;

		return J_NO_REF;
	}

	if (pHikStream->RingBufferCount() > 0)
		pHikStream->DelRingBuffer(pRingBuffer);

	return J_OK;
}

int CHikChannel::OpenParser(void *&pObj)
{
	CHikParser *pHikParser = new CHikParser();
	if (pHikParser == NULL)
		return J_MEMORY_ERROR;

	pObj = pHikParser;

	return J_OK;
}

int CHikChannel::CloseParser(void *pObj)
{
	if (pObj != NULL)
		delete (CHikParser *) pObj;

	return J_OK;
}

int CHikChannel::OpenVodStream(void *&pObj)
{
	CHikVodStream *pHikVodStream = new CHikVodStream(m_pAdapter, m_nChannel);
	if (pHikVodStream == NULL)
		return J_MEMORY_ERROR;

	pObj = pHikVodStream;

	return J_OK;
}

int CHikChannel::CloseVodStream(void *pObj)
{
	if (pObj != NULL)
		delete (CHikVodStream *) pObj;

	return J_OK;
}

int CHikChannel::StartView()
{
	if (m_recvSocket != NULL)
	{
		delete m_recvSocket;
		m_recvSocket = NULL;
	}
	m_recvSocket = new J_OS::CTCPSocket();
	m_recvSocket->Connect(m_pAdapter->GetRemoteIp(),
			m_pAdapter->GetRemotePort());

	ViewSendData viewSendData;
	viewSendData.channelNum = htonl(m_nChannel);
	viewSendData.streamType = htonl(m_nStreamType);

	HikCommHead commHead;
	memset(&commHead, 0, sizeof(HikCommHead));
	commHead.len = htonl(sizeof(HikCommHead) + sizeof(ViewSendData));
	commHead.protoType = 90;/*(THIS_SDK_VERSION < NETSDK_VERSION_V30) ? 90 : 99*/;
	commHead.command = htonl(HIK_CMD_VIDEO_TCP);
	commHead.userId = htonl(m_pAdapter->GetUserId());
	m_pAdapter->GetLocalNetInfo(commHead.clientIP, commHead.clientMAC);
	commHead.checkSum = htonl(m_pAdapter->CheckSum((unsigned char*) &commHead, sizeof(HikCommHead)));

	if (m_recvSocket->Write((char*) &commHead, sizeof(commHead)) < 0)
	{
		if (errno == EPIPE)
		{
			delete m_recvSocket;
			m_recvSocket = NULL;
		}
		return J_INVALID_DEV;
	}

	if (m_recvSocket->Write((char *) &viewSendData, sizeof(viewSendData)) < 0)
	{
		if (errno == EPIPE)
		{
			delete m_recvSocket;
			m_recvSocket = NULL;
		}
		return J_INVALID_DEV;
	}

	HikRetHead retHead;
	int nReadLen = sizeof(HikRetHead);
	if (m_recvSocket->Read((char*) &retHead, nReadLen) < 0)
		return J_INVALID_DEV;

	retHead.len = ntohl(retHead.len);
	retHead.checkSum = ntohl(retHead.checkSum);
	retHead.retVal = ntohl(retHead.retVal);
	if (retHead.retVal != HIK_RET_OK)
	{
		//m_pAdapter->Broken();
		J_OS::LOGINFO("CHikChannel::StartView retVal = %d", retHead.retVal);
		return J_DEV_BROKEN;
	}

	int nRetDataLen = retHead.len - sizeof(HikRetHead);
	nReadLen = nRetDataLen;


	if (m_recvSocket->Read_n((char*) m_pDataBuff/* + sizeof(PackHeader)*/, nReadLen) < 0)
		return J_INVALID_DEV;

	MakeIFrame(m_nChannel);
	m_timer.Create(3 * 1000, CHikChannel::OnTimer, this);

	return J_OK;
}
int CHikChannel::StopView()
{
	//J_OS::LOGINFO("m_timer Destroy");
	m_timer.Destroy();
	if (m_recvSocket != NULL)
	{
		delete m_recvSocket;
		m_recvSocket = NULL;
	}

	return J_OK;
}

void CHikChannel::ExchangeData()
{
	if (NULL == m_recvSocket)
		return;

	HikCommHead commHead;
	memset(&commHead, 0, sizeof(HikCommHead));
	commHead.len = htonl(sizeof(HikCommHead));
	commHead.protoType = 90;/*(THIS_SDK_VERSION < NETSDK_VERSION_V30) ? 90 : 99*/;
	commHead.command = htonl(HIK_CMD_DATA_EXCHANGE);
	commHead.userId = htonl(m_pAdapter->GetUserId());
	m_pAdapter->GetLocalNetInfo(commHead.clientIP, commHead.clientMAC);
	commHead.checkSum = htonl(m_pAdapter->CheckSum((unsigned char*) &commHead, sizeof(HikCommHead)));

	if (m_recvSocket->Write((char*) &commHead, sizeof(commHead)) < 0)
	{
		StopView();
		J_OS::LOGINFO("CHikChannel::ExchangeData ExchangeData error");
	}
	//J_OS::LOGINFO("CHikChannel::ExchangeData ExchangeData error");
}

int CHikChannel::MakeIFrame(int nChannel)
{
	HikCommHead commHead;
	memset(&commHead, 0, sizeof(HikCommHead));
	commHead.len = htonl(sizeof(HikCommHead) + sizeof(int));
	commHead.protoType = 90;//(THIS_SDK_VERSION < NETSDK_VERSION_V30) ? 90 : 99;
	commHead.command = htonl(HIK_CMD_MAIN_MAKE_IFRAME);
	commHead.userId = htonl(m_pAdapter->GetUserId());
	m_pAdapter->GetLocalNetInfo(commHead.clientIP, commHead.clientMAC);
	commHead.checkSum = htonl(
			m_pAdapter->CheckSum((unsigned char*) &commHead,
					sizeof(HikCommHead)));

	J_OS::CTCPSocket sendSocket(m_pAdapter->GetRemoteIp(),
			m_pAdapter->GetRemotePort());
	if (sendSocket.Write((char*) &commHead, sizeof(commHead)) < 0)
	{
		J_OS::LOGINFO("CHikChannel::MakeIFrame IFrame error");
	}

	int nChannelNum = htonl(nChannel);
	if (sendSocket.Write((char*) &nChannelNum, sizeof(int)) < 0)
	{
		J_OS::LOGINFO("CHikChannel::MakeIFrame IFrame error");
	}

	HikRetHead retHead;
	if (sendSocket.Read((char*) &retHead, sizeof(HikRetHead)) < 0)
	{
		J_OS::LOGINFO("CHikChannel::MakeIFrame IFrame error");
	}

	retHead.retVal = ntohl(retHead.retVal);
	if (retHead.retVal != HIK_RET_OK && retHead.retVal != HIK_NO_SUPPORT)
	{
		m_pAdapter->Broken();
		return J_DEV_BROKEN;
	}

	return J_OK;
}

void CHikChannel::Convert2HikTime(time_t utcTime, HikTime &hikTime)
{
	tm *pTime = localtime(&utcTime);
	hikTime.ulYear = htonl(pTime->tm_year + 1900);
	hikTime.ulMonth = htonl(pTime->tm_mon + 1);
	hikTime.ulDay = htonl(pTime->tm_mday);
	hikTime.ulHour = htonl(pTime->tm_hour);
	hikTime.ulMinute = htonl(pTime->tm_min);
	hikTime.ulSecond = htonl(pTime->tm_sec);
}

int CHikChannel::SendCommand(int nCmd, const char *pSendData, int nDataLen)
{
	J_OS::CTCPSocket cmdSocket(m_pAdapter->GetRemoteIp(),
			m_pAdapter->GetRemotePort());
	if (cmdSocket.GetHandle().sock == j_invalid_socket_val)
		return J_INVALID_DEV;

	HikCommHead commHead;
	memset(&commHead, 0, sizeof(HikCommHead));
	commHead.len = htonl(sizeof(HikCommHead) + nDataLen);
	commHead.protoType = 90;//(THIS_SDK_VERSION < NETSDK_VERSION_V30) ? 90 : 99;
	commHead.command = htonl(nCmd);
	commHead.userId = htonl(m_pAdapter->GetUserId());
	m_pAdapter->GetLocalNetInfo(commHead.clientIP, commHead.clientMAC);
	commHead.checkSum = htonl(
			m_pAdapter->CheckSum((unsigned char*) &commHead,
					sizeof(HikCommHead)));

	if (cmdSocket.Write((char*) &commHead, sizeof(commHead)) < 0)
		return J_INVALID_DEV;

	if (pSendData != NULL && nDataLen != 0)
	{
		if (cmdSocket.Write(pSendData, nDataLen) < 0)
			return J_INVALID_DEV;
	}

	return J_OK;
}
