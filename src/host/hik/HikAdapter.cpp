#include "HikAdapter.h"
#include "HikChannel.h"
#include "HikIntercom.h"
#include "HikType.h"
#include "x_adapter_manager.h"

JO_IMPLEMENT_INTERFACE(Adapter, "hik", CHikAdapter::Maker)

CHikAdapter::CHikAdapter(int nDvrId, const char *pAddr, int nPort,
		const char *pUsername, const char *pPassword) :
	m_userId(0),  m_pAlarmSock(NULL), m_bStartAlarm(false)
{
	memset(m_remoteIP, 0, sizeof(m_remoteIP));
	memset(m_username, 0, sizeof(m_username));
	memset(m_password, 0, sizeof(m_password));

	m_remotePort = nPort;
	strcpy(m_remoteIP, pAddr);
	strcpy(m_username, pUsername);
	strcpy(m_password, pPassword);

	m_status = jo_dev_broken;
	Login();

	//定时检测设备状态
	m_timer.Create(5 * 1000, CHikAdapter::OnTimer, this);
	m_drvId = nDvrId;

	J_OS::LOGINFO("CHikAdapter::CHikAdapter(ip = %s, port = %d)", pAddr, nPort);
}

CHikAdapter::~CHikAdapter()
{
	if (Logout() == J_OK)
		m_status = jo_dev_broken;

	m_timer.Destroy();

	J_OS::LOGINFO("CHikAdapter::~CHikAdapter()");
}

///J_VideoAdapter
J_DevStatus CHikAdapter::GetStatus() const
{
	return m_status;
}

int CHikAdapter::Broken()
{
	Logout();

	return J_OK;
}

int CHikAdapter::MakeChannel(const char *pResid, void *&pObj, void *pOwner,
		int nChannel, int nStream, int nMode)
{
	CHikChannel *pChannel = new CHikChannel(pResid, pOwner, nChannel, nStream, nMode);
	if (NULL == pChannel)
		return J_MEMORY_ERROR;

	pObj = pChannel;

	return J_OK;
}

int CHikAdapter::EnableAlarm()
{
	if (m_bStartAlarm)
		return J_OK;

	if (m_pAlarmSock == NULL)
		m_pAlarmSock = new J_OS::CTCPSocket();

	m_pAlarmSock->Connect(m_remoteIP, m_remotePort);
	if (m_pAlarmSock->GetHandle().sock == j_invalid_socket_val)
		return J_INVALID_DEV;

	HikCommHead commHead;
	memset(&commHead, 0, sizeof(HikCommHead));
	commHead.len = htonl(sizeof(HikCommHead));
	commHead.protoType = 90;//(THIS_SDK_VERSION < NETSDK_VERSION_V30) ? 90 : 99;
	commHead.command = htonl(HIK_CMD_ALARMCHAN);
	commHead.userId = htonl(m_userId);
	GetLocalNetInfo(commHead.clientIP, commHead.clientMAC);
	commHead.checkSum = htonl(
			CheckSum((unsigned char*) &commHead, sizeof(HikCommHead)));

	if (m_pAlarmSock->Write((char*) &commHead, sizeof(commHead)) < 0)
		return J_INVALID_DEV;

	m_bStartAlarm = true;
	j_thread_parm parm = {0};
	parm.entry = CHikAdapter::AlarmThread;
	parm.data = this;
	m_threadAlarm.Create(parm);

	return J_OK;
}

int CHikAdapter::DisableAlarm()
{
	if (!m_bStartAlarm)
		return J_OK;

	m_bStartAlarm = false;

	if (m_pAlarmSock != NULL)
	{
		delete m_pAlarmSock;
		m_pAlarmSock = NULL;
	}

	m_threadAlarm.Release();

	return J_OK;
}

int CHikAdapter::EventAlarm(int nDvrId, int nChannel, int nAlarmType)
{
	return SingletonTmpl<CAdapterManager>::Instance()->OnAlarm(nDvrId, nChannel,
			nAlarmType);
}

