#include "x_asio_udp_win.h"
#include "x_errtype.h"
#include "j_module.h"
#include "x_socket.h"

JO_IMPLEMENT_SINGLETON(XUdpAsio)

CXUdpAsio::CXUdpAsio()
{
	m_bStarted = false;
	WSADATA wsaData; 
	WSAStartup(MAKEWORD(2,2), &wsaData);
}

CXUdpAsio::~CXUdpAsio()
{
	Deinit();
	WSACleanup();
}

int CXUdpAsio::Init(j_int32_t nPort, J_Obj *ioUser)
{
	if (!m_bStarted)
	{
		m_hCompletionPort = INVALID_HANDLE_VALUE;
		if ((m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL)
		{
			J_OS::LOGINFO( "CRdAsio::Init() CreateIoCompletionPort failed with error: %d\n", GetLastError());
			return J_SOCKET_ERROR;
		} 

		m_listenSocket.sock = socket(AF_INET, SOCK_DGRAM, 0);
		sockaddr_in localAddr={0}; 
		localAddr.sin_family=AF_INET;
		localAddr.sin_port=htons(nPort);
		localAddr.sin_addr.S_un.S_addr=INADDR_ANY; 
		 bind(m_listenSocket.sock, (sockaddr*)&localAddr, sizeof(sockaddr_in)); 

		int retval;
		setsockopt(m_listenSocket.sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&retval, sizeof(int));
		if (CreateIoCompletionPort((HANDLE)m_listenSocket.sock, m_hCompletionPort, (DWORD)&m_listenSocket, 1) == NULL)
		{
			J_OS::LOGINFO("CXUdpAsio::Init CreateIoCompletionPort failed with error %d\n", WSAGetLastError());
			return J_SOCKET_ERROR;
		}

		m_bStarted = true;
		j_thread_parm parm = {0};
		parm.entry = CXUdpAsio::WorkThread;
		parm.data = this;
		m_workThread.Create(parm);
	}
	return J_OK;
}

void CXUdpAsio::Deinit()
{
	if (m_bStarted)
	{
		m_bStarted = false;
		m_workThread.Release();

		j_close_socket(m_listenSocket.sock);
		if (m_hCompletionPort != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hCompletionPort);
			m_hCompletionPort = INVALID_HANDLE_VALUE;
		}
	}
}

void CXUdpAsio::OnWork()
{
	DWORD dwBytesTransferred;
	LPOVERLAPPED Overlapped;
	DWORD dwFlag = 0;
	J_AsioDataBase *pPerIoData;        
	DWORD SendBytes, RecvBytes;
	DWORD Flags;
	while (m_bStarted)
	{
		SetLastError(ERROR_SUCCESS);
		if (GetQueuedCompletionStatus(m_hCompletionPort, &dwBytesTransferred, (LPDWORD)&dwFlag, (LPOVERLAPPED *)&pPerIoData, 1000) == 0)
		{
			DWORD dwError = WSAGetLastError();
			if (dwError == WAIT_TIMEOUT)
			{
				j_sleep(1);
			}
			else
			{
				J_OS::LOGINFO("CXUdpAsio::OnWork GetQueuedCompletionStatus failed with error %d %d", dwError, pPerIoData);
			}
			continue;
		}
		// 检查数据传送完了吗
		if (dwBytesTransferred)
		{
			DWORD dwError = WSAGetLastError();
			if (dwError != ERROR_SUCCESS && dwError != ERROR_IO_PENDING)
			{
				J_OS::LOGINFO("CXUdpAsio::OnWork Broken %d sock=%d", WSAGetLastError(), pPerIoData->ioHandle);
				continue;
			}
		}  
		if (pPerIoData->ioCall == J_AsioDataBase::j_recvfrom_e)
		{
			//read
			j_sleep(1);
			pPerIoData->ioReceiveFrom.finishedLen = dwBytesTransferred;
			try 
			{
				J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>((J_Obj *)pPerIoData->ioUser);
				pAsioUser->OnRead(pPerIoData, J_OK);
			}
			catch(...)
			{
				J_OS::LOGINFO("1");
			}
		}
		else if (pPerIoData->ioCall == J_AsioDataBase::j_sendto_e)
		{
			//write
			j_sleep(1);
			pPerIoData->ioSendTo.finishedLen = dwBytesTransferred;
			try 
			{
				J_AsioUser *pAsioUser = dynamic_cast<J_AsioUser *>((J_Obj *)pPerIoData->ioUser);
				pAsioUser->OnWrite(pPerIoData, J_OK);
			}
			catch(...)
			{
				J_OS::LOGINFO("2");
			}
		}
	}
}

int CXUdpAsio::Read(J_AsioDataBase *pAsioData)
{
	DWORD Flags = 0;
	WSABUF buf;
	DWORD dwFinishedLen = 0;
	INT nRromLen = sizeof(sockaddr_in);
	DWORD dwError = SOCKET_ERROR;
	pAsioData->ioHandle = m_listenSocket.sock;

	buf.len = pAsioData->ioReceiveFrom.bufLen;
	buf.buf = pAsioData->ioReceiveFrom.buf;
	dwError = WSARecvFrom(m_listenSocket.sock, &buf, 1, (LPDWORD)&dwFinishedLen, &Flags, 
		(sockaddr *)&pAsioData->ioReceiveFrom.sender, &nRromLen, pAsioData, NULL);
	
	if (dwError == SOCKET_ERROR)
	{
		dwError = WSAGetLastError();
		if (dwError != ERROR_IO_PENDING)
		{
			J_OS::LOGINFO("WSARecvFrom error = %d", dwError);
		}
	}
	return 0;
}

int CXUdpAsio::Write(J_AsioDataBase *pAsioData)
{
	WSABUF buf;
	buf.buf = (CHAR *)pAsioData->ioSendTo.buf;
	buf.len = pAsioData->ioSendTo.bufLen;
	pAsioData->ioHandle = m_listenSocket.sock;
	pAsioData->ioCall = J_AsioDataBase::j_sendto_e;
	if (WSASendTo(m_listenSocket.sock, &buf, 1, (LPDWORD)&pAsioData->ioSendTo.finishedLen, 0, 
		(sockaddr *)&pAsioData->ioSendTo.receiver, sizeof(sockaddr_in), pAsioData, NULL) == SOCKET_ERROR)
	{
		DWORD dwError = WSAGetLastError();
		if (dwError != ERROR_IO_PENDING)
		{
			J_OS::LOGINFO("WSASendTo error = %d", dwError);
		}
	}

	return J_OK;
}