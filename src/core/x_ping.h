#ifndef __X_PING_H_
#define __X_PING_H_
#include "j_common.h"

#define PACKET_SIZE 4096

#ifdef WIN32
// IP header structure
typedef struct _iphdr 
{
	//Suppose the BYTE_ORDER is LITTLE_ENDIAN
	unsigned int   ip_hl:4;        // Length of the header
	unsigned int   version:4;      // Version of IP
	unsigned char  tos;            // Type of service
	unsigned short total_len;      // Total length of the packet
	unsigned short id;             // Unique identification
	unsigned short frag_offset;    // Fragment offset
	unsigned char  ttl;            // Time to live
	unsigned char  protocol;       // Protocol (TCP, UDP etc)
	unsigned short checksum;       // IP checksum
	unsigned int   sourceIP;       // Source IP
	unsigned int   destIP;         // Destination IP
} ip;
// ICMP header structure
// This is not the standard header, but we reserve space for time
typedef struct _icmphdr 
{
	BYTE   icmp_type;
	BYTE   icmp_code;                 // Type sub code
	USHORT icmp_cksum;
	USHORT icmp_id;
	USHORT icmp_seq;
	ULONG  icmp_data;
} icmp;
#define ICMP_ECHO				8
#define ICMP_ECHOREPLY	0
#endif

class CXPing
{
    public:
        CXPing();
        CXPing(const char *pAddr);
        ~CXPing();

    public:
        int SetAddr(const char *pAddr);
        int SendPacket();
        int RecvPacket();

    private:
        int Init();
        int Pack(int nPackNo, int nDataLen);
        int UnPack(int nLen);

    private:
        int m_socket;
        struct sockaddr_in m_destAddr;
        std::string m_addr;
        j_pid_t m_pid;
        char m_sendPacket[PACKET_SIZE];
        char m_recvPacket[PACKET_SIZE];
};
#endif // __X_PING_H_