int CHikAdapter::MakeVoice(const char *pResid, void *&pObj, void *pOwner, int nChannel)
{
	CHikIntercom *pIntercom = new CHikIntercom(pResid, pOwner, nChannel);
	if (NULL == pIntercom)
		return J_MEMORY_ERROR;

	pObj = pIntercom;

	return J_OK;
}

int CHikAdapter::Login()
{
	J_OS::CTCPSocket loginSocket(m_remoteIP, m_remotePort);
	if (loginSocket.GetHandle().sock == j_invalid_socket_val)
		return J_INVALID_DEV;

	struct LoginBuf
	{
		HikLoginHead loginHead;
		unsigned char name[32];
		unsigned char passwd[16];
	} loginBuf;

	HikLoginHead* loginHead = &loginBuf.loginHead;
	memset(&loginBuf, 0, sizeof(LoginBuf));
	loginHead->len = htonl(sizeof(LoginBuf));
	loginHead->protoType = 90;
	loginHead->IPProtoType = 0;
	loginHead->command = htonl(HIK_CMD_LOGIN);
	loginHead->DVRVersion = htonl(THIS_SDK_VERSION);
	GetLocalNetInfo(loginHead->clientIP, loginHead->clientMAC);
	loginHead->checkSum = htonl(
			CheckSum((unsigned char*) loginHead, sizeof(HikLoginHead)));

	strncpy((char*) loginBuf.name, m_username, 32);
	strncpy((char*) loginBuf.passwd, m_password, 16);

	if (loginSocket.Write((char*) &loginBuf, sizeof(LoginBuf)) < 0)
		return J_INVALID_DEV;

	struct LoginRetBuf
	{
		HikRetHead retHead;
		HikLoginRet retData;
	} loginRetBuf;

	int nReadLen = sizeof(HikRetHead);
	if (loginSocket.Read((char*) &loginRetBuf.retHead, nReadLen) < 0)
		return J_INVALID_DEV;

	loginRetBuf.retHead.checkSum = ntohl(loginRetBuf.retHead.checkSum);
	loginRetBuf.retHead.len = ntohl(loginRetBuf.retHead.len);
	loginRetBuf.retHead.retVal = ntohl(loginRetBuf.retHead.retVal);
	if (loginRetBuf.retHead.retVal != HIK_RET_OK)
		return J_INVALID_DEV;

	/*if (loginRetBuf.retHead.len != sizeof(loginRetBuf))
	{
		J_OS::LOGINFO("loginRetBuf.retHead.len != sizeof(loginRetBuf)");
		return J_DEV_PARAM_ERROR;
	}*/

	nReadLen = sizeof(HikLoginRet);
	if (loginSocket.Read((char*) &loginRetBuf.retData, nReadLen) < 0)
		return J_INVALID_DEV;

	loginRetBuf.retData.userID = ntohl(loginRetBuf.retData.userID);
	if (loginRetBuf.retData.userID <= 0)
	{
		J_OS::LOGINFO("loginRetBuf.retData.userID <= 0");
		return J_DEV_PARAM_ERROR;
	}
	m_userId = loginRetBuf.retData.userID;
	m_status = jo_dev_ready;

	return J_OK;
}

int CHikAdapter::Logout()
{
	int nRet = J_OK;
	if (m_status == jo_dev_ready)
	{
		//J_OS::LOGINFO("CHikAdapter::Logout() Begin");
		nRet = SendCommand(HIK_CMD_LOGOUT);
		m_userId = 0;
		m_status = jo_dev_broken;
		//J_OS::LOGINFO("CHikAdapter::Logout() End");
	}

	return nRet;
}

