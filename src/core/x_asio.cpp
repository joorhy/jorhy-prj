#include "x_asio.h"
#include "x_errtype.h"
#include "j_module.h"

CRdAsio::CRdAsio(int)
{
	m_bStarted = false;
}

CRdAsio::~CRdAsio()
{

}

int CRdAsio::Init()
{
	if (!m_bStarted)
	{
#ifdef WIN32
		FD_ZERO(&m_fdSet); 
		m_timeout.tv_sec = 1;
		m_timeout.tv_usec = 0;
#else
		m_epoll_fd = 0;
		m_epoll_fd = epoll_create(JO_MAX_ASIOSIZE);
#endif

		m_bStarted = true;
		j_thread_parm parm = {0};
		parm.entry = CRdAsio::WorkThread;
		parm.data = this;
		m_workThread.Create(parm);
	}
	return J_OK;
}

void CRdAsio::Deinit()
{
	if (m_bStarted)
	{
		m_bStarted = false;
		m_workThread.Release();

#ifdef WIN32
		FD_ZERO(&m_fdSet); 
#else
		if (m_epoll_fd != 0)
		{
			close (m_epoll_fd);
			m_epoll_fd = 0;
		}
#endif
	}
}

int CRdAsio::AddUser(j_socket_t nSocket, J_AsioUser *pUser)
{
	TLock(m_locker);
	m_asioMap[nSocket] = pUser;
#ifdef WIN32
	FD_SET(nSocket.sock, &m_fdSet);
#else
	m_evAsio.events = EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP;
	m_evAsio.data.fd = nSocket.sock;

	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, nSocket.sock, &m_evAsio) < 0)
	{
		J_OS::LOGERROR("CRdAsio::AddUser epoll set insertion error");
		return J_SOCKET_ERROR;
	}
#endif
	EnableKeepalive(nSocket);

	J_OS::LOGINFO("CRdAsio::AddUser epoll set insertion sucess fd = %d", nSocket.sock);
	TUnlock(m_locker);

	return J_OK;
}

void CRdAsio::DelUser(j_socket_t nSocket)
{
	TLock(m_locker);
	AsioMap::iterator it = m_asioMap.find(nSocket);
	if (it != m_asioMap.end())
	{
		m_asioMap.erase(it);
	}
#ifdef WIN32
#else
	m_evAsio.events = EPOLLIN | EPOLLRDHUP;
	m_evAsio.data.fd = nSocket.sock;
	epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, nSocket.sock, &m_evAsio);
#endif
	J_OS::LOGINFO("CRdAsio::DelUser epoll set insertion sucess fd = %d", nSocket.sock);
	TUnlock(m_locker);
}

void CRdAsio::OnWork()
{
#ifdef WIN32
#else
	int nfds = 0;
	int i = 0;
	j_socket_t active_fd;
	pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
	while (m_bStarted)
	{
		pthread_testcancel();
		nfds = epoll_wait(m_epoll_fd, m_evConnect, 1024, 1000);
		if (nfds < 0)
		{
			usleep(10);
			if (errno == EINTR)
			{
				continue;
			}
			else
				break;
		}

		for (i = 0; i < nfds; i++)
		{
			if ((m_evConnect[i].events & EPOLLRDHUP) && (m_evConnect[i].events & EPOLLIN))
			{
				//broken
				TLock(m_locker);
				active_fd.sock = m_evConnect[i].data.fd;
				AsioMap::iterator it = m_asioMap.find(active_fd);
				if (it != m_asioMap.end())
				{
                    J_AsioUser *pAsioUser = static_cast<J_AsioUser *>(it->second);
					if (pAsioUser)
						pAsioUser->OnBroken(active_fd.sock);

					m_asioMap.erase(it);
					epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, active_fd.sock, &m_evConnect[i]);
				}
				TUnlock(m_locker);
			}
			else if (m_evConnect[i].events & EPOLLIN)
			{
				//read
				TLock(m_locker);
				active_fd.sock = m_evConnect[i].data.fd;
				AsioMap::iterator it = m_asioMap.find(active_fd);
				if (it != m_asioMap.end())
				{
					J_AsioUser *pAsioUser = static_cast<J_AsioUser *>(it->second);
					if (pAsioUser)
						pAsioUser->OnRead(active_fd.sock);
				}

				m_evAsio.events = EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP;
				m_evAsio.data.fd = active_fd.sock;
				epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, active_fd.sock, &m_evAsio);
				TUnlock(m_locker);
			}
		}
	}
#endif
}

void CRdAsio::EnableKeepalive(j_socket_t sock)
{
	//开启tcp探测
	int keepAlive = 1; 		// 开启keepalive属性
	setsockopt(sock.sock, SOL_SOCKET, SO_KEEPALIVE, (const char *)&keepAlive, sizeof(keepAlive));
#ifdef WIN32
	tcp_keepalive alive_in                = {0};
	tcp_keepalive alive_out              = {0};
	alive_in.keepalivetime                = 3000;                // 开始首次KeepAlive探测前的TCP空闭时间
	alive_in.keepaliveinterval			 = 1000;				// 两次KeepAlive探测间的时间间隔
	alive_in.onoff                             = TRUE;
	unsigned long ulBytesReturn = 0;
	WSAIoctl(sock.sock, SIO_KEEPALIVE_VALS, &alive_in, sizeof(alive_in), &alive_out, sizeof(alive_out), &ulBytesReturn, NULL, NULL);
#else
	int keepIdle = 3; 				// 如该连接在3秒内没有任何数据往来,则进行探测
	int keepInterval = 1;			// 探测时发包的时间间隔为2秒
	//int keepCount = 3; 		// 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.
	setsockopt(sock.sock, SOL_TCP, TCP_KEEPIDLE, (void*)&keepIdle, sizeof(keepIdle));
	setsockopt(sock.sock, SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
#endif
}

