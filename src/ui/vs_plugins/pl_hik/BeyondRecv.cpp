#include "StdAfx.h"
#include "BeyondRecv.h"
#include "pl_type.h"
#include <fstream>
using namespace std;
ofstream hikFile("C:\\Users\\RY-yuanjiajun\\Desktop\\movie\\record\\hik",ios::binary);

BeyondRecv::BeyondRecv(void)
{
	m_socket = NULL;
	m_bStart = TRUE;
	m_hPauseEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_bPause = FALSE;
}


BeyondRecv::~BeyondRecv(void)
{
	StopRecv();
	CloseHandle(m_hPauseEvent);
	m_hPauseEvent = NULL;
}


BOOL BeyondRecv::StartRecv(char *psz_mrl,BeyondBuffer *pBuff)
{
	char IP[32] = {0};
	int port;
	GetAddr(IP,port,psz_mrl);
	if(pBuff)
		m_pBuff = pBuff;
	else
		return FALSE;
	m_socket = new BeyondSocket(IP,port);
	if(m_socket)
	{
		char request[256] = {0};
		MakeHttpRequst(request,psz_mrl);
		if(m_socket->Write(request,sizeof(request)) <= 0)
			return FALSE;
	}
	CreateThread(NULL,0,BeyondRecv::RecvThread,this,0,NULL);
	return TRUE;
}
BOOL BeyondRecv::StopRecv()
{
	PauseRecv(FALSE);
	m_bStart = FALSE;
	return TRUE;
}

BOOL BeyondRecv::GetAddr(char *OUT_ip,int &OUT_port,char *IN_mrl)
{
	if(IN_mrl == NULL)
		return FALSE;

	char *star	= strstr(IN_mrl,"://");
	if(star)
	{
		star += strlen("://");
		while(*star != ':' || *star == '\0')
		{
			*OUT_ip = *star;
			OUT_ip++;star++;
		}
	}
	else
		return FALSE;
	if(*star != '\0')
	{
		star++;
		char port[16];
		int i = 0;
		while(*(star+i) != '/' || *(star+i) == '\0')
		{
			port[i] = *(star+i);
			i++;
		}
		OUT_port = atoi(port);
	}
	else
		return FALSE;

	return TRUE;
}

BOOL BeyondRecv::MakeHttpRequst(char *OUT_request,char *IN_mrl)
{
	if(!OUT_request || ! IN_mrl)
		return FALSE;

	char *start = strstr(IN_mrl,"://");
	if(start)
	{
		start += strlen("://");
		start = strstr(start,"/");
		if(start)
		{
			char tmp[128] = {0};
			int i=0;
			while(*(start+i) != '\0')
			{
				tmp[i] = *(start+i);
				i++;
			}
			sprintf(OUT_request,"GET %s "CUSTOM_VERSION"\r\n\r\n",tmp);
		}
	}
	return TRUE;
}

DWORD WINAPI BeyondRecv::RecvThread(void *param)
{
	BeyondRecv *pThis = reinterpret_cast<BeyondRecv*>(param);
	if(pThis)
		pThis->RecvData();
	return TRUE;
}

void BeyondRecv::RecvData()
{
	char *pRecvBuff = new char[DEFAULT_RECVBUFFSIZE];
	memset(pRecvBuff,0,DEFAULT_RECVBUFFSIZE);
	StreamHeader header = {0};

	int len = m_socket->Read(pRecvBuff,19);
	TRACE("Request Len:%d\n",len);
	if(len < 0)
	{
		TRACE("Get Request:error\n");
		delete pRecvBuff;
		return;
	}
	else
	{
		if(!strstr(pRecvBuff,CUSTOM_VERSION"200"))
		{
			delete pRecvBuff;
			return;
		}
	}
	while(m_bStart)
	{
		
		if(m_bPause)
		{
			TRACE("recvie pause\n");
			WaitForSingleObject(m_hPauseEvent,INFINITE);
		}
		TRACE("READ Head front\n");
		if(m_socket->Read_n((char *)&header,sizeof(StreamHeader)) < 0)
		{
			TRACE("Read head:error\n");
			break;
		}
		TRACE("READ Head end\n");
		header.VideoTypeFCC = (unsigned long)ntohl(header.VideoTypeFCC);
		if(header.VideoTypeFCC == HIKFOURCC)
		{
			TRACE("hik fourcc!\n");
		}
		header.datalen = (unsigned int)ntohl(header.datalen);
		TRACE("header.datalen=%u\n",header.datalen);
		header.datatype = (unsigned int)ntohl(header.datatype);

		if(header.datalen > 0)
		{
			TRACE("READ BODY front\n");
			if(m_socket->Read_n(pRecvBuff,header.datalen) < 0)
			{
				TRACE("Read body:error\n");
				break;
			}
			TRACE("READ BODY end\n");
			TRACE("PUSH buffer front\n");
			hikFile.write(pRecvBuff,header.datalen);
			m_pBuff->PushBuffer(pRecvBuff,header);
			TRACE("PUSH buffer end\n");
		}
		Sleep(1);
	}
	delete pRecvBuff;
	TRACE("Receive thread exit\n");
}



BOOL BeyondRecv::PauseRecv(BOOL bPause)
{
	if(bPause)		
	{
		if(m_bPause)
			return TRUE;
		else
		{
			m_bPause = FALSE;
			SetEvent(m_hPauseEvent);
			char *pauseCancle = CUSTOM_VERSION"play\r\n\r\n";
			m_socket->Write(pauseCancle,sizeof(pauseCancle));

		}
	}
	else
	{
		if(m_bPause)
		{
			m_bPause = TRUE;
			char *pauseOK = CUSTOM_PROTOCOL"/"CUSTOM_VERSION"pause\r\n\r\n";
			m_socket->Write(pauseOK,sizeof(pauseOK));
		}
		else
			return TRUE;
	}
	return TRUE;
}

BOOL BeyondRecv::SetSpeedRecv(BOOL bSpeed)
{
	char speedStr[32] = {0};
	if(bSpeed)
		sprintf(speedStr,CUSTOM_PROTOCOL"/"CUSTOM_VERSION"fast\r\n\r\n");
	else
		sprintf(speedStr,CUSTOM_PROTOCOL"/"CUSTOM_VERSION"slow\r\n\r\n");

	if(m_socket->Write(speedStr,sizeof(speedStr)) < 0)
		return FALSE;
	return TRUE;
}

BOOL BeyondRecv::VodJumpRecv(char *pNewMrl)
{
	return TRUE;
}