int CHikAdapter::SendCommand(int nCmd, const char *pSendData, int nDataLen)
{
	J_OS::CTCPSocket cmdSocket(m_remoteIP, m_remotePort);
	if (cmdSocket.GetHandle().sock == j_invalid_socket_val)
		return J_INVALID_DEV;

	HikCommHead commHead;
	memset(&commHead, 0, sizeof(HikCommHead));
	commHead.len = htonl(sizeof(HikCommHead) + nDataLen);
	commHead.protoType = 90/*(THIS_SDK_VERSION < NETSDK_VERSION_V30) ? 90 : 99*/;
	commHead.command = htonl(nCmd);
	commHead.userId = htonl(m_userId);
	GetLocalNetInfo(commHead.clientIP, commHead.clientMAC);
	commHead.checkSum = htonl(
			CheckSum((unsigned char*) &commHead, sizeof(HikCommHead)));

	if (cmdSocket.Write((char*) &commHead, sizeof(commHead)) < 0)
		return J_INVALID_DEV;

	if (pSendData != NULL && nDataLen != 0)
	{
		if (cmdSocket.Write(pSendData, nDataLen) < 0)
			return J_INVALID_DEV;
	}

	HikRetHead retHead;
	int nReadLen = sizeof(HikRetHead);
	if (cmdSocket.Read((char*) &retHead, nReadLen) < 0)
		return J_INVALID_DEV;

	retHead.len = ntohl(retHead.len);
	retHead.checkSum = ntohl(retHead.checkSum);
	retHead.retVal = ntohl(retHead.retVal);
	if (retHead.retVal != HIK_RET_OK)
		return J_INVALID_DEV;

	int nRetDataLen = retHead.len - sizeof(HikRetHead);
	if (nRetDataLen > 0)
	{
		char *pRetDataBuf = new char[nRetDataLen + 1];
		if (cmdSocket.Read((char*) pRetDataBuf, nRetDataLen) < 0)
		{
			delete pRetDataBuf;
			return J_INVALID_DEV;
		}
		delete pRetDataBuf;
	}

	return J_OK;
}

int CHikAdapter::GetLocalNetInfo(unsigned long & ipAddr, unsigned char* mac)
{
	int ret = -1;
#ifdef WIN32
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD dwRetVal=0;
	pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	if(GetAdaptersInfo(pAdapterInfo,&ulOutBufLen) != ERROR_SUCCESS)
	{
		GlobalFree(pAdapterInfo);
		pAdapterInfo=(IP_ADAPTER_INFO*)malloc(ulOutBufLen);
	}

	if((dwRetVal=GetAdaptersInfo(pAdapterInfo,&ulOutBufLen)) == NO_ERROR)
	{
		pAdapter=pAdapterInfo;
		while(pAdapter)
		{
			if(strstr(pAdapter->Description,"PCI") >= 0//pAdapter->Description中包含"PCI"为：物理网卡
				|| pAdapter->Type==71          //pAdapter->Type是71为：无线网卡
				)
			{
				printf("--------\n");
				printf("AdapterName:%s\n",pAdapter->AdapterName);
				printf("AdapterDesc:%s\n",pAdapter->Description);
				printf("AdapterAddr:");
				for(UINT i=0;i<pAdapter->AddressLength;i++)
				{
					sprintf((char *)(mac+2*i), "%02X",pAdapter->Address[i]);
				}
				printf("AdapterType:%d\n",pAdapter->Type);
				printf("IPAddress:%s\n",pAdapter->IpAddressList.IpAddress.String);
				printf("IPMask:%s\n",pAdapter->IpAddressList.IpMask.String);
			}
			pAdapter=pAdapter->Next;
		}
		//可能网卡有多IP,因此通过循环去判断
		IP_ADDR_STRING *pIpAddrString =&(pAdapter->IpAddressList);
		do 
		{
			ipAddr = inet_addr(pIpAddrString->IpAddress.String);
			pIpAddrString=pIpAddrString->Next;
		} while (pIpAddrString);
	}
	else
	{
		printf("CalltoGetAdaptersInfofailed\n");
	}

#else
	const char* devname = "eth0";
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct ifreq req;
	strcpy(req.ifr_name, devname);
	if (ioctl(sock, SIOCGIFHWADDR, &req) == 0)
	{
		memcpy(mac, req.ifr_hwaddr.sa_data, ETH_ALEN);
		ret = 0;
	}
	if (ret == 0)
	{
		if (ioctl(sock, SIOCGIFADDR, &req) < 0)
		{
			ret = -1;
		}
		else
		{
			ipAddr = ((struct sockaddr_in*) &req.ifr_addr)->sin_addr.s_addr;
		}
	}
	close(sock);
#endif

	return ret;
}

