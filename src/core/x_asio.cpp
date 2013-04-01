#include "x_asio.h"
#include "x_errtype.h"
#include "j_module.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

CRdAsio::CRdAsio(int)
{
	m_workThread = 0;
	m_bStarted = false;
}

CRdAsio::~CRdAsio()
{

}

int CRdAsio::Init()
{
	if (!m_bStarted)
	{
		m_epoll_fd = 0;
		m_epoll_fd = epoll_create(JO_MAX_ASIOSIZE);

		m_workThread = 0;
		m_bStarted = true;
		pthread_create(&m_workThread, NULL, WorkThread, this);
		pthread_detach(m_workThread);
	}
	return J_OK;
}

void CRdAsio::Deinit()
{
	if (m_bStarted)
	{
		m_bStarted = false;
		if (m_workThread != 0)
		{
			pthread_cancel(m_workThread);
			m_workThread = 0;
		}

		if (m_epoll_fd != 0)
		{
			close (m_epoll_fd);
			m_epoll_fd = 0;
		}
	}
}

int CRdAsio::AddUser(int nSocket, J_AsioUser *pUser)
{
	TLock(m_locker);
	m_asioMap[nSocket] = pUser;
	m_evAsio.events = EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP;
	m_evAsio.data.fd = nSocket;

	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, nSocket, &m_evAsio) < 0)
	{
		J_OS::LOGERROR("CRdAsio::AddUser epoll set insertion error");
		return J_SOCKET_ERROR;
	}
	EnableKeepalive(nSocket);

	J_OS::LOGINFO("CRdAsio::AddUser epoll set insertion sucess fd = %d", nSocket);
	TUnlock(m_locker);

	return J_OK;
}

void CRdAsio::DelUser(int nSocket)
{
	TLock(m_locker);
	AsioMap::iterator it = m_asioMap.find(nSocket);
	if (it != m_asioMap.end())
	{
		m_asioMap.erase(it);
	}
	m_evAsio.events = EPOLLIN | EPOLLRDHUP;
	m_evAsio.data.fd = nSocket;
	epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, nSocket, &m_evAsio);
	J_OS::LOGINFO("CRdAsio::DelUser epoll set insertion sucess fd = %d", nSocket);
	TUnlock(m_locker);
}

void CRdAsio::OnWork()
{
	int nfds = 0;
	int i = 0;
	int active_fd = 0;
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
				active_fd = m_evConnect[i].data.fd;
				AsioMap::iterator it = m_asioMap.find(active_fd);
				if (it != m_asioMap.end())
				{
                    J_AsioUser *pAsioUser = static_cast<J_AsioUser *>(it->second);
					if (pAsioUser)
						pAsioUser->OnBroken(active_fd);

					m_asioMap.erase(it);
					epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, active_fd, &m_evConnect[i]);
				}
				TUnlock(m_locker);
			}
			else if (m_evConnect[i].events & EPOLLIN)
			{
				//read
				TLock(m_locker);
				active_fd = m_evConnect[i].data.fd;
				AsioMap::iterator it = m_asioMap.find(active_fd);
				if (it != m_asioMap.end())
				{
					J_AsioUser *pAsioUser = static_cast<J_AsioUser *>(it->second);
					if (pAsioUser)
						pAsioUser->OnRead(active_fd);
				}

				m_evAsio.events = EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLHUP;
				m_evAsio.data.fd = active_fd;
				epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, active_fd, &m_evAsio);
				TUnlock(m_locker);
			}
		}
	}
}

void CRdAsio::EnableKeepalive(int nSocket)
{
    //开启tcp探测
    int keepAlive = 1; 		// 开启keepalive属性
    int keepIdle = 3; 		// 如该连接在3秒内没有任何数据往来,则进行探测
    int keepInterval = 1;	// 探测时发包的时间间隔为2秒
    int keepCount = 3; 		// 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.
    setsockopt(nSocket, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, sizeof(keepAlive));
    setsockopt(nSocket, SOL_TCP, TCP_KEEPIDLE, (void*)&keepIdle, sizeof(keepIdle));
    setsockopt(nSocket, SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
    setsockopt(nSocket, SOL_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));
}

