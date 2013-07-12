#include "HikAdapter.h"
#include "HikIntercom.h"

CHikIntercom::CHikIntercom(const char *pResid, J_Obj *pOwner, int nChannel)
: m_pAdapter(NULL)
{
	m_pAdapter = dynamic_cast<CHikAdapter *>(pOwner);
	m_recvSocket = NULL;
}

CHikIntercom::~CHikIntercom()
{

}


int CHikIntercom::OpenStream(J_Obj *&pObj, CRingBuffer *pRingBuffer)
{
	StartVoice();
	return J_OK;
}

int CHikIntercom::CloseStream(J_Obj *pObj, CRingBuffer *pRingBuffer)
{
	return J_OK;
}

int CHikIntercom::GetCompressType()
{
	return J_OK;
}

int CHikIntercom::StartVoice()
{
	if (m_recvSocket != NULL)
	{
		delete m_recvSocket;
		m_recvSocket = NULL;
	}
	m_recvSocket = new J_OS::CTCPSocket();
	m_recvSocket->Connect(m_pAdapter->GetRemoteIp(),
			m_pAdapter->GetRemotePort());

	struct StartVoice
	{
		HikCommHead commHead;
		HikReserve4 reserve;
	} startVoice;
	memset(&startVoice, 0, sizeof(StartVoice));
	startVoice.commHead.len = htonl(sizeof(StartVoice));
	startVoice.commHead.protoType = /*(THIS_SDK_VERSION < NETSDK_VERSION_V30) ? 90 : */99;
	startVoice.commHead.command = htonl(HIK_START_VOICECOM_V30);
	startVoice.commHead.userId = htonl(m_pAdapter->GetUserId());
	m_pAdapter->GetLocalNetInfo(startVoice.commHead.clientIP, startVoice.commHead.clientMAC);
	startVoice.commHead.checkSum = htonl(
			m_pAdapter->CheckSum((unsigned char*) &startVoice.commHead,
					sizeof(HikCommHead)));

	if (m_recvSocket->Write((char*) &startVoice, sizeof(startVoice)) < 0)
	{
		J_OS::LOGINFO("CHikIntercom::StartVoice() error");
		return J_SOCKET_ERROR;
	}

	HikRetHead retHead;
	if (m_recvSocket->Read((char*) &retHead, sizeof(HikRetHead)) < 0)
	{
		J_OS::LOGINFO("CHikIntercom::StartVoice() error");
		return J_SOCKET_ERROR;
	}

	retHead.retVal = ntohl(retHead.retVal);
	retHead.len = ntohl(retHead.len);
	if (retHead.retVal != HIK_RET_OK)
	{
		m_pAdapter->Broken();
		return J_DEV_BROKEN;
	}

	j_thread_parm parm = {0};
	parm.entry = CHikIntercom::WorkThread;
	parm.data = this;
	sendThread.Create(parm);

	return J_OK;
}

int CHikIntercom::StopVoice()
{
	sendThread.Release();
	return J_OK;
}

void CHikIntercom::OnWork()
{
	static FILE* fp = NULL;
	if (fp == NULL)
		fp = fopen("test3.ogg", "rb+");
	static FILE *fp2 = NULL;
	if (fp2 == NULL)
		fp2 = fopen("test2.ogg", "wb+");

	struct SendBuff
	{
		int num;
		char data[80];
	} sendBuff;
	char recv_buff[8000];
	HikRecvVoiceHead voiceHead;
	while (true)
	{
		sendBuff.num = htonl(1);
		fread(sendBuff.data, 1, 80, fp);
		m_recvSocket->Write_n((char *)&sendBuff, sizeof(SendBuff));
		m_recvSocket->Read_n((char*) &voiceHead, sizeof(HikRecvVoiceHead));
		voiceHead.length = ntohl(voiceHead.length);
		voiceHead.state = ntohl(voiceHead.state);
		if (voiceHead.state == NEEDRECVDATA)
		{
			m_recvSocket->Read_n((char*)recv_buff, voiceHead.length - sizeof(HikRecvVoiceHead));
			fwrite(recv_buff, 1, voiceHead.length - sizeof(HikRecvVoiceHead), fp2);
		}
	}
}