int CHikAdapter::Relogin()
{
	Logout();
	Login();
	return J_OK;
}

unsigned short CHikAdapter::CheckSum(unsigned char *addr, int count)
{
	register long sum = 0;
	while (count > 1)
	{
		sum += *(unsigned short*) addr++;
		count -= 2;
	}

	if (count > 0)
	{
		sum += *(unsigned char *) addr;
	}

	while (sum >> 16)
	{
		sum = (sum & 0xffff) + (sum >> 16);
	}

	return ~sum;
}

void CHikAdapter::UserExchange()
{
	if (m_status == jo_dev_broken)
	{
		int nRet = Login();
		J_OS::LOGINFO("CHikAdapter::UserExchange Relogin, ret = %d", nRet);
	}

	if (SendCommand(HIK_CMD_USEREXCHANGE, NULL, 0) < 0)
	{
		Logout();
		J_OS::LOGINFO("CHikAdapter::UserExchange error");
	}

	//J_OS::LOGINFO("CHikAdapter::UserExchange");
}

void CHikAdapter::OnAlarm()
{
	HikRetHead retHead;
	m_pAlarmSock->Read((char *) &retHead, sizeof(HikRetHead));

	HikRecvAlarmHead recvHead;
	HikAlarmInfo alarmInfo;
	while (m_bStartAlarm)
	{
		memset(&recvHead, 0, sizeof(HikRecvAlarmHead));
		m_pAlarmSock->Read((char *) &recvHead, sizeof(HikRecvAlarmHead));
		recvHead.length = ntohl(recvHead.length);
		recvHead.state = ntohl(recvHead.state);

		if (recvHead.state == NEEDRECVDATA)
		{
			memset(&alarmInfo, 0, sizeof(HikAlarmInfo));
			m_pAlarmSock->Read((char *) &alarmInfo, sizeof(HikAlarmInfo));
			alarmInfo.ulAlarmType = ntohl(alarmInfo.ulAlarmType);
			alarmInfo.ulAlarmInputNumber = ntohl(alarmInfo.ulAlarmInputNumber);
			alarmInfo.ulAlarmOutputNumber
					= ntohl(alarmInfo.ulAlarmOutputNumber);
			alarmInfo.ulAlarmRelateChannel = ntohl(
					alarmInfo.ulAlarmRelateChannel);
			alarmInfo.ulChannel = ntohl(alarmInfo.ulChannel);
			alarmInfo.ulDiskNumber = ntohl(alarmInfo.ulDiskNumber);

			if (alarmInfo.ulAlarmType != 2 && alarmInfo.ulAlarmType != 3
					&& alarmInfo.ulAlarmType != 6)
				return;

			switch (alarmInfo.ulAlarmType)
			{
			case 2:
				EventAlarm(m_drvId, alarmInfo.ulChannel, jo_video_lost);
				break;
			case 3:
				EventAlarm(m_drvId, alarmInfo.ulChannel, jo_video_motdet);
				break;
			case 6:
				EventAlarm(m_drvId, alarmInfo.ulChannel, jo_video_hide);
				break;
			}
		}
		else if (recvHead.state == EXCHANGE)
		{

		}
		else
		{
			char recvBuff[8000];
			m_pAlarmSock->Read((char *) recvBuff,
					recvHead.length - sizeof(HikRecvAlarmHead));
			//J_OS::LOGINFO("CHikAdapter::OnAlarm alarmState Undefined");
		}
	}
}