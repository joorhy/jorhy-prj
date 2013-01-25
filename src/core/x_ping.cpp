#include "x_ping.h"
#include "x_errtype.h"
#include "x_log.h"
#include <string.h>
#include <sys/time.h>

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
    if (sendto(m_socket, m_sendPacket, packet_size, 0,
              (struct sockaddr *)&m_destAddr, sizeof(m_destAddr)) < 0)
    {
        J_OS::LOGINFO("CXPing::SendPacket() sendto error");
        return J_SOCKET_ERROR;
    }

    return J_OK;
}

int CXPing::RecvPacket()
{
    struct sockaddr_in from;
    socklen_t from_len = sizeof(from);
    int n = 0;
    if ((n = recvfrom(m_socket, m_recvPacket, sizeof(m_recvPacket), 0,
            (struct sockaddr *)&from, &from_len)) < 0)
    {
        J_OS::LOGINFO("CXPing::RecvPacket() sendto error");
        return J_SOCKET_ERROR;
    }

    if (UnPack(n) < 0)
    {
        return J_UNKNOW;
    }

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
    if ((m_socket = socket(AF_INET, SOCK_RAW, protocol->p_proto)) < 0)
    {
        J_OS::LOGINFO("CXPing::Init() socket error");
        return J_UNKNOW;
    }

    //回收root权限,设置当前用户权限
    setuid(getuid());
    //扩大套接字接收缓存区
    int size = 50 * 1024;
    setsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
    bzero(&m_destAddr, sizeof(m_destAddr));
    m_destAddr.sin_family = AF_INET;

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
        m_destAddr.sin_addr.s_addr = indaddr;
    }
    m_pid = getpid();

    return J_OK;
}

int CXPing::Pack(int nPackNo, int nDataLen)
{
    int packet_size = 0;
    struct icmp *icmp;
    struct timeval *tval;

    icmp = (struct icmp *)m_sendPacket;
    icmp->icmp_type = ICMP_ECHO;
    icmp->icmp_code = 0;
    icmp->icmp_cksum = 0;
    icmp->icmp_seq = nPackNo;
    icmp->icmp_id = m_pid;
    packet_size = 8 + nDataLen;
    tval = (struct timeval *)icmp->icmp_data;
    gettimeofday(tval, NULL);
    icmp->icmp_cksum = cal_chksum((unsigned short *)icmp, packet_size);
    return packet_size;
}

int CXPing::UnPack(int nLen)
{
    int iphdrlen;
    struct ip *ip;
    struct icmp *icmp;
    int rtt = 0;

    ip = (struct ip *)m_recvPacket;
    iphdrlen = ip->ip_hl << 2;  //ip报长度为IP报头的长度标志*4
    icmp = (struct icmp *)(m_recvPacket + iphdrlen);
    nLen -= iphdrlen;
    if (nLen < 8)
    {
        J_OS::LOGINFO("CXPing::UnPack() length error");
        return J_SOCKET_ERROR;
    }

    if (icmp->icmp_id == m_pid)
    {
         if (icmp->icmp_type == ICMP_ECHOREPLY)
        {
            struct timeval tvRecv;
            gettimeofday(&tvRecv, NULL);
            struct timeval *tvSend = (struct timeval *)icmp->icmp_data;
            rtt = (tvRecv.tv_sec - tvSend->tv_sec) * 1000
                + (tvRecv.tv_usec - tvSend->tv_usec) / 1000;
        }
        else
        {
            return -1;
        }
    }

    return rtt;
}
