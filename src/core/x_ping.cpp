#include "x_ping.h"
#include "x_errtype.h"
#include "x_log.h"

#define RETRY_TIMES 5

static unsigned short cal_chksum(unsigned short *addr, int len)
{
    int nLeft = len;
    int sum = 0;
    unsigned short *w = addr;
    unsigned short answer = 0;

    //把ICMP报头二进制数据以2字节为单位累加起来
    while (nLeft > 1)
    {
        sum += *w++;
        nLeft -= 2;
    }
    if (nLeft == 1)
    {
        *(unsigned char *)(&answer) = *(unsigned char *)w;
        sum += answer;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    answer = ~sum;
    return answer;
}

CXPing::CXPing()
{
    m_socket = -1;
    memset(m_sendPacket, 0, sizeof(m_sendPacket));
    memset(m_recvPacket, 0, sizeof(m_recvPacket));
}

CXPing::CXPing(const char *pAddr)
{
    m_socket = -1;
    memset(m_sendPacket, 0, sizeof(m_sendPacket));
    memset(m_recvPacket, 0, sizeof(m_recvPacket));
    m_addr = pAddr;
	m_timeOutNum = RETRY_TIMES;

    Init();
}

CXPing::~CXPing()
{

}

int CXPing::SetAddr(const char *pAddr)
{
    m_addr = pAddr;
    Init();

    return J_OK;
}

int CXPing::SendPacket()
{
    int packet_size = Pack(1, 56);
BEGIN_SEND:
    if (int nRet = sendto(m_socket, m_sendPacket, packet_size, 0,
              (struct sockaddr *)&m_destAddr, sizeof(m_destAddr)) < 0)
    {
		if (errno == EAGAIN && nRet == 0)
		{
			--m_timeOutNum;
			goto BEGIN_SEND;
		}
		else if (errno == EAGAIN && nRet == 0)
		{
			j_sleep(1);
			goto BEGIN_SEND;
		}
		else if (errno == 0)
		{
		    return nRet;
		}
		m_timeOutNum = RETRY_TIMES;
        J_OS::LOGERROR("CXPing::SendPacket() sendto error fd = %d", m_socket);
        return J_SOCKET_ERROR;
    }

	m_timeOutNum = RETRY_TIMES;
    return J_OK;
}

int CXPing::RecvPacket()
{
    struct sockaddr_in from;
#ifdef WIN32
    j_int32_t from_len = sizeof(from);
#else
	socklen_t from_len = sizeof(from);
#endif
    int n = 0;
BEGIN_RECV:
    if ((n = recvfrom(m_socket, m_recvPacket, sizeof(m_recvPacket), 0,
            (struct sockaddr *)&from, &from_len)) < 0)
    {
		if (errno == EAGAIN && n == 0)
		{
			j_sleep(1);
			goto BEGIN_RECV;
		}
		else if (errno == EAGAIN && n == 0)
		{
			j_sleep(1);
			goto BEGIN_RECV;
		}
		else if (errno == 0)
		{
		    return n;
		}
		
		m_timeOutNum = RETRY_TIMES;
        J_OS::LOGERROR("CXPing::RecvPacket() recvfrom error");
        return J_SOCKET_ERROR;
    }
    if (UnPack(n) < 0)
    {
        return J_UNKNOW;
    }

	m_timeOutNum = RETRY_TIMES;
    return J_OK;
}

int CXPing::Init()
{
    struct protoent *protocol;
    if ((protocol = getprotobyname("icmp")) == NULL)
    {
        J_OS::LOGINFO("CXPing::Init() getprotobyname error");
        return J_UNKNOW;
    }

    //生成使用ICMP的原始套接字,这种套接字只有root才能生成
    if ((m_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
    {
        J_OS::LOGERROR("CXPing::Init() socket error");
        return J_UNKNOW;
    }

    //回收root权限,设置当前用户权限
#ifdef WIN32
#else
    setuid(getuid());
	bzero(&m_destAddr, sizeof(m_destAddr));
#endif
    //扩大套接字接收缓存区
    //int size = 50 * 1024;
    //setsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, (const char *)&size, sizeof(size));
    m_destAddr.sin_family = AF_INET;
	
	SetTTL(255);
	SetTimeOut(1, true);
	SetTimeOut(1, false);

    //判断是主机名还是IP地址
    unsigned long indaddr = 0L;
    if ((indaddr = inet_addr(m_addr.c_str())) == INADDR_NONE)
    {
        //是主机名
        struct hostent *host;
        if ((host = gethostbyname(m_addr.c_str())) == NULL)
        {
            J_OS::LOGINFO("CXPing::Init() gethostbyname error");
            return J_UNKNOW;
        }
        memcpy((char *)&m_destAddr.sin_addr, host->h_addr, host->h_length);
    }
    else
    {
        //是IP地址
		//J_OS::LOGINFO("%s", m_addr.c_str());
        m_destAddr.sin_addr.s_addr = indaddr;
    }
#ifdef WIN32
    m_pid.id = GetCurrentProcessId();
#else
	m_pid.id = getpid();
#endif

    return J_OK;
}

int CXPing::Pack(int nPackNo, int nDataLen)
{
    int packet_size = 0;
    icmp *icmp_head;

    icmp_head = (icmp *)m_sendPacket;
    icmp_head->icmp_type = ICMP_ECHO;
    icmp_head->icmp_code = 0;
    icmp_head->icmp_cksum = 0;
    icmp_head->icmp_seq = nPackNo;
    icmp_head->icmp_id = m_pid.id;
    packet_size = 8 + nDataLen;
#ifdef WIN32
#else
	struct timeval *tval;
    tval = (struct timeval *)icmp_head->icmp_data;
    gettimeofday(tval, NULL);
#endif
    icmp_head->icmp_cksum = cal_chksum((unsigned short *)icmp_head, packet_size);
    return packet_size;
}

int CXPing::UnPack(int nLen)
{
    int iphdrlen;
    ip *ip_head;
    icmp *icmp_head;
    int rtt = 0;

    ip_head = (ip *)m_recvPacket;
    iphdrlen = ip_head->ip_hl << 2;  //ip报长度为IP报头的长度标志*4
    icmp_head = (icmp *)(m_recvPacket + iphdrlen);
    nLen -= iphdrlen;
    if (nLen < 8)
    {
        J_OS::LOGINFO("CXPing::UnPack() length error");
        return J_SOCKET_ERROR;
    }

    if (icmp_head->icmp_type == ICMP_ECHOREPLY)
    {
		if (icmp_head->icmp_id == m_pid.id)
        {
#ifdef WIN32
#else
            struct timeval tvRecv;
            gettimeofday(&tvRecv, NULL);
            struct timeval *tvSend = (struct timeval *)icmp_head->icmp_data;
            rtt = (tvRecv.tv_sec - tvSend->tv_sec) * 1000
                + (tvRecv.tv_usec - tvSend->tv_usec) / 1000;
			return rtt;
#endif
        }
    }

    return -1;
}

int CXPing::SetTTL(int nValue)
{
	setsockopt(m_socket, IPPROTO_IP, IP_TTL, (char *)&nValue, sizeof(nValue));
	return J_OK;
}

int CXPing::SetTimeOut(int nTime, bool bRecv)
{
	struct timeval timeout;
	timeout.tv_sec = nTime;
	timeout.tv_usec = 0;
	setsockopt(m_socket, SOL_SOCKET, bRecv ? SO_RCVTIMEO : SO_SNDTIMEO, (char *)&timeout, sizeof(struct timeval));
	return J_OK;
}
